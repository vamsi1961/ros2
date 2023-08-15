#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
using std::placeholders::_1;
using std::placeholders::_2;


class AddTwoIntsServerNode : public rclcpp::Node // Modify Name
{


public:
    AddTwoIntsServerNode(): Node("add_two_ints_server") // Modify Name
    {
        server_ = this->create_service<example_interfaces::srv::AddTwoInts>(
            "add_two_ints",
            // create a call back function
            std::bind(&AddTwoIntsServerNode::callbackAddTwoInts,this, std::placeholders::_1,_2));

        RCLCPP_INFO(this->get_logger(), "Service server has been started.");

    }

private:

    void callbackAddTwoInts(const example_interfaces::srv::AddTwoInts::Request::SharedPtr request,
                            const example_interfaces::srv::AddTwoInts::Response::SharedPtr response
                                )
    {
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger() , "%d + %d = %d" , request->a , request->b , response->sum);
    }

    // declare
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;
    


};

int main(int argc , char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsServerNode>();  // Modify Name
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}