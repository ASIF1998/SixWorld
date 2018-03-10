#include "abstractRace.hpp"

// Default construction.
abstractRace::abstractRace(): _life(0), _damage(0), _bonuses(0), _numParameters(1),
                                                        _numImage(0), animationImage_(nullptr) {
    
    _name = "No name";
    in = new SDL_Rect [1];
    out = in = new SDL_Rect [1];
}
