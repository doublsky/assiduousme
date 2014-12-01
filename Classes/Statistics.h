//
//  Statistics.h
//  AssiduousMe
//
//  Created by Tony TAN on 9/12/14.
//
//

#ifndef __AssiduousMe__Statistics__
#define __AssiduousMe__Statistics__

#include "cocos2d.h"
#include "cocos-ext.h"


class Statistics : public cocos2d::CCLayerColor, public cocos2d::extension::CCTableViewDelegate
{
public:
    //original function
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Statistics);
    
    //keypad click callback
    void keyBackClicked();
    
    //menu callback
    void menuBackCallback(CCObject* pSender);
    
    //table view
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) ;
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
};

#endif /* defined(__AssiduousMe__Statistics__) */
