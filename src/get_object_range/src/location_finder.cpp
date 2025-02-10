#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/point.hpp"
#include <functional>
#include <chrono>

using std::placeholders::_1;
using namespace std::chrono_literals;

class LocationFinder : public rclcpp::Node
{
public:
    LocationFinder() : Node("get_object_location_pubsub") // This is basically the cpp version of __init__
    {
        RCLCPP_INFO(this->get_logger(), "Starting Location Finder Node");

        recent_scan = sensor_msgs::msg::LaserScan();
        recent_coords = geometry_msgs::msg::Point();

        subscription_1 = this->create_subscription<sensor_msgs::msg::LaserScan>
        (
         "/scan",
         rclcpp::QoS(10).best_effort(),
         std::bind(&LocationFinder::scan_callback,this,_1)
        );

        subscription_2 = this->create_subscription<geometry_msgs::msg::Point>
        (
         "/obj_coords",
         rclcpp::QoS(10).reliable(),
         std::bind(&LocationFinder::coords_callback,this,_1)
        );
        
        timer_ = this->create_wall_timer(20ms, std::bind(&LocationFinder::timer_callback, this));

        publisher_ = this->create_publisher<geometry_msgs::msg::Point>
        ("/obj_range",
         10
        );
    }

private:
    void scan_callback(const sensor_msgs::msg::LaserScan & laser_msg) // message type & variable name
    {
        RCLCPP_INFO(this->get_logger(), "Received Laser Scan");

        recent_scan = laser_msg;
    }

    void coords_callback(const geometry_msgs::msg::Point & coords_msg)
    {
        RCLCPP_INFO(this->get_logger(),  "Received Object Coordinates");

        recent_coords = coords_msg;
    }

    void timer_callback()
    {
        // Check to be sure data has been collected from both topics
        if (!recent_scan.ranges.empty() && !(recent_coords.x == 0.0 && recent_coords.y == 0.0 && recent_coords.z == 0.0))
        {
            // convert the msg to only the part in the camera and publish that to obj_range
            
            RCLCPP_INFO(this->get_logger(),  "Publishing Object Location");
        }


    }

    // memory management in cpp
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_1;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscription_2;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
    sensor_msgs::msg::LaserScan recent_scan;
    geometry_msgs::msg::Point recent_coords;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LocationFinder>());
    rclcpp::shutdown();
    return 0;
}