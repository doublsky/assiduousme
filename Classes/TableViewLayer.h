//
//  TableViewLayer.h
//  AssiduousMe
//
//  Created by Tony TAN on 9/5/14.
//
//

#ifndef __AssiduousMe__TableViewLayer__
#define __AssiduousMe__TableViewLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

class TableViewLayer : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
    virtual bool init();
    
    CREATE_FUNC(TableViewLayer);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) ;
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
};

#endif /* defined(__AssiduousMe__TableViewLayer__) */
