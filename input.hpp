// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _INPUT_HPP_H_
#define _INPUT_HPP_H_

#define Key_Left 0x01
#define Key_Right 0x02
#define Key_StrafeLeft 0x04
#define Key_StrafeRight 0x08
#define Key_Forward 0x10
#define Key_Backward 0x20

class InputManager {
private:
    uint32_t Keys;

public:
    InputManager( void );

    bool IsTurningLeft( void );
    bool IsTurningRight( void );

    bool IsStrafingLeft( void );
    bool IsStrafingRight( void );

    bool IsMovingForward( void );
    bool IsMovingBackward( void );

    void KeyEventCallback( SDL_Keysym Key, bool Down );
    void Update( void );
};

#endif
