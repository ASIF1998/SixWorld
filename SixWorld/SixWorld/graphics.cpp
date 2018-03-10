#include "graphics.hpp"
#include <iostream>
#include <cstdarg>
#include <string>

bool graphics::initialization_ = false;

// Constructor.
graphics::graphics() {
    
    // Create window.
    window_ = SDL_CreateWindow("Six world", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                        SDL_WINDOW_SHOWN);
    
    // Create renderer.
    render_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    // Check for the pressence of a window and renderer.
    if (!window_ || !render_) {
        
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
}

// Destructor.
graphics::~graphics() {
    
    if (window_) {
        
        SDL_DestroyWindow(window_);
    }
    
    if (render_) {
        
        SDL_DestroyRenderer(render_);
    }
}

// Return point window.
SDL_Window* graphics::getWindow() {
    
    return window_;
}

// Return point renderer.
SDL_Renderer* graphics::getRender() {
    
    return render_;
}

// Set color renderer.
void graphics::colorRender(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    
    SDL_SetRenderDrawColor(render_, r, g, b, a);
}

// Clear display.
void graphics::clear() {
    
    SDL_RenderClear(render_);
}

// Output message.
void graphics::message(const char *titel, const char *text) {
    
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, titel, text, window_);
}

// Output message.
int graphics::message(const char *titel, const char *text, Uint8 numButtons, ...) {
    
    // Этот тип используется в качестве параметра для макросов, определенных в
    // <Cstdarg> чтобы получить дополнительные аргументы функции.
    va_list ap;
    
    // Инициализация указателя ap.
    va_start(ap, &numButtons);
    
    // Указатель на кнопки.
    SDL_MessageBoxButtonData* buttons = new SDL_MessageBoxButtonData [numButtons];
    int buttonValue = 0;
    
    // Инициализируем кнопки.
    for (size_t i = 0; i < numButtons; i++, buttonValue++) {
            
        buttons[i].flags = (numButtons - i != 1 ? 0 : SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
        buttons[i].buttonid = buttonValue;
        buttons[i].text = va_arg(ap, const char*);
    }
    
    // Создаём окошко с сообщением.
    SDL_MessageBoxData messageBoxData = {
        
        SDL_MESSAGEBOX_INFORMATION,
        nullptr,
        titel,
        text,
        numButtons,
        buttons,
        nullptr
    };
    
    // Выводим окошко с сообщенеим.
    if (SDL_ShowMessageBox(&messageBoxData, &buttonValue) < 0) {
        
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    
    
    va_end(ap);
    
    delete [] buttons;
    
    return buttonValue;
}

// Copying of a fragment of a texture in a render.
void graphics::copy(SDL_Texture *tex, const SDL_Rect* src, const SDL_Rect* dst) {
    
    SDL_RenderCopy(render_, tex, src, dst);
    
}

// Change the buffer and shown
// the contents of the buffer.
void graphics::present() {
    
    SDL_RenderPresent(render_);
}

// Cleaning.
void graphics::destroy(const char *str, ...) {
    
    Uint32 size = static_cast<Uint32>(strlen(str));
    
    // Этот тип используется в качестве параметра для макросов, определенных в
    // <Cstdarg> чтобы получить дополнительные аргументы функции.
    va_list ap;
    
    // Инициализация указателя ap.
    va_start(ap, &str);
    
    for (size_t i = 0; i < size; i++) {
        
        if (str[i] == '%') {

            switch (str[i + 1]) {
                    
                case 't': {
                    
                    SDL_DestroyTexture(va_arg(ap, SDL_Texture*));
                    break;
                }
                    
                case 's': {
                    
                    SDL_FreeSurface(va_arg(ap, SDL_Surface*));
                    break;
                }
            }
        }
    }
    
    va_end(ap);
}

// Creating a texture.
SDL_Texture* graphics::createTexture(SDL_Surface *surface) {
    
    if (!surface) {
        
        throw exceptionSituated ("The pointer to the surface is empty.", TYPEEXCEPTION_WARNING);
    }
    
    return SDL_CreateTextureFromSurface(render_, surface);
}

void graphics::setPoint(int x, int y) {
    
    SDL_RenderDrawPoint(render_, x, y);
}
