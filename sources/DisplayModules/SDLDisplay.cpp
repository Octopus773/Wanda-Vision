//
// Created by cbihan on 3/22/21.
//

#include "SDLDisplay.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "Events/ClickEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/CloseEvent.hpp"

namespace Arcade
{

	bool SDLDisplay::init()
	{
		if( SDL_Init(SDL_INIT_VIDEO) < 0 )
		{
			std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
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

	std::list<Event> Arcade::SDLDisplay::pullEvents()
	{
		SDL_Event e;
		std::list<Event> events;
		Event event;
		while(SDL_PollEvent(&e) != 0)
		{
			switch (e.type) {
			case SDL_QUIT:
				event = Events::CloseEvent();
				break;
			case SDL_KEYDOWN:
				event = this->createKeyEvent(e.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				// TODO give % for x and y
				event = this->createClickEvent(e.button.x, e.button.y, e.button.button);
				break;
			default:
				continue;
			}
			events.push_back(event);
		}
		return events;
	}

	void SDLDisplay::drawLine(GameObjects::LineObject obj)
	{
		SDL_SetRenderDrawColor(this->_windowRenderer, 0x00, 0x00, 0xFF, 0xFF);
		this->setRendererColor(obj.color);
		SDL_RenderDrawLine(this->_windowRenderer,
					       obj.x * this->_windowWidth,
						   obj.y * this->_windowHeight,
						   obj.endX * this->_windowWidth,
						   obj.endY * this->_windowHeight
						   );
	}

	void SDLDisplay::drawRectangle(GameObjects::RectangleObject obj)
	{
		SDL_Rect fillRect = { obj.x * this->_windowWidth,
							obj.y * this->_windowHeight,
							obj.endX * this->_windowWidth,
							obj.endY * this->_windowHeight
		};
		this->setRendererColor(obj.color);
		SDL_RenderFillRect(this->_windowRenderer, &fillRect);
	}

	void SDLDisplay::drawCircle(GameObjects::CircleObject obj)
	{
		std::cerr << "Circle rendering isn't yet supported with SDL2 display module" << std::endl;
	}

	void SDLDisplay::drawSprite(GameObjects::SpriteObject obj)
	{
		//Put your own bmp image here
		SDL_Surface *bmpSurf = SDL_LoadBMP("x.bmp");
		SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(this->_windowRenderer, bmpSurf);
		SDL_FreeSurface(bmpSurf);

		//Make a target texture to render too
		SDL_Texture *texTarget = SDL_CreateTexture(this->_windowRenderer, SDL_PIXELFORMAT_RGBA8888,
												   SDL_TEXTUREACCESS_TARGET, this->_windowWidth, this->_windowHeight);

		//Now render to the texture
		SDL_SetRenderTarget(this->_windowRenderer, texTarget);
		SDL_RenderClear(this->_windowRenderer);
		SDL_RenderCopy(this->_windowRenderer, bmpTex, NULL, NULL);
		//Detach the texture
		SDL_SetRenderTarget(this->_windowRenderer, NULL);

		//Now render the texture target to our screen, but upside down
		SDL_RenderClear(this->_windowRenderer);
		SDL_RenderCopyEx(this->_windowRenderer, texTarget, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
	}

	void SDLDisplay::refresh() const
	{
		SDL_RenderPresent(this->_windowRenderer);
	}

	Events::KeyEvent SDLDisplay::createKeyEvent(unsigned int key)
	{
		Events::KeyEvent e;

		e.key = key;
		return e;
	}

	Events::ClickEvent SDLDisplay::createClickEvent(unsigned int x, unsigned int y, unsigned int id)
	{
		Events::ClickEvent e;

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
}