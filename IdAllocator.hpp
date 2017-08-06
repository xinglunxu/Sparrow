//
//  IdAllocator.hpp
//  Sparrow
//
//  Created by 许兴伦 on 8/6/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef IdAllocator_hpp
#define IdAllocator_hpp

#include <stdio.h>
#include <list>

using namespace std;

class IdAllocator{
private:
    unsigned int curId;
    list<int> retIntList;
public:
    int GetId();
    void ReturnId(int i);
    IdAllocator();
};

#endif /* IdAllocator_hpp */
