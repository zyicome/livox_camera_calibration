cmake_minimum_required(VERSION 3.8)
project(save_pcd)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(PCL REQUIRED)
find_package(OpenCV)
find_package(pcl_conversions REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)
find_package(PkgConfig REQUIRED)
include_directories(include ${my_msgss_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
pkg_check_modules(LIBUSB1 REQUIRED libusb-1.0)
include_directories(${LIBUSB1_INCLUDE_DIRS})
link_directories(${LIBUSB1_LIBRARY_DIRS})


add_executable(${PROJECT_NAME}_node src/save_pcd.cpp)
ament_target_dependencies(${PROJECT_NAME}_node
        rclcpp
        rclpy
        std_msgs
        cv_bridge
        sensor_msgs
        pcl_conversions
        # radar_msgs
        # tf
)
target_link_directories(${PROJECT_NAME}_node PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include >
      $<INSTALL_INTERFACE:include>)


# add_dependencies(${PROJECT_NAME}_node radar_msgs_generate_messages)
target_link_libraries(${PROJECT_NAME}_node
        ${OpenCV_LIBS}
        ${PCL_LIBRARIES}
        ${Boost_LIBRARIES}
        ${LIBUSB1_LIBRARIES}
        ${PCL_IO_LIBRARY}
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

install(TARGETS
        ${PROJECT_NAME}_node
        DESTINATION lib/${PROJECT_NAME})

ament_package()
