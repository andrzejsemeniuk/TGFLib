    //
    //  CommonCocos2D.h
    //  productWhackyChoir
    //
    //  Created by andrzej semeniuk on 10/22/12.
    //
    //

#pragma once


#include "tinyCocos2DTypes.h"

#include "tinyMath.h"
#include "tinyUtility.h"
#include "tinyVariable.h"
    //#include "tinyApplication.h"

#include <forward_list>
#include <algorithm>
#include <vector>

#include <boost/any.hpp>





#define ccDictionaryForEach CCDICT_FOREACH

#define ccArrayForEach CCARRAY_FOREACH
#define ccArrayForEachBlock(IDENTIFIER,...) do { CCObjectPtr IDENTIFIER = 0; CCARRAY_FOREACH __VA_ARGS__ } while(0)
    //#define ccSetForEach(SET,ITERATOR)  for(CCSetIterator ITERATOR = (SET)->begin(); ITERATOR != (SET)->end(); ITERATOR++ )


#define SELECTOR_SCHEDULE schedule_selector
#define SELECTOR_CALLFUNC callfunc_selector
#define SELECTOR_CALLFUNC_N callfuncN_selector
#define SELECTOR_CALLFUNC_ND callfuncND_selector
#define SELECTOR_CALLFUNC_O callfuncO_selector
#define SELECTOR_MENU menu_selector
#define SELECTOR_EVENT event_selector
#define SELECTOR_COMPARE compare_selector



#define ANGLE_RATIO(RADIANS) (RADIANS / tiny::Math::TwoPI)

#define ANGLE_RATIO_TO_RELATIVE( TARGET, RELATIVE ) \
(ANGLE_RATIO(relative -> getRotation() - target -> getRotation()))

#define ccToRadians CC_DEGREES_TO_RADIANS
#define ccToDegrees CC_RADIANS_TO_DEGREES

#define ccDegreesToRadians CC_DEGREES_TO_RADIANS
#define ccRadiansToDegrees CC_RADIANS_TO_DEGREES

#define ccAngleDegreesToRadians CC_DEGREES_TO_RADIANS
#define ccAngleRadiansToDegrees CC_RADIANS_TO_DEGREES


#define CC_SCHEDULE_METHOD(OBJECT,METHOD,DELAY) \
(OBJECT) -> runAction(CCSequence::create( \
CCDelayTime::create( DELAY ), \
CCCallFunc::create( (OBJECT) ,& METHOD )));





#define ccDirector          (CCDirector::getInstance())
#define ccTouchDispatcher   (ccDirector -> getTouchDispatcher())
#define ccWindowSize        (CCDirector::getInstance()->getWinSize())
#define ccRunningScene      (ccDirector->getRunningScene())
#define ccCurrentScene      (ccDirector->getRunningScene())




#define ccSafeReleaseNull   CC_SAFE_RELEASE_NULL
#define ccSafeRelease       CC_SAFE_RELEASE
#define ccSafeDelete        CC_SAFE_DELETE
#define ccSafeDeleteArray   CC_SAFE_DELETE_ARRAY
#define ccUnusedParameter   CC_UNUSED_PARAM

inline void         ccSafeRetain    (CCObjectPtr p)     { if (p) p->retain(); }





#define ccNewAutoreleaseReturn(TYPE,...)   \
TYPE * r = new TYPE ( __VA_ARGS__ ); if (r) { r -> autorelease(); } else { ccSafeReleaseNull( r ); } return r

#define ccNewInitAutoreleaseReturn(TYPE)   \
TYPE * r = new TYPE (); if (r and r->init()) { r -> autorelease(); } else { ccSafeReleaseNull( r ); } return r

#define ccNewWithArgsThenAutoreleaseReturn(TYPE,...)      \
TYPE * r = new TYPE ( __VA_ARGS__ ); if (r) { r -> autorelease(); } else { ccSafeReleaseNull( r ); } return r

#define ccNewWithArgsThenInitAutoreleaseReturn(TYPE,...) \
TYPE * r = new TYPE ( __VA_ARGS__ ); if (r and r->init()) { r -> autorelease(); } else { ccSafeReleaseNull( r ); } return r

#define ccNewThenInitWithArgsAutoreleaseReturn(TYPE,...) \
TYPE * r = new TYPE (); if (r and r->init( __VA_ARGS__ )) { r -> autorelease(); } else { ccSafeReleaseNull( r ); } return r

#define ccInitWithArgsAutoreleaseReturn(r,...)   \
if (r and r->init( __VA_ARGS__ )) { r -> autorelease(); } else { ccSafeReleaseNull( r ); } return r



#define ccCreate(TYPE) static TYPE##Ptr create() { ccNewInitAutoreleaseReturn( TYPE ); }

#define ccCreateWithParameters(TYPE)  static TYPE##Ptr create(ParametersCRef p) { ccNewThenInitWithArgsAutoreleaseReturn( TYPE , p ); }


































namespace tiny {
    namespace Cocos2D {
        
        using namespace cocos2d;
        
        
        
        
        
        
        
        
        
        
        
        static struct _CCNull {
            CCRect rect = {0,0,0,0};
            CCNodePtr node = 0;
            CCSpritePtr sprite = 0;
            CCObjectPtr object = 0;
            CCPoint point = Vec2(0,0);
            CCPoint vector = Vec2(0,0);
            
            _CCNull() {}
        } const CCNull;
        
        
        
        
        
        
        
        
        inline void             randomReset     (unsigned int p)                        { srand(p); }
        
        inline double           random01        ()                                      { return CCRANDOM_0_1(); }
        inline float            random01f       ()                                      { return CCRANDOM_0_1(); }
        inline double           random11        ()                                      { return CCRANDOM_MINUS1_1(); }
        inline float            random11f       ()                                      { return CCRANDOM_MINUS1_1(); }
        inline double           randomSign      ()                                      { return random11() < 0. ? -1 : +1; }
        inline float            randomSignf     ()                                      { return random11f() < 0 ? -1 : +1; }
        
        inline double           random          (double a, double b)                    { return a==b ? a : min(a,b) + random01() * fabs(b-a); }
        inline double           random          (double a)                              { return a < 0. ? random(a,0.) : random(0.,a); }
        inline float            randomf         (float a, float b)                      { return a==b ? a : min(a,b) + random01f() * fabs(b-a); }
        inline float            randomf         (float a)                               { return a < 0.f ? randomf(a,0.f) : randomf(0.f,a); }

        inline double           randomSign      (double a)                              { return randomSign()*random(a); }
        inline float            randomSignf     (float a)                               { return randomSign()*random(a); }
        inline double           randomSign      (double a, double b)                    { return randomSign()*random(a,b); }
        inline float            randomSignf     (float a, float b)                      { return randomSign()*random(a,b); }

        inline double           randomSigma     (double a, double p = 1)                { return a < p ? random(a,p/a) : random(p/a,a); }
        inline float            randomSigmaf    (float a, float p = 1.f)                { return a < p ? randomf(a,p/a) : randomf(p/a,a); }
        
        inline CCPoint          random          (CCPoint from, CCPoint to)              { return Vec2(random(from.x,to.x),random(from.y,to.y)); }
        
        inline GLubyte          random          (const Span<GLubyte>& r)                { return clamp(0,255,static_cast<GLubyte>(static_cast<int>(random(r.from,r.to)))); }

        inline float            randomRangef    (RangeCRef r)                           { return r.from == r.to ? r.from : randomf(r.from,r.to); }
        inline float            randomSignRangef(RangeCRef r)                           { return randomSign(randomRangef(r)); }

        template<class T> T     randomSpan      (const Span<T>& r)                      { return random(r.from,r.to); }
        
        inline bool             randomBool      ()                                      { return random11() < 0.; }
        
        inline int              pick            (unsigned long size)                    { return (int)tiny::Math::pick01(random01(),size); }
        inline bool             unpick          (unsigned long size)                    { return not pick(size); }
        inline int              pick            (int from, int upto)                    { return from+pick(upto-from); }
        
        inline const string&    pick_string     (const std::vector<std::string>& v)     { return v[pick(v.size())]; }
        
        inline const double&    pick            (const std::vector<double>& v)          { return v[pick(v.size())]; }
        inline const double&    pick_double     (const std::vector<double>& v)          { return v[pick(v.size())]; }
        inline const float&     pick_float      (const std::vector<float>& v)           { return v[pick(v.size())]; }
        
        template<typename T> const T& pick      (const std::vector<T>& v)               { return v.at(pick(v.size())); }
        
        ______ int              pickDifferent   (unsigned long size, unsigned long n);
        
        
        template<typename K, class V>
        const K& pick(const std::map<K,V>& m)
        {
            int i = pick(m.size());
            auto e = m.begin();
            while(0 < i--) {
                e++;
            }
            return e -> first;
        }
        
        template<typename T>
        const T& pick(const std::set<T>& v)
        {
            int i = pick(v.size());
            auto e = v.begin();
            while(0 < i--) {
                e++;
            }
            return *e;
        }
        
        template<typename T> T pickFromPriorities(const map<T,float_01>& p) {
            auto r = random01();
            T pick;
            float_01 best = 1;
            for(auto e:p) {
                if (r < e.second and e.second <= best) {
                    best = e.second;
                    pick = e.first;
                }
            }
            return pick;
        }
        
        template<typename T> T pickFromPriorities(const map<T,float_01>& p, float_01 r) {
            T pick;
            float_01 best = 1;
            for(auto e:p) {
                if (r < e.second and e.second <= best) {
                    best = e.second;
                    pick = e.first;
                }
            }
            return pick;
        }
        
        template<typename K> K pickDecrementPurge(map<K,int>& m, K none) {
            while(not m.empty()) {
                K k = pick(m);
                auto & e = m.at(k);
                if (e.second) {
                    e.second--;
                    if (e.second < 1) {
                        m.erase(e);
                    }
                    return k;
                }
                m.erase(k);
            }
            return none;
        }
        
        
        
        
        
        
        template<class T> std::vector<T>                add                 (std::vector<T> p, std::pair<double,double> r)
        {
            for(autoRef i:p) { i += random(r.first,r.second); }
            
            return p;
        }
        
        template<class T> std::vector<T>                multiply            (std::vector<T> p, std::pair<double,double> r)
        {
            for(autoRef i:p) { i *= random(r.first,r.second); }
            
            return p;
        }
        

        
        
        
        
        
        
        inline ubyte            to255               (float v)               { v = tiny::Math::clamp01(v); return static_cast<ubyte>(floor(v==1.00 ? 255.f : v * 256)); }
        inline float            from255             (int v)                 { return tiny::Math::clamp01(v / 255.f); }
        inline unsigned char    to_uchar            (float v)               { return static_cast<unsigned char>(to255(v)); }
        
        
        
        
        void init();
        
        
        
        
        
        
        inline  CCRatio     ccr                                     (float x, float y)                  { return Vec2(x,y); }
        
        
        
        
        
        
        extern CCSize sizeScreen;
        
        
        
        ______ double       ccScreenDiagonal                        () ;
        
        inline CCSizeCRef   screenGetSize                           ()                                  { return sizeScreen; }
        inline float        screenGetWidth                          ()                                  { return sizeScreen.width; }
        inline float        screenGetHeight                         ()                                  { return sizeScreen.height; }
        inline CCPoint      screenGetCenter                         ()                                  { return sizeScreen/2.; }
        
        inline CCPoint      screenGetPoint                          (CCPoint ratio)                     { return Vec2(ratio.x * sizeScreen.width, ratio.y * sizeScreen.height); }
        inline CCPoint      screenGetPoint                          (float ratiox, float ratioy)        { return Vec2(ratiox * sizeScreen.width, ratioy * sizeScreen.height); }
        inline CCRatio      screenGetRatio                          (CCPoint p)                         { return {p.x/screenGetWidth(),p.y/screenGetHeight()}; }
        inline CCRatio      screenGetRatio                          (float x, float y)                  { return {x/screenGetWidth(),y/screenGetHeight()}; }
        inline bool         screenContainsPoint                     (CCPoint p)                         { return 0 <= p.x and 0 <= p.y and p.x <= screenGetWidth() and p.y <= screenGetHeight(); }
        inline bool         screenContainsRatio                     (CCRatio p)                         { return 0 <= p.x and 0 <= p.y and p.x <= 1 and p.y <= 1; }

        inline float        screenGetAspectRatioYtoX                ()                                  { return screenGetHeight()/screenGetWidth(); }
        inline float        screenGetAspectRatioXtoY                ()                                  { return screenGetWidth()/screenGetHeight(); }
        inline CCRatio      screenGetAspectRatio                    ()                                  { return Vec2(screenGetAspectRatioXtoY(),screenGetAspectRatioYtoX()); }

        inline bool         screenIsResolutioniPhone3               ()                                  { return sizeScreen.width == 480 or sizeScreen.height == 480; }
        inline bool         screenIsResolutioniPhone4               ()                                  { return sizeScreen.width == 960 or sizeScreen.height == 960; }
        inline bool         screenIsResolutioniPhone5               ()                                  { return sizeScreen.width == 1136 or sizeScreen.height == 1136; }
        inline bool         screenIsResolutioniPad2                 ()                                  { return sizeScreen.width == 1024 or sizeScreen.height == 1024; }
        inline bool         screenIsResolutioniPad3                 ()                                  { return sizeScreen.width == 2048 or sizeScreen.height == 2048; }
        
        inline CCPoint      screenGetDeviceSizeOffset               ()                                  { return screenIsResolutioniPhone5() ? CCPoint(0,0) : CCPoint(-88,0); }
        
        
        
        
        
        
        struct CCAngle;
        struct Degrees;
        struct Radians;
        
        
        
        STRUCT (AngleRatio)
        {
            
            static float toRadians      (float ratio)   { return ratio * tiny::Math::twopi; }
            static float fromRadians    (float radians) { return radians / tiny::Math::twopi; }
            static float toDegrees      (float ratio)   { return ratio * 360.; }
            static float fromDegrees    (float degrees) { return degrees / 360.; }
            
            static float normalize(float angle) {
                if (angle < -1.)
                    return angle + (int) angle + 1;
                if (1. < angle)
                    return angle - (int) angle;
                return angle;
            }
            
            static float toRelative(CCNodePtr target, CCNodePtr relative) { return normalize(fromDegrees(relative -> getRotation()) - fromDegrees(target -> getRotation())); }
        };
        
        
        
        
        STRUCT (Degrees)
        {
            float value = 0;
            ______                  Degrees                     (float v = 0) : value(v) {}
            ______                  Degrees                     (CCPoint p)                 { value=ccToDegrees(p.getAngle()); }
            ______                  Degrees                     (CCAngle p);
            ______                  Degrees                     (Radians p);
            
            ______ Radians          asRadians                   () const;
            ______ CCAngle          asCCAngle                   () const;
            
            inline float            difference                  (DegreesCRef p) const           { return 180. - fabs(fmod(fabs(value-p.value),360.f) - 180.f); }
            inline float            delta                       (DegreesCRef p) const           { return fmod(p.value-value,360.f); }
            
            inline float            normalized                  () const                        { return fmod(value,360.f); } //tiny::Math::clamp(0,360,value,true); }
            inline float            normalizedTo180180          () const                        { return tiny::Math::normalizeTo180180(value); }
            inline float            normalize                   ()                              { return value = normalized(); }
            inline float            normalizeTo180180           ()                              { return value = normalizedTo180180(); }
            
            inline DegreesRef       operator =                  (float v)                       { value = v; return *this; }
            inline DegreesRef       operator +=                 (float p)                       { value += p; return *this; }
            inline DegreesRef       operator -=                 (float p)                       { value -= p; return *this; }
            inline DegreesRef       operator *=                 (float p)                       { value *= p; return *this; }
            inline DegreesRef       operator /=                 (float p)                       { value /= p; return *this; }
            inline Degrees          operator -                  () const                        { return - value; }
            inline                  operator float              () const                        { return value; }

            inline bool             isDirectionCW              () const                         { return value <= 0; }
            inline bool             isDirectionCCW              () const                        { return 0 <= value; }
            inline bool             isDirectionSame             (DegreesCRef p, float delta) const      { return not isDirectionDifferent(p,delta); }
            ______ bool             isDirectionDifferent        (DegreesCRef p, float delta) const;
            
            inline bool             equals                      (float r, float delta = 0.0001f) const  { return tiny::Math::equal(value,r,delta); }
            inline float            cosf                        () const                        { return ::cosf(ccDegreesToRadians(value)); }
            inline float            sinf                        () const                        { return ::sinf(ccDegreesToRadians(value)); }
            inline CCVector         asVector                    () const                        { return CCPoint::forAngle(ccDegreesToRadians(value)); }
            
            static std::vector<Degrees> generateFromToBy        (double from, double to, double delta);
            static std::vector<Degrees> generateToBy            (double to, double delta);
            static std::vector<Degrees> generateCountBy         (int count, double by);
            static std::vector<Degrees> generateCountByFrom     (int count, double by, double from);
            static std::vector<Degrees> generateCircleCount     (double count);
            static std::vector<Degrees> generateCircleBy        (double delta);
            
            static const Degrees Zero;
            static const Degrees HalfCircle;
            static const Degrees Circle;

        };
        
        
        
