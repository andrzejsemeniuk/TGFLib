//
//  tinyCocos2DCCTargetAction.h
//  productWhackyChoir
//
//  Created by andrzej semeniuk on 6/5/13.
//
//





STRUCT(CCActionProxy) : public CCAction {
    
    CCNodePtr node = 0;
    CCActionPtr action = 0;
    
    CCActionProxy (void) {
        
    }
    
    CCActionProxy(CCNodePtr n, CCActionPtr a) : node(n), action(a) {
        tAssert (node);
        tAssert (action);

        node -> retain();
        action -> retain();
    }
    
    static CCActionProxyPtr create(CCNodePtr n, CCActionPtr a) {
        ccNewWithArgsThenInitAutoreleaseReturn(CCActionProxy,n,a);
    }
    
    virtual 	~CCActionProxy (void) {
            node -> release();
            action -> release();
    }
    
    virtual bool init() {
        return true;
    }
    
    const char * 	description () {
        return "CCTargetAction";
    }
    
    virtual CCObject * 	copyWithZone (CCZone *pZone) {
        CCZone* pNewZone = NULL;
        CCActionProxyPtr pRet = NULL;
        
        if (pZone && pZone->m_pCopyObject) {
            //in case of being called at sub class
            pRet = (CCActionProxyPtr) (pZone->m_pCopyObject);
        } else {
            pRet = new CCActionProxy(node,action);
            pZone = pNewZone = new CCZone(pRet);
        }
        
        CCAction::copyWithZone(pZone);
        CC_SAFE_DELETE(pNewZone);
        return pRet;
    }
    
    virtual bool 	isDone (void) {
        return action -> isDone();
    }
    
    virtual void 	startWithTarget (CCNode *pTarget) {
        action -> startWithTarget(node);
    }
    
    virtual void 	stop (void) {
        action -> stop();
    }
    
    virtual void 	step (float dt) {
        action -> step(dt);
    }
    
    virtual void 	update (float time) {
        action -> update(time);
    }
    
    CCNode * 	getTarget (void) {
        return node;
    }
    
    void setTarget (CCNode *pTarget) {
        
    }
    
    CCNode * 	getOriginalTarget (void) {
        return node;
    }
    
    void 	setOriginalTarget (CCNode *pOriginalTarget) {
        
    }
    
    int 	getTag (void) {
        return action -> getTag();
    }
    
    void setTag (int nTag) {
        action -> setTag(nTag);
    }
};




//inline CCActionProxyPtr aProxy(CCNodePtr n, CCActionPtr a) {
//    return CCActionProxy::create(n,a);
//}




STRUCT(CCFiniteTimeActionProxy) : public CCFiniteTimeAction {
    
    CCNodePtr node = 0;
    CCFiniteTimeActionPtr action = 0;
    
    CCFiniteTimeActionProxy (void) {
        
    }
    
    CCFiniteTimeActionProxy(CCNodePtr n, CCFiniteTimeActionPtr a) : node(n), action(a) {
        tAssert(node);
        tAssert(action);
        
        node -> retain();
        action -> retain();
    }
    
    static CCFiniteTimeActionProxyPtr create(CCNodePtr n, CCFiniteTimeActionPtr a) {
        ccNewWithArgsThenInitAutoreleaseReturn(CCFiniteTimeActionProxy,n,a);
    }
    
    virtual 	~CCFiniteTimeActionProxy (void) {
        node -> release();
        action -> release();
    }
    
    virtual bool init() {
        return true;
    }
    
    const char * 	description () {
        return "CCFiniteTimeActionProxy";
    }
    
    virtual CCObject * 	copyWithZone (CCZone *pZone) {
        CCZone* pNewZone = NULL;
        CCFiniteTimeActionProxyPtr pRet = NULL;
        
        if (pZone && pZone->m_pCopyObject) {
            //in case of being called at sub class
            pRet = (CCFiniteTimeActionProxyPtr) (pZone->m_pCopyObject);
        } else {
            pRet = new CCFiniteTimeActionProxy(node,action);
            pZone = pNewZone = new CCZone(pRet);
        }
        
        CCFiniteTimeAction::copyWithZone(pZone);
        
        CC_SAFE_DELETE(pNewZone);
        return pRet;
    }
    
    virtual bool 	isDone (void) {
        return action -> isDone();
    }
    
    virtual void 	startWithTarget (CCNode *pTarget) {
        action -> startWithTarget(node);
    }
    
    virtual void 	stop (void) {
        action -> stop();
    }
    
    virtual void 	step (float dt) {
        action -> step(dt);
    }
    
    virtual void 	update (float time) {
        action -> update(time);
    }
    
    CCNode * 	getTarget (void) {
        return node;
    }
    
    void 	setTarget (CCNode *pTarget) {
        
    }
    
    CCNode * 	getOriginalTarget (void) {
        return node;
    }
    
    void 	setOriginalTarget (CCNode *pOriginalTarget) {
        
    }
    
    int 	getTag (void) {
        return action -> getTag();
    }
    
    void 	setTag (int nTag) {
        action -> setTag(nTag);
    }
    
    float 	getDuration (void) {
        return action -> getDuration();
    }
    
    void 	setDuration (float duration) {
        action -> setDuration(duration);
    }
    
    virtual CCFiniteTimeAction * 	reverse (void) {
        return CCFiniteTimeActionProxy::create(node, action -> reverse());
    }
};




