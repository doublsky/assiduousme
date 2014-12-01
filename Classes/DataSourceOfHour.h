//
//  DataSourceOfHour.h
//  AssiduousMe
//
//  Created by Tony TAN on 9/5/14.
//
//

#ifndef __AssiduousMe__DataSourceOfHour__
#define __AssiduousMe__DataSourceOfHour__

#include "cocos2d.h"
#include "cocos-ext.h"

class DataSourceOfHour : public cocos2d::extension::CCTableViewDataSource
{
public:
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
};
#endif /* defined(__AssiduousMe__DataSourceOfHour__) */
