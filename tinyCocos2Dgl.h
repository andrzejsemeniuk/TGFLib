    //
    //  tinyCocos2DOpenGLgl.h
    //  productX
    //
    //  Created by andrzej semeniuk on 1/12/14.
    //
    //

#pragma once

#include "tiny.h"

#include "tinyCocos2D.h"

#include <iomanip>


namespace tiny {
    
    namespace Cocos2D {
        
        
        
        
        namespace gl
        {
            struct PositionXY
            {
                GLfloat x = 0,y = 0;
                
                PositionXY() {}
                PositionXY(GLfloat X, GLfloat Y) : x(X),y(Y) {}
                PositionXY(CCPoint p) : x(p.x),y(p.y) {}
                
                inline operator CCPoint () const { return Vec2(x,y); }
                
                friend std::ostream& operator << (std::ostream& o, const PositionXY& p) { return o << '(' << p.x << ',' << p.y << ')'; }
            };
            struct PositionXYZ
            {
                GLfloat x = 0,y = 0,z = 0;
                
                PositionXYZ() {}
                PositionXYZ(GLfloat X, GLfloat Y, GLfloat Z) : x(X),y(Y),z(Z) {}
                
                friend std::ostream& operator << (std::ostream& o, const PositionXYZ& p) { return o << '(' << p.x << ',' << p.y << ',' << p.z << ')'; }
            };
            struct ColorRGB
            {
                GLfloat r = 0,g = 0,b = 0;
                
                ColorRGB() {}
                ColorRGB(GLfloat R, GLfloat G, GLfloat B) : r(R),g(G),b(B) {}
                ColorRGB(Color3F p) : r(p.r),g(p.g),b(p.b) {}
                
                friend std::ostream& operator << (std::ostream& o, const ColorRGB& p) { return o << '(' << p.r << ',' << p.g << ',' << p.b << ')'; }
            };
            struct ColorRGBA
            {
                GLfloat r = 0,g = 0,b = 0,a = 0;
                
                ColorRGBA() {}
                ColorRGBA(GLfloat R, GLfloat G, GLfloat B, GLfloat A) : r(R),g(G),b(B),a(A) {}
                ColorRGBA(Color3F p, float a_ = 1.f) : r(p.r),g(p.g),b(p.b),a(a_) {}
                ColorRGBA(Color4F p) : r(p.r),g(p.g),b(p.b),a(p.a) {}
                
                friend std::ostream& operator << (std::ostream& o, const ColorRGBA& p) { return o << '(' << p.r << ',' << p.g << ',' << p.b << ',' << p.a << ')'; }
            };
            struct TextureXY
            {
                GLfloat x = 0,y = 0;
                
                TextureXY() {}
                TextureXY(GLfloat X, GLfloat Y) : x(X),y(Y) {}
                TextureXY(CCPoint p) : x(p.x),y(p.y) {}
                
                inline operator CCPoint () const { return Vec2(x,y); }
                
                friend std::ostream& operator << (std::ostream& o, const TextureXY& p) { return o << '(' << p.x << ',' << p.y << ')'; }
            };
            
            
            namespace error
            {
                inline  GLenum  get()                       { return glGetError(); };
#define ccGLErrorLog() CHECK_GL_ERROR_DEBUG()
            }
            
            
            inline void     get(GLenum name, GLboolean *p)  { glGetBooleanv(name,p); }
            inline void     get(GLenum name, GLfloat *p)    { glGetFloatv(name,p); }
            inline void     get(GLenum name, GLint *p)      { glGetIntegerv(name,p); }
            
                //  GL_BLEND If enabled, blend the computed fragment color values with the values in the color buffers. See glBlendFunc.
                //  GL_CULL_FACE If enabled, cull polygons based on their winding in window coordinates. See glCullFace.
                //  GL_DEPTH_TEST If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled. See glDepthFunc and glDepthRangef.
                //  GL_DITHER If enabled, dither color components or indices before they are written to the color buffer.
                //  GL_POLYGON_OFFSET_FILL If enabled, an offset is added to depth values of a polygon's fragments produced by rasterization. See glPolygonOffset.
                //  GL_SAMPLE_ALPHA_TO_COVERAGE If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then ANDed with the fragment coverage value.
                //  GL_SAMPLE_COVERAGE If enabled, the fragment's coverage is ANDed with the temporary coverage value. If GL_SAMPLE_COVERAGE_INVERT is set to GL_TRUE, invert the coverage value. See glSampleCoverage.
                //  GL_SCISSOR_TEST If enabled, discard fragments that are outside the scissor rectangle. See glScissor.
                //  GL_STENCIL_TEST If enabled, do stencil testing and update the stencil buffer. See glStencilFunc and glStencilOp.
                // p=
                //  GL_BLEND
                //  GL_CULL_FACE
                //  GL_DEPTH_TEST
                //  GL_DITHER
                //  GL_POLYGON_OFFSET_FILL
                //  GL_SAMPLE_ALPHA_TO_COVERAGE
                //  GL_SAMPLE_COVERAGE
                //  GL_SCISSOR_TEST
                //  GL_STENCIL_TEST
            inline void         enable(GLenum p)                { glEnable(p); }
            inline void         disable(GLenum p)               { glDisable(p); }
                //                Constant	 See
                //                GL_BLEND	glBlendFunc
                //                GL_CULL_FACE	glCullFace
                //                GL_DEPTH_TEST	glDepthFunc, glDepthRangef
                //                GL_DITHER	glEnable
                //                GL_POLYGON_OFFSET_FILL	glPolygonOffset
                //                GL_SAMPLE_ALPHA_TO_COVERAGE	glSampleCoverage
                //                GL_SAMPLE_COVERAGE	glSampleCoverage
                //                GL_SCISSOR_TEST	glScissor
                //                GL_STENCIL_TEST	glStencilFunc, glStencilOp
            inline GLboolean    enabled(GLenum p)               { return glIsEnabled(p); }
            
            
            inline void         viewport(GLint x,
                                         GLint y,
                                         GLsizei width,
                                         GLsizei height)        { glViewport(x,y,width,height); }
            
            
            inline void         clearColor()                    { glClear(GL_COLOR_BUFFER_BIT); }
            inline void         clearDepth()                    { glClear(GL_DEPTH_BUFFER_BIT); }
            inline void         clearStencil()                  { glClear(GL_STENCIL_BUFFER_BIT); }
            
