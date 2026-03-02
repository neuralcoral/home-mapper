import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from IPython.display import HTML

class Leg:
    def __init__(self, femur_length=4.0, tibia_length=6.0, hip_origin=(0, 0, 0), tolerance=1e-3):
        self.l_femur = femur_length
        self.l_tibia = tibia_length
        self.hip_origin = np.array(hip_origin)
        self.tolerance = tolerance

    def calculate_ik(self, x, y, z):
        """Calculates 0-180 servo angles for a target (x, y, z) coordinate."""
        # 1. Shift target to the Hip's local reference frame
        x_rel = x - self.hip_origin[0]
        y_rel = y - self.hip_origin[1]
        z_rel = z - self.hip_origin[2]

        # 2. Calculate horizontal distance from hip
        r = np.sqrt(x_rel**2 + y_rel**2)
        r_remaining = r - self.l_femur

        # 3. Reachability Check
        L_req = np.sqrt(r_remaining**2 + z_rel**2)
        if abs(L_req - self.l_tibia) > self.tolerance:
            raise ValueError(f"Target ({x:.2f}, {y:.2f}, {z:.2f}) is out of reach.")

        # 4. Calculate mathematical angles
        theta1_math = np.degrees(np.atan2(y_rel, x_rel))
        theta2_math = np.degrees(np.atan2(z_rel, r_remaining))

        # 5. Map to 0-180 Servos
        femur_servo = theta1_math + 90
        tibia_servo = theta2_math + 180

        return {
            "femur": max(0, min(180, femur_servo)),
            "tibia": max(0, min(180, tibia_servo))
        }

    def get_joint_positions(self, angles):
        """Converts servo angles into 3D Cartesian points for the joints."""
        # Reverse servo mapping back to math radians for plotting
        t1 = np.radians(angles['femur'] - 90)
        t2 = np.radians(angles['tibia'] - 180)

        # Joint 0: Origin (Hip mount)
        p0 = self.hip_origin

        # Joint 1: End of Femur (Knee)
        p1 = p0 + np.array([self.l_femur * np.cos(t1), self.l_femur * np.sin(t1), 0])

        # Joint 2: End of Tibia (Foot tip)
        r_tibia_xy = self.l_tibia * np.cos(t2)
        p2 = p1 + np.array([r_tibia_xy * np.cos(t1), r_tibia_xy * np.sin(t1), self.l_tibia * np.sin(t2)])

        return np.array([p0, p1, p2])

class LegVisualizer:
    def __init__(self, leg):
        self.leg = leg
    def plot(self, target_x, target_y, target_z, elev=30, azim=-60):
        """Generates a static 3D plot of the leg reaching a target."""
        try:
            angles = self.leg.calculate_ik(target_x, target_y, target_z)
            points = self.leg.get_joint_positions(angles)
        except ValueError as e:
            print(f"Cannot plot: {e}")
            return

        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')

        # Set the camera angle
        ax.view_init(elev=elev, azim=azim)

        ax.plot(points[:, 0], points[:, 1], points[:, 2], '-o', linewidth=3, markersize=8)

        toe_x, toe_y, toe_z = points[2]
        ax.text(toe_x, toe_y, toe_z, f"  ({toe_x:.2f}, {toe_y:.2f}, {toe_z:.2f})", color='red')

        ax.set_xlabel('X (cm)')
        ax.set_ylabel('Y (cm)')
        ax.set_zlabel('Z (cm)')
        ax.set_title(f'Target: ({target_x}, {target_y}, {target_z})')

        # Keep axes equal
        max_range = np.array([points[:,0].max()-points[:,0].min(), points[:,1].max()-points[:,1].min(), points[:,2].max()-points[:,2].min()]).max() / 2.0
        mid_x = (points[:,0].max()+points[:,0].min()) * 0.5
        mid_y = (points[:,1].max()+points[:,1].min()) * 0.5
        mid_z = (points[:,2].max()+points[:,2].min()) * 0.5
        ax.set_xlim(mid_x - max_range, mid_x + max_range)
        ax.set_ylim(mid_y - max_range, mid_y + max_range)
        ax.set_zlim(mid_z - max_range, mid_z + max_range)

        plt.show()

    def animate_step(self, title="Hexapod Leg Step Animation", z_height=-6.0, step_height=3.0, total_frames=60, trace=False, elev=30, azim=-60):
        """Generates an HTML animation of the leg taking a full step."""
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')

        # Set the camera angle
        ax.view_init(elev=elev, azim=azim)

        ax.set_xlim(-2, 10)
        ax.set_ylim(-6, 6)
        ax.set_zlim(-10, 2)
        ax.set_xlabel('X (cm)')
        ax.set_ylabel('Y (cm)')
        ax.set_zlabel('Z (cm)')
        ax.set_title(title)

        # The main leg line
        line, = ax.plot([], [], [], '-o', linewidth=3, markersize=8)

        # The coordinate text
        coord_text = ax.text2D(0.05, 0.95, "", transform=ax.transAxes, color='red', fontsize=12)

        # The trace line and history arrays
        trace_line, = ax.plot([], [], [], 'r--', linewidth=1.5, alpha=0.6)
        trace_x, trace_y, trace_z = [], [], []

        swing_angles = np.linspace(-45, 45, total_frames // 2)
        stance_angles = np.linspace(45, -45, total_frames // 2)

        def update(frame_idx):
            if frame_idx < total_frames // 2:
                frame_angle = swing_angles[frame_idx]
                progress = (frame_angle - (-45)) / 90.0
                target_z = z_height + (step_height * np.sin(progress * np.pi))
            else:
                frame_angle = stance_angles[frame_idx - (total_frames // 2)]
                target_z = z_height

            angle_rad = np.radians(frame_angle)

            # Dynamically calculate the required radius to keep the tibia exactly 6cm
            dynamic_radius = self.leg.l_femur + np.sqrt(self.leg.l_tibia ** 2 - target_z ** 2)

            # Apply the dynamic radius to the XY plane coordinates
            target_x = dynamic_radius * np.cos(angle_rad)
            target_y = dynamic_radius * np.sin(angle_rad)

            try:
                angles = self.leg.calculate_ik(target_x, target_y, target_z)
                points = self.leg.get_joint_positions(angles)
                line.set_data_3d(points[:, 0], points[:, 1], points[:, 2])

                coord_text.set_text(f"Toe: ({target_x:.2f}, {target_y:.2f}, {target_z:.2f})")

                if trace:
                    trace_x.append(target_x)
                    trace_y.append(target_y)
                    trace_z.append(target_z)
                    trace_line.set_data_3d(trace_x, trace_y, trace_z)

            except ValueError as e:
                print(f"Skipped frame {frame_idx}: {e}")

            return line, coord_text, trace_line

        anim = FuncAnimation(fig, update, frames=total_frames, interval=100, blit=False)
        plt.close()
        return HTML(anim.to_jshtml())