        STRUCT (CCAngle)
        {
            float value = 0;
            ______                  CCAngle                     (float v = 0) : value(v) {}
            ______                  CCAngle                     (CCPoint p)                     { value=-ccToDegrees(p.getAngle()); }
            ______                  CCAngle                     (Degrees p);
            ______                  CCAngle                     (Radians p);
            
            ______ Radians          asRadians                   () const;
            ______ Degrees          asDegrees                   () const;
            
            inline float            difference                  (CCAngleCRef p) const           { return 180. - fabs(fmod(fabs(value-p.value),360.f) - 180.f); }
            inline float            delta                       (CCAngleCRef p) const           { return fmod(p.value-value,360.f); }
            
            inline float            normalized                  () const                        { return fmod(value,360.f); } //tiny::Math::clamp(0,360,value,true); }
            inline float            normalizedTo180180          () const                        { return tiny::Math::normalizeTo180180(value); }
            inline float            normalize                   ()                              { return value = normalized(); }
            inline float            normalizeTo180180           ()                              { return value = normalizedTo180180(); }
            
            inline CCAngleRef       operator =                  (float v)                       { value = v; return *this; }
            inline CCAngleRef       operator +=                 (float p)                       { value += p; return *this; }
            inline CCAngleRef       operator -=                 (float p)                       { value -= p; return *this; }
            inline CCAngleRef       operator *=                 (float p)                       { value *= p; return *this; }
            inline CCAngleRef       operator /=                 (float p)                       { value /= p; return *this; }
            inline CCAngle          operator -                  () const                        { return - value; }
            inline                  operator float              () const                        { return value; }
            
            inline bool             isDirectionCW               () const                        { return value <= 0; }
            inline bool             isDirectionCCW              () const                        { return 0 <= value; }
            inline bool             isDirectionSame             (CCAngleCRef p, float delta) const      { return not isDirectionDifferent(p,delta); }
            ______ bool             isDirectionDifferent        (CCAngleCRef p, float delta) const;
            
            inline bool             equals                      (float r, float delta = 0.0001f) const  { return tiny::Math::equal(value,r,delta); }
            inline float            cosf                        () const                        { return ::cosf(ccDegreesToRadians(-value)); }
            inline float            sinf                        () const                        { return ::sinf(ccDegreesToRadians(-value)); }
            inline CCVector         asVector                    () const                        { return CCPoint::forAngle(ccDegreesToRadians(-value)); }
            
            static std::vector<CCAngle> generateFromToBy        (double from, double to, double delta);
            static std::vector<CCAngle> generateToBy            (double to, double delta);
            static std::vector<CCAngle> generateCountBy         (int count, double by);
            static std::vector<CCAngle> generateCountByFrom     (int count, double by, double from);
            static std::vector<CCAngle> generateCircleCount     (double count);
            static std::vector<CCAngle> generateCircleBy        (double delta);
            
            static const CCAngle Zero;
            static const CCAngle HalfCircle;
            static const CCAngle Circle;

        };
        
        
        
        STRUCT (Radians)
        {
            float value = 0;
            ______                  Radians                     (float v = 0) : value(v) {}
            ______                  Radians                     (CCPoint p)                     { value=p.getAngle(); }
            ______                  Radians                     (CCAngle p);
            ______                  Radians                     (Degrees p);
            
            ______ Degrees          asDegrees                   () const;
            ______ CCAngle          asCCAngle                   () const;
            
            inline float            difference                  (RadiansCRef p) const           { return tiny::Math::pi - fabs(fmod(fabs(value-p.value),tiny::Math::twopi) - tiny::Math::pi); }
            inline float            delta                       (RadiansCRef p) const           { return fmod(p.value-value,tiny::Math::twopi); }
            
            inline float            normalized                  () const                        { return fmod(value,tiny::Math::twopi); } //tiny::Math::clamp(0,tiny::Math::twopi,value,true); }
            inline float            normalizedToPiPi            () const                        { return tiny::Math::normalizeToPiPi(value); }
            inline float            normalize                   ()                              { return value = normalized(); }
            inline float            normalizeToPiPi             ()                              { return value = normalizedToPiPi(); }
            
            inline RadiansRef       operator =                  (float v)                       { value = v; return *this; }
            inline RadiansRef       operator +=                 (float p)                       { value += p; return *this; }
            inline RadiansRef       operator -=                 (float p)                       { value -= p; return *this; }
            inline RadiansRef       operator *=                 (float p)                       { value *= p; return *this; }
            inline RadiansRef       operator /=                 (float p)                       { value /= p; return *this; }
            inline Radians          operator -                  () const                        { return - value; }
            inline                  operator float              () const                        { return value; }
            
            inline bool             isDirectionCW               () const                        { return value <= 0; }
            inline bool             isDirectionCCW              () const                        { return 0 <= value; }
            inline bool             isDirectionSame             (RadiansCRef p, float delta) const      { return not isDirectionDifferent(p,delta); }
            ______ bool             isDirectionDifferent        (RadiansCRef p, float delta) const;
            
            inline bool             equals                      (float r, float delta = 0.0001f) const  { return tiny::Math::equal(value,r,delta); }
            inline float            cosf                        () const                        { return ::cosf(value); }
            inline float            sinf                        () const                        { return ::sinf(value); }
            inline CCVector         asVector                    () const                        { return CCPoint::forAngle(value); }
            
            static std::vector<Radians> generateFromToBy        (double from, double to, double delta);
            static std::vector<Radians> generateToBy            (double to, double delta);
            static std::vector<Radians> generateCountBy         (int count, double by);
            static std::vector<Radians> generateCountByFrom     (int count, double by, double from);
            static std::vector<Radians> generateCircleCount     (double count);
            static std::vector<Radians> generateCircleBy        (double delta);
            
            static const Radians Zero;
            static const Radians HalfCircle;
            static const Radians Circle;
        };
        
        
        
        STRUCT (Angle)
        {
                // REMEMBER 'Angle' value is in radians
            
            ______                      Angle                       (CCPoint p)                     { value = p.getAngle(); }
            ______                      Angle                       (CCAngle p)                     { value = ccDegreesToRadians(-p); }
            ______                      Angle                       (Degrees p)                     { value = ccDegreesToRadians(p); }
            ______                      Angle                       (Radians p)                     { value = p; }
            
            inline float                difference                  (AngleCRef p) const             { return tiny::Math::pi - fabs(fmod(fabs(value-p.value),tiny::Math::twopi) - tiny::Math::pi); }
            inline float                delta                       (AngleCRef p) const             { return fmod(p.value-value,tiny::Math::twopi); }
            inline float                normalized                  () const                        { return fmod(value,tiny::Math::twopi); } //tiny::Math::clamp(0,tiny::Math::twopi,value,true); }
            inline float                normalizedToPiPi            () const                        { return normalized() - tiny::Math::pi; }
            inline float                normalize                   ()                              { return value = normalized(); }
            inline float                normalizeToPiPi             ()                              { return value = normalizedToPiPi(); }
            
            inline AngleRef             operator =                  (Angle v)                       { value = v.asRadians(); return *this; }
            inline AngleRef             operator +=                 (Angle p)                       { value += p.asRadians(); return *this; }
            inline AngleRef             operator -=                 (Angle p)                       { value -= p.asRadians(); return *this; }
            inline AngleRef             operator *=                 (Angle p)                       { value *= p.asRadians(); return *this; }
            inline AngleRef             operator /=                 (Angle p)                       { value /= p.asRadians(); return *this; }
            
            inline Angle                operator +                  (Angle p)                       { return Radians(value + p.asRadians()); }
            inline Angle                operator -                  (Angle p)                       { return Radians(value - p.asRadians()); }
            inline Angle                operator *                  (Angle p)                       { return Radians(value * p.asRadians()); }
            inline Angle                operator /                  (Angle p)                       { return Radians(value / p.asRadians()); }

            inline AngleRef             operator *=                 (float p)                       { value *= p; return *this; }
            inline AngleRef             operator /=                 (float p)                       { value /= p; return *this; }
            
            inline Angle                operator -                  () const                        { return Radians(- value); }
            
            inline bool                 isDirectionCW               () const                        { return value <= 0; }
            inline bool                 isDirectionCCW              () const                        { return 0 <= value; }
            inline bool                 isDirectionSame             (AngleCRef p, float delta) const      { return not isDirectionDifferent(p,delta); }
            ______ bool                 isDirectionDifferent        (AngleCRef p, float delta) const;
            
            inline bool                 equals                      (float r, float delta = 0.0001f) const  { return tiny::Math::equal(value,r,delta); }
            
            inline float                cosf                        () const                        { return ::cosf(value); }
            inline float                sinf                        () const                        { return ::sinf(value); }
            inline CCVector             asVector                    () const                        { return CCPoint::forAngle(value); }
            
            inline  CCAngle             asCCAngle                   () const                        { return - ccRadiansToDegrees(value); }
            inline  Degrees             asDegrees                   () const                        { return ccRadiansToDegrees(value); }
            inline  Radians             asRadians                   () const                        { return value; }
            
            static std::vector<Angle>   generateFromToBy            (Angle from, Angle to, Angle delta);
            static std::vector<Angle>   generateToBy                (Angle to, Angle delta);
            static std::vector<Angle>   generateCountBy             (int count, Angle by);
            static std::vector<Angle>   generateCountByFrom         (int count, Angle by, Angle from);
            static std::vector<Angle>   generateCircleCount         (Angle count);
            static std::vector<Angle>   generateCircleBy            (Angle delta);
            
            static const Angle Zero;
            static const Angle HalfCircle;
            static const Angle Circle;
            
        private:
            
                // 'value' is in radians
            
            float value = 0;
            
        };
        

        
        
        
            //#include "CGPointExtension.h"
        
            //static CGPoint 	ccpNeg (const CGPoint v)
            //static CGPoint 	ccpAdd (const CGPoint v1, const CGPoint v2)
            //static CGPoint 	ccpSub (const CGPoint v1, const CGPoint v2)
            //static CGPoint 	ccpMult (const CGPoint v, const CGFloat s)
            //static CGPoint 	ccpMidpoint (const CGPoint v1, const CGPoint v2)
            //static CGFloat 	ccpDot (const CGPoint v1, const CGPoint v2)
            //static CGFloat 	ccpCross (const CGPoint v1, const CGPoint v2)
            //static CGPoint 	ccpPerp (const CGPoint v)
            //static CGPoint 	ccpRPerp (const CGPoint v)
            //static CGPoint 	ccpProject (const CGPoint v1, const CGPoint v2)
            //static CGPoint 	ccpRotate (const CGPoint v1, const CGPoint v2)
            //static CGPoint 	ccpUnrotate (const CGPoint v1, const CGPoint v2)
            //static CGFloat 	ccpLengthSQ (const CGPoint v)
            //CGFloat 	ccpLength (const CGPoint v)
            //CGFloat 	ccpDistance (const CGPoint v1, const CGPoint v2)
            //CGPoint 	ccpNormalize (const CGPoint v)
            //CGPoint 	CCPoint::forAngle (const CGFloat a)
            //CGFloat 	Point::getAngle (const CGPoint v)
        
        STRUCT (CCLine) {
            CCPoint from,to;
            CCLine() {}
            CCLine(CCPoint f, CCPoint t) : from(f), to(t) {}
            inline float length() const { return (to-from).getLength(); }
            inline float slope() const { float dy = to.y-from.y; return dy ? (to.x-from.x) / dy : NAN; }
            inline float dx() const { return to.x-from.x; }
            inline float dy() const { return to.y-from.y; }
        };
        
        inline CCPoint          ccpOnLine                       (CCPointCRef v1, CCPointCRef v2, float ratio)                   { return v1 + (v2 - v1) * ratio; }
        inline bool             ccpEqual                        (CCPointCRef a, CCPointCRef b, float delta = 0.000001f)         { return fabs(a.x-b.x) < delta and fabs(a.y-b.y) < delta; }
        inline bool             ccpSame                         (CCPointCRef a, CCPointCRef b, float delta = 0.000001f)         { return ccpEqual(a,b,delta); }
        inline bool             ccpDifferent                    (CCPointCRef a, CCPointCRef b, float delta = 0.000001f)         { return not ccpEqual(a,b,delta); }
        inline vector<CCPoint>  ccpAdd                          (vector<CCPoint> v, CCPointCRef p)                              { for(autoRef i:v) i = i + p; return v; }
        
        
        ______ vector<CCPoint>  ccpGenerateWithLine             (CCLine line, int count, CCPoint randomrange = {0,0});
        ______ vector<CCPoint>  ccpGenerateWithOpenLine         (CCLine line, int count, CCPoint randomrange = {0,0});
        ______ vector<CCPoint>  ccpGenerateWithPolyLine         (vector<pair<CCPoint,int>> points, CCPoint randomrange = {0,0});
        ______ vector<CCPoint>  ccpGenerateWithBezier           (CCPoint p0, ccBezierConfig c, int count, Range timerange = {0,0}, CCPoint randomrange = {0,0});
        ______ vector<CCPoint>  ccpGenerateWithBezier           (CCPoint p0, ccBezierConfig c, vector<float> times, CCPoint randomrange = {0,0});
        ______ vector<CCPoint>  ccpGenerateWithBox              (CCRect box, int count);
        ______ vector<CCPoint>  ccpGenerateWithGrid             (CCRect box, Dimension dim, CCPoint randomrange = {0,0}, bool up = true, bool vertical = true);
        ______ vector<CCPoint>  ccpGenerateWithArc              (float distance, CCAngle angle0, CCAngle angle1, CCAngle dangle, bool aspectCorrected = false);
        ______ vector<CCPoint>  ccpGenerateWithOval             (float rx, float ry, CCAngle angle0, CCAngle angle1, CCAngle dangle);
        ______ vector<CCPoint>  ccpGenerateWithSpiralAddition   (float distance0, float distance1, float addition, CCAngle angle0, CCAngle angle1, bool aspectCorrected);
        ______ vector<CCPoint>  ccpGenerateWithSpiralMultiplier (float distance0, float distance1, float multiplier, CCAngle angle0, CCAngle angle1, bool aspectCorrected);
        ______ vector<CCPoint>  ccpGenerateStar                 (int sides, int pointsPerSegment, float_01 innerlength, CCPoint randomrange = {0,0});
        
        
        inline CCPoint          lerp                            (CCPointCRef from, CCPointCRef to, float t)                     { return Vec2(tiny::Math::lerp(from.x,to.x,t),tiny::Math::lerp(from.y,to.y,t)); }
        
        
        inline CCPoint          ccpFromPolar                    (float distance, float angle DEGREES)   { angle=-ccToRadians(angle); return Vec2(distance*cosf(angle),distance*sinf(angle)); }
        inline CCPoint          ccpFromPolarWithAspectCorrectedY(float distance, float angle DEGREES)   { angle=-ccToRadians(angle); return Vec2(distance*cosf(angle),distance*(screenGetWidth()/screenGetHeight())*sinf(angle)); }
        inline CCPoint          ccpFromPolarWithAspectCorrectedX(float distance, float angle DEGREES)   { angle=-ccToRadians(angle); return Vec2(distance*(screenGetHeight()/screenGetWidth())*cosf(angle),distance*sinf(angle)); }
        
        
        inline CCVector         ccvPerpendicular                (CCVector v, bool positive = true)      { return positive ? Vec2(v.y,v.x) : Vec2(-v.y,-v.x); }
        inline CCVector         ccvOrthogonal                   (CCVector v, bool positive = true)      { return ccvPerpendicular(v,positive); }
        inline CCVector         ccvNormalize                    (CCVector v)                            { float length = v.getLength(); if (length) return Vec2(v.x/length,v.y/length); return CCNull.vector; }
        inline CCVector         ccvOrthonormal                  (CCVector v, bool positive = true)      { return ccvNormalize(ccvPerpendicular(v,positive)); }
        
        
        inline CCPoint          ccpAspectCorrectedX             (CCPointCRef from)                      { return Vec2(from.x * screenGetAspectRatioXtoY(),from.y); }
        inline CCPoint          ccpAspectCorrectedY             (CCPointCRef from)                      { return Vec2(from.x,from.y * screenGetAspectRatioYtoX()); }
        inline CCPoint          ccpAspectCorrected              (CCPointCRef from)
        {
            if (screenGetAspectRatioYtoX() < 1)
                return ccpAspectCorrectedX(from);
            else
                return ccpAspectCorrectedY(from);
        }
        
        
        STRUCT (OBJECT) { CCObjectPtr object = 0; };
        STRUCT (NODE)   { CCNodePtr node = 0; };
        STRUCT (SPRITE) { CCSpritePtr sprite = 0; };
        
        
        
        
        inline CCNodePtr                ccParentOf                  (CCNodePtr p)                                       { return p ? p -> getParent() : 0; }
        inline CCNodePtr                ccAncestorOfWithTag         (CCNodePtr p, int tag)                              { while((p = ccParentOf(p))) { if (p->getTag() == tag) return p; } return 0; }
        inline CCNodePtr                ccAncestorOf                (CCNodePtr p, std::function<bool (CCNodePtr)> f)    { while((p = ccParentOf(p))) { if (f(p)) return p; } return 0; }
        inline bool                     ccIsAncestorOf              (CCNodePtr a, CCNodePtr child)                      { while(child and child != a) { child = ccParentOf(child); } return child; }
        inline CCNodePtr                ccRootOf                    (CCNodePtr child)                                   { while(ccParentOf(child)) { child = ccParentOf(child); } return child; }
        
