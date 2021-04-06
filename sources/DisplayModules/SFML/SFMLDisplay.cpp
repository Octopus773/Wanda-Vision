//
// Created by cbihan on 4/6/21.
//

#include "SFMLDisplay.hpp"
#include <SFML/Window.hpp>
#include "Common/Events/MouseClickEvent.hpp"
#include "Common/Events/KeyBoardEvent.hpp"
#include "Common/Events/Event.hpp"
#include "Exceptions/ResourceCreationFailure.hpp"

namespace Arcade
{
	bool SFMLDisplay::init()
	{
		this->_mainWindow.create(sf::VideoMode(800, 800), this->_windowTitle, sf::Style::Resize);

		this->_mainWindow.setKeyRepeatEnabled(false);
		return false;
	}

	bool SFMLDisplay::close()
	{
		this->_mainWindow.close();
		return false;
	}

	std::list<std::unique_ptr<Event>> SFMLDisplay::pullEvents()
	{
		sf::Event event;
		std::list<std::unique_ptr<Event>> events;
		std::unique_ptr<Event> eventTmp;
		Event evt;

		while (this->_mainWindow.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				evt.type = Event::Type::Close;
				eventTmp = std::make_unique<Event>(evt);
				break;
			case sf::Event::KeyPressed:
				eventTmp = std::make_unique<Events::KeyboardEvent>(createKeyEvent(getStdKey(event.key.code), Event::KeyDown));
				this->_keysHolded.push_back(getStdKey(event.key.code));
				break;
			case sf::Event::KeyReleased:
				eventTmp = std::make_unique<Events::KeyboardEvent>(createKeyEvent(getStdKey(event.key.code), Event::KeyUp));
				this->_keysHolded.erase(std::remove(this->_keysHolded.begin(), this->_keysHolded.end(), getStdKey(event.key.code)),
				                        this->_keysHolded.end());
				break;
			case sf::Event::MouseMoved:
				// TODO percentage clicks and handle only in internal window
				eventTmp = std::make_unique<Events::MouseMoveEvent>(createMoveEvent(event.mouseMove.x, event.mouseMove.y));
				break;
			case sf::Event::MouseButtonPressed:
				eventTmp = std::make_unique<Events::MouseClickEvent>(createClickEvent(event.mouseButton.x,
																		  event.mouseButton.y,
																		  getStdClickType(event.mouseButton.button),
																		  Event::KeyDown));
				break;
			case sf::Event::MouseButtonReleased:
				eventTmp = std::make_unique<Events::MouseClickEvent>(createClickEvent(event.mouseButton.x,
				                                                                      event.mouseButton.y,
				                                                                      getStdClickType(event.mouseButton.button),
				                                                                      Event::KeyUp));
				break;
			default:
				continue;
			}
			events.emplace_back(std::move(eventTmp));
		}
		for (const auto &i : this->_keysHolded) {
			events.emplace_back(std::make_unique<Events::KeyboardEvent>(createKeyEvent(i, Event::Type::KeyHold)));
		}
		return events;
	}

	Events::KeyboardEvent SFMLDisplay::createKeyEvent(Events::KeyboardEvent::KeyCode key, Event::Type keyType)
	{
		Events::KeyboardEvent e;

		e.key = key;
		e.type = keyType;
		return e;
	}

	Events::MouseClickEvent
	SFMLDisplay::createClickEvent(unsigned int x, unsigned int y, Events::MouseClickEvent::MouseButton button,
	                             Event::Type clickType)
	{
		Events::MouseClickEvent e;

		e.x = x;
		e.y = y;
		e.button = button;
		e.type = clickType;
		return e;
	}

	Events::MouseMoveEvent SFMLDisplay::createMoveEvent(unsigned int x, unsigned int y)
	{
		Events::MouseMoveEvent e;

		e.x = x;
		e.y = y;
		e.type = Event::Type::MouseMove;
		return e;
	}

	Events::KeyboardEvent::KeyCode SFMLDisplay::getStdKey(unsigned int key)
	{
		switch (key) {
		case sf::Keyboard::A: return Events::KeyboardEvent::KEY_A;
		case sf::Keyboard::B: return Events::KeyboardEvent::KEY_B;
		case sf::Keyboard::C: return Events::KeyboardEvent::KEY_C;
		case sf::Keyboard::D: return Events::KeyboardEvent::KEY_D;
		case sf::Keyboard::E: return Events::KeyboardEvent::KEY_E;
		case sf::Keyboard::F: return Events::KeyboardEvent::KEY_F;
		case sf::Keyboard::G: return Events::KeyboardEvent::KEY_G;
		case sf::Keyboard::H: return Events::KeyboardEvent::KEY_H;
		case sf::Keyboard::I: return Events::KeyboardEvent::KEY_I;
		case sf::Keyboard::J: return Events::KeyboardEvent::KEY_J;
		case sf::Keyboard::K: return Events::KeyboardEvent::KEY_K;
		case sf::Keyboard::L: return Events::KeyboardEvent::KEY_L;
		case sf::Keyboard::M: return Events::KeyboardEvent::KEY_M;
		case sf::Keyboard::N: return Events::KeyboardEvent::KEY_N;
		case sf::Keyboard::O: return Events::KeyboardEvent::KEY_O;
		case sf::Keyboard::P: return Events::KeyboardEvent::KEY_P;
		case sf::Keyboard::Q: return Events::KeyboardEvent::KEY_Q;
		case sf::Keyboard::R: return Events::KeyboardEvent::KEY_R;
		case sf::Keyboard::S: return Events::KeyboardEvent::KEY_S;
		case sf::Keyboard::T: return Events::KeyboardEvent::KEY_T;
		case sf::Keyboard::U: return Events::KeyboardEvent::KEY_U;
		case sf::Keyboard::V: return Events::KeyboardEvent::KEY_V;
		case sf::Keyboard::W: return Events::KeyboardEvent::KEY_W;
		case sf::Keyboard::X: return Events::KeyboardEvent::KEY_X;
		case sf::Keyboard::Y: return Events::KeyboardEvent::KEY_Y;
		case sf::Keyboard::Z: return Events::KeyboardEvent::KEY_Z;
		case sf::Keyboard::Num0 : return Events::KeyboardEvent::KEY_0;
		case sf::Keyboard::Num1: return Events::KeyboardEvent::KEY_1;
		case sf::Keyboard::Num2: return Events::KeyboardEvent::KEY_2;
		case sf::Keyboard::Num3: return Events::KeyboardEvent::KEY_3;
		case sf::Keyboard::Num4: return Events::KeyboardEvent::KEY_4;
		case sf::Keyboard::Num5: return Events::KeyboardEvent::KEY_5;
		case sf::Keyboard::Num6: return Events::KeyboardEvent::KEY_6;
		case sf::Keyboard::Num7: return Events::KeyboardEvent::KEY_7;
		case sf::Keyboard::Num8: return Events::KeyboardEvent::KEY_8;
		case sf::Keyboard::Num9: return Events::KeyboardEvent::KEY_9;
		case sf::Keyboard::Numpad0: return Events::KeyboardEvent::NUMPAD_0;
		case sf::Keyboard::Numpad1: return Events::KeyboardEvent::NUMPAD_1;
		case sf::Keyboard::Numpad2: return Events::KeyboardEvent::NUMPAD_2;
		case sf::Keyboard::Numpad3: return Events::KeyboardEvent::NUMPAD_3;
		case sf::Keyboard::Numpad4: return Events::KeyboardEvent::NUMPAD_4;
		case sf::Keyboard::Numpad5: return Events::KeyboardEvent::NUMPAD_5;
		case sf::Keyboard::Numpad6: return Events::KeyboardEvent::NUMPAD_6;
		case sf::Keyboard::Numpad7: return Events::KeyboardEvent::NUMPAD_7;
		case sf::Keyboard::Numpad8: return Events::KeyboardEvent::NUMPAD_8;
		case sf::Keyboard::Numpad9: return Events::KeyboardEvent::NUMPAD_9;
		case sf::Keyboard::BackSpace: return Events::KeyboardEvent::BACKSPACE;
		case sf::Keyboard::Tab: return Events::KeyboardEvent::TAB;
		case sf::Keyboard::Enter: return Events::KeyboardEvent::ENTER;
		case sf::Keyboard::LShift:
		case sf::Keyboard::RShift: return Events::KeyboardEvent::SHIFT;
		case sf::Keyboard::RControl:
		case sf::Keyboard::LControl: return Events::KeyboardEvent::CTRL;
		case sf::Keyboard::RAlt:
		case sf::Keyboard::LAlt: return Events::KeyboardEvent::ALT;
		case sf::Keyboard::Pause: return Events::KeyboardEvent::PAUSE;
		case sf::Keyboard::Escape: return Events::KeyboardEvent::ESCAPE;
		case sf::Keyboard::Space: return Events::KeyboardEvent::SPACE;
		case sf::Keyboard::PageUp: return Events::KeyboardEvent::PAGE_UP;
		case sf::Keyboard::PageDown: return Events::KeyboardEvent::PAGE_DOWN;
		case sf::Keyboard::End: return Events::KeyboardEvent::END;
		case sf::Keyboard::Home: return Events::KeyboardEvent::HOME;
		case sf::Keyboard::Left: return Events::KeyboardEvent::LEFT_ARROW;
		case sf::Keyboard::Up: return Events::KeyboardEvent::UP_ARROW;
		case sf::Keyboard::Right: return Events::KeyboardEvent::RIGHT_ARROW;
		case sf::Keyboard::Down: return Events::KeyboardEvent::DOWN_ARROW;
		case sf::Keyboard::Insert: return Events::KeyboardEvent::INSERT;
		case sf::Keyboard::Delete: return Events::KeyboardEvent::DELETE;
		case sf::Keyboard::Multiply: return Events::KeyboardEvent::MULTIPLY;
		case sf::Keyboard::Add: return Events::KeyboardEvent::ADD;
		case sf::Keyboard::Subtract: return Events::KeyboardEvent::SUBTRACT;
		case sf::Keyboard::Divide: return Events::KeyboardEvent::DIVIDE;
		case sf::Keyboard::F1: return Events::KeyboardEvent::F1;
		case sf::Keyboard::F2: return Events::KeyboardEvent::F2;
		case sf::Keyboard::F3: return Events::KeyboardEvent::F3;
		case sf::Keyboard::F4: return Events::KeyboardEvent::F4;
		case sf::Keyboard::F5: return Events::KeyboardEvent::F5;
		case sf::Keyboard::F6: return Events::KeyboardEvent::F6;
		case sf::Keyboard::F7: return Events::KeyboardEvent::F7;
		case sf::Keyboard::F8: return Events::KeyboardEvent::F8;
		case sf::Keyboard::F9: return Events::KeyboardEvent::F9;
		case sf::Keyboard::F10: return Events::KeyboardEvent::F10;
		case sf::Keyboard::F11: return Events::KeyboardEvent::F11;
		case sf::Keyboard::F12: return Events::KeyboardEvent::F12;
		case sf::Keyboard::SemiColon: return Events::KeyboardEvent::SEMICOLON;
		case sf::Keyboard::Equal: return Events::KeyboardEvent::EQUALS;
		case sf::Keyboard::Comma: return Events::KeyboardEvent::COMMA;
		case sf::Keyboard::Dash: return Events::KeyboardEvent::DASH;
		case sf::Keyboard::Period: return Events::KeyboardEvent::PERIOD;
		case sf::Keyboard::Slash: return Events::KeyboardEvent::FORWARD_SLASH;
		case sf::Keyboard::BackSlash: return Events::KeyboardEvent::BACK_SLASH;
		case sf::Keyboard::LBracket: return Events::KeyboardEvent::OPEN_BRACKET;
		case sf::Keyboard::RBracket: return Events::KeyboardEvent::CLOSE_BRACKET;
		case sf::Keyboard::Quote: return Events::KeyboardEvent::SINGLE_QUOTE;
		case sf::Keyboard::LSystem: return Events::KeyboardEvent::RIGHT_META;
		case sf::Keyboard::RSystem: return Events::KeyboardEvent::LEFT_META;
		default: return Events::KeyboardEvent::UNDEFINED;
		}
	}

	Events::MouseClickEvent::MouseButton SFMLDisplay::getStdClickType(int type)
	{
		switch (type) {
		case sf::Mouse::Button::Left: return Events::MouseClickEvent::MouseButton::LEFT;
		case sf::Mouse::Button::Middle:	return Events::MouseClickEvent::MouseButton::MIDDLE;
		case sf::Mouse::Button::Right: return Events::MouseClickEvent::MouseButton::RIGHT;
		case sf::Mouse::Button::XButton1: return Events::MouseClickEvent::MouseButton::XBUTTON1;
		case sf::Mouse::Button::XButton2: return Events::MouseClickEvent::MouseButton::XBUTTON2;
		default: return Events::MouseClickEvent::MouseButton::UNDEFINED;
		}
	}

	bool SFMLDisplay::shouldClose()
	{
		return this->_shouldClose;
	}

	bool SFMLDisplay::refresh()
	{
		this->_mainWindow.display();
		this->_mainWindow.clear();
		return true;
	}

	ModInfo::Modtype SFMLDisplay::getType() const
	{
		return ModInfo::GRAPHIC;
	}

	std::variant<sf::Texture, sf::Font>
	SFMLDisplay::createResource(const std::string &type, const std::string &path)
	{
		sf::Texture t;
		sf::Font f;
		sf::Music m;

		if (type == resourceSpriteType) {
			if (!t.loadFromFile(path)) {
				throw ResourceCreationFailure("File error");
			}
			return t;
		} else if (type == resourceFontType) {
			if (!f.loadFromFile(path)) {
				throw ResourceCreationFailure("File error");
			}
			return f;
		} else if (type == resourceMusicType) {
			throw ResourceCreationFailure("Unsupported Music");
		} else {
			throw ResourceCreationFailure("Unknown type");
		}
	}

	bool SFMLDisplay::load(const std::string &type, const std::string &path)
	{
		if (this->_loadedResources.find(path) != this->_loadedResources.end()) {
			return false;
		}
		this->_loadedResources[path] = this->createResource(type, path);
		return false;
	}

	void SFMLDisplay::destroyResource(const std::pair<std::string, void *> &resource)
	{

	}

	extern "C" ModInfo getHeader()
	{
		ModInfo m;

		m.magicNumber = MagicNumber;
		m.name = "SFML";
		m.type = ModInfo::Modtype::GRAPHIC;
		return m;
	}

	extern "C" Arcade::IModule *getModule()
	{
		return new SFMLDisplay;
	}

	SFMLDisplay::Resource::Resource(const std::string &type, const std::string &path)
		: type(type)
	{
		if (type == resourceSpriteType) {
			if (!this->t.loadFromFile(path)) {
				throw ResourceCreationFailure("File error");
			}
		} else if (type == resourceFontType) {
			if (!this->f.loadFromFile(path)) {
				throw ResourceCreationFailure("File error");
			}
		} else if (type == resourceMusicType) {
			if (!this->m.openFromFile(path)) {
				throw ResourceCreationFailure("File error");
			}
			throw ResourceCreationFailure("Unsupported Music");
		} else {
			throw ResourceCreationFailure("Unknown type");
		}
	}
}