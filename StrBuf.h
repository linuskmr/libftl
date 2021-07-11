//
// Created by linus on 11.07.21.
//

#ifndef LIBFTL_STRBUF_H
#define LIBFTL_STRBUF_H

#include "Vec.h"
#include "Str.h"

/**
 * A string buffer providing efficient string concatenation.
 */
class StrBuf {
public:
    /**
     * A char vector holding the string of the String Buffer.
     */
    Vec<char> _arr;

    /**
     * Adds str to this StrBuf by adding each char.
     */
    void add(Str str);

    /**
     * Adds one char to this StrBuf.
     */
    void add(char c);

    /**
     * Returns the length of the content.
     */
    uint64_t len() const;

    /**
     * Returns true if the content is empty, i.e. len() == 0. Otherwise returns true.
     */
    bool isEmpty() const;

    /**
     * Converts StrBuf to a string.
     */
    Str toStr() const;
};


#endif //LIBFTL_STRBUF_H
