#include <luabind/luabind.hpp>
#include <lua.hpp>

#include "ui.hh"
#include "point.hh"
#include "nurbs.hh"

lua_State *lua;

void register_lua(int argc, char*argv[])
{
  using namespace luabind;

  lua = lua_open();
  luaL_openlibs(lua);

  open(lua);

  luabind::registry(lua)["objects"] = luabind::newtable(lua);

  module(lua)
  [
    class_<Window>("Window")
      .def(constructor<int,int,std::string>())
      .def_readwrite("title", &Window::title)
      .def_readwrite("width", &Window::w)
      .def_readwrite("height", &Window::h)
      .def_readwrite("x", &Window::x)
      .def_readwrite("y", &Window::y)
      .def_readwrite("draggable", &Window::draggable)
      .def_readwrite("onMove", &Window::onMove)
      .def_readwrite("onClick", &Window::onClick),

    class_<Point2D>("Point2D")
      .def(constructor<double,double>())
      .def_readwrite("x", &Point2D::x)
      .def_readwrite("y", &Point2D::y),
   
    class_<Nurbs>("Nurbs")
      .def(constructor<>())
      .def("addPoint", &Nurbs::addPoint)
  ];
}

void cleanup_lua()
{
  // remember to clean up lua.
	lua_close(lua);
}
