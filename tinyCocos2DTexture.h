    //
    //  tinyCocos2DTexture.h
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 3/3/14.
    //
    //

#pragma once

#import "tinyCocos2D.h"
#import "tinyCocos2DOperator.h"

namespace tiny
{
    namespace Cocos2D
    {
        namespace Texture
        {

            struct Descriptions;
            
            STRUCT (Description)
            {

                holder_i                        type                        = {0,false};
                
                holder<CCRelative>              relative                    = {CCRelative::ToRoot,false};
                
                CCOperators                     operators;
                CCSpritePtr                     sprite                      = 0;
                
                
                
                ______                          Description                 () {}
                ______                          Description                 (CCOperators o);
                ______                          Description                 (int t);
                ______                          Description                 (int t, CCOperators o);
                ______                          Description                 (int t, CCRelative rel, CCOperators o);
               
                inline  DescriptionRef          add                         (CCOperator o)                  { operators.add({o}); return *this; }
                inline  DescriptionRef          add                         (CCOperators o)                 { operators.add(o); return *this; }
                inline  DescriptionRef          insert                      (CCOperator o, int i = 0)       { operators.insert(o,i); return *this; }
                inline  DescriptionRef          insert                      (CCOperators o, int i = 0)      { operators.insert(o,i); return *this; }
                inline  DescriptionRef          operator +=                 (CCOperator o)                  { return add(o); }
                inline  DescriptionRef          operator +=                 (CCOperators o)                 { return add(o); }
                friend  std::ostream&           operator <<                 (std::ostream& o, DescriptionCRef p);
                
                typedef CCOperators Fluctuation;
                
                ______  Description             afterAddFluctuation         (Fluctuation f) const;
                
                virtual void                    apply                       (CCSpritePtr s);
                
                inline  void                    apply                       ()                              { if (sprite) apply(sprite); }
                
                static  vector<Description>     createByAngle               (CCAngle angle0, CCAngle angle1, CCAngle angleDelta, CCOperators o = {});
                static  vector<Description>     createByAngle               (vector<CCAngle> angles, CCOperators o = {});

                static  vector<Description>     createWithTexture           (CCTexture2DPtr t, vectorCRef(Description) p);
                static  vector<Description>     createWithTextures          (vectorCRef(pair<CCTexture2DPtr,Description>) p);
                static  vector<Description>     createWithFunction          (std::function<CCSpritePtr (DescriptionCRef)> f, vector<Description> p);

                
                STRUCT (Group)
                {
                    std::vector<DescriptionPtr> descriptions;
                    
                    ______                      Group                       ()                          {}
                    ______                      Group                       (vectorRef(Description) p)  { descriptions.reserve(p.size()); for(autoRef e:p) { descriptions.push_back(& e); } }
                   
                    inline void                 add                         (CCOperator o)              { for(auto e:descriptions) e->add(o); }
                    inline void                 add                         (CCOperators o)             { for(auto e:descriptions) e->add(o); }
                    
                    inline void                 apply                       (CCOperators o)             { for(autoRef d:descriptions) o.applyToSprite(d->sprite); }
                };
                
                
            };
            
            

            
            STRUCT (Descriptions)
            {
                vector<Description> descriptions;
                
                
                friend std::ostream& operator << (std::ostream& o, DescriptionsCRef p);
                
                
                ______          Descriptions    () {}
                ______          Descriptions    (vectorCRef(Description) p) : descriptions(p)   {}
                
                
                inline void     createByAngle   (vector<CCAngle> angles, CCOperators o = {})    { descriptions = Description::createByAngle(angles,o); }
                
                inline void     add             (Description p)             { descriptions.push_back(p); }
                inline void     remove          (int type)                  { for(auto i = begin(descriptions); i != end(descriptions); ) if (i->type==type) { i = descriptions.erase(i); } else { i++; }; }
                inline void     apply           (std::function<void (DescriptionRef)> f) { for(autoRef e:descriptions) { f(e); } }
                
                
                inline void     add             (CCOperator o)              { for(autoRef e:descriptions) e.add(o); }
                inline void     add             (CCOperators o)             { for(autoRef e:descriptions) e.add(o); }
                
                
                typedef Description::Group Group;
                
                
                inline Group    groupGet        ()                           { Group r; r.descriptions.reserve(descriptions.size()); for(autoRef e:descriptions) r.descriptions.push_back(&e); return r; }
                inline Group    groupGet        (int type)                   { Group r; r.descriptions.reserve(descriptions.size()); for(autoRef e:descriptions) if (e.type==type) r.descriptions.push_back(&e); return r; }
                inline Group    groupGet        (int from, int to)           { Group r; r.descriptions.reserve(to-from); loopUpFromTo(i,from,to) r.descriptions.push_back(&descriptions.at(i)); return r; }
                inline Group    groupGet        (int type, int from, int to) { Group r; r.descriptions.reserve(to-from); loopUpFromTo(i,from,to) if (descriptions[i].type == type) r.descriptions.push_back(&descriptions.at(i)); return r; }
                inline Group    groupGet        (set<int> indexes)           { Group r; r.descriptions.reserve(indexes.size()); for(auto i:indexes) if (contains(indexes,i)) r.descriptions.push_back(&descriptions.at(i)); return r; }
                inline Group    groupGet        (int type, set<int> indexes) { Group r; r.descriptions.reserve(indexes.size()); for(auto i:indexes) if (descriptions[i].type == type and contains(indexes,i)) r.descriptions.push_back(&descriptions.at(i)); return r; }

                inline Group    operator ()     ()                           { return groupGet(); }
                inline Group    operator ()     (int type)                   { return groupGet(type); }
                inline Group    operator ()     (int from, int to)           { return groupGet(from,to); }
                inline Group    operator ()     (int type, int from, int to) { return groupGet(type,from,to); }
                inline Group    operator ()     (set<int> indexes)           { return groupGet(indexes); }
                inline Group    operator ()     (int type, set<int> indexes) { return groupGet(type,indexes); }
            };

            

            
            
            
            
