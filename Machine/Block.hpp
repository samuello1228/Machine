//
//  Block.hpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp
#include <map>
#include <string>
using namespace std;

#include <iostream>

#include "Coordinate.hpp"
class CompositeBlock;
class RadioEmitter;

class Block
{
    public:
    string name;
    unsigned int tier;
    CompositeBlock* MotherBlock;
    Coordinate coordinate;
    map<unsigned int,RadioEmitter*> radioData;
    
    Block();
    virtual ~Block() {};
    
    virtual void PrintMap(unsigned int indentation) = 0;
    virtual bool isControlCenter() = 0;
    virtual void registerAll() = 0;
    
    virtual unsigned int getPriority() = 0;
    virtual void execute(CompositeBlock* topmost, bool isPrint) = 0;
};

#endif /* Block_hpp */
