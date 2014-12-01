#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "AppDelegate.h"



class HelloWorld : public cocos2d::CCLayerColor, public cocos2d::extension::CCTableViewDelegate
{
public:
    //member variables
    fullTime duration;
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // start callback
    void menuStartCallback(CCObject* pSender);
    void menuStatCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    //keypad click callback
    void keyBackClicked();
    
    //draw lines
    virtual void draw();
    
    //for debugging
    void update(float dt);

    
    //table view
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) ;
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
};

#endif // __HELLOWORLD_SCENE_H__