            STRUCT (Composition)
            {
                STRUCT (Layer)
                {
                    Description         description;
                    
                    Layer () {};
                    Layer (DescriptionCRef p) : description(p) {}
                };
                
                Description                     description;
                vector<Layer>                   layers;
                Color4F                         fill                    = {1,1,1,0};
                bool                            symmetric               = false;
                int                             method                  = 2;
                
                ______                          Composition             ();
                ______                          Composition             (DescriptionCRef d, vectorCRef(Layer) l = {}, bool s = false, int m = 2, Color4F f = {1,1,1,0}) : description(d), layers(l), fill(f), symmetric(s) {}
                
                vector<Description>             layersGetAsDescriptions () const;
            };
            

            
            
            
            
            
            STRUCT (Factory)
            {

                STRUCT (Function)
                {
                    typedef std::function<string (DescriptionCRef)> Filename;
                };
                
                STRUCT (Parameters)
                {
                    struct {
                        CCBlending  applicant;
                        bool        applyToRoot     = false;
                        bool        applyToAll      = false;
                    } blending;
                    
                    struct {
                        std::function<CCSpritePtr (CCNodePtr top, CCSize size, Color4F fill)> function = 0;
                    } render;
                    
                    Parameters();
                } parameters;
                
                STRUCT (Formation)
                {
                    CCSpritePtr     root            = 0;
                    CCSize          size;
                    
                    ______          Formation       (CCSpritePtr r = 0, CCSize s = {0,0}) : root(r), size(s) {}
                };
                
                ______                          Factory                         (ParametersCRef p) : parameters(p) {}
                ______                          Factory                         (bool frames);
                
                ______  CCTexture2DPtr          textureCreateFromDescriptions   (int type, vectorCRef(Description) p, Color4F fill = {1,1,1,0}, bool symmetric = false);
                
                inline  CCTexture2DPtr          textureCreate                   (int type, CCTexture2DPtr t, vectorCRef(Description) p, Color4F fill = {1,1,1,0}, bool symmetric = false)                             { return textureCreateFromDescriptions(type,Description::createWithTexture(t,p),fill,symmetric); }
                inline  CCTexture2DPtr          textureCreate                   (int type, vectorCRef(pair<CCTexture2DPtr,Description>) p, Color4F fill = {1,1,1,0}, bool symmetric = false)                          { return textureCreateFromDescriptions(type,Description::createWithTextures(p),fill,symmetric); }
                inline  CCTexture2DPtr          textureCreate                   (int type, std::function<CCSpritePtr (DescriptionCRef)> f, vector<Description> p, Color4F fill = {1,1,1,0}, bool symmetric = false)   { return textureCreateFromDescriptions(type,Description::createWithFunction(f,p),fill,symmetric); }
                
                ______  CCTexture2DPtr          textureCreateFromComposition    (Composition composition, vectorCRef(Description) angles, std::function<CCSpritePtr (DescriptionCRef)> producerOfSprite);
                
            protected:
                                
                ______  void                    textureCreateStepHierarchy      (CCSpritePtr sprite, CCNodePtr root, CCNodePtr previous, CCNodePtr first, DescriptionCRef description, vectorCRef(Description) descriptions, int count);
                ______  Formation               textureCreateStepFormation      (int type, vectorCRef(Description) descriptions, Color4F fill, bool symmetric);
                ______  CCSpritePtr             textureCreateStepRender         (CCNodePtr root, CCSize size, Color4F fill = {1,1,1,0});
                
            };
            
            
            
            
            
            
            

            
        } // namespace Texture
        
        
        
    }
}