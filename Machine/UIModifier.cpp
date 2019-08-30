//
//  UIModifier.cpp
//  Machine
//
//  Created by Samuel Lo on 5/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>

#include "UIModifier.hpp"

void UIModifier::PrintExtraProperties(unsigned int indentation)
{
    cout<<string(indentation, ' ');
    cout<<"Extra Properties: "<<endl;
    
    cout<<string(indentation+2, ' ');
    cout<<"key: "<<key<<endl;
}
