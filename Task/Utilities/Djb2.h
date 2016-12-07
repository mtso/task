// Djb2.h
// Task/Utilities
// CIS 22C F2016: Mr. Yagni

/*
 djb2
 
 this algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c. another version of this algorithm (now favored by bernstein) uses xor: hash(i) = hash(i - 1) * 33 ^ str[i]; the magic of number 33 (why it works better than many other constants, prime or not) has never been adequately explained.
 
 unsigned long
 hash(unsigned char *str)
 {
 unsigned long hash = 5381;
 int c;
 
 while (c = *str++)
 hash = ((hash << 5) + hash) + c; // hash * 33 + c
 
 return hash;
 }
/**/

#ifndef TASK_DJB2_H
#define TASK_DJB2_H

namespace task {
    
    /**
     * djb2 hash algorithm
     * @returns unsigned long hash value of input unsigned char* string
     */
    unsigned long djb_2(unsigned char *input);
    
}

#endif /* Djb2_hpp */
