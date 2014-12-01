//
//  ChargingBattery.h
//  AssiduousMe
//
//  Created by Tony TAN on 9/9/14.
//
//

#ifndef __AssiduousMe__ChargingBattery__
#define __AssiduousMe__ChargingBattery__

#include "cocos2d.h"
#include "AppDelegate.h"

class ChargingBattery : public cocos2d::CCLayerColor
{
public:
    double ratio;
    int hour;
    int minute;
    float amplitude;
    
    cocos2d::CCPoint controlPoint;
    cocos2d::CCPoint startPoint;
    cocos2d::CCPoint endPoint;
    
    float waveTime;

    //some original function
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(ChargingBattery);
    
    //update the progress bar
    void updateProgress(float dt);
    void update(float dt);      //for debugging
    
    //keypad click callback
    void keyBackClicked();
    
    //test, draw wave
    virtual void draw();
    
    //menuCallback
    void menufinishCallback(CCObject* pSender);
};

#endif /* defined(__AssiduousMe__ChargingBattery__) */