            inline void         clear(GLclampf r,
                                      GLclampf g,
                                      GLclampf b,
                                      GLclampf a)                { glClearColor(r,g,b,a); }
            
            namespace blend
            {
                extern string   name        (int code);

                inline void     color       (GLclampf red,
                                             GLclampf green,
                                             GLclampf blue,
                                             GLclampf alpha)                    { glBlendColor(red,green,blue,alpha); }
                
                inline void     equation    (GLenum q)                          { glBlendEquation(q); }
                
                inline void     function    (GLenum source, GLenum target)      { glBlendFunc(source,target); }
                
                inline void     print       ()
                {
                    int srgb,sa,drgb,da;

                    glGetIntegerv(GL_BLEND_SRC_RGB,&srgb);
                    glGetIntegerv(GL_BLEND_DST_RGB,&drgb);
                    glGetIntegerv(GL_BLEND_SRC_ALPHA,&sa);
                    glGetIntegerv(GL_BLEND_DST_ALPHA,&da);
                    
                    tLog("glBlendFunc src=0x"<<name(srgb)<<",0x"<<name(sa));
                    tLog("glBlendFunc dst=0x"<<name(drgb)<<",0x"<<name(da));
                }
                
                namespace separate
                {
                    inline void equation    (GLenum modeRGB, GLenum modeAlpha)  { glBlendEquationSeparate(modeRGB,modeAlpha); }
                    
                    inline void function    (GLenum srcRGB,
                                             GLenum dstRGB,
                                             GLenum srcAlpha,
                                             GLenum dstAlpha)                   { glBlendFuncSeparate(srcRGB,dstRGB,srcAlpha,dstAlpha); }
                    
                    struct state
                    {
                        GLboolean   enabled     = false;
                        GLint       srgb        = GL_ZERO;
                        GLint       drgb        = GL_ZERO;
                        GLint       sa          = GL_ZERO;
                        GLint       da          = GL_ZERO;
                        
                        state()
                        {
                            enabled         = glIsEnabled(GL_BLEND);
                            
                            if (enabled)
                            {
                                glGetIntegerv(GL_BLEND_SRC_RGB,       & srgb);
                                glGetIntegerv(GL_BLEND_DST_RGB,       & drgb);
                                glGetIntegerv(GL_BLEND_SRC_ALPHA,     & sa);
                                glGetIntegerv(GL_BLEND_DST_ALPHA,     & da);
                            }
                        }
                        
                        void restore() const
                        {
                            if (enabled)
                            {
                                glBlendFuncSeparate(srgb,drgb,sa,da);
                            }
                        }
                    };
                    

                }
            }
            
            namespace stencil
            {
                inline void     function    (GLenum func,
                                             GLint ref,
                                             GLuint mask)       { glStencilFunc(func,ref,mask); }
                inline void     mask        (GLuint mask)       { glStencilMask(mask); }
                inline void     op          (GLenum sfail,
                                             GLenum dpfail,
                                             GLenum dppass)     { glStencilOp(sfail,dpfail,dppass); }
                
                namespace separate
                {
                    inline void     function    (GLenum face,
                                                 GLenum func,
                                                 GLint ref,
                                                 GLuint mask)       { glStencilFuncSeparate(face,func,ref,mask); }
                    inline void     mask        (GLenum face,
                                                 GLuint mask)       { glStencilMaskSeparate(face,mask); }
                    inline void     op          (GLenum face,
                                                 GLenum sfail,
                                                 GLenum dpfail,
                                                 GLenum dppass)     { glStencilOpSeparate(face,sfail,dpfail,dppass); }
                }
            }
            
            
            namespace texture
            {
                    // generate,bind,activate,attach,deactivate,destroy
                
                inline GLuint       generate    ()                                      { GLuint t = 0; glGenTextures(1,&t); return t; }
                inline void         generate    (GLsizei n, GLuint * textures)          { glGenTextures(n,textures); }
                inline void         destroy     (GLsizei n, const GLuint * textures)    { glDeleteTextures(n,textures); }
                inline void         bindFlat    (GLuint texture)                        { glBindTexture(GL_TEXTURE_2D,texture); }
                inline void         bindCube    (GLuint texture)                        { glBindTexture(GL_TEXTURE_CUBE_MAP,texture); }
                inline void         activate    (GLenum target)                         { glActiveTexture(target); }
                inline GLboolean    is          (GLuint texture)                        { return glIsTexture(texture); }
                
                namespace parameter
                {
                    inline void     set         (GLenum target,
                                                 GLenum pname,
                                                 GLfloat param)                         { glTexParameterf(target,pname,param); }
                    inline void     set         (GLenum target,
                                                 GLenum pname,
                                                 GLint param)                           { glTexParameteri(target,pname,param); }
                }
                
                
                STRUCT (Image)
                {
                    GLenum target;
                    GLint level;
                    GLint internalFormat;
                    GLsizei width;
                    GLsizei height;
                    GLint border;
                    GLenum format;
                    GLenum type;
                    GLvoid * data = 0;
                };
                
                inline void         image               (ImageCRef p)
                {
                    glTexImage2D(p.target,p.level,p.internalFormat,p.width,p.height,p.border,p.format,p.type,p.data);
                }
                
