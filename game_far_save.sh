cd "/home/mechax/zyb/livox_camera_calibration"

echo "Starting colcon build"
colcon build
echo "Colcon build finished"

cmds=(  #"ros2 launch mindvision_camera mv_launch.py"
	#"ros2 launch hik_camera hik_camera.launch.py"
	#"ros2 launch livox_ros2_driver livox_lidar_launch.py"
  	 #"ros2 launch foxglove_bridge foxglove_bridge_launch.xml port:=8765"
  	 "ros2 run lidar_camera_calib lidar_camera_calib;exec bash"
  	 "ros2 run save_pcd save_pcd_node"
  	 "ros2 run save_img save_far_img"
        )
        
for cmd in "${cmds[@]}"; 
do
    echo Current CMD : "$cmd"
  	gnome-terminal -- bash -c "cd $(pwd);source install/setup.bash;$cmd;"
    sleep 1.5
done

echo "Script finished"
