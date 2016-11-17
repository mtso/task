// Sha1.h
// Task
// CIS 22C F2016: Matthew Tso
//
// SHA-1 function that takes a string as input and
// returns a string containing the input's hash
// represented as 40 hex characters.
//
// The algorithm is taken from:
// http://www.metamorphosite.com/one-way-hash-encryption-sha1-data-software

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