        inline void                     ccAttach                    (CCNodePtr parent, CCNodePtr child)                 { parent->addChild(child); }
        inline void                     ccAttach                    (CCNodePtr parent, CCNodePtr child, int z)          { parent->addChild(child,z); }
        inline void                     ccDetach                    (CCNodePtr child)                                   { child->removeFromParent(); }
        inline bool                     ccReorder                   (CCNodePtr child, int z)                            { if (child and ccParentOf(child)) { ccParentOf(child)->reorderChild(child,z); return true; } return false; }
        
        ______ void                     ccReparent                  (CCNodePtr child, CCNodePtr newParent) ;
        ______ void                     ccReparent                  (CCNodePtr child, CCNodePtr newParent, int z) ;
        ______ void                     ccReparentPreserved         (CCNodePtr child, CCNodePtr newParent, bool position, bool rotation) ;
        ______ void                     ccReparentPreserved         (CCNodePtr child, CCNodePtr newParent, int z, bool position, bool rotation) ;
        
        void                            ccChildrenApply             (CCNodePtr p, std::function<void (CCNodePtr)> f);
        std::vector<CCNodePtr>          ccChildren                  (CCNodePtr p);
        std::vector<CCNodePtr>          ccChildren                  (CCNodePtr p, std::function<bool (CCNodePtr)> f);
        std::vector<CCNodePtr>          ccChildrenWithTag           (CCNodePtr p, int tag);
        std::vector<CCNodePtr>          ccDescendants               (CCNodePtr p);
        std::vector<CCNodePtr>          ccDescendants               (CCNodePtr p, std::function<bool (CCNodePtr)> f);
        std::vector<CCNodePtr>          ccDescendantsWithTag        (CCNodePtr p, int tag);
        void                            ccContentSize               (CCNodePtr p);
        inline void                     ccContentSize               (CCNodePtr p, CCSize s) { p -> setContentSize(s); }
        inline void                     ccResize                    (CCNodePtr p, CCSize s) { p -> setContentSize(s); }
        

        
        
        
        
        
        void test();
        void print(const char* n, CCNodePtr a);
        string ccPrintSprite(CCSpritePtr p, string n = "");
        
        extern std::string to_string(CCPoint p);
        extern std::string to_string(CCSize p);
        extern std::string to_string(CCRect p);
        
        std::ostream& operator << (std::ostream& o, CCPoint p);
        std::ostream& operator << (std::ostream& o, CCSize p);
        std::ostream& operator << (std::ostream& o, CCRect p);
        std::ostream& operator << (std::ostream& o, CCNodePtr p);
        std::ostream& operator << (std::ostream& o, const VectorOfPoints & p);
        
        
            // 8< ---------------------------------------------------------------------------
        
        
        
        
        
        inline CCPoint      ccpForCCAngle               (CCAngle p)                                 { return CCPoint::forAngle(p.asRadians()); }
        inline CCAngle      ccpToCCAngle                (CCPoint p)                                 { return Radians(p.getAngle()).asCCAngle(); }
        
        inline Radians      ccFromCCAngle               (CCAngle a)                                 { return a.asRadians(); }
        inline CCAngle      ccToCCAngle                 (Radians a)                                 { return a.asCCAngle(); }
        
        inline bool         ccAngleIsBetween            (float angle0, float angle1, float angle)   { return angle0 <= angle and angle <= angle1; }
        inline bool         ccAngleIsStrictlyBetween    (float angle0, float angle1, float angle)   { return angle0 < angle and angle < angle1; }
        
        inline int          ccAngleInDegreesGetSection  (int angle, uint sections)                  { int d = 360/sections; return clamp(0,sections-1,(0 < angle ? (angle % 360) / d : (360 - ((-angle) % 360) / d))); }
        
        inline int          ccAngleTo0360               (int angle)                                 { angle %= 360; if (angle < 0) angle = 360-angle; return angle; }
        
        inline float        ccAngleFromWorldInRadians   (CCNodePtr node, float angle0)              { return node -> convertToNodeSpace(CCPoint::forAngle(angle0)).getAngle(); }
        inline float        ccAngleToWorldInRadians     (CCNodePtr node, float angle0)              { return node -> convertToWorldSpace(CCPoint::forAngle(angle0)).getAngle(); }
        inline float        ccAngleFromWorldInDegrees   (CCNodePtr node, float angle0)              { return CC_RADIANS_TO_DEGREES(node -> convertToNodeSpace(CCPoint::forAngle(CC_DEGREES_TO_RADIANS(angle0)))).getAngle(); }
        inline float        ccAngleToWorldInDegrees     (CCNodePtr node, float angle0)              { return CC_RADIANS_TO_DEGREES(node -> convertToWorldSpace(CCPoint::forAngle(CC_DEGREES_TO_RADIANS(angle0)))).getAngle(); }
        
        ______ CCAngle      ccRotationInWorld           (CCNodePtr p);
        

        
        
        inline CCAngle      an2aw       (CCNodePtr n, CCPoint p)            { return CCAngle(n -> convertToWorldSpace  (p) - n -> convertToWorldSpace(Vec2(0,0))); }
        inline CCAngle      aw2an       (CCNodePtr n, CCPoint p)            { return CCAngle(n -> convertToNodeSpace   (p) - n -> convertToNodeSpace(Vec2(0,0))); }
        inline CCAngle      an2aw       (CCNodePtr n)                       { return an2aw(n,Vec2(1,0)); }
        inline CCAngle      aw2an       (CCNodePtr n)                       { return aw2an(n,Vec2(1,0)); }
        inline CCAngle      an2aw       (CCNodePtr n, CCAngle angle)        { return an2aw(n, angle.asVector()); }
        inline CCAngle      aw2an       (CCNodePtr n, CCAngle angle)        { return aw2an(n, angle.asVector()); }
        
        
        
        
        inline CCPoint      operator +  (CCPointCRef a, float b)            { return Vec2(a.x+b, a.y+b); }
        inline CCPoint      operator +  (float b, CCPointCRef a)            { return Vec2(a.x+b, a.y+b); }
//        inline CCPointRef   operator += (CCPointRef a, CCPointCRef b)       { a.x += b.x; a.y += b.y; return a; }
        inline CCPoint      operator -  (CCPointCRef a, float b)            { return Vec2(a.x-b, a.y-b); }
        inline CCPoint      operator -  (float b, CCPointCRef a)            { return Vec2(-b+a.x, -b+a.y); }
//        inline CCPointRef   operator -= (CCPointRef a, CCPointCRef b)       { a.x -= b.x; a.y -= b.y; return a; }
        
//        inline CCPoint      operator *  (float b, CCPointCRef a)            { return Vec2(a.x * b, a.y * b); }
        inline CCPoint      operator *  (CCPointCRef a, CCPointCRef b)      { return Vec2(a.x*b.x, a.y*b.y); }
        inline CCPoint      operator *  (CCPointCRef a, CCRect b)           { return Vec2(b.origin.x + a.x * b.size.width, b.origin.y + a.y * b.size.height); }
        inline float        dot         (CCPointCRef a, CCPointCRef b)      { return a.x*b.x + a.y*b.y; }
        inline float        cross       (CCPointCRef a, CCPointCRef b)      { return a.x*b.y - a.y*b.x; } // ???
        inline float        norm        (CCPointCRef a)                     { return sqrt(dot(a,a)); }
        
        inline CCPoint      operator *  (CCPointCRef a, CCSizeCRef b)       { return Vec2(a.x*b.width,a.y*b.height); }
        inline CCPoint      operator *  (CCSizeCRef b, CCPointCRef a)       { return Vec2(a.x*b.width,a.y*b.height); }
        
        inline CCSize       operator -  (CCSizeCRef b)                      { return CCSize(-b.width,-b.height); }
        inline CCSize       operator *  (float a, CCSizeCRef b)             { return CCSize(a*b.width,a*b.height); }
        inline CCSize       operator *= (CCSizeCRef b, float a)             { return CCSize(a*b.width,a*b.height); }
        inline CCSize       operator *  (CCSizeCRef a, CCSizeCRef b)        { return CCSize(a.width*b.width,a.height*b.height); }
        
        
        ______ CCRect       ccScale     (CCRectCRef p, float x, float y) ;
        ______ CCRect       operator +  (CCRectCRef a, CCRectCRef b) ;
        ______ CCRect       operator +  (CCRectCRef a, CCPointCRef b) ;
        inline CCRectRef    operator += (CCRectRef a, CCRectCRef b)         { return a = a+b; }
        
        
        
        
        
        
        
        inline CCRect       bounds              (CCNodePtr p)               { return p ? p -> boundingBox() : CCNull.rect; }
        inline CCRect       bb                  (CCNodePtr p)               { return p ? p -> boundingBox() : CCNull.rect; }
        ______ CCRect       bbox                (CCNodePtr p, bool global = false);
        inline CCRect       bbox2w              (CCNodePtr p)               { return bbox(p,true); }
        inline CCRatio      anchor              (CCNodePtr node)            { return node -> getAnchorPoint(); }
        inline CCRatio      origin              (CCNodePtr node)            { return - anchor(node); }
        inline CCPoint      origin_a            (CCNodePtr node)            { return - node -> getAnchorPointInPoints(); }
        inline CCPoint      anchor_o            (CCNodePtr node)            { return node -> getAnchorPointInPoints(); }
        inline CCPoint      oa                  (CCNodePtr node)            { return - node -> getAnchorPointInPoints(); }
        inline CCPoint      ao                  (CCNodePtr node)            { return node -> getAnchorPointInPoints(); }
        inline CCPoint      pa                  (CCNodePtr node)            { return node -> getAnchorPointInPoints(); }
        
        ______ void         anchor              (CCNodePtr node, CCPoint p) ;
        
        
        STRUCT (AABB) : public CCRect
        {
            AABB() {}
            AABB(CCRect p) : CCRect(p) {}
            AABB(CCNodePtr p, bool recursive = false);
            
            inline float    x0                  () const                                                    { return origin.x; }
            inline float    x1                  () const                                                    { return origin.x + size.width; }
            inline float    y0                  () const                                                    { return origin.y; }
            inline float    y1                  () const                                                    { return origin.y + size.height; }
            
            inline bool     contains            (CCPoint p) const                                           { return x0() <= p.x and p.x <= x1() and y0() <= p.y and p.y <= y1(); }
            inline bool     disjoint            (AABBCRef p) const                                          { return x1() < p.x0() or y1() < p.y0() or p.y1() < y0() or p.x1() < x0(); }
            inline bool     intersects          (AABBCRef p) const                                          { return not disjoint(p); }
            
            AABBRef         add                 (AABBCRef p);
            AABBRef         add                 (CCPoint p);
            
            inline AABBRef  add                 (CCNodePtr n)                                               { return add(AABB(n)); }
            inline AABBRef  operator +=         (AABBCRef p)                                                { return add(p); }
        };
        
        
        
        inline CCPoint      scale               (CCNodePtr target, float x, float y)                        { return Vec2(x * target -> getScaleX(), y * target -> getScaleY()); }
        
        inline CCPoint      s2p                 (CCSize size)                                               { return Vec2(size.width,size.height); }
        inline CCSize       p2s                 (CCPoint p)                                                 { return CCSize(p.x,p.y); }
        
        inline CCSize       ccSize              (CCNodePtr p)                                               { return p -> getContentSize(); }
        inline CCSize       ccSizeScaled        (CCNodePtr p)                                               { return p -> getContentSize() * CCSize(p -> getScaleX(), p -> getScaleY()); }
        inline CCSize       ccSize              (CCNodePtr p, bool scaled)                                  { return scaled ? p -> getContentSize() * CCSize(p -> getScaleX(), p -> getScaleY()) : p -> getContentSize(); }
        inline void         ccSize              (CCNodePtr p, CCSize size)                                  { p -> setContentSize(size); }
        inline CCSize       ccSize              (CCNodePtr p, float x, float y)                             { return p -> getContentSize() * CCSize(x,y); }
        
        inline float        ccWidth             (CCNodePtr target, float x = 1)                             { return target -> getContentSize().width * x; }
        inline float        ccHeight            (CCNodePtr target, float y = 1)                             { return target -> getContentSize().height * y; }
        inline float        ccWidthScaled       (CCNodePtr target, float x = 1)                             { return target -> getContentSize().width * x * target -> getScaleX(); }
        inline float        ccHeightScaled      (CCNodePtr target, float y = 1)                             { return target -> getContentSize().height * y * target -> getScaleY(); }
            //    inline float    width       (CCNodePtr target, float x = 1)     { return target -> getContentSize().width * x * target -> getScaleX(); }
            //    inline float    height      (CCNodePtr target, float y = 1)     { return target -> getContentSize().height * y * target -> getScaleY(); }
            //    inline float    sizeX       (CCNodePtr target, float x = 1)     { return target -> getContentSize().width * x * target -> getScaleX(); }
            //    inline float    sizeY       (CCNodePtr target, float y = 1)     { return target -> getContentSize().height * y * target -> getScaleY(); }
        inline float        ccRadius            (CCNodePtr p, bool withChildren = false)                    { AABB aabb(p,withChildren); return std::max(aabb.size.width,aabb.size.height)/2.; }
        
        
        inline CCSize       ccSizeInPixels      (CCTexture2DPtr p)                                          { return p->getContentSizeInPixels(); } //CCSize(p->getPixelsWide(),p->getPixelsHigh()); }
        inline CCSize       ccSize              (CCTexture2DPtr p)                                          { return p->getContentSize(); } //CCSize(p->getPixelsWide(),p->getPixelsHigh()); }

        inline CCSize       ccSizeBigger        (CCSizeCRef a, CCSizeCRef b)                                { return CCSize(a.width<b.width?b.width:a.width,a.height<b.height?b.height:a.height); }
        inline CCSize       ccSizeSmaller       (CCSizeCRef a, CCSizeCRef b)                                { return CCSize(a.width<b.width?a.width:b.width,a.height<b.height?a.height:b.height); }
        
        inline int          ccZOrder            (CCNodePtr n)                                               { return n -> getZOrder(); }
        inline void         ccZOrder            (CCNodePtr n, int z)                                        { n -> setZOrder(z); }
        inline void         ccZOrder            (PairOfSprites n, int z)                                    { n.first -> setZOrder(z); n.second -> setZOrder(z); }
        inline void         ccZOrder            (VectorOfSprites n, int z)                                  { for(auto s:n) ccZOrder(s); }
        
        inline void         ccAnchor            (CCNodePtr n, CCPoint p)                                    { n -> setAnchorPoint(p); }
        inline CCRatio      ccAnchor            (CCNodePtr n)                                               { return n -> getAnchorPoint(); }
        inline CCPoint      ccAnchorPoint       (CCNodePtr n)                                               { return n -> getAnchorPointInPoints(); }
        
