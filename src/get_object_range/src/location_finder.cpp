#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/point.hpp"

using std::placeholders::_1;

class LocationFinder : public rclcpp::Node
{
public:
    LocationFinder() : Node("get_object_location_pubsub") // This is basically the cpp version of __init__
    {
        RCLCPP_INFO(this->get_logger(), "Starting Location Finder Node");

        subscription_1 = this->create_subscription<sensor_msgs::msg::LaserScan>
        (
         "/scan",
         rclcpp::QoS(10).reliable(),
         std::bind(&LocationFinder::location_callback,this,_1)
        );

        subscription_2 = this->create_subscription<geometry_msgs::msg::Point>
        (
         "/obj_coords",
         rclcpp::QoS(10).reliable(),
         std::bind(&LocationFinder::location_callback,this,_1)
        );

        publisher_ = this->create_publisher<geometry_msgs::msg::Point>
        ("/obj_range",
         10
        );
    }

private:
    void location_callback(const sensor_msgs::msg::LaserScan & laser_msg, const geometry_msgs::msg::Point & coords_msg) // message type & variable name
    {
        RCLCPP_INFO(this->get_logger(), "Received Laser Scan and Object Coordinates");

        // convert the msg to only the part in the camera and publish that to obj_range
    }

    // memory management in cpp
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_1;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscription_2;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LocationFinder>());
    rclcpp::shutdown();
    return 0
}