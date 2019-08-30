//
//  CompositeBlock.hpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef CompositeBlock_hpp
#define CompositeBlock_hpp

#include <set>

#include "Block.hpp"
class ControlCenter;

class CompositeBlock : public Block
{
    public:
    unsigned int size;
    ControlCenter* controlCenter;
    set<Block*> Composition;
    
    CompositeBlock(const string& newName, unsigned int newSize);
    ~CompositeBlock();
    
    void PrintMap(unsigned int indentation = 0);
    
    bool checkCoordinate(Coordinate newCoordinate);
    void addControlCenter(const Coordinate& newCoordinate, ControlCenter* newControlCenter);
    void addBlock(unsigned int newPriority, const Coordinate& newCoordinate, Block* newBlock);
    
    void registerAll();
    
    unsigned int getPriority();
    void execute(CompositeBlock* topmost, bool isPrint);
};

#endif /* CompositeBlock_hpp */