        inline CCPoint      ccPosition          (CCNodePtr n)                                               { return n -> getPosition(); }
        inline float        ccPositionX         (CCNodePtr n)                                               { return n -> getPosition().x; }
        inline float        ccPositionY         (CCNodePtr n)                                               { return n -> getPosition().y; }
        inline CCPoint      ccPosition          (CCNodePtr n, CCPoint p)                                    { n -> setPosition(p); return n -> getPosition(); }
        inline CCPoint      ccPosition          (CCNodePtr n, float x, float y)                             { n -> setPosition(Vec2(x,y)); return n -> getPosition(); }
        inline CCPoint      ccPositionX         (CCNodePtr n, float v)                                      { n -> setPosition(Vec2(v,ccPositionY(n))); return n -> getPosition(); }
        inline CCPoint      ccPositionY         (CCNodePtr n, float v)                                      { n -> setPosition(Vec2(ccPositionX(n),v)); return n -> getPosition(); }

        inline CCPoint      ccPositionAnchor    (CCNodePtr n)                                               { return ccPosition(n) + ccAnchorPoint(n); }
        inline float        ccPositionAnchorX   (CCNodePtr n)                                               { return ccPositionAnchor(n).x; }
        inline float        ccPositionAnchorY   (CCNodePtr n)                                               { return ccPositionAnchor(n).y; }
        inline CCPoint      ccPositionAnchor    (CCNodePtr n, CCPoint p)                                    { return ccPosition(n,p-ccAnchorPoint(n)); }
        inline CCPoint      ccPositionAnchorX   (CCNodePtr n, float v)                                      { return ccPositionX(n,v-ccAnchorPoint(n).x); }
        inline CCPoint      ccPositionAnchorY   (CCNodePtr n, float v)                                      { return ccPositionY(n,v-ccAnchorPoint(n).y); }

        inline CCPoint      ccLocation          (CCNodePtr node, CCRatio ratio)                             { ccPosition(node,screenGetPoint(ratio)); return ccPosition(node); }
        inline CCPoint      ccLocation          (CCNodePtr node)                                            { return screenGetRatio(ccPosition(node)); }
        
        inline CCPoint      ccMoveBy            (CCNodePtr n, CCPoint p)                                    { n -> setPosition(n->getPosition()+p); return n -> getPosition(); }
        inline CCPoint      ccMoveByX           (CCNodePtr n, float v)                                      { n -> setPosition(n->getPosition()+Vec2(v,0)); return n -> getPosition(); }
        inline CCPoint      ccMoveByY           (CCNodePtr n, float v)                                      { n -> setPosition(n->getPosition()+Vec2(0,v)); return n -> getPosition(); }
        
        inline float        ccScale             (CCNodePtr n)                                               { return n -> getScale(); }
        inline float        ccScaleAverage      (CCNodePtr n)                                               { return (n -> getScaleX() + n -> getScaleY())/2.f; }
        inline CCPoint      ccScaleXY           (CCNodePtr n)                                               { return Vec2(n -> getScaleX(),n -> getScaleY()); }
        inline void         ccScale             (CCNodePtr n, float s)                                      { n -> setScale(s); }
        inline void         ccScaleZero         (CCNodePtr n)                                               { return n -> setScale(0.001); }
        inline float        ccScaleX            (CCNodePtr n)                                               { return n -> getScaleX(); }
        inline float        ccScaleY            (CCNodePtr n)                                               { return n -> getScaleY(); }
        inline void         ccScaleX            (CCNodePtr n, float s)                                      { n -> setScaleX(s); }
        inline void         ccScaleY            (CCNodePtr n, float s)                                      { n -> setScaleY(s); }
        inline void         ccScaleXY           (CCNodePtr n, float sx, float sy)                           { n -> setScaleX(sx); n -> setScaleY(sy); }
        inline void         ccScaleXY           (CCNodePtr n, CCPoint s)                                    { n -> setScaleX(s.x); n -> setScaleY(s.y); }
        
        ______ void         ccScaleToFit        (CCNodePtr n, CCSize s);
        
        inline void         ccScaleMultiply     (CCNodePtr n, float factor)                                 { ccScaleXY(n,ccScaleX(n)*factor,ccScaleY(n)*factor); }
        inline void         ccScaleMultiply     (CCNodePtr n, float x, float y)                             { ccScaleXY(n,ccScaleX(n)*x,ccScaleY(n)*y); }
        inline void         ccScaleAdd          (CCNodePtr n, float factor)                                 { ccScaleXY(n,ccScaleX(n)+factor,ccScaleY(n)+factor); }
        inline void         ccScaleAdd          (CCNodePtr n, float x, float y)                             { ccScaleXY(n,ccScaleX(n)+x,ccScaleY(n)+y); }
        
        inline float        ccRotation          (CCNodePtr n)                                               { return n -> getRotation(); }
        inline void         ccRotation          (CCNodePtr n, float a)                                      { n -> setRotation(a); }
        inline void         ccRotate            (CCNodePtr n, float a)                                      { n -> setRotation(n -> getRotation() + a); }
        inline float        ccRotationMultiply  (CCNodePtr n, float factor)                                 { ccRotation(n,factor*ccRotation(n)); return n -> getRotation(); }
        inline float        ccRotationAdd       (CCNodePtr n, float factor)                                 { ccRotation(n,factor+ccRotation(n)); return n -> getRotation(); }
        
        inline float        ccSkewX             (CCNodePtr n)                                               { return n -> getSkewX(); }
        inline float        ccSkewY             (CCNodePtr n)                                               { return n -> getSkewY(); }
        inline void         ccSkewX             (CCNodePtr n, float s)                                      { n -> setSkewX(s); }
        inline void         ccSkewY             (CCNodePtr n, float s)                                      { n -> setSkewY(s); }
        inline void         ccSkewXY            (CCNodePtr n, float sx, float sy)                           { n -> setSkewX(sx); n -> setSkewY(sy); }
        
        inline void         ccFlipX             (CCSpritePtr n, bool x)                                     { n -> setFlippedX(x); }
        inline void         ccFlipY             (CCSpritePtr n, bool y)                                     { n -> setFlippedY(y); }
        inline void         ccFlipXY            (CCSpritePtr n, bool x, bool y)                             { ccFlipX(n,x); ccFlipY(n,y); }
        
        inline bool         ccFlipX             (CCSpritePtr n)                                             { return n -> isFlippedX(); }
        inline bool         ccFlipY             (CCSpritePtr n)                                             { return n -> isFlippedY(); }
       
        
        inline void         ccHide              (CCNodePtr n)                                               { n -> setVisible(false); }
        inline void         ccShow              (CCNodePtr n)                                               { n -> setVisible(true); }
        
        inline void         ccVisible           (CCNodePtr n, bool v)                                       { n -> setVisible(v); }
        inline void         ccVisibleFlip       (CCNodePtr n)                                               { n -> setVisible(not n -> isVisible()); }
        inline bool         ccVisible           (CCNodePtr n)                                               { return n -> isVisible(); }
       
        
        inline float    x0          (CCNodePtr p)                       { return (ccPosition(p)-ccAnchorPoint(p)).x; }
        inline float    x1          (CCNodePtr p)                       { return (ccPosition(p)-ccAnchorPoint(p)).x+ccWidthScaled(p); }
        inline float    x           (CCNodePtr p, float x)              { return (ccPosition(p)-ccAnchorPoint(p)).x+ccWidthScaled(p)*x; }
        inline float    y0          (CCNodePtr p)                       { return (ccPosition(p)-ccAnchorPoint(p)).y; }
        inline float    y1          (CCNodePtr p)                       { return (ccPosition(p)-ccAnchorPoint(p)).y+ccHeightScaled(p); }
        inline float    y           (CCNodePtr p, float y)              { return (ccPosition(p)-ccAnchorPoint(p)).y+ccHeightScaled(p)*y; }
        
        inline float    diagonal    (CCSize p)                          { return tiny::Math::hypotenuse(p.width, p.height); }
        inline float    diagonal    (CCNodePtr p)                       { return diagonal(p -> getContentSize()); }
        
        
        
        inline CCPoint  size2point  (CCSizeCRef a)                   { return Vec2(a.width,a.height); }
        inline CCSize   point2size  (CCPointCRef a)                  { return CCSize(a.x,a.y); }
        
        
        
            // r=ratio
            // p=point
            // o=origin
            // a=anchor
            // x=x coordinate
            // y=y coordinate
        
            // "convert ratio to point"
        inline CCPoint      r2p     (CCNodePtr target, CCRatioCRef ratio)       { CCSize s = target -> getContentSize(); return Vec2(ratio.x * s.width, ratio.y * s.height); }
        inline CCPoint      r2p     (CCNodePtr target, float x, float y)        { CCSize s = target -> getContentSize(); return Vec2(x * s.width, y * s.height); }
        inline CCRatio      p2r     (CCNodePtr target, CCPointCRef point)       { CCSize s = target -> getContentSize(); return Vec2(point.x / s.width, point.y / s.height); }
        
        inline float        r2x     (CCNodePtr target, float x)                 { return x * target -> getContentSize().width; }
        inline float        r2y     (CCNodePtr target, float y)                 { return y * target -> getContentSize().height; }
        inline float        x2r     (CCNodePtr target, float x)                 { return x / target -> getContentSize().width; }
        inline float        y2r     (CCNodePtr target, float y)                 { return y / target -> getContentSize().height; }
        
        
        inline CCPoint      pa2pn       (CCNodePtr target, CCPointCRef point)   { return point + ao(target); }
        inline CCPoint      pn2pa       (CCNodePtr target, CCPointCRef point)   { return point - ao(target); }

        inline CCPoint      pn2pw       (CCNodePtr target)                      { return target -> convertToWorldSpace(Vec2(0,0)); }
        inline CCPoint      pn2pw       (CCNodePtr target, CCPointCRef point)   { return target -> convertToWorldSpace(point); }
        inline CCPoint      pw2pn       (CCNodePtr target, CCPointCRef point)   { return target -> convertToNodeSpace(point);}
        inline CCPoint      pw2Ppn      (CCNodePtr target, CCPointCRef point)   { return target -> getParent() -> convertToNodeSpace(point);}
//        inline CCPoint      pa2pw       (CCNodePtr target, CCPointCRef p)        { return pn2pw(target,pa2pn(target,p)); }
//        inline CCPoint      pw2pa       (CCNodePtr target, CCPointCRef p)        { return pn2pa(target,pw2pn(target,p)); }

        inline CCPoint      pa2pw       (CCNodePtr target)                      { return target -> convertToWorldSpace  (target -> getAnchorPointInPoints()); }
        inline CCPoint      pa2pw       (CCNodePtr target, CCPointCRef a)       { return target -> convertToWorldSpace  (a - target -> getAnchorPointInPoints()); }
        inline CCPoint      pw2pa       (CCNodePtr target, CCPointCRef w)       { return target -> convertToNodeSpace   (w) - target -> getAnchorPointInPoints();}
        inline CCPoint      pw2Pa       (CCNodePtr target, CCPointCRef w)       { return pw2pa(target -> getParent(),w); }

        
        inline CCPoint      rn2pn           (CCNodePtr target, CCRatioCRef ratio)        { return ccSize(target) * ratio; }
        inline CCPoint      ra2pa           (CCNodePtr target, CCRatioCRef ratio)        { return ccSize(target) * ratio; }
        inline CCPoint      rn2pa           (CCNodePtr target, CCRatioCRef ratio)        { return pn2pa(target,rn2pn(target,ratio)); }
        inline CCPoint      ra2pn           (CCNodePtr target, CCRatioCRef ratio)        { return pa2pn(target,ra2pa(target,ratio)); }
        inline CCPoint      rn2pw           (CCNodePtr target, CCRatioCRef ratio)        { return pn2pw(target,rn2pn(target,ratio)); }
        inline CCPoint      ra2pw           (CCNodePtr target, CCRatioCRef ratio)        { return pa2pw(target,ra2pa(target,ratio)); }
        
        
        inline CCPoint      p012p11         (CCPoint p)                         { return Vec2(2.*(p.x-.5),2.*(p.y-.5)); }
        inline CCPoint      p112p01         (CCPoint p)                         { return Vec2(p.x*.5+.5,p.y*.5+.5); }
        
        inline CCPoint      convert01to11   (CCPoint p)                         { return Vec2(2.*(p.x-.5),2.*(p.y-.5)); }
        inline CCPoint      convert11to01   (CCPoint p)                         { return Vec2(p.x*.5+.5,p.y*.5+.5); }
        
        
        
            //inline CCPoint      normalize       (CCPoint p)     { return ccpNormalize(p); }
        
        
            //        inline float distance(CCPointCRef p0, CCPointCRef p1) { return sqrt(pow(p1.y - p0.y,2) + pow(p1.x - p0.x,2)); }
        
        
        
        ______ CCSize       sn2swSQ     (CCNodePtr n) ;
        ______ CCSize       sn2sw       (CCNodePtr n) ;
        
        
        
        
        ______  void        Prnrn       (CCNodePtr target, CCRatioCRef ratioT, CCNodePtr relative, CCRatioCRef ratioR);
        ______  void        Prnrn       (CCNodePtr target, CCRatioCRef ratioT, CCRatioCRef ratioP);
        
        inline  void        Prnrn       (CCNodePtr target, float x0, float y0, CCNodePtr relative, float x1, float y1)  { Prnrn(target,Vec2(x0,y0),relative,Vec2(x1,y1)); }
        inline  void        Prnrn       (CCNodePtr target, float x0, float y0, float x1, float y1)                      { Prnrn(target,Vec2(x0,y0),Vec2(x1,y1)); }
        inline  void        Prnrn       (CCNodePtr target, CCRatioCRef ratioP)                                          { Prnrn(target,{.5,.5},ratioP); }
        inline  void        Prnrn       (CCNodePtr target, float x1, float y1)                                          { Prnrn(target,.5,.5,x1,y1); }
        inline  void        Prnrn       (CCNodePtr target)                                                              { Prnrn(target,.5,.5,.5,.5); }
        
        
        void                Prara       (CCNodePtr target, CCRatioCRef ratioT, CCNodePtr relative, CCRatioCRef ratioR);
        
        
        
        
        
        
        
        
        
        
        
        
        typedef struct _Color3F {
            GLfloat r;
            GLfloat g;
            GLfloat b;
            
            Color3B ccc3b () const                    { return {static_cast<GLubyte>(to255(r)),static_cast<GLubyte>(to255(g)),static_cast<GLubyte>(to255(b))}; }
            Color4B ccc4b (float a = 1.f) const       { return {static_cast<GLubyte>(to255(r)),static_cast<GLubyte>(to255(g)),static_cast<GLubyte>(to255(b)),static_cast<GLubyte>(to255(a))}; }
            Color4F ccc4f (float a = 1.f) const       { return {r,g,b,a}; }
        } Color3F;
        
        typedef Color3B  & Color3BRef;
        typedef Color3F  & Color3FRef;
        typedef Color4F  & Color4FRef;
        typedef const Color3B  & Color3BCRef;
        typedef const Color3F  & Color3FCRef;
        typedef const Color4F  & Color4FCRef;
        
        
        struct HSVA;
        
        STRUCT (HSV) {
            float_0360  h;
            float_01    s,v;
            
            HSV(float H = 0, float S = 0, float V = 0) : h(H), s(S), v(V) {}
            HSV(Color3F c);
            HSV(Color4F c);
            
            HSVA    ccHSVA  (float a = 1) const;
            Color3F ccc3f   () const;
            Color4F ccc4f   (float a = 1) const;
        };
        
        STRUCT (HSVA) {
            float_0360  h;
            float_01    s,v,a;
            
            HSVA(float H = 0, float S = 0, float V = 0, float A = 1) : h(H), s(S), v(V), a(A) {}
            HSVA(Color3F c);
            HSVA(Color4F c);
            
            HSV     ccHSV   () const;
            Color3F ccc3f   () const;
            Color4F ccc4f   () const;
        };

        
        extern std::ostream& operator << (std::ostream& o, const Color3F & p);
        extern std::ostream& operator << (std::ostream& o, const Color3B & p);
        extern std::ostream& operator << (std::ostream& o, const Color4F & p);
        extern std::ostream& operator << (std::ostream& o, const Color4B & p);
        extern std::ostream& operator << (std::ostream& o, const HSV & p);
        extern std::ostream& operator << (std::ostream& o, const HSVA & p);
        
        
        
