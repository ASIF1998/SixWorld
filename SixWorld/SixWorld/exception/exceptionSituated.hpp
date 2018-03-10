//
//  exceptionSituated.hpp
//  SixWorld
//
//  Created by Асиф Мамедов on 10.03.18.
//  Copyright © 2018 Asif Mamedov. All rights reserved.
//

#ifndef exceptionSituated_hpp_
#   define exceptionSituated_hpp_
#       include <exception>
#       include <string>

enum typeExcaption {
  
    TYPEEXCEPTION_WARNING = 0,
    TYPEEXCEPTION_ERROR
};

class exceptionSituated: public std::exception {
    
    char* msg_;
    typeExcaption _excet;
    
public:
    
    // Constructors.
    exceptionSituated(typeExcaption __except) noexcept;
    exceptionSituated(const char* msg__, typeExcaption __except) noexcept;
    exceptionSituated(std::string& obj, typeExcaption __except) noexcept;
    
    // Destructor.
    ~exceptionSituated() noexcept;
    
    // A method that returns an exception type.
    int getTypeException() const noexcept;
    
    // A method that returns a string with a message.
    virtual const char* what() const noexcept;
};

#endif /* exceptionSituated_hpp */
