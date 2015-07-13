
#import "tinyCocos2DSpritesheet.h"

#import "tinyApplication.h"





namespace tiny
{
    namespace Cocos2D
    {
        
        
        
        
        
        
        
        void CCSpritesheet::Product::addToCache()
        {
            if (not added)
            {
                tAssert(valid);
                
                CCSpriteFrameCachePtr cache = CCSpriteFrameCache::getInstance();
                
                if (valid)
                {
                    cache -> addSpriteFramesWithDictionary (dictionary, texture);
                    
                    added = true;
                }
                else
                {
                    string n = name + ".plist";
                    
                    std::string fullPath = tiny::Application::IO::pathInDocumentsFolder(n); //CCFileUtils::sharedFileUtils()->fullPathForFilename(c);
                    
                        //            ValueMap *dict = ValueMap::createWithContentsOfFileThreadSafe(c);
                        //            _____cache -> addSpriteFramesWithDictionary(dict, p.texture);
                    cache -> addSpriteFramesWithFile(fullPath, texture);
                        //            dict->release();
                    added = true;
                }
            }
        }
        
        
        
        
        
//        CCSpriteBatchNodePtr CCSpritesheet::Product::createSpriteBatchNode(int elements)
        CCNodePtr CCSpritesheet::Product::createSpriteBatchNode(int elements)
        {
            tAssert(valid);
            addToCache();
//            return CCSpriteBatchNode::createWithTexture(texture,elements);
            return CCNode::create(); //CCSpriteBatchNode::createWithTexture(texture,elements);
        }
        
        
        
        
        
        bool CCSpritesheet::isDuplicateName(const string& p)
        {
            for(auto & e:data.elements) {
                if (e.name == p)
                    return true;
            }
            return false;
        }

        
        
        bool CCSpritesheet::removeDuplicates(const string& p)
        {
            return erase_if(data.elements,[p] (ElementCRef e) {
                return e.name == p;
            });
        }
        

        
        
        
        
        
        bool CCSpritesheet::frameAddEmpty (string name)
        {
            if (name.empty()) { return false; }
            
            
            Element e;
            
            e.name = nameGet(name);
            
            
            if (policy.removeExistingDuplicates)
            {
                removeDuplicates(e.name);
            }
            else if (policy.skipNewDuplicates and isDuplicateName(e.name))
            {
                return false;
            }
            
            
            e.texture = ccSprite("image-empty.png") -> getTexture();
            e.texture -> retain();
            
            tLog("frameAdd (empty): id="<<e.texture->_ID<<",name="<<name<<",content="<<e.texture->getContentSizeInPixels());
            
            data.elements.push_back(e);
            data.empty = e.name;
            return true;
        }
        
        
        
        bool CCSpritesheet::frameAdd (string name)
        {
            if (name.empty()) { return false; }
            
            
            Element e;
            
            e.name = nameGet(name);

            
            if (policy.removeExistingDuplicates)
            {
                removeDuplicates(e.name);
            }
            else if (policy.skipNewDuplicates and isDuplicateName(e.name))
            {
                return false;
            }

            
            e.texture = ccSprite(name) -> getTexture();
            
            e.texture -> retain();
            
            tLog("frameAdd (): id="<<e.texture->_ID<<",name="<<name<<",content="<<e.texture->getContentSizeInPixels());
            
            data.elements.push_back(e);
            
            return true;
        }
        
        
        
        bool CCSpritesheet::frameAdd (string name, float scale, Color4F fill)
        {
            if (name.empty()) { return false; }
            
            
            Element e;
            
            e.name = nameGet(name);
            
            
            if (policy.removeExistingDuplicates)
            {
                removeDuplicates(e.name);
            }
            else if (policy.skipNewDuplicates and isDuplicateName(e.name))
            {
                return false;
            }
            
            
            if (scale != 1)
            {
                    // MUST RECREATE ORIGINAL TEXTURE BECAUSE SPRITE TEXTURE IS Y-AXIS FLIPPED
                auto p = ccSprite(name);
                
                ccScaleXY(p,scale,scale);
                
                float w = ccWidthScaled (p);
                float h = ccHeightScaled(p);
                
                ccFlipY(p,true);
                
                p -> setAnchorPoint    (Vec2(.5,.5));
                p -> setPosition       (Vec2(w/2.,h/2.));
                
                auto r = ccRenderWithFunction(CCSize(w,h),fill,[this,p]
                                              {
                                                  p -> visit();
                                              });
                
                e.texture = r -> getTexture();
            }
            else
            {
                e.texture = ccSprite(name) -> getTexture();
            }
            
            e.texture -> retain();
            
            tLog("frameAdd (name+scale): id="<<e.texture->_ID<<",name="<<name<<",content="<<e.texture->getContentSizeInPixels());
            
            data.elements.push_back(e);
            
            return true;
        }
        
        
        
