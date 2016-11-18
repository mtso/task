//
//  Djb2.hpp
//  TaskApp
//
//  Created by Matthew Tso on 11/17/16.
//  Copyright © 2016 De Anza. All rights reserved.
//

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
