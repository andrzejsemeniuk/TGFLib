    //
    //  CommonCocos2D.cpp
    //  productWhackyChoir
    //
    //  Created by andrzej semeniuk on 10/28/12.
    //
    //

#include "tinyCocos2D.h"

#include <functional>

#include <algorithm>

#include "tinyMath.h"

#include "tinyApplication.h"

#include "tinyUtility.h"

#include "tinyCocos2Dgl.h"

#include <strstream>




namespace tiny {
    
    namespace Cocos2D {
        
        
        
        
        
        using namespace cocos2d;
        
        using namespace tiny;
        using namespace tiny::Math;
        
        
        
        
        
        

        
        
        
        
        std::string to_string   (CCPoint p)    { stringstream o; float x = p.x; float y = p.y; o << '(' << x << ',' << y << ')'; return o.str(); }
        std::string to_string   (CCSize p)     { stringstream o; float w = p.width; float h = p.height; o << '(' << w << 'x' << h << ')'; return o.str(); }
        std::string to_string   (CCRect p)     { stringstream o; o << '[' << to_string(p.origin) << '+' << to_string(p.size) << ']'; return o.str(); }
        
        std::ostream& operator << (std::ostream& o, CCPoint p)    { return o << to_string(p); }
        std::ostream& operator << (std::ostream& o, CCSize p)     { return o << to_string(p); }
        std::ostream& operator << (std::ostream& o, CCRect p)     { return o << to_string(p); }
        
        std::ostream& operator << (std::ostream& o, CCNodePtr p) {
            if (p)
                return o<<"("<<to_string(p->getPosition())<<")";
            return o<<"(CCNodePtr=0)";
#if 0
            return o
            << "node={"
            << "\n ignore-anchor?=" << p -> isIgnoreAnchorPointForPosition()
            << "\n anchor        =" << p -> getAnchorPoint()
            << "\n anchor-points =" << p -> getAnchorPointInPoints()
            << "\n position      =" << p -> getPosition()
            << "\n content-size  =" << p -> getContentSize()
            << "\n bbox          =" << p -> boundingBox()
            << "\n}";
#endif
        }
        
        std::ostream& operator << (std::ostream& o, CRef(VectorOfPoints) points) {
            o << '(';
            bool first = true;
            for(autoCRef p:points) {
                if (not first)
                    o << ',';
                o << p;
                first = false;
            }
            o << ')';
            return o;
        }

        std::ostream& operator << (std::ostream& o, const Color3F & p)      { return o << '(' << tiny::to_string(p.r) << ',' << tiny::to_string(p.g) << ',' << tiny::to_string(p.b) << ')'; }
        std::ostream& operator << (std::ostream& o, const Color3B & p)      { return o << '(' << tiny::to_string(p.r) << ',' << tiny::to_string(p.g) << ',' << tiny::to_string(p.b) << ')'; }
        std::ostream& operator << (std::ostream& o, const Color4F & p)      { return o << '(' << tiny::to_string(p.r) << ',' << tiny::to_string(p.g) << ',' << tiny::to_string(p.b) << ',' << tiny::to_string(p.a) << ')'; }
        std::ostream& operator << (std::ostream& o, const Color4B & p)      { return o << '(' << tiny::to_string(p.r) << ',' << tiny::to_string(p.g) << ',' << tiny::to_string(p.b) << ',' << tiny::to_string(p.a) << ')'; }

        std::ostream& operator << (std::ostream& o, const HSV & p)          { return o << '(' << tiny::to_string(p.h) << ',' << tiny::to_string(p.s) << ',' << tiny::to_string(p.v) << ')'; }
        std::ostream& operator << (std::ostream& o, const HSVA & p)         { return o << '(' << tiny::to_string(p.h) << ',' << tiny::to_string(p.s) << ',' << tiny::to_string(p.v) << ',' << tiny::to_string(p.a) << ')'; }

        string      ccc3bstring (Color3B c)                                 { return tiny::to_string((int)c.r) + ',' + tiny::to_string((int)c.g) + ',' + tiny::to_string((int)c.b); }
        string      ccc3fstring (Color3F c)                                 { return tiny::to_string((float)c.r) + ',' + tiny::to_string((float)c.g) + ',' + tiny::to_string((float)c.b); }