                STRUCT (SubImage)
                {
                    GLenum target;
                    GLint level;
                    GLint xoffset;
                    GLint yoffset;
                    GLsizei width;
                    GLsizei height;
                    GLenum format;
                    GLenum type;
                    GLvoid * data = 0;
                };
                
                inline void         subimage            (SubImageCRef p)
                {
                    glTexSubImage2D(p.target,p.level,p.xoffset,p.yoffset,p.width,p.height,p.format,p.type,p.data);
                }
                
                inline void         attachToFrameBuffer (GLenum target,
                                                         GLenum attachment,
                                                         GLenum textarget,
                                                         GLuint texture,
                                                         GLint level)               { glFramebufferTexture2D(target,attachment,textarget,texture,level); }
                
                namespace mipmap
                {
                    inline void     generate            (GLenum target)             { glGenerateMipmap(target); }
                }
            }
            
            
            
            namespace buffer
            {
                    // there's a "frame" buffer and a "render" buffer
                
                inline GLuint   generate    ()                                      { GLuint buffer = 0; glGenBuffers(1,&buffer); return buffer; }
                inline void     generate    (GLsizei n, GLuint * buffers)           { glGenBuffers(n,buffers); }
                inline void     bind        (GLenum target, GLuint buffer)          { glBindBuffer(target,buffer); }
                
                inline void storeInArray(GLsizeiptr size, const GLvoid * data, GLenum usage) // GL_STREAM|STATIC|DYNAMIC_DRAW
                {
                    glBufferData(GL_ARRAY_BUFFER,size,data,usage);
                }
                inline void storeInArray(GLintptr offset, GLsizeiptr size, const GLvoid * data)
                {
                    glBufferSubData(GL_ARRAY_BUFFER,offset,size,data);
                }
                inline void storeInElementArray(GLsizeiptr size, const GLvoid * data, GLenum usage) // GL_STREAM|STATIC|DYNAMIC_DRAW
                {
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,data,usage);
                }
                inline void storeInElementArray(GLintptr offset, GLsizeiptr size, const GLvoid * data)
                {
                    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,offset,size,data);
                }
                
                
                
                namespace frame
                {
                        // a frame buffer object has a color, a depth, and a stencil buffer! (color,depth,stencil)
                    
                    inline void         generate    (GLsizei n, GLuint * buffers)               { glGenFramebuffers(n,buffers); }
                    inline void         bind        (GLenum target, GLuint buffer)              { glBindFramebuffer(target,buffer); }
                    inline void         destroy     (GLsizei n, const GLuint * buffers)         { glDeleteFramebuffers(n,buffers); }
                    inline GLboolean    is          (GLuint p)                                  { return glIsFramebuffer(p); }
                    
                    inline void attachToRenderBuffer(GLenum framebuffertarget,
                                                     GLenum attachment,
                                                     GLenum renderbuffertarget,
                                                     GLuint renderbuffer) { glFramebufferRenderbuffer(framebuffertarget,attachment,renderbuffertarget,renderbuffer); }
                    
                    STRUCT (Pixels)
                    {
                        GLint x;
                        GLint y;
                        GLsizei width;
                        GLsizei height;
                        GLenum format;
                        GLenum type;
                        GLvoid * data = 0;
                    };
                    
                    inline void         read        (PixelsRef v)
                    {
                        glReadPixels(v.x,v.y,v.width,v.height,v.format,v.type,v.data);
                    }
                }
                
                
                
                namespace render
                {
                    inline void         generate    (GLsizei n, GLuint * buffers)               { glGenRenderbuffers(n,buffers); }
                    inline void         bind        (GLenum target, GLuint buffer)              { glBindRenderbuffer(target,buffer); }
                    inline void         destroy     (GLsizei n, const GLuint * buffers)         { glDeleteRenderbuffers(n,buffers); }
                    inline GLboolean    is          (GLuint p)                                  { return glIsRenderbuffer(p); }
                    
                    inline void         allocate    (GLenum internalformat,
                                                     GLsizei width,
                                                     GLsizei height)                            { glRenderbufferStorage(GL_RENDERBUFFER,internalformat,width,height); }
                }
            }
            
            
                // opengl keywords: program, shader, attribute, vertex, buffer, array,
                // opengl nouns: stencil, location
                // opengl objects: program, shader, buffer, texture, attribute, uniform, varying, vertex, array
            
                // opengl verbs: draw, create, attach, detach, enable, disable, destroy, is, set, get, activate, deactivate
            
            namespace program
            {
                
                inline GLuint       create          ()                          { return glCreateProgram(); }
                inline void         destroy         (GLuint p)                  { glDeleteProgram(p); }
                inline void         link            (GLuint p)                  { glLinkProgram(p); }
                inline void         use             (GLuint p)                  { glUseProgram(p); }
                inline void         validate        (GLuint p)                  { glValidateProgram(p); }
                inline GLboolean    is              (GLuint p)                  { return glIsProgram(p); }
                
                namespace attribute
                {
                    inline void     bind        (GLuint program,
                                                 GLuint attribute,
                                                 const GLchar * name)       { glBindAttribLocation(program,attribute,name); }
                    
                    STRUCT (Value)
                    {
                        GLsizei length = 0;
                        GLint size = 0;
                        GLenum type = 0;
                        GLchar name[255];
                        constexpr static const GLsizei limit = 255;
                    };
                    
                    inline void     active      (GLuint program, GLuint attribute, ValueRef v)
                    {
                        glGetActiveAttrib(program,attribute,Value::limit,&v.length,&v.size,&v.type,v.name);
                    }
                    
                    inline Value    active      (GLuint program, GLuint attribute)
                    {
                        Value v;
                        glGetActiveAttrib(program,attribute,Value::limit,&v.length,&v.size,&v.type,v.name);
                        return v;
                    }
                    
                    inline GLint    location    (GLuint program, const GLchar * name)   { return glGetAttribLocation(program,name); }
                }
                
