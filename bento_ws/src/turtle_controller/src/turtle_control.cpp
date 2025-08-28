#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class TurtleVelocityPublisher : public rclcpp::Node
{
public:
  TurtleVelocityPublisher()
  : Node("turtle_control")
  {
    // Cria o publisher que enviará mensagens Twist para o tópico do turtlesim
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    
    // Configura um timer para chamar a função de callback a cada 500ms
    timer_ = this->create_wall_timer(
      500ms, std::bind(&TurtleVelocityPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = geometry_msgs::msg::Twist();
    
    // Define a velocidade linear para mover a tartaruga para frente (2.0 m/s)
    message.linear.x = 2.0; 
    
    // Define a velocidade angular para rotacionar a tartaruga (1.0 rad/s)
    message.angular.z = 1.0; 
    
    // Exibe a mensagem no console para feedback
    RCLCPP_INFO(this->get_logger(), "Publishing velocity: linear.x=%.2f, angular.z=%.2f", message.linear.x, message.angular.z);
    
    // Publica a mensagem de velocidade no tópico
    publisher_->publish(message);
  }
  
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TurtleVelocityPublisher>());
  rclcpp::shutdown();
  return 0;
}