        bool CCSpritesheet::frameAdd (string name, CCSpritePtr p, Color4F fill)
        {
            if (name.empty()) { return false; }
            
                //tLog("frameAdd (sprite): id="<<p->_ID<<",name="<<name<<",references="<<p->retainCount()<<",content="<<p->getTexture()->getContentSizeInPixels());
            Element e;
            
            e.name = nameGet(name);
            
            
            if (policy.removeExistingDuplicates)
            {
                removeDuplicates(e.name);
            }
            else if (policy.skipNewDuplicates and isDuplicateName(e.name))
            {
                return false;
            }
            
            
            
            if (1)
            {
                auto    a = p -> getAnchorPoint();
                auto    l = ccPosition(p);
                auto    s = ccScaleXY(p);
                float   w = ccWidthScaled(p);
                float   h = ccHeightScaled(p);
                
                ccFlipY(p,true);

                p -> setAnchorPoint    (Vec2(.5,.5));
                p -> setPosition       (Vec2(w/2.,h/2.));
                
                auto r      = ccRenderWithFunction(CCSize(w,h),fill,[this,p]
                                                   {
                                                       p -> visit();
                                                   });
                
                e.texture = r -> getTexture();
                
                p -> setAnchorPoint(a);
                
                ccPosition(p,l);
                
                tLog("frameAdd (sprite): (w,h)=("<<w<<','<<h<<"), content-size="<<p->getTexture()->getContentSizeInPixels());
            }
            else
            {
                e.texture = p -> getTexture();
            }
            
            e.texture -> retain();
            
            data.elements.push_back(e);
            
            return true;
        }
        
        
        
        bool CCSpritesheet::frameAdd (string name, CCTexture2DPtr p)
        {
            if (name.empty()) { return false; }
            
            
            Element e;
            
            e.name = nameGet(name);
            
            
            if (policy.removeExistingDuplicates)
            {
                removeDuplicates(e.name);
            }
            else if (policy.skipNewDuplicates and isDuplicateName(e.name))
            {
                return false;
            }
            
            
            
            if (not p)
            {
//                tLog("name="<<name);
                auto sprite = ccSprite(name);
                p = sprite->getTexture();
            }
            
            tLog("frameAdd (texture): id="<<p->_ID<<",name="<<name<<",content="<<p->getContentSizeInPixels());
            
            e.texture = p;
            e.texture -> retain();
            data.elements.push_back(e);
            
            return true;
        }
        
        
        
        
        
        
        
        CCSpritesheet::~CCSpritesheet()
        {
            clear();
        }
        
        
        
        
        
        
        
