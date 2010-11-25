cmake_minimum_required(VERSION 2.8)
project(PIPE)

find_package(Lua REQUIRED)
find_package(Luabind REQUIRED)

include_directories(
	${LUA_INCLUDE_DIR}
	${LUABIND_INCLUDE_DIR}
)

# System wide
include_directories(${PIPE_SOURCE_DIR}/include)

# Platform specific
if(${UNIX})
  include_directories(${PIPE_SOURCE_DIR}/include/linux)
endif(${UNIX})

add_subdirectory(ui)
add_subdirectory(engine)

add_executable(pipe main.cc)
target_link_libraries(pipe GL GLU glut lua5.1 luabind engine ui)

