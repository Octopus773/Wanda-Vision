//
// Created by cbihan on 3/22/21.
//

#include "SDLDisplay.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Common/Events/MouseClickEvent.hpp"
#include "Common/Events/KeyBoardEvent.hpp"
#include "Common/Events/Event.hpp"
#include "Common/ModInfo.hpp"

namespace Arcade
{

	bool SDLDisplay::init()
	{
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}
		this->_window = SDL_CreateWindow(this->_windowTitle.c_str(),
						 SDL_WINDOWPOS_UNDEFINED,
						 SDL_WINDOWPOS_UNDEFINED,
						 this->_windowWidth,
						 this->_windowHeight,
						 SDL_WINDOW_SHOWN);
		if(this->_window == nullptr)
		{
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}
		this->_windowRenderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
		if(this->_windowRenderer == nullptr)
		{
			std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
		this->_shouldClose = false;
		return true;
	}

	bool SDLDisplay::close()

	{
		for (const auto &pair : this->_loadedResources)
			SDL_DestroyTexture(pair.second);
		this->_loadedResources.clear();
		SDL_DestroyRenderer(this->_windowRenderer);
		this->_windowRenderer = nullptr;
		SDL_DestroyWindow(this->_window);
		this->_window = nullptr;
		SDL_Quit();
		this->_shouldClose = true;
		return true;
	}

	bool SDLDisplay::shouldClose()
	{
		return this->_shouldClose;
	}

	std::list<std::unique_ptr<Event>> SDLDisplay::pullEvents()
	{
		SDL_Event e;
		std::list<std::unique_ptr<Event>> events;
		Event event;
		std::unique_ptr<Event> eventList;

		while(SDL_PollEvent(&e) != 0)
		{
			switch (e.type) {
			case SDL_QUIT:
				eventList = std::make_unique<Event>(event);
				break;
			case SDL_KEYDOWN:
				eventList = std::make_unique<Event>(createKeyEvent(getStdKey(e.key.keysym.sym), Event::Type::KeyDown));
				break;
			case SDL_KEYUP:
				eventList = std::make_unique<Event>(createKeyEvent(getStdKey(e.key.keysym.sym), Event::Type::KeyUp));
				break;
			case SDL_MOUSEBUTTONDOWN:
				eventList = std::make_unique<Event>(createClickEvent((e.button.x * 100) / this->_windowWidth,
																	 (e.button.y * 100) / this->_windowHeight,
																	 getStdClickType(e.button.button), Event::KeyDown));
				break;
			case SDL_MOUSEBUTTONUP:
				eventList = std::make_unique<Event>(createClickEvent((e.button.x * 100) / this->_windowWidth,
																	 (e.button.y * 100) / this->_windowHeight,
																	 getStdClickType(e.button.button), Event::KeyUp));
				break;
			case SDL_MOUSEMOTION:
				eventList = std::make_unique<Event>(createMoveEvent((e.button.x * 100) / this->_windowWidth,
																	 (e.button.y * 100) / this->_windowHeight));
				break;
			default:
				event.type = Event::Type::Unknown;
				eventList = std::make_unique<Event>(event);
				break;
			}
			events.emplace_back(std::move(eventList));
		}
		return events;
	}

	bool SDLDisplay::draw(Drawables::Line &obj)
	{
		SDL_SetRenderDrawColor(this->_windowRenderer, 0x00, 0x00, 0xFF, 0xFF);
		this->setRendererColor(obj.color);
		SDL_RenderDrawLine(this->_windowRenderer,
				   obj.x * this->_windowWidth,
				   obj.y * this->_windowHeight,
				   obj.endX * this->_windowWidth,
				   obj.endY * this->_windowHeight
						   );
		return true;
	}

	bool SDLDisplay::draw(Drawables::Rectangle &obj)
	{
		SDL_Rect fillRect = {obj.x * this->_windowWidth,
				     obj.y * this->_windowHeight,
				     obj.endX * this->_windowWidth,
				     obj.endY * this->_windowHeight};
		this->setRendererColor(obj.color);
		SDL_RenderFillRect(this->_windowRenderer, &fillRect);
		return true;
	}