        inline bool         equal       (Color3B c1, Color3B c2)                    { return c1.r == c2.r and c1.g == c2.g and c1.b == c2.b; }
        
        
        inline Color3B    ccc3b       (double r, double g, double b)                  { return { static_cast<GLubyte>(to255(r)), static_cast<GLubyte>(to255(g)), static_cast<GLubyte>(to255(b)) }; }
        inline Color3B    ccc3b       (const Color3F& c)                            { return {to255(c.r),to255(c.g),to255(c.b)}; }
        inline Color3B    ccc3b       (const Color4F& c)                            { return ccc3b(c.r,c.g,c.b); }
        
        inline Color3F    ccc3f       (double r, double g, double b)                  { return { static_cast<GLfloat>(clamp01(r)), static_cast<GLfloat>(clamp01(g)), static_cast<GLfloat>(clamp01(b)) }; }
        inline Color3F    ccc3f       (const Color3B& c)                            { return { static_cast<GLfloat>(from255(c.r)), static_cast<GLfloat>(from255(c.g)), static_cast<GLfloat>(from255(c.b))}; }
        inline Color3F    ccc3f       (const Color4F& c)                            { return ccc3f(c.r,c.g,c.b); }
        inline Color3F    ccc3b3f     (ubyte r, ubyte g, ubyte b)                     { return { from255(r),from255(g),from255(b) }; }
        inline Color3F    ccc3f       (uint hex)                                      { return ccc3b3f((0xFF0000 & hex) >> 16, (0x00FF00 & hex) >> 8, (0x0000FF & hex) >> 0); }
        
        inline Color4B    ccc4b       (double r, double g, double b, double a = 1)    { return { static_cast<GLubyte>(to255(r)), static_cast<GLubyte>(to255(g)), static_cast<GLubyte>(to255(b)), static_cast<GLubyte>(to255(a)) }; }
        inline Color4B    ccc4b       (const Color4F& c)                            { return ccc4b(c.r,c.g,c.b,c.a); }
            //        inline Color4B    Color4F4b     (const Color4F& c)                            { return ccc4b(c); }
        
        inline Color4F    ccc4F       (double r, double g, double b, double a = 1)    { return { static_cast<GLfloat>(clamp01(r)), static_cast<GLfloat>(clamp01(g)), static_cast<GLfloat>(clamp01(b)), static_cast<GLfloat>(clamp01(a))}; }
        inline Color4F    ccc4F       (const Color3B& c)                            { return ccc4F(from255(c.r), from255(c.g), from255(c.b), 1); }
        inline Color4F    ccc4F       (const Color4B& c)                            { return ccc4F(from255(c.r), from255(c.g), from255(c.b), from255(c.a)); }
        inline Color4F    ccc4F       (const Color3F& c, float a)                   { return ccc4F(clamp01(c.r), clamp01(c.g), clamp01(c.b), clamp01(a)); }
        inline Color4F    ccc4F       (int hex, float a)                              { auto c = ccc3f(hex); return ccc4F(c.r,c.g,c.b,clamp01(a)); }
        
        inline Color3B      pick    (const std::vector<Color3B>& v)               { return v[pick(v.size())]; }
        inline Color3F      pick    (const std::vector<Color3F>& v)               { return v[pick(v.size())]; }
        inline Color4F      pick    (const std::vector<Color4F>& v)               { return v[pick(v.size())]; }
        
        
        inline ubyte        toAlphaB    (const Color4F& c)                            { return (ubyte)to255(c.a); }
        
        
        extern string       ccc3bstring (Color3B c);
        extern Color3B      ccc3bstring (string s);
        extern string       ccc3fstring (Color3F c);
        extern Color3F      ccc3fstring (string s);
        
        
        
        inline Color3F    lerp        (const Color3F& from, const Color3F& to, float t)      { return ccc3f(tiny::Math::lerp(from.r,to.r,t),tiny::Math::lerp(from.g,to.g,t),tiny::Math::lerp(from.b,to.b,t)); }
        inline Color3F    lerp01      (const Color3F& from, const Color3F& to, float t)      { return ccc3f(tiny::Math::lerp01(from.r,to.r,t),tiny::Math::lerp01(from.g,to.g,t),tiny::Math::lerp01(from.b,to.b,t)); }
        
        inline Color4F    lerp        (const Color4F& from, const Color4F& to, float t)      { return Color4F(tiny::Math::lerp(from.r,to.r,t),tiny::Math::lerp(from.g,to.g,t),tiny::Math::lerp(from.b,to.b,t),tiny::Math::lerp(from.a,to.a,t)); }
        inline Color4F    lerp01      (const Color4F& from, const Color4F& to, float t)      { return Color4F(tiny::Math::lerp01(from.r,to.r,t),tiny::Math::lerp01(from.g,to.g,t),tiny::Math::lerp01(from.b,to.b,t),tiny::Math::lerp(from.a,to.a,t)); }
        
        inline Color3B    add         (const Color3B& c, float r, float g, float b) { return { static_cast<GLubyte>(to255(float_01(c.r/255.f+r))), static_cast<GLubyte>(to255(float_01(c.g/255.f+g))), static_cast<GLubyte>(to255(float_01(c.b/255.f+b))), }; }
        inline Color3F    add         (const Color3F& c, float r, float g, float b) { return { static_cast<GLfloat>(float_01(c.r+r)), static_cast<GLfloat>(float_01(c.g+g)), static_cast<GLfloat>(float_01(c.b+b)) }; }
        inline Color3F    add         (const Color3F& c, float v)                   { return { static_cast<GLfloat>(float_01(c.r+v)), static_cast<GLfloat>(float_01(c.g+v)), static_cast<GLfloat>(float_01(c.b+v)) }; }
        
        inline Color3F    operator +  (Color3F base, Color3F p)                   { return add(base,p.r,p.g,p.b); }
        inline Color3F    operator -  (Color3F base, Color3F p)                   { return add(base,-p.r,-p.g,-p.b); }
        inline Color3FRef operator += (Color3FRef base, Color3F p)                { return base = ccc3f(float_01(base.r+p.r),float_01(base.g+p.g),float_01(base.b+p.b)); }
        inline Color3FRef operator -= (Color3FRef base, Color3F p)                { return base = ccc3f(float_01(base.r-p.r),float_01(base.g-p.g),float_01(base.b-p.b)); }
        
        inline Color4F    add         (const Color4F& c, float r, float g, float b) { return { static_cast<GLfloat>(float_01(c.r+r)), static_cast<GLfloat>(float_01(c.g+g)), static_cast<GLfloat>(float_01(c.b+b)), c.a}; }
        inline Color4F    add         (const Color4F& c, float v)                   { return add(c,v,v,v); }
        
        
        inline  Color3B   multiply    (const Color3B& c, float r, float g, float b) { return { static_cast<GLubyte>(to255(float_01(c.r/255.f*r))), static_cast<GLubyte>(to255(float_01(c.g/255.f*g))), static_cast<GLubyte>(to255(float_01(c.b/255.f*b))), }; }
        inline  Color3F   multiply    (const Color3F& c, float r, float g, float b) { return { static_cast<GLfloat>(float_01(c.r*r)), static_cast<GLfloat>(float_01(c.g*g)), static_cast<GLfloat>(float_01(c.b*b)) }; }
        inline  Color4F   multiply    (const Color4F& c, float r, float g, float b) { return { static_cast<GLfloat>(float_01(c.r*r)), static_cast<GLfloat>(float_01(c.g*g)), static_cast<GLfloat>(float_01(c.b*b)), c.a}; }
        inline  Color3B   multiply    (const Color3B& c, float v)                   { return multiply(c,v,v,v); }
        inline  Color3F   multiply    (const Color3F& c, float v)                   { return multiply(c,v,v,v); }
        inline  Color4F   multiply    (const Color4F& c, float v)                   { return multiply(c,v,v,v); }
        
        inline  Color3B   randomize   (const Color3B& c, Range v, bool across = false) { if (across) {float r = randomRangef(v); return ccc3b(c.r * r, c.g * r, c.b * r);}; return ccc3b(c.r * randomRangef(v), c.g * randomRangef(v), c.b * randomRangef(v)); }
        inline  Color3F   randomize   (const Color3F& c, Range v, bool across = false) { if (across) {float r = randomRangef(v); return ccc3f(c.r * r, c.g * r, c.b * r);}; return ccc3f(c.r * randomRangef(v), c.g * randomRangef(v), c.b * randomRangef(v)); }
        inline  Color4F   randomize   (const Color4F& c, Range v, bool across = false) { if (across) {float r = randomRangef(v); return ccc4F(c.r * r, c.g * r, c.b * r, c.a);}; return ccc4F(c.r * randomRangef(v), c.g * randomRangef(v), c.b * randomRangef(v), c.a); }
        
        inline  Color3F   randomAdd         (const Color3F& c, Color3F v)           { return ccc3f(c.r + randomSign(v.r), c.g + randomSign(v.g), c.b + randomSign(v.b)); }
        inline  Color3F   randomMultiply    (const Color3F& c, Color3F v)           { return ccc3f(c.r * randomSign(v.r), c.g * randomSign(v.g), c.b * randomSign(v.b)); }
        
        inline  Color3F   randomRange (Color3F f, Color3F t)    { return {randomRangef({f.r,t.r}),randomRangef({f.g,t.g}),randomRangef({f.b,t.b})}; }
        inline  Color4F   randomRange (Color4F f, Color4F t)    { return {randomRangef({f.r,t.r}),randomRangef({f.g,t.g}),randomRangef({f.b,t.b}),randomRangef({f.a,t.a})}; }
        
        inline  Color3F   operator +  (Color3F c, float v)      { c.r = clamp01(c.r + v); c.g = clamp01(c.g + v); c.b = clamp01(c.b + v); return c; }
        inline  Color3F   operator -  (Color3F c, float v)      { c.r = clamp01(c.r - v); c.g = clamp01(c.g - v); c.b = clamp01(c.b - v); return c; }
        inline  Color3F   operator *  (Color3F c, float v)      { c.r = clamp01(c.r * v); c.g = clamp01(c.g * v); c.b = clamp01(c.b * v); return c; }
        
        inline  Color4F   operator +  (Color4F c, float v)      { c.r = clamp01(c.r + v); c.g = clamp01(c.g + v); c.b = clamp01(c.b + v); return c; }
        inline  Color4F   operator -  (Color4F c, float v)      { c.r = clamp01(c.r - v); c.g = clamp01(c.g - v); c.b = clamp01(c.b - v); return c; }
        inline  Color4F   operator *  (Color4F c, float v)      { c.r = clamp01(c.r * v); c.g = clamp01(c.g * v); c.b = clamp01(c.b * v); return c; }
        

        
        inline  Color3F   HSVtoColor3F        (float h, float s, float v)                                 { return HSV(h,s,v).ccc3f(); }
        inline  Color4F   HSVAtoColor4F       (float h, float s, float v, float a)                        { return HSVA(h,s,v,a).ccc4f(); }

        
        
        
        inline CCRatio      alignment           (CCNodePtr p) {
            if (ccParentOf(p)) {
                CCPoint a = p -> getAnchorPointInPoints();
                CCRect b = bounds(ccParentOf(p));
                return {a.x/b.size.width,a.y/b.size.height};
            }
            return {0,0};
        }
        
        inline float        alignmentX          (CCNodePtr p)                                               { return alignment(p).x; }
        inline float        alignmentY          (CCNodePtr p)                                               { return alignment(p).y; }
        inline void         align               (CCNodePtr p, float x, float y)                             { Prnrn(p, x, y); }
        inline void         align               (CCNodePtr p, float x0, float y0, float x, float y)         { Prnrn(p, x0, y0, x, y); }
        inline void         align               (CCNodePtr p)                                               { align(p,.5,.5,.5,.5); }
        inline void         align               (CCNodePtr p, CCPoint to)                                   { Prnrn(p, to.x, to.y); }
        inline void         align               (CCNodePtr p, CCPoint from, CCPoint to)                     { Prnrn(p, from.x, from.y, to.x, to.y); }
        inline void         align               (CCNodePtr p, CCRatio from, CCNodePtr other, CCRatio to)    { Prnrn(p, from.x, from.y, other, to.x, to.y); }
        
        inline void         alignX              (CCNodePtr p, float from, float to)                         { CCPoint o = ccPosition(p); align(p, from, 0, to, 0); ccPosition(p,Vec2(ccPosition(p).x,o.y)); }
        inline void         alignY              (CCNodePtr p, float from, float to)                         { CCPoint o = ccPosition(p); align(p, 0, from, 0, to); ccPosition(p,Vec2(o.x,ccPosition(p).y)); }
        
        inline void         alignYRatioToPoint  (CCNodePtr n, float ratio, float point)                     { CCRatio p = p2r(ccParentOf(n),Vec2(0,point)); alignY(n,ratio,p.y); }
        inline void         alignXRatioToPoint  (CCNodePtr n, float ratio, float point)                     { CCRatio p = p2r(ccParentOf(n),Vec2(point,0)); alignX(n,ratio,p.x); }
        
        inline void         alignPointToRatio   (CCNodePtr n, CCPoint p, CCRatio to)                        { CCRatio from = p2r(n,p); align(n,from.x,to.x,from.y,to.y); }
        inline void         alignRatioToPoint   (CCNodePtr n, CCRatio from, CCPoint to)                     { CCRatio r = p2r(ccParentOf(n),to); align(n,from.x,r.x,from.y,r.y); }
        
        
        
        
        
        
        inline void         ccUserData          (CCNodePtr n, void * data)                                  { n->setUserData(data); }
        inline void         ccUserDataSetFirst  (CCNodePtr n, void * data)                                  { tAssert(not n->getUserData()); n->setUserData(data); }
        inline void *       ccUserData          (CCNodePtr n)                                               { return n->getUserData(); }
        inline void *       ccUserDataClear     (CCNodePtr n)                                               { auto r = n->getUserData(); n->setUserData(0); return r; }
        
        inline void         ccUserObject        (CCNodePtr n, CCObjectPtr o)                                { n->setUserObject(o); }
        inline void         ccUserObjectSetAndRelease       (CCNodePtr n, CCObjectPtr o)                    { n->setUserObject(o); ccSafeReleaseNull(o); }
        inline void         ccUserObjectSetFirstAndRelease  (CCNodePtr n, CCObjectPtr o)                    { tAssert(not n->getUserObject()); ccUserObjectSetAndRelease(n,o); }
        inline CCObjectPtr  ccUserObject        (CCNodePtr n)                                               { return n->getUserObject(); }
        inline CCObjectPtr  ccUserObjectClear   (CCNodePtr n)                                               { auto r = n->getUserObject(); n->setUserObject(0); return r; }
        
        
        
        
        
        
        inline void         ccTag               (CCNodePtr n, int t)                                        { n -> setTag(t); }
        inline int          ccTag               (CCNodePtr n)                                               { return n -> getTag(); }
        

        
        
        
        inline void         ccOpacity           (CCSpritePtr s, float_01 a)                                 { s -> setOpacity(to255(a)); }
        inline float_01     ccOpacity           (CCSpritePtr s)                                             { return s -> getOpacity()/255.f; }

        inline void         ccOpacity           (CCLayerGradientPtr s, float_01 a)                          { s -> setStartOpacity(to255(a)); s -> setEndOpacity(to255(a)); }
        inline void         ccOpacity           (CCLayerGradientPtr s, float_01 start, float_01 end)        { s -> setStartOpacity(to255(start)); s -> setEndOpacity(to255(end)); }

        inline float_01     ccOpacityStart      (CCLayerGradientPtr s)                                      { return s -> getStartOpacity()/255.f; }
        inline float_01     ccOpacityEnd        (CCLayerGradientPtr s)                                      { return s -> getEndOpacity()/255.f; }

