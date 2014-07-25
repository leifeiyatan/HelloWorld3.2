#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

#include "CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
using namespace cocostudio::timeline;

typedef std::function<void(Armature *armature, MovementEventType movementType, const std::string& movementID)> cb;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void btnCallback(Ref* sender, Widget::TouchEventType event);
    
    
    void frameCallback();
    
    void onFinishEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    void onFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
