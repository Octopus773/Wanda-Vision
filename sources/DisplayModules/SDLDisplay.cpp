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
		for (const auto &pair : this->_loadedTextures)
			SDL_DestroyTexture(pair.second);
		this->_loadedTextures.clear();
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
		std::unique_ptr<Event> event;
		while(SDL_PollEvent(&e) != 0)
		{
			switch (e.type) {
			case SDL_QUIT:
				event = std::make_unique<Event>(Event());
				break;
			case SDL_KEYDOWN:
				// TODO make transition function to link SDL keysym to the correct keycode
				event = std::make_unique<Event>(createKeyEvent(static_cast<Events::KeyboardEvent::KeyCode>(e.key.keysym.sym)));
				break;
			case SDL_MOUSEBUTTONDOWN:
				event = std::make_unique<Event>(createClickEvent((e.button.x * 100) / this->_windowWidth,
										 (e.button.y * 100) / this->_windowHeight,
										  e.button.button));
				break;
			default:
				continue;
			}
			events.emplace_back(std::move(event));
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
		std::cerr << "Circles not implemented" << std::endl;
		return false;
	}

	bool SDLDisplay::draw(Drawables::Text &obj)
	{
		std::cerr << "Text not implemented" << std::endl;
		return false;
	}

	bool SDLDisplay::draw(Drawables::Sprite &obj)
	{
		int w;
		int h;
		std::string path = obj.path;
		SDL_Rect rect;
		SDL_Texture *img;

		if (this->_loadedTextures.find(path) == this->_loadedTextures.end()) {
			std::cerr << "Error resource isn't loaded: " << path << std::endl;
			return false;
		}
		img = this->_loadedTextures[path];
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

	Events::KeyboardEvent SDLDisplay::createKeyEvent(Events::KeyboardEvent::KeyCode key)
	{
		Events::KeyboardEvent e;

		e.key = key;
		return e;
	}

	Events::MouseClickEvent SDLDisplay::createClickEvent(unsigned int x, unsigned int y, unsigned int id)
	{
		Events::MouseClickEvent e;

		e.x = x;
		e.y = y;
		e.id = id;
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
		// TODO in future multiple types of textures will be added
		if (this->_loadedTextures.find(path) == this->_loadedTextures.end()) {
			img = IMG_LoadTexture(this->_windowRenderer, path.c_str());
			if (!img) {
				return false;
			}
			this->_loadedTextures[path] = img;
			return true;
		}
		return false;
	}

	void SDLDisplay::unload(const std::string &path)
	{
		// TODO be able to handle multiple types of resources
		if (this->_loadedTextures.find(path) != this->_loadedTextures.end()) {
			SDL_DestroyTexture(this->_loadedTextures[path]);
			this->_loadedTextures.erase(path);
		}
	}

	void SDLDisplay::unloadAll()
	{
		for (const auto &pair : this->_loadedTextures)
			SDL_DestroyTexture(pair.second);
		this->_loadedTextures.clear();
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
		// test ci
		return new SDLDisplay;
	}
}