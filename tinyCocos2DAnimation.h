    //
    //  tinyAnimation.h
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 8/8/14.
    //
    //

#pragma once

#import "tiny.h"
#import "tinyTime.h"
#import "tinyUtility.h"
#import "tinyCocos2D.h"

namespace tiny
{
    namespace Cocos2D
    {
        namespace Animation
        {
            
            using namespace tiny::Cocos2D;
            
            
            STRUCT (Steps)
            {
                virtual void    addWaitUntil    (CCNodePtr n, tiny::Time::Time time);
                virtual void    addWait         (CCNodePtr n, float duration);
                
                struct Function
                {
                    typedef std::function<void ()> Block;
                    typedef std::function<Block (Block)> Producer;
                };
                
                virtual void    init            ();
                
                virtual void    add             (Function::Producer p);
                
                    // add(StepsProducer(bee, bee->doFlyTo(Vec2(.25,.25),c) ))
#define StepsProducerOn(BOT,...)                                    [BOT]                  (std::function<void ()> c) -> std::function<void ()> { return [BOT,c] { do { __VA_ARGS__ ; } while(0); }; }
#define StepsProducerOnWith1Arg(BOT,ARG1,...)                       [BOT,ARG1]             (std::function<void ()> c) -> std::function<void ()> { return [BOT,ARG1,c] { do { __VA_ARGS__ ; } while(0); }; }
#define StepsProducerOnWith2Args(BOT,ARG1,ARG2,...)                 [BOT,ARG1,ARG2]        (std::function<void ()> c) -> std::function<void ()> { return [BOT,ARG1,ARG2,c] { do { __VA_ARGS__ ; } while(0); }; }
#define StepsProducerOnWith3Args(BOT,ARG1,ARG2,ARG3,...)            [BOT,ARG1,ARG2,ARG3]   (std::function<void ()> c) -> std::function<void ()> { return [BOT,ARG1,ARG2,ARG3,c] { do { __VA_ARGS__ ; } while(0); }; }
                
#define StepsProducer(...)                                          StepsProducerOn(this,__VA_ARGS__)
#define StepsProducerWith1Arg(ARG1,...)                             StepsProducerOnWith1Arg(this,ARG1,__VA_ARGS__)
#define StepsProducerWith2Args(ARG1,ARG2,...)                       StepsProducerOnWith2Args(this,ARG1,ARG2,__VA_ARGS__)
#define StepsProducerWith3Args(ARG1,ARG2,ARG3,...)                  StepsProducerOnWith3Args(this,ARG1,ARG2,ARG3,__VA_ARGS__)
                
#define StepsProducerOnLog(BOT,MESSAGE,...)                         [BOT]                   (std::function<void ()> c) -> std::function<void ()> { return [BOT,c] { do { tLog(MESSAGE); __VA_ARGS__ ; } while(0); }; }
#define StepsProducerOnWith1ArgLog(BOT,ARG1,MESSAGE,...)            [BOT,ARG1]              (std::function<void ()> c) -> std::function<void ()> { return [BOT,ARG1,c] { do { tLog(MESSAGE); __VA_ARGS__ ; } while(0); }; }
#define StepsProducerOnWith2ArgsLog(BOT,ARG1,ARG2,MESSAGE,...)      [BOT,ARG1,ARG2]         (std::function<void ()> c) -> std::function<void ()> { return [BOT,ARG1,ARG2,c] { do { tLog(MESSAGE); __VA_ARGS__ ; } while(0); }; }
#define StepsProducerOnWith3ArgsLog(BOT,ARG1,ARG2,ARG3,MESSAGE,...) [BOT,ARG1,ARG2,ARG3]    (std::function<void ()> c) -> std::function<void ()> { return [BOT,ARG1,ARG2,ARG3,c] { do { tLog(MESSAGE); __VA_ARGS__ ; } while(0); }; }
                
#define StepsProducerLog(MESSAGE,...)                               StepsProducerOnLog(this,MESSAGE,__VA_ARGS__)
#define StepsProducerWith1ArgLog(ARG1,MESSAGE,...)                  StepsProducerOnWith1Arg(this,ARG1,MESSAGE,__VA_ARGS__)
#define StepsProducerWith2ArgsLog(ARG1,ARG2,MESSAGE,...)            StepsProducerOnWith2Args(this,ARG1,ARG2,MESSAGE,__VA_ARGS__)
#define StepsProducerWith3ArgsLog(ARG1,ARG2,ARG3,MESSAGE,...)       StepsProducerOnWith3Args(this,ARG1,ARG2,ARG3,MESSAGE,__VA_ARGS__)
                
                virtual void    clear           ();
                
                virtual void    run             (Function::Block completion = 0);
                
            protected:
                
                struct
                {
                    std::list<Function::Producer> producers;
                } data;
            };
            
            
#if 0
            STRUCT (tv) {
                float time = 0;
                float value = 0;
                tv() {}
                tv(float t, float v) : time(t), value(v) {}
            };
            
            STRUCT (tvv) {
                float time = 0;
                float value0 = 0;
                float value1 = 0;
                tvv() {}
                tvv(float t, float v0, float v1) : time(t), value0(v0), value1(v1) {}
                inline float& operator[] (int i) {
                    switch(i) {
                        case 0: return value0;
                        case 1: return value1;
                        default:
                            tLog("bad i=" << i);
                            tAssert(0);
                            return value0;
                    }
                    
                }
            };
            
            STRUCT (tvvv) {
                float time = 0;
                float value0 = 0;
                float value1 = 0;
                float value2 = 0;
                tvvv() {}
                tvvv(float t, float v0, float v1, float v2) : time(t), value0(v0), value1(v1), value2(v2) {}
                inline float& operator[] (int i) {
                    switch(i) {
                        case 0: return value0;
                        case 1: return value1;
                        case 2: return value2;
                        default:
                            tLog("bad i=" << i);
                            tAssert(0);
                            return value0;
                    }
                    
                }
            };
            
#endif
            
        }
    }
}