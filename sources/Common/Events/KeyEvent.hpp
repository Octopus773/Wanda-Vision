/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** KeyEvent
*/

#pragma once

#include "Common/Event.hpp"

namespace Arcade::Events
{
	//! @brief The enum to allow standardized values between graphical libs
	typedef enum {
        UNDEFINED = 0,
        ESCAPE,
        ENTER,
        SUPPR,
        MOUSE_LEFT,
        MOUSE_RIGHT,
        ARROW_UP,
        ARROW_DOWN,
        ARROW_LEFT,
        ARROW_RIGHT,
        SHIFT,
        K_1,
        K_2,
        K_3,
        K_4,
        K_5,
        K_6,
        K_7,
        K_8,
        K_9,
        K_0,
        K_A,
        K_Z,
        K_E,
        K_R,
        K_T,
        K_Y,
        K_U,
        K_I,
        K_O,
        K_P,
        K_Q,
        K_S,
        K_D,
        K_F,
        K_G,
        K_H,
        K_J,
        K_K,
        K_L,
        K_M,
        K_W,
        K_X,
        K_C,
        K_V,
        K_B,
        K_N
    } KeyCode;

	struct KeyEvent : public Event
	{
		//! @brief The key clicked
		KeyCode key;
	};
}