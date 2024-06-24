cmake_minimum_required(VERSION 3.8)
project(cpp01_topic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(base_interfaces_demo REQUIRED)

add_executable(demo01_talker_str src/demo01_talker_str.cpp)
add_executable(demo02_listener_str src/demo02_listener_str.cpp)

target_include_directories(demo01_talker_str PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(demo01_talker_str PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

ament_target_dependencies(
  demo01_talker_str
  "rclcpp"
  "std_msgs"
  "base_interfaces_demo"
)

ament_target_dependencies(
  demo02_listener_str
  "rclcpp"
  "std_msgs"
  "base_interfaces_demo"
)

install(TARGETS 
  demo01_talker_str
  demo02_listener_str
  DESTINATION lib/${PROJECT_NAME})

# Generate and install prefix_chain.bash
set(PREFIX_CHAIN_BASH_CONTENT
"# generated from colcon_bash/shell/template/prefix_chain.bash.em
# This script extends the environment with the environment of other prefix
# paths which were sourced when this file was generated as well as all packages
# contained in this prefix path.

# function to source another script with conditional trace output
# first argument: the path of the script
_colcon_prefix_chain_bash_source_script() {
  if [ -f \"$1\" ]; then
    if [ -n \"$COLCON_TRACE\" ]; then
      echo \"# . \\\"$1\\\"\"
    fi
    . \"$1\"
  else
    echo \"not found: \\\"$1\\\"\" 1>&2
  fi
}

# source chained prefixes
# setting COLCON_CURRENT_PREFIX avoids determining the prefix in the sourced script
COLCON_CURRENT_PREFIX=\"/opt/ros/humble\"
_colcon_prefix_chain_bash_source_script \"$COLCON_CURRENT_PREFIX/local_setup.bash\"

# setting COLCON_CURRENT_PREFIX avoids determining the prefix in the sourced script
COLCON_CURRENT_PREFIX=\"/home/sora/Desktop/yihe/ws/install\"
_colcon_prefix_chain_bash_source_script \"$COLCON_CURRENT_PREFIX/local_setup.bash\"

# source this prefix
# setting COLCON_CURRENT_PREFIX avoids determining the prefix in the sourced script
COLCON_CURRENT_PREFIX=\"/home/sora/Desktop/yihe/ws/install\"
_colcon_prefix_chain_bash_source_script \"$COLCON_CURRENT_PREFIX/local_setup.bash\"

unset COLCON_CURRENT_PREFIX
unset _colcon_prefix_chain_bash_source_script
")

file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/prefix_chain.bash" CONTENT "${PREFIX_CHAIN_BASH_CONTENT}")

install(FILES
  "${CMAKE_BINARY_DIR}/prefix_chain.bash"
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()