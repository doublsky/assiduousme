//
//  ChargingBattery.cpp
//  AssiduousMe
//
//  Created by Tony TAN on 9/9/14.
//
//

#include "ChargingBattery.h"
#include "HelloWorldScene.h"
//#include "platform/android/CCGL.h"

#define BATTERYWIDTH 180.0f
#define BATTERYHIGHT 270.0f
#define BATTERTHIGHT_FULL 300.0f
#define AMP 10
#define PI 3.1415926

#define USERDEBUG 0

USING_NS_CC;

CCScene* ChargingBattery::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ChargingBattery *layer = ChargingBattery::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool ChargingBattery::init()
{
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(0xff, 0xff, 0xff, 0xff)) )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //enable the return button in Android
    setKeypadEnabled(true);
    
    waveTime = 0.0f;
    amplitude = AMP;
    
    float bottomOfBattery = origin.y+visibleSize.height*2/3 - BATTERYHIGHT/2;
    startPoint = ccp(origin.x+visibleSize.width/2-BATTERYWIDTH/2, bottomOfBattery);
    controlPoint = ccp(origin.x+visibleSize.width/2, bottomOfBattery);
    endPoint = ccp(origin.x+visibleSize.width/2+BATTERYWIDTH/2, bottomOfBattery);
    
    //make a bottle of water
    CCSprite *battery = CCSprite::create("battery.png");
    battery->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height*2/3));
    battery->setAnchorPoint(ccp(0.5, BATTERTHIGHT_FULL/2/battery->getContentSize().height));
    CCLog("anchor: x = %f, y = %f", battery->getAnchorPoint().x, battery->getAnchorPoint().y);
    CCLog("anchor: x = %f, y = %f", battery->getAnchorPointInPoints().x, battery->getAnchorPointInPoints().y);
    addChild(battery, 3);
    
    //get time from storage
    hour = CCUserDefault::sharedUserDefault()->getIntegerForKey("durHour", 0);
    minute = CCUserDefault::sharedUserDefault()->getIntegerForKey("durMinute", 0);
    int startHour = CCUserDefault::sharedUserDefault()->getIntegerForKey("startHour", 0);
    int startMinute = CCUserDefault::sharedUserDefault()->getIntegerForKey("startMinute", 0);
    int startSecond = CCUserDefault::sharedUserDefault()->getIntegerForKey("startSecond", 0);
    
    //get current time
    fullTime time = getFullTime();
    
    ratio=(double)(((time.hour-startHour)*60+(time.minute-startMinute))*60+(time.second-startSecond))/((hour*60+minute)*60);
    ratio = MIN(1, ratio);
    //CCLog("when init layer, ratio is %f", ratio);
    
    schedule(schedule_selector(ChargingBattery::updateProgress), 0);
    
#if (USERDEBUG)
    CCLabelTTF *timeLabel = CCLabelTTF::create("now at : 1970/01/01, 00 : 00 : 00", "Helvetica", 15);
    timeLabel->setColor(ccBLACK);
    timeLabel->setPosition(ccp(origin.x+timeLabel->getContentSize().width/2,
                               origin.y+visibleSize.height-timeLabel->getContentSize().height/2));
    timeLabel->setTag(234);
    addChild(timeLabel);
    scheduleUpdate();
#endif
    
    return true;
}

void ChargingBattery::update(float dt)
{
    //for debugging
    fullTime debugTime = getFullTime();
    char debug_s[50];
    sprintf(debug_s, "now at : %d/%d/%d, %d : %d : %d", debugTime.year, debugTime.month, debugTime.day, debugTime.hour, debugTime.minute, debugTime.second);
    CCLabelTTF *timeLabel = (CCLabelTTF*)getChildByTag(234);
    timeLabel->setString(debug_s);
}

void ChargingBattery::updateProgress(float dt)
{
    //CCLog("hour = %d", hour);
    //CCLog("minute = %d", minute);
    
    waveTime += dt;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (hour != 0 || minute != 0)
    {
        ratio += dt / ((hour*60+minute)*60);
    }
    else
    {
        ratio = 1;
    }
    ratio = MIN(ratio, 1);
    //CCLog("in this frame, ratio is %f", ratio);
    
    if (ratio == 1)
    {
        //add "Assiduous!"
        CCMenuItemFont::setFontName("Helvetica");
        CCMenuItemFont::setFontSize(30);
        CCMenuItemFont *finish = CCMenuItemFont::create("Assiduous!",
                                                        this,
                                                        menu_selector(ChargingBattery::menufinishCallback));
        finish->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height/3));
        finish->setColor(ccBLACK);
        CCMenu *pMenu = CCMenu::create(finish, NULL);
        pMenu->setPosition(CCPointZero);
        addChild(pMenu);
        
        //add a back arrow
        CCSprite *backArrow = CCSprite::create("backarrow.png");
        backArrow->setAnchorPoint(ccp(1.5, 0.5));
        backArrow->setScale(0.4f);
        backArrow->setPosition(ccp(origin.x+visibleSize.width/2-finish->getContentSize().width/2,
                                   origin.y+visibleSize.height/3));
        addChild(backArrow);
        unschedule(schedule_selector(ChargingBattery::updateProgress));
        
        //save statistics
        char *s = whichRegion(hour, minute);
        strcat(s, "_count");
        int count = CCUserDefault::sharedUserDefault()->getIntegerForKey(s, 0);
        delete [] s;

        s = whichRegion(hour, minute);
        strcat(s, "_rate");
        float rate = CCUserDefault::sharedUserDefault()->getFloatForKey(s, 0.0f);
        if (count)
        {
            rate = (rate * (count-1) + 1) / count;
        }
        else
        {
            rate = 0.0f;
        }
        CCUserDefault::sharedUserDefault()->setFloatForKey(s, rate);
        delete [] s;
    }
    else if (ratio > 0.9)
    {
        amplitude = 100.0f * (1.0f - ratio);
    }
    else if (ratio < 0.1)
    {
        amplitude = 100.0f * ratio;
    }
    //CCLog("in this frame, amplitude is %f", amplitude);
    
    float bottomOfBattery = origin.y+visibleSize.height*2/3 - BATTERYHIGHT/2;
    startPoint.y = bottomOfBattery + ratio*BATTERYHIGHT + amplitude*sin(waveTime);
    controlPoint.x = origin.x+visibleSize.width/2 + amplitude*sin(waveTime);
    controlPoint.y = bottomOfBattery + ratio*BATTERYHIGHT + amplitude + 1.5*amplitude*sin(waveTime+PI*3/2);
    endPoint.y = bottomOfBattery + ratio*BATTERYHIGHT + amplitude*(sin(-waveTime));
}

void ChargingBattery::draw()
{
    CCLayerColor::draw();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
#else
    glEnable(GL_BLEND);
    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    glEnable(GL_SAMPLE_COVERAGE);
#endif
    glLineWidth(5.0f);
    ccDrawColor4B(0, 0, 0, 255);
    ccDrawQuadBezier(startPoint, controlPoint, endPoint, 200);
}

void ChargingBattery::menufinishCallback(cocos2d::CCObject *pSender)
{
    //CCDirector::sharedDirector()->purgeCachedData();
    CCScene *nextScene = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, nextScene, ccWHITE));
}

void ChargingBattery::keyBackClicked()
{
    CCDirector::sharedDirector()->end();
}