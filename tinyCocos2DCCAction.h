    //
    //  tinyCocos2DCCAction.h
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 5/2/14.
    //
    //


STRUCT (CCActionInstantWrapper) : public CCActionInterval {
    
    static CCActionInstantWrapperPtr create(CCActionInstantPtr p);
    
    virtual void startWithTarget(CCNode *pTarget) override;
    
    virtual void update(float time) override;
    
protected:
    
    virtual bool init(CCActionInstantPtr p);
    
    virtual ~CCActionInstantWrapper();
    
private:
    
    CCActionInstantPtr m_pInnerAction = 0;
    bool executed = false;
};



inline CCActionIntervalPtr aiAction         (CCActionInstantPtr a)                  { return CCActionInstantWrapper::create(a); }







STRUCT (CCEaseUpdate) : public CCActionEase
{
    typedef std::function<float (float)> Function;
    
    Function function = 0;
    
    virtual void update (float time) override;
    
    virtual CCActionInterval* reverse (void);
    
    virtual bool init (CCActionInterval* action, Function f);
    
    static CCEaseUpdate* create(CCActionInterval* pAction, Function f);
};


inline CCEaseUpdatePtr eUpdate              (CCActionIntervalPtr a, CCEaseUpdate::Function f) { return CCEaseUpdate::create(a,f); }

#define eFormula(ACTION,...) eUpdate( (ACTION), [] (float t) -> float { return __VA_ARGS__ ; } )
    // USAGE: eFormula(myAction, sinf(t/2)*t );






STRUCT (CCEaseCurve) : public CCActionEase
{
    
    
    
    struct Point {
        
        float v = 0;
        
        tiny::Math::float_01 t = 0;
        
        Point(float t_ = 0, float v_ = 0) : t(t_), v(v_)        {}
        Point(Vec2 p)                                           { t=p.x; v=p.y; }
        
        inline friend std::ostream& operator << (std::ostream& o, const Point& p) { return o << '{' << p.t << ',' << p.v << '}'; }
        
        static std::vector<Point> generateZigZagWithSpans(const Point& from,
                                                          const Point& to,
                                                          const float span0,
                                                          const float span1,
                                                          const int points);
        
        static std::vector<Point> generateZigZagWithDamping(const Point& from,
                                                            const Point& to,
                                                            const float dv0,
                                                            const float dv1,
                                                            const float dt,
                                                            const float ddt);
    };
    
    static CCEaseCurvePtr create(CCActionIntervalPtr a, float v, bool reverse = false) ;
    static CCEaseCurvePtr create(CCActionIntervalPtr a, Point p, bool reverse = false) ;
    static CCEaseCurvePtr create(CCActionIntervalPtr a, Point p1, Point p2, bool reverse = false) ;
    static CCEaseCurvePtr create(CCActionIntervalPtr a, Point p1, Point p2, Point p3, bool reverse = false) ;
    static CCEaseCurvePtr create(CCActionIntervalPtr a, const std::vector<Point>& p) ;
    
    CCActionIntervalPtr reverse(void) ;
    void update(float time) override ;
    bool init(CCActionIntervalPtr a, const std::vector<Point>& p) ;
    
    static void test() ;
    static void test(CCEaseCurvePtr p) ;
    
protected:
    
    int find0(float t) ;
    
    int find(float t) ;
    
    float average(float v0, float v1, float t0, float t1, float t) ;
    
    float average1(float v0, float v1, float t0, float t1, float t) ;
    
    float curve (const Point& p0, const Point& p1, const Point& p2, float t) ;
    
    int classify (int n) ;
    
    float calculate (const float t) ;
    
    std::vector<Point> points;
};





inline CCEaseCurvePtr eCurve        (CCActionIntervalPtr a, float v, bool reverse = false)                                      { return CCEaseCurve::create(a,v,reverse); }
inline CCEaseCurvePtr eCurve        (CCActionIntervalPtr a, CCEaseCurve::Point p, bool reverse = false)                         { return CCEaseCurve::create(a,p,reverse); }
inline CCEaseCurvePtr eCurve        (CCActionIntervalPtr a, CCEaseCurve::Point p1, CCEaseCurve::Point p2, bool reverse = false) { return CCEaseCurve::create(a,p1,p2,reverse); }
inline CCEaseCurvePtr eCurve        (CCActionIntervalPtr a, CCEaseCurve::Point p1, CCEaseCurve::Point p2, CCEaseCurve::Point p3, bool reverse = false) { return CCEaseCurve::create(a,p1,p2,p3,reverse); }
inline CCEaseCurvePtr eCurveVector  (CCActionIntervalPtr a, const std::vector<CCEaseCurve::Point>& p)                           { return CCEaseCurve::create(a,p); }













