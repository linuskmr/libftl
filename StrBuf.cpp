//
// Created by linus on 11.07.21.
//

#include <iostream>
#include "StrBuf.h"
#include "Str.h"

void StrBuf::add(Str str) {
    for (uint64_t i = 0; i < str._len; i++) {
        add(str.charAt(i));
    }
}

void StrBuf::add(char c) {
    _arr.push(c);
    // Ensure null-terminated string
    _arr._data[_arr._len] = '\0';
}

Str StrBuf::toStr() const {
    // _arr._data ist always null-terminated, see `void StrBuf::add(char c)`.
    Str s(_arr._data);
    return s;
}

bool StrBuf::isEmpty() const {
    return len() == 0;
}

uint64_t StrBuf::len() const {
    return _arr._len;
}
