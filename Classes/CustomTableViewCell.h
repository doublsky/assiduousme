//
//  CustomTableViewCell.h
//  AssiduousMe
//
//  Created by Tony TAN on 9/5/14.
//
//

#ifndef __AssiduousMe__CustomTableViewCell__
#define __AssiduousMe__CustomTableViewCell__

#include "cocos2d.h"
#include "cocos-ext.h"

class CustomTableViewCell : public cocos2d::extension::CCTableViewCell
{
public:
	virtual void draw();
};

class StatTableViewCell : public cocos2d::extension::CCTableViewCell
{
public:
	virtual void draw();
};

#endif /* defined(__AssiduousMe__CustomTableViewCell__) */
