#include <iostream>
#include <cctype>

#include "lua.hh"

#include "ui.hh"
#include "components.hh"
#include "gl.hh"
#include "font.hh"

#define PADDING 2

static const float ui_text[] = { 0.0, 0.0, 0.8 };
static const float ui_front[] = { 0.7, 0.7, 0.7 };
static const float ui_pressed[] = { 0.8, 0.8, 0.8 };
static const float ui_border1[] = { 1.0, 1.0, 1.0 };
static const float ui_border2[] = { 0.2, 0.2, 0.2 };

Component::~Component() {
  if(!System::exiting) {
    std::cerr << "DEBUG: " << this << " destroyed" << std::endl;
  }
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

void Container::layout()
{
  // Just keep the components in their designed position
  // But update width and heights of child containers
  for (std::vector<Component*>::iterator it = children.begin(); it != children.end(); it++) {
    Container *ct = dynamic_cast<Container*>(*it);
    if (ct) {
      ct->layout();
    }
  }
}

void Panel::layout()
{
  Container::layout();
}

void VerticalPanel::layout()
{
  // First layout all sub-containers (this will update their size)
  // At the same time update the width and height
  h = 0;
  w = 0;
  for (std::vector<Component*>::iterator it = children.begin(); it != children.end(); it++) {
    Container *ct = dynamic_cast<Container*>(*it);
    if (ct) {
      ct->layout();
    }
    (*it)->y = h;
    (*it)->x = 0;
    h += (*it)->h + PADDING * 2;
    w = w > (*it)->w ? w : (*it)->w;
  }
}

void HorizontalPanel::layout()
{
  // First layout all sub-containers (this will update their size)
  // At the same time update the width and height
  h = 0;
  w = 0;
  for (std::vector<Component*>::iterator it = children.begin(); it != children.end(); it++) {
    Container *ct = dynamic_cast<Container*>(*it);
    if (ct) {
      ct->layout();
    }
    (*it)->y = 0;
    (*it)->x = w;
    w += (*it)->w + PADDING * 2;
    h = h > (*it)->h ? h : (*it)->h;
  }
}

Label::Label(const std::string &text, int w)
	: Component(0, 0, w, 16), caption(text)
{
}

void Label::draw(int px, int py)
{
  glColor3f(0, 0, 0);
  glRasterPos2i(px + x, py + y + 14);
  glPrint("%s", caption.c_str());
}

Button::Button(const std::string &text, int width)
	: Component(0,0,width,20), caption(text)
{
}

Button::Button(int x, int y, int mw, int mh, const std::string &text)
	: Component(x,y,mw,mh), caption(text)
{
}

void Button::draw(int px, int py)
{
	int nx = x + px;
	int ny = y + py;

  bool focus = ui.hasFocus(this);

	if (focus) {
    glColor3fv(ui_pressed);
	} else {
    glColor3fv(ui_front);
  }

  fillRect(nx, ny, nx+w, ny+h);

  glColor3f(0, 0, 0);
	glRasterPos2i(nx + 2, ny + 15);
	glPrint("%s", caption.c_str());

  glBegin(GL_LINE_LOOP);
    if (focus) {
      glColor3fv(ui_border2);
    } else {
      glColor3fv(ui_border1);
    }

    glVertex2i(nx,ny);
    glVertex2i(nx+w,ny);

    if (focus) {
      glColor3fv(ui_border1);
    } else {
      glColor3fv(ui_border2);
    }

    glVertex2i(nx+w,ny+h);
    glVertex2i(nx,ny+h);
  glEnd();
}

ImageButton::ImageButton(Texture *fg, int w, int h)
  : Button("", w), tex(fg)
{
  this->h = h;
}

void ImageButton::draw(int px, int py)
{
	int nx = x + px;
	int ny = y + py;

  bool focus = ui.hasFocus(this);

	if (focus) {
    glColor3fv(ui_pressed);
	} else {
    glColor3fv(ui_front);
  }

  fillRect(nx, ny, nx+w, ny+h);

  glEnable(GL_TEXTURE_2D);
  tex->use();
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // Draw image
  glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex2i(nx, ny);
    glTexCoord2f(1,1);
    glVertex2i(nx+w, ny);
    glTexCoord2f(1,0);
    glVertex2i(nx+w, ny+h);
    glTexCoord2f(0,0);
    glVertex2i(nx, ny+h);
  glEnd();

  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
  
  // Draw border
  glBegin(GL_LINE_LOOP);
    if (focus) {
      glColor3fv(ui_border2);
    } else {
      glColor3fv(ui_border1);
    }

    glVertex2i(nx,ny);
    glVertex2i(nx+w,ny);

    if (focus) {
      glColor3fv(ui_border1);
    } else {
      glColor3fv(ui_border2);
    }

    glVertex2i(nx+w,ny+h);
    glVertex2i(nx,ny+h);
  glEnd();
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

TextBox::TextBox(const std::string &text, int width)
	: Component(0, 0, width, 20), text(text)
{
}

TextBox::TextBox(int x, int y, int mw, int mh, const std::string &text)
	: Component(x, y, mw, mh), text(text)
{
}

const std::string &TextBox::getText()
{
	return text;
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
