cmake_minimum_required(VERSION 2.8.3)
project(dynamixel_control_hw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIBDYNAMIXEL "")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  urdf
  std_msgs
  embedded_joint_limits_interface
  message_generation
  hardware_interface
  controller_manager
  libdynamixel_ros
)

catkin_package(CATKIN_DEPENDS
  roscpp
  urdf
  std_msgs
  message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_executable(dynamixel_control_p1 src/dynamixel_control.cpp)
target_compile_definitions(dynamixel_control_p1 PRIVATE PROTOCOL1)
target_link_libraries(dynamixel_control_p1 ${catkin_LIBRARIES})

add_executable(dynamixel_control_p2 src/dynamixel_control.cpp)
target_link_libraries(dynamixel_control_p2 ${catkin_LIBRARIES})

add_library(dynamixel_hw
  src/hardware_interface.cpp
)
target_link_libraries(dynamixel_hw ${catkin_LIBRARIES})

install(TARGETS dynamixel_hw
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(FILES dynamixel_plugins.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
