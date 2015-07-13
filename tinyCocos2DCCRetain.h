	//
	//  tinyCocos2DCCRetain.h
	//  productBots
	//
	//  Created by Andrzej Semeniuk on 10/13/13.
	//
	//

STRUCT (CCRetain) : public CCActionInstant {
    
    static CCRetainPtr create(CCObjectPtr o) ;
    
    static CCRetainPtr create(vectorCRef(CCObjectPtr) p) ;
    
    virtual void update(float time) override ;
    
protected:
    
    virtual bool init(vectorCRef(CCObjectPtr) p) ;
    
    virtual ~CCRetain() ;
    
private:
    
    vector<CCObjectPtr> objects;
};

inline CCRetainPtr          aRetain         (CCObjectPtr o)                     { return CCRetain::create(o); }
inline CCActionIntervalPtr  aiRetain        (CCObjectPtr o)                     { return aiAction(CCRetain::create(o)); }
inline CCActionIntervalPtr  aiRetain        (float delay, CCObjectPtr o)        { return aiDelay(delay,CCRetain::create(o)); }
inline CCRetainPtr          aRetain         (const vector<CCObjectPtr>& o)      { return CCRetain::create(o); }
inline CCActionIntervalPtr  aiRetain        (const vector<CCObjectPtr>& o)      { return aiAction(CCRetain::create(o)); }




