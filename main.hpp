// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _MAIN_HPP_H_
#define _MAIN_HPP_H_

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstdarg>
#include <SDL.h>

#include "raycastcamera.hpp"
#include "input.hpp"
#include "world.hpp"

#define MakeRGBA32( r, g, b, a ) static_cast< uint32_t >( ( ( a & 0xFF ) << 24 ) | ( ( r & 0xFF ) << 16 ) | ( ( g & 0xFF ) << 8 ) | ( b & 0xFF ) )

#define ClampInt( Value, Min, Max ) { \
    Value = Value < Min ? Min : Value; \
    Value = Value > Max ? Max : Value; \
}

#define DegreesToRadians( Degrees ) ( ( Degrees * M_PI * 2.0 ) / 360.0 )
#define RadiansToDegrees( Radians ) ( ( Radians * 360.0 ) / ( ( M_PI * 2.0f ) ) )

#define MainScreenWidth 800
#define MainScreenHeight 600

#define CeilingColor 0xFE
#define FloorColor 0xFD

#define WallHeight 64
#define WallWidth 64

#define PlayerHeight 32

void Terminate( const char* Reason, ... );
void CopyCameraToScreen( void );
void Cleanup( void );
bool Setup( void );

extern const SDL_Rect Fullscreen;

extern World Worldspawn;
extern RaycasterCamera Camera;
extern InputManager Input;

#endif
