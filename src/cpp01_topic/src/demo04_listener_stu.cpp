#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"

using base_interfaces_demo::msg::Student;
class ListenerStu: public rclcpp::Node
{
    public:
        ListenerStu():Node("ListenerStu_node_cpp")
        {
            sub_= this->create_subscription<Student>("chatter_stu",10,std::bind(&ListenerStu::do_cb,this,std::placeholders::_1));
        }

    private:
        void do_cb(const Student &stu)
        {
            RCLCPP_INFO(this->get_logger(),"subscripted student's info: name=%s,age=%d,height=%.2f",stu.name.c_str(),stu.age,stu.height);
        }
        rclcpp::Subscription<Student>::SharedPtr sub_;
};

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<ListenerStu>());
    rclcpp::shutdown();
    return 0;
}