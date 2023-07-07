#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>

int main(int argc, char  *argv[])
{
    //初始化ros节点，订阅名为“input_topic”
    ros::init(argc,argv,"pub");
    //创建ros句柄
    ros::NodeHandle nh;
    //缓存不超过10条
    ros::Publisher pub=nh.advertise<std_msgs::String>("input_topic",10);
    //创建被发布的消息
    std_msgs::String msg;
    //设置发布频率
    ros::Rate rate(10);
   

    //编写循环，循环中发布消息
    while(ros::ok())
    {
        setlocale(LC_ALL,"");

        msg.data = "hello world";
        pub.publish(msg); 
        //转换成c风格的字符窜类型
        ROS_INFO("发布字母：%s",msg.data.c_str());
       
        rate.sleep();
        ros::spinOnce();
    }

    return 0;
}
