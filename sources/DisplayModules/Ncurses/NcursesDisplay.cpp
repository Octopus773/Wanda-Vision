//
// Created by Zoe Roux on 3/22/21.
//

#include "NcursesDisplay.hpp"
#include <ncurses.h>
#include <iostream>
#include "Common/Events/MouseClickEvent.hpp"
#include "Common/Events/KeyBoardEvent.hpp"
#include "Common/Events/Event.hpp"
#include "Common/ModInfo.hpp"

namespace Arcade
{

	bool NcursesDisplay::init()
	{
		this->_shouldClose = false;
		initscr();
		cbreak();
		curs_set(FALSE);
		keypad(stdscr, TRUE);
		mousemask(ALL_MOUSE_EVENTS, NULL);
		start_color();

		for (auto &color : colors) {
			short i = (((color[0] / 255) << 0) |
	                   ((color[1] / 255) << 1) |
	                   ((color[2] / 255) << 2));
			init_pair(color[3] + 1, i, COLOR_BLACK);
		}

		timeout(500);
		noecho();
		this->refresh();
		return true;
	}

	bool NcursesDisplay::close()
	{
		endwin();
		return true;
	}

	bool NcursesDisplay::shouldClose()
	{
		return this->_shouldClose;
	}

	std::list<std::unique_ptr<Event>> NcursesDisplay::pullEvents()
	{
		std::list<std::unique_ptr<Event>> events;
		std::vector<Events::KeyboardEvent::KeyCode> holded;
		int key;

		while ((key = getch()) != ERR) {
			if (key == KEY_MOUSE) {
				MEVENT mouse;
				Events::MouseClickEvent event;
				event.type = Event::KeyDown;
				if (getmouse(&mouse) != OK)
					continue;
				event.x = mouse.x * 100. / this->_width;
				event.y = mouse.y * 100. / this->_height;
				event.button = mouse.bstate & BUTTON1_PRESSED ? Events::MouseClickEvent::LEFT : Events::MouseClickEvent::RIGHT;
				events.emplace_back(std::make_unique<Events::MouseClickEvent>(event));
				continue;
			}
			Events::KeyboardEvent::KeyCode code = this->_getStdKey(key);
			bool contains = std::find(this->_keysHolded.begin(), this->_keysHolded.end(), code) != this->_keysHolded.end();

			Events::KeyboardEvent event;
			event.type = contains ? Event::KeyHold : Event::KeyDown;
			event.key = code;

			events.emplace_back(std::make_unique<Events::KeyboardEvent>(event));
			holded.push_back(code);
		}
		auto filter = std::views::filter([&holded](auto x)
		{
			return std::find(holded.begin(), holded.end(), x) == holded.end();
		});
		for (auto code : this->_keysHolded | filter) {
			Events::KeyboardEvent event;
			event.type = Event::KeyUp;
			event.key = code;
			events.emplace_back(std::make_unique<Events::KeyboardEvent>(event));
		}
		this->_keysHolded = holded;
		return events;
	}

	int NcursesDisplay::_getPosX(int x) const
	{
		int max = std::min(this->_width, this->_height * 2);
		int off = (this->_width - max) / 2;
		return off + int(max / 100. * x);
	}

	int NcursesDisplay::_getPosY(int y) const
	{
		int max = std::min(this->_width, this->_height);
		int off = (this->_height - max) / 2;
		return off + int(max / 100. * y);
	}

	void NcursesDisplay::_setColor(Drawables::ADrawable &obj) const
	{
		unsigned char r = (obj.color & (0xFF << 24)) >> 24;
		unsigned char g = (obj.color & (0xFF << 16)) >> 16;
		unsigned char b = (obj.color & (0xFF << 8)) >> 8;

		auto bcolor = colors[0];
		for (const auto &ccolor : colors)
			if (std::sqrt((r * ccolor[0]) + (g * ccolor[1]) + (b * ccolor[2])) >
			    std::sqrt((r * bcolor[0]) + (g * bcolor[1]) + (b * bcolor[2])))
				bcolor = ccolor;
		attron(COLOR_PAIR(bcolor[3] + 1));
	}

	bool NcursesDisplay::draw(Drawables::Line &obj)
	{
		if (obj.y == obj.endY) {
			this->_setColor(obj);
			int x = std::min(this->_getPosX(obj.x), this->_getPosX(obj.endX));
			int length =  std::abs(this->_getPosX(obj.endX) - this->_getPosX(obj.x)) + 1;
			mvaddstr(this->_getPosY(obj.y), x, ('+' + std::string(length - 2, '-') + '+').c_str());
			return true;
		}
		if (obj.x == obj.endX) {
			this->_setColor(obj);
			int x = this->_getPosX(obj.x);
			int i = std::min(this->_getPosY(obj.y),  this->_getPosY(obj.endY));
			int end = std::max(this->_getPosY(obj.y),  this->_getPosY(obj.endY));
			mvaddch(i, x, '+');
			for (i++; i < end; i++)
				mvaddch(i, x, '|');
			mvaddch(i, x, '+');
			return true;
		}
		return false;
	}