                namespace uniform
                {
                    inline void     get         (GLuint program,
                                                 GLint location,
                                                 GLfloat * params)      { glGetUniformfv(program,location,params); }
                    inline void     get         (GLuint program,
                                                 GLint location,
                                                 GLint * params)        { glGetUniformiv(program,location,params); }
                    
                    STRUCT (Value)
                    {
                        GLsizei length = 0;
                        GLint size = 0;
                        GLenum type = 0;
                        GLchar name[255];
                        constexpr static const GLsizei limit = 255;
                    };
                    
                    inline void     active      (GLuint program, GLuint location, ValueRef v)
                    {
                        glGetActiveUniform(program,location,Value::limit,&v.length,&v.size,&v.type,v.name);
                    }
                    
                    inline Value    active      (GLuint program, GLuint location)
                    {
                        Value v;
                        glGetActiveUniform(program,location,Value::limit,&v.length,&v.size,&v.type,v.name);
                        return v;
                    }
                    
                    inline GLint    location    (GLuint program,
                                                 const GLchar * name)                   { return glGetUniformLocation(program,name); }
                    
                    inline void     set         (GLint loc,
                                                 GLfloat v0)                            { glUniform1f(loc,v0); }
                    inline void     set         (GLint loc,
                                                 GLfloat v0,
                                                 GLfloat v1)                            { glUniform2f(loc,v0,v1); }
                    inline void     set         (GLint loc,
                                                 GLfloat v0,
                                                 GLfloat v1,
                                                 GLfloat v2)                            { glUniform3f(loc,v0,v1,v2); }
                    inline void     set         (GLint loc,
                                                 GLfloat v0,
                                                 GLfloat v1,
                                                 GLfloat v2,
                                                 GLfloat v3)                            { glUniform4f(loc,v0,v1,v2,v3); }
                    
                    inline void     set         (GLint loc,
                                                 GLint v0)                              { glUniform1i(loc,v0); }
                    inline void     set         (GLint loc,
                                                 GLint v0,
                                                 GLint v1)                              { glUniform2i(loc,v0,v1); }
                    inline void     set         (GLint loc,
                                                 GLint v0,
                                                 GLint v1,
                                                 GLint v2)                              { glUniform3i(loc,v0,v1,v2); }
                    inline void     set         (GLint loc,
                                                 GLint v0,
                                                 GLint v1,
                                                 GLint v2,
                                                 GLint v3)                              { glUniform4i(loc,v0,v1,v2,v3); }
                    
                    inline void     set1        (GLint loc,
                                                 GLsizei count,
                                                 const GLfloat * v)                     { glUniform1fv(loc,count,v); }
                    inline void     set2        (GLint loc,
                                                 GLsizei count,
                                                 const GLfloat * v)                     { glUniform2fv(loc,count,v); }
                    inline void     set3        (GLint loc,
                                                 GLsizei count,
                                                 const GLfloat * v)                     { glUniform3fv(loc,count,v); }
                    inline void     set4        (GLint loc,
                                                 GLsizei count,
                                                 const GLfloat * v)                     { glUniform4fv(loc,count,v); }
                    
                    inline void     set1        (GLint loc,
                                                 GLsizei count,
                                                 const GLint * v)                       { glUniform1iv(loc,count,v); }
                    inline void     set2        (GLint loc,
                                                 GLsizei count,
                                                 const GLint * v)                       { glUniform2iv(loc,count,v); }
                    inline void     set3        (GLint loc,
                                                 GLsizei count,
                                                 const GLint * v)                       { glUniform3iv(loc,count,v); }
                    inline void     set4        (GLint loc,
                                                 GLsizei count,
                                                 const GLint * v)                       { glUniform4iv(loc,count,v); }
                    
                    
                    inline void     set2        (GLint loc,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLfloat * v)                     { glUniformMatrix2fv(loc,count,transpose,v); }
                    inline void     set3        (GLint loc,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLfloat * v)                     { glUniformMatrix3fv(loc,count,transpose,v); }
                    inline void     set4        (GLint loc,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLfloat * v)                     { glUniformMatrix4fv(loc,count,transpose,v); }
                    
                }
            }
            
            
            
            
            namespace shader
            {
                    // "vertex shader is called once per each vertex specified
                    // "fragment shader is called once per PIXEL (on screen)
                    // "varying values are interpolated (in fragment shader) between vertices
                
                    // "drawing is specifying positions of vertices and interpolating colors between those positions
                
                
                inline void         attach          (GLuint program, GLuint shader)             { glAttachShader(program,shader); }
                inline void         detach          (GLuint program, GLuint shader)             { glDetachShader(program,shader); }
                inline void         destroy         (GLuint shader)                             { glDeleteShader(shader); }
                inline GLboolean    is              (GLuint p)                                  { return glIsShader(p); }
                
            }
            
            
            
            namespace vertex
            {
                    // a "vertex" is an element of a geometry object
                    // -it has attributes such as position (geometry) (xyz), color (rgba), texture info (xy), normal vector, etc
                
                namespace buffer
                {
                        // vertex buffer object
                        // -just like any other buffer object, but stores vertex data
                        // -a buffer object with GL_ARRAY_BUFFER type
                        // -stored in the GPU (server) memory (VRAM)
                        // -VRAM is x10 faster to access for the GPU than from CPU memory (RAM)
                        // -stores arbitrary data relevant to a vertex
                        // -can by static (unchangable), dynamic (changable)
                        // -data is passed from here according to instrutions from vao to shader
                    
                        // generate,bind,copy,enable.describe,draw  gbcedd
                    
                    inline GLuint   generate        ()                          { GLuint buffer = 0; glGenBuffers(1,&buffer); return buffer; }
                    inline void     generate        (GLsizei n,
                                                     GLuint * buffers)          { glGenBuffers(n,buffers); }
                    inline void     bind            (GLuint buffer)             { glBindBuffer(GL_ARRAY_BUFFER,buffer); }
                    inline void     unbind          ()                          { glBindBuffer(GL_ARRAY_BUFFER,0); }
                    
