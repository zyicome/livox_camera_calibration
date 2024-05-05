#include "save_pcd.hpp"
#include <exception>

#include "pcl/filters/passthrough.h"

RadarDeal::RadarDeal() : Node("radar_deal")
{
    cloud_pub = this->create_publisher<sensor_msgs::msg::PointCloud2>("/livox/deal", 10);

    begin_calibration_pub = this->create_publisher<std_msgs::msg::Int8>("/begin_calibration", 10);

    cloud_sub = this->create_subscription<sensor_msgs::msg::PointCloud2>("/livox/lidar", 10, std::bind(&RadarDeal::pointCloudCallback, this, std::placeholders::_1));

    i = 0;

    all_cloud.reset(new pcl::PointCloud<pcl::PointXYZI>);
}

void RadarDeal::pointCloudCallback(const sensor_msgs::msg::PointCloud2 &input)
{
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>);
    pcl::PCLPointCloud2 pcl_pc2;
    pcl_conversions::toPCL(input, pcl_pc2);
    pcl::fromPCLPointCloud2(pcl_pc2, *cloud);   
    
    /*pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0, -250);
    pass.setFilterLimitsNegative(true);
    pass.filter(*cloud);*/

    /*pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud(cloud);
    std::vector<pcl::PointIndices> cluster_indices;
    pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
    ec.setClusterTolerance(0.5);
    ec.setMinClusterSize(100);
    ec.setMaxClusterSize(25000);
    ec.setSearchMethod(tree);
    ec.setInputCloud(cloud);
    ec.extract(cluster_indices);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster_all(new pcl::PointCloud<pcl::PointXYZ>);
    for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it)
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZ>);
        for (std::vector<int>::const_iterator pit = it->indices.begin(); pit != it->indices.end(); ++pit)
        {
            cloud_cluster->points.push_back(cloud->points[*pit]);
        }
        cloud_cluster->width = cloud_cluster->points.size();
        cloud_cluster->height = 1;
        cloud_cluster->is_dense = true;

        *cloud_cluster_all += *cloud_cluster;
    }*/

    if(i % 10 == 0)
    {
        std::cout << "save" << std::endl;
        *all_cloud += *cloud;
    }
    if(i == 150)
    {
        pcl::io::savePCDFileASCII("/home/mechax/zyb/lidar_camera_calibration_data/calibration_pcd.pcd", *all_cloud);
        std::cout << "success to save pcd!" << std::endl;
        for(int j = 0;j<20;j++)
        {
            std_msgs::msg::Int8 msg;
            msg.data = 1;
            begin_calibration_pub->publish(msg);
            std::cout << "success to pub!" << std::endl;
        }
        throw std::runtime_error("Terminating at i == 150");
    }

    i++;

    /*sensor_msgs::msg::PointCloud2 output;
    pcl::toROSMsg(*cloud_cluster_all, output);
    output.header.frame_id = "livox_frame";
    cloud_pub->publish(output);*/
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RadarDeal>();
    try
    {
        rclcpp::spin(node);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        node.reset();
    }
    return 0;
}