// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef _RAYCASTCAMERA_H_
#define _RAYCASTCAMERA_H_

class RaycasterCamera {
private:
    uint8_t* ScreenBuffer;
    size_t ScreenBufferSize;

    float ProjPlaneDist;
    float Angle;
    float Fov;
    float x;
    float y;

    int ScreenWidth;
    int ScreenHeight;

    float GetAngleBetweenRays( void );
    float ClampAngle( float Input );

    void DrawCeiling( void );
    void DrawFloor( void );

    void SetupProjectionPlane( void );

    bool AllocateScreenBuffer( void );
    void FreeScreenBuffer( void );

public:
    RaycasterCamera( void ) = delete;
    RaycasterCamera( int _ScreenWidth, int _ScreenHeight );
    RaycasterCamera( int _ScreenWidth, int _ScreenHeight, float _Fov );
    RaycasterCamera( int _ScreenWidth, int _ScreenHeight, float _Fov, float _x, float _y );
    RaycasterCamera( int _ScreenWidth, int _ScreenHeight, float _Fov, float _x, float _y, float _Angle );
    ~RaycasterCamera( void );

    void DrawCamera( SDL_Renderer* RenderTarget, int Radius );
    void Draw3D( SDL_Renderer* RenderTarget );
    
    void Translate( float dx, float dy );
    void Translate( float Magnitude );
    void Rotate( float Amount );

    void CopyScreenBuffer( uint8_t* Dest, size_t Size );
    void CopyScreenBuffer( uint8_t* Dest, int DestPitch, int SrcX, int SrcY, int Width, int Height );

    void CopyScreenBuffer32( uint32_t* Dest, const uint32_t* Palette, int Pitch );
};

#endif
