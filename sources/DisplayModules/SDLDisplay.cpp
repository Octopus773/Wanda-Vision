//
// Created by cbihan on 3/22/21.
//

#include "SDLDisplay.hpp"
#include <SDL2/SDL.h>
#include <iostream>

namespace Arcade
{

	bool SDLDisplay::init()
	{
		if( SDL_Init(SDL_INIT_VIDEO) < 0 )
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
		this->_windowSurface = SDL_GetWindowSurface(this->_window);
		if(this->_windowSurface == nullptr)
		{
			std::cerr << "Window Surface could not be created!" << std::endl;
			return false;
		}
		this->_shouldClose = false;
		return true;
	}

	bool SDLDisplay::close()
	{
		SDL_FreeSurface(this->_windowSurface);
		this->_windowSurface = nullptr;
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

	std::list<Event> Arcade::SDLDisplay::pullEvents()
	{
		return std::list<Event>();
	}

	void SDLDisplay::drawLine(GameObjects::LineObject obj)
	{

	}

	void SDLDisplay::drawRectangle(GameObjects::RectangleObject obj)
	{

	}

	void SDLDisplay::drawCircle(GameObjects::CircleObject obj)
	{

	}

	void SDLDisplay::drawSprite(GameObjects::SpriteObject obj)
	{

	}

	void SDLDisplay::refresh() const
	{
		SDL_UpdateWindowSurface(this->_window);
	}
}