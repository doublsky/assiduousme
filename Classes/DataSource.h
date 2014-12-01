//
//  DataSource.h
//  AssiduousMe
//
//  Created by Tony TAN on 9/12/14.
//
//

#ifndef __AssiduousMe__DataSource__
#define __AssiduousMe__DataSource__

#include "cocos2d.h"
#include "cocos-ext.h"

class DataSourceOfHour : public cocos2d::extension::CCTableViewDataSource
{
public:
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
};

class DataSourceOfMin : public cocos2d::extension::CCTableViewDataSource
{
public:
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
};

class DataSourceOfStat : public cocos2d::extension::CCTableViewDataSource
{
public:
    //initiate different cells
    void init1stCell(cocos2d::extension::CCTableViewCell *cell);
    void init2ndCell(cocos2d::extension::CCTableViewCell *cell);
    
    //override functions
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
};
#endif /* defined(__AssiduousMe__DataSource__) */
