# Robot-Programming-Project
This project implements robot localization using the Iterative Closest Point (ICP) algorithm using ROS. The objective of the project is to enable the robot to autonomously determine its position within the environment by comparing its real-time sensor data with a known reference map.
# Requirements 
This project requires ROS *Noetic* istalled in your machine. If you haven't istalled yet, you can check the Ros installation documentation (http://wiki.ros.org/ROS/Installation).
### Map Server
Install the `ros-${DISTRO}-map-server` package.
   ```sh
    sudo apt install ros-noetic-map-server
   ```
### Stage-ROS
Install the `ros-${DISTRO}-stage-ros` and `ros-${DISTRO}-teleop-twist-keyboard` package.
```sh
  sudo apt install ros-noetic-stage-ros ros-noetic-teleop-twist-keyboard
  ```
# Create Workspace
To run the code first you must create a ROS workspace in your root folder:
```sh
cd ~
mkdir ros_workspaces
cd ros_workspaces
mkdir ICP_localization
cd ICP_localization
mkdir src
cd src
catkin_init_workspace
```
Clone the repository:
```sh
git clone https://github.com/MrBadonzi/Robot-Programming-Project.git
```
Then build your catkin workspace `(-DPYTHON_EXECUTABLE=/usr/bin/python3`  argument is needed only if it's the first time the workspace is initialized):
```sh
cd ..
catkin_make -DPYTHON_EXECUTABLE=/usr/bin/python3
source devel/setup.bash
```

# How to Run
Each of the following points must be executed in a different terminals, inside the project directory (ICP_localization folder)
### Compile and execute the main node
If you ever need to compile the code use the following command:
```sh
catkin build
```
To launch the main node use:
```sh
rosecore
```
### Map server
To launch the Map server node, still inside the project directory, run the following commands:
```sh
source /opt/ros/noetic/setup.bash
rosrun map_server map_server src/Robot-Programming-Project/02_icp_localization/test_data/cappero_map.yaml
```
### Stage-ROS
 To launch the simulator, go to the project directory, source ros, launch the roscore and launch the `stageros` node
   ```sh
    source /opt/ros/noetic/setup.bash
    rosrun stage_ros stageros src/Robot-Programming-Project/02_icp_localization/test_data/cappero.world   
```
### Localizer 
To launch the localizer node. 
```sh
source devel/setup.bash
rosrun icp_localization localizer_node
```

### Visualize Results

You can test your localizer using `RViz`. We have provided a configuration that you can directly run after your node has started.

Go to the project directory, source ros and launch rviz with our configuration
```sh
rviz -d src/Robot-Programming-Project/02_icp_localization/test_data/rviz.rviz
```


