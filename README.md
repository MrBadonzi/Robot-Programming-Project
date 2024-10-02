# Robot-Programming-Project
The project uses the ICP algorithm to localize the position of the robot inside a map.
# Requirements 
This project requires ROS *Noetic* istalled in your machine. If you havent't istalled yet, you can check the Ros installation documentation (http://wiki.ros.org/ROS/Installation).
### Map Server
- Install the `ros-${DISTRO}-map-server` package.
   ```sh
    sudo apt install ros-noetic-map-server
   ```
### Stage-ROS
- Install the `ros-${DISTRO}-stage-ros` and `ros-${DISTRO}-teleop-twist-keyboard` package.
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
catkin_init_workspace
```
then go inside the src directory and clone the repository:
```sh
cd src
git clone https://github.com/MrBadonzi/Robot-Programming-Project.git
```
# How to Run
you need to open five different terminals insisde the ICP_localization folder. Each of the following points must be executed in a different terminal.  
### Compile and execute the main node
to compile the code use the following command:
```sh
catkin build
```
to launch the main node use:
```sh
rosecore
```
### Map server
To launch the Map server node, still inside the ICP_localization folder, run the following commands:
```sh
source /opt/ros/noetic/setup.bash
rosrun map_server map_server src/02_icp_localization/test_data/cappero_map.yaml
```
### Stage-ROS
- To launch the simulator, go to the project directory, source ros, launch the roscore and launch the `stageros` node
  - ```sh
    source /opt/ros/noetic/setup.bash
    rosrun stage_ros stageros src/02_icp_localization/test_data/cappero.world
    ```
### Visualize Results

You can test your localizer using `RViz`. We have provided a configuration that you can directly run after your node has started.

Go to the project directory, source ros and launch rviz with our configuration
```sh
rviz -d src/02_icp_localization/test_data/rviz.rviz
```
### Localizer 
To lanch the localizer node. 
```sh
source devel/setup.bash
rosrun icp_localization localizer_node
```
