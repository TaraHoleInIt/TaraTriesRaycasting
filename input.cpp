// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.hpp"

#define TestExclusiveKey( Key, Notkey ) ( ( this->Keys & Key ) && ! ( this->Keys & Notkey ) )

InputManager::InputManager( void ) : Keys( 0 ) {
}

bool InputManager::IsTurningLeft( void ) {
    return TestExclusiveKey( Key_Left, Key_Right ) ? true : false;
}

bool InputManager::IsTurningRight( void ) {
    return TestExclusiveKey( Key_Right, Key_Left ) ? true : false;
}

bool InputManager::IsStrafingLeft( void ) {
    return TestExclusiveKey( Key_StrafeLeft, Key_StrafeRight ) ? true : false;
}

bool InputManager::IsStrafingRight( void ) {
    return TestExclusiveKey( Key_StrafeRight, Key_StrafeLeft ) ? true : false;
}

bool InputManager::IsMovingForward( void ) {
    return TestExclusiveKey( Key_Forward, Key_Backward ) ? true : false;
}

bool InputManager::IsMovingBackward( void ) {
    return TestExclusiveKey( Key_Backward, Key_Forward ) ? true : false;
}

void InputManager::Update( void ) {
    const uint8_t* Keyboard = NULL;

    if ( ( Keyboard = SDL_GetKeyboardState( NULL ) ) != NULL ) {
        this->Keys = 0;

        this->Keys |= ( Keyboard[ SDL_SCANCODE_LEFT ] ) ? Key_Left : 0;
        this->Keys |= ( Keyboard[ SDL_SCANCODE_RIGHT ] ) ? Key_Right : 0;
        this->Keys |= ( Keyboard[ SDL_SCANCODE_W ] ) ? Key_Forward : 0;
        this->Keys |= ( Keyboard[ SDL_SCANCODE_S ] ) ? Key_Backward : 0;
        this->Keys |= ( Keyboard[ SDL_SCANCODE_A ] ) ? Key_StrafeLeft : 0;
        this->Keys |= ( Keyboard[ SDL_SCANCODE_D ] ) ? Key_StrafeRight : 0;
    }
}
