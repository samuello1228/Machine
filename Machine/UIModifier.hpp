//
//  UIModifier.hpp
//  Machine
//
//  Created by Samuel Lo on 5/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef UIModifier_hpp
#define UIModifier_hpp

#include "UIntergerBlock.hpp"

class UIModifier : public UIntergerBlock
{
    public:
    string key;
    
    UIModifier(const string& newName, unsigned int newNumber, unsigned int newDirection, const string& newKey) : UIntergerBlock(newName, newNumber), key(newKey)
    {
        properties_UI["direction"] = newDirection;
    }
    
    void PrintExtraProperties(unsigned int indentation = 0);
};

#endif /* UIModifier_hpp */
