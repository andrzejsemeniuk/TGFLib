    //
    //  tinyCocos2DCCCallBlock.h
    //  productWhackyChoir
    //
    //  Created by andrzej semeniuk on 6/5/13.
    //
    //




STRUCT (CCCallBlock) : public CCActionInstant {
    
    typedef std::function<void ()> Function;
    
    static CCCallBlockPtr create (Function p) ;
    
    virtual void update (float time) override ;
    
protected:
    
    virtual bool init (Function p) ;
    
private:
    
    Function block = 0;
};

#define ccDelayedCallBlock(TIME,FUNC)       (CCSequence::create(CCDelayTime::create( TIME ),CCCallBlock::create( FUNC ), 0)
#define ccCallBlock(FUNC)                   (CCCallBlock::create( FUNC ))
#define ccCallThis(...)                     (CCCallBlock::create([this] __VA_ARGS__ ))
#define aiCallThis(...)                     aiAction(CCCallBlock::create([this] __VA_ARGS__ ))
#define ccCallMe                            ccCallThis

inline CCActionInstantPtr aFork(CCNodePtr target, CCActionPtr a) {
    auto f = [target,a]() {
        target -> runAction(a);
    };
    return ccCallBlock(f);
}

inline CCActionInstantPtr   aCall   (CCCallBlock::Function f)                { return CCCallBlock::create(f); }
    //inline CCActionIntervalPtr  aiCall  (CCCallBlock::Function f)                { return aiAction(aCall(f)); }
inline CCActionIntervalPtr  aiCall  (CCCallBlock::Function f)                { return f ? aiAction(aCall(f)) : aiEmpty(); }
inline CCActionIntervalPtr  aiCall  (float delay, CCCallBlock::Function f)   { return aiDelay(delay,aiCall(f)); }






STRUCT (CCCallBlockWithData) : public CCActionInstant {
    
    typedef vector<boost::any> Data;
    
    typedef std::function<void (Data&)> Function;
    
    Data data;
    
    static CCCallBlockWithDataPtr create (Function p) ;
    
    virtual void update (float time) override ;
    
    
protected:
    
    virtual bool init (Function p) ;
    
private:
    
    Function block = 0;
};

inline CCActionInstantPtr   aCall   (CCCallBlockWithData::Function f)                   { return CCCallBlockWithData::create(f); }
inline CCActionIntervalPtr  aiCall  (CCCallBlockWithData::Function f)                   { return aiAction(aCall(f)); }
inline CCActionIntervalPtr  aiCall  (float delay, CCCallBlockWithData::Function f)      { return aiDelay(delay,aiCall(f)); }







STRUCT (CCCallBlockIntervalWithData) : public CCActionInterval {
    
    typedef vector<boost::any> Data;
    
    typedef std::function<void (Data&,float)> Function;
    
    Data data;
    
    static CCCallBlockIntervalWithDataPtr create (float duration, Function p) ;
    
    virtual void update (float time) override ;
    
    virtual void startWithTarget(CCNodePtr p) override ;
    
protected:
    
    virtual bool init (float duration, Function p) ;
    
    virtual ~CCCallBlockIntervalWithData() ;
    
private:
    
    Function block = 0;
};

inline CCCallBlockIntervalWithDataPtr aiCall    (float duration, CCCallBlockIntervalWithData::Function f) { return CCCallBlockIntervalWithData::create(duration,f); }







STRUCT (CCCallBlockInterval) : public CCActionInterval {
    
    typedef std::function<CCActionIntervalPtr ()> Function;
    
    static CCCallBlockIntervalPtr create (Function p);
    
    virtual void update (float time) override;
    
protected:
    
    virtual bool init (Function p);
    
    virtual ~CCCallBlockInterval();
    
private:
    
    CCActionIntervalPtr product = 0;
    
    Function block = 0;
};

inline CCActionIntervalPtr aiBlock  (CCCallBlockInterval::Function f) { return CCCallBlockInterval::create(f); }

#define ccCallThisInterval(...) aiBlock( [this] () -> CCActionIntervalPtr __VA_ARGS__ )







STRUCT (CCCallBlockIntervalWithSelf) : public CCActionInterval {
    
    typedef vector<boost::any> Data;
    
    typedef std::function<void (CCCallBlockIntervalWithSelf &,float)> Function;
    
    Data data;
    
    static CCCallBlockIntervalWithSelfPtr create (float duration, Function f);
    
    virtual void update (float time) override ;
    
    virtual void startWithTarget (CCNodePtr p) override ;
    
    inline bool isFirstTime () const { return dt < 0.; }
    
protected:
    
    virtual bool init (float duration, Function f);
    
    virtual ~CCCallBlockIntervalWithSelf();
    
private:
    
    float dt = -1.f;
    
    std::function<void (CCCallBlockIntervalWithSelf&,float)> block = 0;
};

inline CCActionIntervalPtr aiBlock  (float duration, CCCallBlockIntervalWithSelf::Function f) { return CCCallBlockIntervalWithSelf::create(duration, f); }







STRUCT (CCCallBlockIntervalWithUpdate) : public CCActionInterval {
    
    typedef std::function<void (float)> Function;
    
    static CCCallBlockIntervalWithUpdatePtr create (float duration, Function f);
    
    virtual void update (float time) override ;
    
protected:
    
    virtual bool init (float duration, Function f);
    
    virtual ~CCCallBlockIntervalWithUpdate() ;
    
private:
    
    Function block = 0;
};

inline CCActionIntervalPtr aiBlock  (float duration, CCCallBlockIntervalWithUpdate::Function f) { return CCCallBlockIntervalWithUpdate::create(duration, f); }
inline CCActionIntervalPtr aiDuring (float duration, CCCallBlockIntervalWithUpdate::Function f) { return CCCallBlockIntervalWithUpdate::create(duration, f); }
inline CCActionIntervalPtr aiDuring (float duration, std::function<void ()> f)                  { return CCCallBlockIntervalWithUpdate::create(duration, [f] (float dt) { f(); }); }









STRUCT (CCCondition) : public CCActionInstant
{
    typedef std::function<bool(float)> Function;
    
    static CCConditionPtr create (Function p) ;
    
    CCCondition() {}
    
    virtual ~CCCondition();
    
    virtual void update (float dt) override;
    
    virtual bool isDone (void);
    
protected:
    
    virtual bool init (Function p);
    
    bool done = false;
    Function block = 0;
};


STRUCT (CCConditionLoop) : public CCRepeatForever
{
    static CCConditionLoopPtr create (CCConditionPtr p) ;
    
    CCConditionLoop() {}
    
    virtual ~CCConditionLoop();
    
    virtual void step (float dt) override;
    
    virtual bool isDone (void);
    
protected:
    
    virtual bool init (CCConditionPtr p);
};

inline CCConditionLoopPtr aiWhile   (CCCondition::Function p) { return CCConditionLoop::create(CCCondition::create(p)); }
inline CCConditionLoopPtr aiUntil   (CCCondition::Function p) { return CCConditionLoop::create(CCCondition::create([p] (float dt) { return not p(dt); })); }





