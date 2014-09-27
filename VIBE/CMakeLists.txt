##################################
# VIBE library
##################################

include_directories(${VIBE_DEPENDENCY_DIRS})

##################################
# Sources

file(GLOB_RECURSE vibe_cpp src/*.cpp)
file(GLOB_RECURSE vibe_hpp include/*.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
##################################

##################################
# Target

add_library(vibe ${vibe_cpp} ${vibe_hpp})
target_link_libraries(vibe ${VIBE_DEPENDENCY_LIBS})

##################################
