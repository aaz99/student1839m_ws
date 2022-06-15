#include <ros/ros.h>
#include <nav_msgs/GridCells.h>
#include <std_msgs/Header.h>
#include <geometry_msgs/Point.h>
//#include <sensor_msgs/PointCloud2.h>
//#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/OccupancyGrid.h>
#include <cmath>


static sensor_msgs::LaserScan lidar_cloud;
static bool flag = false;


void get_laser_scan(const sensor_msgs::LaserScan &msg){
    lidar_cloud = msg;
    flag = true;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "lab5_1_gridcells_node");
    ros::NodeHandle nh;
    ros::Subscriber pc_su = nh.subscribe ("/scan", 10, get_laser_scan);
    nav_msgs::GridCells grid_cells_map;


    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();



    ros::Rate r(10);

    while (ros::ok()) {
        ros::spinOnce();
        current_time = ros::Time::now();
        grid_cells_map.header.frame_id = "cells";
        grid_cells_map.header.stamp = ros::Time::now();
        grid_cells_map.cell_width = 0.1;
        grid_cells_map.cell_height = 0.1;
        grid_cells_map.header.seq =

//        lidar_cloud.header.frame_id = ""



//        if(flag){



//            flag = false;
//        }







//        last_time = current_time;

        r.sleep();
    }

    return 0;
}
