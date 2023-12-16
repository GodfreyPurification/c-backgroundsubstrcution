cmake_minimum_required(VERSION 3.0.0)
project(parkingsystem VERSION 0.1.0)

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(parkingsystem main.cpp)
target_link_libraries(parkingsystem ${OpenCV_LIBS} )

find_package( OpenCV REQUIRED )
link_directories($(OpenCV_INCLUDE_DIRS))
include_directories(${VEHICLE_PARKING_DEMO_SOURCE_DIR}/parkingrepo)
add_subdirectory(parkingrepo)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)