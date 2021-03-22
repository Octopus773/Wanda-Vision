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
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}
		this->window = SDL_CreateWindow(this->windowTitle.c_str(),
										  SDL_WINDOWPOS_UNDEFINED,
										  SDL_WINDOWPOS_UNDEFINED,
										  this->windowWidth,
										  this->windowHeight,
										  SDL_WINDOW_SHOWN);
		if(window == nullptr)
		{
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		return true;
	}

	bool SDLDisplay::close()
	{
		return false;
	}

	bool SDLDisplay::shouldClose()
	{
		return false;
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

	}
}