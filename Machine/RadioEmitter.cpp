//
//  RadioEmitter.cpp
//  Machine
//
//  Created by Samuel Lo on 24/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>
using namespace std;

#include "RadioEmitter.hpp"

RadioEmitter::RadioEmitter(unsigned int newTier, unsigned int newChannel, bool newIsEmitting)
{
    tier = newTier;
    channel = newChannel;
    isEmitting = newIsEmitting;
}

void RadioEmitter::Print()
{
    unsigned int extractedExpr = channel;
    cout<<"Emitter:(Tier:"<<tier<<", Channel:"<<extractedExpr<<", isEmitting:"<<isEmitting<<")";
}