	bool NcursesDisplay::draw(Drawables::Rectangle &obj)
	{
		this->_setColor(obj);
		int x = std::min(this->_getPosX(obj.x), this->_getPosX(obj.endX));
		int y = std::min(this->_getPosY(obj.y), this->_getPosY(obj.endY));
		int width = std::abs(this->_getPosX(obj.endX) - this->_getPosX(obj.x)) + 1;
		int height = std::abs(this->_getPosY(obj.endY) - this->_getPosY(obj.y));
		mvaddstr(y, x, ('+' + std::string(std::max(width - 2, 0), '-') + '+').c_str());
		for (int i = y + 1; i < height - 1; i++)
			mvaddstr(i, x, ('|' + std::string(width - 2, 'o') + '|').c_str());
		mvaddstr(y + height, x, ('+' + std::string(std::max(width - 2, 0), '-') + '+').c_str());
		return true;
	}

	bool NcursesDisplay::draw(Drawables::Circle &obj)
	{
		return false;
	}

	bool NcursesDisplay::draw(Drawables::Text &obj)
	{
		this->_setColor(obj);
		mvaddstr(this->_getPosY(obj.y) + 1, this->_getPosX(obj.x), obj.text.c_str());
		return true;
	}

	bool NcursesDisplay::draw(Drawables::Sprite &obj)
	{
		return false;
	}

	bool NcursesDisplay::refresh()
	{
		::refresh();
		clear();
		getmaxyx(stdscr, this->_height, this->_width);
		return true;
	}

	ModInfo::Modtype NcursesDisplay::getType() const
	{
		return ModInfo::GRAPHIC;
	}

	bool NcursesDisplay::load(const std::string &type, const std::string &path)
	{
		return false;
	}

	void NcursesDisplay::unload(const std::string &type, const std::string &path) { }

	void NcursesDisplay::unloadAll() { }

	Events::KeyboardEvent::KeyCode NcursesDisplay::_getStdKey(unsigned int key) const
	{
		switch (key) {
		case 'a':           return Events::KeyboardEvent::KEY_A;
		case 'b':           return Events::KeyboardEvent::KEY_B;
		case 'c':           return Events::KeyboardEvent::KEY_C;
		case 'd':           return Events::KeyboardEvent::KEY_D;
		case 'e':           return Events::KeyboardEvent::KEY_E;
		case 'f':           return Events::KeyboardEvent::KEY_F;
		case 'g':           return Events::KeyboardEvent::KEY_G;
		case 'h':           return Events::KeyboardEvent::KEY_H;
		case 'i':           return Events::KeyboardEvent::KEY_I;
		case 'j':           return Events::KeyboardEvent::KEY_J;
		case 'k':           return Events::KeyboardEvent::KEY_K;
		case 'l':           return Events::KeyboardEvent::KEY_L;
		case 'm':           return Events::KeyboardEvent::KEY_M;
		case 'n':           return Events::KeyboardEvent::KEY_N;
		case 'o':           return Events::KeyboardEvent::KEY_O;
		case 'p':           return Events::KeyboardEvent::KEY_P;
		case 'q':           return Events::KeyboardEvent::KEY_Q;
		case 'r':           return Events::KeyboardEvent::KEY_R;
		case 's':           return Events::KeyboardEvent::KEY_S;
		case 't':           return Events::KeyboardEvent::KEY_T;
		case 'u':           return Events::KeyboardEvent::KEY_U;
		case 'v':           return Events::KeyboardEvent::KEY_V;
		case 'w':           return Events::KeyboardEvent::KEY_W;
		case 'x':           return Events::KeyboardEvent::KEY_X;
		case 'y':           return Events::KeyboardEvent::KEY_Y;
		case 'z':           return Events::KeyboardEvent::KEY_Z;
		case '0':           return Events::KeyboardEvent::KEY_0;
		case '1':           return Events::KeyboardEvent::KEY_1;
		case '2':           return Events::KeyboardEvent::KEY_2;
		case '3':           return Events::KeyboardEvent::KEY_3;
		case '4':           return Events::KeyboardEvent::KEY_4;
		case '5':           return Events::KeyboardEvent::KEY_5;
		case '6':           return Events::KeyboardEvent::KEY_6;
		case '7':           return Events::KeyboardEvent::KEY_7;
		case '8':           return Events::KeyboardEvent::KEY_8;
		case '9':           return Events::KeyboardEvent::KEY_9;
		case '\b':
		case '\x7F':
		case KEY_BACKSPACE: return Events::KeyboardEvent::BACKSPACE;
		case KEY_HOME:      return Events::KeyboardEvent::HOME;
		case KEY_LEFT:      return Events::KeyboardEvent::LEFT_ARROW;
		case KEY_UP:        return Events::KeyboardEvent::UP_ARROW;
		case KEY_RIGHT:     return Events::KeyboardEvent::RIGHT_ARROW;
		case KEY_DOWN:      return Events::KeyboardEvent::DOWN_ARROW;
		case KEY_DC:        return Events::KeyboardEvent::DELETE;
		case KEY_SELECT:    return Events::KeyboardEvent::SELECT;
		case '*':           return Events::KeyboardEvent::MULTIPLY;
		case '+':           return Events::KeyboardEvent::ADD;
		case '-':           return Events::KeyboardEvent::SUBTRACT;
		case '.':           return Events::KeyboardEvent::DECIMAL;
		case ',':           return Events::KeyboardEvent::COMMA;
		default:            return Events::KeyboardEvent::UNDEFINED;
		}
	}

	void NcursesDisplay::playSound(Sound &sound)
	{
	}

	extern "C" ModInfo getHeader()
	{
		ModInfo m;

		m.magicNumber = MagicNumber;
		m.name = "Ncurses";
		m.type = ModInfo::Modtype::GRAPHIC;
		return m;
	}

	extern "C" Arcade::IModule *getModule()
	{
		return new NcursesDisplay;
	}
}