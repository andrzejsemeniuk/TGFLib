    //
    //  tinyCocos2DVariable.h
    //  productWhackyChoir
    //
    //  Created by Andrzej Semeniuk on 7/29/13.
    //
    //


#pragma once

#import "tinyCocos2D.h"

namespace tiny
{
    namespace Cocos2D
    {
        
        
        STRUCT(CCActionIntervalForVariable) : public CCActionInterval {
            
            CCActionIntervalForVariable (void) { }
            
            static CCActionIntervalForVariablePtr create(VariablePtr var, float duration, float v) ;
            
            bool init(VariablePtr var, float duration, float v) ;
            
            const char * 	description () ;
            
            virtual void update (float time) ; // time in [0,1]
            
            inline float valueFromGet() const { return valueFrom; }
            inline float valueToGet() const { return valueTo; }
            
        protected:
            
            VariablePtr variable = 0;
            bool first = true;
            float valueFrom = 0;
            float valueTo = 0;
        };
        
        
        
        
        
        
        STRUCT (CCActionInstantForVariable) : public CCActionInstant {
            
            CCActionInstantForVariable (void) { }
            
            static CCActionInstantForVariablePtr create(VariablePtr var, float v) ;
            
            bool init(VariablePtr var, float v) ;
            
            const char * description () ;
            
            virtual void update(float time) ;
            
        private:
            
            VariablePtr variable = 0;
            float valueTo = 0;
        };
        
        
        
        
        
        
        
        STRUCT(CCActionIntervalForVariableValuesWithDelay) : public CCActionInterval {
            
                // construct
            
            CCActionIntervalForVariableValuesWithDelay (void) { }
            
            static CCActionIntervalForVariableValuesWithDelayPtr create(VariablePtr var, const vector<tuple<float,float>>& values) ;
            
            bool init(VariablePtr var, const vector<tuple<float,float>>& v) ;
            
            const char * description () ;
            
            virtual void update (float time) ; // time in [0,1]
            
        protected:
            
            VariablePtr variable = 0;
            vector<tuple<float,float>> values;
            vector<float> times;
            int index = 0;
        };
        
        inline CCActionInstantPtr   aVariable   (VariablePtr var, float magnitude)                  { return CCActionInstantForVariable::create(var,magnitude); }
        inline CCActionIntervalPtr  aiVariable  (VariablePtr var, float magnitude)                  { return aiAction(CCActionInstantForVariable::create(var,magnitude)); }
        inline CCActionIntervalPtr  aiVariable  (VariablePtr v, float magnitude, float duration)    { return CCActionIntervalForVariable::create(v,duration,magnitude); }
        
        inline vector<CCActionIntervalPtr> aiVariables (VariablesPtr v, float duration, const vector<float>& values) {
            tAssert(v and v -> size() <= values.size());
            vector<CCActionIntervalPtr> r;
            r.reserve(values.size());
            int index=0;
            for(float value:values) {
                r.push_back(aiVariable((*v)[index++].ptrGet(),value,duration));
            }
            return r;
        }
        
        inline CCActionIntervalPtr aiVariables (VariablesPtr v, const vector<float>& values, float duration = 0) {
            auto r = aiVariables(v,duration,values);
            return aSpawn(r);
        }
        
        
        
        inline CCActionIntervalPtr aVariableSequence (VariablePtr v, const vector<tuple<float,float>>& arrayValueDelay) {
#if 0
            vector<CCActionIntervalPtr> actions;
            actions.reserve(arrayValueDelay.size());
            for(const auto& e:arrayValueDelay) {
                actions.push_back(aiVariable(v,tupleGet0(e),tupleGet1(e)));
            }
            return aSequence(actions);
#else
            return CCActionIntervalForVariableValuesWithDelay::create(v,arrayValueDelay);
#endif
        }
        
        
        
