#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
// 创建一个订阅者，订阅名为"topic_name"的topic，并打印接收到的消息内容。
using std::placeholders::_1;
using std_msgs::msg::String;
class Listener: public rclcpp::Node
{
    public:
    // 构造函数
    Listener():Node("Listener_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"Listener created!");
        sub_=this->create_subscription<std_msgs::msg::String>("chatter",10,std::bind(&Listener::do_cd,this,std::placeholders::_1));// 1. topic name 2. queue size 3. callback function
    }
    private:
    // 回调函数
    void do_cd(const std_msgs::msg::String & msg)
    {
        RCLCPP_INFO(this->get_logger(),"I heard: %s",msg.data.c_str());
    }
    // 订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;

};
int main(int argc, char const *argv[])
{
    // 初始化ROS2
    rclcpp::init(argc, argv);

    // 创建并运行Listener节点
    rclcpp::spin(std::make_shared<Listener>());

    // 关闭ROS2
    rclcpp::shutdown();
    
    return 0;
   
}
//     // 关闭ROS2
//     rclcpp::shutdown();
    
//     return 0;
   
// }