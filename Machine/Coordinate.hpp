//
//  Coordinate.hpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef Coordinate_hpp
#define Coordinate_hpp

class Coordinate
{
    public:
    unsigned int x;
    unsigned int y;
    
    Coordinate(unsigned int newx = 0, unsigned int newy = 0): x(newx), y(newy){}
    
    bool isEqual(const Coordinate& another) const
    {
        if(x == another.x && y == another.y) return true;
        else return false;
    }
};

#endif /* Coordinate_hpp */
