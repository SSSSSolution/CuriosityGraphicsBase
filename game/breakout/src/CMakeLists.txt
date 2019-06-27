aux_source_directory(. SRC_LIST)

#include_directories(${PROJECT_ROOT_PATH}/include)
#include_directories(${PROJECT_ROOT_PATH}/src)

#link_directories(${CuriosityGraphicsBase_SOURCE_DIR}/lib)
add_executable (breakout ${SRC_LIST})

set(COMMON_LIBS CuriosityGraphicsBase freetype png assimp sb7 glfw3 X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL rt dl pthread z)
target_link_libraries(breakout ${COMMON_LIBS})