        Color3B     ccc3bstring (string s)                                  { auto rgb = to_vector(split(s,",")); return ccc3(to_int(rgb[0]),to_int(rgb[1]),to_int(rgb[2])); }
        Color3F     ccc3fstring (string s)                                  { auto rgb = to_vector(split(s,",")); return ccc3f(to_float(rgb[0]),to_float(rgb[1]),to_float(rgb[2])); }
       
        
        
        
        void print(const char* n, CCNodePtr a)
        {
            std::cout << n << " " << a << std::endl;
            std::cout << n << ".anchor=" << anchor(a) << std::endl;
            std::cout << n << ".origin=" << origin(a) << std::endl;
            std::cout << n << ".origin_a=" << origin_a(a) << std::endl;
            std::cout << n << ".anchor_o=" << anchor_o(a) << std::endl;
            std::cout << n << ".oa=" << oa(a) << std::endl;
            std::cout << n << ".ao=" << ao(a) << std::endl;
            std::cout << n << ".position=" << ccPosition(a) << std::endl;
            
            std::cout << n << ".pa2pn(0,0)=" << pa2pn(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".pn2pa(0,0)=" << pn2pa(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".pn2pw(0,0)=" << pn2pw(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".pw2pn(0,0)=" << pw2pn(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".pw2pa(0,0)=" << pw2pa(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".pa2pw(0,0)=" << pa2pw(a,Vec2(0,0)) << std::endl;
            
            std::cout << n << ".rn2pw(0,0)=" << rn2pw(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".rn2pw(-1,-1)=" << rn2pw(a,Vec2(-1,-1)) << std::endl;
            std::cout << n << ".rn2pw(1,1)=" << rn2pw(a,Vec2(1,1)) << std::endl;
            std::cout << n << ".rn2pw(.5,.5)=" << rn2pw(a,Vec2(.5,.5)) << std::endl;
            
            std::cout << n << ".rn2pn(0,0)=" << rn2pn(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".rn2pn(-1,-1)=" << rn2pn(a,Vec2(-1,-1)) << std::endl;
            std::cout << n << ".rn2pn(1,1)=" << rn2pn(a,Vec2(1,1)) << std::endl;
            std::cout << n << ".rn2pn(.5,.5)=" << rn2pn(a,Vec2(.5,.5)) << std::endl;
            
            std::cout << n << ".rn2pa(0,0)=" << rn2pa(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".rn2pa(-1,-1)=" << rn2pa(a,Vec2(-1,-1)) << std::endl;
            std::cout << n << ".rn2pa(1,1)=" << rn2pa(a,Vec2(1,1)) << std::endl;
            std::cout << n << ".rn2pa(.5,.5)=" << rn2pa(a,Vec2(.5,.5)) << std::endl;
            
            std::cout << n << ".ra2pw(0,0)=" << ra2pw(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".ra2pw(-1,-1)=" << ra2pw(a,Vec2(-1,-1)) << std::endl;
            std::cout << n << ".ra2pw(1,1)=" << ra2pw(a,Vec2(1,1)) << std::endl;
            std::cout << n << ".ra2pw(.5,.5)=" << ra2pw(a,Vec2(.5,.5)) << std::endl;
            
            std::cout << n << ".ra2pn(0,0)=" << ra2pn(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".ra2pn(-1,-1)=" << ra2pn(a,Vec2(-1,-1)) << std::endl;
            std::cout << n << ".ra2pn(1,1)=" << ra2pn(a,Vec2(1,1)) << std::endl;
            std::cout << n << ".ra2pn(.5,.5)=" << ra2pn(a,Vec2(.5,.5)) << std::endl;
            
            std::cout << n << ".ra2pa(0,0)=" << ra2pa(a,Vec2(0,0)) << std::endl;
            std::cout << n << ".ra2pa(-1,-1)=" << ra2pa(a,Vec2(-1,-1)) << std::endl;
            std::cout << n << ".ra2pa(1,1)=" << ra2pa(a,Vec2(1,1)) << std::endl;
            std::cout << n << ".ra2pa(.5,.5)=" << ra2pa(a,Vec2(.5,.5)) << std::endl;
        }
        
            //        void debugWithShadow(CCNodePtr n);
        
        
        string ccPrintSprite(CCSpritePtr p, string n) {
            stringstream s;
            if (n.length())
                s<<n<<'=';
            s<<"{";
            s<<"c="<<ccc3bstring(p->getColor());
            s<<'|';
            s<<"o="<<((int)p->getOpacity());
            s<<'|';
            s<<"s=("<<p->getScaleX()<<','<<p->getScaleY()<<')';
            s<<'|';
            s<<"r="<<p->getRotation();
            s<<"}";
            return s.str();
        }

        
        void test() {
            auto ASSERT = [] (int flag, const char* msg) {
                if (!flag) {
                    std::cerr << "!ASSERT: " << msg << std::endl;
                        //                    exit(0);
                }
            };
            
            auto EQUAL = [] (float v, float test, const char* msg) {
                bool flag = (v <= (test+FLT_EPSILON) && (v >= (test-FLT_EPSILON)));
                if (flag) {
                    std::cerr << " EQUAL: (" << v << " == " << test << ") " << msg << std::endl;
                        //                    exit(0);
                }
                else {
                    std::cerr << "!EQUAL: (" << v << " <> " << test << ") " << msg << std::endl;
                        //                    exit(0);
                }
            };
            
            if (true)
            {
                CCNodePtr a = CCNode::create();
                CCNodePtr b = CCNode::create();
                
                a -> setContentSize(CCSize(300,400));
                a -> setAnchorPoint(Vec2(.5,.5));
                a -> addChild(b);
                
                b -> setContentSize(CCSize(200,100));
                b -> setAnchorPoint(Vec2(.5,.5));
                b -> setPosition(Vec2(33,70));
                
                Prnrn(b,.5,.5,.5,.5);
                Prnrn(b,0,0,1,1);
                
                print("a",a);
                print("b",b);
            }
            
            if (false)
            {
                CCNodePtr a = CCNode::create();
                a -> setContentSize(CCSize(300,400));
                ASSERT(a!=0,"1");
                CCNodePtr b = CCNode::create();
                b -> setContentSize(CCSize(200,100));
                ASSERT(b!=0,"2");
                
                a -> setAnchorPoint(Vec2(.5,.5));
                b -> setAnchorPoint(Vec2(1,1));
                a -> addChild(b);
                
                print("a",a);
                b -> setPosition(Vec2(50,50));
                print("b",b);
                
                EQUAL(pw2pn(b,pn2pw(b,anchor_o(b))).x,anchor_o(b).x,"pw2pn(pn2pw)).x");
                EQUAL(pw2pn(b,pn2pw(b,anchor_o(b))).y,anchor_o(b).y,"pw2pn(pn2pw)).y");
                
                EQUAL(pw2pa(b,pa2pw(b,origin_a(b))).x,origin_a(b).x,"pw2pa(pa2pw)).x");
                EQUAL(pw2pa(b,pa2pw(b,origin_a(b))).y,origin_a(b).y,"pw2pa(pa2pw)).y");
                
                EQUAL(pn2pw(b,Vec2(0,0)).x,ccPosition(b).x-r2x(b,1),"pn2pw(0,0).x");
                EQUAL(pn2pw(b,Vec2(0,0)).y,50-100,"pn2pw(0,0).y");
                EQUAL(pn2pw(b,Vec2(100,0)).x,50-200+100,"pn2pw(100,0).x");
                EQUAL(pn2pw(b,Vec2(0,100)).y,50-100+100,"pn2pw(0,100).y");
                
                EQUAL(pw2pn(b,Vec2(0,0)).x,50-200,"pw2pn(0,0).x");
                EQUAL(pw2pn(b,Vec2(0,0)).y,50-100,"pw2pn(0,0).y");
                EQUAL(pw2pn(b,Vec2(100,0)).x,50-100,"pw2pn(100,0).x");
                EQUAL(pw2pn(b,Vec2(0,100)).y,50-100,"pw2pn(0,100).y");
                
                EQUAL(pa2pw(b,Vec2(0,0)).x,50,"pa2pw(0,0).x");
                EQUAL(pa2pw(b,Vec2(0,0)).y,50,"pa2pw(0,0).y");
                EQUAL(pa2pw(b,Vec2(100,0)).x,50+100,"pa2pw(100,0).x");
                EQUAL(pa2pw(b,Vec2(0,100)).y,50+100,"pa2pw(0,100).y");
                
                EQUAL(pw2pa(b,Vec2(0,0)).x,-50,"pw2pa(0,0).x");
                EQUAL(pw2pa(b,Vec2(0,0)).y,-50,"pw2pa(0,0).y");
                EQUAL(pw2pa(b,Vec2(100,0)).x,50,"pw2pa(100,0).x");
                EQUAL(pw2pa(b,Vec2(0,100)).y,50,"pw2pa(0,100).y");
                
                EQUAL(rn2pw(b,Vec2(0,0)).x,50-200,"rn2pw(.5).x");
                EQUAL(rn2pw(b,Vec2(0,0)).y,50-100,"rn2pw(.5).y");
                EQUAL(rn2pw(b,Vec2(.5,.5)).x,50-200+100,"rn2pw(.5).x");
                EQUAL(rn2pw(b,Vec2(.5,.5)).y,50-100+100,"rn2pw(.5).y");
                
                EQUAL(ra2pw(b,Vec2(0,0)).x,-50,"ra2pw(.5).x");
                EQUAL(ra2pw(b,Vec2(0,0)).y,-50,"ra2pw(.5).y");
                EQUAL(ra2pw(b,Vec2(.5,.5)).x,50-200+100,"ra2pw(.5).x");
                EQUAL(ra2pw(b,Vec2(.5,.5)).y,50-100+100,"ra2pw(.5).y");
                
                EQUAL(rn2pn(b,Vec2(.5,.5)).x,.5*ccWidthScaled(b),"rn2pn(.5).x");
                EQUAL(rn2pn(b,Vec2(.5,.5)).y,.5*ccHeightScaled(b),"rn2pn(.5).y");
                
                exit(1);
            }
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        namespace io
        {
            
            bool saveToFilePNG (CCNodePtr sprite, string f)
            {
                if (sprite)
                {
                    CCPoint p       = ccPosition(sprite);
                    CCPoint a       = ccAnchor  (sprite);
                    CCSize SIZE     = bbox      (sprite).size; //p2s(ccSize(sprite));
                    
                    if (1)
                    {
                        tDebug(         std::string fullpath = CCFileUtils::getInstance()->getWritablePath() + f; tLog( "io::saveToFilePNG: "<<f<<"="<<fullpath ); );

                        auto r = ccRenderWithFunctionToFilePNG(SIZE,{1,1,1,0},f,[sprite,SIZE,a,p]
                        {
                            sprite -> setAnchorPoint    (Vec2(.5,.5));
                            sprite -> setPosition       (s2p(SIZE/2.));
                            sprite -> visit             ();
                            sprite -> setAnchorPoint    (a);
                            sprite -> setPosition       (p);
                        });
                    }
                    else
                    {
                        CCRenderTexturePtr t = CCRenderTexture::create(SIZE.width,SIZE.height,CCTexture2D::PixelFormat::RGBA8888);
                        t -> beginWithClear(.7, .7, .7, 0);
                        sprite -> setAnchorPoint(Vec2(.5,.5));
                        sprite -> setPosition(s2p(SIZE/2.));
                        sprite -> visit();
                        sprite -> setAnchorPoint(a);
                        sprite -> setPosition(p);
                        t -> end();
                        tDebug(         std::string fullpath = CCFileUtils::getInstance()->getWritablePath() + f; tLog( "io::saveToFilePNG: "<<f<<"="<<fullpath ); );
                        t -> saveToFile(f,CCImage::Format::PNG);
                    }
                    return true;
                }
                return false;
            }
            
            
            
            
            CCSpritePtr readFromFilePNG (string filenameInDocumentsDirectory)
            {
//                NSString *documentDirectory = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
//                NSString *logoImagePath = [NSString stringWithFormat:@"%@/%@", documentDirectory, @"image0.png"];
//                UIImage *logoImage = [UIImage imageWithContentsOfFile:logoImagePath];
//                    // Then use spriteWithCGImage
//                CCSprite *logoSprite = [CCSprite spriteWithCGImage:logoImage.CGImage key:nil];
                
                

                    //auto path = tiny::Application::IO::pathInDocumentsFolder(filenameInDocumentsDirectory);
                
                    // NOTE: FileUtils::getInstance()->getWritablePath() IS USED IN CCRenderTexture::saveToFile()
                
                auto path = FileUtils::getInstance()->getWritablePath() + filenameInDocumentsDirectory;
                
                tLog("readFromFilePNG: writable path="<<path);
                
                
                    // NOTE: FileUtils::getInstance()->fullPathForFilename() IS USED IN CCTextureCache::addImage()
                
                if (1)
                {
                    path = FileUtils::getInstance()->fullPathForFilename(path);
                
                    tLog("readFromFilePNG: full path="<<path);
                }
                
                    // /var/mobile/Containers/Data/Application/35047B1D-48BE-4912-8DE4-FE7E8BEE8C13/Documents/tmp-image-render.png
                    // /var/mobile/Containers/Data/Application/35047B1D-48BE-4912-8DE4-FE7E8BEE8C13/Documents/tmp-image-render.png
                
                if (1)
                {
                    tLog("document-exists: filename="<<tiny::Application::IO::documentExistsWithFilename(filenameInDocumentsDirectory));
                    tLog("document-exists: path="<<tiny::Application::IO::documentExistsWithFilename(path));
                }
                auto r = ccSprite(path);
                
                return r;
            }
            
            
            
        }
        
        
        
        
        
        
        
        
        int              pickDifferent  (unsigned long size, unsigned long n)
        {
            tAssert(1 < size);
            
            int n0 = n;
            
            while(n0==n)
            {
                n = pick(size);
            }
            
            return n;
        }

        
        
        
        
        
        
        
        
        
        
        Degrees::Degrees (CCAngle p) { value=p.asDegrees(); }
        Degrees::Degrees (Radians p) { value=p.asDegrees(); }
        
        CCAngle::CCAngle (Degrees p) { value=p.asCCAngle(); }
        CCAngle::CCAngle (Radians p) { value=p.asCCAngle(); }
        
        Radians::Radians (CCAngle p) { value=p.asRadians(); }
        Radians::Radians (Degrees p) { value=p.asRadians(); }
        
        
        Radians          Degrees::asRadians                   () const            { return ccToRadians(value); }
        CCAngle          Degrees::asCCAngle                   () const            { return - value; }

        Radians          CCAngle::asRadians                   () const            { return - ccToRadians(value); }
        Degrees          CCAngle::asDegrees                   () const            { return - value; }

        Degrees          Radians::asDegrees                   () const            { return ccToDegrees(value); }
        CCAngle          Radians::asCCAngle                   () const            { return - ccToDegrees(value); }

        
        
        
        const Degrees    Degrees::Zero         = Degrees(0);
        const Degrees    Degrees::HalfCircle   = Degrees(90);
        const Degrees    Degrees::Circle       = Degrees(180);

        const CCAngle    CCAngle::Zero         = CCAngle(0);
        const CCAngle    CCAngle::HalfCircle   = CCAngle(90);
        const CCAngle    CCAngle::Circle       = CCAngle(180);
        
        const Radians    Radians::Zero         = Radians(0);
        const Radians    Radians::HalfCircle   = Radians(tiny::Math::Pi);
        const Radians    Radians::Circle       = Radians(tiny::Math::TwoPi);
        
        const Angle      Angle::Zero           = Degrees(0);
        const Angle      Angle::HalfCircle     = Degrees(90);
        const Angle      Angle::Circle         = Degrees(180);
        
        
        
        
        bool             Degrees::isDirectionDifferent        (DegreesCRef p, float _delta) const
        {
                            // angle = 180 - fabs(fabs(a1-a2)%360 - 180);
                            //return different(0, 180.f - fabs(fmod(fabs(value-b.value),360.f) - 180.f), delta);
            return different(0.f, difference(p), _delta);
        }

        bool             CCAngle::isDirectionDifferent        (CCAngleCRef p, float _delta) const
        {
                //return different(0, 180.f - fabs(fmod(fabs(value-b.value),360.f) - 180.f), delta);
            return different(0.f, difference(p), _delta);
        }
        
        bool             Radians::isDirectionDifferent        (RadiansCRef p, float _delta) const
        {
                //return different(0, tiny::Math::Angle::Pi - fabs(fmod(fabs(value-b.value),tiny::Math::twopi) - tiny::Math::Angle::Pi), delta);
            return different(0.f, difference(p), _delta);
        }
        
        bool             Angle::isDirectionDifferent          (AngleCRef p, float _delta) const
        {
                //return different(0, tiny::Math::Angle::Pi - fabs(fmod(fabs(value-b.value),tiny::Math::twopi) - tiny::Math::Angle::Pi), delta);
            return different(0.f, difference(p), _delta);
        }
        

        
        
        std::vector<Degrees> Degrees::generateFromToBy (double from, double to, double delta)
        {
            delta = fabs(delta);
            
            std_vectorWithCapacity(r,Degrees,fabs(to-from)/delta+1);
            
            if (from<to)
                for(;from<to;from+=delta) r.push_back(from);
            else
                for(;to<from;from+=delta) r.push_back(from);
            
            return r;
        };
        
        
        std::vector<CCAngle> CCAngle::generateFromToBy (double from, double to, double delta)
        {
            delta = fabs(delta);
            
            std_vectorWithCapacity(r,CCAngle,fabs(to-from)/delta+1);
            
            if (from<to)
                for(;from<to;from+=delta) r.push_back(from);
            else
                for(;to<from;from+=delta) r.push_back(from);
            
            return r;
        };
        
        
        std::vector<Radians> Radians::generateFromToBy (double from, double to, double delta)
        {
            delta = fabs(delta);
            
            std_vectorWithCapacity(r,Radians,fabs(to-from)/fabs(delta)+1);
            
            if (from<to)
                for(;from<to;from+=delta) r.push_back(from);
            else
                for(;to<from;from+=delta) r.push_back(from);
            
            return r;
        };
        
        
        
        std::vector<Angle> Angle::generateFromToBy (Angle from, Angle to, Angle delta)
        {
            std_vectorWithCapacity(r,Angle,fabs(to.asRadians()-from.asRadians())/fabs(delta.asRadians())+1);
            
            float f = from.asRadians();
            float d = delta.asRadians();
            float t = to.asRadians();
            
            if (f<t)
                for(;f<t;f+=d) r.push_back(Radians(f));
            else
                for(;t<f;f+=d) r.push_back(Radians(f));
            
            return r;
        };
        

        
        
        
        std::vector<CCAngle> CCAngle::generateToBy (double to, double by)
        {
            return generateFromToBy(Zero,to,by);
        };
        
        std::vector<Degrees> Degrees::generateToBy (double to, double by)
        {
            return generateFromToBy(Zero,to,by);
        };
        
        std::vector<Radians> Radians::generateToBy (double to, double by)
        {
            return generateFromToBy(Zero,to,by);
        };
        
        std::vector<Angle> Angle::generateToBy (Angle to, Angle by)
        {
            return generateFromToBy(Zero,to,by);
        };
        

        
        
        
        std::vector<CCAngle> CCAngle::generateCountBy (int count, double by)
        {
            return generateCountByFrom(count,by,Zero);
        };
        
        std::vector<Degrees> Degrees::generateCountBy (int count, double by)
        {
            return generateCountByFrom(count,by,Zero);
        };
        
        std::vector<Radians> Radians::generateCountBy (int count, double by)
        {
            return generateCountByFrom(count,by,Zero);
        };
        
        std::vector<Angle> Angle::generateCountBy (int count, Angle by)
        {
            return generateCountByFrom(count,by,Zero);
        };
        

        
        
        
        
        
        std::vector<CCAngle> CCAngle::generateCountByFrom (int count, double by, double from)
        {
            std_vectorWithCapacity(r,CCAngle,count);
            
            loopUpTo(i,count)
            {
                r.push_back(from);
                from += by;
            }
            
            return r;
        };
        
        std::vector<Degrees> Degrees::generateCountByFrom (int count, double by, double from)
        {
            std_vectorWithCapacity(r,Degrees,count);
            
            loopUpTo(i,count)
            {
                r.push_back(from);
                from += by;
            }
            
            return r;
        };
        
        std::vector<Radians> Radians::generateCountByFrom (int count, double by, double from)
        {
            std_vectorWithCapacity(r,Radians,count);
            
            loopUpTo(i,count)
            {
                r.push_back(from);
                from += by;
            }
            
            return r;
        };
        
        std::vector<Angle> Angle::generateCountByFrom (int count, Angle by, Angle from)
        {
            std_vectorWithCapacity(r,Angle,count);
            
            loopUpTo(i,count)
            {
                r.push_back(from);
                from += by;
            }
            
            return r;
        };
        
        
        
        
        
        std::vector<CCAngle> CCAngle::generateCircleBy (double by)
        {
            return generateFromToBy(Zero,360,by);
        };
        
        std::vector<Degrees> Degrees::generateCircleBy (double by)
        {
            return generateFromToBy(Zero,Circle,by);
        };
        
        std::vector<Radians> Radians::generateCircleBy (double by)
        {
            return generateFromToBy(Zero,Circle,by);
        };
        
        std::vector<Angle> Angle::generateCircleBy (Angle by)
        {
            return generateFromToBy(Zero,Circle,by);
        };
        
        
        
        
        
        
        std::vector<CCAngle> CCAngle::generateCircleCount (double count)
        {
            float to = 360.f-360.f/count*0.10;
            return generateFromToBy(Zero,to,360./count);
        };
        
        std::vector<Degrees> Degrees::generateCircleCount (double count)
        {
            float to = Circle-Circle/count*0.10;
            return generateFromToBy(Zero,to,Circle/count);
        };
        
        std::vector<Radians> Radians::generateCircleCount (double count)
        {
            float to = Circle-Circle/count*0.10;
            return generateFromToBy(Zero,to,Circle/count);
        };
        
        std::vector<Angle> Angle::generateCircleCount (Angle count)
        {
            return generateFromToBy(Zero,Circle,Radians(Circle.asRadians()/count.asRadians()));
        };
        
        

        
        
        
        CCAngle       ccRotationInWorld   (CCNodePtr p)
        {
            CCAngle r = 0;
            while(p) {
                r += ccRotation(p);
                p = ccParentOf(p);
            }
            return r;
        }
        
        

        
        
        vector<CCPoint> ccpGenerateWithLine (CCLine line, int count, CCPoint randomrange)
        {
            vector<CCPoint> r;
            r.reserve(count);
            float dx = line.dx()/(count-1.f);
            float dy = line.dy()/(count-1.f);
            loopUpTo(i,count)
            {
//                CCPoint dp = Vec2(randomf(-randomrange.x,randomrange.x), randomf(-randomrange.y,randomrange.y));
                CCPoint dp = Vec2(randomSign()*random(fabs(randomrange.x)), randomSign()*random(fabs(randomrange.y)));
                r.push_back(line.from+dp);
                line.from.x += dx;
                line.from.y += dy;
            }
            return r;
        }
        
        vector<CCPoint> ccpGenerateWithOpenLine (CCLine line, int count, CCPoint randomrange)
        {
            vector<CCPoint> r;
            r.reserve(count);
            float dx = line.dx()/(count);
            float dy = line.dy()/(count);
            loopUpTo(i,count)
            {
                    //                CCPoint dp = Vec2(randomf(-randomrange.x,randomrange.x), randomf(-randomrange.y,randomrange.y));
                CCPoint dp = Vec2(randomSign()*random(fabs(randomrange.x)), randomSign()*random(fabs(randomrange.y)));
                r.push_back(line.from+dp);
                line.from.x += dx;
                line.from.y += dy;
            }
            return r;
        }
        
        vector<CCPoint> ccpGenerateWithPolyLine (vector<pair<CCPoint,int>> points, CCPoint randomrange)
        {
            vector<CCPoint> r;
            r.reserve(64);
            
            CCPoint p0;
            
            bool first = true;
            
            for(autoCRef point:points)
            {
                if (not first)
                {
                    append(r,ccpGenerateWithOpenLine({p0,point.first},point.second,randomrange));
                }
                first   = false;
                p0      = point.first;
            }
            return r;
        }
        
        vector<CCPoint> ccpGenerateWithBezier (CCPoint p0, ccBezierConfig c, int count, Range timerange, CCPoint randomrange)
        {
            vector<CCPoint> r;
            r.reserve(count);
            loopUpTo(i,count)
            {
                CCPoint dp = Vec2(randomSign()*random(fabs(randomrange.x)), randomSign()*random(fabs(randomrange.y)));
                float t = i/(count-1.f);
                t += randomRangef(timerange);
                r.push_back(ccBezierAt(p0,t,c)+dp);
            }
            return r;
        }
        
        vector<CCPoint> ccpGenerateWithBezier (CCPoint p0, ccBezierConfig c, vector<float> times, CCPoint randomrange)
        {
            vector<CCPoint> r;
            r.reserve(times.size());
            for(float t:times)
            {
                CCPoint dp = Vec2(randomSign()*random(fabs(randomrange.x)), randomSign()*random(fabs(randomrange.y)));
                r.push_back(ccBezierAt(p0,t,c)+dp);
            }
            return r;
        }
        
        vector<CCPoint> ccpGenerateWithBox (CCRect box, int count)
        {
            vector<CCPoint> r;
            r.reserve(count);
            loopUpTo(i,count)
            {
                r.push_back(Vec2(box.origin.x+randomf(box.size.width),box.origin.y+randomf(box.size.height)));
            }
            return r;
        }
        
        vector<CCPoint> ccpGenerateWithGrid (CCRect box, Dimension dim, CCPoint randomrange, bool up, bool vertical)
            // up=true  vertical=true   => up first, then right  => (1,1)(1,2)...(1,n),(2,1)(2,2)...(2,n)
            // up=true  vertical=false  => right first, then up  => (1,1)(2,1)...(n,1),(1,2)(2,2)...(n,2)
            // up=false vertical=true   => down first, then left => (n,n)(n,n-1)...(n,1),(n-1,n)(n-1,n-1)...(n-1,1)
            // up=false vertical=false  => left first, then down => (n,n)(n-1,n)...(1,n),(n,n-1)(n-1,n-1)...(1,n-1)
        {
            vector<CCPoint> r;
            r.reserve(dim.across*dim.down);
            float dx = box.size.width / (dim.across-1.f);
            float dy = box.size.height / (dim.down-1.f);
            struct Compare
            {
                std::function<bool (const CCPoint &, const CCPoint &)> function = 0;
                inline bool operator () (const CCPoint & a, const CCPoint & b) const { return function(a,b); }
            };
            Compare compare;
            if (up)
            {
                if (vertical)
                    compare.function = [] (const CCPoint & a, const CCPoint & b) -> bool { return a.x < b.x or (a.x == b.x and a.y < b.y); };
                else
                    compare.function = [] (const CCPoint & a, const CCPoint & b) -> bool { return a.y < b.y or (a.y == b.y and a.x < b.x); };
            }
            else
            {
                if (vertical)
                    compare.function = [] (const CCPoint & a, const CCPoint & b) -> bool { return a.x > b.x or (a.x == b.x and a.y > b.y); };
                else
                    compare.function = [] (const CCPoint & a, const CCPoint & b) -> bool { return a.y > b.y or (a.y == b.y and a.x > b.x); };
            }
            std::set<CCPoint,Compare> locations(compare);
            loopUpTo(x,dim.across) {
                loopUpTo(y,dim.down) {
                    CCPoint loc = Vec2(box.origin.x + x*dx, box.origin.y + y*dy);
                    locations.insert(loc);
                }
            }
            for(auto loc:locations) {
//                CCPoint dp = Vec2(randomf(-randomrange.x,randomrange.x), randomf(-randomrange.y,randomrange.y));
                CCPoint dp = Vec2(randomSign()*random(fabs(randomrange.x)), randomSign()*random(fabs(randomrange.y)));
                r.push_back(loc+dp);
            }
            return r;
        }
        
        vector<CCPoint> ccpGenerateWithArc (float distance, CCAngle angle0, CCAngle angle1, CCAngle dangle, bool aspectCorrected)
        {
            if (aspectCorrected)
            {
                std_vectorWithCapacity(r,CCPoint,(1+(angle1-angle0)/dangle));
                for(CCAngle a=angle0; a <= angle1; a+=dangle) { r.push_back(ccpFromPolarWithAspectCorrectedY(distance,a)); }
                return r;
            }
            return ccpGenerateWithOval(distance,distance,angle0,angle1,dangle);
        };

        vector<CCPoint> ccpGenerateWithOval (float rx, float ry, CCAngle angle0, CCAngle angle1, CCAngle dangle)
        {
            std_vectorWithCapacity(r,CCPoint,(1+(angle1-angle0)/dangle));
            for(CCAngle a=angle0; a <= angle1; a+=dangle) {
                float angle = a.asRadians();
                r.push_back(Vec2(rx*cosf(angle),ry*sinf(angle)));
            }
            return r;
        };

        vector<CCPoint> ccpGenerateWithSpiralAddition (float distance0, float distance1, float addition, CCAngle angle0, CCAngle angle1, bool aspectCorrected)
        {
            std_vectorWithCapacity(r,CCPoint,(angle1-angle0)/4);
            for(float d=distance0; d <= distance1; d+=addition)
            {
                float t = tiny::Math::progress(distance0,distance1,d);
                CCAngle a = tiny::Math::lerp(angle0,angle1,t);
                if (aspectCorrected)
                    r.push_back(ccpFromPolarWithAspectCorrectedY(d,a));
                else
                    r.push_back(Vec2(a.cosf(),a.sinf())*d);
            }
            return r;
        };
        
        vector<CCPoint> ccpGenerateWithSpiralMultiplier (float distance0, float distance1, float multiplier, CCAngle angle0, CCAngle angle1, bool aspectCorrected)
        {
            std_vectorWithCapacity(r,CCPoint,(angle1-angle0)/4);
            for(float d=distance0; d <= distance1; d*=multiplier)
            {
                float t = tiny::Math::progress(distance0,distance1,d);
                CCAngle a = tiny::Math::lerp(angle0,angle1,t);
                if (aspectCorrected)
                    r.push_back(ccpFromPolarWithAspectCorrectedY(d,a));
                else
                    r.push_back(Vec2(a.cosf(),a.sinf())*d);
            }
            return r;
        };
        
        vector<CCPoint> ccpGenerateStar (int sides, int pointsPerSegment, float_01 innerlength, CCPoint randomrange)
        {
            auto angles = CCAngle::generateCircleCount(2*sides);
            
            angles.push_back(angles[0]);
            
            vector<pair<CCPoint,int>> poly;
            
            poly.reserve(angles.size()+1);
            
            float   radius  = 1;
            bool    flag    = true;
            auto    angle0  = -angles[1]/2.;
            
            for(auto angle:angles)
            {
                angle += angle0;
                poly.push_back({angle.asVector() * radius,pointsPerSegment});
                flag = not flag;
                if (flag)
                    radius = 1;
                else
                    radius = innerlength;
            }
            return ccpGenerateWithPolyLine(poly,randomrange);
        }
        
        
        
        CCSize sn2swSQ(CCNodePtr n) {
            CCSize s = ccSize(n);
            CCPoint v00 = pn2pw(n,{0,0});
            CCPoint v10 = pn2pw(n,{s.width,0});
            CCPoint v01 = pn2pw(n,{0,s.height});
            return {ccpDistanceSQ(v10,v00),ccpDistanceSQ(v01,v00)};
        }
        
        CCSize sn2sw(CCNodePtr n) {
            CCSize s = ccSize(n);
            CCPoint v00 = pn2pw(n,{0,0});
            CCPoint v10 = pn2pw(n,{s.width,0});
            CCPoint v01 = pn2pw(n,{0,s.height});
            return {ccpDistance(v10,v00),ccpDistance(v01,v00)};
        }

        
        
        
        
        
        void Prnrn(CCNodePtr target,
                   CCRatioCRef ratioT,
                   CCNodePtr relative,
                   CCRatioCRef ratioR)
        {
            CCPoint t = r2p(target,ratioT); // t is in target space
            t = target -> convertToWorldSpace(t);
            CCPoint r = r2p(relative,ratioR); // r is in relative space
            r = relative -> convertToWorldSpace(r); // r is in world space
            
            CCPoint d = r - t;
            
            CCPoint p0 = ccPosition(target); // p0 is in ccParentOf(target) space (translation from origin of content rectangle of parent)
            
            p0 = ccParentOf(target) -> convertToWorldSpace(p0);
            
            p0 = p0 + d;
            
            p0 = ccParentOf(target) -> convertToNodeSpace(p0);
            
            ccPosition(target,p0);
        }
        
        void Prnrn(CCNodePtr target,
                   CCRatioCRef ratioT,
                   CCRatioCRef ratioP)
        {
            Prnrn(target,ratioT,ccParentOf(target),ratioP);
        }
        
        void Prara(CCNodePtr target,
                   CCRatioCRef ratioT,
                   CCNodePtr relative,
                   CCRatioCRef ratioR)
        {
            CCPoint r = ccPosition(target) + (pw2pa(target,rn2pw(relative,ratioR)) - rn2pa(target,ratioT));
            
            target -> setPosition(r);
        }
        
        
        
        
        double ccScreenDiagonal() {
            static double diagonal = -1;
            if (diagonal < 0) {
                diagonal = tiny::Math::hypotenuse(sizeScreen.width, sizeScreen.height);
            }
            return diagonal;
        }

        
        
        
        
        
        void ccScaleToFit (CCNodePtr n, CCSize s)
        {
            auto size = ccSize(n);
            
            if (0 < size.width and 0 < size.height and 0 < s.width and 0 < s.height)
            {
                float factorw = s.width / size.width;
                float factorh = s.height / size.height;
                
                if (factorw < factorh)
                {
                    ccScale(n,factorw);
                }
                else
                {
                    ccScale(n,factorh);
                }
            }
        }
        
        
        
        
        CCRect ccScale(CCRectCRef p, float x, float y) {
            CCRect r = p;
            float sw = r.size.width * x;
            float sh = r.size.height * y;
            r.origin.x += (r.size.width - sw)/2.;
            r.origin.y += (r.size.height - sh)/2.;
            r.size.width = sw;
            r.size.height = sh;
            return r;
        }
        
        CCRect operator + (CCRectCRef a, CCRectCRef b) {
            CCRect r;
            r.origin.x = std::min(a.origin.x,b.origin.x);
            r.origin.y = std::min(a.origin.y,b.origin.y);
            r.size.width = std::max(a.origin.x+a.size.width,b.origin.x+b.size.width) - r.origin.x;
            r.size.height = std::max(a.origin.y+a.size.height,b.origin.y+b.size.height) - r.origin.y;
            return r;
        }
        
        CCRect operator + (CCRectCRef a, CCPointCRef b) {
            CCRect r;
            r.origin.x = std::min(a.origin.x,b.x);
            r.origin.y = std::min(a.origin.y,b.y);
            r.size.width = std::max(a.origin.x+a.size.width,b.x) - r.origin.x;
            r.size.height = std::max(a.origin.y+a.size.height,b.y) - r.origin.y;
            return r;
        }

        
        
        void ccReparent             (CCNodePtr child, CCNodePtr newParent) {
            child -> retain();
            child -> removeFromParentAndCleanup(false);
            newParent -> addChild(child);
            child -> release();
        }
        
        void ccReparent             (CCNodePtr child, CCNodePtr newParent, int z) {
            child -> retain();
            child -> removeFromParentAndCleanup(false);
            newParent -> addChild(child,z);
            child -> release();
        }

        void ccReparentPreserved    (CCNodePtr child, CCNodePtr parent, bool position, bool rotation) {
            CCPoint point0;
            if (position) point0 = pn2pw(child);
            CCAngle angle0;
            if (rotation) angle0 = ccRotationInWorld(child);
            ccReparent(child,parent);
            if (rotation) ccRotation(child,angle0-ccRotationInWorld(ccParentOf(child)));
            if (position) ccPosition(child,pw2pn(parent,point0));
        }
        
        void ccReparentPreserved    (CCNodePtr child, CCNodePtr parent, int z, bool position, bool rotation) {
            CCPoint point0;
            if (position) point0 = pn2pw(child);
            CCAngle angle0;
            if (rotation) angle0 = ccRotationInWorld(child);
            ccReparent(child,parent,z);
            if (rotation) ccRotation(child,angle0-ccRotationInWorld(ccParentOf(child)));
            if (position) ccPosition(child,pw2pn(parent,point0));
        }
        

        void anchor                 (CCNodePtr node, CCPoint p) {
            if (ccParentOf(node)) {
                CCPoint p0 = ccAnchor(node);
                CCPoint p1 = ccPosition(node);
                CCPoint dp = p-p0;
                p1 += dp * ccSize(node);
                ccPosition(node,p1);
            }
            node -> setAnchorPoint(p);
        }

        void setRotation            (CCNodePtr target, float rotationRatio)
        {
            target -> setRotation(AngleRatio::toDegrees(rotationRatio));
        }
        
        
        
        
        
        
        
        
        
        
        vector<CCNodePtr> ccChildren    (CCNodePtr p)
        {
            vector<CCNodePtr> r;
            if (p)
            {
                int size = (int)p -> getChildrenCount();
                r.reserve(size);
                for(auto child:p -> getChildren())
                {
                    r.push_back((CCNodePtr)child);
                }
            }
            return r;
        }
        
        
        
        
        
        vector<CCNodePtr>   ccDescendants               (CCNodePtr p)
        {
            vector<CCNodePtr> r;
            if (p)
            {
                int size = 10 * (int) p-> getChildrenCount();
                r.reserve(size);
                for(CCNodePtr c:p->getChildren())
                {
                    append(r,c);
                    vector<CCNodePtr> r1 = ccDescendants(c);
                    append(r,r1);
                }
            }
            return r;
        }
        
        
        
        
        
        
        vector<CCNodePtr>   ccChildren                  (CCNodePtr p, std::function<bool (CCNodePtr)> f)
        {
            vector<CCNodePtr> r;
            if (p)
            {
                auto count = (int)p -> getChildrenCount();
                if (0 < count)
                {
                    r.reserve(count);
                    for(auto child:p->getChildren())
                    {
                        CCNodePtr c = (CCNodePtr) child;
                        if (f(c))
                        {
                            r.push_back(c);
                        }
                    }
                }
            }
            return r;
        }
        
        
        
        
        
        
        vector<CCNodePtr>   ccChildrenWithTag           (CCNodePtr p, int tag)
        {
            return ccChildren(p, [tag] (CCNodePtr p) {
                return tag == ccTag(p);
            });
        }
        

        
        
        
        
        void                ccChildrenApply             (CCNodePtr p, std::function<void (CCNodePtr)> f)
        {
            for(auto child:p->getChildren())
            {
                CCNodePtr c = (CCNodePtr) child;
                f(c);
            }
        }
        
        
        
        
        
        vector<CCNodePtr>   ccDescendants               (CCNodePtr p, std::function<bool (CCNodePtr)> f)
        {
            vector<CCNodePtr> r;
            if (p) {
                r.reserve(256);
                for(CCNodePtr c:ccChildren(p)) {
                    if (f(c)) r.push_back(c);
                    vector<CCNodePtr> r1 = ccDescendants(c,f);
                    append(r,r1);
                }
            }
            return r;
        }
        
        
        
        
        vector<CCNodePtr> ccDescendantsWithTag (CCNodePtr p, int tag)
        {
            return ccDescendants(p, [tag] (CCNodePtr p) {
                return tag == ccTag(p);
            });
        }
        
        
        
        
        CCRect       bbox                (CCNodePtr p, bool global)
        {
            if (p)
            {
                if (global)
                {
                    auto size = ccSize(p);
                    CCRect rect = CCRect(0, 0, size.width, size.height);
                    return RectApplyAffineTransform(rect,p->nodeToWorldTransform());
                }
                    // NOTE: 'boundingBox' RETURNS RECTANGLE IN >>PARENT'S<< SPACE (NOT ROOT/GLOBAL SPACE)
                return p -> boundingBox();
            }
            return CCNull.rect;
        }

        
        
        
        
        AABB::AABB(CCNodePtr p, bool recursive) : AABB(bbox(p,true))
        {
            if (recursive)
            {
                    //for(auto n:ccChildren(p)) { add(AABB(n,true)); }
                for(auto n:ccDescendants(p)) { add(AABB(n,false)); }
            }
        }
        
        
        
        
        AABBRef AABB::add(AABBCRef p)
        {
            float X1 = max(p.x1(),x1());
            float Y1 = max(p.y1(),y1());
            float X0 = min(p.x0(),x0());
            float Y0 = min(p.y0(),y0());
            origin.x        = X0;
            origin.y        = Y0;
            size.width      = fabs(X1-X0);
            size.height     = fabs(Y1-Y0);
            return *this;
        }
        
        AABBRef AABB::add(CCPoint p)
        {
            float X1 = max(p.x,x1());
            float Y1 = max(p.y,y1());
            float X0 = min(p.x,x0());
            float Y0 = min(p.y,y0());
            origin.x        = X0;
            origin.y        = Y0;
            size.width      = fabs(X1-X0);
            size.height     = fabs(Y1-Y0);
            return *this;
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        HSV::HSV(Color3F p)
        {
            typedef struct
            {
                double h;       // angle in degrees
                double s;       // percent
                double v;       // percent
            } HSV;
            
            typedef struct
            {
                double r;       // percent
                double g;       // percent
                double b;       // percent
                double a;       // percent
            } RGBA;
            
            RGBA value;
            
            value.r = min(1.f,max(0.f,p.r));
            value.g = min(1.f,max(0.f,p.g));
            value.b = min(1.f,max(0.f,p.b));
            value.a = 1;
            
            HSV         out;
            double      min, max, delta;
            
            min = value.r < value.g ? value.r : value.g;
            min = min  < value.b ? min  : value.b;
            
            max = value.r > value.g ? value.r : value.g;
            max = max  > value.b ? max  : value.b;
            
            out.v = max;                                // v
            
            delta = max - min;
            
            if( 0. < delta and 0. < max )
            {
                out.s = (delta / max);                  // s
                
                if( max == value.r )                        // > is bogus, just keeps compilor happy
                {
                    out.h = ( value.g - value.b ) / delta;        // between yellow & magenta
                }
                else
                {
                    if( max == value.g )
                        out.h = 2.0 + ( value.b - value.r ) / delta;  // between cyan & yellow
                    else
                        out.h = 4.0 + ( value.r - value.g ) / delta;  // between magenta & cyan
                }
                
                out.h *= 60.0;                              // degrees
                
                if( out.h < 0.0 )
                {
                    out.h += 360.0;
                }
            }
            else
            {
                    // r = g = b = 0                        // s = 0, v is undefined
                out.s = 0.0;
                out.h = 0.0; // -1;                           // its now undefined (don't know if setting to NAN is a good idea)
            }
            
        exit:
            
            h = out.h;
//            tLog("converting to hsv, out.h="<<out.h<<" r.h="<<r.h);
            s = out.s;
            v = out.v;
        }
        
        HSV::HSV(Color4F c) : HSV(Color3F{c.r,c.g,c.b})
        {
        }
        

        
        
        Color3F HSV::ccc3f() const
        {
            typedef struct
            {
                double h;       // angle in degrees [0,360]
                double s;       // percent [0,1]
                double v;       // percent [0,1]
            } HSV;
            
            typedef struct
            {
                double r;       // percent [0,1]
                double g;       // percent [0,1]
                double b;       // percent [0,1]
                double a;       // percent [0,1]
            } RGBA;
            
            HSV value;
            
            value.h = h;
            value.s = s;
            value.v = v;
            
            double      hh, p, q, t, ff;
            long        i;
            RGBA        out;
            out.a        = 1;
            
            if (value.s <= 0.0) // < is bogus, just shuts up warnings
            {
                if (isnan(value.h)) // value.h == NAN
                {
                    out.r = value.v;
                    out.g = value.v;
                    out.b = value.v;
                    goto exit;
                }
                
                    // error - should never happen
                out.r = 0.0;
                out.g = 0.0;
                out.b = 0.0;
                goto exit;
            }
            
            hh = value.h;
            if(hh >= 360.0)
            {
                hh = 0.0;
            }
            hh /= 60.0;
            i = (long)hh;
            ff = hh - i;
            p = value.v * (1.0 - value.s);
            q = value.v * (1.0 - (value.s * ff));
            t = value.v * (1.0 - (value.s * (1.0 - ff)));
            
            switch(i)
            {
                case 0:
                    out.r = value.v;
                    out.g = t;
                    out.b = p;
                    break;
                case 1:
                    out.r = q;
                    out.g = value.v;
                    out.b = p;
                    break;
                case 2:
                    out.r = p;
                    out.g = value.v;
                    out.b = t;
                    break;
                    
                case 3:
                    out.r = p;
                    out.g = q;
                    out.b = value.v;
                    break;
                case 4:
                    out.r = t;
                    out.g = p;
                    out.b = value.v;
                    break;
                case 5:
                default:
                    out.r = value.v;
                    out.g = p;
                    out.b = q;
                    break;
            }
            
        exit:
            
            Color3F r;
            
            r.r = out.r;
            r.g = out.g;
            r.b = out.b;
            
            return r;
        }
        
        
        
        
        Color4F HSV::ccc4f(float a) const
        {
            auto c = this->ccc3f();
            
            return {c.r,c.g,c.b,a};
        }
        
        
        HSVA HSV::ccHSVA(float a) const
        {
            return HSVA(h,s,v,a);
        }
        
        
        
        
        
        
        
        
        
        HSVA::HSVA(Color3F c)
        {
            auto hsv = HSV(c);
            
            h = hsv.h;
            s = hsv.s;
            v = hsv.v;
            a = 1;
        }
        
        HSVA::HSVA(Color4F c) : HSVA(Color3F{c.r,c.g,c.b})
        {
            a = c.a;
        }

        HSV HSVA::ccHSV() const
        {
            return HSV(h,s,v);
        }
        
        
        
        
        Color3F HSVA::ccc3f() const
        {
            return ccHSV().ccc3f();
        }
        
        
        
        
        Color4F HSVA::ccc4f() const
        {
            return ccHSV().ccc4f(a);
        }
        
        

        
        
        
        
        
        
        
        
        Color3F ccc3fBLACK    {0,0,0};
        Color3F ccc3fWHITE    {1,1,1};
        Color3F ccc3fRED      {1,0,0};
        
        
        
        
        
        void ccContentSize (CCNodePtr node)
        {
            typedef struct {
                float x1, y1, x2, y2;
            } BBox;
            
            BBox outline = {0, 0, 0, 0};
            
            for(auto child:node -> getChildren())
            {
                CCNodePtr n = (CCNodePtr) child;
                ccContentSize(n);
                
                CCPoint position = n -> getPosition();
                CCSize  size = n -> getContentSize();
                CCPoint anchorPoint = n -> getAnchorPoint();
                
                BBox bbox;
                
                bbox.x1 = position.x - size.width * anchorPoint.x;
                bbox.y1 = position.y - size.height * anchorPoint.y;
                bbox.x2 = position.x + size.width * (1.f-anchorPoint.x) ;
                bbox.y2 = position.y + size.height * (1.f-anchorPoint.y);
                
                if (bbox.x1 < outline.x1) { outline.x1 = bbox.x1; }
                if (bbox.y1 < outline.y1) { outline.y1 = bbox.y1; }
                if (bbox.x2 > outline.x2) { outline.x2 = bbox.x2; }
                if (bbox.y2 > outline.y2) { outline.y2 = bbox.y2; }
            }
            
            if (0 < node -> getChildrenCount())
            {
                CCSize newContentSize;
                newContentSize.width    = (outline.x2 - outline.x1);
                newContentSize.height   = (outline.y2 - outline.y1);
                node -> setContentSize(newContentSize);
            }
        }
        
        
        
        
        
        
#if 0
        STRUCT(ShaderPositionsColor) : public CCGLProgram
        {
            ShaderPositionsColor()
            {
                initWithVertexShaderFilename("shaderVertexPositionsColor.h","shaderFragmentPositionsColor.h");
                bindAttribLocation("Position",0);
                bindAttribLocation("SourceColor",1);
            }
            
            GLuint getLocationForAttributeColor()
            {
                glGetAttribLocation(GLuint program, const GLchar *name);
            }
        };
#endif
        
        
        
        
        
        
        
        CCSize sizeScreen;
        
        
        
        
        void init() {
            sizeScreen = CCDirector::getInstance() -> getWinSize();
            std::cout << "tiny::Cocos2D::init(): sizeScreen=(" << sizeScreen.width << ',' << sizeScreen.height << ')' << std::endl;
            
            
#if 0
            CCGLProgramPtr program = new CCGLProgram();
            program -> autorelease();
            program -> initWithVertexShaderFilename("shaderVertexDefault.vsl","shaderFragmentDefault.fsl");
            program -> bindAttribLocation("Position",0);
            program -> bindAttribLocation("SourceColor",1);
            
            
            cache -> addProgram(program,"default");
            
                //            program -> link(); // glLinkProgram
                //            program -> use(); // glUseProgram
                //            program -> reset(); // clears content of both shaders and program
            
            std::cout << "log for vertex   shader of 'default'=" << program -> vertexShaderLog() << std::endl;
            std::cout << "log for fragment shader of 'default'=" << program -> fragmentShaderLog() << std::endl;
            std::cout << "log for program         of 'default'=" << program -> programLog() << std::endl;
#endif
            
        }
        
        
        
        
        
        
        
        
        
        void layerInitTouchEnabled(Touch::CCLayerPtr layer) {
            layer -> ignoreAnchorPointForPosition(false);
            layer -> setContentSize(screenGetSize());
            layer -> setAnchorPoint(Vec2(.5,.5));
            layer -> setPosition(screenGetPoint(.5,.5));
            layer -> setEnabledTouch(true);
        }
        
        void layerInitTouchDisabled(Touch::CCLayerPtr layer) {
            layer -> ignoreAnchorPointForPosition(false);
            layer -> setContentSize(screenGetSize());
            layer -> setAnchorPoint(Vec2(.5,.5));
            layer -> setPosition(screenGetPoint(.5,.5));
            layer -> setEnabledTouch(false);
        }
        
        void layerInit(CCLayerPtr layer) {
            layer -> ignoreAnchorPointForPosition(false);
            layer -> setContentSize(screenGetSize());
            layer -> setAnchorPoint(Vec2(.5,.5));
            layer -> setPosition(screenGetPoint(.5,.5));
        }
        

        void sceneInit(CCScenePtr scene) {
            scene -> ignoreAnchorPointForPosition(false);
            scene -> setAnchorPoint(Vec2(.5,.5));
            scene -> setPosition(screenGetPoint(.5,.5));
            scene -> setContentSize(screenGetSize());
        }
        
        
        
        
        
        
        
        
        bool ccContains(CCNodePtr node, CCPoint screen, bool onlyWhenVisible) {
            if (node and (node -> isVisible() or not onlyWhenVisible))
            {
                CCRect r;
                r.size = node -> getContentSize();// * node -> getScale();
                return r.containsPoint(node -> convertToNodeSpace(screen));
            }
            return false;
        }
        
        bool ccContainsOval(CCNodePtr node, CCPoint screen, float factor, bool onlyWhenVisible) {
            if (node and (node -> isVisible() or not onlyWhenVisible))
            {
                screen = node -> convertToNodeSpace(screen);
                    //tLog("screen="<<screen);
                CCPoint size = ccSize(node);
                CCPoint center = size/2.;
                screen -= center;
                    //tLog("screen="<<screen);
                float angle = atan2(screen.y,screen.x);
                CCPoint point = Vec2(size.x * cosf(angle), size.y * sinf(angle));
                    //tLog("point="<<point);
                point = point * factor * 0.5;
                    //tLog("point="<<point);
                float d1 = screen.getLength();
                float d2 = point.getLength();
                    //tLog("d1="<<d1<<",d2="<<d2);
                return d1 < d2;
            }
            return false;
        }
        
        
        CCActionIntervalPtr aiAlignToRatio(float duration, CCPoint ratio) {
            return aiBlock(duration,[ratio] (CCCallBlockIntervalWithSelfRef action, float dt) {
                CCNodePtr node = action.getTarget();
                if (dt < 0) {
                    CCPoint p0 = ccPosition(node);
                    action.data.push_back(p0);
                }
                else {
                    CCPoint p0 = boost::any_cast<CCPoint>(action.data[0]);
                    CCPoint p1 = r2p(ccParentOf(node),ratio);
                    CCPoint p;
                    p.x = Math::lerp(p0.x,p1.x,dt);
                    p.y = Math::lerp(p0.y,p1.y,dt);
                    ccPosition(node,p);
                }
            });
        }
        
        
        CCActionIntervalPtr aiAlignToPoint(float duration, CCPoint point) {
            return aiBlock(duration,[point] (CCCallBlockIntervalWithSelfRef action, float dt) {
                CCNodePtr node = action.getTarget();
                if (dt < 0) {
                    CCPoint p0 = ccPosition(node);
                    action.data.push_back(p0);
                }
                else {
                    CCPoint p0 = boost::any_cast<CCPoint>(action.data[0]);
                    CCPoint p;
                    p.x = Math::lerp(p0.x,point.x,dt);
                    p.y = Math::lerp(p0.y,point.y,dt);
                    ccPosition(node,p);
                }
            });
        }
        
        
        
        
        
        
        
        
        void         ccAlignToOther      (CCNodePtr me, CCRatio rme, CCNodePtr other, CCRatio rother, CCPoint move)
        {
            ccPosition(me,pw2Ppn(me,pn2pw(other,r2p(other,rother)))-r2p(me,rme)+r2p(me,ccAnchor(me))+move);
        }
        
        
        void         ccAlignToScreen     (CCNodePtr me, CCRatio rme, CCRatio rscreen, CCPoint move)
        {
            ccPosition(me,pw2Ppn(me,screenGetPoint(rscreen))-r2p(me,rme)+r2p(me,ccAnchor(me))+move);
        }

        
        
        
        
        
        ccBezierConfig           ccBezierFrom            (CCPoint from, ccBezierConfig c) {
            c.controlPoint_1    = from + c.controlPoint_1;
            c.controlPoint_2    = from + c.controlPoint_2;
            c.endPosition       = from + c.endPosition;
            return c;
        }
        
        
        ccBezierConfig ccBezierConfigWithAngleAbsolute(CCPoint p0, CCAngle angleD0, float d0, CCPoint p1, CCAngle angleD1, float d1) {
                // d0=ratio of |p1-p0|
                // d1=ratio
                // angle0/angle1=angle in degrees
                // calculate d
                // calculate c0, c1
            ccBezierConfig r;
            r.endPosition = p1-p0;
            float d = r.endPosition.getLength();
            tLog("ccBezierConfigWithAngleAbsolute: p0="<<p0<<" a0="<<angleD0<<" d0="<<d0<<" -> p1="<<p1<<" a1="<<angleD1<<" d1="<<d1<<", d="<<d);
            r.controlPoint_1 = CCPoint::forAngle(angleD0.asRadians()) * d * d0;
            r.controlPoint_2 = r.endPosition + CCPoint::forAngle(angleD1.asRadians()) * d * d1;
            return r;
        }
 
        
        ccBezierConfig ccBezierConfigWithAngleRelative(CCPoint p0, CCAngle angleD0, float d0, CCPoint p1, CCAngle angleD1, float d1) {
                // calculate d
                // calculate c0, c1
            ccBezierConfig r;
            r.endPosition = p1-p0;
            float d     = r.endPosition.getLength();
            Radians a   = r.endPosition.getAngle();
            a.normalize();
            tLog("ccBezierConfigWithAngleRelative: p0="<<p0<<" a0="<<angleD0<<" d0="<<d0<<" -> p1="<<p1<<" a1="<<angleD1<<" d1="<<d1<<", d="<<d);
            r.controlPoint_1 = CCPoint::forAngle(a-angleD0.asRadians()) * d * d0;
            r.controlPoint_2 = r.endPosition + CCPoint::forAngle(a-angleD1.asRadians()) * d * d1;
            return r;
        }
        
        
        double ccBezierLength(CCPoint p0, ccBezierConfigCRef config, float dt)
        {
            double r = 0;
            
            dt = fabs(dt);
            
            if (0 < dt)
            {
                CCPoint p,pp = p0;
                
                for(float t = dt; ; )
                {
                    {
                        p    =  ccBezierAt(p0,t,config);
                        r   +=  p.getDistance(pp);
                        pp   =  p;
                    }
                    
                    if (t == 1)
                    {
                        break;
                    }
                    
                    t   +=  dt;
                    
                    if (1 < t)
                    {
                        t   = 1;
                    }
                }
            }
            return r;
        }
        

        ccBezierDistance ccBezierDistanceTo(CCPoint p0, ccBezierConfigCRef config, CCPoint to, float dt)
        {
            ccBezierDistance r;
            
            dt = fabs(dt);
            
            if (0 < dt)
            {
                CCPoint pp = p0;
                
                for(float t = 0; ; )
                {
                    CCPoint p = ccBezierAt(p0,t,config);
                    {
                        double distance = p.getDistance(to);
                        
                        if (distance < r.minimum.v)
                        {
                            r.minimum.t = t;
                            r.minimum.v = distance;
                        }
                        if (r.maximum.v < distance)
                        {
                            r.maximum.t = t;
                            r.maximum.v = distance;
                        }
                    }
                    
                    if (t == 1)
                    {
                        break;
                    }
                    
                    t   +=  dt;
                    
                    if (1 < t)
                    {
                        t   = 1;
                    }

                }
            }
            return r;
        }
        
        
        
        
        CCAngle                  ccBezierAngleAt         (float_01 t, ccBezierConfigCRef c, float delta)
        {
            if ((t-delta)<0)   return CCAngle(ccBezierAt(t+delta,c)-ccBezierAt(t,c));
            if (1<(t+delta))   return CCAngle(ccBezierAt(t,c)-ccBezierAt(t-delta,c));
            
            return CCAngle(ccBezierAt(t+delta,c)-ccBezierAt(t-delta,c));
        }

        
        
        
        std::ostream & operator << (std::ostream & o, const ccBezierDescription & p)
        {
            return o << '(' << p.distance0 << ':' << p.angle0.value << ',' << p.distance1 << ':' << p.angle1.value << ')';
        }
        
        
        
        
        CCSequencePtr aSequence(const std::vector<CCActionIntervalPtr>& actions) {
            int tag = 0;
            Vector<FiniteTimeAction*> r;
            r.reserve(actions.size());
            for(CCActionIntervalPtr a:actions) { tag |= ccTag(a); r.pushBack(a); }
            auto v = CCSequence::create(r);
            ccTag(v,tag);
            return v;
        }
        
        CCSpawnPtr aSpawn(const std::vector<CCActionIntervalPtr>& actions) {
            int tag = 0;
            Vector<FiniteTimeAction*> r;
            r.reserve(actions.size());
            for(CCActionIntervalPtr a:actions) { tag |= ccTag(a); r.pushBack(a); }
            auto v = CCSpawn::create(r);
            ccTag(v,tag);
            return v;
        }
       
        
        
        
        int                             ccTagOr      (vectorCRef(CCActionPtr) p)
        {
            int r = 0;
            for(autoCRef a:p) r |= ccTag(a);
            return r;
        }
        
        std::vector<CCActionPtr>        ccActionsOf    (CCNodePtr n)
        {
            return n->getActionManager()->getActionsByTarget(n);
        }
        
        
        
        
        
        
        bool ccRemoveFromParent  (CCNodePtr n, bool cleanup) {
            if (n and ccParentOf(n)) {
                ccParentOf(n) -> removeChild(n,cleanup);
                return true;
            }
            return false;
        }

        bool ccRemoveFromParentAndClear  (CCNodePtr & n, bool cleanup) {
            if (ccRemoveFromParent(n,cleanup)) {
                n = 0;
                return true;
            }
            return false;
        }
        
        
        
        
        CCAnimationPtr ccAnimation(float duration, const vector<string>& filenamesAndDurations, bool restore) {
            CCAnimationPtr r = CCAnimation::create();
            for(auto & e : filenamesAndDurations) {
                r -> addSpriteFrameWithFile(e);
            }
            r -> setDelayPerUnit(duration/filenamesAndDurations.size());
            r -> setRestoreOriginalFrame(restore);
            return r;
        }
        
        
        CCSpriteBatchNodePtr ccSpriteBatchNodeCreate(string name, int elements) {
            CCSpriteFrameCachePtr _____cache = CCSpriteFrameCache::getInstance();
            _____cache -> addSpriteFramesWithFile(name+".plist");
            return CCSpriteBatchNode::create(name+".png",elements);
        }

        
        
        
        
            // 8< --------------------------------------------------------------------------------------
        
        namespace Geometry2D
        {
            CCPoint circleGetCenterFrom3Points(CCPoint A, CCPoint B, CCPoint C)
            {
                float yDelta_a = B.y - A.y;
                float xDelta_a = B.x - A.x;
                float yDelta_b = C.y - B.y;
                float xDelta_b = C.x - B.x;
                CCPoint center = Vec2(0,0);
                float aSlope = yDelta_a/xDelta_a;
                float bSlope = yDelta_b/xDelta_b;
                center.x = (aSlope*bSlope*(A.y - C.y) + bSlope*(A.x + B.x) - aSlope*(B.x+C.x) )/(2* (bSlope-aSlope) );
                if (aSlope)
                    center.y = -1 * (center.x - (A.x + B.x) / 2) / aSlope + (A.y + B.y)/2;
                else
                    center.y = -1 * (center.x - (B.x + C.x) / 2) / bSlope + (B.y + C.y) / 2;
                return center;
            }
            
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            //                    GL_ZERO                       (0,0,0,0)                       //0 0 0 0
            //                    GL_ONE                        (1,1,1,1)                       //1 1 1 1
        
            //                    GL_SRC_COLOR	                (Rs,Gs,Bs,As)                   //R s k R G s k G B s k B A s k A
            //                    GL_ONE_MINUS_SRC_COLOR	    (1-Rs,1-Gs,1-Bs,1-As)           //1 1 1 1 - R s k R G s k G B s k B A s k A
        
            //                    GL_DST_COLOR                  (Rd,Gd,Bd,Ad)                   //R d k R G d k G B d k B A d k A
            //                    GL_ONE_MINUS_DST_COLOR        (1-Rd,1-Gd,1-Bd,1-Ad)           //1 1 1 1 - R d k R G d k G B d k B A d k A
        
            //                    GL_SRC_ALPHA                  (As,As,As,As)                   //A s k A A s k A A s k A A s k A
            //                    GL_ONE_MINUS_SRC_ALPHA        (1-As,1-As,1-As,1-As)           //1 1 1 1 - A s k A A s k A A s k A A s k A
        
            //                    GL_DST_ALPHA                  (Ad,Ad,Ad,Ad)                   //A d k A A d k A A d k A A d k A
            //                    GL_ONE_MINUS_DST_ALPHA        (1-Ad,1-Ad,1-Ad,1-Ad)           //1 1 1 1 - A d k A A d k A A d k A A d k A
        
            //                    GL_CONSTANT_COLOR             (Rc,Gc,Bc,Ac)                   //R c G c B c A c
            //                    GL_ONE_MINUS_CONSTANT_COLOR	(1-Rc,1-Gc,1-Bc,1-Ac)           //1 1 1 1 - R c G c B c A c
        
            //                    GL_CONSTANT_ALPHA             (Ac,Ac,Ac,Ac)                   //A c A c A c A c
            //                    GL_ONE_MINUS_CONSTANT_ALPHA	(1-Ac,1-Ac,1-Ac,1-Ac)           //1 1 1 1 - A c A c A c A c
        
            //                    GL_SRC_ALPHA_SATURATE         (i,i,i,1)                       //i i i 1
        
            // RESULTANT PIXEL COLOR (R,G,B,A) = (Rs*sR,Gs*sG,Bs*sB,As*sA) +|-|r- (Rd*dR,Gd*dG,Bd*dB,Ad*dA)
            //               SOURCE COLOR=(Rs,Gs,Bs,As)
            //          DESTINATION COLOR=(Rd,Gd,Bd,Ad)
            //       SOURCE BLEND FACTORS=(sR,sG,sB,sA)
            //  DESTINATION BLEND FACTORS=(dR,dG,dB,dA)
        
            // glBlendFunc(mode src, mode dst)
            // glBlendFuncSeparate(mode src rgb, mode dst rgb, mode src a, mode dst a)
            // glBlendEquation(mode)
            //  mode is one of:
            //   GL_FUNC_ADD               = (Rs*sR + Rd*dR, Gs*sG + Gd*dG, Bs*sB + Bd*dB, As*sA + Ad*dA)
            //   GL_FUNC_SUBTRACT          = (Rs*sR - Rd*dR, Gs*sG - Gd*dG, Bs*sB - Bd*dB, As*sA - Ad*dA)
            //   GL_FUNC_REVERSE_SUBTRACT  = (Rd*dR - Rs*sR, Gd*dG - Gs*sG, Bd*dB - Bs*sB, Ad*dA - As*sA)
            // glBlendEquationSeparate(mode rgb, mode alpha)

        CCRenderTexturePtr ccRenderTextureWithFunction(CCSize size, Color4F c, std::function<void ()> f)
        {
            tAssert(f);
            
            CCRenderTexturePtr rt = CCRenderTexture::create(tiny::Math::ceiling(size.width),
                                                            tiny::Math::ceiling(size.height));
            
                // 2: Call CCRenderTexture:begin
            
            rt -> beginWithClear(c.r,c.g,c.b,c.a);
            
                // 3: Draw into the texture
            
            f();
            
                // 4: Call CCRenderTexture:end
            
            rt -> end();
            
                // HACK! SEE DISCUSSION: http://discuss.cocos2d-x.org/t/bugs-for-unknown-commands-in-renderer/16865/10
                // NOTE: IN ESSENCE, BECAUSE WE WANT TO CREATE A TEXTURE DURING AN UPDATE (THIS METHOD IS LIKELY CALLED
                //       IN THE UPDATE STATE), WE ARE NOT INTERFERING WITH DRAW COMMAND QUEUE (IE IT IS PROBABLY FINISHED
                //       AND EMPTY), WE CAN SAFELY CALL RENDER() ON THE RENDERER TO RENDER THE DRAW COMMANDS WE HAVE
                //       QUEUED DURING OUR RENDERTEXTURE PROCESS.
                //CCDirector::getInstance() -> getRenderer() -> render();
                //ccRender();

            string flag = rt->getSprite()->getTexture()->hasPremultipliedAlpha() ? "yes" : "no";
            tLog("ccRenderTextureWithFunction: created texture is PMA: " << flag);
            
            return rt;
        }
        

        CCSpritePtr ccRenderWithFunction(CCSize size, Color4F c, std::function<void ()> f)
        {
            auto rt = ccRenderTextureWithFunction(size,c,f);
            
            return ccSprite(rt -> getSprite() -> getTexture());
        }


        
        
        CCSpritePtr ccRenderWithFunctionToFile(CCSize size, Color4F c, string filename, CCImage::Format format, std::function<void ()> f)
        {
            auto rt = ccRenderTextureWithFunction(size,c,f);
            
            rt -> saveToFile(filename,format);

            return ccSprite(rt -> getSprite() -> getTexture());
        }

        
        CCSpritePtr ccRenderWithFunctionToFilePNG(CCSize size, Color4F c, string filename, std::function<void ()> f)
        {
            return ccRenderWithFunctionToFile(size,c,filename,CCImage::Format::PNG,f);
        }

        
        
        
        
        
        
        CCSpritePtr ccRender(CCNodePtr r, CCSize screen, Color4F c, CCPoint loc)
        {
            tAssert(r);
            
            CCPoint     p0  = ccPosition    (r);
            auto        s0  = ccScaleXY     (r);
            
            CCRenderTexturePtr rt = CCRenderTexture::create(tiny::Math::ceiling(screen.width),
                                                            tiny::Math::ceiling(screen.height));
            
                // 2: Call CCRenderTexture:begin
            
            rt -> beginWithClear(c.r,c.g,c.b,c.a);
            
                // 3: Draw into the texture
            
                //r -> setScaleY(-1);
            
            ccPosition      (r, loc);
            
                // NOTE: EVERY ELEMENT OF A TEXTURE MUST BE Y-FLIPPED!
            ccScaleY        (r, -s0.y);
            
//            glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ZERO, GL_ONE);//ONE_MINUS_SRC_ALPHA);

            r -> visit();
            
                //tDebug( tLog("ccRender: after  visit."); CCBlending::print() );
            
                // 4: Call CCRenderTexture:end
            
            rt -> end();
            
                // HACK! SEE DISCUSSION: http://discuss.cocos2d-x.org/t/bugs-for-unknown-commands-in-renderer/16865/10
                // NOTE: IN ESSENCE, BECAUSE WE WANT TO CREATE A TEXTURE DURING AN UPDATE (THIS METHOD IS LIKELY CALLED
                //       IN THE UPDATE STATE), WE ARE NOT INTERFERING WITH DRAW COMMAND QUEUE (IE IT IS PROBABLY FINISHED
                //       AND EMPTY), WE CAN SAFELY CALL RENDER() ON THE RENDERER TO RENDER THE DRAW COMMANDS WE HAVE
                //       QUEUED DURING OUR RENDERTEXTURE PROCESS.
//            CCDirector::getInstance() -> getRenderer() -> render();
            
                // NOTE: COMMENTED OUT THE ccRender() METHOD BECAUSE IT WAS CAUSING A 'WHITE FLASH'
//            ccRender();
            
            ccPosition      (r,p0);
            ccScaleXY       (r,s0);
            
            
            string flag = rt->getSprite()->getTexture()->hasPremultipliedAlpha() ? "yes" : "no";
            tLog("ccRenderTextureWithFunction: created texture is PMA: " << flag);
            
                // 5: Create a new Sprite from the texture
            
            return ccSprite(rt -> getSprite() -> getTexture());
        }
        
        
        
        
        
        
        
        
        
            // 8< ------------------------------------------------------------
        
        
        
        CCCallBlockPtr CCCallBlock::create(Function p) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCCallBlock,p);
        }
        
        
        void CCCallBlock::update(float time) {
            ccUnusedParameter(time);
            if (block) block();
        }
        
        bool CCCallBlock::init(Function p) {
            this -> block = p;
            return true;
        }
        
        
        
        
        
        
            // 8< ----------------------------------------------------------------------------
        
        CCCallBlockWithDataPtr CCCallBlockWithData::create(Function p) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCCallBlockWithData,p);
        }
        
        void CCCallBlockWithData::update(float time) {
            ccUnusedParameter(time);
            if (block) block(data);
        }
        
        bool CCCallBlockWithData::init(Function p) {
            this -> block = p;
            return true;
        }
        
        
        
        
        
        
            // 8< ----------------------------------------------------------------------------
        
        CCCallBlockIntervalWithDataPtr CCCallBlockIntervalWithData::create(float duration, Function p) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCCallBlockIntervalWithData,duration,p);
        }
        
        void CCCallBlockIntervalWithData::update(float time) {
            block(data,time);
        }
        
        void CCCallBlockIntervalWithData::startWithTarget(CCNodePtr p) {
            CCActionInterval::startWithTarget(p);
            block(data,-1);
        }
        
        bool CCCallBlockIntervalWithData::init(float duration, Function p) {
            if (CCActionInterval::initWithDuration(duration)) {
                tAssert(p);
                this -> block = p;
                return true;
            }
            return false;
        }
        
        CCCallBlockIntervalWithData::~CCCallBlockIntervalWithData() {
        }
        
        
        
        
        
        
        
        
        
            // 8< ----------------------------------------------------------------------------
        
        CCCallBlockIntervalPtr CCCallBlockInterval::create(Function p) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCCallBlockInterval,p);
        }
        
        void CCCallBlockInterval::update(float time) {
            if (not product) {
                product = block();
                product -> retain();
            }
            product -> update(time);
        }
        
        bool CCCallBlockInterval::init(Function p) {
            tAssert(p);
            this -> block = p;
            return true;
        }
        
        CCCallBlockInterval::~CCCallBlockInterval() {
            ccSafeReleaseNull(product);
        }
        
        
        
        
        
        
            // 8< ----------------------------------------------------------------------------
        
        CCCallBlockIntervalWithSelfPtr CCCallBlockIntervalWithSelf::create(float duration, Function p) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCCallBlockIntervalWithSelf,duration,p);
        }
        
        void CCCallBlockIntervalWithSelf::update(float time) {
            dt = time;
            block(*this,time);
        }
        
        void CCCallBlockIntervalWithSelf::startWithTarget(CCNodePtr p) {
            CCActionInterval::startWithTarget(p);
            dt = -1.f;
            block(*this,dt);
        }
        
        
        bool CCCallBlockIntervalWithSelf::init(float duration, Function p) {
            if (CCActionInterval::initWithDuration(duration)) {
                tAssert(p);
                this -> block = p;
                return true;
            }
            return false;
        }
        
        CCCallBlockIntervalWithSelf::~CCCallBlockIntervalWithSelf() {
        }
        
        
        
        
        
        
            // 8< ----------------------------------------------------------------------------
        
        CCCallBlockIntervalWithUpdatePtr CCCallBlockIntervalWithUpdate::create(float duration, Function p) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCCallBlockIntervalWithUpdate,duration,p);
        }
        
        void CCCallBlockIntervalWithUpdate::update(float time) {
            block(time);
        }
        
        bool CCCallBlockIntervalWithUpdate::init(float duration, Function p) {
            if (CCActionInterval::initWithDuration(duration)) {
                tAssert(p);
                this -> block = p;
                return true;
            }
            return false;
        }
        
        CCCallBlockIntervalWithUpdate::~CCCallBlockIntervalWithUpdate() {
        }
        
        
        
        
        
        
            // 8< ----------------------------------------------------------------------------
        
        CCConditionPtr CCCondition::create(Function p) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCCondition,p);
        }
        
