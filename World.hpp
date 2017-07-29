//
//  World.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/20/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <list>
#include "System.hpp"

using namespace std;

class World{
public:
    void Run();
    World();
    template <typename T>
    void AddSystem();

private:
    void Update();
    list<System*> systems;
    
};

template <typename T>
void World::AddSystem(){
    systems.insert(systems.end(), new T());
}

#endif /* World_hpp */