                    template<class T> void fill     (std::vector<T> & values, bool dynamic = false )
                    {
                        glBufferData(GL_ARRAY_BUFFER, sizeof(T) * values.size(), &values[0], dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
                    }
                    template<class T> void fill     (T * values, bool dynamic = false )
                    {
                        glBufferData(GL_ARRAY_BUFFER, sizeof(T), values, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
                    }
                }
                
                
                namespace attribute
                {
                        // "generic vertex attribute"
                        // -ie the attribute is generic
                        // -ie the attribute describes a vertex
                        // "xyz" is an attribute of a vertex - describes position
                        // "rgba" is an attribute of a vertex - describes color
                        // "xyz" is an attribute of a vertex - describes normal
                    
                    inline void     set         (GLuint index, GLfloat v0)                                      { glVertexAttrib1f(index,v0); }
                    inline void     set         (GLuint index, GLfloat v0, GLfloat v1)                          { glVertexAttrib2f(index,v0,v1); }
                    inline void     set         (GLuint index, GLfloat v0, GLfloat v1, GLfloat v2)              { glVertexAttrib3f(index,v0,v1,v2); }
                    inline void     set         (GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)  { glVertexAttrib4f(index,v0,v1,v2,v3); }
                    
                        // pname=
                        //  GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING
                        //  GL_VERTEX_ATTRIB_ARRAY_ENABLED
                        //  GL_VERTEX_ATTRIB_ARRAY_SIZE
                        //  GL_VERTEX_ATTRIB_ARRAY_STRIDE
                        //  GL_VERTEX_ATTRIB_ARRAY_TYPE
                        //  GL_VERTEX_ATTRIB_ARRAY_NORMALIZED
                        //  GL_CURRENT_VERTEX_ATTRIB
                    inline void     get         (GLuint index, GLenum pname, GLfloat *params)   { glGetVertexAttribfv(index,pname,params); }
                    inline void     get         (GLuint index, GLenum pname, GLint *params)     { glGetVertexAttribiv(index,pname,params); }
                    
                    
                    namespace array
                    {
                            // vertex attribute array ("vaa")
                            // -at least 8 allowed [0..7] in opengl es 2
                        
                        inline void     enable      (GLuint array)          { glEnableVertexAttribArray(array); } // [0..7]
                        inline void     disable     (GLuint array)          { glDisableVertexAttribArray(array); } // [0..7]
                        
                        
                        STRUCT (Description)
                        {
                            GLuint attribute = 0; // attribute location
                            GLint size = 4; // number of components in this attribute (ex. xyz=3)
                            GLenum type = GL_FLOAT; // component type
                            GLboolean normalized = GL_FALSE;
                            GLsizei stride = 0; // byte spacing between consequtive elements, ex. sizeof(MyStruct)
                            GLvoid * offset = 0; // offset within the struct to the first value of attribute
                            
                            Description() {}
                            Description(GLenum t, GLint s) : type(t), size(s) {}
                            Description(GLuint a, GLenum t, GLint s) : attribute(a), type(t), size(s) {}
                        };
                        
                        inline void     describe    (DescriptionCRef p)
                        {
                                //                                glEnableVertexAttribArray(GLKVertexAttribPosition);
                                //                                glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 8, BUFFER_OFFSET(6));
                                //                                glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
                                //                                glVertexAttribPointer(GLKVertexAttribTexCoord0, 2, GL_FLOAT, GL_FALSE, 8, BUFFER_OFFSET(0));
                                //                                glEnableVertexAttribArray(GLKVertexAttribNormal);
                                //                                glVertexAttribPointer(GLKVertexAttribNormal, 3, GL_FLOAT, GL_FALSE, 8, BUFFER_OFFSET(3));
                            
                                //                                • The first parameter specifies the attribute name to set. We just use the pre- defined constants GLKit set up.
                                //                                • The second parameter specifies how many values are present for each vertex. If you look back up at the Vertex struct, you'll see that for the position there are three floats (x,y,z) and for the color there are four floats (r,g,b,a).
                                //                                • The third parameter specifies the type of each value - which is float for both Posi- tion and Color.
                                //                                • The fourth parameter is always set to false.
                                //                                • The fifth parameter is the size of the stride, which is a fancy way of saying "the size of the data structure containing the per-vertex data". So we can simply pass in sizeof(Vertex) here to get the compiler to compute it for us.
                                //                                • The final parameter is the offset within the structure to find this data. We can use the handy offsetof operator to find the offset of a particular field within a struc-ture.
                            
                            glVertexAttribPointer(p.attribute,p.size,p.type,p.normalized,p.stride,p.offset);
                        }
                        
                        inline void     describe    (GLuint attribute,
                                                     GLint size = 4, // ie xyz = 3 components, hence = 3
                                                     GLenum type = GL_FLOAT,
                                                     GLboolean normalized = GL_FALSE,
                                                     GLsizei stride = 0, // stride = offset between consequtive per attribute, ex. sizeof(MyStruct)
                                                     const GLvoid * offset = 0) // byte offset from beginning of array
                        {
                            glVertexAttribPointer(attribute, size, type, normalized, stride, offset);
                        }
                        
                        inline void     describe    (GLuint buffer,
                                                     GLuint array,
                                                     GLuint attribute,
                                                     GLint size = 4, // ie xyz = 3 components, hence = 3
                                                     GLenum type = GL_FLOAT,
                                                     GLboolean normalized = GL_FALSE,
                                                     GLsizei stride = 0, // stride = offset between consequtive per attribute
                                                     const GLvoid * offset = 0) // byte offset from beginning of array
                        {
                            glBindBuffer(GL_ARRAY_BUFFER, buffer);
                            glEnableVertexAttribArray(array);
                            glVertexAttribPointer(attribute, size, type, normalized, stride, offset);
                        }
                        
                        inline void     pointer     (GLuint index, GLvoid ** pointer) { glGetVertexAttribPointerv(index,GL_VERTEX_ATTRIB_ARRAY_POINTER,pointer); }
                        
                        
                        
                        template<class T> void link(GLuint attribute, const vector<T>& data)
                        {
                            glVertexAttribPointer(attribute,sizeof(T)/sizeof(GLfloat),GL_FLOAT,GL_FALSE,0,(const GLvoid *)&data[0]);
                        }
                        
                        template<class T> void link(GLuint attribute, GLsizei size, const vector<T>& data)
                        {
                            glVertexAttribPointer(attribute,size,GL_FLOAT,GL_FALSE,0,(const GLvoid *)&data[0]);
                        }
                        
                        template<class T> void link(GLuint attribute, GLsizei size, GLsizei stride, const vector<T>& data)
                        {
                            glVertexAttribPointer(attribute,size,GL_FLOAT,GL_FALSE,stride,(const GLvoid *)&data[0]);
                        }
                        
                        inline void link(GLuint attribute, GLsizei size, const GLvoid * pointer)
                        {
                            glVertexAttribPointer(attribute,size,GL_FLOAT,GL_FALSE,0,pointer);
                        }
                        
                        inline void link(GLuint attribute, GLsizei size, GLenum type, const GLvoid * pointer)
                        {
                            glVertexAttribPointer(attribute,size,type,GL_FALSE,0,pointer);
                        }
                        
                        inline void link(GLuint attribute, GLsizei size, GLenum type, GLsizei stride, const GLvoid * pointer)
                        {
                            glVertexAttribPointer(attribute,size,type,GL_FALSE,stride,pointer);
                        }
                        
                        
                        inline void     draw                (GLenum what,
                                                             GLint first,
                                                             GLsizei count)                 { glDrawArrays(what,first,count); }
                        
                    }
                    
                    namespace element
                    {
                        inline void     draw    (GLenum mode,
                                                 GLsizei count,
                                                 GLenum type,
                                                 const GLvoid * indices){ glDrawElements(mode,count,type,indices); }
                    }
                    
                    
                }
            }
            
            
            
            
            inline void     draw                (GLenum what,
                                                 GLint first,
                                                 GLsizei count)                 { glDrawArrays(what,first,count); }
            
