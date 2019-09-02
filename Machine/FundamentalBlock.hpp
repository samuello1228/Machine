//
//  FundamentalBlock.hpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef FundamentalBlock_hpp
#define FundamentalBlock_hpp

#include <map>
#include <string>

#include "Block.hpp"
#include "Action.hpp"
#include "Detector.hpp"
class Module;

class FundamentalBlock : public Block
{
    public:
    map<string,unsigned int> properties_UI;
    //direction: 1 = north, 2 = east, 3 = south, 4 = west
    
    map<string,Module*> module;
    
    FundamentalBlock(const string& newName);
    ~FundamentalBlock();
    
    void addPropertiesUI(const string&, unsigned int value);
    void addEmitter(unsigned int newPriority, string module_name, const RadioEmitter& newEmitter);
    void addReceiver(unsigned int newPriority, string module_name, const RadioReceiver& newReceiver);
    
    void PrintMap(unsigned int indentation = 0);
    virtual void PrintExtraProperties(unsigned int indentation = 0);
    
    Block* getTierBlock(unsigned int tier);
    bool isControlCenter();
    void registerAll();
    
    unsigned int getPriority();
    void execute(CompositeBlock* topmost, bool isPrint);
};

#endif /* FundamentalBlock_hpp */