        string CCSpritesheet::write(string name, CCSize size, const std::vector<Element>& elements)
        {
            if (0)
            {
                for(auto e:elements) {
                    tDebug( io::saveToFilePNG(CCSprite::createWithTexture(e.texture),"test-texture--"+e.name); );
                }
            }
            
            stringstream ss;
            
            ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            ss << "\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" ;
            ss << "\n<plist version=\"1.0\">" ;
            
            ss << "\n<dict>" ;
            
            ss << "\n <key>frames</key>" ;
            ss << "\n  <dict>" ;
            
                //ss << "   <key>framename.png</key> " ;
                //ss << "   <dict> " ;
                //ss << "    <key>aliases</key> <array/> " ;
                //ss << "    <key>spriteColorRect</key>    <string>{{0, 0}, {44, 53}}</string> " ;
                //ss << "    <key>spriteOffset</key>       <string>{0, -0}</string> " ;
                //ss << "    <key>spriteSize</key>         <string>{44, 53}</string> " ;
                //ss << "    <key>spriteSourceSize</key>   <string>{44, 53}</string> " ;
                //ss << "    <key>spriteTrimmed</key>      <true/> " ;
                //ss << "    <key>textureRect</key>        <string>{{90, 0}, {44, 53}}</string> " ;
                //ss << "    <key>textureRotated</key>     <false/> " ;
                //ss << "   </dict>" ;
            
            auto f2 = [] (int a, int b) {
                return tiny::to_string("{",a,", ",b,"}");
            };
            
            auto ff = [this,f2] (stringstream& ss, ElementCRef e)
            {
                string origin = f2((int)e.rect.origin.x,(int)e.rect.origin.y);
                string size = f2((int)e.rect.size.width,(int)e.rect.size.height);
                
                ss << "\n   <key>" << e.name << "</key> " ;
                ss << "\n   <dict> " ;
                ss << "\n    <key>aliases</key> <array/> " ;
                ss << "\n    <key>spriteColorRect</key>    <string>{{0, 0}, " << size << "}</string> " ;
                ss << "\n    <key>spriteOffset</key>       <string>{0, 0}</string> " ;
                ss << "\n    <key>spriteSize</key>         <string>" << size << "</string> " ;
                ss << "\n    <key>spriteSourceSize</key>   <string>" << size << "</string> " ;
                ss << "\n    <key>spriteTrimmed</key>      <true/> " ;
                ss << "\n    <key>textureRect</key>        <string>{" << origin << ", " << size << "}</string> " ;
                ss << "\n    <key>textureRotated</key>     <false/> " ;
                ss << "\n   </dict>" ;
            };
            
            for(auto & e:elements) {
                ff(ss,e);
            }
            
            ss << "\n  </dict>" ;
            
            ss << "\n <key>metadata</key> " ;
            ss << "\n <dict> " ;
            ss << "\n  <key>version</key>              <string>1.5.5</string> " ;
            ss << "\n  <key>format</key>               <integer>3</integer> " ;
            ss << "\n  <key>size</key>                 <string>" << f2(size.width,size.height) << "</string> " ;
            ss << "\n  <key>name</key>                 <string>" << name << "</string> " ;
            ss << "\n  <key>premultipliedAlpha</key>   <false/> " ;
            ss << "\n  <key>target</key> " ;
            ss << "\n   <dict> " ;
            ss << "\n    <key>name</key>                        <string>default</string> " ;
            ss << "\n    <key>textureFileName</key>             <string>" << name << "</string> " ;
            ss << "\n    <key>textureFileExtension</key>        <string>.png</string> " ;
            ss << "\n    <key>coordinatesFileName</key>         <string>" << name << "</string> " ;
            ss << "\n    <key>coordinatesFileExtension</key>    <string>.plist</string> " ;
            ss << "\n    <key>premultipliedAlpha</key>          <false/> " ;
            ss << "\n   </dict> " ;
            ss << "\n </dict> " ;
            
            ss << "\n</dict> " ;
            
            ss << "\n</plist> " ;
            
            string content = ss.rdbuf()->str();
            
            tLog("xml contents=\n\n"+content);
            
            bool r = tiny::Application::IO::writeToFilenameInDocumentsFolder(name+".plist",content,true);
            
            return r ? content : "";
        }
        
        
        std::pair<ValueMap,bool> CCSpritesheet::dictionaryCreate(string name, CCSize size, const std::vector<Element>& elements)
        {
            if (0)
            {
                for(auto e:elements) {
                    tDebug( io::saveToFilePNG(CCSprite::createWithTexture(e.texture),"test-texture--"+e.name); );
                }
            }
            
            ValueMap r;
            
            ValueMap FRAMES;
            
            auto f2 = [] (int a, int b) {
                return tiny::to_string("{",a,", ",b,"}");
            };
            
            
                //                ss << "\n   <key>" << e.name << "</key> " ;
                //                ss << "\n   <dict> " ;
                //                ss << "\n    <key>aliases</key> <array/> " ;
                //                ss << "\n    <key>spriteColorRect</key>    <string>{{0, 0}, " << size << "}</string> " ;
                //                ss << "\n    <key>spriteOffset</key>       <string>{0, 0}</string> " ;
                //                ss << "\n    <key>spriteSize</key>         <string>" << size << "</string> " ;
                //                ss << "\n    <key>spriteSourceSize</key>   <string>" << size << "</string> " ;
                //                ss << "\n    <key>spriteTrimmed</key>      <true/> " ;
                //                ss << "\n    <key>textureRect</key>        <string>{" << origin << ", " << size << "}</string> " ;
                //                ss << "\n    <key>textureRotated</key>     <false/> " ;
                //                ss << "\n   </dict>" ;
            
            for(auto & e:elements)
            {
                string origin   = f2((int)e.rect.origin.x,(int)e.rect.origin.y);
                string size     = f2((int)e.rect.size.width,(int)e.rect.size.height);
                
                ValueMap FRAME;
                
                FRAME["aliases"]            = ValueVectorNull;
                FRAME["spriteColorRect"]    = Value("{{0,0},"+size+"}");
                FRAME["spriteOffset"]       = Value("{0,0}");
                FRAME["spriteSize"]         = Value(size);
                FRAME["spriteSourceSize"]   = Value(size);
                FRAME["spriteTrimmed"]      = Value(true);
                FRAME["textureRect"]        = Value("{"+origin+","+size+"}");
                FRAME["textureRotated"]     = Value(false);
                
                FRAMES[e.name]              = FRAME;
            }
            
            r["frames"] = FRAMES;
            
            ValueMap METADATA;
            
                //            ss << "\n  </dict>" ;
            
                //            ss << "\n <key>metadata</key> " ;
                //            ss << "\n <dict> " ;
                //            ss << "\n  <key>version</key>              <string>1.5.5</string> " ;
                //            ss << "\n  <key>format</key>               <integer>3</integer> " ;
                //            ss << "\n  <key>size</key>                 <string>" << f2(size.width,size.height) << "</string> " ;
                //            ss << "\n  <key>name</key>                 <string>" << name << "</string> " ;
                //            ss << "\n  <key>premultipliedAlpha</key>   <false/> " ;
                //            ss << "\n  <key>target</key> " ;
                //            ss << "\n   <dict> " ;
                //            ss << "\n    <key>name</key>                        <string>default</string> " ;
                //            ss << "\n    <key>textureFileName</key>             <string>" << name << "</string> " ;
                //            ss << "\n    <key>textureFileExtension</key>        <string>.png</string> " ;
                //            ss << "\n    <key>coordinatesFileName</key>         <string>" << name << "</string> " ;
                //            ss << "\n    <key>coordinatesFileExtension</key>    <string>.plist</string> " ;
                //            ss << "\n    <key>premultipliedAlpha</key>          <false/> " ;
                //            ss << "\n   </dict> " ;
                //            ss << "\n </dict> " ;
            
            METADATA["version"]                     = Value("1.5.5");
            METADATA["format"]                      = Value("3");
            METADATA["size"]                        = Value(f2(size.width,size.height));
            METADATA["name"]                        = Value(name);
            METADATA["premultipliedAlpha"]          = Value(false);
            
            if (1)
            {
                ValueMap TARGET;
                
                TARGET["name"]                      = Value("default");
                TARGET["textureFileName"]           = Value(name);
                TARGET["textureFileExtension"]      = Value(".png");
                TARGET["coordinatesFileName"]       = Value(name);
                TARGET["coordinatesFileExtension"]  = Value(".plist");
                TARGET["premultipliedAlpha"]        = Value(false);
                
                METADATA["target"] = TARGET;
            }
            
            r["metadata"] = METADATA;
            
            
                //            ss << "\n</dict> " ;
            
                //            ss << "\n</plist> " ;
            
                //            string content = ss.rdbuf()->str();
            
                //            tLog("xml contents=\n\n"+content);
            
                //            bool r = tiny::Application::IO::writeToFilenameInDocumentsFolder(name+".plist",content,true);
            
                //            return r ? content : "";
            
            return {r,true};
        }
        
        
        
