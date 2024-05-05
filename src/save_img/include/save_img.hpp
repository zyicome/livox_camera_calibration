#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point_stamped.hpp"
#include <tf2_ros/transform_broadcaster.h>
#include <sensor_msgs/msg/image.hpp>

#include <cv_bridge/cv_bridge.h>

#include "opencv2/opencv.hpp"

#include <std_msgs/msg/int8.hpp>

using namespace std;

class SaveImg : public rclcpp::Node
{
public:
  SaveImg();

  void imgCallBack(const sensor_msgs::msg::Image::SharedPtr msg);

  int i =0;

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub;

  rclcpp::Publisher<std_msgs::msg::Int8>::SharedPtr label_pub;
};
