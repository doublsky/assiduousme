//
//  line.h
//  AssiduousMe
//
//  Created by Tony TAN on 9/9/14.
//
//

#ifndef __AssiduousMe__line__
#define __AssiduousMe__line__

#include "cocos2d.h"

class line : public cocos2d::CCNode
{
public:
    virtual void draw();
    static line* create();
    virtual bool init();
};

#endif /* defined(__AssiduousMe__line__) */