        inline void         ccRGB               (CCSpritePtr n, double r, double g, double b)               { n -> setColor(ccc3b(r,g,b)); }
        inline void         ccRGBA              (CCSpritePtr n, double r, double g, double b, double a)     { ccRGB(n,r,g,b); ccOpacity(n,a); }
        inline void         ccColor             (CCSpritePtr n, Color3B c)                                  { n -> setColor(c); }
        inline void         ccColor             (CCSpritePtr n, Color3F c)                                  { n -> setColor(ccc3b(c)); }
        inline void         ccColor             (CCSpritePtr n, Color4F c)                                  { n -> setColor(ccc3b(c)); ccOpacity(n,c.a); }
        inline void         ccColor             (CCSpritePtr n, double r, double g, double b)               { n -> setColor(ccc3b(r,g,b)); }
        inline void         ccColor             (CCSpritePtr n, double r, double g, double b, double a)     { ccRGB(n,r,g,b); ccOpacity(n,a); }
        inline void         ccColor             (CCSpritePtr n, double gray)                                { ccRGB(n,gray,gray,gray); }
        inline void         ccColor             (CCSpritePtr n, double gray, double a)                      { ccRGB(n,gray,gray,gray); ccOpacity(n,a); }
        
        inline Color3F      ccColor             (CCSpritePtr n)                                             { return ccc3f(n -> getColor()); }
        inline Color3B      ccc3b               (CCSpritePtr n)                                             { return n -> getColor(); }
        inline Color3F      ccc3f               (CCSpritePtr n)                                             { return ccc3f(n -> getColor()); }
        inline Color4F      ccc4F               (CCSpritePtr n)                                             { return ccc4F(ccc3f(n), ccOpacity(n)); }
        
        
        inline HSV          ccColorHSV          (CCSpritePtr p)                                             { return HSV(ccColor(p)); }
        inline void         ccColorHSV          (CCSpritePtr p, HSV c)                                      { ccColor(p,c.ccc3f()); }
        inline void         ccColor             (CCSpritePtr p, HSV c)                                      { ccColor(p,c.ccc3f()); }
        
        inline void         ccBlend             (CCSpritePtr n, CCBlending b)                               { n->setBlendFunc(b); }
        inline CCBlending   ccBlend             (CCSpritePtr n)                                             { return n->getBlendFunc(); }
        inline void         ccBlending          (CCSpritePtr n, CCBlending b)                               { ccBlend(n,b); }
        inline CCBlending   ccBlending          (CCSpritePtr n)                                             { return ccBlend(n); }
        
        inline CCRatio      ccAlignment         (CCNodePtr p)                                               { return alignment(p); }
        inline float        ccAlignmentX        (CCNodePtr p)                                               { return ccAlignment(p).x; }
        inline float        ccAlignmentY        (CCNodePtr p)                                               { return ccAlignment(p).y; }
        inline void         ccAlign             (CCNodePtr p, float x, float y)                             { Prnrn(p, x, y); }
        inline void         ccAlign             (CCNodePtr p, float x0, float y0, float x, float y)         { Prnrn(p, x0, y0, x, y); }
        inline void         ccAlign             (CCNodePtr p)                                               { ccAlign(p,.5,.5,.5,.5); }
        inline void         ccAlign             (CCNodePtr p, CCPoint to)                                   { Prnrn(p, to.x, to.y); }
        inline void         ccAlign             (CCNodePtr p, CCPoint from, CCPoint to)                     { Prnrn(p, from.x, from.y, to.x, to.y); }
        inline void         ccAlign             (CCNodePtr p, CCRatio from, CCNodePtr other, CCRatio to)    { Prnrn(p, from.x, from.y, other, to.x, to.y); }
        
        inline void         ccAlignX            (CCNodePtr p, float from, float to)                         { CCPoint o = ccPosition(p); ccAlign(p, from, 0, to, 0); ccPosition(p,Vec2(ccPosition(p).x,o.y)); }
        inline void         ccAlignY            (CCNodePtr p, float from, float to)                         { CCPoint o = ccPosition(p); ccAlign(p, 0, from, 0, to); ccPosition(p,Vec2(o.x,ccPosition(p).y)); }
        inline void         ccAlignX            (CCNodePtr p, float to)                                     { CCPoint o = ccPosition(p); ccAlign(p, ccAnchor(p).x, 0, to, 0); ccPosition(p,Vec2(ccPosition(p).x,o.y)); }
        inline void         ccAlignY            (CCNodePtr p, float to)                                     { CCPoint o = ccPosition(p); ccAlign(p, 0, ccAnchor(p).y, 0, to); ccPosition(p,Vec2(o.x,ccPosition(p).y)); }
        
        inline void         ccAlignTo           (CCNodePtr p, CCRatio to)                                   { ccAlign(p,ccAnchor(p),to); }
        
        inline void         ccAlignYRatioToPoint(CCNodePtr n, float ratio, float point)                     { CCRatio p = p2r(ccParentOf(n),Vec2(0,point)); ccAlignY(n,ratio,p.y); }
        inline void         ccAlignXRatioToPoint(CCNodePtr n, float ratio, float point)                     { CCRatio p = p2r(ccParentOf(n),Vec2(point,0)); ccAlignX(n,ratio,p.x); }
        
        inline void         ccAlignPointToRatio (CCNodePtr n, CCPoint p, CCRatio to)                        { CCRatio from = p2r(n,p); ccAlign(n,from.x,to.x,from.y,to.y); }
        inline void         ccAlignRatioToPoint (CCNodePtr n, CCRatio from, CCPoint to)                     { CCRatio r = p2r(ccParentOf(n),to); ccAlign(n,from.x,r.x,from.y,r.y); }
        
        ______ void         ccAlignToOther      (CCNodePtr me, CCRatio rme, CCNodePtr other, CCRatio rother, CCPoint move = CCPoint(0,0));
        ______ void         ccAlignToScreen     (CCNodePtr me, CCRatio rme, CCRatio rscreen, CCPoint move = CCPoint(0,0));

        inline void         ccAttach            (CCNodePtr parent, CCNodePtr child, CCRatio loc)            { parent->addChild(child); ccAlign(child,loc); }
        inline void         ccAttach            (CCNodePtr parent, CCNodePtr child, CCRatio loc, int z)     { parent->addChild(child,z); ccAlign(child,loc); }
        
        extern Color3F ccc3fBLACK;
        extern Color3F ccc3fWHITE;
        extern Color3F ccc3fRED;
        
        CCActionIntervalPtr aiAlignToRatio      (float duration, CCPoint ratio) ;
        CCActionIntervalPtr aiAlignToPoint      (float duration, CCPoint point) ;
        
        
        
        
        
        STRUCT (CCAlignment) {
            CCRatio to = {.5,.5};
            CCRatio from = {.5,.5};
            CCAlignment() {}
            CCAlignment(CCRatio t) : to(t) ,from(t) {}
            CCAlignment(CCRatio f, CCRatio t) : to(t) ,from(f) {}
            CCAlignment(float x, float y) : to(Vec2(x,y)) ,from(Vec2(x,y)) {}
            CCAlignment(float fx, float fy, float tx, float ty) : to(Vec2(tx,ty)) ,from(Vec2(fx,fy)) {}
            inline void apply(CCNodePtr p) const { ccAlign(p,from,to); }
            inline CCAlignment inverse              (bool h, bool v) const
            {
                return CCAlignment(Vec2(h ? 1-from.x : from.x, v ? 1-from.y : from.y),Vec2(h ? 1 - to.x : to.x, v ? 1-to.y : to.y));
            }
            inline CCAlignment inverseHorizontal    () const { return inverse(true,false); }
            inline CCAlignment inverseVertical      () const { return inverse(false,true); }
        };
        
        STRUCT (CCAnchor) : public CCPoint {
            CCAnchor() : CCPoint(.5,.5) {}
            CCAnchor(CCPoint p) : CCPoint(p) {}
            CCAnchor(float x, float y) : CCPoint(x,y) {}
            inline void apply(CCNodePtr p) const { ccAnchor(p,*this); }
        };
        
        STRUCT (CCScale) : public CCPoint {
            CCScale(float s = 1) : CCPoint(s,s) {}
            CCScale(CCPoint p) : CCPoint(p) {}
            CCScale(float x, float y) : CCPoint(x,y) {}
            inline void apply(CCNodePtr p) const { ccScaleXY(p,x,y); }
        };
        
        STRUCT (CCSkew) : public CCPoint {
            CCSkew(float k = 0) : CCPoint(k,k) {}
            CCSkew(CCPoint p) : CCPoint(p) {}
            CCSkew(float x, float y) : CCPoint(x,y) {}
            inline void apply(CCNodePtr p) const { ccSkewXY(p,x,y); }
        };
        
        STRUCT (CCPosition) : public CCPoint {
            CCPosition() : CCPoint(0,0) {}
            CCPosition(CCPoint p) : CCPoint(p) {}
            CCPosition(float x, float y) : CCPoint(x,y) {}
            inline void apply(CCNodePtr p) const { ccPosition(p,*this); }
        };
        
        STRUCT (CCRotation) {
            float value = 0.f;
            CCRotation() {}
            CCRotation(float r) : value(r) {}
            inline operator float () const { return value; }
            inline void apply(CCNodePtr p) const { ccRotation(p,value); }
        };
        
        STRUCT (CCOpacity) {
            tiny::Math::float_01 value = 0.f;
            CCOpacity() {}
            CCOpacity(float r) : value(r) {}
            inline operator float () const { return value; }
            inline void apply(CCSpritePtr p) const { ccOpacity(p,value); }
        };
        
        STRUCT (CCColor) : public Color3F {
            CCColor() {}
            CCColor(Color3F p) { r = p.r; g = p.g; b = p.b; }
            CCColor(tiny::Math::float_01 pr, tiny::Math::float_01 pg, tiny::Math::float_01 pb) { r=pr; g = pg, b = pb; }
            inline void apply(CCSpritePtr p) const { ccColor(p,*this); }
        };
        
        typedef CCAlignment     CCPropertyAlignment;
        typedef CCAnchor        CCPropertyAnchor;
        typedef CCScale         CCPropertyScale;
        typedef CCSkew          CCPropertySkew;
        typedef CCPosition      CCPropertyPosition;
        typedef CCRotation      CCPropertyRotation;
        typedef CCOpacity       CCPropertyOpacity;
        typedef CCColor         CCPropertyColor;
        
        
        
        
        
        
        namespace Tag
        {
            namespace Node
            {
                
            }
            
            namespace Sprite
            {
                
            }
            
            namespace Action
            {
                enum
                {
                    None                = 0,
                    
                    Scale               = 1,
                    Rotation            = 1 << 1,
                    Position            = 1 << 2,
                    Color               = 1 << 3,
                    Opacity             = 1 << 4,
                    Time                = 1 << 5,
                };
            }
        }
        
        inline int          ccTag                       (CCActionPtr a)             { return a->getTag(); }
        inline CCActionPtr  ccTag                       (CCActionPtr a, int tag)    { a->setTag(tag); return a; }
        inline CCActionPtr  ccTagS                      (CCActionPtr a)             { a->setTag(Tag::Action::Scale); return a; }
        inline CCActionPtr  ccTagR                      (CCActionPtr a)             { a->setTag(Tag::Action::Rotation); return a; }
        inline CCActionPtr  ccTagP                      (CCActionPtr a)             { a->setTag(Tag::Action::Position); return a; }
        inline CCActionPtr  ccTagC                      (CCActionPtr a)             { a->setTag(Tag::Action::Color); return a; }
        inline CCActionPtr  ccTagO                      (CCActionPtr a)             { a->setTag(Tag::Action::Opacity); return a; }
        inline CCActionPtr  ccTagT                      (CCActionPtr a)             { a->setTag(Tag::Action::Time); return a; }
        
        ______ int          ccTagOr                     (vectorCRef(CCActionPtr) p);
        
        inline void         ccActionStop                (CCActionPtr a)             { if (a) { a->getOriginalTarget()->stopAction(a); } }
        inline void         ccActionStopAndClear        (CCActionPtr & a)           { if (a) { a->getOriginalTarget()->stopAction(a); a = 0; } }
        inline void         ccActionStopAndClear        (CCActionIntervalPtr & a)   { if (a) { a->getOriginalTarget()->stopAction(a); a = 0; } }
        inline void         ccActionStopAll             (CCNodePtr n)               { if (n) { n->stopAllActions(); } }

        ______ std::vector<CCActionPtr>     ccActionsOf (CCNodePtr n);
        
        inline void         ccActionStopAllWithTag                  (CCNodePtr n, int tag)              { for(auto a:ccActionsOf(n)) if (tag == ccTag(a)) ccActionStop(a); }
        inline void         ccActionStopAllWithTagPartial           (CCNodePtr n, int tag)              { for(auto a:ccActionsOf(n)) if (tag & ccTag(a)) ccActionStop(a); }
        inline void         ccActionStopAllWithTagAndRunOn          (CCNodePtr n, CCActionPtr a)        { ccActionStopAllWithTag(n,ccTag(a)); n->runAction(a); }
        inline void         ccActionStopAllWithTagPartialAndRunOn   (CCNodePtr n, CCActionPtr a)        { ccActionStopAllWithTagPartial(n,ccTag(a)); n->runAction(a); }
        inline void         ccActionStopAndRunOn                    (CCNodePtr n, CCActionPtr a)        { ccActionStopAllWithTagPartialAndRunOn(n,a); }
        
        
        
        inline void         ccRetain            (CCNodePtr n)                                               { n -> retain(); }
        inline void         ccRelease           (CCNodePtr n)                                               { n -> release(); }
        
        
        ______  bool                ccContains                  (CCNodePtr node, CCPoint screen, bool onlyWhenVisible = true);
        ______  bool                ccContainsOval              (CCNodePtr node, CCPoint screen, float factor = 1, bool onlyWhenVisible = true);
        inline  bool                hit                         (CCNodePtr node, CCPoint screen, bool onlyWhenVisible = true) { return ccContains(node,screen,onlyWhenVisible); }
        
        
        
        
        namespace io
        {
            bool        saveToFilePNG   (CCNodePtr sprite, string f);
            CCSpritePtr readFromFilePNG (string filenameInDocumentsDirectory);
        }
        
        
        
#define ccAddSpritesheet(PLIST)                     CCSpriteFrameCache::sharedSpriteFrameCache() -> addSpriteFramesWithFile( PLIST );
        
