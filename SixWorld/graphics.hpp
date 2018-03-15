#ifndef _graphics_hpp_
#   define _graphics_hpp_
#       include <SDL2/SDL.h>
#       include <SDL2/SDL_image.h>
#       include <string>
#       include "exception/exceptionSituated.hpp"
#       include <SDL2/SDL_ttf.h>

class graphics {
    
     // Pointer to the window.
    SDL_Window *window_;
    
    // Pointer to the renderer.
    SDL_Renderer *render_;
        
    // Flag initialization.
    static bool initialization_;
    
public:
    
    struct imageParameters;
    
    // Constructor.
    graphics();
    
    // Destructor.
    ~graphics();
    
    graphics(const graphics&) = delete;
    void operator= (const graphics&) = delete;
    
    // Return point window.
    SDL_Window* getWindow();
    
    // Return point renderer.
    SDL_Renderer* getRender();
    
    // Set color renderer.
    void colorRender (Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    
    // Clear display.
    void clear();
    
    // Output message.
    void message(const char *titel, const char *text);
    
    // Output message.
    int message(const char *titel, const char *text, Uint8 numButtons, ...);
    
    // Copying of a fragment of a texture in a render.
    void copy(SDL_Texture* tex, const SDL_Rect* src, const SDL_Rect* dst);
    
    // Change the buffer and shown
    // the contents of the buffer.
    void present();
    
    // Cleaning.
    void destroy(const char* str, ...);
    
    // Creating a texture.
    SDL_Texture* createTexture(SDL_Surface* surface);
    
    void setPoint(int x, int y);
    
    // recource SDL initialization.
    static void init() {
        
        if (!initialization_) {
            
            if (SDL_Init(SDL_INIT_EVERYTHING)) {
                
                throw std::string ("Error: ") += SDL_GetError();
            }
            
            if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)) {
                
                throw exceptionSituated (IMG_GetError(), TYPEEXCEPTION_ERROR);
            }
            
            if (TTF_Init() < 0) {
                
                throw exceptionSituated (TTF_GetError(), TYPEEXCEPTION_ERROR);
            }
            
            initialization_ = true;
        }
    }
    
    // liberition recource SDL.
    static void quit() {
        
        if (initialization_) {
            
            IMG_Quit();
            SDL_Quit();
            TTF_Quit();
            initialization_ = false;
        }
    }
};

struct graphics::imageParameters {
    
    SDL_Rect in, out;
};

#endif /* _graphics_hpp_ */
