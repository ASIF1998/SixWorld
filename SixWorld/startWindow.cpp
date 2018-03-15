#include "startWindow.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

// The method in which the start window is displayed.
void startWindow::win(graphics &space) {
    
    // Background image options.
    SDL_Rect backgroundOption = {0, 0, 800, 600};
    
    // Animation options.
    SDL_Rect exAnimationOption = {0, 500, 100, 100}, inAnimationOption = {0, 0, 300, 300};
    
    SDL_Rect buttonOut_1 = {550, 50, 210, 110},
             buttonOut_2 = {550, 180, 210, 110},
             buttonIn_1 = {1578, 138, 570, 290},
             buttonIn_2 = {1578, 510, 570, 290};
    
    // Variables with which can track time.
    int t1 = SDL_GetTicks(), t2;
    
    // The variable state of which determines the existence of the program.
    bool stay = true;
    
    bool animationButton_1 = true, animationButton_2 = true;
    
    // A variable that handles events.
    SDL_Event* event = new SDL_Event;
    
    while (stay) {
        
        // The cycle in which events are processed.
        while (SDL_PollEvent(event)) {
            
            switch (event->type) {
                    
                // If the "cross" button was pressed, the program is terminated.
                case SDL_QUIT: {
                    
                    stay = false;
                    break;
                }
                    
                case SDL_MOUSEBUTTONUP: {
                    
                    if (event->button.button == SDL_BUTTON_LEFT) {
                        
                        if (event->motion.x > 560 && event->motion.x < 760) {
                            
                            if (event->motion.y > 50 && event->motion.y < 150) {
                                
                                Sint32 num = choiceOfRace(space);
                                
                                if (num == -1) {
                                    
                                    stay = false;
                                    
                                } else if (num == 1) {
                                    
                                    std::cout << "Северный" << std::endl;
                                    
                                } else if (num == 2) {
                                    
                                    std::cout << "Южный" << std::endl;
                                    
                                } else if (num == 3) {
                                    
                                    std::cout << "Подземный" << std::endl;
                                    
                                } else if (num == 4) {
                                    
                                    std::cout << "Лесной" << std::endl;
                                    
                                }
                                animationButton_1 = true;
                            }
                            
                            if (event->motion.y > 180 && event->motion.y < 280) {
                                
                                animationButton_2 = true;
                            }
                        }
                    }
                    
                    break;
                }
                    
                case SDL_MOUSEBUTTONDOWN: {
                    
                    if (event->button.button == SDL_BUTTON_LEFT) {
                        
                        if (event->motion.x > 560 && event->motion.x < 760) {
                            
                            if (event->motion.y > 50 && event->motion.y < 150) {
                                
                                animationButton_1 = false;
                                
                            } else if (event->motion.y > 180 && event->motion.y < 280) {
                                
                                animationButton_2 = false;
                            }
                        }
                    }

                    
                    break;
                }
                    
                case SDL_KEYUP: {
                    
                    // If the "escape" button was pressed, the program terminates&
                    if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        
                        stay = false;
                        
                    }
                    
                    break;
                }
            }
        }
        
        t2 = SDL_GetTicks();
        
        if (t2 - t1 > 80) {
            
            t1 = t2;
            
            inAnimationOption.x = (inAnimationOption.x < 650 ? inAnimationOption.x += 30 : 0);
            
            space.copy(*field_, nullptr, &backgroundOption);
            
            if (animationButton_1) {
                
                space.copy(*field_, &buttonIn_1, &buttonOut_1);
                
            }
            
            if (animationButton_2) {
                
                space.copy(*field_, &buttonIn_2, &buttonOut_2);
            }
            
            for (int i = 0; i < 8; i++) {
            
                space.copy(*animationElement_, &inAnimationOption, &exAnimationOption);
                exAnimationOption.x += 100;
            }
            
            exAnimationOption.x = 0;
            space.present();
        }
    }
}

