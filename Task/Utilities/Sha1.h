// Sha1.h
// Task/Utilities
// CIS 22C F2016: Matthew Tso

#ifndef TASK_SHA1_H
#define TASK_SHA1_H

#include <string>
#include <stdint.h>

using namespace std;

namespace task {
    
    // Returns a 40 hex-char string of the input's SHA1 hash.
    string sha_1(const string& input);
}

#endif /* Hashbrown.h */
