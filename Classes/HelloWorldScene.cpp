#include "HelloWorldScene.h"



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    if ( !Layer::init() )
    {
        return false;
    }
//    mac版本
//    Layout* root = dynamic_cast<Layout*>(cocostudio::timeline::NodeReader::getInstance()->createNode("DemoLogin.json"));
//    addChild( root );

////    windows版本
//    ui::Layout* root = dynamic_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("DemoLogin.json"));
//    addChild(root);
//    
//    //根据名称获取元素
//    //Button* btn = static_cast<Button*>(root->getChildByName("login_Button"));
//    //根据tag获取元素
//    Button* btn = dynamic_cast<Button*>(root->getChildByTag(14) );
//    btn -> addTouchEventListener( CC_CALLBACK_2(HelloWorld::btnCallback,this) );
////    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
////    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
//    
//    //播放ui中动画
//    CallFunc * fun = CallFunc::create(std::bind(&HelloWorld::frameCallback, this));
//    ActionManagerEx::getInstance()->playActionByName("DemoLogin.json" , "Animation0",fun);
    

    
//    //创建动画
//    Armature* armature = Armature::create("p1wTest");
//    armature->setPosition( Point(480,320) );
//    armature->setScale( 2 );
//    //播放第一个动画
//    //armature->getAnimation()->playWithIndex(0);
//    armature->getAnimation()->play("walk2");
//    addChild(armature);
//    
//    //回调贞事件
//    armature->getAnimation()->setFrameEventCallFunc(std::bind(&HelloWorld::onFrameEvent,this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4) );

//    LivingUnit* unit = LivingUnit::createByDirection( State::Unit_State_Walk, Direction::Unit_Direction_LEFTUP );
//    unit -> setPosition( Point (480,320) );
//    addChild( unit );
//    
//    EventDispatcher* event = Director::getInstance() -> getEventDispatcher();
//    auto listener = EventListenerTouchOneByOne::create();
//    listener -> setSwallowTouches( true );
//    listener -> onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
//    listener -> onTouchEnded = [=](Touch* touch, Event* event){
//                auto target = static_cast<Node*>(event->getCurrentTarget());
//            };
//    event -> addEventListenerWithSceneGraphPriority(listener, this);
    //removeEventListener( listener );
    
    //回调运动结束事件
//    armature->getAnimation()->setMovementEventCallFunc(std::bind(&HelloWorld::onFinishEvent,this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    

    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png");
//    Director::getInstance()->getTextureCache()->addImage("01.png");
//    ActionTimeline* action = ActionTimelineCache::getInstance()->createAction("NewTestFrameAni.json");
//    Node* node = NodeReader::getInstance()->createNode("NewTestFrameAni.json");
//    ui::Layout* root1 = dynamic_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("NewTestFrameAni.json"));
//    addChild(root1);
//    ActionTimeline* action = ActionTimelineCache::getInstance()->createAction("ActionTimeline/boy_1.ExportJson");
//    
//    node->runAction(action);
//    action->gotoFrameAndPlay(0, 60, true);
//    
//    node->setScale(0.2f);
//    node->setPosition(150,100);
//    
//    addChild(node);
//    ImageView* star = dynamic_cast<ImageView*>( root ->getChildByName("star_ImageView") );

//    star -> runAction(<#cocos2d::Action *action#>);
//    star -> setPosition( star -> getPosition() + Point(100,100) );
//    star -> play
//    int a = star -> getActionTag();
//    int b = 0;
//    setFrameEventCallFunc(CC_CALLBACK_1(HelloWorld::onFrameEvent, this));
//    armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(TestFrameEvent::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    return true;
}

void HelloWorld::frameCallback()
{
    ActionObject* obj = ActionManagerEx::getInstance() -> getActionByName("DemoLogin.json" , "Animation0");
    obj -> setLoop(false);
}

void HelloWorld::btnCallback(Ref* sender, Widget::TouchEventType event)
{
    
}

void HelloWorld::onFinishEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (movementType == LOOP_COMPLETE)
    {
        if (movementID == "TestAni1")
        {
            
        }
        else if (movementID == "FireMax")
        {

        }
    }
}
void HelloWorld::onFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);
    
//    if (!_gridNode->getActionByTag(FRAME_EVENT_ACTION_TAG) || _gridNode->getActionByTag(FRAME_EVENT_ACTION_TAG)->isDone())
//    {
//        _gridNode->stopAllActions();
//        
//        ActionInterval *action =  ShatteredTiles3D::create(0.2f, Size(16,12), 5, false);
//        action->setTag(FRAME_EVENT_ACTION_TAG);
//        _gridNode->runAction(action);
//    }
}


//void HelloWorld::onFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
//{
//    CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);
//    
//    if (!_gridNode->getActionByTag(FRAME_EVENT_ACTION_TAG) || _gridNode->getActionByTag(FRAME_EVENT_ACTION_TAG)->isDone())
//    {
//        _gridNode->stopAllActions();
//        
//        ActionInterval *action =  ShatteredTiles3D::create(0.2f, Size(16,12), 5, false);
//        action->setTag(FRAME_EVENT_ACTION_TAG);
//        _gridNode->runAction(action);
//    }
//}
//vo

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
    
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
