#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "TableViewLayer.h"
#include "ChargingBattery.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene;
    if (isNewTurn())
    {
        pScene = HelloWorld::scene();
    }
    else
    {
        pScene = ChargingBattery::scene();
    }

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    
    CCDirector::sharedDirector()->purgeCachedData();

    CCScene *pScene;
    if (isNewTurn())
    {
        pScene = HelloWorld::scene();
    }
    else
    {
        pScene = ChargingBattery::scene();
    }
    
    // run
    CCDirector::sharedDirector()->replaceScene(pScene);

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

bool AppDelegate::isNewTurn()
{
    //get current time
    CCLog("computing new turn...");
    fullTime currentTime = getFullTime();
    
    //retrieve the data from storage
    int startYear = CCUserDefault::sharedUserDefault()->getIntegerForKey("startYear", 0);
    int startMonth = CCUserDefault::sharedUserDefault()->getIntegerForKey("startMonth", 0);
    int startDay = CCUserDefault::sharedUserDefault()->getIntegerForKey("startDay", 0);
    int startHour = CCUserDefault::sharedUserDefault()->getIntegerForKey("startHour", 0);
    int startMinute = CCUserDefault::sharedUserDefault()->getIntegerForKey("startMinute", 0);
    int startSecond = CCUserDefault::sharedUserDefault()->getIntegerForKey("startSecond", 0);
    
    int durHour = CCUserDefault::sharedUserDefault()->getIntegerForKey("durHour", 0);
    int durMinute = CCUserDefault::sharedUserDefault()->getIntegerForKey("durMinute", 0);
    
    CCLog("start at : day %d, %d : %d : %d", startDay, startHour, startMinute, startSecond);
    
    //compare the end monent with current time
    int currentTimeInSecond = (((currentTime.day-1)*24+currentTime.hour)*60+currentTime.minute)*60+currentTime.second;
    int startTimeInSecond = (((startDay-1)*24+startHour)*60+startMinute)*60+startSecond;
    int durationInSecond = (durHour*60+durMinute)*60;
    
    int endTimeInSecond = startTimeInSecond + durationInSecond;
    
    //CCLog("current second: %d, duration: %d, end second: %d", currentTimeInSecond, durationInSecond, endTimeInSecond);
    if (currentTime.year > startYear)
    {
        CCLog("current year is greater than start one");
        return true;
    }
    else if (currentTime.year < startYear)
    {
        CCLog("current year is smaller than start one");
        return false;
    }
    else if (currentTime.month > startMonth)
    {
        CCLog("current month is greater than start one");
        return true;
    }
    else if (currentTime.month < startMonth)
    {
        CCLog("current month is smaller than start one");
        return false;
    }
    else if (currentTimeInSecond > endTimeInSecond)
    {
        return true;
    }
    
    return false;
}

fullTime getFullTime()
{
    time_t timep;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    time(&timep);
#else
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    timep = now.tv_sec;
    //CCLog("millisecond: %ld", timep);
#endif
    struct tm *tm;
    fullTime level;
    
    tm = localtime(&timep);
    level.year = tm->tm_year + 1900;
    level.month = tm->tm_mon + 1;
    level.day = tm->tm_mday;
    level.hour=tm->tm_hour;
    level.minute=tm->tm_min;
    level.second=tm->tm_sec;
    
    CCLog("now at : day %d, %d : %d : %d", level.day, level.hour, level.minute, level.second);
    
    return level;
}

char* whichRegion(int hour, int minute)
{
    char* s = new char[50];
    if (hour == 0)
    {
        if (minute <= 15)
        {
            sprintf(s, "lessThan15mins");
        }
        else if (minute <= 30)
        {
            sprintf(s, "lessThan30mins");
        }
        else
        {
            sprintf(s, "lessThan1h");
        }
    }
    else if (hour <= 12)
    {
        sprintf(s, "lessThan%dhs", hour+1);
        
    }
    else
    {
        sprintf(s, "moreThan12hs");
    }
    return s;
}
