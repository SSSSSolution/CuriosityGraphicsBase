aux_source_directory(. SRC_LIST)
aux_source_directory(./drawable_object SRC_LIST)
aux_source_directory(./text_renderer SRC_LIST)
aux_source_directory(./geometry SRC_LIST)
aux_source_directory(./scene_managing SRC_LIST)
aux_source_directory(./data_struct SRC_LIST)

set(COMMON_LIBS freetype glfw3 X11 Xrandr Xinerama Xi Xxf86vm XCursor GL rt dl pthread)

add_library(CuriosityGraphicsBase SHARED ${SRC_LIST})
set_target_properties(CuriosityGraphicsBase PROPERTIES VERSION 1.0.0 SOVERSION 0)

#aux_source_directory(. SRC_LIST)

#include_directories(${PROJECT_SOURCE_DIR}/include)

#link_directories(${PROJECT_SOURCE_DIR}/lib)

#add_executable (03_draw_triangle ${SRC_LIST})

#set(COMMON_LIBS sb7 glfw3 X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL rt dl pthread)
#target_link_libraries(03_draw_triangle ${COMMON_LIBS})
#set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
