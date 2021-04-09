//
// Created by cbihan on 4/6/21.
//

#include "SFMLDisplay.hpp"
#include <SFML/Window.hpp>
#include "Common/Events/MouseClickEvent.hpp"
#include "Common/Events/KeyBoardEvent.hpp"
#include "Common/Events/Event.hpp"
#include "Exceptions/ResourceCreationFailure.hpp"
#include <iostream>

namespace Arcade
{
	bool SFMLDisplay::init()
	{
		this->_mainWindow.create(sf::VideoMode(1300, 700), this->_windowTitle, sf::Style::Default);

		this->_mainWindow.setKeyRepeatEnabled(false);
		this->updateInternalWindow();
		this->_shouldClose = false;
		this->_internalWindow.texture.create(this->_internalWindow.size, this->_internalWindow.size);
		return true;
	}

	bool SFMLDisplay::close()
	{
		this->unloadAll();
		this->_shouldClose = true;
		this->_mainWindow.close();
		return false;
	}

	std::list<std::unique_ptr<Event>> SFMLDisplay::pullEvents()
	{
		sf::Event event;
		std::list<std::unique_ptr<Event>> events;
		std::unique_ptr<Event> eventTmp;
		Event evt;
		sf::FloatRect visibleArea;

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
				if ((event.mouseMove.x < this->_internalWindow.offsetX || event.mouseMove.x > this->_internalWindow.offsetX + this->_internalWindow.size)
					|| (event.mouseMove.y < this->_internalWindow.offsetY || event.mouseMove.y > this->_internalWindow.offsetY + this->_internalWindow.size)) {
					continue;
				}
				eventTmp = std::make_unique<Events::MouseMoveEvent>(createMoveEvent(
					preciseCrossProduct(event.mouseMove.x - this->_internalWindow.offsetX, 100, this->_internalWindow.size),
					preciseCrossProduct(event.mouseMove.y - this->_internalWindow.offsetY, 100, this->_internalWindow.size)));
				break;
			case sf::Event::MouseButtonPressed:
				if ((event.mouseButton.x < this->_internalWindow.offsetX || event.mouseButton.x > this->_internalWindow.offsetX + this->_internalWindow.size)
				    || (event.mouseButton.y < this->_internalWindow.offsetY || event.mouseButton.y > this->_internalWindow.offsetY + this->_internalWindow.size)) {
					continue;
				}
				eventTmp = std::make_unique<Events::MouseClickEvent>(createClickEvent(
					preciseCrossProduct(event.mouseButton.x - this->_internalWindow.offsetX, 100, this->_internalWindow.size),
					preciseCrossProduct(event.mouseButton.y - this->_internalWindow.offsetY, 100, this->_internalWindow.size),
					getStdClickType(event.mouseButton.button),
					Event::KeyDown));
				break;
			case sf::Event::MouseButtonReleased:
				if ((event.mouseButton.x < this->_internalWindow.offsetX || event.mouseButton.x > this->_internalWindow.offsetX + this->_internalWindow.size)
				    || (event.mouseButton.y < this->_internalWindow.offsetY || event.mouseButton.y > this->_internalWindow.offsetY + this->_internalWindow.size)) {
					continue;
				}
				eventTmp = std::make_unique<Events::MouseClickEvent>(createClickEvent(
					preciseCrossProduct(event.mouseButton.x - this->_internalWindow.offsetX, 100, this->_internalWindow.size),
					preciseCrossProduct(event.mouseButton.y - this->_internalWindow.offsetY, 100, this->_internalWindow.size),
					getStdClickType(event.mouseButton.button),
					Event::KeyUp));
				break;
			case sf::Event::Resized:
				this->updateInternalWindow();
				// update the view to the new size of the window
				visibleArea.left = 0;
				visibleArea.top = 0;
				visibleArea.width = event.size.width;
				visibleArea.height = event.size.height;
				this->_mainWindow.setView(sf::View(visibleArea));
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
		sf::Vector2u screenSize = this->_mainWindow.getSize();
		sf::RectangleShape rect;
		sf::Sprite sprite;
		unsigned int widerLength = std::max(screenSize.x, screenSize.y);

		this->_internalWindow.texture.display();

		// Background sprite
		sprite.setTexture(this->_internalWindow.texture.getTexture(), true);
		sprite.setPosition(std::min(static_cast<double>(0), (static_cast<int>(this->_internalWindow.size) - static_cast<int>(screenSize.y)) / 2.),
                            std::min(static_cast<double>(0), (static_cast<int>(screenSize.x) - static_cast<int>(this->_internalWindow.size)) / 2.));
		sprite.scale(widerLength / static_cast<float>(this->_internalWindow.size),
		             widerLength / static_cast<float>(this->_internalWindow.size));
		sprite.setColor(sf::Color(100, 100, 100));
		this->_mainWindow.draw(sprite);

		// internal Window (the centered window)
		sprite.setColor(sf::Color(255, 255, 255));
		sprite.setScale(1, 1);
		sprite.setPosition(this->_internalWindow.offsetX, this->_internalWindow.offsetY);

		// green separator
		rect.setPosition(this->_internalWindow.offsetX - 5, this->_internalWindow.offsetY - 5);
		rect.setSize(sf::Vector2f(this->_internalWindow.size + 10, this->_internalWindow.size + 10));
		rect.setFillColor(sf::Color(0xFFFF00FF));
		this->_mainWindow.draw(rect);

		this->_mainWindow.draw(sprite);

		this->_mainWindow.display();

		this->_mainWindow.clear();
		this->_internalWindow.texture.clear();
		return true;
	}