            //#define mTagAction(ACTION,TAG) (ACTION) -> setTag((int)(TAG))
        
#define ccRun(ACTION)                               runAction(ACTION)
#define ccRunOn(TARGET,ACTION)                      (TARGET) -> runAction( ACTION )
#define ccRunBlock(BLOCK)                           runAction( aiCall( BLOCK ) )
#define ccRunBlockOn(TARGET,BLOCK)                  (TARGET) -> runAction( aiCall( BLOCK ) )
        
#define ccRunDelayed(DELAY,ACTION)                  runAction(CCSequence::create(CCDelayTime::create( DELAY ),( ACTION ), NULL))
#define ccRunDelayedOn(DELAY,TARGET,ACTION)         (TARGET) -> runAction(CCSequence::create(CCDelayTime::create( DELAY ),( ACTION ), NULL))
#define ccRunDelayedBlock(DELAY,BLOCK)              runAction( aiCall( (DELAY), BLOCK ) )
#define ccRunDelayedBlockOn(DELAY,TARGET,BLOCK)     (TARGET) -> runAction( aiCall( (DELAY), BLOCK ) )
        
#define ccRunSequence(...)                          runAction(CCSequence::create( __VA_ARGS__ , NULL))
#define ccRunSequenceOn(TARGET,...)                 (TARGET) -> runAction( CCSequence::create( __VA_ARGS__ , NULL) )
        
#define ccRunDelayedSequence(DELAY,...)             runAction(CCSequence::create(CCDelayTime::create( DELAY ), __VA_ARGS__ , NULL))
#define ccRunDelayedSequenceOn(DELAY,TARGET,...)    (TARGET) -> runAction(CCSequence::create(CCDelayTime::create( DELAY ), __VA_ARGS__ , NULL))
        
#define ccRunForever(ACTION)                        runAction(CCRepeatForever::create( ACTION ))
#define ccRunForeverOn(TARGET,ACTION)               (TARGET) -> runAction(CCRepeatForever::create( ACTION ))
#define ccRunForeverDelayed(DELAY,ACTION)           runAction(CCSequence::create(CCDelayTime::create( DELAY ), CCRepeat::create( (ACTION), 65535 ), NULL))
#define ccRunForeverDelayedOn(DELAY,TARGET,ACTION)  (TARGET) -> runAction( CCSequence::create( CCDelayTime::create( DELAY ), CCRepeat::create( ( ACTION ), 65535 ), NULL))
#define ccRunDelayedForever(DELAY,ACTION)           runAction(CCSequence::create(CCDelayTime::create( DELAY ), CCRepeat::create( (ACTION), 65535 ), NULL))
#define ccRunDelayedForeverOn(DELAY,TARGET,ACTION)  (TARGET) -> runAction( CCSequence::create( CCDelayTime::create( DELAY ), CCRepeat::create( ( ACTION ), 65535 ), NULL))
#define ccRunForeverBlock(BLOCK)                    runAction(CCRepeatForever::create( aiCall( BLOCK )))
#define ccRunForeverBlockOn(TARGET,BLOCK)           (TARGET) -> runAction(CCRepeatForever::create( aiCall( BLOCK )))
        
#define ccForever(ACTION)                           (CCRepeatForever::create( ACTION ))
#define ccSequence(...)                             (CCSequence::create( __VA_ARGS__ , NULL))
#define ccDelayedSequence(TIME,...)                 (CCSequence::create( CCDelayTime::create((TIME) <= 0 ? 0 : (TIME)), __VA_ARGS__ , NULL))
#define ccForeverSequence(...)                      (CCRepeat::create((CCActionIntervalPtr)CCSequence::create( __VA_ARGS__ , NULL), 65535 ))
#define ccRepeatSequence(COUNT,...)                 (CCRepeat::create((CCActionIntervalPtr)CCSequence::create( __VA_ARGS__ , NULL), COUNT))
#define ccRepeatALot(...)                           (CCRepeat::create( __VA_ARGS__ , 65535 ))
        
#define ccSpawn(...)                                ((CCActionIntervalPtr)CCSpawn::create( __VA_ARGS__ , NULL))
        
#define ccDelay(TIME,ACTION)                        (CCSequence::create(CCDelayTime::create( TIME ),( ACTION ), NULL))
        
#define ccDelayedCall(TIME,FUNC)                    (CCSequence::create(CCDelayTime::create( TIME ), CCCallFunc::create(this,SELECTOR_CALLFUNC( FUNC )),0))
#define ccDelayedCallN(TIME,FUNC)                   (CCSequence::create(CCDelayTime::create( TIME ), CCCallFuncN::create(this,SELECTOR_CALLFUNC_N( FUNC )),0))
#define ccDelayedCallND(TIME,FUNC,DATA)             (CCSequence::create(CCDelayTime::create( TIME ), CCCallFuncND::create(this,SELECTOR_CALLFUNC_ND( FUNC ),(void *)( DATA )),0))
#define ccDelayedCallO(TIME,FUNC,OBJECT)            (CCSequence::create(CCDelayTime::create( TIME ), CCCallFuncO::create(this,SELECTOR_CALLFUNC_O( FUNC ),( OBJECT )),0))
        
#define ccDelayedCallOn(TIME,TARGET,FUNC)           (CCSequence::create(CCDelayTime::create( TIME ), CCCallFunc::create(TARGET,SELECTOR_CALLFUNC( FUNC )),0))
#define ccDelayedCallOnN(TIME,TARGET,FUNC)          (CCSequence::create(CCDelayTime::create( TIME ), CCCallFuncN::create(TARGET,SELECTOR_CALLFUNC_N( FUNC )),0))
#define ccDelayedCallOnND(TIME,TARGET,FUNC,DATA)    (CCSequence::create(CCDelayTime::create( TIME ), CCCallFuncND::create(TARGET,SELECTOR_CALLFUNC_ND( FUNC ),(void *)( DATA )),0))
#define ccDelayedCallOnO(TIME,TARGET,FUNC,OBJECT)   (CCSequence::create(CCDelayTime::create( TIME ), CCCallFuncO::create(TARGET,SELECTOR_CALLFUNC_O( FUNC ),( OBJECT )),0))
        
#define ccCall(FUNC)                                (CCCallFunc::create(this,SELECTOR_CALLFUNC( FUNC )))
#define ccCallN(FUNC)                               (CCCallFuncN::create(this,SELECTOR_CALLFUNC_N( FUNC )))
#define ccCallND(FUNC,DATA)                         (CCCallFuncND::create(this,SELECTOR_CALLFUNC_ND( FUNC ),(void *)( DATA )))
#define ccCallO(FUNC,OBJECT)                        (CCCallFuncO::create(this,SELECTOR_CALLFUNC_O( FUNC ),OBJECT))
        
#define ccCallOn(TARGET,FUNC)                       (CCCallFunc::create(TARGET,SELECTOR_CALLFUNC( FUNC )))
#define ccCallOnN(TARGET,FUNC)                      (CCCallFuncN::create(TARGET,SELECTOR_CALLFUNC_N( FUNC )))
#define ccCallOnND(TARGET,FUNC,DATA)                (CCCallFuncND::create(TARGET,SELECTOR_CALLFUNC_ND( FUNC ),(void *)( DATA )))
#define ccCallOnO(TARGET,FUNC,OBJECT)               (CCCallFuncO::create(TARGET,SELECTOR_CALLFUNC_O( FUNC ),OBJECT))
        
        
        
        inline vector<CCActionIntervalPtr> operator +       (vectorCRef(CCActionIntervalPtr) v, vectorCRef(CCActionIntervalPtr) b)    { vector<CCActionIntervalPtr> r = v; append(r,b); return r; }
        inline vector<CCActionIntervalPtr> operator +       (vectorCRef(CCActionIntervalPtr) v, CCActionIntervalPtr b)                { vector<CCActionIntervalPtr> r; r.resize(1+v.size()); std::copy(begin(v),end(v),begin(r)); return r; }
        inline vector<CCActionIntervalPtr> operator +       (CCActionIntervalPtr b, vectorCRef(CCActionIntervalPtr) v)                { vector<CCActionIntervalPtr> r; r.resize(1+v.size()); r[0] = b; std::copy(begin(v),end(v),begin(r)+1); return r; }
        
        
        
#include "tinyCocos2DCCAction.h"
        
        
        
        inline CCActionIntervalPtr      aiDelay                 (float t )                              { auto r = CCDelayTime::create(t < 0 ? 0 : t); ccTagT(r); return r; }
        inline CCActionIntervalPtr      aiDelay                 (float t, CCActionIntervalPtr a)        { auto r = (t <= 0) ? a : CCSequence::create(CCDelayTime::create(t),a,NULL); ccTag(r,ccTag(a)); return r; }
        inline CCActionIntervalPtr      aiDelay                 (float t, CCActionInstantPtr a)         { return aiDelay(t,aiAction(a)); }
        inline CCActionIntervalPtr      aiDelayUpTo             (float tmax, CCActionIntervalPtr a)     { tmax = std::max(0.f,tmax-a->getDuration()); return aiDelay(tmax,a); }
        
        inline CCRepeatForeverPtr       aForever                (CCActionIntervalPtr a)                 { auto r = CCRepeatForever::create(a); ccTag(r,ccTag(a)); return r; }
        inline CCRepeatPtr              aRepeat                 (uint count, CCFiniteTimeActionPtr a)   { auto r = CCRepeat::create(a,count); ccTag(r,ccTag(a)); return r; }
        inline CCRepeatPtr              aRepeatEndlessly        (CCFiniteTimeActionPtr a)               { auto r = CCRepeat::create(a,65536*8); ccTag(r,ccTag(a)); return r; }
        
        inline CCTargetedActionPtr      aTargeted               (CCNodePtr t, CCActionInstantPtr a)     { auto r = CCTargetedAction::create(t,aiAction(a)); ccTag(r,ccTag(a)); return r; }
        inline CCTargetedActionPtr      aTargeted               (CCNodePtr t, CCActionIntervalPtr a)    { auto r = CCTargetedAction::create(t,a); ccTag(r,ccTag(a)); return r; }
        inline CCActionIntervalPtr      aiTargeted              (CCNodePtr t, CCActionIntervalPtr a)    { auto r = CCTargetedAction::create(t,a); ccTag(r,ccTag(a)); return r; }
        
        inline CCSpeedPtr               aSpeed                  (CCActionIntervalPtr a, float speed)    { auto r = CCSpeed::create(a,speed); ccTag(r,ccTag(a)); return r; }
        
        inline CCActionPtr              aEmpty                  ()                                      { return aiDelay(0.f); }
        inline CCActionIntervalPtr      aiEmpty                 (float t = 0.f)                         { return aiDelay(t); }
        inline CCActionIntervalPtr      aiEmpty                 (float delay, float duration)           { return aiDelay(delay+duration); }
        
        inline CCActionInstantPtr       aHide                   ()                                      { return CCHide::create(); }
        inline CCActionInstantPtr       aShow                   ()                                      { return CCShow::create(); }
        inline CCActionIntervalPtr      aiHide                  ()                                      { return aiAction(aHide()); }
        inline CCActionIntervalPtr      aiShow                  ()                                      { return aiAction(aShow()); }
        
        
        inline CCEaseIn *               eIn                     (CCActionIntervalPtr a, float f)        { auto r = EaseIn::create(a,f); ccTag(r,ccTag(a)); return r; }
        inline CCEaseOut *              eOut                    (CCActionIntervalPtr a, float f)        { auto r = EaseOut::create(a,f); ccTag(r,ccTag(a)); return r; }
        inline CCEaseInOut *            eInOut                  (CCActionIntervalPtr a, float f)        { auto r = EaseInOut::create(a,f); ccTag(r,ccTag(a)); return r; }
        
        inline CCEaseBackIn *           eBackIn                 (CCActionIntervalPtr a)                 { auto r = EaseBackIn::create(a); ccTag(r,ccTag(a)); return r; }
        inline CCEaseBackOut *          eBackOut                (CCActionIntervalPtr a)                 { auto r = EaseBackOut::create(a); ccTag(r,ccTag(a)); return r; }
        inline CCEaseBackInOut *        eBackInOut              (CCActionIntervalPtr a)                 { auto r = EaseBackInOut::create(a); ccTag(r,ccTag(a)); return r; }
        
        inline CCEaseBounceIn *         eBounceIn               (CCActionIntervalPtr a)                 { auto r = EaseBounceIn::create(a); ccTag(r,ccTag(a)); return r; }
        inline CCEaseBounceOut *        eBounceOut              (CCActionIntervalPtr a)                 { auto r = EaseBounceOut::create(a); ccTag(r,ccTag(a)); return r; }
        inline CCEaseBounceInOut *      eBounceInOut            (CCActionIntervalPtr a)                 { auto r = EaseBounceInOut::create(a); ccTag(r,ccTag(a)); return r; }
        
        inline CCEaseElasticIn *        eElasticIn              (CCActionIntervalPtr a, float f)        { auto r = EaseElasticIn::create(a,f); ccTag(r,ccTag(a)); return r; }
        inline CCEaseElasticOut *       eElasticOut             (CCActionIntervalPtr a, float f)        { auto r = EaseElasticOut::create(a,f); ccTag(r,ccTag(a)); return r; }
        inline CCEaseElasticInOut *     eElasticInOut           (CCActionIntervalPtr a, float f)        { auto r = EaseElasticInOut::create(a,f); ccTag(r,ccTag(a)); return r; }
        
        inline CCEaseExponentialIn *    eExponentialIn          (CCActionIntervalPtr a)                 { auto r = EaseExponentialIn::create(a); ccTag(r,ccTag(a)); return r; }
        inline CCEaseExponentialOut *   eExponentialOut         (CCActionIntervalPtr a)                 { auto r = EaseExponentialOut::create(a); ccTag(r,ccTag(a)); return r; }
        inline CCEaseExponentialInOut * eExponentialInOut       (CCActionIntervalPtr a)                 { auto r = EaseExponentialInOut::create(a); ccTag(r,ccTag(a)); return r; }
        
        inline CCEaseRate *             eRate                   (CCActionIntervalPtr a, float f)        { auto r = CCEaseRate::create(a,f); ccTag(r,ccTag(a)); return r; }
        
        inline CCEaseSineIn *           eSineIn                 (CCActionIntervalPtr a)                 { auto r = EaseSineIn::create(a); ccTag(r,ccTag(a)); return r; }
        inline CCEaseSineOut *          eSineOut                (CCActionIntervalPtr a)                 { auto r = EaseSineOut::create(a); ccTag(r,ccTag(a)); return r; }
        inline CCEaseSineInOut *        eSineInOut              (CCActionIntervalPtr a)                 { auto r = EaseSineInOut::create(a); ccTag(r,ccTag(a)); return r; }
        
        
        
        
        
        
        inline CCMoveTo *               aMoveTo                 (float duration, CCPoint p)         { auto r = CCMoveTo::create(duration,p); ccTagP(r); return r; }
        inline CCMoveBy *               aMoveBy                 (float duration, CCPoint p)         { auto r = CCMoveBy::create(duration,p); ccTagP(r); return r; }
        
        
        
        
        
        inline CCBezierTo *             aBezierTo               (float duration, ccBezierConfig c)  { auto r = CCBezierTo::create(duration,c); ccTagP(r); return r; }
        inline CCBezierBy *             aBezierBy               (float duration, ccBezierConfig c)  { auto r = CCBezierBy::create(duration,c); ccTagP(r); return r; }
        
            //                                                                                                                [i].x = powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x;
        inline float                    ccBezierAt              (float a, float b, float c, float d, float t)                               { const float _t = (1.f-t); return a*_t*_t*_t + 3.f*t*_t*_t*b + 3.f*t*t*_t*c + d*t*t*t; }
        inline CCPoint                  ccBezierAt              (float_01 t, ccBezierConfigCRef c)                                          { return Vec2(ccBezierAt(0, c.controlPoint_1.x, c.controlPoint_2.x, c.endPosition.x, t), ccBezierAt(0, c.controlPoint_1.y, c.controlPoint_2.y, c.endPosition.y, t)); }
        inline CCPoint                  ccBezierAt              (CCPointCRef from, float_01 t, ccBezierConfigCRef c)                        { return from+ccBezierAt(t,c); }
            //return Vec2(ccBezierAt(from.x, from.x+c.controlPoint_1.x, from.x+c.controlPoint_2.x, from.x+c.endPosition.x, t), ccBezierAt(from.y, from.y+c.controlPoint_1.y, from.y+c.controlPoint_2.y, from.y+c.endPosition.y, t));
        ______ CCAngle                  ccBezierAngleAt         (float_01 t, ccBezierConfigCRef c, float delta = 0.001);                     //{ return CCAngle(ccBezierAt(t+delta,c)-ccBezierAt(t-delta,c)); }
        
        ______ ccBezierConfig           ccBezierConfigWithAngleAbsolute (CCPoint p0, CCAngle angleD0, float d0, CCPoint p1, CCAngle angleD1, float d1);
        ______ ccBezierConfig           ccBezierConfigWithAngleRelative (CCPoint p0, CCAngle angleD0, float d0, CCPoint p1, CCAngle angleD1, float d1);
        ______ double                   ccBezierLength                  (CCPoint p0, ccBezierConfigCRef config, float dt);
        
        STRUCT (ccBezierDistance)
        {
            struct {
                float t = -1;
                float v = -1;
            } minimum, maximum;
            
            ccBezierDistance()
            {
                minimum.v  = std::numeric_limits<double>::max();
                maximum.v  = std::numeric_limits<double>::min();
            }
            inline bool valid () const { return minimum.v <= maximum.v; }
        };
        
        ______ ccBezierDistance         ccBezierDistanceTo      (CCPoint p0, ccBezierConfigCRef config, CCPoint to, float dt);
        ______ ccBezierConfig           ccBezierFrom            (CCPoint from, ccBezierConfig c);
        
        STRUCT (ccBezierDescription)
        {
            CCAngle angle0;
            CCAngle angle1;
            float distance0 = 0;
            float distance1 = 0;
            
            ccBezierDescription() {}
            ccBezierDescription(float d0, CCAngle a0, float d1, CCAngle a1) : distance0(d0), angle0(a0), distance1(d1), angle1(a1) {}
            
            inline ccBezierConfig bezierConfigWithAngleRelative (CCPoint p0, CCPoint p1) const { return ccBezierConfigWithAngleRelative(p0,angle0,distance0,p1,angle1,distance1); }
            inline ccBezierConfig bezierConfigWithAngleAbsolute (CCPoint p0, CCPoint p1) const { return ccBezierConfigWithAngleAbsolute(p0,angle0,distance0,p1,angle1,distance1); }
        };
        
        std::ostream & operator << (std::ostream & o, const ccBezierDescription & p);
        
        
        
        
        inline CCActionIntervalPtr      aInterval       (CCActionInstantPtr a)                              { return aiAction(a); }
        
        ______ CCSequencePtr            aSequence       (vectorCRef(CCActionIntervalPtr) actions) ;
        ______ CCSpawnPtr               aSpawn          (vectorCRef(CCActionIntervalPtr) actions) ;
        

        
        
