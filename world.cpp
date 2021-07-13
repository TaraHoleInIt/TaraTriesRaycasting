// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.hpp"
#include <new>

World::World( const uint8_t* _Map, int _MapWidth, int _MapHeight ) {
    LoadFromMemory( _Map, _MapWidth, _MapHeight );
}

World::World( void ) : Map( NULL ), MapWidth( 0 ), MapHeight( 0 ), MapSize( 0 ) {
}

World::~World( void ) {
    if ( this->Map ) {
        delete this->Map;
    }
}

bool World::LoadFromMemory( const uint8_t* _Map, int _MapWidth, int _MapHeight ) {
    if ( _Map != NULL && _MapWidth > 0 && _MapHeight > 0 ) {
        try {
            this->Map = new uint8_t[ _MapWidth * _MapHeight ];
        } catch ( std::bad_alloc ) {
            Terminate( "Failed to allocate %d bytes for the world map", _MapWidth * _MapHeight );
            return false;
        }

        this->MapSize = _MapWidth * _MapHeight;
        this->MapWidth = _MapWidth;
        this->MapHeight = _MapHeight;

        memcpy( this->Map, _Map, this->MapSize );
        return true;
    }

    Close( );
    return false;
}

void World::Close( void ) {
    if ( this->Map ) {
        delete this->Map;
    }

    this->Map = NULL;
    this->MapWidth = 0;
    this->MapHeight = 0;
    this->MapSize = 0;
}

uint8_t World::TileAt( int x, int y ) {
    return this->operator( )( x, y );
}

int World::operator( )( int x, int y ) {
    ClampInt( x, 0, this->MapWidth - 1 );
    ClampInt( y, 0, this->MapHeight - 1 );

    return this->Map[ x + ( y * this->MapWidth ) ];
}

int World::Width( void ) {
    return this->MapWidth;
}

int World::Height( void ) {
    return this->MapHeight;
}
