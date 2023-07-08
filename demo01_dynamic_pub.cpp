#include"ros/ros.h"
#include"turtlesim/Pose.h"
#include"tf2_ros/transform_broadcaster.h"
#include"geometry_msgs/TransformStamped.h"
#include"tf2/LinearMath/Quaternion.h"
/*
    发布方：需要订阅乌龟的位置信息，转换成相对于窗体的坐标关系，并发布
    准  备：
        话题; /turtle1/pose

        消息：turtlesim/Pose
    流程：
        1.包含头文件
        2.设置编码，初始化，nodehandle
        3.创建订阅对象，订阅 话题
        4.回调函数处理订阅的消息: 将位置信息转换成坐标相对关系并发布
        5.spin（)


*/
void doPose(const turtlesim::Pose::ConstPtr& pose){
       //获取位置信息，转换成坐标相对关系（核心），并发布
       //a.创建发布对象
       static tf2_ros::TransformBroadcaster pub;
       //b.组织被发布的数据
       geometry_msgs::TransformStamped ts;
       ts.header.frame_id = "world";
       ts.header.stamp = ros::Time::now();
       ts.child_frame_id= "turtle1";
       //偏移量
       ts.transform.translation.x = pose->x;
       ts.transform.translation.y = pose->y;
       ts.transform.translation.z = 0;
       //坐标（四元数)
       /*
       位置信息中没有四元数，但有个偏航角，已知乌龟是2D，没有翻滚和俯仰角 ，得出乌龟的欧拉角：0 0 theta
       */
       tf2::Quaternion qtn;
       qtn.setRPY(0,0,pose->theta);
    

       ts.transform.rotation.x = qtn.getX();
       ts.transform.rotation.y = qtn.getY();
       ts.transform.rotation.z = qtn.getZ();
       ts.transform.rotation.w = qtn.getW();


       
       
       //发布
       pub.sendTransform(ts); 
}

int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");

    //2.设置编码，初始化，nodehandle
    ros::init(argc,argv,"dynamic_pub");
    ros::NodeHandle nh;
    //3.创建订阅对象，订阅 话题
    ros::Subscriber sub = nh.subscribe("/turtle1/pose",100,doPose);
    //4.回调函数处理订阅的消息 将位置信息转换成坐标相对关系并发布
    //5.spin（)
    ros::spin();
    return 0;
}
