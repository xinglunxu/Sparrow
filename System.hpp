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
#include <iostream>

class System{
public:
    virtual void Update()=0;
    int worldId;
    System(int worldId){
        this->worldId = worldId;
    }
private:
    System();
};


#endif /* System_hpp */
