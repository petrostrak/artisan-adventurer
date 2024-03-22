//
// Created by pit_trak on 3/21/24.
//

#include "SDL2/SDL.h"

bool HandleEvent(SDL_Event *Event)
{
    bool ShouldQuit = false;

    switch (Event->type) {
        case SDL_QUIT:
        {
            printf("SDL_QUIT\n");
            ShouldQuit = true;
        }
        case SDL_WINDOWEVENT:
        {
            switch (Event->window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                {
                    printf("SDL_WINDOWEVENT_RESIZED (%d, %d)\n", Event->window.data1, Event->window.data2);
                }
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                {
                    SDL_Window *Window = SDL_GetWindowFromID(Event->window.windowID);
                    SDL_Renderer *Renderer = SDL_GetRenderer(Window);
                    static bool IsWhite = true;
                    if (IsWhite)
                    {
                        SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
                        IsWhite = false;
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
                        IsWhite = true;
                    }
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

    SDL_Window *Window;
    Window = SDL_CreateWindow("Artisan Adventurer",
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