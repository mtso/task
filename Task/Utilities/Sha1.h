// Sha1.h
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_SHA1_H
#define TASK_SHA1_H

#include <string>
#include <stdint.h>

using namespace std;

namespace task {
    
    // Returns a 40 hex-char string of the input's SHA1 hash.
    std::string sha_1(const std::string& input);
}

#endif /* Hashbrown.h */
