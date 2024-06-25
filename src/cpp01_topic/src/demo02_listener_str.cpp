#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;
using std_msgs::msg::String;
class Listener: public rclcpp::Node
{
    public:
    
    Listener():Node("Listener_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"Listener created!");
        sub_=this->create_subscription<std_msgs::msg::String>("chatter",10,std::bind(&Listener::do_cd,this,std::placeholders::_1));// 1. topic name 2. queue size 3. callback function
    }
    private:
    
    void do_cd(const std_msgs::msg::String & msg)
    {
        RCLCPP_INFO(this->get_logger(),"I heard: %s",msg.data.c_str());
    }
    
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;

};
int main(int argc, char const *argv[])
{
    
    rclcpp::init(argc, argv);

   
    rclcpp::spin(std::make_shared<Listener>());


    rclcpp::shutdown();
    
    return 0;
   
}