// In this method, the race is selected.
// If the return value is:
// -1 - exit the game;
//  0 - nationality not selected;
//  1 - northern;
//  2 - southern;
//  3 - belowgraun;
//  4 - forest;
Sint32 startWindow::choiceOfRace(graphics &space) {
    
    // Pointer to the background image
#ifdef  __APPLE__
    SDL_Texture* imageWithNamesOfNationalities = IMG_LoadTexture(space.getRender(), "/Users/asifmamedov/Desktop/SixWorld/SixWorld/image/character choice/RGAW9zKlG08.jpg");
#else
    SDL_Texture* imageWithNamesOfNationalities = IMG_LoadTexture(space.getRender(), "image/character choice/RGAW9zKlG08.jpg");
#endif
    
    SDL_Rect optionsDisplayingBackgroundImage = {0, 0, 800, 600};
    
    SDL_Texture *textureCinder, *textureLeaf, *textureSand;
    
    // Loading texture.
    try {
        
        loadTexture(space ,textureCinder, textureLeaf, textureSand);
        
    } catch (const exceptionSituated& except) {
        
        //  If an exception occurs, a message is displayed and the method returns the following value:
        //  0 - if it was a warning;
        // -1 - if it was some kind of mistake;
        std::cerr << except.what() << std::endl;
        space.destroy("%t %t %t %t", imageWithNamesOfNationalities, textureCinder, textureLeaf, textureSand);
        return except.getTypeException() * (-1);
    }
    
    // Required for event processing.
    SDL_Event* event = new SDL_Event;
    
    // Required to display the current image.
    bool stay = true, exit = false;
    
    // A variable in which the return value of the
    // function is stored.
    Sint32 getNumFunction = 0;
    
    // numCinder - the number of objects of type cinder.
    // numLeaf - the number of objects of type leaf.
    // numSand - the number of objects of type sand.
    // numSnow - the number of objects of type snow.
    size_t numCinder = 2000, numLeaf = 1000, numSand = 2000, numSnow = 1000;
    
    // cinderRect - parameters of the displayed image textureCinder
    // leafRect - parameters of the displayed image textureLeaf
    // sandRect - parameters of the displayed image textureSand
    SDL_Rect cinderRect = {0, 0, 1, 2}, leafRect = {0, 0, 5, 1}, sandRect = {0, 0, 1, 2};
    
    // We need in order to simulate the size of the buttons.
    graphics::imageParameters button_1 = {{280, 250, 560, 250}, {88, 88, 220, 120}},
                              button_2 = {{1415, 250, 560, 250}, {489, 88, 220, 120}},
                              button_3 = {{280, 1125, 570, 250}, {93, 390, 220, 120}},
                              button_4 = {{1415, 1125, 560, 250}, {499, 390, 220, 120}};
    
    // Need to know which button to click.
    bool activeButton_1 = true, activeButton_2 = true, activeButton_3 = true, activeButton_4 = true;
    
    // Required to locate the cursor.
    int pos_x = 0, pos_y = 0;
    
    cinder* cinders = new cinder [numCinder];
    leaf* leafs = new leaf [numLeaf];
    sand* sands = new sand [numSand];
    snow* snows = new snow [numSnow];
    
    // Initial initialization.
    for (size_t i = 0; i < numCinder; i++) {
        
        cinders[i].x = rand() % 400;
        cinders[i].y = rand() % 200 + 500;
        cinders[i].length = rand() % 2 + 1;
    }
    
    // Initial initialization.
    for (size_t i = 0; i < numLeaf; i++) {
        
        leafs[i].x = 400 + rand() % 400;
        leafs[i].y = 300 + rand() % 300;
        leafs[i].length = 0;
        leafs[i].motion_x = rand() % 2;
    }
    
    // Initial initialization.
    for (size_t i = 0; i < numSand; i++) {
        
        sands[i].x = 400 + rand() % 400;
        sands[i].y = 100 + rand() % 200;
        sands[i].motion_y = rand() % 2;
        sands[i].length = 3 + rand() % 5;
    }
    
    // Initial initialization.
    for (size_t i = 0; i < numSnow; i++) {
        
        snows[i].x = rand() % 400;
        snows[i].y = rand() % 300;
        snows[i].motion_x = rand() % 2;
        snows[i].length = 1 + rand() % 5;
    }
    
    // Draw a dot in white for the image of snowflakes.
    space.colorRender(0xff, 0xff, 0xff, 0xff);
    
    Uint8 r = 240, g = 240, b = 240;
    
    while (stay) {
        
        /* --------------------------------------------------- */
        /*                Event handling.                      */
        while (SDL_PollEvent(event)) {

            switch (event->type) {

                case SDL_QUIT: {

                    getNumFunction = -1;
                    stay = false;
                    break;
                }

                case SDL_KEYUP: {

                    if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {

                        getNumFunction = -1;
                        stay = false;

                    } else if (event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                        
                        getNumFunction = 0;
                        exit = true;
                    }
                    
                    break;
                }
                    
                case SDL_MOUSEBUTTONDOWN: {
                    
                    if (pos_x > 99 && pos_x < 319 && pos_y > 88 && pos_y < 208) {
                        
                        activeButton_1 = false;
                    }
                    
                    if (pos_x > 499 && pos_x < 719 && pos_y > 88 && pos_y < 208) {
                        
                        activeButton_2 = false;
                    }
                    
                    if (pos_x > 93 && pos_x < 313 && pos_y > 390 && pos_y < 510) {
                        
                        activeButton_3 = false;
                    }
                    
                    if (pos_x > 499 && pos_x < 719 && pos_y > 390 && pos_y < 510) {
                        
                        activeButton_4 = false;
                    }
                    
                    break;
                }
                    
                case SDL_MOUSEBUTTONUP: {
                    
                    if (!activeButton_1) {
                        
                        getNumFunction = 1;
                        exit = true;
                        
                    } else if (!activeButton_2) {
                        
                        getNumFunction = 2;
                        exit = true;
                        
                    } else if (!activeButton_3) {
                        
                        getNumFunction = 3;
                        exit = true;
                        
                    } else if (!activeButton_4) {
                        
                        getNumFunction = 4;
                        exit = true;
                    }
                    
                    break;
                }
                    
                case SDL_MOUSEMOTION: {
                    
                    pos_x = event->motion.x;
                    pos_y = event->motion.y;
                    break;
                }
            }
        }
        
        /* --------------------------------------------------- */
        space.copy(imageWithNamesOfNationalities, nullptr, &optionsDisplayingBackgroundImage);
        
        if (pos_x > 99 && pos_x < 319 && pos_y > 88 && pos_y < 208 && activeButton_1) {
            
            space.copy(imageWithNamesOfNationalities, &button_1.in, &button_1.out);
            
        } else if (pos_x > 499 && pos_x < 719 && pos_y > 88 && pos_y < 208 && activeButton_2) {
            
            space.copy(imageWithNamesOfNationalities, &button_2.in, &button_2.out);
            
        } else if (pos_x > 93 && pos_x < 313 && pos_y > 390 && pos_y < 510 && activeButton_3) {
            
            space.copy(imageWithNamesOfNationalities, &button_3.in, &button_3.out);
            
        }else if (pos_x > 499 && pos_x < 719 && pos_y > 390 && pos_y < 510 && activeButton_4) {
            
            space.copy(imageWithNamesOfNationalities, &button_4.in, &button_4.out);
        }
        
        // Realization of movement.
        for (size_t i = 0; i < numCinder; i++) {
            
            if (cinders[i].y < rand() % 100 + 400) {
                
                cinders[i].y = 600;
                cinders[i].x = rand() % 400;
            }
            
            cinderRect.x = cinders[i].x = (rand() % 2 ? ++cinders[i].x : --cinders[i].x);
            cinderRect.y = cinders[i].y -= cinders[i].length;
            space.copy(textureCinder, nullptr, &cinderRect);
        }
        
        // Realization of movement.
        for (size_t i = 0; i < numLeaf; i++) {
            
            if (!leafs[i].length) {
                
                leafs[i].motion_x = !leafs[i].motion_x;
                leafs[i].length = rand() % 300;
            }
            
            if (leafs[i].y > 600) {
                
                leafs[i].x = 400 + rand() % 400;
                leafs[i].y = 300;
            }
            
            if (leafs[i].x < 400 || leafs[i].x > 800) {
                
                leafs[i].motion_x = !leafs[i].motion_x;
            }
            
            leafs[i].length--;
            leafRect.x = (leafs[i].motion_x ? ++leafs[i].x : --leafs[i].x);
            leafRect.y = ++leafs[i].y;
            space.copy(textureLeaf, nullptr, &leafRect);
        }
        
        // Realization of movement.
        for (size_t i = 0; i < numSand; i++) {
            
            if (sands[i].y > 300 || sands[i].y < 0 || sands[i].x < 400) {
                
                sands[i].motion_y = !sands[i].motion_y;
            }
            
            sandRect.x = (sands[i].motion_y ? sands[i].x -= sands[i].length : sands[i].x += sands[i].length);
            sandRect.y = (sands[i].motion_y ? sands[i].y += sands[i].length : sands[i].y -= sands[i].length);
            space.copy(textureSand, nullptr, &sandRect);
        }
        
        // Realization of movement.
        for (size_t i = 0; i < numSnow; i++) {
            
            if (snows[i].x < 0 || snows[i].x > 400) {
                
                snows[i].x = rand() % 400;
            }
            
            if (snows[i].y > 290) {
                
                snows[i].y = (i < numSnow / 2 ? 0 : rand() % 300);
            }
            
            snows[i].x += (snows[i].motion_x ? 1 : -1);
            snows[i].y += snows[i].length;
            space.setPoint(snows[i].x, snows[i].y);
        }
        

        if (exit) {
            
            r -= 2;
            g -= 2;
            b -= 2;
            
            SDL_SetTextureColorMod(imageWithNamesOfNationalities, r, g, b);
            
            if (!r && !g && !b) {
                
                stay = false;
            }
        }
        
        space.present();
    }
    
    delete [] cinders;
    delete [] leafs;
    delete [] sands;
    delete [] snows;
    delete event;
    
    space.destroy("%t %t %t %t", imageWithNamesOfNationalities, textureCinder, textureLeaf, textureSand);
    return getNumFunction;
}