	bool SDLDisplay::draw(Drawables::Circle &)
	{
		return false;
	}

	bool SDLDisplay::draw(Drawables::Text &obj)
	{
		return false;
	}

	bool SDLDisplay::draw(Drawables::Sprite &obj)
	{
		int w;
		int h;
		std::string path = obj.path;
		SDL_Rect rect;
		SDL_Texture *img;

		if (this->_loadedResources.find(path) == this->_loadedResources.end()) {
			return false;
		}
		if (this->_loadedResources[path].first != "image") {
			return false;
		}
		img = static_cast<SDL_Texture *>(this->_loadedResources[path].second);
		SDL_QueryTexture(img, nullptr, nullptr, &w, &h);
		rect.x = obj.x - (w / 2);
		rect.y = obj.y - (h / 2);
		rect.w = static_cast<int>(obj.sizeX);
		rect.h = static_cast<int>(obj.sizeY);
		SDL_RenderCopyEx(this->_windowRenderer, img, nullptr, &rect, obj.rotation, nullptr, SDL_FLIP_NONE);
		return true;
	}

	bool SDLDisplay::refresh()
	{
		SDL_RenderPresent(this->_windowRenderer);
		SDL_RenderClear(this->_windowRenderer);
		return true;
	}

	Events::KeyboardEvent SDLDisplay::createKeyEvent(Events::KeyboardEvent::KeyCode key, Event::Type keyType)
	{
		Events::KeyboardEvent e;

		e.key = key;
		e.type = keyType;
		return e;
	}

	Events::MouseClickEvent
	SDLDisplay::createClickEvent(unsigned int x, unsigned int y, Events::MouseClickEvent::MouseButton button, Event::Type clickType)
	{
		Events::MouseClickEvent e;

		e.x = x;
		e.y = y;
		e.button = button;
		e.type = clickType;
		return e;
	}

	void SDLDisplay::setRendererColor(unsigned int color)
	{
		SDL_SetRenderDrawColor(this->_windowRenderer,
				      (color & (0xFF << 24)) >> 24,
				      (color & (0xFF << 16)) >> 16,
				      (color & (0xFF << 8)) >> 8,
				       color & 0xFF);
	}

	ModInfo::Modtype SDLDisplay::getType() const
	{
		return ModInfo::GRAPHIC;
	}

	bool SDLDisplay::load(const std::string &path)
	{
		SDL_Texture *img;
		if (this->_loadedResources.find(path) == this->_loadedResources.end()) {
			img = IMG_LoadTexture(this->_windowRenderer, path.c_str());
			if (!img) {
				return false;
			}
			// TODO in future multiple types of textures or ttf files will be added
			this->_loadedResources[path] = std::make_pair("image", img);
			return true;
		}
		return false;
	}

	void SDLDisplay::unload(const std::string &path)
	{
		if (this->_loadedResources.find(path) != this->_loadedResources.end()) {
			this->destroyResource(this->_loadedResources[path]);
			this->_loadedResources.erase(path);
		}
	}

	void SDLDisplay::unloadAll()
	{
		for (const auto &pair : this->_loadedResources)
			this->destroyResource(pair.second);
		this->_loadedResources.clear();
	}

