// Created by Mamedov Asif and Kiseleva Elena
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "graphics.hpp"
#include <string>
#include "diologWindow.hpp"
#include "startWindow.hpp"
#include "exception/exceptionSituated.hpp"
#include "abstractRace.hpp"
#include <ctime>

int main(int argc, const char * argv[]) {
    
    srand((unsigned int) time(nullptr));
    
    try {
        
        graphics::init();
        
    } catch (const exceptionSituated& except) {
        
        std::cerr << except.what() << std::endl;
        
        if (except.getTypeException() == TYPEEXCEPTION_ERROR) {
            
            graphics::quit();
            exit(-1);
        }
    }
    
    graphics space;
    
#ifdef __APPLE__
    diologWindow<startWindow> startGame ("/Users/asifmamedov/Desktop/SixWorld/SixWorld/image/fire animation/pao",
                                         "/Users/asifmamedov/Desktop/SixWorld/SixWorld/image/fire animation/animationFire",
                                         1, 1, space.getRender(), SW_TRANSPARENTCOLOR_BLACK);
#else
    diologWindow<startWindow> startGame ("image/fire animation/pao", "animationFire", 1, 1, space.getRender(), SW_TRANSPARENTCOLOR_BLACK);
#endif
    
    startGame.win(space);
    
    graphics::quit();
    
    return 0;
}
