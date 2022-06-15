#include "ros/ros.h"
#include "turtlesim/Kill.h"
#include "turtlesim/Color.h"
#include "std_srvs/Empty.h"
#include "turtlesim/Spawn.h"
#include "turtlesim/SetPen.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "iostream"


turtlesim::Pose turtlesim_pose;


void callback_leni(const turtlesim::Pose &msg){
    turtlesim_pose = msg;

    ROS_INFO("Leni pose received");
}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "lab1_turtlesim_node");


    ros::NodeHandle nh;
    int background;
    nh.getParam("/turtlesim/background_b", background);

//    while ((background != 255)){
//        ROS_INFO("Waiting launch turtlesim_node");
//    }

    nh.setParam("/turtlesim/background_b", 0);
    nh.setParam("/turtlesim/background_g", 0);
    nh.setParam("/turtlesim/background_r", 255);
    ros::ServiceClient clear_srv = nh.serviceClient<std_srvs::Empty>("/clear");
    std_srvs::Empty srv;
    clear_srv.call(srv);


    ros::ServiceClient kill_srv = nh.serviceClient<turtlesim::Kill>("/kill");
    turtlesim::Kill kill_obj;
    kill_obj.request.name = "turtle1";

    while(!kill_srv.call(kill_obj)) {}





    ros::ServiceClient spawn_srv = nh.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn spawn_obj;



    spawn_obj.request.x = 2.0;
    spawn_obj.request.y = 2.0;
    spawn_obj.request.theta = 0.0;
    spawn_obj.request.name = "leni";
    spawn_srv.call(spawn_obj);


    spawn_obj.request.x = 6.0;
    spawn_obj.request.y = 6.0;
    spawn_obj.request.theta = 0.0;
    spawn_obj.request.name = "steven";
    spawn_srv.call(spawn_obj);

    ros::ServiceClient setpen_leni_srv = nh.serviceClient<turtlesim::SetPen>("/leni/set_pen");
    turtlesim::SetPen setpen_obj;
    setpen_obj.request.b = 0;
    setpen_obj.request.g = 255;
    setpen_obj.request.r = 255;
    setpen_obj.request.width = 10;
    setpen_leni_srv.call(setpen_obj);

    ros::ServiceClient setpen_steven_srv = nh.serviceClient<turtlesim::SetPen>("/steven/set_pen");
    setpen_obj.request.b = 0;
    setpen_obj.request.g = 255;
    setpen_obj.request.r = 0;
    setpen_obj.request.width = 10;
    setpen_steven_srv.call(setpen_obj);



    ros::Publisher pose_leni = nh.advertise<geometry_msgs::Twist>("/leni/cmd_vel", 1000);
    geometry_msgs::Twist moveCircle_leni;
    moveCircle_leni.linear.x = 1.0;
    moveCircle_leni.angular.z = 1.0;

    ros::Publisher pose_steven = nh.advertise<geometry_msgs::Twist>("/steven/cmd_vel", 1000);
    geometry_msgs::Twist moveCircle_steven;
    moveCircle_steven.linear.x = 2.0;
    moveCircle_steven.angular.z = 1.0;

    ros::Time current_time, last_time;
    last_time = ros::Time::now();

    ros::Subscriber leniPose_sub = nh.subscribe ("/leni/pose", 1000, callback_leni);

    ros::Rate r(2000);

    while (ros::ok()) {


        std::cout<<turtlesim_pose.theta<<std::endl;


        if ((turtlesim_pose.theta < 0) && (turtlesim_pose.theta > -0.05)){

            moveCircle_leni.linear.x = 0.0;
            moveCircle_leni.angular.z = 0.0;

            moveCircle_steven.linear.x = 0.0;
            moveCircle_steven.angular.z = 0.0;

            pose_leni.publish(moveCircle_leni);
            pose_steven.publish(moveCircle_steven);

            break;
        }

        pose_leni.publish(moveCircle_leni);
        pose_steven.publish(moveCircle_steven);
        ros::spinOnce();
        r.sleep();
    }


    return 0;
}
