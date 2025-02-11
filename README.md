# IRR Lab 3
This ROS2 package is an orange-ball following program. Run
1. `ros2 launch turtlebot3_bringup camera_robot.launch.py` Launch turtlebot stack (includes camera)
2. `ros2 run find_object_py find_object_py_pubsub` Run CV node which subscribes to the /image_raw/compressed and publishes the object's normed location relative to center of the image to /obj_coords
4. `ros2 run get_object_range get_object_range_pubsub` Run node which subscribes to /scan and /obj_coords and publishes object location to /obj_location
5. `ros2 run chase_object chase_object_pubsub` Run control node which subscribes to the /obj_location and publishes velocity command to /cmd_vel

Ideally, we can run these all with the launch file:
`ros2 launch find_object_py follow_object.py`

## ROS Diagram
![rosdiagram](rqt_graph.png)
