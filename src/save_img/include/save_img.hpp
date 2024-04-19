#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point_stamped.hpp"
#include <tf2_ros/transform_broadcaster.h>
#include <sensor_msgs/msg/image.hpp>

#include <cv_bridge/cv_bridge.h>

#include "opencv2/opencv.hpp"

using namespace std;

class SaveImg : public rclcpp::Node
{
public:
  SaveImg();

  void imgCallBack(const sensor_msgs::msg::Image::SharedPtr msg);

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub;
};
