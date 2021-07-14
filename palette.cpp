// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.hpp"

Color32::Color32( void ) : R( 0 ), G( 0 ), B( 0 ), A( 0xFF ) {
}

Color32::Color32( uint8_t _R, uint8_t _G, uint8_t _B, uint8_t _A ) : R( _R ), G( _G ), B( _B ), A( _A ) {
}

Color32::Color32( uint32_t Color ) {
    this->A = ( Color >> 24 ) & 0xFF;
    this->R = ( Color >> 16 ) & 0xFF;
    this->G = ( Color >> 8 ) & 0xFF;
    this->B = Color & 0xFF;
}

uint8_t& Color32::operator[ ]( int Index ) {
    uint8_t& Temp = this->R;

    switch ( Index ) {
        case 0: {
            Temp = this->R;
            break;
        }
        case 1: {
            Temp = this->G;
            break;
        }
        case 2: {
            Temp = this->B;
            break;
        }
        case 3: {
            Temp = this->A;
            break;
        }
        default: break;
    };

    Terminate( "%s: Index %d is out of range. Expecting 0 to 3.", __FUNCTION__, Index );
    return Temp;
}

Color32::operator uint32_t( void ) {
    return \
        ( ( this->A & 0xFF ) << 24 ) | \
        ( ( this->R & 0xFF ) << 16 ) | \
        ( ( this->G & 0xFF ) << 8 ) | \
        ( ( this->B & 0xFF ) ) \
    ;
}

Color32 Color32::operator=( const uint32_t& Color ) {
    return Color32( Color );
}

Palette::Palette( int _Length ) : Length( _Length ) {
    try {
        this->Colormap = new Color32[ _Length ];
    } catch ( std::bad_alloc ) {
        Terminate( "%s: Failed to allocate %d bytes for a palette.", __FUNCTION__, _Length * sizeof( uint32_t ) );
    }

    memset( this->Colormap, 0, _Length * sizeof( Color32 ) );
}

Palette::~Palette( void ) {
    if ( this->Colormap != NULL ) {
        delete[ ] this->Colormap;
    }

    this->Colormap = NULL;
}

Color32& Palette::operator[ ]( int Index ) {
    if ( Index < 0 || Index >= this->Length ) {
        Terminate( "%s: Index %d is out of range. Expected 0 to %d", __FUNCTION__, Index, this->Length - 1 );
    }

    return this->Colormap[ Index ];
}

Palette::Palette( const Palette& In ) {
    
}

Palette::Palette( int Size, const Color32* In ) : Palette( Size ) {
    memcpy( this->Colormap, In, Size * sizeof( Color32 ) );
}

void Palette::operator=( const Color32* p ) {
    memcpy( this->Colormap, p, this->Length * sizeof( Color32 ) );
}
