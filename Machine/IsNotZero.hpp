//
//  IsNotZero.hpp
//  Machine
//
//  Created by Samuel Lo on 5/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef IsNotZero_hpp
#define IsNotZero_hpp

#include "Detector.hpp"
class UIntergerBlock;

class IsNotZero : public Detector
{
    public:
    UIntergerBlock* host;
    
    IsNotZero(unsigned int newPriority, const RadioEmitter& newEmitter, UIntergerBlock* newHost) : Detector(newPriority,newEmitter), host(newHost) {}
    
    FundamentalBlock* getHost();
    void Do();
};

#endif /* IsNotZero_hpp */