	ModInfo::Modtype SFMLDisplay::getType() const
	{
		return ModInfo::GRAPHIC;
	}

	SFMLDisplay::Resource SFMLDisplay::createResource(const std::string &type, const std::string &path)
	{
		sf::Texture t;
		sf::Font f;

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
			throw ResourceCreationFailure("Music not supported");
		} else {
			throw ResourceCreationFailure("Unknown type");
		}
	}

	bool SFMLDisplay::load(const std::string &type, const std::string &path)
	{
		Resource resource;

		if (this->_loadedResources.find(path) != this->_loadedResources.end()) {
			return false;
		}
		try {
			resource = this->createResource(type, path);
		} catch (const ResourceCreationFailure &) {
			return false;
		}
		this->_loadedResources[path] = std::make_pair(type, resource);
		return true;
	}

	void SFMLDisplay::destroyResource(const std::pair<std::string, Resource> &)
	{
	}

	void SFMLDisplay::unload(const std::string &type, const std::string &path)
	{
		if (this->_loadedResources.find(path) == this->_loadedResources.end()) {
			return;
		}
		this->destroyResource(this->_loadedResources[path]);
		this->_loadedResources.erase(path);
	}

	void SFMLDisplay::unloadAll()
	{
		for(auto iter = this->_loadedResources.begin(); iter != this->_loadedResources.end(); ++iter)
		{
			this->unload(iter->first, iter->second.first);
		}
		this->_loadedResources.clear();
	}

	bool SFMLDisplay::draw(Drawables::Rectangle &obj)
	{
		sf::RectangleShape rect;

		rect.setSize(sf::Vector2f(preciseCrossProduct(obj.endX - obj.x, this->_internalWindow.size),
									preciseCrossProduct(obj.endY - obj.y, this->_internalWindow.size)));
		rect.setPosition(preciseCrossProduct(obj.x, this->_internalWindow.size),
				            preciseCrossProduct(obj.y, this->_internalWindow.size));
		rect.setFillColor(sf::Color(obj.color));
		this->_internalWindow.texture.draw(rect);
		return true;
	}

	bool SFMLDisplay::draw(Drawables::Line &obj)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(preciseCrossProduct(obj.x, this->_internalWindow.size),
						                        preciseCrossProduct(obj.y, this->_internalWindow.size))),
			sf::Vertex(sf::Vector2f(preciseCrossProduct(obj.endX, this->_internalWindow.size),
			                         preciseCrossProduct(obj.endY, this->_internalWindow.size)))
		};
		line[0].color = sf::Color(obj.color);
		line[1].color = sf::Color(obj.color);
		this->_internalWindow.texture.draw(line, 2, sf::Lines);
		return true;
	}

	bool SFMLDisplay::draw(Drawables::Circle &obj)
	{
		int radius = preciseCrossProduct(obj.size, this->_internalWindow.size);
		sf::CircleShape circle(radius);
		circle.setPosition(sf::Vector2f(preciseCrossProduct(obj.x, this->_internalWindow.size) - radius,
		                                preciseCrossProduct(obj.y, this->_internalWindow.size) - radius));
		circle.setFillColor(sf::Color(obj.color));
		this->_internalWindow.texture.draw(circle);
		return true;
	}

	bool SFMLDisplay::draw(Drawables::Sprite &obj)
	{
		sf::Sprite sprite;
		sf::Vector2<unsigned int> textureSize(0, 0);

		if (this->_loadedResources.find(obj.path) == this->_loadedResources.end()
			|| this->_loadedResources[obj.path].first != resourceSpriteType) {
			return false;
		}
		textureSize = std::get<sf::Texture>(this->_loadedResources[obj.path].second).getSize();
		sprite.setOrigin(sf::Vector2f((textureSize.x / 2), (textureSize.y / 2)));
		sprite.setTexture(std::get<sf::Texture>(this->_loadedResources[obj.path].second));
		sprite.setPosition(sf::Vector2f(preciseCrossProduct(obj.x, this->_internalWindow.size),
								  preciseCrossProduct(obj.y, this->_internalWindow.size)));
		sprite.setRotation(obj.rotation);
		sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
		sprite.scale((obj.sizeX / 100.) * this->_internalWindow.size / textureSize.x,
		             (obj.sizeY / 100.) * this->_internalWindow.size / textureSize.y);
		this->_internalWindow.texture.draw(sprite);
		return true;
	}

	bool SFMLDisplay::draw(Drawables::Text &obj)
	{
		sf::Text text;

		if (this->_loadedResources.find(obj.path) == this->_loadedResources.end()
		    || this->_loadedResources[obj.path].first != resourceFontType) {
			return false;
		}
		if (obj.text.empty()) {
			return true;
		}

		text.setFont(std::get<sf::Font>(this->_loadedResources[obj.path].second));
		text.setFillColor(sf::Color(obj.color));
		text.setCharacterSize(obj.fontSize);
		text.setString(obj.text);
		text.setPosition(sf::Vector2f(preciseCrossProduct(obj.x, this->_internalWindow.size),
		                             preciseCrossProduct(obj.y, this->_internalWindow.size)));
		this->_internalWindow.texture.draw(text);
		return true;
	}

	int SFMLDisplay::preciseCrossProduct(float percent, float total, float base)
	{
		return static_cast<int>(percent * (total / base) + 1);
	}

	void SFMLDisplay::updateInternalWindow()
	{
		this->_internalWindow.size = std::min(this->_mainWindow.getSize().x - 50, this->_mainWindow.getSize().y - 50);
		this->_internalWindow.offsetX = std::max(0U, (this->_mainWindow.getSize().x - this->_internalWindow.size) / 2);
		this->_internalWindow.offsetY = std::max(0U, (this->_mainWindow.getSize().y - this->_internalWindow.size) / 2);
		this->_internalWindow.texture.create(this->_internalWindow.size, this->_internalWindow.size);
	}

	void SFMLDisplay::playSound(Sound &sound)
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
}