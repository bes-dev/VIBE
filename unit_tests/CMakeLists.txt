##################################
# vibe_unittest
##################################

include_directories(${VIBE_DEPENDENCY_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/VIBE/include)

##################################
# Sources

file(GLOB_RECURSE sources_cpp *.cpp)
file(GLOB_RECURSE sources_h *.h)

include_directories()
##################################


##################################
# Target
add_executable(vibe_unittest ${sources_cpp} ${sources_h})
target_link_libraries(vibe_unittest vibe ${VIBE_DEPENDENCY_LIBS})

##################################
