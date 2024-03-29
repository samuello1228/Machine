//
//  Action.hpp
//  Machine
//
//  Created by Samuel Lo on 24/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef Action_hpp
#define Action_hpp

#include "Module.hpp"

class RadioReceiver
{
public:
    unsigned int tier;
    unsigned int channel;
    
    RadioReceiver(unsigned int newTier, unsigned int newChannel) : tier(newTier), channel(newChannel) {}
};

class Action : public Module
{
public:
    RadioReceiver receiver;
    
    Action(unsigned int newPriority, const RadioReceiver& newReceiver) : Module(newPriority), receiver(newReceiver) {}
    
    void Print();
    bool getChannelSignal();
};

#endif /* Action_hpp */
