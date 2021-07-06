// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.hpp"
#include <new>

World::World( void ) : Map( NULL ), MapWidth( 0 ), MapHeight( 0 ), MapSize( 0 ) {
}

World::~World( void ) {
    if ( this->Map ) {
        delete this->Map;
    }
}

bool World::LoadFromMemory( const uint8_t* _Map, int _MapWidth, int _MapHeight ) {
    if ( _Map != NULL && _MapWidth > 0 && _MapHeight > 0 ) {
        this->Map = new( std::nothrow ) uint8_t[ _MapWidth * _MapHeight ];

        if ( this->Map ) {
            this->MapSize = _MapWidth * _MapHeight;
            this->MapWidth = _MapWidth;
            this->MapHeight = _MapHeight;

            memcpy( this->Map, _Map, this->MapSize );
            return true;
        }
    }

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

void World::Draw2D( SDL_Renderer* RenderTarget, float Scale ) {
    SDL_Rect Re = {
        .x = 0,
        .y = 0,
        .w = ( int ) Scale,
        .h = ( int ) Scale
    };
    int Tile = 0;
    int x = 0;
    int y = 0;

    for ( y = 0; y < this->MapHeight; y++ ) {
        for ( x = 0; x < this->MapWidth; x++ ) {
            Tile = TileAt( x, y );

            switch ( Tile ) {
                case Tile_Blue: {
                    SDL_SetRenderDrawColor( RenderTarget, 0, 0, 255, 255 );
                    break;
                }
                case Tile_Green: {
                    SDL_SetRenderDrawColor( RenderTarget, 0, 255, 0, 255 );
                    break;
                }
                case Tile_Cyan: {
                    SDL_SetRenderDrawColor( RenderTarget, 0, 255, 255, 255 );
                    break;
                }
                case Tile_Empty: {
                    SDL_SetRenderDrawColor( RenderTarget, 0, 0, 0, 255 );
                    break;
                }
                default: continue;
            };

            Re.x = x * ( int ) Scale;
            Re.y = y * ( int ) Scale;

            SDL_RenderDrawRect( RenderTarget, &Re );
        }
    }
}

uint8_t World::TileAt( int x, int y ) {
    if ( x >= 0 && y >= 0 && x < this->MapWidth && y < this->MapHeight ) {
        return this->Map[ x + ( y * this->MapWidth ) ];
    }

    return Tile_Empty;
}
