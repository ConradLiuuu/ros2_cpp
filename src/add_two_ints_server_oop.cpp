#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <memory>

class MinimalServer : public rclcpp::Node
{
  protected: 
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;
  
    
    void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request, std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
    {
      response->sum = request->a + request->b;
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming requests\na: %1d" " b: %1d", request->a, request->b);
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%1d]", (long int)response->sum);
      //return 0;
    }
    
    /*
    auto add = [this] (const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request, std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
    {
      response->sum = request->a + request->b;
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming requests\na: %1d" " b: %1d", request->a, request->b);
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%1d]", (long int)response->sum);
    };
    */
    
  public: 
    MinimalServer() : Node("minimal_server")
    {
      server_ = this->create_service<example_interfaces::srv::AddTwoInts>("add_two_intss", std::bind(&MinimalServer::add, this, std::placeholders::_1, std::placeholders::_2));
    }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalServer>());
  rclcpp::shutdown();
  
  return 0;
}
