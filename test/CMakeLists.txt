aux_source_directory(. SRC_LIST)

#include_directories(${PROJECT_ROOT_PATH}/include)
#include_directories(${PROJECT_ROOT_PATH}/src)

#link_directories(${CuriosityGraphicsBase_SOURCE_DIR}/lib)
add_executable (01_test_model 01_test_model.cpp)
add_executable (02_test_cube_block 02_test_cube_block.cpp)
add_executable (03_test_skybox 03_test_skybox.cpp)
add_executable (04_test_freetype 04_test_freetype.cpp)
add_executable (05_test_octree 05_test_octree.cpp)

set(COMMON_LIBS CuriosityGraphicsBase freetype png assimp sb7 glfw3 X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL rt dl pthread z)
target_link_libraries(01_test_model ${COMMON_LIBS})
target_link_libraries(02_test_cube_block ${COMMON_LIBS})
target_link_libraries(03_test_skybox ${COMMON_LIBS})
target_link_libraries(04_test_freetype ${COMMON_LIBS})
target_link_libraries(05_test_octree ${COMMON_LIBS})

