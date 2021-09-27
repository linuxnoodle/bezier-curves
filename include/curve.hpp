#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

struct vector2{
    float x;
    float y;
};

struct controlPoint{
    vector2 position;
    SDL_Rect rect{static_cast<int>(position.x), static_cast<int>(position.y), 30, 30};
    bool isBeingDragged = false;
};


namespace curve {
    float linearInterpolate(float x1, float x2, float t);
    vector2 nthBezier(std::vector<controlPoint> points, float t);
}
