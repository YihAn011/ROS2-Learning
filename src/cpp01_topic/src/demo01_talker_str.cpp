#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using namespace std::chrono_literals;



class Talker:public rclcpp::Node
{
  public:
  Talker():Node("talker_node_cpp")
  {
    RCLCPP_INFO(this->get_logger(),"talker_node_cpp is created");
    publisher_=this->create_publisher<std_msgs::msg::String>("chatter", 10);
    timer_=this->create_wall_timer(1s,std::bind(&Talker::on_timer,this));
  }
  private:
  
  void on_timer()
  {
    auto message = std_msgs::msg::String();
    message.data="hello world"+std::to_string(count++);
    // RCLCPP_INFO(this->get_logger(),"Published INFO:%s", message.data.c_str());
    RCLCPP_INFO(this->get_logger(),"Published INFO:%s", message.data.c_str());
    
  
    publisher_->publish(message);

    if(count >=200)
    {
      RCLCPP_INFO(this->get_logger(),"shutting down node...");
      
      rclcpp::shutdown();
    }
  }

  
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  size_t count;

};




int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Talker>());
  rclcpp::shutdown();
  
  return 0;
}
