#include "abstractRace.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "exception/exceptionSituated.hpp"
#include <string>

weapon::~weapon() {
    
    if (imageWeapons_) {
        
        SDL_DestroyTexture(imageWeapons_);
    }
    
    if (imageSoorting_) {
        
        SDL_DestroyTexture(imageSoorting_);
    }
}

abstractRace::abstractRace(graphics &space) {
    
    const char* __name = nullptr;
    
    try {
        
#ifdef __APPLE__
            __name = entryName(space, "/Users/asifmamedov/Desktop/SixWorld/SixWorld/image/images for name input window/com.apple.desktop.admin.png");
#else
            __name = entryName(space, "image/images for name input window/com.apple.desktop.admin.png");
#endif
    } catch (const exceptionSituated& except) {
        
        space.message("Error !!!", except.what());
        return ;
    }
    
    _name = __name;
    delete [] __name;
}

abstractRace::abstractRace(graphics &space, SDL_Rect __imageParametersPersonal): abstractRace(space) {
    
    _imageParametersPersonal = __imageParametersPersonal;
}

abstractRace::~abstractRace() {
    
    if (imagePersonage_) {
        
        SDL_DestroyTexture(imagePersonage_);
    }
    
#ifdef __APPLE__
    delete weapon_;
#else
    
    if (weapon_) {
        
        delete weapon_;
    }
#endif

}

Sint16 abstractRace::getLife() const noexcept {
    
    return _life;
}

std::string& abstractRace::getName() noexcept {
    
    return _name;
}

std::string abstractRace::getName() const noexcept {
    
    return _name;
}

SDL_Rect& abstractRace::getImageParametersPersonal() noexcept {
    
    return _imageParametersPersonal;
}

SDL_Rect abstractRace::getImageParametersPersonal() const noexcept {
    
    return _imageParametersPersonal;
}

Uint8 abstractRace::getNumWeapons() const noexcept {
    
    return _numWeapons;
}

void abstractRace::setPoint(Uint64 __point) noexcept {
    
    _points = __point;
}

void abstractRace::setLife(Sint16 __life) noexcept {
    
    _life = __life;
}

// Static method that provides output of the input line to the screen.
// Return the string entered by the user.
const char* abstractRace::entryName(graphics &space, const char *path) {
    
    // The background.
    SDL_Texture*  backgroundImage = IMG_LoadTexture(space.getRender(), path);
    
    // backgroundImageRect - background parameters (required for display on the window and background animation).
    // fontRace - required to display text
    graphics::imageParameters backgroundImageRect = {{0, 0, 1000, 1000}, {0, 0, 800, 600}}, fontRace = {{0, 0, 0, 0}, {400, 250, 0, 20}};
    
    // motionBackground_x - required for movement on the axis x (backgroundImage).
    // motionBackground_y - required for movement on the axis y (backgroundImage).
    // stay - the variable state of which determines the existence of the program.
    bool motionBackground_x = true, motionBackground_y = true, stay = true;
    
#ifdef __APPLE__
    TTF_Font* font = TTF_OpenFont("/Users/asifmamedov/Desktop/SixWorld/SixWorld/fonts/Space_Mono/SpaceMono-BoldItalic.ttf", 50);
#else
    TTF_Font* font = TTF_OpenFont("fonts/Space_Mono/SpaceMono-BoldItalic.ttf", 50);
#endif
    
    if (!backgroundImage) {
        
        throw exceptionSituated(IMG_GetError(),TYPEEXCEPTION_ERROR);
    }
    
    if (!font) {
        
        throw exceptionSituated(TTF_GetError(),TYPEEXCEPTION_ERROR);
        
    }
    
    // Array, in which the name of the character will be stored character.
    char* name = new char [100];
    name[0] = '\0';
    
    Uint8 characters = 0;
    
    TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE | TTF_STYLE_ITALIC);
    
    // A variable that handles events.
    SDL_Event* event = new SDL_Event;
    
    // Font Color.
    SDL_Color colorText = {0xdc, 0xff, 0xff};
    
    // Create text.
    SDL_Surface* surfaceText = TTF_RenderUTF8_Blended(font, name, colorText);
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(space.getRender(), surfaceText);
    
    while (stay) {
        
        /* --------------------------------------------------- */
        /*                Event handling.                      */
        
        while (SDL_PollEvent(event)) {
            
            switch(event->type) {
                    
                case SDL_TEXTINPUT: {
                    
                    if (characters < 70) {
                        
                        characters++;
                        fontRace.out.w += 10;
                        fontRace.out.x -= 5;
                        strcat(name, event->text.text);
                        surfaceText = TTF_RenderUTF8_Blended(font, name, colorText);
                    }
                    
                    break;
                }
                    
                case SDL_KEYDOWN: {
                    
                    if (event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE && characters) {
                        
                        characters--;
                        fontRace.out.w -= 10;
                        fontRace.out.x += 5;
                        name[characters] = '\0';
                        surfaceText = TTF_RenderUTF8_Blended(font, name, colorText);
                    }
                    
                    break;
                }
                    
                case SDL_KEYUP: {
                    
                    if (event->key.keysym.scancode == SDL_SCANCODE_RETURN) {
                        
                        stay = false;
                    }
                    
                    break;
                }
            }
        }
        /* --------------------------------------------------- */
        
        // Realization of movement.
        if (backgroundImageRect.in.x + backgroundImageRect.in.w > 2880 || backgroundImageRect.in.x < 0) {
            
            motionBackground_x = !motionBackground_x;
        }
        
        if (backgroundImageRect.in.y + backgroundImageRect.in.h > 1880 || backgroundImageRect.in.y < 0) {
            
            motionBackground_y = !motionBackground_y;
        }
        
        backgroundImageRect.in.x += (motionBackground_x ? 1 : -1);
        backgroundImageRect.in.y += (motionBackground_y ? 1 : -1);
        
        if (surfaceText) {
            
            SDL_DestroyTexture(textureText);
            textureText = SDL_CreateTextureFromSurface(space.getRender(), surfaceText);
            fontRace.in.h = surfaceText->clip_rect.h;
            fontRace.in.w = surfaceText->clip_rect.w;
            SDL_FreeSurface(surfaceText);
            surfaceText = nullptr;
        }
        
        space.copy(backgroundImage, &backgroundImageRect.in, &backgroundImageRect.out);
        space.copy(textureText, &fontRace.in, &fontRace.out);
        space.present();
    }
    
    space.destroy("%t %t", backgroundImage, textureText);
    
    delete event;
    
    return name;
}






