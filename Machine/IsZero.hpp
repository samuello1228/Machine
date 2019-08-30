//
//  IsZero.hpp
//  Machine
//
//  Created by Samuel Lo on 6/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef IsZero_hpp
#define IsZero_hpp

#include "Detector.hpp"
class UIntergerBlock;

class IsZero : public Detector
{
public:
    UIntergerBlock* host;
    IsZero(unsigned int newPriority, const RadioEmitter& newEmitter, UIntergerBlock* newHost) : Detector(newPriority,newEmitter), host(newHost) {}
    
    FundamentalBlock* getHost();
    void Do();
};

#endif /* IsZero_hpp */
