#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

/*
    订阅方：订阅发布的坐标系的相对关系，传入一个坐标点，使用tf 实现转换
    

    流程：
       1.包含头文件
       2.初始化ros节点
       3.创建节点句柄（必须）
       4.创建订阅对象------> 订阅坐标相对关系
       5.组织一个坐标点数据
       6.转换算法，需要TF内置实现
       6.最后输出

    


*/

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");

    //2.初始化ros节点
    ros::init(argc,argv,"static_sub"); 
    //   3.创建节点句柄（必须）
    ros::NodeHandle nh;
    //   4.创建订阅对象------> 订阅坐标相对关系
    //  4-1.创建一个buffer缓存
    tf2_ros::Buffer buffer;
    //  4-2.再创建一个监听对象（监听对象可以将订阅的数据存入buffer)
    tf2_ros::TransformListener listener(buffer);
    //   5.组织一个坐标点数据
    geometry_msgs::PointStamped ps;
    ps.header.frame_id = "laser";
    ps.header.stamp = ros::Time::now();
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;
    //添加休眠
    ros::Duration(2).sleep();
    //   6.转换算法，需要TF内置实现
    ros::Rate rate(10);
    while (ros::ok())
    {
      //核心代码------ 将 ps 转换成相对于 base_link 的坐标点
      geometry_msgs::PointStamped ps_out;
      ps_out = buffer.transform(ps,"base_link");
      //6.输出
      ROS_INFO("转换后的坐标：(%.2f,%.2f,%.2f),参考坐标系：%s",
                  ps.point.x,
                  ps.point.y ,
                  ps.point.z , 
                  ps_out.header.frame_id.c_str());
      rate.sleep();
      ros::spinOnce();
    }
    

    //   6.最后输出

    return 0;
}
