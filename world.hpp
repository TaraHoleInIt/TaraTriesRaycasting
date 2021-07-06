// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "main.hpp"

#define Tile_Empty 0
#define Tile_Blue 1
#define Tile_Green 2
#define Tile_Cyan 3

class World {
    uint8_t* Map;

    int MapWidth;
    int MapHeight;
    int MapSize;

public:
    World( void );
    ~World( void );

    bool LoadFromMemory( const uint8_t* _Map, int _MapWidth, int _MapHeight );
    void Close( void );

    void Draw2D( SDL_Renderer* RenderTarget, float Scale );

    uint8_t TileAt( int x, int y );
};

#endif