void startWindow::loadTexture(graphics& space, SDL_Texture *&textureCinder, SDL_Texture *&textureLeaf, SDL_Texture *&textureSand) {
    
    SDL_Surface* surfaceCinder, *surfaceLeaf, *surfaceSand;
    
    // Loading image.
#ifndef __APPLE__
    surfaceCinder = IMG_Load("image/character choice/ImageAhg.png");
    surfaceLeaf = IMG_Load("image/character choice/Imageleaf.png");
    surfaceSand = IMG_Load("image/character choice/imagepng.png");
#else
    surfaceCinder = IMG_Load("/Users/asifmamedov/Desktop/SixWorld/SixWorld/image/character choice/ImageAhg.png");
    surfaceLeaf = IMG_Load("/Users/asifmamedov/Desktop/SixWorld/SixWorld/image/character choice/Imageleaf.png");
    surfaceSand = IMG_Load("/Users/asifmamedov/Desktop/SixWorld/SixWorld/image/character choice/imagepng.png");
#endif
    
    if (!surfaceCinder || !surfaceLeaf || !surfaceSand) {
        
        throw exceptionSituated ("Could not load photo.", TYPEEXCEPTION_WARNING);
    }
    
    // Make white color transparent.
    SDL_SetColorKey(surfaceCinder, SDL_TRUE, SW_TRANSPARENTCOLOR_WHITE);
    SDL_SetColorKey(surfaceLeaf, SDL_TRUE, SW_TRANSPARENTCOLOR_WHITE);
    SDL_SetColorKey(surfaceSand, SDL_TRUE, SW_TRANSPARENTCOLOR_WHITE);
    
    // Create a texture.
    try {
        
        textureCinder = space.createTexture(surfaceCinder);
        textureLeaf = space.createTexture(surfaceLeaf);
        textureSand = space.createTexture(surfaceSand);
        
    } catch (const exceptionSituated& except) {
        
        throw except;
    }
    
    // Destroy the surface.
    space.destroy("%s %s %s", surfaceCinder, surfaceLeaf, surfaceSand);
}

