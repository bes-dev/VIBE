##################################
# vibe simple app
##################################

include_directories(${VIBE_DEPENDENCY_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/VIBE/include)

##################################
# Sources

file(GLOB_RECURSE sources_cpp *.cpp)
file(GLOB_RECURSE sources_hpp *.hpp)
##################################

##################################
# Target

add_executable(simple_app ${sources_cpp} ${sources_hpp})
target_link_libraries(simple_app vibe ${VIBE_DEPENDENCY_LIBS})
##################################
