//
//  DataSource.cpp
//  AssiduousMe
//
//  Created by Tony TAN on 9/12/14.
//
//

#include "DataSource.h"
#include "CustomTableViewCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define WIDTH 100
#define HIGHT 50
#define STAT_WIDTH 300.0f
#define MAX_BAR_HIGHT 300.0f


CCSize DataSourceOfHour::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    return CCSizeMake(visibleSize.width/4, visibleSize.width/8);
}

CCTableViewCell* DataSourceOfHour::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    float fontSize = visibleSize.width/16;
    
    CCString *string;
    if (idx >= 2 && idx <= 25)
        string = CCString::createWithFormat("%0.2d", idx-2);
    else
        string = CCString::createWithFormat("");
    
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", fontSize);
        label->setColor(ccBLACK);
        label->setPosition(ccp(visibleSize.width/8, visibleSize.width/16));
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

CCSize DataSourceOfMin::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    return CCSizeMake(visibleSize.width/4, visibleSize.width/8);
}

CCTableViewCell* DataSourceOfMin::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    float fontSize = visibleSize.width/16;
    
    CCString *string;
    if (idx >= 2 && idx <= 61)
        string = CCString::createWithFormat("%0.2d", idx-2);
    else
        string = CCString::createWithFormat("");
    
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", fontSize);
        label->setColor(ccBLACK);
        label->setPosition(ccp(visibleSize.width/8, visibleSize.width/16));
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

unsigned int DataSourceOfMin::numberOfCellsInTableView(CCTableView *table)
{
    return 64;
}

CCSize DataSourceOfStat::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    return CCSizeMake(visibleSize.width, visibleSize.height/2);
}

CCTableViewCell* DataSourceOfStat::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    //CCString *string = CCString::createWithFormat("%d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        switch (idx+1)
        {
            case 1:
                init1stCell(cell);
                CCLog("draw No.1");
                break;
            case 2:
                init2ndCell(cell);
                CCLog("draw No.2");
                break;
                
            default:
                break;
        }
        
        /*CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        label->setColor(ccBLACK);
        cell->addChild(label);*/
    }
    else
    {
        /*CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());*/
    }
    
    return cell;
}

void DataSourceOfStat::init1stCell(cocos2d::extension::CCTableViewCell *cell)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    //get stat from file
    char s[50];
    int barHeight[15];
    
    barHeight[0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("lessThan15mins_count", 0);
    barHeight[1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("lessThan30mins_count", 0);
    barHeight[2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("lessThan1h_count", 0);
    for (int i = 2; i <= 12; i++)
    {
        sprintf(s, "lessThan%dhs_count", i);
        barHeight[i+1] = CCUserDefault::sharedUserDefault()->getIntegerForKey(s, 0);
    }
    barHeight[14] = CCUserDefault::sharedUserDefault()->getIntegerForKey("moreThan12hs_count", 0);
    
    //add X axis
    CCSprite *frame = CCSprite::create("frame_FinD.png");
    frame->setPosition(ccp(visibleSize.width/2, 0));
    frame->setAnchorPoint(ccp(0.5, 0));
    cell->addChild(frame, 2);
    
    CCSprite *axis = CCSprite::create("frame.png");
    float offset = axis->getContentSize().height;
    
    //add a layer accommondate stat bars
    CCLayerColor *background = CCLayerColor::create(ccc4(255, 255, 255, 255), STAT_WIDTH, visibleSize.height/2);
    background->setPosition(ccp(visibleSize.width/2, 0));
    background->setAnchorPoint(ccp(0.5, 0));
    background->ignoreAnchorPointForPosition(false);
    
    //draw bars
    int barWidth = STAT_WIDTH / 15;
    int maxHeight = barHeight[0];
    for (int i = 1; i <= 14; i++)
    {
        if (barHeight[i] > maxHeight)
        {
            maxHeight = barHeight[i];
        }
    }
    int unitBarHight = MAX_BAR_HIGHT / maxHeight;
    
    //add a label of the highest one
    sprintf(s, "%d", maxHeight);
    CCLabelTTF *marker = CCLabelTTF::create(s, "Helvetica", 20);
    marker->setColor(ccBLACK);
    marker->setAnchorPoint(CCPointZero);
    marker->setPosition(ccp(visibleSize.width/2+STAT_WIDTH/2, MAX_BAR_HIGHT+offset));
    cell->addChild(marker, 2);
    
    CCLayerColor *bar;
    for (int i = 0; i <= 14; i++)
    {
        bar = CCLayerColor::create(ccc4(0, 0, 0, 255), barWidth, barHeight[i]*unitBarHight);
        bar->ignoreAnchorPointForPosition(true);
        bar->setPosition(ccp(i*barWidth, offset));
        background->addChild(bar);
    }
    cell->addChild(background, 1);
}

void DataSourceOfStat::init2ndCell(CCTableViewCell *cell)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    //get stat from file
    char s[50];
    float rateHeight[15];
    
    rateHeight[0] = CCUserDefault::sharedUserDefault()->getFloatForKey("lessThan15mins_rate", 0.0f);
    rateHeight[1] = CCUserDefault::sharedUserDefault()->getFloatForKey("lessThan30mins_rate", 0.0f);
    rateHeight[2] = CCUserDefault::sharedUserDefault()->getFloatForKey("lessThan1h_rate", 0.0f);
    for (int i = 2; i <= 12; i++)
    {
        sprintf(s, "lessThan%dhs_rate", i);
        rateHeight[i+1] = CCUserDefault::sharedUserDefault()->getFloatForKey(s, 0.0f);
    }
    rateHeight[14] = CCUserDefault::sharedUserDefault()->getFloatForKey("moreThan12hs_rate", 0.0f);
    
    //add X axis
    CCSprite *frame = CCSprite::create("frame_AR.png");
    frame->setPosition(ccp(visibleSize.width/2, 0));
    frame->setAnchorPoint(ccp(0.5, 0));
    cell->addChild(frame, 2);
    
    CCSprite *axis = CCSprite::create("frame.png");
    float offset = axis->getContentSize().height;
    
    //add a label of the highest one
    CCLabelTTF *marker = CCLabelTTF::create("100%", "Helvetica", 20);
    marker->setColor(ccBLACK);
    marker->setAnchorPoint(CCPointZero);
    marker->setPosition(ccp(visibleSize.width/2+STAT_WIDTH/2, MAX_BAR_HIGHT+offset));
    cell->addChild(marker, 2);

    
    //add a layer accommondate stat bars
    CCLayerColor *background = CCLayerColor::create(ccc4(255, 255, 255, 255), STAT_WIDTH, visibleSize.height/2);
    background->setPosition(ccp(visibleSize.width/2, 0));
    background->setAnchorPoint(ccp(0.5, 0));
    background->ignoreAnchorPointForPosition(false);
    
    //draw bars
    int barWidth = STAT_WIDTH / 15;
    int unitBarHight = MAX_BAR_HIGHT;
    
    CCLayerColor *bar;
    for (int i = 0; i <= 14; i++)
    {
        bar = CCLayerColor::create(ccc4(0, 0, 0, 255), barWidth, rateHeight[i]*unitBarHight);
        bar->ignoreAnchorPointForPosition(true);
        bar->setPosition(ccp(i*barWidth, offset));
        background->addChild(bar);
    }
    cell->addChild(background, 1);
}

unsigned int DataSourceOfStat::numberOfCellsInTableView(CCTableView *table)
{
    return 2;
}