// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.hpp"

RaycasterCamera::RaycasterCamera( int _ScreenWidth, int _ScreenHeight ) : \
    ScreenWidth( _ScreenWidth ), \
    ScreenHeight( _ScreenHeight ), \
    Fov( 60.0f ), \
    x( 0.0f ), \
    y( 0.0f ) \
    {
        AllocateScreenBuffer( );
        SetupProjectionPlane( );
}

RaycasterCamera::RaycasterCamera( int _ScreenWidth, int _ScreenHeight, float _Fov ) : \
    ScreenWidth( _ScreenWidth ), \
    ScreenHeight( _ScreenHeight ), \
    x( 0.0f ), \
    y( 0.0f ), \
    Fov( _Fov ) \
    {
        AllocateScreenBuffer( );
        SetupProjectionPlane( );
}

RaycasterCamera::RaycasterCamera( int _ScreenWidth, int _ScreenHeight, float _Fov, float _x, float _y ) : \
    ScreenWidth( _ScreenWidth ), \
    ScreenHeight( _ScreenHeight ), \
    x( _x ), \
    y( _y ), \
    Fov( _Fov ) \
    {
        AllocateScreenBuffer( );
        SetupProjectionPlane( );
}

RaycasterCamera::RaycasterCamera( int _ScreenWidth, int _ScreenHeight, float _Fov, float _x, float _y, float _Angle ) : \
    ScreenWidth( _ScreenWidth ), \
    ScreenHeight( _ScreenHeight ), \
    x( _x ), \
    y( _y ), \
    Fov( _Fov ), \
    Angle( _Angle ) \
    {
        AllocateScreenBuffer( );
        SetupProjectionPlane( );
}

float RaycasterCamera::GetAngleBetweenRays( void ) {
    return Fov / ( float ) ScreenWidth;
}

void RaycasterCamera::DrawCamera( SDL_Renderer* RenderTarget, int Radius ) {
    float HalfFov = this->Fov / 2.0f;
    float RayLeft = 0.0f;
    float RayRight = 0.0f;
    float px = 0.0f;
    float py = 0.0f;
    int i = 0;

    RayLeft = ClampAngle( this->Angle - HalfFov );
    RayRight = ClampAngle( this->Angle + HalfFov );

    SDL_SetRenderDrawColor( RenderTarget, 0, 255, 0, 255 );

    for ( i = 0; i <= 360; i++ ) {
        px = this->x + ( cos( DegreesToRadians( i ) ) * Radius );
        py = this->y + ( sin( DegreesToRadians( i ) ) * Radius );

        SDL_RenderDrawLine(
            RenderTarget,
            ( int ) this->x,
            ( int ) this->y,
            ( int ) px,
            ( int ) py
        );
    }

    SDL_SetRenderDrawColor( RenderTarget, 0, 255, 255, 255 );

    px = this->x + ( cos( DegreesToRadians( RayLeft ) ) * 32.0f );
    py = this->y + ( sin( DegreesToRadians( RayLeft ) ) * 32.0f );

    SDL_RenderDrawLine(
        RenderTarget,
        ( int ) this->x,
        ( int ) this->y,
        ( int ) px,
        ( int ) py
    );

    px = this->x + ( cos( DegreesToRadians( RayRight ) ) * 32.0f );
    py = this->y + ( sin( DegreesToRadians( RayRight ) ) * 32.0f );

    SDL_RenderDrawLine(
        RenderTarget,
        ( int ) this->x,
        ( int ) this->y,
        ( int ) px,
        ( int ) py
    );

    SDL_SetRenderDrawColor( RenderTarget, 255, 0, 0, 255 );

    px = this->x + ( cos( DegreesToRadians( this->Angle) ) * 256.0f );
    py = this->y + ( sin( DegreesToRadians( this->Angle ) ) * 256.0f );

    SDL_RenderDrawLine(
        RenderTarget,
        ( int ) this->x,
        ( int ) this->y,
        ( int ) px,
        ( int ) py
    );
}

void RaycasterCamera::Translate( float dx, float dy ) {
    float px = this->x + dx;
    float py = this->y + dy;

    if ( px >= 0.0f && py >= 0.0f ) {
        this->x = px;
        this->y = py;
    }
}

void RaycasterCamera::Rotate( float Amount ) {
    this->Angle+= Amount;

    this->Angle = this->Angle < 0.0f ? this->Angle + 360.0f : this->Angle;
    this->Angle = this->Angle > 360.0f ? this->Angle - 360.0f : this->Angle;
}

float RaycasterCamera::ClampAngle( float Input ) {
    Input = Input < 0.0f ? Input + 360.0f : Input;
    Input = Input > 360.0f ? Input - 360.0f : Input;

    return Input;
}

void RaycasterCamera::Translate( float Magnitude ) {
    float tx = 0.0f;
    float ty = 0.0f;

    Translate(
        cos( DegreesToRadians( this->Angle ) ) * Magnitude,
        sin( DegreesToRadians( this->Angle ) ) * Magnitude
    );
}

void RaycasterCamera::Draw3D( SDL_Renderer* RenderTarget ) {
    float RayAngle = 0.0f;
    float px = 0.0f;
    float py = 0.0f;
    float dx = 0.0f;
    float dy = 0.0f;
    int tx = 0;
    int ty = 0;
    int t = 0;
    int x = 0;

    DrawCeiling( );
    DrawFloor( );

    RayAngle = ClampAngle( this->Angle - ( this->Fov / 2.0f ) );

    for ( x = 0; x < this->ScreenWidth; x++ ) {
        RayAngle = ClampAngle( GetAngleBetweenRays( ) + RayAngle );

        dx = cos( DegreesToRadians( RayAngle ) );
        dy = sin( DegreesToRadians( RayAngle ) );

        break;
    }
}

void RaycasterCamera::DrawCeiling( void ) {
    // FIXME:
    // Proper palette
    memset( this->ScreenBuffer, CeilingColor, this->ScreenWidth * ( this->ScreenHeight / 2 ) );
}

void RaycasterCamera::DrawFloor( void ) {
    int Offset = this->ScreenWidth * ( this->ScreenHeight / 2 );

    // FIXME:
    // Proper palette
    memset( &this->ScreenBuffer[ Offset ], FloorColor, Offset );
}

void RaycasterCamera::SetupProjectionPlane( void ) {
    this->ProjPlaneDist = ( ( float ) ( ScreenWidth / 2 ) ) / tan( DegreesToRadians( this->Fov / 2.0f ) );
}

bool RaycasterCamera::AllocateScreenBuffer( void ) {
    try {
        ScreenBuffer = new uint8_t[ ScreenWidth * ScreenHeight ];
    }
    catch ( std::bad_alloc ) {
        std::cout << "Failed to allocate framebuffer memory." << std::endl << "Aborting." << std::endl;
        exit( 1 );

        return false;
    }

    return true;
}

void RaycasterCamera::FreeScreenBuffer( void ) {
    if ( this->ScreenBuffer ) {
        delete[ ] this->ScreenBuffer;
        this->ScreenBuffer = NULL;
    }
}

RaycasterCamera::~RaycasterCamera( void ) {
    FreeScreenBuffer( );
}
