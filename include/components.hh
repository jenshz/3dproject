#ifndef _COMPONENTS_HH_
#define _COMPONENTS_HH_

#include <string>
#include <vector>

#include "stdafx.h"

class Container;

class Component {
public:
	Component()
		: x(0), y(0), w(0), h(0), parent(0), visible(true)
	{ }
	
	Component(int mx, int my, int mw, int mh)
		: x(mx), y(my), w(mw), h(mh), parent(0), visible(true) 
	{ }

	virtual ~Component();

	virtual void draw(int px, int py) = 0;

	virtual void setParent(Container *p) {
		this->parent = p;
	}

	// Vars:
	Container *parent;

	int x, y;
	int w, h;

	bool visible;
};


class Container : public Component {
protected:
	std::vector<Component*> children;
public:
	Container(int mx, int my, int mw, int mh)
		: Component(mx, my, mw, mh)
	{
	}

	virtual void add(Component *comp);
	virtual void layout() = 0;
	virtual void draw(int px, int py);
	virtual bool onClick(int cx, int cy);
};


class ClickListener {
public:
	virtual void click();
	virtual void onMouseDown();

	luabind::object onClick;
};


class KeyListener {
public:
	virtual void gainFocus() = 0;
	virtual void keyPressed(int key) = 0;

	luabind::object onKeyDown;
};


class Panel : public Container {
public:
	virtual void layout();
};


class VerticalPanel : public Panel {
public:
	virtual void layout();
};


class HorizontalPanel : public Panel {
public:
	virtual void layout();
};


class Label : public Component {
public:
	Label(int x, int y, const std::string &text);

	virtual void draw(int px, int py);

	std::string caption;
};


class Button : public Component, public ClickListener {
public:
	Button(int x, int y, int w, int h, const std::string &text);

	virtual void draw(int px, int py);

	std::string caption;
};


class TextBox : public Component, public KeyListener {
public:
	TextBox(int mx, int my, int w, int h, const std::string &mtext);

	const std::string &getText();

	virtual void gainFocus();
	virtual void keyPressed(int key);
	virtual void draw(int px, int py);

	std::string text;
};

#endif