            inline void     drawPoints          (GLint first, GLsizei count)    { glDrawArrays(GL_POINTS,first,count); }
            inline void     drawLineStrip       (GLint first, GLsizei count)    { glDrawArrays(GL_LINE_STRIP,first,count); }
            inline void     drawLineLoop        (GLint first, GLsizei count)    { glDrawArrays(GL_LINE_LOOP,first,count); }
            inline void     drawLines           (GLint first, GLsizei count)    { glDrawArrays(GL_LINES,first,count); }
            inline void     drawTriangleStrip   (GLint first, GLsizei count)    { glDrawArrays(GL_TRIANGLE_STRIP,first,count); }
            inline void     drawTriangleFan     (GLint first, GLsizei count)    { glDrawArrays(GL_TRIANGLE_FAN,first,count); }
            inline void     drawTriangles       (GLint first, GLsizei count)    { glDrawArrays(GL_TRIANGLES,first,count); }
            
            inline void     draw                (GLenum type,
                                                 const vector<GLubyte>& indices)  { glDrawElements(type,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_BYTE,&indices[0]); }
            
            inline void     drawPoints          (const vector<GLubyte>& indices)  { glDrawElements(GL_POINTS,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_BYTE,&indices[0]); }
            inline void     drawLineStrip       (const vector<GLubyte>& indices)  { glDrawElements(GL_LINE_STRIP,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_BYTE,&indices[0]); }
            inline void     drawLineLoop        (const vector<GLubyte>& indices)  { glDrawElements(GL_LINE_LOOP,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_BYTE,&indices[0]); }
            inline void     drawLines           (const vector<GLubyte>& indices)  { glDrawElements(GL_LINES,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_BYTE,&indices[0]); }
            inline void     drawTriangleStrip   (const vector<GLubyte>& indices)  { glDrawElements(GL_TRIANGLE_STRIP,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_BYTE,&indices[0]); }
            inline void     drawTriangleFan     (const vector<GLubyte>& indices)  { glDrawElements(GL_TRIANGLE_FAN,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_BYTE,&indices[0]); }
            inline void     drawTriangles       (const vector<GLubyte>& indices)  { glDrawElements(GL_TRIANGLES,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_BYTE,&indices[0]); }
            
            inline void     draw                (GLenum type,
                                                 const vector<GLushort>& indices)  { glDrawElements(type,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_SHORT,&indices[0]); }
            
            inline void     drawPoints          (const vector<GLushort>& indices)  { glDrawElements(GL_POINTS,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_SHORT,&indices[0]); }
            inline void     drawLineStrip       (const vector<GLushort>& indices)  { glDrawElements(GL_LINE_STRIP,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_SHORT,&indices[0]); }
            inline void     drawLineLoop        (const vector<GLushort>& indices)  { glDrawElements(GL_LINE_LOOP,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_SHORT,&indices[0]); }
            inline void     drawLines           (const vector<GLushort>& indices)  { glDrawElements(GL_LINES,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_SHORT,&indices[0]); }
            inline void     drawTriangleStrip   (const vector<GLushort>& indices)  { glDrawElements(GL_TRIANGLE_STRIP,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_SHORT,&indices[0]); }
            inline void     drawTriangleFan     (const vector<GLushort>& indices)  { glDrawElements(GL_TRIANGLE_FAN,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_SHORT,&indices[0]); }
            inline void     drawTriangles       (const vector<GLushort>& indices)  { glDrawElements(GL_TRIANGLES,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_SHORT,&indices[0]); }
            
            
            
            
            
            
            
