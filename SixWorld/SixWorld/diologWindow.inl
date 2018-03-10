#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "graphics.hpp"

template <class type>
class diologWindow {
    
protected:
    
    // Array of pointers to the background image.
    SDL_Texture **field_;
    
    // Array of pointers to an image with animation.
    SDL_Texture **animationElement_;
    
    // Number of background images.
    size_t _numField;
    
    // Number of animated images.
    size_t _numIlustration;
    
    // A method that loads images, making the white color transparent.
    SDL_Texture** convertTexture (const char* path_, size_t num_, SDL_Renderer *render_, transparenColor flag) {
        
        // An array of pointers to objects of type SDL_Surface.
        // Required for discoloration of a specific color.
        SDL_Surface** image = new SDL_Surface* [num_];
        
        // An array of pointers to objects of type SDL_Texture.
        // Further objects of type SDL_Surface will be transformed
        // to type SDL_Texture (with a transparent background).
        SDL_Texture** tex = new SDL_Texture* [num_];
        
        // Necessary for image search.
        char search[100];
        
        for (size_t i = 0; i < num_; i++ ) {
            
            //Building the path to the image.
            sprintf(search, "%s%u.png", path_, (unsigned int) i);
            
            // Uploading image.
            image[i] = IMG_Load(search);
            
            // If the image does not load, then throw an exception.
            if (!image[i]) {
                
                throw std::string ("Error: ") += IMG_GetError();
            }
            
            if (flag != SW_NOTTRANSPARENT) {
                
                // Make the color transparent.
                SDL_SetColorKey(image[i], SDL_TRUE, flag);
            }
            
            // Create a texture.
            tex[i] = SDL_CreateTextureFromSurface(render_, image[i]);
        }
        
        // Clean memory.
        for (size_t i = 0; i < num_; i++) {
            
            SDL_FreeSurface(image[i]);
        }
        
        delete [] image;
        
        return tex;
    }
    
    
    SDL_Texture** loadImage(const char* path_, size_t num_, SDL_Renderer *render_) {
        
        // An array of pointers to objects of type SDL_Texture.
        SDL_Texture** tex = new SDL_Texture* [num_];
        
        // Necessary for image search.
        char search[100];
        
        for (size_t i = 0; i  <num_; i++) {
            
            // Building the path to the image.
            sprintf(search, "%s%u.png", path_, (unsigned int) i);
            
            // uploading image
            tex[i] = IMG_LoadTexture(render_, search);
            
            // If the image does not load, then throw an exception.
            if (!tex[i]) {
                
                throw std::string ("Error: ") += IMG_GetError();
            }
        }
        
        return tex;
    }
    
public:
    
    diologWindow(const char *pathField__, const char *pathAnim__, size_t __numField, size_t __numIlustration, SDL_Renderer *redner_, transparenColor flag) {
        
        _numField = __numField;
        _numIlustration = __numIlustration;
        
        try {
            
            field_ = (_numField ? loadImage(pathField__, _numField, redner_) : nullptr);
            animationElement_ = (_numIlustration ? convertTexture(pathAnim__, _numIlustration, redner_, flag) : nullptr);
            
        } catch (std::string err) {
            
            std::cerr << err << std::endl;
            exit(-1);
        }
    }
    
    diologWindow(SDL_Texture** field__, SDL_Texture** animationElement__, size_t __numField, size_t __numIlustration) {
        
        field_ = field__;
        animationElement_ = animationElement__;
        _numField = __numField;
        _numIlustration = __numIlustration;
    }
    
    ~diologWindow() {
        
        if (_numField) {
            
            for (size_t i = 0; i < _numField; i++) {
                
                SDL_DestroyTexture(field_[i]);
            }
            
            delete [] field_;
        }
        
        if (_numIlustration) {
            
            for (size_t i = 0; i < _numIlustration; i++) {
                
                SDL_DestroyTexture(animationElement_[i]);
            }
            
            delete [] animationElement_;
        }
    }
    
    void win(graphics& space) {

        static_cast<type*> (this)->win(space);
    }
};
