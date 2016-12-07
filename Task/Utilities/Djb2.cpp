// Djb2.cpp
// Task/Utilities
// CIS 22C F2016: Mr. Yagni

#include "Djb2.h"

unsigned long task::djb_2(unsigned char *input)
{
    unsigned long hash = 5381; // Magic djb constant, UNTESTED in this environment
    int character;
    
    // When the null terminator is assigned into c,
    // the statement evaluates to 0
    while ((character = *(input++)) != 0) {
        
		hash = hash * 33 + character;
		// Same as:
        // hash += (hash << 5) + character;
    }
    
    return hash;
}
