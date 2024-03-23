//
// Created by pit_trak on 3/21/24.
//

#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

#define internal static
#define local_persist static
#define global_variable static

global_variable SDL_Texture *Texture;
global_variable void *BitmapMemory;
global_variable int BitmapWidth;

internal void
SDLResizeTexture(SDL_Renderer *Renderer, int Width, int Height)
{
    if(BitmapMemory)
    {
        free(BitmapMemory);
    }
    if(Texture)
    {
        SDL_DestroyTexture(Texture);
    }
    Texture = SDL_CreateTexture(Renderer,
                                SDL_PIXELFORMAT_ABGR8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                Width,
                                Height);
    BitmapWidth = Width;
    BitmapMemory = malloc(Width * Height * 4);
}

internal void
SDLUpdateWindow(SDL_Window *Window, SDL_Renderer *Renderer)
{
    SDL_UpdateTexture(Texture,
                      0,
                      BitmapMemory,
                      BitmapWidth + 4);

    SDL_RenderCopy(Renderer,
                   Texture,
                   0,
                   0);

    SDL_RenderPresent(Renderer);
}

bool HandleEvent(SDL_Event *Event)
{
    bool ShouldQuit = false;

    switch (Event->type) {
        case SDL_QUIT:
        {
            printf("SDL_QUIT\n");
            ShouldQuit = true;
        }
            break;

        case SDL_WINDOWEVENT:
        {
            switch (Event->window.event) {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                {
                    SDL_Window *Window = SDL_GetWindowFromID(Event->window.windowID);
                    SDL_Renderer  *Renderer = SDL_GetRenderer(Window);
                    printf("SDL_WINDOWEVENT_SIZE_CHANGED (%d, %d)\n", Event->window.data1, Event->window.data2);
                    SDLResizeTexture(Renderer, Event->window.data1, Event->window.data2);
                }
                    break;

                case SDL_WINDOWEVENT_FOCUS_GAINED:
                {
                    printf("SDL_WINDOWEVENT_FOCUS_GAINED\n");
                }

                case SDL_WINDOWEVENT_EXPOSED:
                {
                    SDL_Window *Window = SDL_GetWindowFromID(Event->window.windowID);
                    SDL_Renderer *Renderer = SDL_GetRenderer(Window);
                    SDLUpdateWindow(Window, Renderer);
                }
                    break;
            }
        }
            break;
    }

    return(ShouldQuit);
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return SDL_SetError("Failed to initialize SDL\n");
    }

    SDL_Window *Window = SDL_CreateWindow("Artisan Adventurer",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              480,
                              SDL_WINDOW_RESIZABLE);

    if (Window)
    {
        // Create a "Renderer" for our window
        SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, 0);

        if (Renderer)
        {
            for(;;)
            {
                SDL_RenderClear(Renderer);
                SDL_RenderPresent(Renderer);

                SDL_Event Event;
                SDL_WaitEvent(&Event);
                if (HandleEvent(&Event))
                {
                    break;
                }
            }
        }

    }



    SDL_Quit();
    return 0;
}