	Events::KeyboardEvent::KeyCode SDLDisplay::getStdKey(unsigned int key)
	{
		switch (key) {
		case SDL_KeyCode::SDLK_a: return Events::KeyboardEvent::KEY_A;
		case SDL_KeyCode::SDLK_b: return Events::KeyboardEvent::KEY_B;
		case SDL_KeyCode::SDLK_c: return Events::KeyboardEvent::KEY_C;
		case SDL_KeyCode::SDLK_d: return Events::KeyboardEvent::KEY_D;
		case SDL_KeyCode::SDLK_e: return Events::KeyboardEvent::KEY_E;
		case SDL_KeyCode::SDLK_f: return Events::KeyboardEvent::KEY_F;
		case SDL_KeyCode::SDLK_g: return Events::KeyboardEvent::KEY_G;
		case SDL_KeyCode::SDLK_h: return Events::KeyboardEvent::KEY_H;
		case SDL_KeyCode::SDLK_i: return Events::KeyboardEvent::KEY_I;
		case SDL_KeyCode::SDLK_j: return Events::KeyboardEvent::KEY_J;
		case SDL_KeyCode::SDLK_k: return Events::KeyboardEvent::KEY_K;
		case SDL_KeyCode::SDLK_l: return Events::KeyboardEvent::KEY_L;
		case SDL_KeyCode::SDLK_m: return Events::KeyboardEvent::KEY_M;
		case SDL_KeyCode::SDLK_n: return Events::KeyboardEvent::KEY_N;
		case SDL_KeyCode::SDLK_o: return Events::KeyboardEvent::KEY_O;
		case SDL_KeyCode::SDLK_p: return Events::KeyboardEvent::KEY_P;
		case SDL_KeyCode::SDLK_q: return Events::KeyboardEvent::KEY_Q;
		case SDL_KeyCode::SDLK_r: return Events::KeyboardEvent::KEY_R;
		case SDL_KeyCode::SDLK_s: return Events::KeyboardEvent::KEY_S;
		case SDL_KeyCode::SDLK_t: return Events::KeyboardEvent::KEY_T;
		case SDL_KeyCode::SDLK_u: return Events::KeyboardEvent::KEY_U;
		case SDL_KeyCode::SDLK_v: return Events::KeyboardEvent::KEY_V;
		case SDL_KeyCode::SDLK_w: return Events::KeyboardEvent::KEY_W;
		case SDL_KeyCode::SDLK_x: return Events::KeyboardEvent::KEY_X;
		case SDL_KeyCode::SDLK_y: return Events::KeyboardEvent::KEY_Y;
		case SDL_KeyCode::SDLK_z: return Events::KeyboardEvent::KEY_Z;
		case SDL_KeyCode::SDLK_0: return Events::KeyboardEvent::KEY_0;
		case SDL_KeyCode::SDLK_1: return Events::KeyboardEvent::KEY_1;
		case SDL_KeyCode::SDLK_2: return Events::KeyboardEvent::KEY_2;
		case SDL_KeyCode::SDLK_3: return Events::KeyboardEvent::KEY_3;
		case SDL_KeyCode::SDLK_4: return Events::KeyboardEvent::KEY_4;
		case SDL_KeyCode::SDLK_5: return Events::KeyboardEvent::KEY_5;
		case SDL_KeyCode::SDLK_6: return Events::KeyboardEvent::KEY_6;
		case SDL_KeyCode::SDLK_7: return Events::KeyboardEvent::KEY_7;
		case SDL_KeyCode::SDLK_8: return Events::KeyboardEvent::KEY_8;
		case SDL_KeyCode::SDLK_9: return Events::KeyboardEvent::KEY_9;
		case SDL_KeyCode::SDLK_KP_0: return Events::KeyboardEvent::NUMPAD_0;
		case SDL_KeyCode::SDLK_KP_1: return Events::KeyboardEvent::NUMPAD_1;
		case SDL_KeyCode::SDLK_KP_2: return Events::KeyboardEvent::NUMPAD_2;
		case SDL_KeyCode::SDLK_KP_3: return Events::KeyboardEvent::NUMPAD_3;
		case SDL_KeyCode::SDLK_KP_4: return Events::KeyboardEvent::NUMPAD_4;
		case SDL_KeyCode::SDLK_KP_5: return Events::KeyboardEvent::NUMPAD_5;
		case SDL_KeyCode::SDLK_KP_6: return Events::KeyboardEvent::NUMPAD_6;
		case SDL_KeyCode::SDLK_KP_7: return Events::KeyboardEvent::NUMPAD_7;
		case SDL_KeyCode::SDLK_KP_8: return Events::KeyboardEvent::NUMPAD_8;
		case SDL_KeyCode::SDLK_KP_9: return Events::KeyboardEvent::NUMPAD_9;
		case SDL_KeyCode::SDLK_BACKSPACE: return Events::KeyboardEvent::BACKSPACE;
		case SDL_KeyCode::SDLK_TAB:
		case SDL_KeyCode::SDLK_KP_TAB: return Events::KeyboardEvent::TAB;
		case SDL_KeyCode::SDLK_KP_ENTER: return Events::KeyboardEvent::ENTER;
		case SDL_KeyCode::SDLK_LSHIFT:
		case SDL_KeyCode::SDLK_RSHIFT: return Events::KeyboardEvent::SHIFT;
		case SDL_KeyCode::SDLK_RCTRL:
		case SDL_KeyCode::SDLK_LCTRL: return Events::KeyboardEvent::CTRL;
		case SDL_KeyCode::SDLK_RALT:
		case SDL_KeyCode::SDLK_LALT: return Events::KeyboardEvent::ALT;
		case SDL_KeyCode::SDLK_PAUSE: return Events::KeyboardEvent::PAUSE;
		case SDL_KeyCode::SDLK_CAPSLOCK: return Events::KeyboardEvent::CAPS_LOCK;
		case SDL_KeyCode::SDLK_ESCAPE: return Events::KeyboardEvent::ESCAPE;
		case SDL_KeyCode::SDLK_SPACE:
		case SDL_KeyCode::SDLK_KP_SPACE: return Events::KeyboardEvent::SPACE;
		case SDL_KeyCode::SDLK_PAGEUP: return Events::KeyboardEvent::PAGE_UP;
		case SDL_KeyCode::SDLK_PAGEDOWN: return Events::KeyboardEvent::PAGE_DOWN;
		case SDL_KeyCode::SDLK_END: return Events::KeyboardEvent::END;
		case SDL_KeyCode::SDLK_AC_HOME:
		case SDL_KeyCode::SDLK_HOME: return Events::KeyboardEvent::HOME;
		case SDL_KeyCode::SDLK_LEFT: return Events::KeyboardEvent::LEFT_ARROW;
		case SDL_KeyCode::SDLK_UP: return Events::KeyboardEvent::UP_ARROW;
		case SDL_KeyCode::SDLK_RIGHT: return Events::KeyboardEvent::RIGHT_ARROW;
		case SDL_KeyCode::SDLK_DOWN: return Events::KeyboardEvent::DOWN_ARROW;
		case SDL_KeyCode::SDLK_INSERT: return Events::KeyboardEvent::INSERT;
		case SDL_KeyCode::SDLK_DELETE: return Events::KeyboardEvent::DELETE;
		case SDL_KeyCode::SDLK_SELECT: return Events::KeyboardEvent::SELECT;
		case SDL_KeyCode::SDLK_KP_MULTIPLY:
		case SDL_KeyCode::SDLK_KP_MEMMULTIPLY: return Events::KeyboardEvent::MULTIPLY;
		case SDL_KeyCode::SDLK_KP_MEMADD: return Events::KeyboardEvent::ADD;
		case SDL_KeyCode::SDLK_KP_MEMSUBTRACT: return Events::KeyboardEvent::SUBTRACT;
		case SDL_KeyCode::SDLK_KP_DECIMAL: return Events::KeyboardEvent::DECIMAL;
		case SDL_KeyCode::SDLK_KP_DIVIDE:
		case SDL_KeyCode::SDLK_KP_MEMDIVIDE: return Events::KeyboardEvent::DIVIDE;
		case SDL_KeyCode::SDLK_F1: return Events::KeyboardEvent::F1;
		case SDL_KeyCode::SDLK_F2: return Events::KeyboardEvent::F2;
		case SDL_KeyCode::SDLK_F3: return Events::KeyboardEvent::F3;
		case SDL_KeyCode::SDLK_F4: return Events::KeyboardEvent::F4;
		case SDL_KeyCode::SDLK_F5: return Events::KeyboardEvent::F5;
		case SDL_KeyCode::SDLK_F6: return Events::KeyboardEvent::F6;
		case SDL_KeyCode::SDLK_F7: return Events::KeyboardEvent::F7;
		case SDL_KeyCode::SDLK_F8: return Events::KeyboardEvent::F8;
		case SDL_KeyCode::SDLK_F9: return Events::KeyboardEvent::F9;
		case SDL_KeyCode::SDLK_F10: return Events::KeyboardEvent::F10;
		case SDL_KeyCode::SDLK_F11: return Events::KeyboardEvent::F11;
		case SDL_KeyCode::SDLK_F12: return Events::KeyboardEvent::F12;
		case SDL_KeyCode::SDLK_NUMLOCKCLEAR: return Events::KeyboardEvent::NUM_LOCK;
		case SDL_KeyCode::SDLK_SCROLLLOCK: return Events::KeyboardEvent::SCROLL_LOCK;
		case SDL_KeyCode::SDLK_SEMICOLON: return Events::KeyboardEvent::SEMICOLON;
		case SDL_KeyCode::SDLK_EQUALS:
		case SDL_KeyCode::SDLK_KP_EQUALSAS400:
		case SDL_KeyCode::SDLK_KP_EQUALS: return Events::KeyboardEvent::EQUALS;
		case SDL_KeyCode::SDLK_COMMA:
		case SDL_KeyCode::SDLK_KP_COMMA: return Events::KeyboardEvent::COMMA;
		case SDL_KeyCode::SDLK_KP_MINUS:
		case SDL_KeyCode::SDLK_MINUS: return Events::KeyboardEvent::DASH;
		case SDL_KeyCode::SDLK_PERIOD:
		case SDL_KeyCode::SDLK_KP_PERIOD: return Events::KeyboardEvent::PERIOD;
		case SDL_KeyCode::SDLK_SLASH: return Events::KeyboardEvent::FORWARD_SLASH;
		case SDL_KeyCode::SDLK_BACKSLASH: return Events::KeyboardEvent::BACK_SLASH;
		case SDL_KeyCode::SDLK_BACKQUOTE: return Events::KeyboardEvent::GRAVE_ACCENT;
		case SDL_KeyCode::SDLK_LEFTBRACKET: return Events::KeyboardEvent::OPEN_BRACKET;
		case SDL_KeyCode::SDLK_RIGHTBRACKET: return Events::KeyboardEvent::CLOSE_BRACKET;
		case SDL_KeyCode::SDLK_QUOTE: return Events::KeyboardEvent::SINGLE_QUOTE;
		case SDL_KeyCode::SDLK_RGUI: return Events::KeyboardEvent::RIGHT_META;
		case SDL_KeyCode::SDLK_LGUI: return Events::KeyboardEvent::LEFT_META;
		default: return Events::KeyboardEvent::UNDEFINED;
		}
	}

