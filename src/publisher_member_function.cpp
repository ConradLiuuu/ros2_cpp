#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher() : Node("minimal_publisher")
    {
      publisher_ = this -> create_publisher<std_msgs::msg::String>("talker", 10);
      timer_ = this -> create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
      count_ = 0;
    }
    
  protected:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_;
  
    void timer_callback()
    {
      std_msgs::msg::String msg = std_msgs::msg::String();
      msg.data = "Hello world! " + std::to_string(count_++);
      
      RCLCPP_INFO(this -> get_logger(), "Publishing: '%s'", msg.data.c_str());
      publisher_->publish(msg);
    }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  
  return 0;
}
