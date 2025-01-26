cmake_minimum_required(VERSION 3.8)
project(jambot)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(micro_ros_agent REQUIRED)
find_package(teleop_twist_joy REQUIRED)


# Add the executable and link dependencies
add_executable(controller_node src/controller_node.cpp)
ament_target_dependencies(controller_node rclcpp sensor_msgs geometry_msgs)

# Install the executable
install(TARGETS
controller_node
  DESTINATION lib/${PROJECT_NAME})

# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

# If testing is enabled, set up linter and testing tools
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # Skips the linter that checks for copyrights
  # Comment the line when a copyright and license are added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # Skips cpplint (only works in a git repo)
  # Comment the line when this package is in a git repo and when
  # a copyright and license are added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
