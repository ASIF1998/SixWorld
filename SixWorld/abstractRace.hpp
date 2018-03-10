#ifndef _abstractRace_hpp_
#define _abstractRace_hpp_
#   include <SDL2/SDL.h>
#   include <SDL2/SDL_image.h>
#   include <string>
#   include <iostream>

class abstractRace {
    
protected:
    
    // Player name.
    std::string _name;
    
    // Player images.
    static SDL_Texture* personageImage_;
    
    SDL_Texture* animationImage_;
    
    // Parameters image;
    SDL_Rect* in, *out;
    
    // Quantity images.
    size_t _numImage, _numParameters;
    
    Uint8 _life, _damage;
    
    Uint16 _bonuses;
    
public:
    
    // Default construction.
    abstractRace();
    
    // Loading personage image.
    static void createPersonageImage() {
        
        
    }
    
    // Destroy personage image.
    static void destroyPersonageImage() {
        
        
    }
};

#endif /* _abstractRace_hpp_ */
