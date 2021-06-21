#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

class MinimalClient : public rclcpp::Node
{
  protected: 
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
    //example_interfaces::srv::AddTwoInts::Request req_ = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();

    void call_service(auto req)
    {
      
      while (!client_->wait_for_service())
      {
        if (!rclcpp::ok())
        {
          RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting...");
          //return 0;
        }

        RCLCPP_INFO(rclcpp::get_logger("rclcppA"), "service not avaliable, waiting again.");
      }
      
      auto res = client_->async_send_request(req);
      /*
      if (rclcpp::spin_until_future_complete(&MinimalClient, res) == rclcpp::FutureReturnCode::SUCCESS)
      {
        RCLCPP_INFO(rclcpp::get_logger("rclcppB"), "Sum: %1d", res.get()->sum);
      }
      else
      {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
      }
      */
      RCLCPP_INFO(rclcpp::get_logger("rclcppB"), "Sum: %1d", res.get()->sum);
    }

  public: 
    MinimalClient(int a, int b) : Node("minimal_client")
    {
      client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_intss");
      //req_->a = a;
      //req_->b = b;
      auto req_ = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
      req_->a = a;
      req_->b = b;

      call_service(req_);
    }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 3)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client X Y");
    return 1;
  }

  auto client = std::make_shared<MinimalClient>(atoll(argv[1]), atoll(argv[2]));
  
  rclcpp::shutdown();
  return 0;
}