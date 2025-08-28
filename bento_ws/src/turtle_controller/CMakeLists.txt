cmake_minimum_required(VERSION 3.8)
project(turtle_controller)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

# Adiciona um executável a partir do seu arquivo .cpp
add_executable(turtle_control src/turtle_control.cpp)

# Define as dependências do executável para que o linker possa encontrá-las
ament_target_dependencies(turtle_control rclcpp geometry_msgs)

# Adiciona o executável ao diretório de instalação do ROS 2
install(TARGETS
  turtle_control
  DESTINATION lib/${PROJECT_NAME}
)

# Exporta as dependências para que outros pacotes possam encontrá-las
ament_export_dependencies(rclcpp geometry_msgs)

ament_package()