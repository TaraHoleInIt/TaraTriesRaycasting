// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.hpp"

void Cleanup( void );
bool Setup( void );

SDL_Renderer* RenderHandle = NULL;
SDL_Window* MainWindow = NULL;
SDL_Texture* GameTexture = NULL;

bool MainThreadRun = true;

RaycasterCamera Camera( MainScreenWidth, MainScreenHeight, 60.0f, 1.0f, 1.0f, -270.0f );
InputManager Input;
World Worldspawn;

const SDL_Rect Fullscreen = {
	.h = MainScreenHeight,
	.w = MainScreenWidth,
	.x = 0,
	.y = 0
};

const uint8_t Map[ 8 * 8 ] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 2, 0, 0, 0, 0, 1,
	1, 0, 2, 2, 3, 0, 0, 1,
	1, 0, 0, 0, 3, 0, 0, 1,
	1, 0, 0, 0, 3, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

const uint32_t pal[ 256 ] = {
	MakeRGBA32( 0, 0, 0, 255 ),
	MakeRGBA32( 0, 0, 255, 255 ),
	MakeRGBA32( 0, 255, 0, 255 ),
	MakeRGBA32( 0, 255, 255, 255 ),

	[ CeilingColor ] = MakeRGBA32( 128, 128, 128, 255 ),
	[ FloorColor ] = MakeRGBA32( 64, 64, 64, 255 )
};

void Cleanup( void ) {
	if ( GameTexture ) {
		SDL_DestroyTexture( GameTexture );
	}

	if ( RenderHandle ) {
		SDL_DestroyRenderer( RenderHandle );
	}

	if ( MainWindow != NULL ) {
		SDL_DestroyWindow( MainWindow );
	}

	if ( SDL_WasInit( 0 ) ) {
		SDL_Quit( );
	}
}

void Terminate( const char* Reason, ... ) {
	static char Buffer[ 1024 ];
	va_list Argp;

	va_start( Argp, Reason );
		vsnprintf( Buffer, sizeof( Buffer ), Reason, Argp );
	va_end( Argp );

	std::cout << "Terminating application." << std::endl;
	std::cout << "Reason: " << Buffer << std::endl;

	exit( 1 );
}

bool Setup( void ) {
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		Terminate( SDL_GetError( ) );
	}

	if ( ( MainWindow = SDL_CreateWindow( "Fart",  400, 400, MainScreenWidth, MainScreenHeight, SDL_WINDOW_SHOWN ) ) == NULL ) {
		Terminate( SDL_GetError( ) );
	}

	if ( ( RenderHandle = SDL_CreateRenderer( MainWindow, -1, 0 ) ) == NULL ) {
		Terminate( SDL_GetError( ) );
	}

	if ( ( GameTexture = SDL_CreateTexture( RenderHandle, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, MainScreenWidth, MainScreenHeight ) ) == NULL ) {
		Terminate( "Failed to create render texture", SDL_GetError( ) );
	}

	SDL_RenderSetIntegerScale( RenderHandle, SDL_TRUE );
	SDL_RenderSetScale( RenderHandle, 4.0f, 4.0f );

	return true;
}

void CopyCameraToScreen( void ) {
	uint32_t* Pixels = NULL;
	int Pitch = 0;

	SDL_LockTexture( GameTexture, &Fullscreen, ( void** ) &Pixels, &Pitch );
		Camera.CopyScreenBuffer32( Pixels, pal, Pitch );
	SDL_UnlockTexture( GameTexture );

	SDL_RenderCopy( RenderHandle, GameTexture, &Fullscreen, &Fullscreen );
}

// todo:
// something
Palette GamePalette( 256 );

int main( int Argc, char** Argv ) {
	SDL_Event Ev;

	atexit( Cleanup );

	if ( Setup( ) ) {
		Worldspawn.LoadFromMemory( Map, 8, 8 );

		while ( MainThreadRun ) {
			if ( SDL_PollEvent( &Ev ) ) {
				Input.Update( );

				switch ( Ev.type ) {
					case SDL_QUIT: {
						MainThreadRun = false;
						break;
					}
					default: break;
				};
			}

			if ( Input.IsTurningLeft( ) ) {
				Camera.Rotate( -1.5f );
			}

			if ( Input.IsTurningRight( ) ) {
				Camera.Rotate( 1.5f );
			}

			if ( Input.IsMovingForward( ) ) {
				Camera.Translate( 1.5f );
			}

			if ( Input.IsMovingBackward( ) ) {
				Camera.Translate( -1.5f );
			}

			if ( Input.IsStrafingLeft( ) ) {
				Camera.Translate( -1.5f, 0.0f );
			}

			if ( Input.IsStrafingRight( ) ) {
				Camera.Translate( 1.5f, 0.0f );
			}

			SDL_SetRenderDrawColor( RenderHandle, 0, 0, 0, 255 );
			SDL_RenderClear( RenderHandle );

			//Worldspawn.Draw2D( RenderHandle, 64 );
			//Camera.DrawCamera( RenderHandle, 8 );
			//Camera.Draw3D( RenderHandle );

			CopyCameraToScreen( );

			SDL_RenderPresent( RenderHandle );
			SDL_Delay( 16 );
		}

		Worldspawn.Close( );
	}

	return 0;
}
