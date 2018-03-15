#ifndef _startWindow_hpp
#   define _startWindow_hpp
#       include "diologWindow.hpp"
#       include "graphics.hpp"
#       include <SDL2/SDL.h>
#       include "exception/exceptionSituated.hpp"

class startWindow: public diologWindow<startWindow> {
    
    // Structure describing the ashes.
    struct cinder;
    
    // Structure describing the snow.
    struct snow;
    
    // Type describing the leaf.
    typedef snow leaf;
    
    // Structure describing sand.
    struct sand;
    
public:
    
    // In this method, the race is selected.
    // If the return value is:
    //  1 - northern;
    //  2 - southern;
    //  3 - belowgraun;
    //  4 - forest;
    Sint32 choiceOfRace(graphics &space);
    
    void loadTexture(graphics& space, SDL_Texture*& textureCinder, SDL_Texture*&  textureLeaf, SDL_Texture*& textureSand);
    
    // The method in which the start window is displayed.
    void win(graphics& space);
};

// Structure describing the ashes.
struct startWindow::cinder: public SDL_Point {
    
    // In general, this field is responsible for
    // the particle velocity of the ash.
    // In successor classes, this variable can also
    // act as a speed indicator, but it can also act
    // as a distance store.
    Uint8 length;
};

// Structure describing the snow.
struct startWindow::snow: public startWindow::cinder {
    
    // A field that is a flag for the direction of
    // movement along the x axis.
    bool motion_x;
};

// Structure describing sand.
struct startWindow::sand: public startWindow::cinder {
    
    // A field that is a flag for the direction of
    // movement along the y axis.
    bool motion_y;
};

#endif /* _startWindow_hpp */

