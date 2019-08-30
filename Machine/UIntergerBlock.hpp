//
//  UIntergerBlock.hpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef UIntergerBlock_hpp
#define UIntergerBlock_hpp

#include "FundamentalBlock.hpp"

class UIntergerBlock : public FundamentalBlock
{
    public:
    
    UIntergerBlock(const string& newName, unsigned int newNumber) : FundamentalBlock(newName)
    {
        properties_UI["UInterger"] = newNumber;
    }
};

#endif /* UIntergerBlock_hpp */
