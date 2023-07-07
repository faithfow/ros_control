#include "ros/ros.h"
#include  "std_msgs/String.h"

void doSUB(const std_msgs::String::ConstPtr& Msg){
    ROS_INFO("发布：%s",Msg->data.c_str());
    
}

int main(int argc, char  *argv[])
{
   setlocale(LC_ALL,"");

    //初始化ros节点
    ros::init(argc,argv,"sub");
    //创建节点句柄
    ros::NodeHandle nh;
    //创建订阅对象
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("output_topic",10,doSUB);
    //循环调用回调函数
    ros::spin();
 
    
    return 0;
}
