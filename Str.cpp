//
// Created by linus on 11.07.21.
//

#include <iostream>
#include "Str.h"

char Str::charAt(uint64_t index) const {
    if (index >= _len) {
        std::cout << "ERROR: Str::charAt(): index >= _len: Returning null byte." << std::endl;
        return '\0';
    }
    return _cstr[index];
}

Str Str::toStr() const {
    return *this;
}
