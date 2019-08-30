//
//  Module.hpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef Module_hpp
#define Module_hpp

#include <vector>
using namespace std;

#include "Coordinate.hpp"
#include "Channel.hpp" //For all derived class of "Module"
class FundamentalBlock;
class CompositeBlock;

struct ForwardBlockOutput
{
    //status
    bool isOutOfBoundary;
    bool isEmpty;
    
    //For existing block
    FundamentalBlock* existingBlock = nullptr;
    
    //For empty space, to create new block
    CompositeBlock* MotherBlock = nullptr;; //the existing mother block
    vector<Coordinate> coordinate; //the coordinate under the existing mother block
    //the first element is the bottommost coordinate
};

class Module
{
    public:
    unsigned int priority;
    
    Module(unsigned int newPriority) : priority(newPriority) {}
    virtual ~Module() {};
    
    virtual void Print() = 0;
    virtual FundamentalBlock* getHost() = 0;
    virtual void Do() = 0;
    
    static ForwardBlockOutput getForwardBlock(FundamentalBlock* host);
};

#endif /* Module_hpp */
