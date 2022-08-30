cmake_minimum_required(VERSION 2.8.3)
project(state_machine)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wl,--no-as-needed")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

find_package(catkin REQUIRED COMPONENTS 
  roscpp 
  rospy 
  std_msgs 
  geometry_msgs 
  mav_msgs
  eigen_conversions
  tf_conversions
)

catkin_package(CATKIN_DEPENDS 
  roscpp 
  std_msgs 
  mav_msgs 
  tf
  eigen_conversions
  tf_conversions
)

find_package(Eigen3)

include_directories(${catkin_INCLUDE_DIRS})
link_directories(${CATKIN_DEVEL_PREFIX}/lib)
include_directories(${CATKIN_DEVEL_PREFIX}/include)

add_executable(state_machine src/state_machine.cc)
target_include_directories(state_machine PUBLIC include)
target_link_libraries(state_machine ${catkin_LIBRARIES})
