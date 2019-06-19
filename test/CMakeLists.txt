aux_source_directory(. SRC_LIST)

#include_directories(${PROJECT_ROOT_PATH}/include)
#include_directories(${PROJECT_ROOT_PATH}/src)

#link_directories(${CuriosityGraphicsBase_SOURCE_DIR}/lib)
add_executable (01_test_model 01_test_model.cpp)
add_executable (02_test_cube_block 02_test_cube_block.cpp)

set(COMMON_LIBS CuriosityGraphicsBase assimp sb7 glfw3 X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL rt dl pthread)
target_link_libraries(01_test_model ${COMMON_LIBS})
target_link_libraries(02_test_cube_block ${COMMON_LIBS})

