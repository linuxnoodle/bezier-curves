#include <SDL2/SDL_render.h>
#include <engine.hpp>

SDL_Window *window;
SDL_Renderer *renderer;

int screenWidth, screenHeight;
int mouseX, mouseY;
bool engine::runningState = true;

std::vector<controlPoint> controlPoints;

bool checkRectCollision(int mouseX, int mouseY, vector2 point, vector2 size){
    return (mouseX >= point.x - (size.x * 0.5) && mouseX <= point.x + (size.x * 0.5) && mouseY >= point.y - (size.y * 0.5) && mouseY <= point.y + (size.y * 0.5));
}

void engine::init(int width, int height){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        screenWidth = width;
        screenHeight = height;

        controlPoints.push_back({{0,0}});
        controlPoints.push_back({{static_cast<float>(screenWidth), static_cast<float>(screenHeight)}});

        window = SDL_CreateWindow("Bezier Curves", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        } else {
            SDL_Log("Failed to initialize. Error: %s", SDL_GetError());
            std::exit(1);
        }
    } else {
        SDL_Log("Failed to initialize. Errors:\n %s", SDL_GetError());
        std::exit(1);
    }
}

void engine::update(){
    SDL_GetMouseState(&mouseX, &mouseY);
    // Event handling. 
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_KEYDOWN:{
            switch (event.key.keysym.sym){
                case SDLK_ESCAPE: {
                    engine::runningState = false;
                    break;
                }
            }
        }
        case SDL_MOUSEBUTTONDOWN:{
            for (unsigned int i = 0; i < controlPoints.size(); ++i){
                if (event.button.button == SDL_BUTTON_LEFT){
                    controlPoints[i].isBeingDragged = true;
                }
            }
            if (event.button.button == SDL_BUTTON_RIGHT){
                // Kinda janky, but you then can't stack points
                bool noPointCollision = true;
                int position = 0;
                for (unsigned int i = 0; i < controlPoints.size(); ++i){
                    if (checkRectCollision(mouseX, mouseY, controlPoints[i].position, {40, 40})){
                        position = i;
                        noPointCollision = false;
                        break;
                    }
                }
                if (noPointCollision){
                    controlPoints.insert(controlPoints.end() - 1, {{static_cast<float>(mouseX), static_cast<float>(mouseY)}});
                } else if (controlPoints.size() > 2){
                    controlPoints.erase(controlPoints.begin() + position);
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:{
            for (unsigned int i = 0; i < controlPoints.size(); ++i){
                if (event.button.button == SDL_BUTTON_LEFT){
                    controlPoints[i].isBeingDragged = false;    
                }
            }
            break;
        }
    }
    for (unsigned int i = 0; i < controlPoints.size(); ++i){
        if (controlPoints[i].isBeingDragged && checkRectCollision(mouseX, mouseY, controlPoints[i].position, {40, 40})){
            controlPoints[i].position.x = mouseX;
            controlPoints[i].position.y = mouseY;
        }
    }
}

void engine::render(){
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (float t = 0; t < 1.0; t += 0.0001){
        vector2 point = curve::nthBezier(controlPoints, t);
        SDL_RenderDrawPointF(renderer, point.x, point.y);
    }
  
    // Draws lines between points
    SDL_SetRenderDrawColor(renderer, 120, 120, 250, 255);
    for (unsigned int i = 0; i < controlPoints.size() - 1; ++i)
        SDL_RenderDrawLine(renderer, controlPoints[i].position.x, controlPoints[i].position.y, controlPoints[i + 1].position.x, controlPoints[i + 1].position.y); 

    // Draws rects around "control points" (endpoints)
    SDL_SetRenderDrawColor(renderer, 170, 150, 150, 255);
    std::vector<SDL_Rect> controlRects;
    for (unsigned int i = 0; i < controlPoints.size(); ++i){
        controlRects.push_back(SDL_Rect{static_cast<int>(controlPoints[i].position.x) - 15, static_cast<int>(controlPoints[i].position.y) - 15, 40, 40});
        SDL_RenderFillRect(renderer, &controlRects[i]);
    }
    
    SDL_RenderPresent(renderer);
}

void engine::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
