#include "stdafx.h"

#include <luabind/luabind.hpp>
#include <lua.hpp>

#include "ui.hh"
#include "point.hh"
#include "nurbs.hh"

#include "gl.hh"

#include <stdlib.h>


class System {
public:
	static void exit(int errorCode) {
		::exit(errorCode);
	}

	static void print(const std::string &what) {
		std::cout << what << std::endl;
	}
};

lua_State *lua;

void register_lua(int argc, char*argv[])
{
  using namespace luabind;

  lua = lua_open();
  luaL_openlibs(lua);

  open(lua);

  module(lua)
  [
    class_<Component>("Component"),
    class_<Window>("Window")
      .def(constructor<int,int,std::string>())
	  .def("add", &Window::add)
      .def_readwrite("title", &Window::title)
      .def_readwrite("width", &Window::w)
      .def_readwrite("height", &Window::h)
      .def_readwrite("x", &Window::x)
      .def_readwrite("y", &Window::y)
      .def_readwrite("draggable", &Window::draggable)
      .def_readwrite("onMove", &Window::onMove),

    class_<Point2D>("Point2D")
      .def(constructor<double,double>())
      .def_readwrite("x", &Point2D::x)
      .def_readwrite("y", &Point2D::y),
   
    class_<Nurbs>("Nurbs")
      .def(constructor<>())
      .def("addPoint", &Nurbs::addPoint),

	class_<Button, Component>("Button")
      .def(constructor<int,int,int,int,std::string>())
      .def_readwrite("caption", &Button::caption)
      .def_readwrite("width", &Button::w)
      .def_readwrite("height", &Button::h)
      .def_readwrite("x", &Button::x)
      .def_readwrite("y", &Button::y)
      .def_readwrite("onClick", &Button::onClick),

	class_<TextBox, Component>("TextBox")
      .def(constructor<int,int,int,int,std::string>())
      .def_readwrite("text", &TextBox::text)
      .def_readwrite("width", &TextBox::w)
      .def_readwrite("height", &TextBox::h)
      .def_readwrite("x", &TextBox::x)
      .def_readwrite("y", &TextBox::y)
      .def_readwrite("onKeyDown", &TextBox::onKeyDown),

	class_<Screen>("Screen")
	.scope
	[
	  def("getWidth", &Screen::getWidth),
	  def("getHeight", &Screen::getHeight),
	  def("setSize", &Screen::setSize),
	  def("toggleFullScreen", &Screen::toggleFullScreen)
	],

	class_<System>("System")
	.scope
	[
	  def("print", &System::print),
	  def("exit", &System::exit)
	]

  ];
}

void cleanup_lua()
{
  // remember to clean up lua.
	lua_close(lua);
}
