#include "stdafx.h"

#include <luabind/luabind.hpp>
#include <lua.hpp>

#include "ui.hh"
#include "point.hh"
#include "nurbs.hh"

#include "gl.hh"

#include "engine.hh"

#include <stdlib.h>


namespace System {
  bool exiting = false;
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
    class_<Container, Component>("Container")
      .def("layout", &Container::layout)
      .def("add", &Container::add),

    class_<Window, Container>("Window")
      .def(constructor<int,int,std::string>())
      .def("pack", &Window::pack)
      .def_readwrite("border", &Window::border)
      .def_readwrite("title", &Window::title)
      .def_readwrite("width", &Window::w)
      .def_readwrite("height", &Window::h)
      .def_readwrite("x", &Window::x)
      .def_readwrite("y", &Window::y)
      .def_readwrite("draggable", &Window::draggable)
      .def_readwrite("onMove", &Window::onMove),

    class_<Nurbs>("Nurbs")
      .def(constructor<>())
      .def("addPoint", &Nurbs::addPoint),

    class_<Panel, Container>("Panel")
      .def(constructor<>())
      .def_readwrite("x", &Panel::x)
      .def_readwrite("y", &Panel::y),

    class_<HorizontalPanel, Container>("HorizontalPanel")
      .def(constructor<>())
      .def_readwrite("x", &HorizontalPanel::x)
      .def_readwrite("y", &HorizontalPanel::y),

    class_<VerticalPanel, Container>("VerticalPanel")
      .def(constructor<>())
      .def_readwrite("x", &VerticalPanel::x)
      .def_readwrite("y", &VerticalPanel::y),

    class_<Label, Component>("Label")
      .def(constructor<std::string, int>())
      .def_readwrite("caption", &Label::caption)
      .def_readwrite("x", &Label::x)
      .def_readwrite("y", &Label::y),

    class_<Button, Component>("Button")
      .def(constructor<std::string, int>())
      .def(constructor<int,int,int,int,std::string>())
      .def_readwrite("caption", &Button::caption)
      .def_readwrite("width", &Button::w)
      .def_readwrite("height", &Button::h)
      .def_readwrite("x", &Button::x)
      .def_readwrite("y", &Button::y)
      .def_readwrite("onClick", &Button::onClick),

	class_<TextBox, Component>("TextBox")
      .def(constructor<std::string, int>())
      .def(constructor<int,int,int,int,std::string>())
      .def_readwrite("text", &TextBox::text)
      .def_readwrite("width", &TextBox::w)
      .def_readwrite("height", &TextBox::h)
      .def_readwrite("x", &TextBox::x)
      .def_readwrite("y", &TextBox::y)
      .def_readwrite("onKeyDown", &TextBox::onKeyDown),

  class_<Point3f>("Point3f")
    .def(constructor<>())
    .def(constructor<float, float, float>()),

  class_<SceneObject>("SceneObject")
    .def(constructor<int>())
    .def_readwrite("pos", &SceneObject::pos)
    .def_readwrite("color", &SceneObject::color)
    .def_readwrite("scale", &SceneObject::scale)
    .def_readwrite("onClick", &SceneObject::onClick)
    .def_readwrite("id", &SceneObject::id)
    .enum_("constants")
    [
      value("MQuad", 0),
      value("MCube", 1),
      value("MSphere", 2),
      value("MObject", 3)
     ],
  def("createQuad", &SceneObject::createQuad),

  class_<Camera>("Camera")
    .def_readwrite("rotX", &Camera::rotX)
    .def_readwrite("rotY", &Camera::rotY),

  class_<Scene>("Scene")
    .def_readwrite("onDeselect", &Scene::onDeselect)	
    .def("add", &Scene::add)
    .def("getCamera", &Scene::getCamera)
    .scope
	  [
      def("get", &Scene::get)
  	],

	class_<Screen>("Screen")
	.scope
	[
	  def("getWidth", &Screen::getWidth),
	  def("getHeight", &Screen::getHeight),
	  def("setSize", &Screen::setSize),
	  def("toggleFullScreen", &Screen::toggleFullScreen)
	]
  ];
}

void cleanup_lua()
{
  // remember to clean up lua.
	lua_close(lua);
}
