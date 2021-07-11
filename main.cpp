#include <iostream>
#include <unistd.h>
#include <cstring>
#include <functional>

#include "Str.h"
#include "Vec.h"
#include "StrBuf.h"
#include "IntWrapper.h"
#include "StrJoin.h"


/**
 * Prints value to stdout.
 */
template<class T>
void print(T value) {
    Str value_str = value.toStr();
    write(1, value_str._cstr, value_str._len);
}

/**
 * Converts a value to a str.
 */
template<class T>
Str vecToStr(Vec<T> arr) {
    StrJoin strjoin(", ");
    for (int i = 0; i < arr._len; i++) {
        // Get element and append its str representation to the buffer
        T *element = arr.get(i);
        Str elementStr = element->toStr();
        strjoin.add(elementStr);
    }
    return strjoin.toStr();
}

int main() {
    std::cout << "Str" << std::endl;
    Str str("Hallo");
    std::cout << std::endl;

    std::cout << "print" << std::endl;
    print(str);
    std::cout << std::endl;

    std::cout << "IntWrapper" << std::endl;
    IntWrapper iw(42);
    print(iw.toStr());
    std::cout << std::endl;

    std::cout << "StrBuf" << std::endl;
    StrBuf strbuf;
    strbuf.add(str);
    print(strbuf.toStr());
    std::cout << std::endl;

    std::cout << "Create Vec" << std::endl;
    Vec<IntWrapper> v;
    for (int i = 0; i < 10; i++) {
        v.push(i);
    }

    std::cout << "Update element from vec" << std::endl;
    *v.get(9) = 42;
    assert(v.get(9)->value == IntWrapper(42).value);
    assert(v.get(10) == nullptr);

    std::cout << "vecToStr" << std::endl;
    print(vecToStr(v));
    std::cout << std::endl;
}
