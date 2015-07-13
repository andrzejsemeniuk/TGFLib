

#import "tinyCocos2DVariable.h"

namespace tiny
{
    namespace Cocos2D
    {
        
        
        
            // 8< -----------------------------------------------------------------
        
        
        
        
        
        
        
        CCActionIntervalForVariablePtr CCActionIntervalForVariable::create(VariablePtr var, float duration, float v) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCActionIntervalForVariable,var,duration,v);
        }
        
        bool CCActionIntervalForVariable::init(VariablePtr var, float duration, float v)
        {
            if (CCActionInterval::initWithDuration(duration))
            {
                first = true;
                variable = var;
                valueTo = v;
                return true;
            }
            
            return false;
        }
        
        
        const char * 	CCActionIntervalForVariable::description () {
            return "CCActionIntervalForVariable";
        }
        
        
        void CCActionIntervalForVariable::update (float time) { // time in [0,1]
            if (first) {
                first = false;
                valueFrom = variable -> valueGet();
            }
            auto v = Math::lerp(valueFrom,valueTo,time);
            variable -> valueSet(v);
        }
        
        
        
        
        
        
        
        
        CCActionInstantForVariablePtr CCActionInstantForVariable::create(VariablePtr var, float v) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCActionInstantForVariable,var,v);
        }
        
        bool CCActionInstantForVariable::init(VariablePtr var, float v)
        {
                // NOTE: DO NOT RETAIN
            variable = var;
            valueTo = v;
            return true;
        }
        
        const char * CCActionInstantForVariable::description () {
            return "CCActionInstantForVariable";
        }
        
        void CCActionInstantForVariable::update(float time) {
            CC_UNUSED_PARAM(time);
            variable -> valueSet(valueTo);
        }
        
        
        
        
        
        
        
        
        
        
        
        CCActionIntervalForVariableValuesWithDelayPtr CCActionIntervalForVariableValuesWithDelay::create(VariablePtr var, const vector<tuple<float,float>>& values) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCActionIntervalForVariableValuesWithDelay,var,values);
        }
        
        bool CCActionIntervalForVariableValuesWithDelay::init(VariablePtr var, const vector<tuple<float,float>>& v)
        {
            float duration = 0;
            for(auto i:v) {
                duration += tupleGet1(i);
            }
            
            if (CCActionInterval::initWithDuration(duration))
            {
                variable = var;
                values = v;
                times.reserve(v.size());
                float time = 0;
                loopUpTo(i,v.size()) {
                    time = times[i] = time + tupleGet1(v[i])/duration;
                }
                return true;
            }
            
            return false;
        }
        
        const char * CCActionIntervalForVariableValuesWithDelay::description () {
            return "CCActionIntervalForVariableValuesWithDelay";
        }
        
        
        void CCActionIntervalForVariableValuesWithDelay::update (float time) { // time in [0,1]
            while(index < values.size() and times[index] <= time) {
                variable -> valueSet(tupleGet0(values[index]));
                index++;
            }
        }
        
        
        
        
        
        
        namespace Variable
        {
        }
        
        
        
        
    }
}