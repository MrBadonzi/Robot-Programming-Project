# Robot-Programming-Project
The project uses the ICP algorithm to localize the position of the robot inside a map.
# Requirements 
This project requires ROS *Noetic* istalled in your machine. If you havent't istalled yet, you can check the Ros installation documentation (http://wiki.ros.org/ROS/Installation).
### Map Server
- Install the `ros-${DISTRO}-map-server` package.
   ```sh
    sudo apt install ros-noetic-map-server
   ```
- To launch the node, go to the project directory, source ros and launch the `map_server` node
  - ```sh
    source /opt/ros/noetic/setup.bash
    rosrun map_server map_server test_data/cappero_map.yaml    
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
git clone https://github.com/MrBadonzi/Robot-Programming-Project.git
```
# How to Run

