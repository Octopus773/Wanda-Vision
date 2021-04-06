//
// Created by cbihan on 4/6/21.
//

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <any>
#include <variant>
#include "Common/IDisplayModule.hpp"
#include "Common/Events/MouseClickEvent.hpp"
#include "Common/Events/MouseMoveEvent.hpp"
#include "Common/Events/KeyBoardEvent.hpp"
#include "Common/Events/Event.hpp"

namespace Arcade
{
	//! @brief Implementation of the SDL Graphic Library
	class SFMLDisplay : public IDisplayModule
	{
	private:
		struct _InternalWindow {
			//! @brief The internal window for the bestfit (resize)
			unsigned int _size;
			//! @brief The horizontal offset
			unsigned offsetX;
			//! @brief The vertical offset
			unsigned offsetY;
		};

		//! @brief A game resource
		struct TrashResource {
			//! @brief The type of this resource used to known witch member is initialised
			std::string type;
			//! @brief A Texture
			sf::Texture t;
			//! @brief A font
			sf::Font f;
			//! @brief A Music
			sf::Music m;
		};

		std::variant<sf::Texture, sf::Font> typedef Resource;

		//! @brief The main window
		sf::RenderWindow _mainWindow;
		//! @brief The window title
		std::string _windowTitle;
		//! @brief A list of the keys that are currently hold
		//! @info keys are inserted in the list when an event keyDown as occurred and pop out when a keyUp occurred
		std::vector<Events::KeyboardEvent::KeyCode> _keysHolded;
		//! @brief If the Display should close
		bool _shouldClose = false;
		//! @brief A list of all the resources that are loaded and cached and then not needed to open again
		//! @info the pair is holding the type of the resource type and the resource
		//! @details saving string for the path (used to check if the texture is already loaded) and the Texture ptr
		std::map<std::string, std::pair<std::string, Resource>> _loadedResources;
		//! @brief Music type resource
		static constexpr std::string_view resourceMusicType = "music";
		//! @brief Font type resource
		static constexpr std::string_view resourceFontType = "font";
		//! @brief Sprite type resource
		static constexpr std::string_view resourceSpriteType = "sprite";

		//! @brief Binding of a constructor for KeyEvent struct
		//! @param key Value of key attribute of struct Events::KeyEvent
		//! @param keyType The type of the key registered (Up, Down or Hold)
		//! @return A KeyEvent struct with it's values correctly filled
		static Events::KeyboardEvent createKeyEvent(Events::KeyboardEvent::KeyCode key, Event::Type keyType);
		//! @brief Binding of a constructor for ClickEvent struct
		//! @param x The x position (in percentage)
		//! @param y The y position (in percentage)
		//! @param id The ID of this click.
		//! @param clickType The type of the click registered (Up, Down or Hold)
		//! @return A ClickEvent struct with it's values correctly filled
		static Events::MouseClickEvent
		createClickEvent(unsigned int x, unsigned int y, Events::MouseClickEvent::MouseButton button, Event::Type clickType);
		//! @brief Binding of a constructor for MoveEvent struct
		//! @param x The x position (in percentage)
		//! @param y The y position (in percentage)
		//! @return A MoveEvent struct with it's values correctly filled
		static Events::MouseMoveEvent createMoveEvent(unsigned int x, unsigned int y);
		//! @brief Allows to get the standard KeyCode for a key
		//! @param key The key given by the SDL2 library
		//! @return A a value for the key in the standard enum KeyCode
		//! @info If no equivalence found the value KeyCode::UNDEFINED is returned
		static Events::KeyboardEvent::KeyCode getStdKey(unsigned int key);
		//! @brief Allows to get the standard Click type for a click
		//! @param type The type of click given by the SDL2 library
		//! @return A a value for the click type in the standard enum Type of MouseClickEvent
		//! @info If no equivalence found the value MouseButton::UNDEFINED is returned
		static Events::MouseClickEvent::MouseButton getStdClickType(int type);
		//! @brief Allocate the resource given as param
		//! @param type The type of the resource
		//! @param path The location of the resource file
		//! @return A pointer to the resource or nullptr if a problem occurred
		Resource createResource(const std::string &type, const std::string &path);
		//! @brief Free the resource given as param
		//! @param resource the pair is holding the type of the resource type and the resource
		//! @info Only used if additional steps are required to delete correctly a resource
		void destroyResource(const std::pair<std::string, Resource> &resource);
	public:
		//! @brief Default constructor
		//! @warning In order to properly use this class you must call the init member function
		SFMLDisplay() = default;
		//! @brief Default copy constructor.
		//! @warning You must call the close member function before the destructor if you called the init member function
		~SFMLDisplay() override =  default;
		//! @brief Default copy constructor.
		SFMLDisplay(const SFMLDisplay &) = default;
		//! @brief Default  assignment operator
		SFMLDisplay &operator=(const SFMLDisplay &) = default;

		//! @brief Initialize this library. (Create windows & so on)
		//! @return True if the initialization was successful. False otherwise.
		bool init() override;

		//! @brief Allow to say to the library to shutdown and free it's content
		//! @return True if the shutdown was successful. False otherwise.
		bool close() override;

		//! @brief Should this module be closed?
		//! @return True if this module should be closed. False otherwise.
		bool shouldClose() override;

		//! @brief Pull events (Keys, Clicks, Closes...)
		//! @return The list of events that occured.
		std::list<std::unique_ptr<Event>> pullEvents() override;

		//! @brief Draw a line.
		//! @param obj The line to draw.
		//! @return True if the text could be drawned. False otherwise.
		bool draw(Drawables::Line &obj) override;

		//! @brief Draw a rectangle.
		//! @param obj The rectangle to draw.
		//! @return True if the draw was successful. False otherwise.
		bool draw(Drawables::Rectangle &obj) override;

		//! @brief Draw a circle.
		//! @param obj The circle to draw.
		//! @return True if the draw was successful. False otherwise.
		bool draw(Drawables::Circle &obj) override;

		//! @brief Draw a sprite.
		//! @param obj The sprite to draw.
		//! @return True if the draw was successful. False otherwise.
		bool draw(Drawables::Sprite &obj) override;

		//! @brief Draw a text.
		//! @param obj The text to draw.
		//! @return True if the draw was successful. False otherwise.
		bool draw(Drawables::Text &obj) override;

		//! @brief Refresh the screen, clear left-overs and draw requested objects.
		bool refresh() override;

		//! @brief Gives the library type
		//! @return A value of the enum ModType representing the type of the library
		ModInfo::Modtype getType() const override;

		//! @brief Load a sprite
		//! @param path The path to the texture to load
		//! @return Return true if the texture was successfully loaded. False otherwise
		bool load(const std::string &type, const std::string &path) override;

		//! @brief Unload a sprite
		//! @param path The path to the texture to load
		void unload(const std::string &type, const std::string &path) override;

		//! @brief Unload all sprites loaded.
		void unloadAll() override;

		//! @brief Play a sound
		void playSound(Sound &sound) override;
	};
}


