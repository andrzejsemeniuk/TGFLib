
#include "tinyCocos2DOpenGL.h"

namespace tiny
{
    namespace Cocos2D
    {
        namespace OpenGL
        {
            
            
            
            void init()
            {
                static bool initialized = false;
                
                if (not initialized)
                {
                    initialized = true;
                }
            }
            
            
#if 0
            
            void ccDrawPoint( const CCPoint& point )
            {
                lazy_init();
                
                ccVertex2F p;
                p.x = point.x;
                p.y = point.y;
                
                ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
                s_pShader->use();
                s_pShader->setUniformForModelViewProjectionMatrix();
                
                s_pShader->setUniformLocationWith4fv(s_nColorLocation, (GLfloat*) &s_tColor.r, 1);
                s_pShader->setUniformLocationWith1f(s_nPointSizeLocation, s_fPointSize);
                
                glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, &p);
                
                glDrawArrays(GL_POINTS, 0, 1);
                
                CC_INCREMENT_GL_DRAWS(1);
            }
            
#endif
            void drawPositionsAndColor(int mode,
                                       GLsizei count,
                                       void * positions,
                                       Color4F color)
            {
                CCGLProgramPtr program = CCShaderCache::getInstance() -> getGLProgram(kCCShader_Position_uColor);
                
                program -> use();
                CHECK_GL_ERROR_DEBUG();
                program -> setUniformsForBuiltins();
                CHECK_GL_ERROR_DEBUG();
                
                ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
                CHECK_GL_ERROR_DEBUG();
                
                glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, positions);
                CHECK_GL_ERROR_DEBUG();
                
                program -> setUniformLocationWith4fv(kCCVertexAttrib_Color, (GLfloat*) &color.r, 1);
                CHECK_GL_ERROR_DEBUG();
                
                glDrawArrays(mode, 0, count);
            }
            
            void drawPositionsAndColorWithTriangleStrip(GLsizei count,
                                                        void * positions,
                                                        Color4F color)
            {
                drawPositionsAndColor(GL_TRIANGLE_STRIP,count,positions,color);
            }
            
            void drawPositionsAndColors(int mode,
                                        GLsizei count,
                                        void * positions2f,
                                        void * colors4f)
            {
#if 1
                CCGLProgramPtr program = CCShaderCache::getInstance() -> getGLProgram(kCCShader_PositionColor);
                
                program -> use();
                CHECK_GL_ERROR_DEBUG();
                program -> setUniformsForBuiltins();
                CHECK_GL_ERROR_DEBUG();
                
                
                ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color );
                CHECK_GL_ERROR_DEBUG();
                
                glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, positions2f);
                CHECK_GL_ERROR_DEBUG();
                
                glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors4f);
                CHECK_GL_ERROR_DEBUG();
                
                glDrawArrays(mode, 0, count);
#else
//                Shaders::getShaderPositionsColors() -> draw(mode,count,positions,colors);
#endif
            }
            
            void drawPositionsAndColorsWithTriangleStrip(GLsizei count,
                                                         void * positions,
                                                         void * colors)
            {
                drawPositionsAndColors(GL_TRIANGLE_STRIP,count,positions,colors);
            }
            
            
            void drawPositionsAndTexels(int mode,
                                        GLsizei count,
                                        void * positions,
                                        void * texels)
            {
                CCGLProgramPtr program = CCShaderCache::getInstance() -> getGLProgram(kCCShader_PositionTexture);
                
                program -> use();
                CHECK_GL_ERROR_DEBUG();
                program -> setUniformsForBuiltins();
                CHECK_GL_ERROR_DEBUG();
                
                ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords );
                CHECK_GL_ERROR_DEBUG();
                
                glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, positions);
                CHECK_GL_ERROR_DEBUG();
                
                glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, texels);
                CHECK_GL_ERROR_DEBUG();
                
                glDrawArrays(mode, 0, count);
            }
            
            void drawPositionsAndTexelsWithTriangleStrip(GLsizei count,
                                                         void * positions,
                                                         void * texels)
            {
                drawPositionsAndTexels(GL_TRIANGLE_STRIP,count,positions,texels);
            }
            
            
            
            
            
            
            
            
            
        }
    }
}