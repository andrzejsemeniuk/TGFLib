    //
    //  tinyAnimation.cpp
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 8/8/14.
    //
    //

#import "tinyCocos2DAnimation.h"

namespace tiny
{
    namespace Cocos2D
    {
        namespace Animation
        {
            
            
            
            void    Steps::addWaitUntil     (CCNodePtr n, tiny::Time::Time t)
            {
                add([t,n] (Function::Block p)
                    {
                        return [t,n,p]
                        {
                            tLog("Steps::addWaitUntil: time="<<t);
#if 0
                            auto f = [t,n,p] {
                                if (tiny::Time::now() <= t)
                                {
                                    tLog("Steps::addWaitUntil: time="<<t<<", completed");
                                    if (p) p();
                                    return false;
                                }
                                return true;
                            };
                            ccRunOnWhile(n,f);
#endif
                            ccRunDelayedOn(max(0.,t-tiny::Time::now()),n,aiCall([t,p] {
                                tLog("Steps::addWaitUntil: time="<<t<<", completed");
                                if (p) p();
                            }));
                        };
                    });
            }
            
            void    Steps::addWait          (CCNodePtr n, float t)
            {
                add([t,n] (Function::Block p)
                    {
                        return [t,n,p]
                        {
                            tLog("Steps::addWait: duration="<<t);
                            ccRunOn(n,aiCall(t,[p,t] {
                                tLog("Steps::addWait: duration="<<t<<", completed");
                                if (p) p();
                            }));
                        };
                    });
            }
            
            void    Steps::init             ()
            {
                clear();
            }
            
            void    Steps::add              (Function::Producer p)
            {
                data.producers.push_front(p);
            }
            
            void    Steps::clear            ()
            {
                data.producers.clear();
            }
            
            void    Steps::run              (Function::Block completion)
            {
                Function::Block root = completion;
                
                for(auto producer:data.producers)
                {
                    root = producer(root);
                }
                
                if (root) root();
            }
            
            
            
            
        }
    }
}
