#ifndef _abstractRace_hpp_
#   define _abstractRace_hpp_
#     include <SDL2/SDL.h>
#     include <string>
#     include <iostream>
#     include "graphics.hpp"

// Base class for weapons.
struct weapon {
  
    SDL_Texture* imageWeapons_, *imageSoorting_;
    SDL_Rect _locationWeapon, _locationShoorting;
    
    // Number of damage.
    Uint8 _damage;
    
    weapon() = default;
    virtual ~weapon();
    
    // Method that returns the speed of the projectile.
    virtual Uint8 getSpeed() = 0;
    
    // Methods that return a pointer to the texture of weapons and shells.
    SDL_Texture* getWeapons();
    SDL_Texture* getShoorting();
    
protected:
    
    // Methods that loads the image of weapons and shells.
    virtual SDL_Texture* getImageWeapons() = 0;
    virtual SDL_Texture* getImageShoorting() = 0;
};

// Base class of the character.
class abstractRace {
    
    // Name personage.
    std::string _name;
    
    // The field in which the collected points will be stored.
    Uint64 _points;
    
    // The field in which the number of player lives is stored.
    Sint16 _life;
    
    // Character photo options.
    SDL_Rect _imageParametersPersonal;
    
    // Pointer to the displayed texture of the character.
    SDL_Texture* imagePersonage_;
    
    // Pointer to weapons.
    weapon* weapon_;
    
    // Number weapons.
    Uint8 _numWeapons;
    
protected:

    abstractRace(graphics &space);
    abstractRace(graphics &space, SDL_Rect __imageParametersPersonal);
    
    // The method that loads the character image.
    virtual SDL_Texture* loadImagePersonage() noexcept = 0;
    
    // Static method that provides output of the input line to the screen.
    // Return the string entered by the user.
    static const char* entryName(graphics &space, const char* path);
    
public:
    
    virtual ~abstractRace();
    
    // Heathers.
    Sint16 getLife() const noexcept;
    std::string& getName() noexcept;
    std::string getName() const noexcept;
    SDL_Rect& getImageParametersPersonal() noexcept;
    SDL_Rect getImageParametersPersonal() const noexcept;
    Uint8 getNumWeapons() const noexcept;
    
    // Setters.
    void setPoint(Uint64 __point) noexcept;
    void setLife(Sint16 __life) noexcept;
};


#endif /* _abstractRace_hpp_ */
