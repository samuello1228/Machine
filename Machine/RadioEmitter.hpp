//
//  RadioEmitter.hpp
//  Machine
//
//  Created by Samuel Lo on 24/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef RadioEmitter_hpp
#define RadioEmitter_hpp

class RadioEmitter
{
public:
    unsigned int tier;
    unsigned int channel;
    bool isEmitting;
    
    void Print();
    RadioEmitter(unsigned int newTier, unsigned int newChannel, bool newIsEmitting);
};

#endif /* RadioEmitter_hpp */
