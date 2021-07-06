// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _MAIN_HPP_H_
#define _MAIN_HPP_H_

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <SDL.h>

#include "raycastcamera.hpp"
#include "input.hpp"
#include "world.hpp"

typedef struct {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
} __attribute__( ( packed ) ) Color24;

#define DegreesToRadians( Degrees ) ( ( Degrees * M_PI * 2.0 ) / 360.0 )
#define RadiansToDegrees( Radians ) ( ( Radians * 360.0 ) / ( ( M_PI * 2.0f ) ) )

#define MainScreenWidth 800
#define MainScreenHeight 600

#define CeilingColor 0xFE
#define FloorColor 0xFD

#define WallHeight 64
#define WallWidth 64

#define PlayerHeight 32

extern World Worldspawn;
extern RaycasterCamera Camera;

#endif