            namespace cc
            {
                namespace attribute
                {
                    namespace name
                    {
                        static const char *   position                    = GLProgram::ATTRIBUTE_NAME_POSITION;
                        static const char *   coordinate                  = GLProgram::ATTRIBUTE_NAME_TEX_COORD;
                        static const char *   color                       = GLProgram::ATTRIBUTE_NAME_COLOR;
                    }
                    
                    namespace location
                    {
                        constexpr static int            position                    = GLProgram::VERTEX_ATTRIB_POSITION;
                        constexpr static int            coordinate                  = GLProgram::VERTEX_ATTRIB_TEX_COORD;
                        constexpr static int            color                       = GLProgram::VERTEX_ATTRIB_COLOR;
                    }
                    
                    namespace flags
                    {
//                        constexpr static int            position                    = kCCVertexAttribFlag_Position;
//                        constexpr static int            coordinate                  = kCCVertexAttribFlag_TexCoords;
//                        constexpr static int            color                       = kCCVertexAttribFlag_Color;
                    }
                }
                
                namespace uniform
                {
                    namespace name
                    {
//                        constexpr static const char * matrix_p          = kCCUniformPMatrix_s;
//                        constexpr static const char * matrix_mv         = kCCUniformMVMatrix_s;
//                        constexpr static const char * matrix_mvp        = kCCUniformMVPMatrix_s;
//                        constexpr static const char * time              = kCCUniformTime_s;
//                        constexpr static const char * time_sin          = kCCUniformSinTime_s;
//                        constexpr static const char * time_cos          = kCCUniformCosTime_s;
//                        constexpr static const char * random01          = kCCUniformRandom01_s;
//                        constexpr static const char * sampler           = kCCUniformSampler_s;
//                        constexpr static const char * alphatestvalue    = kCCUniformAlphaTestValue;
                    }
                    
                    namespace location
                    {
//                        constexpr static const int matrix_p     = kCCUniformPMatrix;
//                        constexpr static const int matrix_mv    = kCCUniformMVMatrix;
//                        constexpr static const int matrix_mvp   = kCCUniformMVPMatrix;
//                        constexpr static const int time         = kCCUniformTime;
//                        constexpr static const int time_sin     = kCCUniformSinTime;
//                        constexpr static const int time_cos     = kCCUniformCosTime;
//                        constexpr static const int random01     = kCCUniformRandom01;
//                        constexpr static const int sampler      = kCCUniformSampler;
                    }
                }
                
                namespace program
                {
                    inline CCGLProgramPtr create(string vertex, string fragment, map<string,GLuint> attributes)
                    {
                        auto program = new CCGLProgram();
                        
                        program -> initWithByteArrays(vertex.c_str(),fragment.c_str());
                        
                        for(auto e:attributes)
                        {
                            program -> bindAttribLocation(e.first.c_str(),e.second);
                        }
                        
                        program -> link();
                        
                        program -> updateUniforms();
                        
                        return program;
                    }
                    
                    inline void use(CCGLProgramPtr program)
                    {
                            // 2
                        program -> use();
                            // 3
                        program -> setUniformsForBuiltins();
                            //                            ccGLBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );
                        
                    }
                    
                    inline void use(CCGLProgramPtr program, int flags)
                    {
                            // 0 see CC_NODE_DRAW_SETUP() in ccMacros.h
                            //                            ccGLEnable(m_eGLServerState);
                            // 1
//                        attribute::flags::enable(flags);
                            // 2
                        program -> use();
                            // 3
                        program -> setUniformsForBuiltins();
                            //                            ccGLBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );
                        
                    }
                    
                    namespace name
                    {
//                        constexpr static const char * PositionTextureColor              = kCCShader_PositionTextureColor;
//                        constexpr static const char * PositionTextureColorAlphaTest     = kCCShader_PositionTextureColorAlphaTest;
//                        constexpr static const char * PositionColor                     = kCCShader_PositionColor;
//                        constexpr static const char * PositionTexture                   = kCCShader_PositionTexture;
//                        constexpr static const char * PositionTexture_uColor            = kCCShader_PositionTexture_uColor;
//                        constexpr static const char * PositionTextureABColor            = kCCShader_PositionTextureA8Color;
//                        constexpr static const char * Position_uColor                   = kCCShader_Position_uColor;
//                        constexpr static const char * PositionLengthTextureColor        = kCCShader_PositionLengthTexureColor;
//                        constexpr static const char * ControlSwitch                     = kCCShader_ControlSwitch;
                    }
                    
                    inline CCGLProgramPtr get(const char * name)
                    {
                        return CCShaderCache::getInstance() -> getGLProgram(name);
                    }
                    
#if 0
                    namespace engage
                    {
                        inline void PositionTextureColor(CCGLProgramPtr program,
                                                         GLuint texture,
                                                         const vector<ColorRGBA>& colors,
                                                         const vector<PositionXY>& positions,
                                                         const vector<TextureXY>& coordinates)
                        {
                            gl::cc::program::use(program,gl::cc::attribute::flags::position|gl::cc::attribute::flags::coordinate|gl::cc::attribute::flags::color);
                            ccGLErrorLog();
                            gl::texture::activate(GL_TEXTURE0);
                            ccGLErrorLog();
                            gl::texture::bindFlat(texture); // "name" ie generated texture id
                            ccGLErrorLog();
                            gl::program::uniform::set(program -> getUniformLocationForName(gl::cc::uniform::name::sampler),
                                                      0); // ie GL_TEXTUER0
                            ccGLErrorLog();
                            gl::vertex::attribute::array::link(gl::cc::attribute::location::color, colors);
                            ccGLErrorLog();
                            gl::vertex::attribute::array::link(gl::cc::attribute::location::position, positions);
                            ccGLErrorLog();
                            gl::vertex::attribute::array::link(gl::cc::attribute::location::coordinate, coordinates);
                            ccGLErrorLog();
                        }
                        
