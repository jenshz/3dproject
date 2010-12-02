#include <iostream>
#include <cctype>

#include "lua.hh"

#include "ui.hh"
#include "components.hh"
#include "gl.hh"
#include "font.hh"


Component::~Component() {
std::cerr << "DEBUG: " << this << " destroyed" << std::endl;
}

void Container::add(Component *comp)
{
	children.push_back(comp);
}

void Container::draw(int px, int py)
{
	for (std::vector<Component*>::iterator it = children.begin(); it != children.end(); it++)
		if ((*it)->visible)
			(*it)->draw(x + px, y + py);
}

bool Container::onClick(int cx, int cy)
{
	cx -= x;
	cy -= y;
	for (std::vector<Component*>::reverse_iterator it = children.rbegin(); it != children.rend(); it++) {
		Component *c = *it;
		if ((*it)->visible && cx >= c->x && cy >= c->y && (cx < c->x + c->w) && (cy < c->y + c->h)) {
			// Is this a container?
			Container *t = dynamic_cast<Container*>(c);
			if (t) {
				return t->onClick(cx, cy);
			}

			ClickListener *cl = dynamic_cast<ClickListener*>(c);
			if (cl) {
				cl->onMouseDown();
				return true;
			}

			KeyListener *kl = dynamic_cast<KeyListener*>(c);
			if (kl) {
				kl->gainFocus();
				return true;
			}
		}
	}

	return false;
}

void Panel::layout()
{
}

void VerticalPanel::layout()
{
	// TODO
}

void HorizontalPanel::layout()
{
	// TODO
}

Label::Label(int rx, int ry, const std::string &text)
	: Component(rx, ry, 0, 0), caption(text)
{
}

void Label::draw(int px, int py)
{
  glColor3f(1., 0, 0);
  glRasterPos2i(px + x, py + y + 14);
  glPrint("%s", caption.c_str());
}

Button::Button(int x, int y, int mw, int mh, const std::string &text)
	: Component(x,y,mw,mh), caption(text)
{

}

void Button::draw(int px, int py)
{
	int nx = x + px;
	int ny = y + py;

	if (ui.hasFocus(this)) {
		glColor3f(0, 0, 0);
		fillRect(nx, ny, nx+w, ny+h);

		glColor3f(1, 1, 1);
	} else {
		glColor3f(1, 1, 1);
		fillRect(nx, ny, nx+w, ny+h);

		glColor3f(0, 0, 0);
	}

	glRasterPos2i(nx + 2, ny + 15);
	glPrint("%s", caption.c_str());

	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_LINE_LOOP);
		glVertex2i(nx,ny);
		glVertex2i(nx+w,ny);
		glVertex2i(nx+w,ny+h);
		glVertex2i(nx-1,ny+h);
	glEnd();
}

TextBox::TextBox(int x, int y, int mw, int mh, const std::string &text)
	: Component(x, y, mw, mh), text(text)
{
}

const std::string &TextBox::getText()
{
	return text;
}

void ClickListener::click()
{
	try {
		if (onClick && luabind::type(onClick) == LUA_TFUNCTION) {
			onClick(boost::ref(*this));
		}
	} catch (const std::exception &e) {
		std::cerr << e.what() << ":" << std::endl << lua_tostring(lua, -1) << std::endl;
	}
}

void ClickListener::onMouseDown()
{
	ui.setFocus(dynamic_cast<Component*>(this));
}

void TextBox::gainFocus()
{
	ui.setFocus(this);
}

void TextBox::keyPressed(int key)
{
	try {
		if (onKeyDown && luabind::type(onKeyDown) == LUA_TFUNCTION) {
			onKeyDown(boost::ref(*this), key);
		}
	} catch (const std::exception &e) {
		std::cerr << e.what() << ":" << std::endl << lua_tostring(lua, -1) << std::endl;
	}

	if (key == 8) {
		if (!text.empty()) {
			text.erase(text.length()-1);
		}
		return;
	} else if (key >= 32) {
		text += (char)key;
	}
}

void TextBox::draw(int px, int py)
{
	int nx = x + px;
	int ny = y + py;

	glColor3f(1, 1, 1);
	fillRect(nx, ny, nx+w, ny+h);

	if (ui.hasFocus(this)) {
		glColor3f(0, 0, 0);
		glRasterPos2i(nx + 2, ny + 15);
		glPrint("%s", text.c_str());

		int c[4];
		glGetIntegerv(GL_CURRENT_RASTER_POSITION, c);

		glColor3f(1., 0.3, 0.3);
		glRasterPos2i(c[0], app::height - c[1]);
		glPrint("|");
	} else {
		glColor3f(0, 0, 0);
		glRasterPos2i(nx + 2, ny + 15);
		glPrint("%s", text.c_str());

	}

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINE_LOOP);
		glVertex2i(nx,ny);
		glVertex2i(nx+w,ny);
		glVertex2i(nx+w,ny+h);
		glVertex2i(nx-1,ny+h);
	glEnd();

}
