//
//  DataSourceOfHour.cpp
//  AssiduousMe
//
//  Created by Tony TAN on 9/5/14.
//
//

#include "DataSourceOfHour.h"
#include "CustomTableViewCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define WIDTH 100
#define HIGHT 50

CCSize DataSourceOfHour::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(WIDTH, HIGHT);
}

CCTableViewCell* DataSourceOfHour::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string;
    if (idx >= 2 && idx <= 25)
        string = CCString::createWithFormat("%0.2d", idx-2);
    else
        string = CCString::createWithFormat("");

    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 25.0);
        label->setColor(ccBLACK);
        label->setPosition(ccp(WIDTH/2, HIGHT/2));
		label->setAnchorPoint(ccp(0.5,0.5));
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    
    
    return cell;
}

unsigned int DataSourceOfHour::numberOfCellsInTableView(CCTableView *table)
{
    return 28;
}