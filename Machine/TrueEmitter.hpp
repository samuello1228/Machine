//
//  TrueEmitter.hpp
//  Machine
//
//  Created by Samuel Lo on 31/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef TrueEmitter_hpp
#define TrueEmitter_hpp

#include "Detector.hpp"

class TrueEmitter : public Detector
{
public:
    FundamentalBlock* host;
    TrueEmitter(unsigned int newPriority, const RadioEmitter& newEmitter, FundamentalBlock* newHost) : Detector(newPriority,newEmitter), host(newHost)
    {
        emitter.isEmitting = true;
    }
    
    FundamentalBlock* getHost();
    void Do();
};

#endif /* TrueEmitter_hpp */
