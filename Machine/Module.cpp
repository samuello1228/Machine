//
//  Module.cpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include "Channel.hpp"
#include "Module.hpp"
#include "CompositeBlock.hpp"
#include "FundamentalBlock.hpp"

ForwardBlockOutput Module::getForwardBlock(FundamentalBlock* host)
{
    ForwardBlockOutput output;
    
    //Find the coordinate of the forward block
    //The algorithm is like adding one in decimal integer.
    Block* SonBlock = host;
    CompositeBlock* MotherBlock = SonBlock->MotherBlock;
    vector<Coordinate> coordinate; //record the path of coordinate
    unsigned int direction = host->properties_UI["direction"];
    while(true)
    {
        unsigned int x = SonBlock->coordinate.x;
        unsigned int y = SonBlock->coordinate.y;
        
        if(direction == 1)
        {
            //North
            if(y != MotherBlock->size)
            {
                y++;
                coordinate.push_back(Coordinate(x,y));
                break;
            }
            else
            {
                y = 1;
                coordinate.push_back(Coordinate(x,y));
            }
        }
        
        SonBlock = MotherBlock;
        MotherBlock = SonBlock->MotherBlock;
        if(MotherBlock == nullptr)
        {
            //the forward block is outside the boundary
            output.isOutOfBoundary = true;
            output.isEmpty = false;
            return output;
        }
    }
    
    //the forward block is inside the boundary
    output.isOutOfBoundary = false;
    
    //find the bottommost existing mother block
    while(true)
    {
        bool isFound = false;
        Coordinate newCoordinate = coordinate.back();
        for(set<Block*>::iterator it = MotherBlock->Composition.begin(); it!=MotherBlock->Composition.end(); it++)
        {
            if( (*it)->coordinate.isEqual(newCoordinate) )
            {
                isFound = true;
                coordinate.pop_back();
                MotherBlock = dynamic_cast<CompositeBlock*>(*it);
                
                if(!MotherBlock)
                {
                    //the forward block exists
                    output.isEmpty = false;
                    output.existingBlock = dynamic_cast<FundamentalBlock*>(*it);
                    return output;
                }
            }
        }
        
        if(!isFound)
        {
            //the forward block is empty
            output.isEmpty = true;
            output.MotherBlock = MotherBlock;
            output.coordinate = coordinate;
            return output;
        }
    }
}
