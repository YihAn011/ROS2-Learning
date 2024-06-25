#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"

using base_interfaces_demo::msg::Student;
using namespace std::chrono_literals;

class TalkerStu: public rclcpp::Node
{
    public:
        TalkerStu():Node("Talkerstu_node_cpp"),age_(0)
        {
            publisher_ = this->create_publisher<Student>("chatter_stu",10);
            timer_ = this->create_wall_timer(500ms, std::bind(&TalkerStu::on_timer,this));
        }
    private:
        rclcpp::Publisher<Student>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        int age_;
        void on_timer()
        {
            auto stu = Student();
            stu.name = "huluwa";
            stu.age = age_;
            stu.height = 2.20;
            age_++;
            publisher_ -> publish(stu);
            RCLCPP_INFO(this->get_logger(), "published info(%s,%d,%.2f)",stu.name.c_str(),stu.age,stu.height);
        }

        

};

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<TalkerStu>());
    rclcpp::shutdown();
    return 0;
}