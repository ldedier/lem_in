/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/11 18:41:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

int angle  = 0;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Texture* bg;

int InitEverything();
int InitSDL();
int CreateWindow();
int CreateRenderer();
void SetupRenderer();

void Render();
void RunGame();

SDL_Rect playerPos;

int main()
{
	if ( !InitEverything() ) 
		return -1;
	playerPos.x = 20;
	playerPos.y = 20;
	playerPos.w = 100;
	playerPos.h = 100;
	RunGame();
}

void Render()
{
	SDL_Point center;
	center.x = playerPos.w / 2;
	center.y = playerPos.h / 2;
	SDL_RenderCopy(renderer, bg, NULL, NULL);
	SDL_RenderCopyEx(renderer, texture, NULL, &playerPos, angle, &center, SDL_FLIP_NONE);
	SDL_RenderPresent( renderer);
}

SDL_Texture* LoadTexture(const char *str)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, str);
	if (texture == NULL)
	{
		return NULL;
	}
	return texture;
}

int	init_texture()
{
	texture = LoadTexture(PATH"/resources/ant.png");
	bg = LoadTexture(PATH"/resources/swag.png");
	if (!texture || !bg)
		return (0);
	return (1);
}

int InitEverything()
{
	if (!InitSDL())
		return 0;
	if (!CreateWindow())
		return 0;
	if (!CreateRenderer())
		return 0;
	if (!init_texture())
		return 0;
	SetupRenderer();
	return 1;
}

int InitSDL()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		return 0;

	return 1;
}

int CreateWindow()
{
	window = SDL_CreateWindow( "lem-in_visu", 300, 200, WIN_WIDTH, WIN_HEIGHT, 0 );
	if ( window == NULL )
		return 0;
	return 1;
}

int CreateRenderer()
{
	renderer = SDL_CreateRenderer( window, -1, 0 );

	if ( renderer == NULL )
		return 0;
	return 1;
}

void SetupRenderer()
{
	SDL_RenderSetLogicalSize( renderer, WIN_WIDTH, WIN_HEIGHT );
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
}

void RunGame()
{
	int loop = 1;

	while ( loop )
	{
		SDL_Event event;
		while ( SDL_PollEvent( &event ) )
		{
			if ( event.type == SDL_QUIT || 
			(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) )
				loop = 0;
			else if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_RIGHT:
						playerPos.x += 10;
						break;
					case SDLK_LEFT:
						playerPos.x -= 10;
						break;
					case SDLK_DOWN:
						playerPos.y += 10;
						break;
					case SDLK_UP:
						playerPos.y -= 10;
						break;
					default :
						break;
				}
			}
		}
		angle++;
		Render();
		SDL_Delay( 16 );
	}
}
