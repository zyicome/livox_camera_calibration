#include "save_img.hpp"
#include <exception>

SaveImg::SaveImg()
: Node("save_rightimg")
{
    i =0;

      img_sub = this->create_subscription<sensor_msgs::msg::Image>("/image_far", rclcpp::SensorDataQoS(), std::bind(&SaveImg::imgCallBack, this, std::placeholders::_1));

      label_pub = this->create_publisher<std_msgs::msg::Int8>("/camera_label", 10);
}

void SaveImg::imgCallBack(const sensor_msgs::msg::Image::SharedPtr msg)
{
    

    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception &e)
    {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }

    cv::imwrite("/home/mechax/zyb/lidar_camera_calibration_data/calibration_img.jpg", cv_ptr->image);
    RCLCPP_INFO(this->get_logger(), "success to save rightimg!");

    if(i == 20)
    {
      std_msgs::msg::Int8 label;
      label.data = 2;
      label_pub->publish(label);
        throw std::runtime_error("Terminating at i == 20");
    }

    i++;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<SaveImg>();
  try
  {
    rclcpp::spin(node);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    node.reset();
  }
  return 0;
}