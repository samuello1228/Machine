//
//  Detector.hpp
//  Machine
//
//  Created by Samuel Lo on 24/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef Detector_hpp
#define Detector_hpp

#include "Module.hpp"

class Detector : public Module
{
public:
    RadioEmitter emitter;
    
    Detector(unsigned int newPriority, const RadioEmitter& newEmitter) : Module(newPriority), emitter(newEmitter) {}
    
    void Print();
};

#endif /* Detector_hpp */