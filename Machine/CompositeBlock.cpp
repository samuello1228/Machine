//
//  CompositeBlock.cpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include "FundamentalBlock.hpp"
#include "CompositeBlock.hpp"
#include "ControlCenter.hpp"

#include "Module.hpp"
#include "EndReceiver.hpp"

CompositeBlock::CompositeBlock(const string& newName, unsigned int newSize) : size(newSize)
{
    name = newName;
    controlCenter = nullptr;
}

CompositeBlock::~CompositeBlock()
{
    for(set<Block*>::iterator it = Composition.begin(); it!=Composition.end(); it++)
    {
        delete (*it);
    }
}

void CompositeBlock::PrintMap(unsigned int indentation)
{
    cout<<string(indentation, ' ');
    cout<<"Tier:"<<tier<<", ";
    cout<<"Type:"<<name<<", ";
    cout<<"Size:"<<size<<", ";
    cout<<"Coordinate:("<<coordinate.x<<","<<coordinate.y<<")";
    //cout<<", Control Center:"<<controlCenter;
    cout<<endl;
    
    //Check Control Center
    if(controlCenter)
    {
        if(tier != controlCenter->properties_UI["tier"] + 1) cout<<"Error: The ControlCenter link has wrong value of tier."<<endl;
        controlCenter->PrintMap();
    }
    else
    {
        cout<<string(indentation, ' ');
        cout<<"This composite block does not have a control center."<<endl;
    }
    
    if(radioData.size() != 0)
    {
        cout<<string(indentation, ' ');
        cout<<"Radio data: "<<endl;
        for (map<unsigned int,RadioEmitter*>::iterator it=radioData.begin(); it!=radioData.end(); it++)
        {
            cout<<string(indentation+2, ' ');
            cout<<"Channel "<<it->first<< ": "<<it->second->isEmitting<<endl;
        }
    }
    
    cout<<string(indentation, ' ');
    cout<<"Composition:"<<endl;
    vector<Block*> ControlCenters;
    vector<Block*> NormalCenters;
    for(set<Block*>::iterator it = Composition.begin(); it!=Composition.end(); it++)
    {
        if((*it)->isControlCenter()) ControlCenters.push_back((*it));
        else NormalCenters.push_back((*it));
        
        //check MotherBlock link
        if((*it)->MotherBlock != this)
        {
            cout<<"Error: The MotherBlock link is wrong."<<endl;
            return;
        }
    }
    
    //ControlCenters
    for(unsigned int i = 0; i < ControlCenters.size(); i++)
    {
        ControlCenters[i]->PrintMap(indentation+2);
        cout<<endl;
    }
    
    //sort NormalCenters
    sort(NormalCenters.begin(), NormalCenters.end(), [](Block* a, Block* b)->bool{return a->getPriority() < b->getPriority();});
    for(unsigned int i = 0; i < NormalCenters.size(); i++)
    {
        NormalCenters[i]->PrintMap(indentation+2);
        cout<<endl;
    }
}

bool CompositeBlock::checkCoordinate(Coordinate newCoordinate)
{
    if(newCoordinate.x == 0) return false;
    if(newCoordinate.x > size) return false;
    if(newCoordinate.y == 0) return false;
    if(newCoordinate.y > size) return false;
    return true;
}

void CompositeBlock::addControlCenter(const Coordinate& newCoordinate, ControlCenter* newControlCenter)
{
    tier = newControlCenter->properties_UI["tier"] + 1;
    newControlCenter->MotherBlock = this;
    
    if(checkCoordinate(newCoordinate))
    {
        newControlCenter->coordinate = newCoordinate;
    }
    else
    {
        cout<<"Error: The coordinate is out of range."<<endl;
        return;
    }
    
    this->Composition.insert(newControlCenter);
}

