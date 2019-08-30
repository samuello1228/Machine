//
//  UIWriter.cpp
//  Machine
//
//  Created by Samuel Lo on 4/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>

#include "UIWriter.hpp"
#include "UIModifier.hpp"

FundamentalBlock* UIWriter::getHost()
{
    return host;
}

void UIWriter::Do()
{
    if(getChannelSignal())
    {
        ForwardBlockOutput output = Module::getForwardBlock(host);
        if(output.isOutOfBoundary)
        {
            cout<<"Error: the forward block is outside the boundary."<<endl;
            return;
        }
        else if(output.isEmpty)
        {
            cout<<"Error: the forward block is empty space."<<endl;
            return;
        }
        else
        {
            FundamentalBlock* forwardBlock = output.existingBlock;
            string& key = host->key;
            std::map<string,unsigned int>::iterator it = forwardBlock->properties_UI.find(key);
            if(it == forwardBlock->properties_UI.end())
            {
                cout<<"Error: cannot find the property \""<<key<<"\" in the forward block."<<endl;
                return;
            }
            else
            {
                it->second = host->properties_UI["UInterger"];
                return;
            }
        }
    }
}
