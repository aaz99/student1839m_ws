#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <turtlesim/Pose.h>

static double path_1 = 0,
path_2 = 0,
x_last = 0,
y_last = 0,
x2_last = 0,
y2_last = 0;

static bool flag_1 = true, flag_2 = true;


int main(int argc, char **argv)
{
    ros::init(argc, argv, "lab3_bagfile_node");
    ros::NodeHandle nh;

    //Открываем файл с данными для чтения
    rosbag::Bag bag;
    bag.open("/home/pinton/Documents/ros_labs/student1839m_ws/src/lab3_bagfile/src/first_turtle.bag", rosbag::bagmode::Read);

    //Определяем топики, которые будем считывать
    std::vector<std::string> topics;
    topics.push_back(std::string("/lemmi/pose"));

    //Определяем конфигурацию для считывания нескольких топиков
    rosbag::View view(bag, rosbag::TopicQuery(topics));

    //считываем все имеющиеся данные и выводим в консоль
    for(rosbag::MessageInstance const m: rosbag::View(bag))
    {
        turtlesim::Pose::ConstPtr first_turtle = m.instantiate<turtlesim::Pose>();
        if (first_turtle != NULL){
            if(flag_1){
                x_last = first_turtle ->x;
                y_last = first_turtle ->y;
                flag_1 = false;
            }
            std::cout <<"X: "<< first_turtle -> x<<std::endl;
            std::cout <<"Y: "<< first_turtle -> y<<std::endl;
            path_1 += sqrt((first_turtle->x - x_last)*(first_turtle->x - x_last)+(first_turtle->y - y_last)*(first_turtle->y - y_last));



            x_last = first_turtle ->x;
            y_last = first_turtle ->y;
        }

    }
    bag.close();

    rosbag::Bag bag2;
    bag2.open("/home/pinton/Documents/ros_labs/student1839m_ws/src/lab3_bagfile/src/second_turtle.bag", rosbag::bagmode::Read);

    //Определяем топики, которые будем считывать
    std::vector<std::string> topics2;
    topics2.push_back(std::string("/memmi/pose"));

    //Определяем конфигурацию для считывания нескольких топиков
    rosbag::View view2(bag2, rosbag::TopicQuery(topics2));

    //считываем все имеющиеся данные и выводим в консоль
    for(rosbag::MessageInstance const m: rosbag::View(bag2))
    {

        turtlesim::Pose::ConstPtr second_turtle = m.instantiate<turtlesim::Pose>();
        if (second_turtle != NULL){
            if (flag_2){
                x2_last = second_turtle ->x;
                y2_last = second_turtle ->y;
                flag_2 = false;
            }
            std::cout <<"X: "<< second_turtle -> x<<std::endl;
            std::cout <<"Y: "<< second_turtle -> y<<std::endl;
            path_2 += sqrt((second_turtle->x - x2_last)*(second_turtle->x - x2_last)+(second_turtle->y - y2_last)*(second_turtle->y - y2_last));

            //            path_1 = sqrt ((poseStamped.pose.position.x - x_last)*(poseStamped.pose.position.x - x_last)+ (poseStamped.pose.position.y-y_last)*(poseStamped.pose.position.y-y_last));
            x2_last = second_turtle ->x;
            y2_last = second_turtle ->y;
        }
    }
    std::cout<<"Total path first turtle is: "<< path_1<<std::endl;
    std::cout<<"Total path second turtle is: "<< path_2<<std::endl;
    bag2.close();
}







//#include <ros/ros.h>
//#include <rosbag/bag.h>
//#include <rosbag/view.h>
//#include <std_msgs/Int32.h>
//#include <std_msgs/String.h>
//#include <turtlesim/Pose.h>

//bool flag = 1;
//void callback_pose(const turtlesim::Pose &msg){
//    if(msg.angular_velocity == 0){
//        flag = 0;
//        ROS_WARN("FLAG IS ZERO");    }

//}


//int main(int argc, char **argv)
//{
//    ros::init(argc, argv, "lab3_bagfile_node");
//    ros::NodeHandle nh;
// ros::Subscriber turtleVel_sub = nh.subscribe ("/lemmi/pose", 1000, callback_pose);
//    //Открываем файл с данными для чтения
//    rosbag::Bag bag_first;
//    bag_first.open("/home/pinton/Documents/ros_labs/student1839m_ws/src/lab3_bagfile/first_turtle.bag", rosbag::bagmode::Write);

////    rosbag::Bag bag_second;
////    bag_second.open("/home/pinton/Documents/ros_labs/student1839m_ws/src/lab3_bagfile/second_turtle.bag", rosbag::bagmode::Write);

//    turtlesim::Pose first_turtle_pose;
//    turtlesim::Pose second_turtle_pose;
//    ros::Rate r(10);
//    //В цикле формируем содержимое и отправляем в файл
//    while (flag && ros::ok()) {
//        bag_first.write("/lemmi/pose", ros::Time::now(), first_turtle_pose);
////        bag_second.write("/memmi/pose", ros::Time::now(), second_turtle_pose);

//        ros::spinOnce();
//        r.sleep();
//    }

//    ROS_WARN("PROGRAM IS NO END!!!!!!!!!!");
//    bag_first.close();
////    bag_second.close();
//    ROS_WARN("PROGRAM IS END!!!!!!!!!!");

//    return 0;
//}
