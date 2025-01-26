#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <vector>
#include <string>

class TriggerControlNode : public rclcpp::Node
{
public:
    TriggerControlNode() : Node("trigger_control_node"),
                           current_linear_speed_(0.5), // Default linear speed scale
                           current_angular_speed_(0.5) // Default angular speed scale
    {
        // Create a publisher for /cmd_vel2
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel2", 10);

        // Create a subscriber for /joy topic (joystick input)
        subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "/joy", 10, std::bind(&TriggerControlNode::joy_callback, this, std::placeholders::_1));

        // Initialize Twist message
        twist_ = geometry_msgs::msg::Twist();
    }

private:
    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
{
    // Example: Check if specific buttons are pressed
    if (msg->buttons[0]) { RCLCPP_INFO(this->get_logger(), "Button A pressed!"); }
    if (msg->buttons[1]) { RCLCPP_INFO(this->get_logger(), "Button B pressed!"); }
    if (msg->buttons[2]) { RCLCPP_INFO(this->get_logger(), "Button X pressed!"); }
    if (msg->buttons[3]) { RCLCPP_INFO(this->get_logger(), "Button Y pressed!"); }
    if (msg->buttons[4]) { RCLCPP_INFO(this->get_logger(), "Button L1 pressed!"); }
    if (msg->buttons[5]) { RCLCPP_INFO(this->get_logger(), "Button L2 pressed!"); }
    if (msg->buttons[6]) { RCLCPP_INFO(this->get_logger(), "Button R2 pressed!"); }
    if (msg->buttons[7]) { RCLCPP_INFO(this->get_logger(), "Button R3 pressed!"); }

    // Handle D-Pad for speed adjustment (axes[6] for horizontal, axes[7] for vertical)
    float dpad_horizontal = msg->axes[6]; // D-Pad horizontal axis
    float dpad_vertical = msg->axes[7];   // D-Pad vertical axis

    // Adjust linear speed scale with D-Pad vertical
    if (dpad_vertical > 0.0) // D-Pad up
    {
        current_linear_speed_ += 0.05;
        current_linear_speed_ = std::min(current_linear_speed_, 1.0f); // Clamp to max 1.0
        RCLCPP_INFO(this->get_logger(), "Increased linear speed scale: %.2f", current_linear_speed_);
    }
    else if (dpad_vertical < 0.0) // D-Pad down
    {
        current_linear_speed_ -= 0.05;
        current_linear_speed_ = std::max(current_linear_speed_, 0.1f); // Clamp to min 0.1
        RCLCPP_INFO(this->get_logger(), "Decreased linear speed scale: %.2f", current_linear_speed_);
    }

    // Adjust angular speed scale with D-Pad horizontal
    if (dpad_horizontal > 0.0) // D-Pad right
    {
        current_angular_speed_ -= 0.05;
        current_angular_speed_ = std::min(current_angular_speed_, 1.0f); // Clamp to max 1.0
        RCLCPP_INFO(this->get_logger(), "Increased angular speed scale: %.2f", current_angular_speed_);
    }
    else if (dpad_horizontal < 0.0) // D-Pad left
    {
        current_angular_speed_ += 0.05;
        current_angular_speed_ = std::max(current_angular_speed_, 0.1f); // Clamp to min 0.1
        RCLCPP_INFO(this->get_logger(), "Decreased angular speed scale: %.2f", current_angular_speed_);
    }

    // Map right trigger (R2) to forward speed (0 to 1 range)
    float right_trigger = msg->axes[5]; // Right trigger
    twist_.linear.x = current_linear_speed_ * right_trigger;

    // Map left trigger (L2) to reverse speed (0 to -1 range)
    float left_trigger = msg->axes[4]; // Left trigger
    twist_.linear.x += current_linear_speed_ * (-left_trigger);

    // Use left joystick (horizontal axis) for turning
    twist_.angular.z = current_angular_speed_ * msg->axes[0]; // Left joystick horizontal axis

    // Publish the updated Twist message to /cmd_vel2
    publisher_->publish(twist_);
}


    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
    geometry_msgs::msg::Twist twist_;

    float current_linear_speed_; // Current linear speed scale
    float current_angular_speed_; // Current angular speed scale
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TriggerControlNode>());
    rclcpp::shutdown();
    return 0;
}
