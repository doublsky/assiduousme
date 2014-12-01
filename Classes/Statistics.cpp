//
//  Statistics.cpp
//  AssiduousMe
//
//  Created by Tony TAN on 9/12/14.
//
//

#include "Statistics.h"
#include "DataSource.h"
#include "HelloWorldScene.h"

#define STAT_WIDTH 300.0f
#define MAX_BAR_HIGHT 300.0f


USING_NS_CC;
USING_NS_CC_EXT;

CCScene*  Statistics::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Statistics *layer = Statistics::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Statistics::init()
{
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //enable the return button in Android
    setKeypadEnabled(true);
    
    //create list view of charts
    DataSourceOfStat *statData = new DataSourceOfStat;
    CCTableView* tableView = CCTableView::create(statData, CCSizeMake(visibleSize.width, visibleSize.height));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->ignoreAnchorPointForPosition(false);
    tableView->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2+50));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView);
    tableView->reloadData();
    
    //add a back button
    CCMenuItemFont::setFontName("Helvetica");
    CCMenuItemFont::setFontSize(30);
    CCMenuItemFont *back = CCMenuItemFont::create("back!",
                                                    this,
                                                    menu_selector(Statistics::menuBackCallback));
    back->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+back->getContentSize().height/2));
    back->setColor(ccBLACK);
    CCMenu *pMenu = CCMenu::create(back, NULL);
    pMenu->setPosition(CCPointZero);
    addChild(pMenu);
    
    return true;
}

void Statistics::scrollViewDidScroll(CCScrollView *view)
{
    CCLog("scrolling...");
}

void Statistics::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

void Statistics::menuBackCallback(cocos2d::CCObject *pSender)
{
    //CCDirector::sharedDirector()->purgeCachedData();
    CCScene *nextScene = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, nextScene, ccWHITE));
}

void Statistics::keyBackClicked()
{
    CCDirector::sharedDirector()->purgeCachedData();
    CCScene *nextScene = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, nextScene, ccWHITE));
}
