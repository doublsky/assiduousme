//
//  TableViewLayer.cpp
//  AssiduousMe
//
//  Created by Tony TAN on 9/5/14.
//
//

#include "TableViewLayer.h"
#include "CustomTableViewCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define WIDTH 50
#define HIGHT 50

bool TableViewLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCTableView* tableView = CCTableView::create(this, CCSizeMake(WIDTH, 5*HIGHT));
	tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->ignoreAnchorPointForPosition(false);
	tableView->setPosition(ccp(origin.x+visibleSize.width/4, origin.y+visibleSize.height*2/3));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();
    
    return true;
}

void TableViewLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize TableViewLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(WIDTH, HIGHT);
}

CCTableViewCell* TableViewLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("%0.2d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        //CCSprite *sprite = CCSprite::create("inkFull.png");
        //sprite->setAnchorPoint(CCPointZero);
        //sprite->setPosition(ccp(0, 0));
        //cell->addChild(sprite);
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
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

void TableViewLayer::scrollViewDidScroll(cocos2d::extension::CCScrollView *view)
{
    //CCLog("scrolling");
    //CCLog("view id: %x", view);
    
    CCPoint offSet = view->getContentOffset();
    CCLog("scroll at x: %f, y: %f", offSet.x, offSet.y);
}

unsigned int TableViewLayer::numberOfCellsInTableView(CCTableView *table)
{
    return 20;
}