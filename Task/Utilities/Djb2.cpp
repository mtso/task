//
//  Djb2.cpp
//  TaskApp
//
//  Created by Matthew Tso on 11/17/16.
//  Copyright © 2016 De Anza. All rights reserved.
//

#include "Djb2.h"

unsigned long task::djb_2(unsigned char *input)
{
    unsigned long hash = 5381; // Magic djb constant, UNTESTED
    int character;
    
    // When the null terminator is assigned into c,
    // the statement evaluates to 0
    while ((character = *(input++)) != 0) {
        
		hash = hash * 33 + character;
        // hash += (hash << 5) + character;
    }
    
    return hash;
}
