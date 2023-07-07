#include"ros/ros.h"
#include"add_two_ints/Addints.h"


int main(int argc, char  *argv[])
{
    //优化实现，获取命令中参数
    if(argc != 3){

        ROS_INFO("提交的参数个数不对。");
        return 1;
    }

    setlocale(LC_ALL,"");

    //    2.初始化ros节点
    ros::init(argc,argv,"add_two_ints_client");
    //    3.创建节点句柄
    ros::NodeHandle nh;
    //    4.创建一个客户端对象
    ros::ServiceClient client = nh.serviceClient<plumbing_server_client::Addints>("AddTwoInts");
    //    5.提交请求并处理响应
    add_two_ints::Addints ai;
    //  5-1.组织请求
    ai.request.num1 = atoi(argv[1]);
    ai.request.num2 = atoi(argv[2]);
    //  5-2.处理响应
    //调用判断服务器状态的函数
    //函数1
    //client.waitForExistence();
    ros::service::waitForService("addInts");
    bool flag = client.call(ai);
    if (flag)
    {
        ROS_INFO("响应成功");
        //获取结果
        ROS_INFO("响应结果 = %d",ai.response.sum);
    }
    else{
        ROS_INFO("处理失败...");
    }

    return 0;
}
