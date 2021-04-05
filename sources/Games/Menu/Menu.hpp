//
// Created by Zoe Roux on 2021-04-05.
//


#pragma once

#include "Core/Runner/Runner.hpp"
#include "Common/IGameModule.hpp"

namespace Arcade::Menu
{
	//! @brief A menu that allow the user to select a game and a display module.
	class Menu : public IGameModule
	{
	private:
		//! @brief Instance of the runner
		Core::Runner &_runner;

		//! @brief List of drawables
		std::vector<std::unique_ptr<Drawables::ADrawable>> _drawables = {};

		//! @brief List of resources
		std::vector<std::pair<std::string, std::string>> _resources = {};

		//! @brief List of sounds
		std::vector<Sound> _sounds = {};

		//! @brief Should the menu close?
		bool _shouldClose;
	public:
		//! @brief Initialize this library. (Create windows & so on)
		//! @return True if the initialization was successful. False otherwise.
		bool init() override;

		//! @brief Allow to say to the library to shutdown and free it's content
		//! @return True if the shutdown was successful. False otherwise.
		bool close() override;

		//! @brief Should this module be closed?
		//! @return True if this module should be closed. False otherwise.
		bool shouldClose() override;

		//! @brief Get the type of this module
		ModInfo::Modtype getType() const override;

		//! @brief Get resources to preload.
		//! @info Only called once.
		//! @return A vector of tupple of (type of resource, path of the resource).
		const std::vector<std::pair<std::string, std::string>> &getResources() const override;

		//! @brief Return a list of drawables to display.
		//! @return The list of objects
		const std::vector<std::unique_ptr<Drawables::ADrawable>> &getDrawables() override;

		//! @brief Return a list of sounds to make.
		//! @return The list of sounds
		const std::vector<Sound> &getSounds() override;

		//! @brief Advance the game of x seconds
		//! @param tick The number of ticks that occured since the last call.
		void addTicks(unsigned tick) override;

		//! @brief Restart the game.
		void restart() override;

		//! @brief Handle one event (A key press, a click, a close event...)
		//! @param event The event to handle.
		void handleEvent(Event &event) override;

		//! @brief Get the score (used for saving/displaying)
		unsigned long getScore() override;

		//! @brief Constructor
		explicit Menu(Core::Runner &runner);
		//! @brief Default copy constructor
		Menu(const Menu &) = default;
		//! @brief Default destructor
		~Menu() override = default;
		//! @brief Deleted assignment operator
		Menu &operator=(const Menu &) = delete;
	};
}
