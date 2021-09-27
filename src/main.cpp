#include <iostream>

#include <curve.hpp>
#include <engine.hpp>

int main(int argc, char **argv){
    engine::init(1280, 720);

    while (engine::runningState){
        engine::update();
        engine::render();
    }
    
    engine::clean();
    return 0; 
}