void CompositeBlock::addBlock(unsigned int newPriority, const Coordinate& newCoordinate, Block* newBlock)
{
    newBlock->MotherBlock = this;
    
    if(checkCoordinate(newCoordinate))
    {
        newBlock->coordinate = newCoordinate;
    }
    else
    {
        cout<<"Error: The coordinate is out of range."<<endl;
        return;
    }
    
    FundamentalBlock* FundamentalBlock1 = dynamic_cast<FundamentalBlock*>(newBlock);
    if(FundamentalBlock1)
    {
        FundamentalBlock1->properties_UI["priority"] = newPriority;
    }
    
    CompositeBlock* CompositeBlock1 = dynamic_cast<CompositeBlock*>(newBlock);
    if(CompositeBlock1)
    {
        CompositeBlock1->controlCenter->properties_UI["priority"] = newPriority;
    }
    
    this->Composition.insert(newBlock);
}

bool CompositeBlock::isControlCenter()
{
    for(set<Block*>::iterator it = Composition.begin(); it!=Composition.end(); it++)
    {
        if(! (*it)->isControlCenter() ) return false;
    }
    
    return true;
}

void CompositeBlock::registerAll()
{
    for(set<Block*>::iterator it = Composition.begin(); it!=Composition.end(); it++)
    {
        (*it)->registerAll();
    }
    
    if(!isControlCenter() && controlCenter == nullptr)
    {
        cout<<"Error: Control center cannot be found."<<endl;
        return;
    }
}

unsigned int CompositeBlock::getPriority()
{
    if(isControlCenter())
    {
        return 0;
    }
    else if(controlCenter == nullptr)
    {
        cout<<"Error: Control center cannot be found."<<endl;
        return 0;
    }
    
    return controlCenter->properties_UI["priority"];
}

void CompositeBlock::execute(CompositeBlock* topmost, bool isPrint)
{
    unsigned int count = 1;
    while(true)
    {
        vector<Block*> sortedBlock;
        for(set<Block*>::iterator it = Composition.begin(); it!=Composition.end(); it++)
        {
            if((*it)->getPriority() != 0) sortedBlock.push_back(*it);
        }
        
        if(sortedBlock.size() != 0)
        {
            //classified by the priority
            sort(sortedBlock.begin(), sortedBlock.end(), [](Block* a, Block* b)->bool{return a->getPriority() < b->getPriority();});
            
            vector<vector< Block* > > classifiedBlock;
            vector< Block* > element;
            element.push_back(sortedBlock[0]);
            unsigned int index = 0;
            while(true)
            {
                if(index == sortedBlock.size() -1)
                {
                    classifiedBlock.push_back(element);
                    element.clear();
                    break;
                }
                
                index++;
                if(sortedBlock[index]->getPriority() == sortedBlock[index-1]->getPriority())
                {
                    element.push_back(sortedBlock[index]);
                }
                else
                {
                    classifiedBlock.push_back(element);
                    element.clear();
                    element.push_back(sortedBlock[index]);
                }
            }
            
            //check
            for(unsigned int i = 0; i<classifiedBlock.size();i++)
            {
                if(classifiedBlock[i].size() != 1)
                {
                    cout<<"Error: the priority ";
                    cout<<classifiedBlock[i][0]->getPriority();
                    cout<<" for modules: ";
                    for(unsigned int j = 0; j<classifiedBlock[i].size();j++)
                    {
                        cout<<classifiedBlock[i][j]->name<<" ";
                    }
                    cout<<"are repeated."<<endl;
                    return;
                }
            }
            
            if(isPrint) cout<<name<<": The number of loop: "<<count<<endl;
            
            //Run
            for(unsigned int i = 0; i<classifiedBlock.size();i++)
            {
                classifiedBlock[i][0]->execute(topmost,isPrint);
            }
            count++;
            
            //check end
            if(controlCenter == nullptr)
            {
                cout<<"Error: Control center cannot be found."<<endl;
                return;
            }
            
            EndReceiver* endReceiver = dynamic_cast<EndReceiver*>(controlCenter->module["EndReceiver"]);
            if(endReceiver)
            {
                if(endReceiver->getChannelSignal()) return;
            }
            else
            {
                cout<<"Error: The end receiver of the control center is corrupted."<<endl;
                return;
            }
            
        }
    }
}
