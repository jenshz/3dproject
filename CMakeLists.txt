cmake_minimum_required(VERSION 2.8)
project(PIPE)

find_package(Lua51 REQUIRED)
find_package(Luabind REQUIRED)

include_directories(
	/usr/include/lua5.1
	${LUABIND_INCLUDE_DIR}
	"${PIPE_SOURCE_DIR}/include"
	"${PIPE_SOURCE_DIR}/include/linux"
)

add_subdirectory(ui)
add_subdirectory(engine)

add_executable(pipe main.cc)
target_link_libraries(pipe GL GLU glut lua5.1 luabind engine ui)

