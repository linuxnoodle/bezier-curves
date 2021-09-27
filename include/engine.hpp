#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_log.h>
#include <cstdlib>
#include <cstdint>
#include <ctgmath>
#include <curve.hpp>

namespace engine {
    extern bool runningState;

    /**
     * Initializes SDL2.
     * @param width - Window width
     * @param height - Window height
     */
    void init(int width, int height);
    void update();
    void render();
    void clean();
}
