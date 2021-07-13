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
    private:
        uint8_t* Map;

        int MapWidth;
        int MapHeight;
        int MapSize;

    public:
        int operator( )( int x, int y );

        World( const uint8_t* Map, int _MapWidth, int _MapHeight );
        World( void );
        ~World( void );

        bool LoadFromMemory( const uint8_t* _Map, int _MapWidth, int _MapHeight );
        void Close( void );

        uint8_t TileAt( int x, int y );

        int Width( void );
        int Height( void );
};

#endif
