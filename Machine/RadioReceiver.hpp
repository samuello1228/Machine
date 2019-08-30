//
//  RadioReceiver.hpp
//  Machine
//
//  Created by Samuel Lo on 24/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef RadioReceiver_hpp
#define RadioReceiver_hpp

class RadioReceiver
{
public:
    unsigned int tier;
    unsigned int channel;
    
    void Print();
    RadioReceiver(unsigned int newTier, unsigned int newChannel);
};

#endif /* RadioReceiver_hpp */
