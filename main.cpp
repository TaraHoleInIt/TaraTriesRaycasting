// Copyright (c) 2021 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.hpp"

void Cleanup( void );
bool Setup( void );

SDL_Renderer* RenderHandle = NULL;
SDL_Window* MainWindow = NULL;

bool MainThreadRun = true;

RaycasterCamera Camera( MainScreenWidth, MainScreenHeight, 60.0f, 1.0f, 1.0f, -270.0f );
InputManager Input;
World Worldspawn;

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

Color24 Palette[ 256 ] = {
	{ .Red = 0, .Green = 0, .Blue = 0 },		// Empty
	{ .Red = 0, .Green = 0, .Blue = 255 },		// Tile_Blue
	{ .Red = 0, .Green = 255, .Blue = 0 },		// Tile_Green
	{ .Red = 0, .Green = 255, .Blue = 255 },	// Tile_Cyan

	[ CeilingColor ] = { .Red = 128, .Green = 128, .Blue = 128 },	// Ceiling
	[ FloorColor ] = { .Red = 64, .Green = 64, .Blue = 64 }			// Floor
};

void Cleanup( void ) {
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

bool Setup( void ) {
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
		printf( "%s\n", SDL_GetError( ) );
		return false;
	}

	if ( ( MainWindow = SDL_CreateWindow( "Fart",  400, 400, MainScreenWidth, MainScreenHeight, SDL_WINDOW_SHOWN ) ) == NULL ) {
		printf( "%s\n", SDL_GetError( ) );
		return false;
	}

	if ( ( RenderHandle = SDL_CreateRenderer( MainWindow, -1, 0 ) ) == NULL ) {
		printf( "%s\n", SDL_GetError( ) );
		return false;
	}

	return true;
}

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
			Camera.Draw3D( RenderHandle );

			SDL_RenderPresent( RenderHandle );
			SDL_Delay( 16 );
		}

		Worldspawn.Close( );
	}

	return 0;
}