//inline CCFiniteTimeActionProxyPtr aProxy(CCNodePtr n, CCFiniteTimeActionPtr a) {
//    return CCFiniteTimeActionProxy::create(n,a);
//}





STRUCT(CCActionIntervalProxy) : public CCActionInterval {
    
    CCNodePtr node = 0;
    CCActionIntervalPtr action = 0;
    
    CCActionIntervalProxy (void) {
        
    }
    
    CCActionIntervalProxy(CCNodePtr n, CCActionIntervalPtr a) : node(n), action(a) {
        tAssert(node);
        tAssert(action);
        
        node -> retain();
        action -> retain();
    }
    
    static CCActionIntervalProxyPtr create(CCNodePtr n, CCActionIntervalPtr a) {
        ccNewWithArgsThenInitAutoreleaseReturn(CCActionIntervalProxy,n,a);
    }
    
    virtual ~CCActionIntervalProxy (void) {
        node -> release();
        action -> release();
    }
    
    virtual bool init() {
        return true;
    }
    
    const char * 	description () {
        return "CCActionIntervalProxy";
    }
    
    virtual CCObject * 	copyWithZone (CCZone *pZone) {
        CCZone* pNewZone = NULL;
        CCActionIntervalProxyPtr pRet = NULL;
        
        if (pZone && pZone->m_pCopyObject) {
            //in case of being called at sub class
            pRet = (CCActionIntervalProxyPtr) (pZone->m_pCopyObject);
        } else {
            pRet = new CCActionIntervalProxy(node,action);
            pZone = pNewZone = new CCZone(pRet);
        }
        
        CCActionInterval::copyWithZone(pZone);
        
        CC_SAFE_DELETE(pNewZone);
        return pRet;
    }
    
    virtual bool 	isDone (void) {
        return action -> isDone();
    }
    
    virtual void 	startWithTarget (CCNode *pTarget) {
        action -> startWithTarget(node);
    }
    
    virtual void 	stop (void) {
        action -> stop();
    }
    
    virtual void 	step (float dt) {
        action -> step(dt);
    }
    
    virtual void 	update (float time) {
        action -> update(time);
    }
    
    CCNode * getTarget (void) {
        return node;
    }
    
    void setTarget (CCNode *pTarget) {
        
    }
    
    CCNode * getOriginalTarget (void) {
        return node;
    }
    
    void setOriginalTarget (CCNode *pOriginalTarget) {
        
    }
    
    int 	getTag (void) {
        return action -> getTag();
    }
    
    void 	setTag (int nTag) {
        action -> setTag(nTag);
    }
    
    float 	getDuration (void) {
        return action -> getDuration();
    }
    
    void 	setDuration (float duration) {
        action -> setDuration(duration);
    }
    
    virtual CCActionInterval * 	reverse (void) {
        return CCActionIntervalProxy::create(node, action -> reverse());
    }
    
    void 	setAmplitudeRate (float amp) {
        action -> setAmplitudeRate(amp);
    }
    
    float 	getAmplitudeRate (void) {
        return action -> getAmplitudeRate();
    }
};




//inline CCActionIntervalProxyPtr aProxy(CCNodePtr n, CCActionIntervalPtr a) {
//    return CCActionIntervalProxy::create(n,a);
//}



