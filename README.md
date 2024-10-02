# Robot-Programming-Project
The project uses the ICP algorithm to localize the position of the robot inside a map.
# Requirements 
This project requires ROS *Noetic* istalled in your machine. If you havent't istalled yet, you can check the Ros installation documentation()
### Map Server
- Install the `ros-${DISTRO}-map-server` package. In our case (valid for Lattinone VM) we are using _ROS Noetic_
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
