#include "ros/ros.h"
#include  "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <algorithm>

//设置全局变量 实例化发布
static ros::Publisher pub;


//回调函数
void ChangeB(const std_msgs::String::ConstPtr& msg){
    std::string Msg = msg->data;//定义字符串变量来接收
    std_msgs::String respond;//消息类型
    std::transform(Msg.begin(),Msg.end(),Msg.begin(),::toupper);//转换字母大小写
    respond.data = Msg;//将Msg中的值递给data
    pub.publish(respond);
    ROS_INFO("大写字母为：%s",Msg.c_str());

}


int main(int argc, char  *argv[])
{
   setlocale(LC_ALL,"");

    //初始化ros节点
    ros::init(argc,argv,"string_converter");
    //创建节点句柄
    ros::NodeHandle fb;
    pub = fb.advertise<std_msgs::String>("output_topic",10);
    sub = fb.advertise<std_msgs::String>("input_topic",10);
   
    ros::spin();
    return 0;
}
