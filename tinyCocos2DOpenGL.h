    //
    //  CommonOpenGL.h
    //  productHoHoHo
    //
    //  Created by andrzej semeniuk on 11/23/12.
    //
    //

#pragma once

#include "tiny.h"

#include "tinyCocos2D.h"


typedef cocos2d::CCGLProgram * CCGLProgramPtr;


namespace tiny {
    
    namespace Cocos2D {
        
        
        namespace OpenGL {
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            void init();
            
            
            
            void drawPositionsAndColor(int mode,
                                       GLsizei count,
                                       void * positions,
                                       Color4F color);
            
            void drawPositionsAndColorWithTriangleStrip(GLsizei count,
                                                        void * positions,
                                                        Color4F color);
            
            void drawPositionsAndColors(int mode,
                                        GLsizei count,
                                        void * positions,
                                        void * colors);
            
            void drawPositionsAndColorsWithTriangleStrip(GLsizei count,
                                                         void * positions,
                                                         void * colors);
            
            void drawPositionsAndTexels(int mode,
                                        GLsizei count,
                                        void * positions,
                                        void * texels);
            
            void drawPositionsAndTexelsWithTriangleStrip(GLsizei count,
                                                         void * positions,
                                                         void * texels);
            
            
            
            
            
            
            
        } // OpenGL
        
        
        
        
        
        
        
        
    } // Cocos2D
    
} // Common
