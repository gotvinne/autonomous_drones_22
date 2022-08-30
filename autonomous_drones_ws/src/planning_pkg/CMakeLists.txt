cmake_minimum_required(VERSION 2.8.3)
project(planning_pkg)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wl,--no-as-needed")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

find_package(catkin REQUIRED COMPONENTS
	geometry_msgs
	roscpp
	rospy
	sensor_msgs
	std_msgs
	tf
	image_transport
		fla_utils
		fla_msgs
		cv_bridge
		message_generation
		mav_msgs
)

catkin_package(CATKIN_DEPENDS
    mav_msgs
)

link_directories(${CATKIN_DEVEL_PREFIX}/lib)
include_directories(${catkin_INCLUDE_DIRS})

add_executable(map_service src/map_service.cpp)
target_link_libraries(map_service ${catkin_LIBRARIES})
add_dependencies(map_service ${catkin_EXPORTED_TARGETS})

add_executable(point_cloud_converter src/point_cloud_converter.cc)
target_include_directories(point_cloud_converter PUBLIC include)
target_link_libraries(point_cloud_converter ${catkin_LIBRARIES})
add_dependencies(point_cloud_converter ${catkin_EXPORTED_TARGETS})

add_executable(pointcloud_merger src/pointcloud_merger.cpp)
target_include_directories(pointcloud_merger PUBLIC include)
target_link_libraries(pointcloud_merger  ${catkin_LIBRARIES})
add_dependencies(pointcloud_merger ${catkin_EXPORTED_TARGETS})

