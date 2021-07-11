//
// Created by linus on 11.07.21.
//

#include "IntWrapper.h"

Str IntWrapper::toStr() const {
    char* buf = static_cast<char*>(malloc(33 * sizeof(char)));
    sprintf(buf, "%d", value);
    Str s(buf);
    return s;
}
