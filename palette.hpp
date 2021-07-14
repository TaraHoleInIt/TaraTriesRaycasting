// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _PALETTE_HPP_H_
#define _PALETTE_HPP_H_

#include "main.hpp"

class Color32 {
    public:
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;

        Color32( void );
        Color32( uint8_t _R, uint8_t _G, uint8_t _B, uint8_t _A );
        Color32( uint32_t Color );

        uint8_t& operator[ ]( int Index );
        Color32 operator=( const uint32_t& Color );

        operator uint32_t( void );
};

class Palette {
    private:
        Color32* Colormap;
        int Length;

    public:
        Palette( const Palette& In );
        Palette( int Size, const Color32* In );

        Palette( int Size );
        ~Palette( void );

        Color32& operator[ ]( int Index );

        void operator=( const Color32* p );
};

#endif
