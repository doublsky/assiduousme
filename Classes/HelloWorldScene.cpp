#include "HelloWorldScene.h"
#include "DataSource.h"
#include "ChargingBattery.h"
#include "Statistics.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define MENU 100
#define BAR 200
#define SMOKE 300
#define HOURTABLE 400
#define MINTABLE 500
#define WIDTH 100
#define HIGHT 50
#define HITONE 600
#define HITTWO 700


#define USERDEBUG 0

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(0xff, 0xff, 0xff, 0xff)) )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //enable the return button in Android
    setKeypadEnabled(true);
    
    /////////////////////////////
    // 3. add your codes below...
    
    float factor = visibleSize.width/480;
    
    //a "start" button should be shown
    CCMenuItemImage *start = CCMenuItemImage::create("startbutton.png",
                                                     "startbutton.png",
                                                     this,
                                                     menu_selector(HelloWorld::menuStartCallback));
    start->setScale(factor);
    start->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/5));
    
    //the statistice is also available at menu
    CCMenuItemImage *stat = CCMenuItemImage::create("stat.png",
                                                    "stat.png",
                                                    this,
                                                    menu_selector(HelloWorld::menuStatCallback));
    stat->setScale(visibleSize.width/480);
    stat->setPosition(ccp(origin.x+visibleSize.width-factor*stat->getContentSize().width,
                          origin.y+visibleSize.height-factor*stat->getContentSize().height));
    
    // create menu, it's an autorelease object
    CCMenu* mainMenu = CCMenu::create(start, stat, NULL);
    mainMenu->setPosition(CCPointZero);
    this->addChild(mainMenu, 1, MENU);
    
    float fontSize = visibleSize.width/16;
    
    //add label to indicate hour or minute
    CCLabelTTF *labelHour = CCLabelTTF::create("Hour", "Helvetica", fontSize);
    labelHour->setColor(ccBLACK);
    labelHour->setPosition(ccp(origin.x+visibleSize.width*5/12, origin.y+visibleSize.height*2/3));
    addChild(labelHour);
    
    CCLabelTTF *labelMin = CCLabelTTF::create("Minute", "Helvetica", fontSize);
    labelMin->setColor(ccBLACK);
    labelMin->setPosition(ccp(origin.x+visibleSize.width*7/12, origin.y+visibleSize.height*2/3));
    addChild(labelMin);
    
    //create list view of "hour" of duration
    DataSourceOfHour *hourData = new DataSourceOfHour;
    CCTableView* tableView = CCTableView::create(hourData, CCSizeMake(visibleSize.width/4, 5*visibleSize.width/8));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->ignoreAnchorPointForPosition(false);
    tableView->setPosition(ccp(origin.x+visibleSize.width/4, origin.y+visibleSize.height*2/3));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView, 1, HOURTABLE);
    tableView->reloadData();
    
    //then create the view of "minute" of duration
    DataSourceOfMin *minData = new DataSourceOfMin;
    tableView = CCTableView::create(minData, CCSizeMake(visibleSize.width/4, 5*visibleSize.width/8));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->ignoreAnchorPointForPosition(false);
    tableView->setPosition(ccp(origin.x+visibleSize.width*3/4, origin.y+visibleSize.height*2/3));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView, 1, MINTABLE);
    tableView->reloadData();
    
    //add hit
    CCSprite *hit1;
    if (visibleSize.width < 960.0f)
    {
        hit1 = CCSprite::create("hit1.png");
        hit1->setScale(visibleSize.width/480.0f);
    }
    else
    {
        hit1 = CCSprite::create("hit1_2x.png");
        hit1->setScale(visibleSize.width/960.0f);
    }
    hit1->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height*5/6));
    hit1->setAnchorPoint(ccp(0.5, 1));
    hit1->setTag(HITONE);
    addChild(hit1);
    
    CCSprite *hit2;
    if (visibleSize.width < 960.0f)
    {
        hit2 = CCSprite::create("hit2.png");
        hit2->setScale(visibleSize.width/480.0f);
    }
    else
    {
        hit2 = CCSprite::create("hit2_2x.png");
        hit2->setScale(visibleSize.width/960.0f);
    }
    hit2->setPosition(ccp(origin.x+visibleSize.width/2-start->getContentSize().width, origin.y+visibleSize.height/5));
    hit2->setAnchorPoint(ccp(1, 0));
    hit2->setTag(HITTWO);
    addChild(hit2);
    
#if (USERDEBUG)
    CCLabelTTF *timeLabel = CCLabelTTF::create("now at : 1970/01/01, 00 : 00 : 00", "Helvetica", fontSize/2);
    timeLabel->setColor(ccBLACK);
    timeLabel->setPosition(ccp(origin.x+timeLabel->getContentSize().width/2,
                               origin.y+visibleSize.height-timeLabel->getContentSize().height/2));
    timeLabel->setTag(234);
    addChild(timeLabel);
    scheduleUpdate();
#endif

    return true;
}

