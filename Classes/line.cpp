//
//  line.cpp
//  AssiduousMe
//
//  Created by Tony TAN on 9/9/14.
//
//

#include "line.h"

#define HIGHT 50
#define WIDTH 100

USING_NS_CC;

void line::draw()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    glLineWidth(2.0f);
    ccDrawColor4B(0, 0, 0, 255);
    ccDrawLine(ccp(origin.x+visibleSize.width/4-WIDTH/2, origin.y+visibleSize.height*2/3+HIGHT/2),
               ccp(origin.x+visibleSize.width*3/4+WIDTH/2, origin.y+visibleSize.height*2/3+HIGHT/2));
    ccDrawLine(ccp(origin.x+visibleSize.width/4-WIDTH/2, origin.y+visibleSize.height*2/3-HIGHT/2),
               ccp(origin.x+visibleSize.width*3/4+WIDTH/2, origin.y+visibleSize.height*2/3-HIGHT/2));
}

line* line::create()
{
    line * pRet = new line();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}
bool line::init()
{
    return CCNode::init();
}