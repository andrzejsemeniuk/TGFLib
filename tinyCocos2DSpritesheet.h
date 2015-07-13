    //
    //  tinyCocos2DTexture.h
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 3/3/14.
    //
    //

#pragma once

#import "tinyCocos2D.h"

namespace tiny
{
    namespace Cocos2D
    {

        
        using namespace std;
        using namespace cocos2d;
        using namespace tiny;
        using namespace tiny::Cocos2D;
        
        
        
        STRUCT (CCSpritesheet)
        {
            virtual bool frameAddEmpty(string name);
            
            virtual bool        frameAdd            (string name);
            virtual bool        frameAdd            (string name, float scale, Color4F fill = {1,1,1,0});
            virtual bool        frameAdd            (string name, CCSpritePtr p, Color4F fill = {1,1,1,0});
            virtual bool        frameAdd            (string name, CCTexture2DPtr p);
            inline  bool        frameAdd            (pair<string,CCTexture2DPtr> p) { return frameAdd(p.first,p.second); }
            inline  void        framesAdd           (vectorCRef(pair<string,CCSpritePtr>) entries) { for(autoRef e:entries) frameAdd(e.first,e.second); }
            inline  void        framesAdd           (setCRef(pair<string,CCSpritePtr>) entries) { for(autoRef e:entries) frameAdd(e.first,e.second); }
            inline  void        framesAdd           (vectorCRef(pair<string,CCTexture2DPtr>) entries) { for(autoRef e:entries) frameAdd(e.first,e.second); }
            inline  void        framesAdd           (setCRef(pair<string,CCTexture2DPtr>) entries) { for(autoRef e:entries) frameAdd(e.first,e.second); }
            inline  void        framesAdd           (vectorCRef(string) entries) { for(autoRef e:entries) frameAdd(e); }
            inline  void        framesAdd           (setCRef(string) entries) { for(autoRef e:entries) frameAdd(e); }
            inline  void        framesAdd           (vectorCRef(string) entries, float scale, Color4F fill = {1,1,1,0}) { for(autoRef e:entries) frameAdd(e,scale,fill); }
            inline  void        framesAdd           (setCRef(string) entries, float scale, Color4F fill = {1,1,1,0}) { for(autoRef e:entries) frameAdd(e,scale,fill); }
            
            inline string       nameEmpty           () const { return data.empty; }
            inline CCSpritePtr  spriteCreateEmpty   () const { return CCSprite::createWithSpriteFrameName(nameEmpty()); }
            
            inline string       prefixGet           () const { return data.prefix; }
            inline string       nameGet             (string name) const { return data.prefix+name;}
            
            STRUCT (Product)
            {
                CCTexture2DPtr                  texture         = 0;
                int                             elements        = 0;
                std::string                     name;
                std::string                     content;
                ValueMap                        dictionary;
                bool                            valid           = false;
                
                CCNodePtr                       createSpriteBatchNode  (int elements);
                
            protected:
                bool                added          = false;
                void                addToCache     ();
            };
            
            ______                  CCSpritesheet           () {}
            ______                  CCSpritesheet           (string p) { data.prefix = p; }
            
            virtual                 ~CCSpritesheet  ();
            
            virtual void            produce             (ProductRef p, string name, Color4F fill = {1,1,1,0});
            
            inline Product produce(string name, Color4F fill = {1,1,1,0} ) {
                Product r;
                produce(r,name,fill);
                return r;
            }
            
            void clear();
            
            struct {
                bool removeExistingDuplicates   = true;
                bool skipNewDuplicates          = true;
            } policy;
            
        protected:
            
            STRUCT (Element)
            {
                std::string                 name;
                CCTexture2DPtr              texture             = 0;
                CCRect                      rect;
            };
            
            std::string                     write               (string filename, CCSize size, const std::vector<Element>& elements);
            std::pair<ValueMap,bool>        dictionaryCreate    (string name, CCSize size, const std::vector<Element>& elements);
            
            bool                            isDuplicateName     (const string& p);
            bool                            removeDuplicates    (const string& p);

            struct
            {
                string                      prefix;
                string                      empty;
                std::vector<Element>        elements;
            } data;
            
            
        };
       
        
        
        
    }
}