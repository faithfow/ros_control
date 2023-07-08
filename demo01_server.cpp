#include"ros/ros.h"
#include"add_two_ints/Addints.h"


bool doNums(add_two_ints::Addints::Request &request,
            add_two_ints::Addints::Response &response){
    //  1.处理请求
    int num1 = request.num1;
    int num2 = request.num2;
    ROS_INFO("收到请求数字: num1 = %d,num2 = %d",num1,num2);
    //  2.组织响应
    int sum = num1 + num2;
    response.sum = sum;
    ROS_INFO("求和结果: sum = %d ",sum);
 
    return true ;
}

int main(int argc, char  *argv[])
{ 
    setlocale(LC_ALL,"");
  
    //    2.初始化ros节点
    ros::init(argc,argv,"add_two_ints_server");//节点名称需要保证唯一
    //    3.创建节点句柄
    ros::NodeHandle nh;
    //    4.创建一个服务对象
    ros::ServiceServer server = nh.advertiseService("AddTwoInts",doNums);    //    5.处理请求并产生响应
   ROS_INFO("服务器端启动");
    //    5.处理请求并响应
    //    6.spin（ ）
    ros::spin();
    return 0;
}