	Events::MouseMoveEvent SDLDisplay::createMoveEvent(unsigned int x, unsigned int y)
	{
		Events::MouseMoveEvent e;

		e.x = x;
		e.y = y;
		e.type = Event::Type::MouseMove;
		return e;
	}

	Events::MouseClickEvent::MouseButton SDLDisplay::getStdClickType(uint8_t type)
	{
		switch (type) {
		case SDL_BUTTON_LEFT: return Events::MouseClickEvent::MouseButton::LEFT;
		case SDL_BUTTON_MIDDLE: return Events::MouseClickEvent::MouseButton::MIDDLE;
		case SDL_BUTTON_RIGHT: return Events::MouseClickEvent::MouseButton::RIGHT;
		case SDL_BUTTON_X1: return Events::MouseClickEvent::MouseButton::XBUTTON1;
		case SDL_BUTTON_X2: return Events::MouseClickEvent::MouseButton::XBUTTON2;
		default: return Events::MouseClickEvent::MouseButton::UNDEFINED;
		}
	}

	void SDLDisplay::destroyResource(const std::pair<std::string, void *> &resource)
	{
		if (resource.first == "image") {
			SDL_DestroyTexture(static_cast<SDL_Texture *>(resource.second));
		}
	}

	extern "C" ModInfo getHeader()
	{
		ModInfo m;

		m.magicNumber = MagicNumber;
		m.name = "SDL2";
		m.type = ModInfo::Modtype::GRAPHIC;
		return m;
	}

	extern "C" Arcade::IModule *getModule()
	{
		return new SDLDisplay;
	}
}