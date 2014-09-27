#############################################
# VIBE project
#############################################
cmake_minimum_required(VERSION 2.8)

project(VIBE)
set(VIBE_VERSION_MAJOR 0)
set(VIBE_VERSION_MINOR 1)

#############################################
# Dependencies

#OpenCV
find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(SEND_ERROR "Faild to find Opencv")
    return()
else()
    set(VIBE_DEPENDENCY_DIRS ${OpenCV_INCLUDE_DIRS} ${VIBE_DEPENDENCY_DIRS})
    set(VIBE_DEPENDENCY_LIBS ${OpenCV_LIBS} ${VIBE_DEPENDENCY_LIBS})
endif()
#############################################


#############################################
#General compiler flags

add_definitions(-DDEBUG_MODE) #This shows all messages from LOG()
add_definitions(-Wall) #Enable all warnings always
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=gnu++0x -mtune=corei7 -march=corei7 -lpthread")

#############################################
add_subdirectory(3rdparty)
add_subdirectory(VIBE)
add_subdirectory(apps)
add_subdirectory(unit_tests)