        void CCSpritesheet::produce(ProductRef p, string name, Color4F fill)
        {
                // create texture
                //  determine if better to stack horizontally or vertically
                //  for each frame added
                //   sort based on size
                //
                // create plist file for texture
                //  encode
            
            float totalWidths   = 0;
            float maxWidth      = 0;
            float totalHeights  = 0;
            float maxHeight     = 0;
            
            for(auto & e:data.elements)
            {
                float w = e.texture -> getPixelsWide();
                float h = e.texture -> getPixelsHigh();
                
                totalWidths     += w;
                totalHeights    += h;
                
                maxHeight       = std::max(maxHeight,h);
                maxWidth        = std::max(maxWidth,w);
                
                e.rect          = CCRect();
            }
            
            
            CCSize      size;
            
            bool        horizontal      = totalWidths < totalHeights;
            
            auto        elements        = data.elements;
            
            const int   limit           = 4096;
            
            
            if (horizontal)
            {
                    // sort by height
                struct Sort {
                    inline bool operator () (ElementCRef a, ElementCRef b) const {
                        return a.texture -> getPixelsHigh() > b.texture -> getPixelsHigh();
                    }
                } sort;
                
                std::sort(elements.begin(),elements.end(),sort);
                
                CCRect      last;
                float       margin          = 0;
                float       h0              = 0;
                float       w1              = 0;
                float       y0              = 0;
                bool        first           = true;
                
                for(auto & e:elements)
                {
                    if (not first)
                        margin = 2;
                    else
                        first = false;
                    
                    e.rect.origin.x             = last.origin.x + last.size.width + margin;
                    e.rect.origin.y             = y0;
                    e.rect.size.width           = e.texture -> getPixelsWide();
                    e.rect.size.height          = e.texture -> getPixelsHigh();
                    
                    if (limit < (e.rect.origin.x + e.rect.size.width))
                    {
                        y0                  += h0 + margin;
                        e.rect.origin.x     = 0;
                        e.rect.origin.y     = y0;
                        h0                  = 0;
                    }
                    if (h0 < e.rect.size.height)
                    {
                        h0 = e.rect.size.height;
                    }
                    if (w1 < (e.rect.origin.x + e.rect.size.width))
                    {
                        w1 = e.rect.origin.x + e.rect.size.width;
                    }
                    
                    last = e.rect;
                    
                    tLog("h pack frame="<<e.name<<",rect="<<e.rect);
                }
                
                size.width  = w1;
                size.height = y0+h0;
            }
            else
            {
                struct Sort {
                    inline bool operator () (ElementCRef a, ElementCRef b) const {
                        return a.texture -> getPixelsWide() > b.texture -> getPixelsWide();
                    }
                } sort;
                
                std::sort(elements.begin(),elements.end(),sort);
                
                CCRect  last;
                float   margin  = 0;
                float   x0      = 0;
                float   w0      = 0;
                float   h1      = 0;
                bool    first   = true;
                
                for(auto & e:elements)
                {
                    if (not first)
                        margin = 2;
                    else
                        first = false;
                    
                    e.rect.origin.y         = last.origin.y + last.size.height + margin;
                    e.rect.origin.x         = x0;
                    e.rect.size.width       = e.texture -> getPixelsWide();
                    e.rect.size.height      = e.texture -> getPixelsHigh();
                    
                    if (limit < (e.rect.origin.y + e.rect.size.height))
                    {
                        x0                  += w0 + margin;
                        e.rect.origin.y     = 0;
                        e.rect.origin.x     = x0;
                        w0                  = 0;
                    }
                    if (w0 < e.rect.size.width)
                    {
                        w0 = e.rect.size.width;
                    }
                    if (h1 < (e.rect.origin.y + e.rect.size.height))
                    {
                        h1 = e.rect.origin.y + e.rect.size.height;
                    }
                    
                    last = e.rect;
                    
                    tLog("v pack frame="<<e.name<<",rect="<<e.rect);
                }
                
                size.height = h1;
                size.width  = x0+w0;
            }
            
            
            tLog("creating spritesheet with dimensions="<<size);
            
            
            p.name                      = name;

            if (1)
            {
                auto r = ccRenderWithFunctionToFilePNG(size,fill,"spritesheet-product-"+p.name+"-rendertexture.png",[this,&elements,size]
                {
                        // NOTES:
                        // -PROBLEM: SOME NODES ARE NOT DRAWN, SPECIFICALLY THOSE THAT ARE OUTSIDE OF "SCREEN BOUNDS" (1136X640)
                        // -SOLVED! DISABLED CULLING WITH 'CC_USE_CULLING' SET TO 0 IN base/CCConfig.h
                    
                    for(autoCRef e:elements)
                    {
                        auto s = ccSprite(e.texture);
                        if (1)
                        {
                            bool    pma = s->getTexture()->hasPremultipliedAlpha();
                            auto    src = s->getBlendFunc().src;
                            auto    dst = s->getBlendFunc().dst;
                            tLog("CCSpritesheet::produce: element.name="<<e.name<<", pma="<<pma<<", blend={"<<src<<','<<dst<<'}');
                        }
                        ccPosition  (s,e.rect.origin+e.rect.size/2);
                        ccSize      (s,e.rect.size);
                            // NOTE: EVERY ELEMENT OF A TEXTURE MUST BE Y-FLIPPED!
                        s->setScale (1,-1);
                        s->visit    ();
                    }
                });
                
                p.texture = r -> getTexture();
            }
            
            tDebug( { io::saveToFilePNG(ccSprite(p.texture), "spritesheet-product-"+p.name+".png"); } );
            
            p.elements                  = (int)elements.size();
            
            tie(p.dictionary,p.valid)   = dictionaryCreate (name,size,elements);
            
        }
        
        
        void CCSpritesheet::clear()
        {
            for(auto & e:data.elements) {
                    // tLog("releasing: id="<<e.texture->_ID<<",name="<<e.name<<",references="<<e.texture->retainCount());
                ccSafeReleaseNull(e.texture);
            }
            data.elements.clear();
        }
        
        
        
        
        
        
        
        
        
    }
}
