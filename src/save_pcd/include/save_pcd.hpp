#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "cv_bridge/cv_bridge.h"
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <pcl/point_cloud.h>
#include <sensor_msgs/msg/detail/image__struct.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>
#include <pcl/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl_conversions/pcl_conversions.h>
#include <vector>

#include <pcl/visualization/pcl_visualizer.h>

#include <fstream>

#include <boost/thread/thread.hpp>

class RadarDeal : public rclcpp::Node
{
public:
    RadarDeal();

    void pointCloudCallback(const sensor_msgs::msg::PointCloud2 &input);

    int i;

    pcl::PointCloud<pcl::PointXYZI>::Ptr all_cloud;

    // publisher
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_pub;
    // subscriber
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_sub;
};