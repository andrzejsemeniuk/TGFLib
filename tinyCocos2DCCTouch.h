    //
    //  tinyCocos2DCCTouch.h
    //  productBots
    //
    //  Created by Andrzej Semeniuk on 9/2/13.
    //
    //

#pragma once


namespace Touch
{
    enum class Type : char {
        Began,
        Moved,
        Ended,
        Cancelled
    };
    
    
    void describe(CCTouchPtr touch);
    
    
    bool isSwipeLeft (CCTouchPtr touch);
    bool isSwipeRight(CCTouchPtr touch);
    bool isSwipeDown (CCTouchPtr touch);
    bool isSwipeUp   (CCTouchPtr touch);
    
    

    
    STRUCT (CCData) {
        CCNodePtr view = 0;
        
        CCPoint pointInView;
        CCPoint pointOnScreen;
        CCRatio ratioOnScreen;
        CCTouch touch;
        Type type;
        
        CCData() ;
        CCData(CCPoint pointOnScreen, Type type) ;
        CCData(CCNodePtr view, CCTouchPtr touch, Type type) ;
        
        static std::vector<CCData> create(CCNodePtr view, vectorCRef(CCTouchPtr) touches, Type type) ;
        
        bool isSlideInView(float distance PIXELS) const ;
    };
    
    
    
    
    STRUCT(CCLayer) : public cocos2d::Layer {
        
        ______  float       getTimeOfLastTouch                      () const ;
        
        static  CCLayerPtr  create                                  (bool touchEnabled = true) ;
        
        virtual bool        init                                    (bool touchEnabled) ;
        virtual bool        init                                    () override ;
        
//        virtual void        registerWithTouchDispatcher             () override ;
        
        virtual bool        onTouchBegan                            (CCTouchPtr touch, CCEventPtr event)  ;
        virtual void        onTouchMoved                            (CCTouchPtr touch, CCEventPtr event)  ;
        virtual void        onTouchEnded                            (CCTouchPtr touch, CCEventPtr event)  ;
        virtual void        onTouchCancelled                        (CCTouchPtr touch, CCEventPtr event)  ;
        
        virtual void        onTouchesBegan                          (vectorCRef(CCTouchPtr) touches, CCEventPtr event)  ;
        virtual void        onTouchesMoved                          (vectorCRef(CCTouchPtr) touches, CCEventPtr event)  ;
        virtual void        onTouchesEnded                          (vectorCRef(CCTouchPtr) touches, CCEventPtr event)  ;
        virtual void        onTouchesCancelled                      (vectorCRef(CCTouchPtr) touches, CCEventPtr event)  ;
        
        virtual bool        touchProcess                            (CCTouchPtr touch, CCPoint screen, Touch::Type type) ;
        virtual bool        touchesProcess                          (vectorCRef(CCTouchPtr) touches, CCPoint screen, Touch::Type type) ;
        
        virtual void        onAccelerate                            (CCAccelerationPtr a) ;
        
        
        ______  void        setEnabledTouch                         (bool flag);
        ______  void        setEnabledTouches                       (bool flag);
        ______  void        setEnabledAcceleration                  (bool flag);
        
        
    protected:
        
        typedef std::function<bool(CCTouchPtr touch, CCPoint location, Touch::Type type)> TouchCallback;
        typedef std::function<bool(vectorCRef(CCTouchPtr) touches, CCPoint location, Touch::Type type)> TouchesCallback;
        
        bool containsLocationOfTouch(CCNodePtr node, CCPoint screen) ;
        
        void addTouchCallback(CCNodePtr node, const TouchCallback& f) ;
        void addTouchesCallback(CCNodePtr node, const TouchesCallback& f) ;
        
        virtual void removeTouchCallback(CCNodePtr node) final ;
        virtual void removeTouchesCallback(CCNodePtr node) final ;
        
        virtual ~CCLayer() ;
        
        
    private:
        
        std::list<std::pair<CCNodePtr,TouchCallback>> listOfTouchTargetAndCallback;
        std::list<std::pair<CCNodePtr,TouchesCallback>> listOfTouchesTargetAndCallback;
        
        tiny::Time::Time timeLastTouch = 0;
        
        struct {
            CCEventListenerTouchOneByOnePtr touch = 0;
        } listener;

    };
    
    
    
}