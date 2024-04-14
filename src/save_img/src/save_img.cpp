#include "save_img.hpp"

SaveImg::SaveImg()
: Node("save_img")
{
      img_sub = this->create_subscription<sensor_msgs::msg::Image>("/image_raw", rclcpp::SensorDataQoS(), std::bind(&SaveImg::imgCallBack, this, std::placeholders::_1));
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
    RCLCPP_INFO(this->get_logger(), "success to save img!");
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<SaveImg>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}