        inline CCScaleTo *              aScaleTo        (float duration, float f)                           { auto r = CCScaleTo::create(duration,f); ccTagS(r); return r; }
        inline CCScaleTo *              aScaleToZero    (float duration)                                    { return aScaleTo(duration,0.001); }
        inline CCScaleTo *              aScaleTo        (float duration, float x, float y)                  { auto r = CCScaleTo::create(duration,x,y); ccTagS(r); return r; }
        inline CCScaleTo *              aScaleTo        (float duration, CCPoint p)                         { return aScaleTo(duration,p.x,p.y); }
        inline CCScaleBy *              aScaleBy        (float duration, float f)                           { auto r = CCScaleBy::create(duration,f); ccTagS(r); return r; }
        inline CCScaleBy *              aScaleBy        (float duration, float x, float y)                  { auto r = CCScaleBy::create(duration,x,y); ccTagS(r); return r; }
        inline CCScaleTo *              aScaleBy        (float duration, CCPoint p)                         { return aScaleBy(duration,p.x,p.y); }
        
        inline CCSkewTo *               aSkewTo         (float duration, float f)                           { auto r = CCSkewTo::create(duration,f,f); ccTagS(r); return r; }
        inline CCSkewTo *               aSkewToZero     (float duration)                                    { return aSkewTo(duration,0.0); }
        inline CCSkewTo *               aSkewTo         (float duration, float x, float y)                  { auto r = CCSkewTo::create(duration,x,y); ccTagS(r); return r; }
        inline CCSkewTo *               aSkewTo         (float duration, CCPoint p)                         { return aSkewTo(duration,p.x,p.y); }
        inline CCSkewBy *               aSkewBy         (float duration, float f)                           { auto r = CCSkewBy::create(duration,f,f); ccTagS(r); return r; }
        inline CCSkewBy *               aSkewBy         (float duration, float x, float y)                  { auto r = CCSkewBy::create(duration,x,y); ccTagS(r); return r; }
        inline CCSkewTo *               aSkewBy         (float duration, CCPoint p)                         { return aSkewBy(duration,p.x,p.y); }
        
        inline CCRotateTo *             aRotateTo       (float duration, float f)                           { auto r = CCRotateTo::create(duration,f); ccTagR(r); return r; }
        inline CCRotateBy *             aRotateBy       (float duration, float f)                           { auto r = CCRotateBy::create(duration,f); ccTagR(r); return r; }
        
        ______ CCActionInterval *       aSwayBy         (float duration, float r);

        inline CCFadeTo *               aOpacityTo      (float duration, float_01 f)                        { auto r = CCFadeTo::create(duration,to255(f)); ccTagO(r); return r; }
        inline CCFadeTo *               aOpacity        (float duration, float_01 f)                        { auto r = CCFadeTo::create(duration,to255(f)); ccTagO(r); return r; }
        
        inline CCFadeTo *               aFadeTo         (float duration, float_01 f)                        { auto r = CCFadeTo::create(duration,to255(f)); ccTagO(r); return r; }
        inline CCFadeOut *              aFadeOut        (float duration)                                    { auto r = CCFadeOut::create(duration); ccTagO(r); return r; }
        inline CCFadeIn *               aFadeIn         (float duration)                                    { auto r = CCFadeIn::create(duration); ccTagO(r); return r; }
        
        inline CCTintTo *               aColorTo        (float duration, Color3F p)                         { Color3B c = p.ccc3b(); auto r = CCTintTo::create(duration,c.r,c.g,c.b); ccTagC(r); return r; }
        inline CCTintTo *               aColor          (float duration, Color3F p)                         { return aColorTo(duration,p); }
        inline CCActionInterval *       aColorTo        (float duration, Color3F p, float a)                { auto r = aSpawn({ aColorTo(duration,p), aOpacityTo(duration,a) }); ccTagO(r); ccTagC(r); return r; }
        inline CCActionInterval *       aColor          (float duration, Color3F p, float a)                { return aColorTo(duration,p,a); }
        inline CCActionInterval *       aColorTo        (float duration, Color4F p)                         { return aColorTo(duration,Color3F {p.r,p.g,p.b},p.a); }
        inline CCActionInterval *       aColor          (float duration, Color4F p)                         { return aColorTo(duration,p); }
        inline CCTintTo *               aTintTo         (float duration, Color3F p)                         { return aColorTo(duration,p); }
        inline CCTintTo *               aTintTo         (float duratio, float_01 r, float_01 g, float_01 b) { Color3B c = ccc3b(r,g,b); auto R = CCTintTo::create(duratio,c.r,c.g,c.b); ccTagC(R); return R; }
        inline CCTintBy *               aTintBy         (float duratio, float_01 r, float_01 g, float_01 b) { Color3B c = ccc3b(r,g,b); auto R = CCTintBy::create(duratio,c.r,c.g,c.b); ccTagC(R); return R; }
        
        inline CCActionInstantPtr       aRemoveSelf           (bool cleanup=true) { return CCRemoveSelf::create(cleanup); }
        inline CCActionInstantPtr       aRemoveFromParent     (bool cleanup=true) { return CCRemoveSelf::create(cleanup); }
        
        inline CCActionIntervalPtr      aiRemoveSelf         (bool cleanup=true) { return aiAction(CCRemoveSelf::create(cleanup)); }
        inline CCActionIntervalPtr      aiRemoveFromParent   (bool cleanup=true) { return aiAction(CCRemoveSelf::create(cleanup)); }
        
        ______ bool             ccRemoveFromParent          (CCNodePtr n, bool cleanup = true) ;
        ______ bool             ccRemoveFromParentAndClear  (CCNodePtr & n, bool cleanup = true) ;
        inline void             ccChildrenRemoveWithTag     (CCNodePtr p, int tag)                           { for(auto n:ccChildren(p)) if (ccTag(n)==tag) ccRemoveFromParent(n); }
        inline void             ccChildrenRemove            (CCNodePtr p, std::function<bool (CCNodePtr)> f) { for(auto n:ccChildren(p)) if (f(n)) ccRemoveFromParent(n); }
        
        
        
        
        ______ CCAnimationPtr   ccAnimation             (float duration, const vector<string>& filenamesAndDurations, bool restore = false) ;
        
        inline CCAnimatePtr     aAnimate                (CCAnimationPtr p)          { return CCAnimate::create(p); }
        
        
        ______ CCSpriteBatchNodePtr ccSpriteBatchNodeCreate (string name, int elements = 0) ;
        
        
        
        
        
        inline CCTexture2DPtr   ccTexture               (string filename)                                   { return CCSprite::create(filename)->getTexture(); }
        inline CCSpritePtr      ccSprite                (string filename)                                   { return CCSprite::create(filename); }
        inline CCSpritePtr      ccSprite                (CCTexture2DPtr t)                                  { return CCSprite::createWithTexture(t); }
        inline CCSpritePtr      ccSpriteEmpty           ()                                                  { return ccSprite("image-empty.png"); }
        inline CCSpritePtr      ccSpriteEmpty           (CCSize s)                                          { auto r = ccSpriteEmpty(); ccResize(r,s); return r; }
        inline CCSpritePtr      ccFrame                 (string filename)                                   { return CCSprite::createWithSpriteFrameName(filename); }

        
        
        inline CCRendererPtr    ccRenderer              ()                                                  { return CCDirector::getInstance() -> getRenderer(); }
        inline void             ccRender                ()                                                  { ccRenderer() -> render(); }

        
        ______ CCSpritePtr      ccRender                (CCNodePtr r, CCSize screen, Color4F c, CCPoint loc);
        
        inline CCSpritePtr      ccRender                (CCNodePtr r, CCSize screen, Color4F c)             { return ccRender(r,screen,c,Vec2(screen.width/2.,screen.height/2.)); }
        inline CCSpritePtr      ccRender                (CCNodePtr r, CCSize screen, const Color3F& c)      { return ccRender(r,screen,{c.r,c.g,c.b,1}); }
        inline CCSpritePtr      ccRender                (CCNodePtr r, CCSize screen, CCPoint loc)           { return ccRender(r,screen,{1,1,1,0},loc); }
        inline CCSpritePtr      ccRender                (CCNodePtr r, CCSize screen)                        { return ccRender(r,screen,{1,1,1,0}); }
        inline CCSpritePtr      ccRender                (CCNodePtr n, Color4F c)                            { return ccRender(n,CCSize(ccWidthScaled(n),ccHeightScaled(n)),c); }
        inline CCSpritePtr      ccRender                (CCNodePtr n, const Color3F& c)                     { return ccRender(n,CCSize(ccWidthScaled(n),ccHeightScaled(n)),{c.r,c.g,c.b,1}); }
        inline CCSpritePtr      ccRender                (CCNodePtr n)                                       { return ccRender(n,CCSize(ccWidthScaled(n),ccHeightScaled(n))); } //screenGetSize()); }

        
        
        ______ CCRenderTexturePtr   ccRenderTextureWithFunction         (CCSize size, Color4F c, std::function<void ()> f);

        ______ CCSpritePtr          ccRenderWithFunction                (CCSize size, Color4F c, std::function<void ()> f);
        ______ CCSpritePtr          ccRenderWithFunctionToFile          (CCSize size, Color4F c, string filename, CCImage::Format format, std::function<void ()> f);
        ______ CCSpritePtr          ccRenderWithFunctionToFilePNG       (CCSize size, Color4F c, string filename, std::function<void ()> f);
        
        
        
        
        
        STRUCT (CCLocation) : public CCPoint
        {
            typedef std::function<CCLocation ()> Producer;
            
            inline                      CCLocation                  ()                                  {}
            
            inline  CCRatio             asRatio                     () const                            { return screenGetRatio(*this); }
            inline  CCPoint             asPoint                     () const                            { return *this; }
            inline  Producer            asProducer                  () const                            { CCLocation r = *this; return [r] { return r; }; }
            
            static  CCLocation          fromPoint                   (CCPoint p)                         { return CCLocation(p); }
            static  CCLocation          fromPoint                   (float x, float y)                  { return fromPoint(Vec2(x,y)); }
            static  CCLocation          fromRatio                   (CCRatio p)                         { return CCLocation(screenGetPoint(p)); }
            static  CCLocation          fromRatio                   (float x, float y)                  { return fromRatio(Vec2(x,y)); }
            
        private:
            
            inline                      CCLocation                  (CCPoint p)                         { x=p.x; y=p.y; }
        };
        
        
        
        
        
        

#include "tinyCocos2DCCRetain.h"
#include "tinyCocos2DCCCallBlock.h"
#include "tinyCocos2DCCTouch.h"
        
        
        
        
        
        
        void                            layerInitTouchEnabled       (Touch::CCLayerPtr layer);
        void                            layerInitTouchDisabled      (Touch::CCLayerPtr layer);
        void                            layerInit                   (CCLayerPtr layer);
        void                            sceneInit                   (CCScenePtr scene);
        
        

        
        
        inline CCActionIntervalPtr      aiHide                      (CCNodePtr p) { return aiCall([p] { p->setVisible(false); }); }
        inline CCActionIntervalPtr      aiShow                      (CCNodePtr p) { return aiCall([p] { p->setVisible(true); }); }
        
        
        inline CCActionIntervalPtr      aiOpacityTo                 (float t, CCLayerGradientPtr s, float_01 start1, float_01 end1)
        {
            float_01 start0,end0;
            return aiDuring(t,[s,start0,start1,end0,end1] (float dt) mutable {
                if (dt <= 0)
                {
                    start0  = ccOpacityStart(s);
                    end0    = ccOpacityEnd(s);
                }
                ccOpacity(s,lerp(start0,start1,dt),lerp(end0,end1,dt));
            });
        }

        inline CCActionIntervalPtr      aiOpacityTo                 (float t, CCLayerGradientPtr s, float_01 a1)
        {
            return aiOpacityTo(t,s,a1,a1);
        }
        

        inline CCActionIntervalPtr      aiOpacity                   (float t, CCLayerGradientPtr s, float_01 a0, float_01 a1)
        {
            return aiDuring(t,[s,a0,a1] (float dt) {
                ccOpacity(s,lerp(a0,a1,dt));
            });
        }
        inline CCActionIntervalPtr      aiOpacity                   (float t, CCLayerGradientPtr s, float_01 start0, float_01 start1, float_01 end0, float_01 end1)
        {
            return aiDuring(t,[s,start0,start1,end0,end1] (float dt) {
                ccOpacity(s,lerp(start0,start1,dt),lerp(end0,end1,dt));
            });
        }
        
        

        
        
        
        
        ______  CCRepeatForeverPtr      aLoop                       (CCNodePtr n, std::function<bool ()> condition, std::function<void ()> cargo, bool positive);
        ______  CCRepeatForeverPtr      aLoop                       (CCNodePtr n, std::function<bool ()> condition, bool positive);
        
        inline  CCRepeatForeverPtr      aLoopWhile                  (CCNodePtr n, std::function<bool ()> condition)                                 { return aLoop(n,condition,true); }
        inline  CCRepeatForeverPtr      aLoopWhile                  (CCNodePtr n, std::function<bool ()> condition, std::function<void ()> cargo)   { return aLoop(n,condition,cargo,true); }
        inline  CCRepeatForeverPtr      aLoopUntil                  (CCNodePtr n, std::function<bool ()> condition)                                 { return aLoop(n,condition,false); }
        inline  CCRepeatForeverPtr      aLoopUntil                  (CCNodePtr n, std::function<bool ()> condition, std::function<void ()> cargo)   { return aLoop(n,condition,cargo,false); }
        
#define ccRunOnWhile(NODE,CONDITION)                            ccRunOn(n,aLoopWhile(n,CONDITION))
#define ccRunOnUntil(NODE,CONDITION)                            ccRunOn(n,aLoopUntil(n,CONDITION))
#define ccRunDelayedOnWhile(DELAY,NODE,CONDITION)               ccRunDelayedOn(DELAY,n,aLoopWhile(n,CONDITION))
#define ccRunDelayedOnUntil(DELAY,NODE,CONDITION)               ccRunDelayedOn(DELAY,n,aLoopUntil(n,CONDITION))
#define ccRunDelayedOnWhileBlock(DELAY,NODE,CONDITION,BLOCK)    ccRunDelayedOn(DELAY,n,aLoopWhile(n,CONDITION,BLOCK))
#define ccRunDelayedOnUntilBlock(DELAY,NODE,CONDITION,BLOCK)    ccRunDelayedOn(DELAY,n,aLoopUntil(n,CONDITION,BLOCK))
        
        ______  CCRepeatForeverPtr      aWhen                       (CCNodePtr n, std::function<bool ()> condition, std::function<void ()> cargo, bool positive);
        inline  CCRepeatForeverPtr      aWhen                       (CCNodePtr n, std::function<bool ()> condition, std::function<void ()> cargo)                   { return aWhen(n,condition,cargo,true); }
        inline  CCRepeatForeverPtr      aWhenNot                    (CCNodePtr n, std::function<bool ()> condition, std::function<void ()> cargo)                   { return aWhen(n,condition,cargo,false); }
        inline  CCRepeatForeverPtr      aSignal                     (CCNodePtr n, std::function<bool ()> condition, std::function<void ()> cargo)                   { return aWhen(n,condition,cargo,true); }
        inline  CCRepeatForeverPtr      aStrike                     (CCNodePtr n, std::function<bool ()> condition, std::function<void ()> cargo)                   { return aWhen(n,condition,cargo,false); }
        
#define ccRunOnWhenOn(NODE,CONDITION,BLOCK)                     ccRunOn(n,aWhen(n,CONDITION,BLOCK))
#define ccRunOnWhenNot(NODE,CONDITION,BLOCK)                    ccRunOn(n,aWhenNot(n,CONDITION,BLOCK))
#define ccRunDelayedOnWhen(DELAY,NODE,CONDITION,BLOCK)          ccRunDelayedOn(DELAY,n,aWhen(n,CONDITION,BLOCK))
#define ccRunDelayedOnWhenNot(DELAY,NODE,CONDITION,BLOCK)       ccRunDelayedOn(DELAY,n,aWhenNot(n,CONDITION,BLOCK))
        
        
        
        namespace Geometry2D
        {
            CCPoint                     circleGetCenterFrom3Points  (CCPoint A, CCPoint B, CCPoint C);
        }
        
        
        ______ void             ccPurge                 (bool textures = true, bool frames = true);
        
        
        
        
        
    }
}