                        inline void PositionColor(CCGLProgramPtr program,
                                                  const vector<PositionXY>& positions,
                                                  const vector<ColorRGBA>& colors)
                        {
                            gl::cc::program::use(program,gl::cc::attribute::flags::position|gl::cc::attribute::flags::color);
                            ccGLErrorLog();
                            gl::vertex::attribute::array::link(gl::cc::attribute::location::color, colors);
                            ccGLErrorLog();
                            gl::vertex::attribute::array::link(gl::cc::attribute::location::position, positions);
                            ccGLErrorLog();
                        }
                        
                        inline void PositionTexture(CCGLProgramPtr program,
                                                    GLuint texture,
                                                    const vector<PositionXY>& positions,
                                                    const vector<TextureXY>& coordinates)
                        {
                            gl::cc::program::use(program,gl::cc::attribute::flags::position|gl::cc::attribute::flags::coordinate);
                            ccGLErrorLog();
                            gl::texture::activate(GL_TEXTURE0);
                            ccGLErrorLog();
                            gl::texture::bindFlat(texture); // "name" ie generated texture id
                            ccGLErrorLog();
                            gl::program::uniform::set(program -> getUniformLocationForName(gl::cc::uniform::name::sampler),
                                                      0); // ie GL_TEXTUER0
                            ccGLErrorLog();
                            gl::vertex::attribute::array::link(gl::cc::attribute::location::position, positions);
                            ccGLErrorLog();
                            gl::vertex::attribute::array::link(gl::cc::attribute::location::coordinate, coordinates);
                            ccGLErrorLog();
                        }
                        
                        inline void PositionTexture_uColor(CCGLProgramPtr program,
                                                           GLuint texture,
                                                           Color4F color,
                                                           const vector<PositionXY>& positions,
                                                           const vector<TextureXY>& coordinates)
                        {
                            gl::cc::program::use(program,gl::cc::attribute::flags::position|gl::cc::attribute::flags::coordinate);
                            ccGLErrorLog();
                            gl::texture::activate(GL_TEXTURE0);
                            ccGLErrorLog();
                            gl::texture::bindFlat(texture); // "name" ie generated texture id
                            ccGLErrorLog();
                            gl::program::uniform::set(program -> getUniformLocationForName(gl::cc::uniform::name::sampler),
                                                      0); // ie GL_TEXTUER0
                            ccGLErrorLog();
                            gl::program::uniform::set(program -> getUniformLocationForName("u_color"),
                                                      color.r,
                                                      color.g,
                                                      color.b,
                                                      color.a);
                            ccGLErrorLog();
                            gl::vertex::attribute::array::link(gl::cc::attribute::location::position, positions);
                            ccGLErrorLog();
                            gl::vertex::attribute::array::link(gl::cc::attribute::location::coordinate, coordinates);
                            ccGLErrorLog();
                        }
                        
                        inline void Position_uColor(CCGLProgramPtr program,
                                                    Color4F color,
                                                    const vector<PositionXY>& positions)
                        {
                            gl::cc::program::use(program,gl::cc::attribute::flags::position|gl::cc::attribute::flags::coordinate);
                            ccGLErrorLog();
                            gl::program::uniform::set(program -> getUniformLocationForName("u_color"),
                                                      color.r,
                                                      color.g,
                                                      color.b,
                                                      color.a);
                            ccGLErrorLog();
                            gl::vertex::attribute::array::link(gl::cc::attribute::location::position, positions);
                            ccGLErrorLog();
                        }
                    } // engage
#endif
                    
                } // program
                
            } // cc
            

            
            
            inline void fillRectangle(Color4F color, CCPoint ll, CCPoint tr)
            {
                tAssert(0);
#if 0
                vector<PositionXY> points = {{ll.x,ll.y},{tr.x,ll.y},{tr.x,tr.y},{ll.x,tr.y}};
                cc::program::engage::Position_uColor(cc::program::get(cc::program::name::Position_uColor),
                                                     color,
                                                     points);
                drawTriangleFan(0,4);
                ccGLErrorLog();
                
                CC_INCREMENT_GL_DRAWS(1);
#endif
            }
            
            inline void fillRectangle(Color4F color, CCPoint ll, CCSize size)
            {
                tAssert(0);
#if 0
                vector<PositionXY> points = {{ll.x,ll.y},{ll.x+size.width,ll.y},{ll.x+size.width,ll.y+size.height},{ll.x,ll.y+size.height}};
                cc::program::engage::Position_uColor(cc::program::get(cc::program::name::Position_uColor),
                                                     color,
                                                     points);
                drawTriangleFan(0,4);
                ccGLErrorLog();
                
                CC_INCREMENT_GL_DRAWS(1);
#endif
            }
            
            inline void fillDots(Color4F color, float diameter, const vector<PositionXY>& locations)
            {
                tAssert(0);
#if 0
                cc::program::engage::Position_uColor(cc::program::get(cc::program::name::Position_uColor),
                                                     color,
                                                     locations);
                drawPoints(0,locations.size());
                ccGLErrorLog();
                
                CC_INCREMENT_GL_DRAWS(1);
#endif
            }
            
            
            
            
            namespace custom
            {
                namespace shader
                {
                    namespace fragment
                    {
                        constexpr static const char * f1 =
                        "precision lowp float; "
                        "uniform vec4 u_color;"
                        "varying vec2 v_texCoord;"
                        "uniform sampler2D CC_Texture0;"
                        "void main()"
                        "{"
                        "gl_FragColor = texture2D(CC_Texture0, v_texCoord) * u_color;"
                        "}";
                    } // fragment
                    
                } // shader
                
            } // custom
            
            
            
            
            
        } // gl
        
        
        
    }
}