void HelloWorld::update(float dt)
{
    //for debugging
    fullTime debugTime = getFullTime();
    char debug_s[50];
    sprintf(debug_s, "now at : %d/%d/%d, %d : %d : %d", debugTime.year, debugTime.month, debugTime.day, debugTime.hour, debugTime.minute, debugTime.second);
    CCLabelTTF *timeLabel = (CCLabelTTF*)getChildByTag(234);
    timeLabel->setString(debug_s);
}

void HelloWorld::menuStartCallback(CCObject* pSender)
{
    //CCLog("start clicked");
    
    //get current time when "start" is clicked
    fullTime startTime = getFullTime();
    
    //store the start time
    CCUserDefault::sharedUserDefault()->setIntegerForKey("startYear", startTime.year);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("startMonth", startTime.month);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("startDay", startTime.day);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("startHour", startTime.hour);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("startMinute", startTime.minute);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("startSecond", startTime.second);
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("durHour", duration.hour);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("durMinute", duration.minute);
    
    //save statistics
    char *s = whichRegion(duration.hour, duration.minute);
    s = strcat(s, "_count");
    int count = CCUserDefault::sharedUserDefault()->getIntegerForKey(s, 0);
    count++;
    CCUserDefault::sharedUserDefault()->setIntegerForKey(s, count);
    delete [] s;
    
    //make all the file IO valid
    CCUserDefault::sharedUserDefault()->flush();
    
    //change the scene
    //CCDirector::sharedDirector()->purgeCachedData();      //if we don't keep cache, returning from background
                                                            //may rander problems
    CCScene *nextScene = ChargingBattery::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, nextScene, ccWHITE));
}

void HelloWorld::menuStatCallback(cocos2d::CCObject *pSender)
{
    char s[50];
    CCLog("less than 15 mins: %f", CCUserDefault::sharedUserDefault()->getFloatForKey("lessThan15mins_rate"));
    CCLog("less than 30 mins: %f", CCUserDefault::sharedUserDefault()->getFloatForKey("lessThan30mins_rate"));
    CCLog("less than 1 h: %f", CCUserDefault::sharedUserDefault()->getFloatForKey("lessThan1h_rate"));
    for (int i = 2; i <= 12; i++)
    {
        sprintf(s, "lessThan%dhs_rate", i);
        CCLog("less than %d hs: %f", i, CCUserDefault::sharedUserDefault()->getFloatForKey(s));
    }
    CCLog("more than 12 hs: %f", CCUserDefault::sharedUserDefault()->getFloatForKey("moreThan12hs_rate"));
    
    CCScene *nextScene = Statistics::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, nextScene, ccWHITE));
}

void HelloWorld::draw()
{
    CCLayerColor::draw();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    glLineWidth(visibleSize.width/240);
    ccDrawColor4B(0, 0, 0, 255);
    float width = visibleSize.width/4;
    float height = visibleSize.width/8;
    ccDrawLine(ccp(origin.x+visibleSize.width/4-width/2, origin.y+visibleSize.height*2/3+height/2),
               ccp(origin.x+visibleSize.width*3/4+width/2, origin.y+visibleSize.height*2/3+height/2));
    ccDrawLine(ccp(origin.x+visibleSize.width/4-width/2, origin.y+visibleSize.height*2/3-height/2),
               ccp(origin.x+visibleSize.width*3/4+width/2, origin.y+visibleSize.height*2/3-height/2));
}

void HelloWorld::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

void HelloWorld::scrollViewDidScroll(cocos2d::extension::CCScrollView *view)
{
    //CCLog("scrolling");
    //CCLog("view id: %x", view);
    
    CCPoint offSet = view->getContentOffset();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    float height = visibleSize.width/8;
    int intheight = (int)height;
    //CCLog("((int)(-offSet.y+height/2))/height = %f", (int)(-offSet.y+height/2)/height);

    //CCLog("scroll at x: %f, y: %f", offSet.x, offSet.y);
    //CCLog("min at: %f", view->minContainerOffset().y);
    
    if (offSet.y != view->minContainerOffset().y) {
        CCSprite *hit1 = (CCSprite*)getChildByTag(HITONE);
        if (hit1) {
            removeChild(hit1);
        }
        CCSprite *hit2 = (CCSprite*)getChildByTag(HITTWO);
        if (hit2) {
            removeChild(hit2);
        }
    }
    
    if (view->minContainerOffset().y > -2000)
    {
        duration.hour = 23 - ((int)(-offSet.y+intheight/2))/intheight;
        if (duration.hour < 0) {
            duration.hour = 0;
        }
        if (duration.hour > 23) {
            duration.hour = 23;
        }
        //CCLog("hour is %d", duration.hour);
    }
    else
    {
        duration.minute = 59 - ((int)(-offSet.y+intheight/2))/intheight;
        if (duration.minute < 0) {
            duration.minute = 0;
        }
        if (duration.minute > 59) {
            duration.minute = 59;
        }
        //CCLog("min is %d", duration.minute);
    }
}

void HelloWorld::keyBackClicked()
{
    CCDirector::sharedDirector()->end();
}
