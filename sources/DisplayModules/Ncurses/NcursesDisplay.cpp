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
		timeout(500);
		noecho();
//		start_color();
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
		return int(this->_width / 100. * x);
	}

	int NcursesDisplay::_getPosY(int y) const
	{
		return int(this->_height / 100. * y);
	}

	bool NcursesDisplay::draw(Drawables::Line &obj)
	{
		if (obj.y == obj.endY) {
			int length =  this->_getPosX(obj.endX) - this->_getPosX(obj.x);
			mvaddstr(this->_getPosY(obj.y), this->_getPosX(obj.x), ('+' + std::string(length - 1, '-') + '+').c_str());
			return true;
		}
		if (obj.x == obj.endX) {
			int x = this->_getPosX(obj.x);
			int i = this->_getPosY(obj.y);
			mvaddch(i, x, '+');
			for (i++; i < this->_getPosY(obj.endY); i++)
				mvaddch(i, x, '|');
			mvaddch(i, x, '+');
			return true;
		}
		return false;
	}

	bool NcursesDisplay::draw(Drawables::Rectangle &obj)
	{
		int width = this->_getPosX(obj.endX) - this->_getPosX(obj.x);
		mvaddstr(this->_getPosY(obj.y), this->_getPosX(obj.x), ('+' + std::string(width - 2, '-') + '+').c_str());
		for (int i = this->_getPosY(obj.y) + 1; i < this->_getPosY(obj.endY) - 1; i++)
			mvaddstr(i, this->_getPosX(obj.x), ('|' + std::string(width - 2, 'o') + '|').c_str());
		mvaddstr(this->_getPosY(obj.y), this->_getPosX(obj.x), ('+' + std::string(width - 2, '-') + '+').c_str());
		return true;
	}

	bool NcursesDisplay::draw(Drawables::Circle &obj)
	{
		return false;
	}

	bool NcursesDisplay::draw(Drawables::Text &obj)
	{
		mvaddstr(this->_getPosY(obj.y), this->_getPosX(obj.x), obj.text.c_str());
		return true;
	}

	bool NcursesDisplay::draw(Drawables::Sprite &obj)
	{
		return false;
	}

	bool NcursesDisplay::refresh()
	{
		::refresh();
		erase();
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