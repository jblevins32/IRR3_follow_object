#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <algorithm>

// use literals instead of std:chrono every time
using std::placeholders::_1;

// This class inherits from rclcpp::Node
class RotateRobot : public rclcpp::Node
{
public:
    RotateRobot():Node("chase_object_pubsub") // This is initializing the node
    {
        RCLCPP_INFO(this->get_logger(), "Starting Rotate Robot Node");

        // Create a subscription to the topic "coordinates"
        // test publishing to obj_coords with r
        subscription_ = this->create_subscription<geometry_msgs::msg::Point>(
            "/obj_coords", rclcpp::QoS(10).reliable(), std::bind(&RotateRobot::topic_callback, this, _1)); // _1 means the function will allow one argument

        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    }

private:
    void topic_callback(const geometry_msgs::msg::Point & msg)
    {
        // Log the received message IF THIS IS NOT SHOWING, BE SURE THE TOPIC EXISTS IN THE SPECIFIC TERMINAL
        RCLCPP_INFO(this->get_logger(), "Received coordinates: x=%f, y=%f", msg.x, msg.y);
        
        // Instantiate a Twist message
        auto twist_msg = geometry_msgs::msg::Twist();
        
        // Calculate proportional control command which is a twist around the z axis
        int Kp = 2.5;
        twist_msg.angular.z = Kp*msg.x;
        RCLCPP_INFO(this->get_logger(), "Twist command: %f", twist_msg.angular.z);

        // Publish the command velocity
        publisher_->publish(twist_msg);
    }

    // memory management in cpp
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv); // Setup ros2 system
    rclcpp::spin(std::make_shared<RotateRobot>());
    rclcpp::shutdown();
    return 0;
}