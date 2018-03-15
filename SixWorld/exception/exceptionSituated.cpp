//
//  exceptionSituated.cpp
//  SixWorld
//
//  Created by Асиф Мамедов on 10.03.18.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#include "exceptionSituated.hpp"

exceptionSituated::exceptionSituated(typeExcaption __except) noexcept:
                                        _excet(__except), msg_(nullptr), std::exception() {
    
    
}

exceptionSituated::exceptionSituated(const char* msg__, typeExcaption __except) noexcept:
                                                              exceptionSituated(__except) {
    
    msg_ = new char [strlen(msg__) + 40];
    sprintf(msg_, (_excet == TYPEEXCEPTION_ERROR) ? "Error: %s" : "Warning: %s", msg__);
}

exceptionSituated::exceptionSituated(std::string& obj, typeExcaption __except) noexcept:
                                                exceptionSituated(obj.c_str(), __except)  {
            
}

exceptionSituated::~exceptionSituated() noexcept {
    
#ifndef __APPLE__
    if (msg_) {
        
        delete [] msg_;
    }
#elseif
    delete [] msg_;
#endif
}

// A method that returns an exception type.
int exceptionSituated::getTypeException() const noexcept {
    
    return _excet;
}

// A method that returns a string with a message.
const char* exceptionSituated::what() const noexcept {
    
    return msg_;
}
