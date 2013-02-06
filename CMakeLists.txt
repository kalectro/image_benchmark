cmake_minimum_required(VERSION 2.8.3)
project(image_benchmark)

find_package(catkin REQUIRED COMPONENTS cv_bridge image_transport std_msgs rospy roscpp)

catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES image_publisher image_subscriber
  CATKIN_DEPENDS cv_bridge image_transport std_msgs rospy roscpp
  DEPENDS system_lib
)

add_executable(image_transport_publisher_node src/image_transport_publisher.cpp)
add_executable(image_transport_subscriber_node src/image_transport_subscriber.cpp)
add_executable(feature_detection_node src/feature_detection.cpp)
add_executable(rosinit_benchmark_node src/rosinit_benchmark.cpp)

target_link_libraries(image_transport_publisher_node ${catkin_LIBRARIES})
target_link_libraries(image_transport_subscriber_node ${catkin_LIBRARIES})
target_link_libraries(feature_detection_node ${catkin_LIBRARIES})
target_link_libraries(rosinit_benchmark_node ${catkin_LIBRARIES})

