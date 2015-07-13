    //
    //  tinyCocos2DNode.h
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 5/2/14.
    //
    //

#pragma once

#import "tinyCocos2D.h"

#include <boost/any.hpp>

namespace tiny
{
    namespace Cocos2D
    {
        namespace Node
        {
            
            
            
            void oglDrawSolidTriangleFan(CCBlendFunc blend, const CCPoint *poli, unsigned int numberOfPoints, Color4F * colors );
            
            
            
            STRUCT (CCLayerDrawPolygonWithTriangleFan) : public CCNode, public CCBlendProtocol {
                
                static CCLayerDrawPolygonWithTriangleFanPtr create();
                
                static CCLayerDrawPolygonWithTriangleFanPtr create(vector<CCPoint> points, vector<Color4F> colors);
                
                void set(vector<CCPoint> points, vector<Color4F> colors);
                
                void mydraw() override;
                
                CCBlendFuncCRef getBlendFunc() const;
                
                void setBlendFunc(CCBlendFuncCRef blendFunc);
                
            protected:
                
                struct {
                    CCBlendFunc blendFunc = {GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
                    
                    vector<CCPoint> points;
                    vector<CCPoint> vertices;
                    vector<Color4F> colors;
                } data;
                
                bool init();
                
                CCLayerDrawPolygonWithTriangleFan(vector<CCPoint> points, vector<Color4F> colors);
            };
            
            
            
            
            STRUCT (CCLayerGradientRadial) : public CCNode, public CCBlendProtocol {
                
                static CCLayerGradientRadialPtr create(Color4F colorFrom = {1,0,0,1}, Color4F colorTo = {1,0,0,0});
                
                inline void set(Color4F colorFrom = {1,0,0,1}, Color4F colorTo = {1,0,0,0});
                
                void mydraw() override;
                
                CCBlendFuncCRef getBlendFunc() const ;
                
                void setBlendFunc(CCBlendFuncCRef blendFunc) override ;
                
            protected:
                
                struct {
                    CCBlendFunc blendFunc = {GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
                    
                    struct {
                        Color4F from;
                        Color4F to;
                    } color;
                } data;
                
                CCLayerGradientRadial(Color4F from, Color4F to) {
                    data.color.from = from;
                    data.color.to = to;
                    tAssert(data.color.from.b == from.b);
                }
                
                bool init();
                
            };
            
            
            
            
            STRUCT (CCSunburst) : public CCNode, public CCBlendProtocol {
                
                static CCSunburstPtr create(int sections = 64, Color4F colorFrom = {1,0,0,1}, Color4F colorTo = {1,0,0,0}, int cutOffInPixels = 0) ;
                
                void mydraw() override;
                
                CCBlendFuncCRef getBlendFunc() const ;
                
                void setBlendFunc(CCBlendFuncCRef blendFunc) override ;
                
            protected:
                
                struct {
                    CCBlendFunc blendFunc = {GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
                    
                    struct {
                        Color4F from;
                        Color4F to;
                    } color;
                    int sections;
                    int cutOffInPixels;
                } data;
                
                CCSunburst(int s, Color4F from, Color4F to, int r) ;
                
                bool init();
                
            };
            
            
            
            
            
            
            
            
            
            
                // 8< ---------------------------------------------------------------------------
            
            
            
            
            STRUCT (CCSnapshotOfNode)
            {
                tiny::Time::Time time = 0;
                    //            bool ignoreAnchor = false;
                CCPoint anchor;
                    //            CCPoint anchorPointInPoints;
                CCPoint location;
                
                float   rotation    = 0;
                float   scalex      = 1;
                float   scaley      = 1;
                float   skewx       = 0;
                float   skewy       = 0;

                int     z           = 0;
                
                bool    visible     = true;
                
                ______                      CCSnapshotOfNode    ()              {}
                ______                      CCSnapshotOfNode    (CCNodePtr p) ;
                
                void                        set                 (CCNodePtr p) ;
                
                void                        apply               (CCNodePtr p) ;
                
                static CCSnapshotOfNode     create              (CCNodePtr p) ;
            };
            
            
            
            
                // 8< ---------------------------------------------------------------------------
            
            
            
            
            STRUCT (CCSnapshotOfSprite) : public CCSnapshotOfNode
            {
                GLubyte     opacity;
                
                Color3B     color;
                
                ______                      CCSnapshotOfSprite  () {}
                
                ______                      CCSnapshotOfSprite  (CCSpritePtr p) ;
                
                void                        set                 (CCSpritePtr p) ;
                
                void                        apply               (CCSpritePtr p) ;
                
                static CCSnapshotOfSprite   create              (CCSpritePtr p) ;
            };
            
            
            
                // 8< ---------------------------------------------------------------------------

            
            
            STRUCT (CCDrawing) : public CCNode
            {
                typedef std::function<void ()> Function;
                
                ccCreate(CCDrawing);
                
                std::vector<boost::any> data;
                
                int         addDrawing      (Function f);
                
                void        removeDrawing   (int i);
                
                void        mydraw          () override ;
                
            private:
                
                std::list<std::pair<int,Function>> functions;
                
                int count = 0;
            };
            
            
            
            
        }
        
        
    }
}