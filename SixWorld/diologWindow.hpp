#ifndef _diologWindow_hpp_
#   define _diologWindow_hpp_

// The union, by means of which it is
// determined which color will become transparent.
enum transparenColor {
    
    SW_NOTTRANSPARENT = 0x00000001,
    SW_TRANSPARENTCOLOR_WHITE = 0xffffffff,
    SW_TRANSPARENTCOLOR_BLACK = 0xff000000
};

#       include "diologWindow.inl"
#endif
