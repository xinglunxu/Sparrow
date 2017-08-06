//
//  System.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/20/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef System_hpp
#define System_hpp

#include <stdio.h>
#include "World.hpp"

using namespace std;

class System{
public:
    virtual void Update()=0;
    int worldId;
protected:
//    World w;
};


#endif /* System_hpp */
