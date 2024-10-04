#include "localizer2d.h"

#include "icp/eigen_icp_2d.h"


Localizer2D::Localizer2D()
    : _map(nullptr),
      _laser_in_world(Eigen::Isometry2f::Identity()),
      _obst_tree_ptr(nullptr) {}

/**
 * @brief Set the internal map reference and constructs the KD-Tree containing
 * obstacles coordinates for fast access.
 *
 * @param map_
 */
void Localizer2D::setMap(std::shared_ptr<Map> map_) {
  // Set the internal map pointer
  _map = map_;
  /**
   * If the map is initialized, fill the _obst_vect vector with world
   * coordinates of all cells representing obstacles.
   * Finally instantiate the KD-Tree (obst_tree_ptr) on the vector.
   */
  // TODO
  if (_map->initialized()) { 

    size_t Maprows = _map->rows();
    size_t Mapcols = _map->cols();
   
   // get the grid data
    const std::vector<int8_t>& mapGrid = _map->grid();

    for (auto row=1; row <= Maprows; ++row){
      for(auto col=1; col <= Mapcols; ++col){
        
        //take the corresponding cell status in the vector 
        int grid_element = _map->operator()(row,col);

        if (grid_element == CellType::Occupied){

          //convert the grid coordinate into the world coordinate
          cv::Point2i Gridcoord(row, col);
          Eigen::Vector2f worldCoords = _map->grid2world(Gridcoord);
          //add into the obstacle vector
          _obst_vect.push_back(worldCoords);

        }

      }
    }
  }

  // Create KD-Tree
  // TODO
  
  _obst_tree_ptr = std::make_shared<TreeType>(_obst_vect.begin(), _obst_vect.end());
  
  
}

/**
 * @brief Set the current estimate for laser_in_world
 *
 * @param initial_pose_
 */
void Localizer2D::setInitialPose(const Eigen::Isometry2f& initial_pose_) {
  // TODO
  _laser_in_world = initial_pose_;
}

/**
 * @brief Process the input scan.
 * First creates a prediction using the current laser_in_world estimate
 *
 * @param scan_
 */
void Localizer2D::process(const ContainerType& scan_) {
  // Use initial pose to get a synthetic scan to compare with scan_
  // TODO
  ContainerType prediction;
  getPrediction(prediction);


  /**
   * Align prediction and scan_ using ICP.
   * Set the current estimate of laser in world as initial guess (replace the
   * solver X before running ICP)
   */
  // TODO
  static const int min_points_leaf = 5;
  //create ICP object 
  ICP icp(prediction, scan_, min_points_leaf);
  //Set the current estimate of laser in world as initial guess 
  icp.X() = _laser_in_world;

  static const int Max_iter = 64;
  icp.run(Max_iter);

  /**
   * Store the solver result (X) as the new laser_in_world estimate
   *
   */
  // TODO
  _laser_in_world =  icp.X();
}

/**
 * @brief Set the parameters of the laser scanner. Used to predict
 * measurements.
 * These parameters should be taken from the incoming sensor_msgs::LaserScan
 * message
 *
 * For further documentation, refer to:
 * http://docs.ros.org/en/noetic/api/sensor_msgs/html/msg/LaserScan.html
 *
 *
 * @param range_min_
 * @param range_max_
 * @param angle_min_
 * @param angle_max_
 * @param angle_increment_
 */
void Localizer2D::setLaserParams(float range_min_, float range_max_,
                                 float angle_min_, float angle_max_,
                                 float angle_increment_) {
  _range_min = range_min_;
  _range_max = range_max_;
  _angle_min = angle_min_;
  _angle_max = angle_max_;
  _angle_increment = angle_increment_;
}

/**
 * @brief Computes the predicted scan at the current laser_in_world pose
 * estimate.
 *
 * @param dest_ Output predicted scan
 */
void Localizer2D::getPrediction(ContainerType& prediction_) {
  prediction_.clear();
  /**
   * To compute the prediction, query the KD-Tree and search for all points
   * around the current laser_in_world estimate.
   * You may use additional sensor's informations to refine the prediction.
   */
  // TODO
  static const int ball_radius = 10;

  std::vector<PointType*> neighbors;

  _obst_tree_ptr->fullSearch(neighbors, _laser_in_world.translation(), ball_radius);
  
  for (auto& point : neighbors) {
    
    PointType diference = _laser_in_world.translation() - *point;

    float distance = diference.norm();
    float angle = atan2(diference.y(), diference.x());

    if(distance <= _range_max && angle >= _angle_min && angle <= _angle_max){     
      prediction_.push_back(*point);
    }
  }



}