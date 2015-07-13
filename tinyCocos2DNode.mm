

#import "tinyCocos2DNode.h"

namespace tiny
{
    namespace Cocos2D
    {
        
        
        
            // 8< --------------------------------------------------------------------------------------
        
        namespace Node
        {
            
            
            
            
            
            
            
            
            
            
                // 8< --------------------------------------------------------------------------------------
            
            void oglDrawSolidTriangleFan(CCBlendFunc blend, const CCPoint *poli, unsigned int numberOfPoints, Color4F * colors )
            {
                static struct {
                    bool initialized = false;
                    CCGLProgram* key = NULL;
                    struct {
                        int color = -1;
                        int position = -1;
                    } location;
                } shader;
                
                if (not shader.initialized)
                {
                    shader.key = CCShaderCache::getInstance()->getGLProgram(kCCShader_PositionColor);
                    
                    shader.location.position = glGetUniformLocation( shader.key->getProgram(), "a_position");
                    CHECK_GL_ERROR_DEBUG();
                    
                    shader.location.color = glGetUniformLocation( shader.key->getProgram(), "a_color");
                    CHECK_GL_ERROR_DEBUG();
                    
                    shader.initialized = true;
                }
                
                shader.key -> use();
                shader.key -> setUniformsForBuiltins();
                
                ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color );
                
                    // 1 POSITION
                glEnableVertexAttribArray( kCCVertexAttribFlag_Position );
                
                    // XXX: Mac OpenGL error. arrays can't go out of scope before draw is executed
                ccVertex2F* newPoli = new ccVertex2F[numberOfPoints];
                
                    // iPhone and 32-bit machines optimization
                if( sizeof(CCPoint) == sizeof(ccVertex2F) )
                {
                    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, poli);
                }
                else
                {
                        // Mac on 64-bit
                    for( unsigned int i=0; i<numberOfPoints;i++)
                    {
                        newPoli[i] = vertex2( poli[i].x, poli[i].y );
                    }
                    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, newPoli);
                }
                
                    // 2 COLOR
                glEnableVertexAttribArray( kCCVertexAttribFlag_Color );
                glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
                
                ccGLBlendFunc( blend.src, blend.dst );
                
