//
//  Channel.hpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef Channel_hpp
#define Channel_hpp

class Channel
{
    public:
    unsigned int tier;
    unsigned int channel;
    
    void Print();
    Channel(unsigned int newTier, unsigned int newChannel);
};

#endif /* Channel_hpp */