        CCCondition::~CCCondition()
        {
            block = 0;
        }
        
        void CCCondition::update(float dt)
        {
            tLog("CCCondition::update("<<dt<<"):before,done="<<done);
            if (not done)
            {
                done = block(dt);
            }
            tLog("CCCondition::update("<<dt<<"):after,done="<<done);
        }
        
        bool CCCondition::isDone(void)
        {
            tLog("CCCondition::isDone():done="<<done);
            return done;
        }
        
        bool CCCondition::init(Function p)
        {
            {
                block = p;
                done = false;
                return true;
            }
            return false;
        }
        
        
        
        
        
        CCConditionLoopPtr CCConditionLoop::create(CCConditionPtr p) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCConditionLoop,p);
        }
        
        CCConditionLoop::~CCConditionLoop()
        {
        }
        
        void CCConditionLoop::step(float dt)
        {
            tLog("CCConditionLoop::update("<<dt<<"):before,done="<<isDone());
            if (not _innerAction->isDone())
            {
                _innerAction->step(dt);
            }
            tLog("CCConditionLoop::update("<<dt<<"):after,done="<<isDone());
        }
        bool CCConditionLoop::isDone(void)
        {
            tLog("CCConditionLoop::isDone():done="<<isDone());
            return _innerAction->isDone();
        }
        
        bool CCConditionLoop::init(CCConditionPtr p)
        {
            return CCRepeatForever::initWithAction(aiAction(p));
        }
        
        
        
        
        
        
        
        
            // 8< ------------------------------------------------------------
        
        
        
        
        CCActionInstantWrapperPtr CCActionInstantWrapper::create(CCActionInstantPtr p) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCActionInstantWrapper,p);
        }
        
        void CCActionInstantWrapper::startWithTarget(CCNode *pTarget) {
            executed = false;
            CCActionInterval::startWithTarget(pTarget);
        }
        
        void CCActionInstantWrapper::update(float time) {
            if (not executed)
            {
                m_pInnerAction -> setTarget(getTarget());
                m_pInnerAction -> update(time);
                executed = true;
            }
        }
        
        bool CCActionInstantWrapper::init(CCActionInstantPtr p) {
            if (CCActionInterval::initWithDuration(0)) {
                executed = false;
                tAssert(p);
                m_pInnerAction = p;
                p -> retain();
                return true;
            }
            return false;
        }
        
        CCActionInstantWrapper::~CCActionInstantWrapper() {
            ccSafeReleaseNull(m_pInnerAction);
        }
        
        
        
        
        
        
        
        void CCEaseUpdate::update (float time)
        {
            _inner->update(function(time));
        }
        
        CCActionInterval* CCEaseUpdate::reverse (void)
        {
            return create(_inner->reverse(),function);
        }
        
        bool CCEaseUpdate::init (CCActionInterval* action, Function f)
        {
            tAssert(function = f);
            return CCActionEase::initWithAction(action);
        }
        
        CCEaseUpdate* CCEaseUpdate::create(CCActionInterval* pAction, Function f)
        {
            ccNewThenInitWithArgsAutoreleaseReturn(CCEaseUpdate,pAction,f);
        }
        
        
        
        
        
        
        
            // 8< ---------------------------------------------------------
        
        
        
        
        std::vector<CCEaseCurve::Point> CCEaseCurve::Point::generateZigZagWithSpans(const Point& from,
                                                                                    const Point& to,
                                                                                    const float span0,
                                                                                    const float span1,
                                                                                    const int points)
        {
            std::vector<Point> r;
            if (0 < points) {
                if (from.t < to.t) {
                    float sign = 0;
                    if (from.v < to.v) {
                        sign = 1;
                    }
                    else if (to.v < from.v) {
                        sign = -1;
                    }
                    if (sign)
                    {
                        r.resize(2+points);
                        r.front() = from;
                        r.back() = to;
                        float dt = to.t - from.t;
                        dt = dt/(float)(1+points);
                        float dv = span0;
                        float ddv = (span1-span0)/(float)points;
                        for(int i = 1; i < r.size()-1; i++) {
                            r[i].t = r[i-1].t + dt;
                            r[i].v = r[i-1].v + dv * sign;
                            sign *= -1;
                            dv += ddv;
                        }
                    }
                }
            }
            return r;
        }
        
        std::vector<CCEaseCurve::Point> CCEaseCurve::Point::generateZigZagWithDamping(const Point& from,
                                                                                      const Point& to,
                                                                                      const float dv0,
                                                                                      const float dv1,
                                                                                      const float dt,
                                                                                      const float ddt)
        {
            std::vector<Point> r;
            if (0 < dt and 0 < ddt) {
                if (from.t < to.t) {
                    if (from.v != to.v)
                    {
                        std::list<Point> points;
                        points.push_front(from);
                        const float DV = fabs(to.v-from.v);
                        const float sign = from.v < to.v ? +1 : -1;
                        float T = from.t;
                        float DT = dt;
                        int turn = 0;
                        float V0 = DV * dv0;
                        float V1 = DV * dv1;
                        while((T += (DT *= ddt)) < to.t) {
                            if (turn % 2) {
                                float V = to.v - sign * V1;
                                points.push_back({T,V});
                                V1 += V1 * dv1;
                            }
                            else {
                                float V = from.v + sign * V0;
                                points.push_back({T,V});
                                V0 += V0 * dv0;
                            }
                            turn++;
                            std::cout << "generated(" << points.size() << ")=" << points.back() << std::endl;
                            if (50 < turn)
                                break;
                        }
                        points.push_back(to);
                        r.resize(points.size());
                        std::copy(points.begin(),points.end(),r.begin());
                    }
                }
            }
            return r;
        }
        
        CCEaseCurvePtr CCEaseCurve::create(CCActionIntervalPtr a, float v, bool reverse) {
            if (reverse)
            {
                ccNewThenInitWithArgsAutoreleaseReturn(CCEaseCurve,a,{Point(0,1),Point(.5,v),Point(1,0)});
            }
            else
            {
                ccNewThenInitWithArgsAutoreleaseReturn(CCEaseCurve,a,{Point(0,0),Point(.5,v),Point(1,1)});
            }
        }
        
        CCEaseCurvePtr CCEaseCurve::create(CCActionIntervalPtr a, Point p, bool reverse) {
            if (reverse)
            {
                ccNewThenInitWithArgsAutoreleaseReturn(CCEaseCurve,a,{Point(0,1),p,Point(1,0)});
            }
            else
            {
                ccNewThenInitWithArgsAutoreleaseReturn(CCEaseCurve,a,{Point(0,0),p,Point(1,1)});
            }
        }
        
        CCEaseCurvePtr CCEaseCurve::create(CCActionIntervalPtr a, Point p1, Point p2, bool reverse) {
            if (reverse)
            {
                ccNewThenInitWithArgsAutoreleaseReturn(CCEaseCurve,a,{Point(0,1),p1,p2,Point(1,0)});
            }
            else
            {
                ccNewThenInitWithArgsAutoreleaseReturn(CCEaseCurve,a,{Point(0,0),p1,p2,Point(1,1)});
            }
        }
        
        CCEaseCurvePtr CCEaseCurve::create(CCActionIntervalPtr a, Point p1, Point p2, Point p3, bool reverse) {
            if (reverse)
            {
                ccNewThenInitWithArgsAutoreleaseReturn(CCEaseCurve,a,{Point(0,1),p1,p2,p3,Point(1,0)});
            }
            else
            {
                ccNewThenInitWithArgsAutoreleaseReturn(CCEaseCurve,a,{Point(0,0),p1,p2,p3,Point(1,1)});
            }
        }
        
        CCEaseCurvePtr CCEaseCurve::create(CCActionIntervalPtr a, const std::vector<Point>& p) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCEaseCurve,a,p);
        }
        
        CCActionIntervalPtr CCEaseCurve::reverse(void)
        {
            std::vector<Point> p1 = points;
            std::reverse(p1.begin(),p1.end());
            for(auto & p:p1) {
                p.t = 1-p.t;
            }
            return CCEaseCurve::create(_inner->reverse(), p1);
        }
        
        void CCEaseCurve::update(float time) {
            CC_UNUSED_PARAM(time);
            CCActionEase::update(calculate(time));
        }
        
        bool CCEaseCurve::init(CCActionIntervalPtr a, const std::vector<Point>& p) {
            if (CCActionEase::initWithAction(a)) {
                
                if (p.size() < 3) {
                    return false;
                }
                
                if (0 < p[0].t) {
                    return false;
                }
                
                if (p[p.size()-1].t < 1) {
                    return false;
                }
                
                float t0 = -1;
                for(auto & i:p) {
                    if (i.t <= t0) {
                        return false;
                    }
                    t0 = i.t;
                }
                
                points = p;
                
                return true;
            }
            return false;
        }
        
        void CCEaseCurve::test() {
            if (true)
            {
                std::vector<Point> p = {
                    {0,0},
                    {1,1}
                };
                std::vector<Point> p1;
                    //p1 = Point::generateZigZagWithDamping({.5,.5}, {.99,1}, .01, 0, .057, 0.9);
                p1 = Point::generateZigZagWithDamping({.5,.5}, {.9,1}, .0, 0, .1, 0.85);
                p.insert(p.begin()+1,p1.begin(),p1.end());
                CCEaseCurvePtr c = CCEaseCurve::create(aScaleBy(1,2),p);
                test(c);
                return;
            }
            if (true)
            {
                std::vector<Point> p = {
                    {0,0},
                    {1,.5}
                };
                std::vector<Point> p1 = Point::generateZigZagWithSpans({.5,1}, {.9,.5},.5,.1, 8);
                p.insert(p.begin()+1,p1.begin(),p1.end());
                CCEaseCurvePtr c = CCEaseCurve::create(aScaleBy(1,2),p);
                test(c);
                return;
            }
            auto test = [] (const char *name, CCEaseCurvePtr p0) {
                std::cout << "test: " << name << ", points=(";
                for(auto i:p0 -> points) {
                    std::cout << i;
                }
                std::cout << ')' << std::endl;
                std::vector<Point> values;
                values.resize(100);
                std::cout << '{';
                for(int i = 0; i < values.size(); i++) {
                    values[i].t = i/100.f;
                    values[i].v = p0->calculate(values[i].t);
                    if (0 < i) {
                        std::cout << ',';
                    }
                    std::cout << values[i];
                }
                std::cout << '}';
                std::cout << std::endl;
                std::cout << "test: " << name << std::endl;
            };
            
            {
                test("1",create(aScaleBy(1,2),.1f));
                test("2",create(aScaleBy(1,2),{.1,.5},{.9,.5}));
                test("3",create(aScaleBy(1,2),{{0,0},{.1,.8},{.9,.2},{1,1}}));
                test("4",create(aScaleBy(1,2),{{0,0},{.1,.8},{.3,.3},{.6,.6},{.9,.2},{1,1}}));
                test("5",create(aScaleBy(1,2),.5f));
            }
            std::cout.flush();
        }
        
        void CCEaseCurve::test(CCEaseCurvePtr p) {
            std::cout << "test: points={";
            char d = ' ';
            for(auto i:p -> points) {
                std::cout << d << i;
                d = ',';
            }
            std::cout << '}' << std::endl;
            std::vector<Point> values;
            values.resize(100);
            std::cout << '{';
            for(int i = 0; i < values.size(); i++) {
                values[i].t = i/100.f;
                values[i].v = p->calculate(values[i].t);
                if (0 < i) {
                    std::cout << ',';
                }
                std::cout << values[i];
            }
            std::cout << '}';
            std::cout << std::endl;
        }
        
        
        int CCEaseCurve::find0(float t) {
            auto compare = [] (const Point& A, const Point& B) -> bool {
                return A.t < B.t;
            };
            auto i = std::equal_range(points.begin(),points.end(),t,compare);
            if (i.first == points.end())
                return (int)points.size()-1;
            if (i.second == points.end())
                return 0;
            return (int)std::distance(i.first,i.second);
        }
        
        int CCEaseCurve::find(float t)
        {
            const int L = (int)points.size();
            for(int i = 1; i < L; i++) {
                if (t < points[i].t) {
                    return i-1;
                }
            }
            return L-1;
        }
        
        
        float CCEaseCurve::average (float v0, float v1, float t0, float t1, float t)
        {
            float T = t1 - t0;
            return v0 * ( (t1 - t) / T ) + v1 * ( (t - t0) / T );
        }
        
        float CCEaseCurve::average1 (float v0, float v1, float t0, float t1, float t)
        {
            float T = t1 - t0;
            return v0 * powf( (t1 - t) / T, 2. ) + v1 * powf( (t - t0) / T, 2. );
        }
        
        float CCEaseCurve::curve (const Point& p0, const Point& p1, const Point& p2, float t)
        {
            const float x = t;
            const float x1 = p0.t;
            const float y1 = p0.v;
            const float x2 = p1.t;
            const float y2 = p1.v;
            const float x3 = p2.t;
            const float y3 = p2.v;
            
            const float x1x1 = x1*x1;
            const float x2x2 = x2*x2;
            const float x3x3 = x3*x3;
            
                // f(t) = A t * t + B * t + C
                // A = [(Y2-Y1)(X1-X3) + (Y3-Y1)(X2-X1)] / [(X1-X3)(X2^2-X1^2) + (X2-X1)(X3^2-X1^2)]
                // B = [(Y2 - Y1) - A(X2^2 - X1^2)] / (X2-X1)
                // C = Y1 - AX1^2 - BX1
            
            const float _a = (x1-x3)*(x2x2-x1x1) + (x2-x1)*(x3x3-x1x1);
            const float a = ((y2-y1)*(x1-x3) + (y3-y1)*(x2-x1)) / _a;
            const float _b = (x2-x1);
            const float b = ((y2-y1) - a * (x2x2 - x1x1)) / _b;
            const float c = y1 - a * x1x1 - b * x1;
            
            const float r = a * x * x + b * x + c;
            
            return r;
        }
        
        int CCEaseCurve::classify (int n)
        {
            if (3 < points.size()) {
                return n == 0 ? 0 : n >= points.size()-1 ? 2 : 1;
            }
            else {
                return 0;
            }
        }
        
        float CCEaseCurve::calculate (const float t)
        {
            float r = 0;
            int n = find(t);
            int c = classify(n);
            switch(c) {
                case 0:
                    r = curve(points[0],points[1],points[2],t);
                    break;
                case 2:
                    r = curve(points[points.size()-3],points[points.size()-2],points[points.size()-1],t);
                    break;
                case 1:
                    if (t == points[n].t)
                    {
                        r = points[n].v;
                    }
                    else
                    {
                        if (t < points[n].t or points[n+1].t < t) {
                            std::cout << "bad t=" << t << " not between " << points[n].t << " and " << points[n+1].t << std::endl;
                        }
                        float v0 = curve(points[n-1],points[n],points[n+1],t);
                        float v1 = curve(points[n],points[n+1],points[n+2],t);
                        
                        r = average(v0,v1,points[n].t,points[n+1].t,t);
                    }
                    break;
            }
                //                std::cout << " calculate(" << t << ")=" << r << "/n=" << n << "/type=" << c << std::endl;
            return r;
        }
        
        
        
        
        
        
        
            // 8< ------------------------------------------------------
        
        
        CCRetainPtr CCRetain::create(CCObjectPtr o) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCRetain,{o});
        }
        
        CCRetainPtr CCRetain::create(const vector<CCObjectPtr>& o) {
            ccNewThenInitWithArgsAutoreleaseReturn(CCRetain,o);
        }
        
        void CCRetain::update(float time) {
            ccUnusedParameter(time);
        }
        
        
        bool CCRetain::init(vectorCRef(CCObjectPtr) p) {
            objects.reserve(p.size());
            for(auto o:p) {
                if (o) {
                    o -> retain();
                    objects.push_back(o);
                }
            }
            return true;
        }
        
        CCRetain::~CCRetain() {
            for(auto o:objects) {
                ccSafeReleaseNull(o);
            }
            objects.clear();
        }
        
        
        
        
        
        
        
            // 8< ------------------------------------------------------
        
        
        
        
        
        namespace Touch
        {
            
            void describe(CCTouchPtr touch)
            {
                CCPoint location = touch -> getLocationInView(); // location on screen
                tLog(" touch-location-in-view           :" << location);
                    //        CCPoint screen = touch -> getLocation(); // location in OpenGL view
                tLog(" touch-screen   (screen)(gl)      :" << location);
                CCPoint location1 = CCDirector::getInstance() -> convertToGL(touch -> getLocation());
                tLog(" touch-location (converted-to-gl) :" << location1);
                
                    //        tLog(" touch-screen->to-node            :" << convertToNodeSpace(screen)); // wrt anchor
                    //        tLog(" touch-screen->to-node->to-world  :" << convertToWorldSpace(convertToNodeSpace(screen)));
            }
            
            
            
            
            bool isSwipeLeft    (CCTouchPtr touch) { return  touch -> getLocationInView().x <= touch -> getPreviousLocationInView().x and touch -> getPreviousLocationInView().x < touch -> getStartLocationInView().x; }
            bool isSwipeRight   (CCTouchPtr touch) { return  touch -> getLocationInView().x >= touch -> getPreviousLocationInView().x and touch -> getPreviousLocationInView().x > touch -> getStartLocationInView().x; }
            bool isSwipeDown    (CCTouchPtr touch) { return  touch -> getLocationInView().y <= touch -> getPreviousLocationInView().y and touch -> getPreviousLocationInView().y < touch -> getStartLocationInView().y; }
            bool isSwipeUp      (CCTouchPtr touch) { return  touch -> getLocationInView().y >= touch -> getPreviousLocationInView().y and touch -> getPreviousLocationInView().y > touch -> getStartLocationInView().y; }
            
            
            
            CCData::CCData() {
                type = Type::Cancelled;
            }
            
            
            
            CCData::CCData(CCNodePtr view, CCTouchPtr touch, Type type)
            {
                this -> view = view;
                this -> type = type;
                pointInView = touch -> getLocationInView();
                pointOnScreen = view -> convertToWorldSpace(view -> convertToNodeSpace(touch -> getLocation()));
                ratioOnScreen = screenGetRatio(pointOnScreen);
                if (1)
                {
                    CCSize size = view -> getContentSize();
                    CCPoint p;
                    p = touch->getStartLocationInView();
                    this -> touch.setTouchInfo(touch->getID(),p.x,size.height-p.y);
                    p = touch->getPreviousLocationInView();
                    this -> touch.setTouchInfo(touch->getID(),p.x,size.height-p.y);
                    p = touch->getLocationInView();
                    this -> touch.setTouchInfo(touch->getID(),p.x,size.height-p.y);
                }
                else
                {
                    this -> touch = *touch;
                }
            }
            
            CCData::CCData(CCPoint pointOnScreen, Type type)
            {
                this -> type = type;
                this -> pointOnScreen = pointOnScreen;
                ratioOnScreen = screenGetRatio(pointOnScreen);
            }
            
            std::vector<CCData> CCData::create          (CCNodePtr view, vectorCRef(CCTouchPtr) touches, Type type)
            {
                std::vector<CCData> r;
                r.reserve(touches.size());
                for(autoCRef touch:touches)
                {
                    r.push_back(CCData(view,touch,type));
                }
                return r;
            }
            
            bool                CCData::isSlideInView  (float distance PIXELS) const
            {
                return distance < touch.getStartLocationInView().getDistance(touch.getLocationInView());
            }
            
            
            
            
            
            
            
            
            
            
            
            
            float CCLayer::getTimeOfLastTouch() const {
                return timeLastTouch;
            }
            
            
            CCLayerPtr CCLayer::create(bool touchEnabled) {
                ccNewThenInitWithArgsAutoreleaseReturn(CCLayer,touchEnabled);
            }
            
            
            bool CCLayer::init(bool touchEnabled) {
                if (cocos2d::Layer::init())
                {
                    setEnabledTouch(touchEnabled);
                    
                    return true;
                }
                return false;
            }
            
            bool CCLayer::init() {
                return init(true);
            }
            
            
            
            
            
            
            bool CCLayer::onTouchBegan(CCTouchPtr touch, CCEventPtr event)
            {
                    //describe(touch);
                CCPoint screen = convertToWorldSpace(convertToNodeSpace(touch->getLocation()));
                timeLastTouch = tiny::Time::now();
                    // NOTE: ONLY IF TRUE IS RETURNED WILL MOVED/ENDED EVENTS BE PROCESSED
                return touchProcess(touch,screen,Touch::Type::Began);
            }
            void CCLayer::onTouchMoved(CCTouchPtr touch, CCEventPtr event)
            {
                    //describe(touch);
                CCPoint screen = convertToWorldSpace(convertToNodeSpace(touch->getLocation()));
                timeLastTouch = tiny::Time::now();
                touchProcess(touch,screen,Touch::Type::Moved);
            }
            void CCLayer::onTouchEnded(CCTouchPtr touch, CCEventPtr event)
            {
                    //describe(touch);
                CCPoint screen = convertToWorldSpace(convertToNodeSpace(touch->getLocation()));
                timeLastTouch = tiny::Time::now();
                touchProcess(touch,screen,Touch::Type::Ended);
            }
            void CCLayer::onTouchCancelled(CCTouchPtr touch, CCEventPtr event)
            {
                    //describe(touch);
                CCPoint screen = convertToWorldSpace(convertToNodeSpace(touch->getLocation()));
                timeLastTouch = tiny::Time::now();
                touchProcess(touch,screen,Touch::Type::Cancelled);
            }
            
            
            void CCLayer::onTouchesBegan(vectorCRef(CCTouchPtr) touches, CCEventPtr event)
            {
                    //describe(touch);
                CCPoint screen = convertToWorldSpace(convertToNodeSpace(static_cast<CCTouchPtr>(*touches.begin())->getLocation()));
                timeLastTouch = tiny::Time::now();
                touchesProcess(touches,screen,Touch::Type::Began);
            }
            void CCLayer::onTouchesMoved(vectorCRef(CCTouchPtr) touches, CCEventPtr event)
            {
                    //describe(touch);
                CCPoint screen = convertToWorldSpace(convertToNodeSpace(static_cast<CCTouchPtr>(*touches.begin())->getLocation()));
                timeLastTouch = tiny::Time::now();
                touchesProcess(touches,screen,Touch::Type::Moved);
            }
            void CCLayer::onTouchesEnded(vectorCRef(CCTouchPtr) touches, CCEventPtr event)
            {
                    //describe(touch);
                CCPoint screen = convertToWorldSpace(convertToNodeSpace(static_cast<CCTouchPtr>(*touches.begin())->getLocation()));
                timeLastTouch = tiny::Time::now();
                touchesProcess(touches,screen,Touch::Type::Ended);
            }
            void CCLayer::onTouchesCancelled(vectorCRef(CCTouchPtr) touches, CCEventPtr event)
            {
                    //describe(touch);
                CCPoint screen = convertToWorldSpace(convertToNodeSpace(static_cast<CCTouchPtr>(*touches.begin())->getLocation()));
                timeLastTouch = tiny::Time::now();
                touchesProcess(touches,screen,Touch::Type::Cancelled);
            }
            
            
            bool CCLayer::touchProcess (CCTouchPtr touch, CCPoint screen, Touch::Type type) {
                bool r = false;
                    //        tLog("touch-targets: " << listOfTouchTargetAndCallback.size());
                for(auto & e:listOfTouchTargetAndCallback) {
                        //            tLog("touch-target: " << e.first);
                    if (containsLocationOfTouch(e.first,screen)) {
                        if (e.second(touch,screen,type)) {
                            r = true;
                            break;
                        }
                    }
                }
                return r;
            }
            
            bool CCLayer::touchesProcess (vectorCRef(CCTouchPtr) touches, CCPoint screen, Touch::Type type) {
                bool r = false;
                    //        tLog("touch-targets: " << listOfTouchTargetAndCallback.size());
                for(auto & e:listOfTouchesTargetAndCallback) {
                        //            tLog("touch-target: " << e.first);
                    if (containsLocationOfTouch(e . first, screen)) {
                        r = true;
                        if (e . second(touches,screen,type)) {
                            break;
                        }
                    }
                }
                return r;
            }
            
            bool CCLayer::containsLocationOfTouch(CCNodePtr node, CCPoint screen) {
                bool R = false;
                if (node) {
                    CCPoint p = node -> convertToNodeSpace(screen);
                    CCRect r;
                    r.size = node -> getContentSize();
                    R = r.containsPoint(p);
                        //                    std::cout << "containsLocationOfTouch: R = " << R << ", p = " << p << ", r = " << r << std::endl;
                }
                return R;
            }
            
            void CCLayer::addTouchCallback(CCNodePtr node, const TouchCallback& f) {
                if (node and f) {
                        // NOTE: TouchCallback is a std::function.  std::function has no == operator (ie you can't compare if two std::functions are equal)
                        //       Therefore, we need to associate a callback with a node, hence the CCNodePtr parameter.
                    listOfTouchTargetAndCallback.push_back({node,f});
                }
            }
            
            void CCLayer::removeTouchCallback(CCNodePtr node) {
                if (node) {
                    erase_if(listOfTouchTargetAndCallback,
                             [node](const std::pair<CCNodePtr,TouchCallback>& p) { return p.first == node; });
                }
            }
            
            
            void CCLayer::addTouchesCallback(CCNodePtr node, const TouchesCallback& f) {
                if (node and f) {
                        // NOTE: TouchCallback is a std::function.  std::function has no == operator (ie you can't compare if two std::functions are equal)
                        //       Therefore, we need to associate a callback with a node, hence the CCNodePtr parameter.
                    listOfTouchesTargetAndCallback.push_back({node,f});
                }
            }
            
            void CCLayer::removeTouchesCallback(CCNodePtr node) {
                if (node) {
                    erase_if(listOfTouchesTargetAndCallback,
                             [node](const std::pair<CCNodePtr,TouchesCallback>& p) { return p.first == node; });
                }
            }
            
            
            
            
            
            void CCLayer::onAccelerate  (CCAccelerationPtr p)
            {
                    // empty
            }
            
            
            
            
            
            ______  void       CCLayer::setEnabledTouch                         (bool flag)
            {
                if (not listener.touch)
                {
                    listener.touch = EventListenerTouchOneByOne::create();
                    listener.touch->setSwallowTouches(true);
                    listener.touch->onTouchBegan = CC_CALLBACK_2(CCLayer::onTouchBegan, this);
                    listener.touch->onTouchMoved = CC_CALLBACK_2(CCLayer::onTouchMoved, this);
                    listener.touch->onTouchEnded = CC_CALLBACK_2(CCLayer::onTouchEnded, this);
                    listener.touch->retain();
                    
                    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener.touch, this);
                }
                
                listener.touch->setEnabled(flag);
            }
            
            
            ______  void        CCLayer::setEnabledTouches                       (bool flag)
            {
                tAssert(0);
            }
            
            
            ______  void        CCLayer::setEnabledAcceleration                  (bool flag)
            {
                tAssert(0);
            }
            

            
            
            
            
            
            
            CCLayer::~CCLayer()
            {
                ccSafeReleaseNull(listener.touch);
            }
            
            
            
            
            
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        CCRepeatForeverPtr      aLoop        (CCNodePtr n, std::function<bool ()> condition, std::function<void ()> cargo, bool positive)
        {
            auto a = aForever(aiEmpty());
            a->setInnerAction(aiCall([a,n,condition,cargo,positive]
                                     {
                                         if (positive==condition()) {
                                             n->stopAction(a);
                                         }
                                         else
                                         {
                                             cargo();
                                         }
                                     }));
            return a;
        }
        
        CCRepeatForeverPtr      aLoop        (CCNodePtr n, std::function<bool ()> condition, bool positive)
        {
            auto a = aForever(aiEmpty());
            a->setInnerAction(aiCall([a,n,condition,positive]
                                     {
                                         if (positive==condition()) {
                                             n->stopAction(a);
                                         }
                                     }));
            return a;
        }

        
        
        
        
        
        
        
        
        CCRepeatForeverPtr      aWhen        (CCNodePtr n, std::function<bool ()> condition, std::function<void ()> cargo, bool positive)
        {
            auto a = aForever(aiEmpty());
            a->setInnerAction(aiCall([a,n,condition,cargo,positive]
                                     {
                                         if (positive==condition()) {
                                             cargo();
                                             n->stopAction(a);
                                         }
                                     }));
            return a;
        }
        

        
        
        
        
        
        
        
        void             ccPurge                  (bool textures, bool frames)
        {
            if (frames)     {CCSpriteFrameCache::getInstance() -> removeUnusedSpriteFrames();}
            if (textures)   {CCTextureCache::getInstance() -> removeUnusedTextures();}
        }

        
        
        
        
        
        CCActionInterval *   aSwayBy     (float t, float r)
        {
            return aSequence({
                eSineInOut(aRotateBy(t,-r)),
                eSineInOut(aRotateBy(t,+r)),
            });
        }

        
        
        
        
        
        
        
        
    } // namespace Cocos2D
    
} // namespace tiny


