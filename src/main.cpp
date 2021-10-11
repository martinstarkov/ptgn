#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cassert>

void INIT() {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }

    auto surface = IMG_Load("../../resources/acorn.png");
    if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) < 0) {
        SDL_Log("Unable to initialize Audio: %s", SDL_GetError());
        return;
    }

    if (TTF_Init() < 0) {
        SDL_Log("Unable to initialize TTF: %s", SDL_GetError());
        return;
    }

    auto font = TTF_OpenFont("../../resources/retro_gaming.ttf", 30);

    assert(font != nullptr);

    Mix_Chunk* sound = NULL;

    sound = Mix_LoadWAV("../../resources/test3.ogg"); if (sound == NULL) { fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError()); }

    int channel;

    channel = Mix_PlayChannel(-1, sound, 0); if (channel == -1) { fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError()); }
    while (Mix_Playing(channel) != 0);

    Mix_FreeChunk(sound);

    Mix_CloseAudio();

    assert(surface != nullptr);

    auto window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return;
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example


    // Close and destroy the window
    SDL_DestroyWindow(window);
    Mix_Quit();

    // Clean up
    SDL_Quit();

}