                    // 3 RENDER
                glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei) numberOfPoints);
                
                ccSafeDeleteArray(newPoli);
                CC_INCREMENT_GL_DRAWS(1);
            }
            
            
            
            
            
            
            
                // 8< --------------------------------------------------------------------------------------
            
            
            CCLayerDrawPolygonWithTriangleFanPtr CCLayerDrawPolygonWithTriangleFan::create()
            {
                ccNewWithArgsThenInitAutoreleaseReturn(CCLayerDrawPolygonWithTriangleFan,{},{});
            }
            
            CCLayerDrawPolygonWithTriangleFanPtr CCLayerDrawPolygonWithTriangleFan::create(vector<CCPoint> points, vector<Color4F> colors)
            {
                ccNewWithArgsThenInitAutoreleaseReturn(CCLayerDrawPolygonWithTriangleFan,points,colors);
            }
            
            CCBlendFuncCRef CCLayerDrawPolygonWithTriangleFan::getBlendFunc() const
            {
                return data.blendFunc;
            }
            
            void CCLayerDrawPolygonWithTriangleFan::setBlendFunc(CCBlendFuncCRef blendFunc)
            {
                data.blendFunc = blendFunc;
            }
            
            CCLayerDrawPolygonWithTriangleFan::CCLayerDrawPolygonWithTriangleFan(vector<CCPoint> points, vector<Color4F> colors)
            {
                set(points,colors);
            }
            
            bool CCLayerDrawPolygonWithTriangleFan::init()
            {
                setGLProgram(CCShaderCache::getInstance() -> getGLProgram(kCCShader_PositionColor));
                
                return true;
            }
            
            void CCLayerDrawPolygonWithTriangleFan::set(vector<CCPoint> points, vector<Color4F> colors)
            {
                tAssert(points.size() == colors.size());
                data.points = points;
                data.colors = colors;
                data.vertices = points;
            }
            
            void CCLayerDrawPolygonWithTriangleFan::mydraw()
            {
                if (2 < data.points.size())
                {
                    float w = ccWidthScaled(this);
                    float h = ccHeightScaled(this);
                    
                    loopUpTo(i,(int)data.vertices.size())
                    {
                        data.vertices[i].x = w * data.points[i].x;
                        data.vertices[i].y = h * data.points[i].y;
                    }
                    
                    oglDrawSolidTriangleFan(getBlendFunc(), &data.vertices[0], data.vertices.size(), &data.colors[0] );
                }
            }
            
            
            
            
            
            
                // 8< --------------------------------------------------------------------------------------
            
            CCLayerGradientRadialPtr CCLayerGradientRadial::create (Color4F colorFrom, Color4F colorTo)
            {
                ccNewWithArgsThenInitAutoreleaseReturn(CCLayerGradientRadial,colorFrom,colorTo);
            }
            
            void CCLayerGradientRadial::set (Color4F colorFrom, Color4F colorTo)
            {
                data.color.from = colorFrom; data.color.to = colorTo;
            }
            
            CCBlendFuncCRef CCLayerGradientRadial::getBlendFunc () const
            {
                return data.blendFunc;
            }
            
            void CCLayerGradientRadial::setBlendFunc (CCBlendFuncCRef blendFunc)
            {
                data.blendFunc = blendFunc;
            }
            
            bool CCLayerGradientRadial::init ()
            {
                setGLProgram(CCShaderCache::getInstance() -> getGLProgram(kCCShader_PositionColor));
                
                return true;
            }
            
            void CCLayerGradientRadial::mydraw ()
            {
                float w = ccWidthScaled(this);
                float h = ccHeightScaled(this);
                CCPoint center = Vec2(w/2.,h/2.);
                
                CCPoint vertices[] {
                    center,
                    Vec2(w,0),
                    Vec2(w,h),
                    Vec2(0,h),
                    Vec2(0,0),
                    Vec2(w,0)
                };
                Color4F colors[] {
                    data.color.from,
                    data.color.to,
                    data.color.to,
                    data.color.to,
                    data.color.to,
                    data.color.to
                };
                
                oglDrawSolidTriangleFan(getBlendFunc(), vertices, 6, colors );
            }
            
            
            
            
            
            
            
                // 8< --------------------------------------------------------------------------------------
            
            CCSunburstPtr CCSunburst::create(int sections, Color4F colorFrom, Color4F colorTo, int cutOffInPixels)
            {
                ccNewWithArgsThenInitAutoreleaseReturn(CCSunburst,sections,colorFrom,colorTo,cutOffInPixels);
            }
            
            CCBlendFuncCRef CCSunburst::getBlendFunc() const
            {
                return data.blendFunc;
            }
            
            void CCSunburst::setBlendFunc(CCBlendFuncCRef blendFunc)
            {
                data.blendFunc = blendFunc;
            }
            
            CCSunburst::CCSunburst(int s, Color4F from, Color4F to, int r) {
                data.sections = s;
                data.cutOffInPixels = r;
                data.color.from = from;
                data.color.to = to;
                tAssert(data.color.from.b == from.b);
            }
            
            bool CCSunburst::init()
            {
                setContentSize(CCSize(3000,3000));
                setAnchorPoint(Vec2(.5,.5));
                setGLProgram(CCShaderCache::getInstance() -> getGLProgram(kCCShader_PositionColor));
                return true;
            }
            
            void CCSunburst::mydraw()
            {
                    //                    ccDrawColor4F(1, 0, 0, .1);
                int s = data.sections;
                float angled = tiny::Math::twopi/s;
                s /= 2;
                float angle = 0;
                float hypotenuse0 = tiny::Math::hypotenuse(ccWidthScaled(this), ccHeightScaled(this))/2.;
                CCPoint center = Vec2(ccWidthScaled(this)/2.,ccHeightScaled(this)/2.);
                float hypotenuse1 = data.cutOffInPixels;//hypotenuse0 * ratio;
                float cosfa, sinfa, cosfaa, sinfaa;
                
                CCPoint vertices[4];
                Color4F colors[4];
                
                for(int i = 0; i < s; i ++)
                {
                    cosfa = cosf(angle);
                    sinfa = sinf(angle);
                    cosfaa = cosf(angle+angled);
                    sinfaa = sinf(angle+angled);
                    
                    float x0 = hypotenuse0 * cosfa;
                    float y0 = hypotenuse0 * sinfa;
                    float x1 = hypotenuse0 * cosfaa;
                    float y1 = hypotenuse0 * sinfaa;
                    float x2 = hypotenuse1 * cosfaa;
                    float y2 = hypotenuse1 * sinfaa;
                    float x3 = hypotenuse1 * cosfa;
                    float y3 = hypotenuse1 * sinfa;
                    
                    vertices[0] = Vec2(center.x+x0,center.y+y0);
                    vertices[1] = Vec2(center.y+x1,center.y+y1);
                    vertices[2] = Vec2(center.x+x2,center.y+y2);
                    vertices[3] = Vec2(center.x+x3,center.y+y3);
                    
                    colors[0] = data.color.from;
                    colors[1] = data.color.from;
                    colors[2] = data.color.to;
                    colors[3] = data.color.to;
                    
                        //                    ccDrawSolidPoly(vertices, 4, color0);
                    oglDrawSolidTriangleFan(getBlendFunc(), vertices, 4, colors );
                    
                    angle += angled + angled;
                }
            }
            
            
            
            
            
            
            
            
            
                // 8< --------------------------------------------------------------------------------------
            
            
            
            
            
            
            CCSnapshotOfNode::CCSnapshotOfNode(CCNodePtr p) {
                set(p);
            }
            
            void CCSnapshotOfNode::set(CCNodePtr p) {
                time = tiny::Time::now();
                    //                ignoreAnchor = p -> isIgnoreAnchorPointForPosition();
                anchor = p -> getAnchorPoint();
                    //                anchorPointInPoints = p -> getAnchorPointInPoints();
                location    = p -> getPosition();
                rotation    = p -> getRotation();
                scalex      = p -> getScaleX();
                scaley      = p -> getScaleY();
                skewx       = p -> getSkewX();
                skewy       = p -> getSkewY();
                
                visible     = p -> isVisible();
                
                z           = p -> getZOrder();
            }
            
            void CCSnapshotOfNode::apply(CCNodePtr p) {
                    //                p -> ignoreAnchorPointForPosition(ignoreAnchor);
                p -> setAnchorPoint (anchor);
                p -> setRotation    (rotation);
                p -> setScaleX      (scalex);
                p -> setScaleY      (scaley);
                p -> setSkewX       (skewx);
                p -> setSkewY       (skewy);
                p -> setPosition    (location);
                p -> setVisible     (visible);
                p -> setZOrder      (z);
            }
            
            CCSnapshotOfNode CCSnapshotOfNode::create(CCNodePtr p) {
                return CCSnapshotOfNode(p);
            }
            
            
            
            
            
            
            
            ______              CCSnapshotOfSprite::CCSnapshotOfSprite              (CCSpritePtr p) : CCSnapshotOfNode(p)
            {
                set(p);
            }
            
            void CCSnapshotOfSprite::set(CCSpritePtr p)
            {
                CCSnapshotOfNode::set(p);
                
                color               = p -> getColor();
                opacity             = p -> getOpacity();
            }
            
            void                CCSnapshotOfSprite::apply                           (CCSpritePtr p)
            {
                CCSnapshotOfNode::apply(p);
                
                p -> setColor       (color);
                p -> setOpacity     (opacity);
            }
            
            CCSnapshotOfSprite CCSnapshotOfSprite::create                           (CCSpritePtr p)
            {
                return CCSnapshotOfSprite(p);
            }
            
            
            
            
            
            
            int CCDrawing::addDrawing (Function f)
            {
                functions.push_back({++count,f});
                return count;
            }
            
            void CCDrawing::removeDrawing (int i)
            {
                erase_if(functions, [i] (const std::pair<int,Function>& p) { return i==p.first; });
            }
            
            void CCDrawing::mydraw()
            {
                for(auto f:functions) { f.second(); }
            }
            
            
        }
        
        
        

        
    }
}