        inline CCActionIntervalPtr aVariableSequence (VariablePtr v, const vector<tuple<float,float,float>>& arrayValueDurationDelay) {
            vector<CCActionIntervalPtr> actions;
            actions.reserve(arrayValueDurationDelay.size());
            for(const auto& e:arrayValueDurationDelay) {
                actions.push_back(aiDelay(tupleGet2(e),aiVariable(v,tupleGet0(e),tupleGet1(e)))); // value,duration,delay
            }
            return aSequence(actions);
        }
        
        
        
        
        
        
        
        namespace Variable
        {
            STRUCT (Manager) : public tiny::Variable::Manager
            {
                inline void variablesAddUpdateForRotation          (CCSpritePtr s, tiny::Variable& v)                                                                          { auto V = v.ptrGet(); variablesAddUpdate(v, [this,s,V] (float dt) { ccRotation(s, V->valueGet());  }); }
                inline void variablesAddUpdateForOpacity           (CCSpritePtr s, tiny::Variable& v)                                                                          { auto V = v.ptrGet(); variablesAddUpdate(v, [this,s,V] (float dt) { ccOpacity(s, V->valueGet());  }); }
                inline void variablesAddUpdateForColor             (CCSpritePtr s,
                                                                    tiny::Variable& r,
                                                                    tiny::Variable& g,
                                                                    tiny::Variable& b)                                                                                         { auto R = r.ptrGet(); auto G = g.ptrGet(); auto B = b.ptrGet(); variablesAddUpdate(r,g,b, [this,s,R,G,B] (float dt) { ccColor(s,ccc3f(R->valueGet(),G->valueGet(),B->valueGet()));  }); }
                inline void variablesAddUpdateForColor             (CCSpritePtr s,
                                                                    tiny::Variable& r,
                                                                    tiny::Variable& g,
                                                                    tiny::Variable& b,
                                                                    tiny::Variable& a)                                                                                         { auto R = r.ptrGet(); auto G = g.ptrGet(); auto B = b.ptrGet(); auto A = a.ptrGet(); variablesAddUpdate(r,g,b,a, [this,s,R,G,B,A] (float dt) { ccColor(s,ccc3f(R->valueGet(),G->valueGet(),B->valueGet())); ccOpacity(s,A->valueGet());  }); }
                inline void variablesAddUpdateForScale             (CCSpritePtr s, tiny::Variable& v)                                                                          { auto V = v.ptrGet(); variablesAddUpdate(v, [this,s,V] (float dt) { s -> setScale(V->valueGet()); }); }
                inline void variablesAddUpdateForScaleX            (CCSpritePtr s, tiny::Variable& v)                                                                          { auto V = v.ptrGet(); variablesAddUpdate(v, [this,s,V] (float dt) { s -> setScaleX(V->valueGet()); }); }
                inline void variablesAddUpdateForScaleY            (CCSpritePtr s, tiny::Variable& v)                                                                          { auto V = v.ptrGet(); variablesAddUpdate(v, [this,s,V] (float dt) { s -> setScaleY(V->valueGet()); }); }
                inline void variablesAddUpdateForScaleXY           (CCSpritePtr s, tiny::Variable& x, tiny::Variable& y)                                                       { auto X = x.ptrGet(); auto Y = y.ptrGet(); variablesAddUpdate(x, y, [this,s,X,Y] (float dt) { s -> setScaleX(X->valueGet()); s -> setScaleY(Y->valueGet()); }); }
                inline void variablesAddUpdateForSkewX             (CCSpritePtr s, tiny::Variable& v)                                                                          { auto V = v.ptrGet(); variablesAddUpdate(v, [this,s,V] (float dt) { s -> setSkewX(V->valueGet()); }); }
                inline void variablesAddUpdateForSkewY             (CCSpritePtr s, tiny::Variable& v)                                                                          { auto V = v.ptrGet(); variablesAddUpdate(v, [this,s,V] (float dt) { s -> setSkewY(V->valueGet()); }); }
                inline void variablesAddUpdateForSkewXY            (CCSpritePtr s, tiny::Variable& x, tiny::Variable& y)                                                       { auto X = x.ptrGet(); auto Y = y.ptrGet(); variablesAddUpdate(x, y, [this,s,X,Y] (float dt) { s -> setSkewX(X->valueGet()); s -> setSkewY(Y->valueGet()); }); }
                inline void variablesAddUpdateForAlignAnchorTo     (CCSpritePtr s, tiny::Variable& x, tiny::Variable& y)                                                       { auto X = x.ptrGet(); auto Y = y.ptrGet(); variablesAddUpdate(x, y, [this,s,X,Y] (float dt) { auto a = s -> getAnchorPoint(); align(s,a.x,a.y,X->valueGet(),Y->valueGet()); }); }
                inline void variablesAddUpdateForAlignCenterTo     (CCSpritePtr s, tiny::Variable& x, tiny::Variable& y)                                                       { auto X = x.ptrGet(); auto Y = y.ptrGet(); variablesAddUpdate(x, y, [this,s,X,Y] (float dt) { align(s,.5,.5,X->valueGet(),Y->valueGet()); }); }
                inline void variablesAddUpdateForAlignToCenter     (CCSpritePtr s, tiny::Variable& x, tiny::Variable& y)                                                       { auto X = x.ptrGet(); auto Y = y.ptrGet(); variablesAddUpdate(x, y, [this,s,X,Y] (float dt) { align(s,X->valueGet(),Y->valueGet(),.5,.5); }); }
                inline void variablesAddUpdateForAlignTo           (CCSpritePtr s, tiny::Variable& x, tiny::Variable& y, float tox, float toy)                                 { auto X = x.ptrGet(); auto Y = y.ptrGet(); variablesAddUpdate(x, y, [this,s,X,Y,tox,toy] (float dt) { align(s,X->valueGet(),Y->valueGet(),tox,toy); }); }
                inline void variablesAddUpdateForAlignFrom         (CCSpritePtr s, float fromy, float fromx, tiny::Variable& x, tiny::Variable& y)                             { auto X = x.ptrGet(); auto Y = y.ptrGet(); variablesAddUpdate(x, y, [this,s,fromx,fromy,X,Y] (float dt) { align(s,fromx,fromy,X->valueGet(),Y->valueGet()); }); }
                inline void variablesAddUpdateForAlign             (CCSpritePtr s, tiny::Variable& fromx, tiny::Variable& fromy, tiny::Variable& tox, tiny::Variable& toy)     { auto FROMX = fromx.ptrGet(); auto FROMY = fromy.ptrGet(); auto TOX = tox.ptrGet(); auto TOY = toy.ptrGet(); variablesAddUpdate(fromx, fromy, tox, toy, [this,s,FROMX,FROMY,TOX,TOY] (float dt) { align(s,FROMX->valueGet(),FROMY->valueGet(),TOX->valueGet(),TOY->valueGet()); }); }
                inline void variablesAddUpdateForPositionX         (CCSpritePtr s, tiny::Variable& v)                                                                          { auto V = v.ptrGet(); variablesAddUpdate(v, [this,s,V] (float dt) { s -> setPosition(Vec2(V->valueGet(),s -> getPosition().y)); }); }
                inline void variablesAddUpdateForPositionY         (CCSpritePtr s, tiny::Variable& v)                                                                          { auto V = v.ptrGet(); variablesAddUpdate(v, [this,s,V] (float dt) { s -> setPosition(Vec2(s -> getPosition().x,V->valueGet())); }); }
                inline void variablesAddUpdateForPositionXY        (CCSpritePtr s, tiny::Variable& x, tiny::Variable& y)                                                       { auto X = x.ptrGet(); auto Y = y.ptrGet(); variablesAddUpdate(x, y, [this,s,X,Y] (float dt) { s -> setPosition(Vec2(X->valueGet(),Y->valueGet())); }); }
            };
        }
        
        
        
        
        
    }
}
