    //
    //  tinyCocos2DOperator.h
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 9/16/14.
    //
    //

#pragma once

#include "tinyCocos2D.h"


namespace tiny
{
    namespace Cocos2D
    {
        
        
        
        
        STRUCT (CCOperand)
        {
            inline CCObjectPtr  asCCObjectPtr                       () const                { return object; }
            inline CCNodePtr    asCCNodePtr                         () const                { return node; }
            inline CCSpritePtr  asCCSpritePtr                       () const                { return sprite; }
            
            CCOperand() {}
            
            static CCOperand    createWithObject                    (CCObjectPtr p)         { CCOperand r; r.object = p; return r; }
            static CCOperand    createWithNode                      (CCNodePtr p)           { CCOperand r; r.object = r.node = p; return r; }
            static CCOperand    createWithSprite                    (CCSpritePtr p)         { CCOperand r; r.object = r.node = r.sprite = p; return r; }
            
        private:
            
            CCObjectPtr     object      = 0;
            CCNodePtr       node        = 0;
            CCSpritePtr     sprite      = 0;
        };
        
        
        typedef std::function<bool (CCOperandCRef p)> CCOperator;
        
        
        
        
        STRUCT (CCOperators)
        {
            std::vector<CCOperator> operators;
            
            ______                      CCOperators                     ()                                                          {}
            ______                      CCOperators                     (int size)                                                  { operators.reserve(size); }
            ______                      CCOperators                     (std::vector<CCOperator> p)                                 { operators = p; }
            
            inline  CCOperators         operator +                      (CCOperator p) const                                        { CCOperators r = *this; r.operators.push_back(p); return r; }
            ______  CCOperators         operator +                      (CCOperatorsCRef p) const;
            
            inline  CCOperatorsRef      add                             (CCOperator p)                                              { operators.push_back(p); return *this; }
            ______  CCOperatorsRef      add                             (CCOperatorsCRef p);

            ______  CCOperatorsRef      insert                          (CCOperator p, int i = 0)                                   { operators.insert(operators.begin()+i,p); return *this; }
            ______  CCOperatorsRef      insert                          (CCOperatorsCRef p, int i = 0);

            inline  CCOperatorsRef      operator +=                     (CCOperator p)                                              { return add(p); }
            inline  CCOperatorsRef      operator +=                     (CCOperatorsCRef p)                                         { return add(p); }
            
            ______  bool                run                             (CCOperandCRef p, bool continueIfFail = true);
            inline  bool                runAll                          (CCOperandCRef p)                                           { return run(p,true); }
            
            inline  void                clear                           ()                                                          { operators.clear(); }
            
            inline  bool                applyToObject                   (CCObjectPtr p, bool continueIfFail = true)                 { return run(CCOperand::createWithObject(p),continueIfFail); }
            inline  bool                applyToNode                     (CCNodePtr p, bool continueIfFail = true)                   { return run(CCOperand::createWithNode(p),continueIfFail); }
            inline  bool                applyToSprite                   (CCSpritePtr p, bool continueIfFail = true)                 { return run(CCOperand::createWithSprite(p),continueIfFail); }
            
            
            
            STRUCT (Examination)
            {
                STRUCT (Field)
                {
                    bool    assigned    = false;
                    int     step        = 0;
                    range   span        = {0,0};
                    
                    void    set         (range r);
                    void    set         (float v);
                    
                    bool    get (float & v0, float d0, float & v1, float d1) const;
                };
                
                struct
                {
                    Field   r,g,b,h,s,v,a;
                } color;
                struct
                {
                    Field   x,y;
                } anchor, position, moveby, scale, stretch, skew, flip;
                struct
                {
                    struct
                    {
                        Field   x,y;
                    } from,to;
                } alignment;
                Field rotation;
                Field z;
                struct
                {
                    Field   width,height;
                } size;
                Field blending;
                
            };
            
            Examination                 examine                         (CCOperand a) const;
        };
        
        
        
        
        inline CCNodePtr    ccAttachNode                                (CCNodePtr parent, CCNodePtr child, std::vector<CCOperator> o)      { parent->addChild(child); CCOperators(o).run(CCOperand::createWithNode(child)); return child; }
        inline CCSpritePtr  ccAttachSprite                              (CCNodePtr parent, CCSpritePtr child, std::vector<CCOperator> o)    { parent->addChild(child); CCOperators(o).run(CCOperand::createWithSprite(child)); return child; }

        
        extern void         ccOperateOnNode                             (CCNodePtr node, std::vector<CCOperator> o);
        extern void         ccOperateOnSprite                           (CCSpritePtr node, std::vector<CCOperator> o);
        extern void         ccOperateOnNodes                            (std::vector<CCNodePtr> nodes, std::vector<CCOperator> o);
        extern void         ccOperateOnSprites                          (std::vector<CCSpritePtr> nodes, std::vector<CCOperator> o);
        
        extern void         ccOperateOnNodesExcept                      (std::vector<CCNodePtr> nodes, CCNodePtr node, std::vector<CCOperator> o);
        extern void         ccOperateOnSpritesExcept                    (std::vector<CCSpritePtr> nodes, CCSpritePtr node, std::vector<CCOperator> o);
        extern void         ccOperateOnNodesExcept                      (std::vector<CCNodePtr> nodes, CCNodePtr node, std::vector<CCOperator> o, std::vector<CCOperator> alternate);
        extern void         ccOperateOnSpritesExcept                    (std::vector<CCSpritePtr> nodes, CCSpritePtr node, std::vector<CCOperator> o, std::vector<CCOperator> alternate);
        extern void         ccOperateOnNodesExcept                      (std::vector<CCNodePtr> nodes, int index, std::vector<CCOperator> o);
        extern void         ccOperateOnSpritesExcept                    (std::vector<CCSpritePtr> nodes, int index, std::vector<CCOperator> o);
        extern void         ccOperateOnNodesExcept                      (std::vector<CCNodePtr> nodes, int index, std::vector<CCOperator> o, std::vector<CCOperator> alternate);
        extern void         ccOperateOnSpritesExcept                    (std::vector<CCSpritePtr> nodes, int index, std::vector<CCOperator> o, std::vector<CCOperator> alternate);
        extern void         ccOperateOnNodesExcept                      (std::vector<CCNodePtr> nodes, std::set<CCNodePtr> except, std::vector<CCOperator> o);
        extern void         ccOperateOnSpritesExcept                    (std::vector<CCSpritePtr> nodes, std::set<CCSpritePtr> except, std::vector<CCOperator> o);
        extern void         ccOperateOnNodesExcept                      (std::vector<CCNodePtr> nodes, std::set<CCNodePtr> except, std::vector<CCOperator> o, std::vector<CCOperator> alternate);
        extern void         ccOperateOnSpritesExcept                    (std::vector<CCSpritePtr> nodes, std::set<CCSpritePtr> except, std::vector<CCOperator> o, std::vector<CCOperator> alternate);
        extern void         ccOperateOnNodesExcept                      (std::vector<CCNodePtr> nodes, std::set<int> except, std::vector<CCOperator> o);
        extern void         ccOperateOnSpritesExcept                    (std::vector<CCSpritePtr> nodes, std::set<int> except, std::vector<CCOperator> o);
        extern void         ccOperateOnNodesExcept                      (std::vector<CCNodePtr> nodes, std::set<int> except, std::vector<CCOperator> o, std::vector<CCOperator> alternate);
        extern void         ccOperateOnSpritesExcept                    (std::vector<CCSpritePtr> nodes, std::set<int> except, std::vector<CCOperator> o, std::vector<CCOperator> alternate);
        
        extern CCOperator   oAlign                          (CCRatio r);
        extern CCOperator   oAlign                          (CCRatio from, CCRatio to);
        extern CCOperator   oAlign                          (pair<range,range> from, CCRatio to);
        extern CCOperator   oAlign                          (CCRatio from, pair<range,range> to);
        extern CCOperator   oAlign                          (pair<range,range> from, pair<range,range> to);
        extern CCOperator   oAlign                          (float x, float y);
        extern CCOperator   oAlignTo                        (float x, float y);
        extern CCOperator   oAlignX                         (float from, float to);
        extern CCOperator   oAlignY                         (float from, float to);
        extern CCOperator   oAlign                          (CCAlignment v);
        extern CCOperator   oAlign                          ();
        
        extern CCOperator   oAlignToPolar                   (CCAngle angle, float distance );
        extern CCOperator   oAlignToPolar                   (CCAngle angle);
        extern CCOperator   oAlignToPolar                   (CCRatio from, CCAngle angle, float distance);

        extern CCOperator   oBlend                          (CCBlending v);
        extern CCOperator   oBlending                       (CCBlending p);
        inline CCOperator   oBlend                          (GLenum src, GLenum dst)                                { return oBlend({src,dst}); }
//        inline CCOperator   oBlend                          (GLenum srgb, GLenum drgb, GLenum sa, GLenum da)        { return oBlend({srgb,drgb,sa,da}); }
        extern CCOperator   oBlendDisable;
        extern CCOperator   oBlendAdditive;
        extern CCOperator   oBlendAlphaPremultiplied;
        extern CCOperator   oBlendAlphaNonPremultiplied;
        
        extern CCOperator   oAnchor                         (CCRatio r);
        extern CCOperator   oAnchor                         (float x, float y);
        extern CCOperator   oAnchor                         (range x, float y);
        extern CCOperator   oAnchor                         (float x, range y);
        extern CCOperator   oAnchor                         (range x, range y);
        extern CCOperator   oAnchor                         ();
        
        extern CCOperator   oZ                              (int z);
        extern CCOperator   oZAdd                           (int z);
        extern CCOperator   oZGrow                          (int z);
        extern CCOperator   oZFlip                          ();
        
        extern CCOperator   oSize                           (CCSize size);
        
        extern CCOperator   oPosition                       (CCPoint v);
        extern CCOperator   oPosition                       (float x, float y);
        extern CCOperator   oPositionX                      (float x);
        extern CCOperator   oPositionY                      (float y);
        extern CCOperator   oPositionX                      (range x);
        extern CCOperator   oPositionY                      (range y);
        extern CCOperator   oPositionXY                     (range x, float y);
        extern CCOperator   oPositionXY                     (float x, range y);
        extern CCOperator   oPositionXY                     (range x, range y);
        
        extern CCOperator   oPositionRatio                  (CCRatio v);

        extern CCOperator   oMoveBy                         (CCPoint v);
        extern CCOperator   oMoveBy                         (float x, float y);
        extern CCOperator   oMoveByX                        (float x);
        extern CCOperator   oMoveByY                        (float y);
        extern CCOperator   oMoveByX                        (range x);
        extern CCOperator   oMoveByY                        (range y);
        extern CCOperator   oMoveByXY                       (range x, float y);
        extern CCOperator   oMoveByXY                       (float x, range y);
        extern CCOperator   oMoveByXY                       (range x, range y);

        extern CCOperator   oScaleZero                      ();
        extern CCOperator   oScale                          (float x, float y);
        extern CCOperator   oScale                          (range x, float y);
        extern CCOperator   oScale                          (float x, range y);
        extern CCOperator   oScale                          (range x, range y);
        extern CCOperator   oScaleX                         (float x);
        extern CCOperator   oScaleX                         (range x);
        extern CCOperator   oScaleY                         (float y);
        extern CCOperator   oScaleY                         (range y);
        extern CCOperator   oScaleXY                        (range s);
        extern CCOperator   oScale                          (float s);
        extern CCOperator   oScale                          (range s);
        extern CCOperator   oScale                          (CCPoint v);
        
        extern CCOperator   oStretchXY                      (float x, float y);
        extern CCOperator   oStretchXY                      (CCRatio s);
        extern CCOperator   oStretchX                       (float s);
        extern CCOperator   oStretchY                       (float s);
        extern CCOperator   oStretch                        (float s = 1);
        
        extern CCOperator   oFlipX                          (bool x = true);
        extern CCOperator   oFlipY                          (bool y = true);
        extern CCOperator   oFlipXY                         (bool x = true, bool y = true);

        extern CCOperator   oFlipXRandom                    ();
        extern CCOperator   oFlipYRandom                    ();
        extern CCOperator   oFlipXYRandom                   ();

        extern CCOperator   oSkew                           (float x, float y);
        extern CCOperator   oSkewX                          (float x);
        extern CCOperator   oSkewY                          (float y);
        extern CCOperator   oSkew                           (float x, float y);
        
        extern CCOperator   oRotation                       (float a);
        extern CCOperator   oRotation                       (range v);
        
        extern CCOperator   oOpacity                        (float o);
        extern CCOperator   oOpacity                        (range o);
        
        extern CCOperator   oColorR                         (double v=1);
        extern CCOperator   oColorG                         (double v=1);
        extern CCOperator   oColorB                         (double v=1);
        extern CCOperator   oColorRG                        (double v);
        extern CCOperator   oColorRB                        (double v);
        extern CCOperator   oColorGB                        (double v);
        extern CCOperator   oColorR                         (range v);
        extern CCOperator   oColorG                         (range v);
        extern CCOperator   oColorB                         (range v);
        extern CCOperator   oColorRG                        (range v);
        extern CCOperator   oColorRB                        (range v);
        extern CCOperator   oColorGB                        (range v);
        extern CCOperator   oColorRGB                       (range v);
        extern CCOperator   oColorA                         (range v);
        extern CCOperator   oColor                          (double r, double g, double b);
        extern CCOperator   oColor                          (double r, double g, double b, double a);
        
        extern CCOperator   oColor                          (range r, double g, double b, double a = 1);
        extern CCOperator   oColor                          (double r, range g, double b, double a = 1);
        extern CCOperator   oColor                          (double r, double g, range b, double a = 1);
        extern CCOperator   oColor                          (double r, double g, double b, range a);
        extern CCOperator   oColor                          (range r, double g, double b, range a);
        extern CCOperator   oColor                          (double r, range g, double b, range a);
        extern CCOperator   oColor                          (double r, double g, range b, range a);
        extern CCOperator   oColor                          (range r, range g, double b, double a = 1);
        extern CCOperator   oColor                          (range r, double g, range b, double a = 1);
        extern CCOperator   oColor                          (double r, range g, range b, double a = 1);
        extern CCOperator   oColor                          (range r, range g, range b, double a = 1);
        extern CCOperator   oColor                          (range r, range g, double b, range a);
        extern CCOperator   oColor                          (range r, double g, range b, range a);
        extern CCOperator   oColor                          (double r, range g, range b, range a);
        extern CCOperator   oColor                          (range r, range g, range b, range a);
        
        extern CCOperator   oColor3                         (GLubyte r, GLubyte g, GLubyte b);
        extern CCOperator   oColor3                         (spanGLub r, GLubyte g, GLubyte b);
        extern CCOperator   oColor3                         (GLubyte r, spanGLub g, GLubyte b);
        extern CCOperator   oColor3                         (GLubyte r, GLubyte g, spanGLub b);
        extern CCOperator   oColor3                         (spanGLub r, spanGLub g, GLubyte b);
        extern CCOperator   oColor3                         (spanGLub r, GLubyte g, spanGLub b);
        extern CCOperator   oColor3                         (GLubyte r, spanGLub g, spanGLub b);
        extern CCOperator   oColor3                         (spanGLub r, spanGLub g, spanGLub b);

        extern CCOperator   oColor                          (Color3B c);
        extern CCOperator   oColor                          (Color3B c, double a);
        extern CCOperator   oColor                          (Color3F c);
        extern CCOperator   oColor                          (Color3F a, Color3F b);
        extern CCOperator   oColor                          (Color4F c);
        extern CCOperator   oColor                          (Color4F a, Color4F b);
        extern CCOperator   oColor                          (HSV c);
        extern CCOperator   oColorH                         (float_c0360 h);
        extern CCOperator   oColorS                         (float_01 s);
        extern CCOperator   oColorV                         (float_01 v);
        extern CCOperator   oColorHS                        (float_c0360 h,float_01 s);
        extern CCOperator   oColorHV                        (float_c0360 h,float_01 v);
        
        extern CCOperator   oColorHSV                       (float_c0360 h,float_01 s,float_01 v);
        extern CCOperator   oColorHSV                       (range h,float_01 s,float_01 v);
        extern CCOperator   oColorHSV                       (float_c0360 h,range s,float_01 v);
        extern CCOperator   oColorHSV                       (float_c0360 h,float_01 s,range v);
        extern CCOperator   oColorHSV                       (range h,range s,float_01 v);
        extern CCOperator   oColorHSV                       (range h,float_01 s,range v);
        extern CCOperator   oColorHSV                       (float_c0360 h,range s,range v);
        extern CCOperator   oColorHSV                       (range h,range s,range v);
        
        extern CCOperator   oColorHSV                       (float_c0360 h,float_01 s,float_01 v, float_01 a);
        extern CCOperator   oColorHSV                       (range h,float_01 s,float_01 v, float_01 a);
        extern CCOperator   oColorHSV                       (float_c0360 h,range s,float_01 v, float_01 a);
        extern CCOperator   oColorHSV                       (float_c0360 h,float_01 s,range v, float_01 a);
        extern CCOperator   oColorHSV                       (range h,range s,float_01 v, float_01 a);
        extern CCOperator   oColorHSV                       (range h,float_01 s,range v, float_01 a);
        extern CCOperator   oColorHSV                       (float_c0360 h,range s,range v, float_01 a);
        extern CCOperator   oColorHSV                       (range h,range s,range v, float_01 a);
        
        extern CCOperator   oColorHSV                       (float_c0360 h,float_01 s,float_01 v, range a);
        extern CCOperator   oColorHSV                       (range h,float_01 s,float_01 v, range a);
        extern CCOperator   oColorHSV                       (float_c0360 h,range s,float_01 v, range a);
        extern CCOperator   oColorHSV                       (float_c0360 h,float_01 s,range v, range a);
        extern CCOperator   oColorHSV                       (range h,range s,float_01 v, range a);
        extern CCOperator   oColorHSV                       (range h,float_01 s,range v, range a);
        extern CCOperator   oColorHSV                       (float_c0360 h,range s,range v, range a);
        extern CCOperator   oColorHSV                       (range h,range s,range v, range a);
        
        extern CCOperator   oColor                          (HSV a, HSV b);
        extern CCOperator   oColor                          (HSV a, HSVA b);
        extern CCOperator   oColor                          (HSVA a, HSV b);
        extern CCOperator   oColor                          (HSVA a, HSVA b);

        extern CCOperator   oColorH                         (range v);
        extern CCOperator   oColorS                         (range v);
        extern CCOperator   oColorV                         (range v);
        extern CCOperator   oColorGray                      (double v);
        extern CCOperator   oColorGray                      (range v);
        extern CCOperator   oColor000;
        extern CCOperator   oColor111;
        extern CCOperator   oColor100;
        extern CCOperator   oColor010;
        extern CCOperator   oColor001;
        extern CCOperator   oColor110;
        extern CCOperator   oColor101;
        extern CCOperator   oColor011;

        extern CCOperator   oVisible                        (bool f);
        extern CCOperator   oShow                           ();
        extern CCOperator   oHide                           ();
        
        extern CCOperator   oTag                            (int t);
        
        
        extern CCOperator   oAddColor                       (Color3F c);
        extern CCOperator   oAddColor                       (Color3B c);
        extern CCOperator   oAddColorR                      (double v);
        extern CCOperator   oAddColorG                      (double v);
        extern CCOperator   oAddColorB                      (double v);
        extern CCOperator   oAddColorR                      (range v);
        extern CCOperator   oAddColorG                      (range v);
        extern CCOperator   oAddColorB                      (range v);
        extern CCOperator   oAddColorRG                     (range v);
        extern CCOperator   oAddColorRB                     (range v);
        extern CCOperator   oAddColorGB                     (range v);
        extern CCOperator   oAddColorRGB                    (range v);
        extern CCOperator   oAddColorH                      (float_c0360 h);
        extern CCOperator   oAddColorS                      (float_c01 s);
        extern CCOperator   oAddColorV                      (float_c01 v);
        extern CCOperator   oAddColorH                      (range v);
        extern CCOperator   oAddColorS                      (range v);
        extern CCOperator   oAddColorV                      (range v);
        extern CCOperator   oAddOpacity                     (float o);
        extern CCOperator   oAddOpacity                     (range o);
        extern CCOperator   oAddColorA                      (range v);
        extern CCOperator   oAddRotation                    (float r);
        extern CCOperator   oAddRotation                    (range r);
        extern CCOperator   oAddPosition                    (float x, float y);
        extern CCOperator   oAddPosition                    (range x, float y);
        extern CCOperator   oAddPosition                    (float x, range y);
        extern CCOperator   oAddPosition                    (range x, range y);
        extern CCOperator   oAddScaleXY                     (float x, float y);
        extern CCOperator   oAddScaleXY                     (range x, float y);
        extern CCOperator   oAddScaleXY                     (float x, range y);
        extern CCOperator   oAddScaleXY                     (range x, range y);
        extern CCOperator   oAddScaleX                      (float x);
        extern CCOperator   oAddScaleY                      (float y);
        extern CCOperator   oAddScale                       (float s);
        extern CCOperator   oAddScale                       (CCPoint s);
        
        extern CCOperator   oGrowOpacity                    (float o);
        extern CCOperator   oGrowOpacity                    (range o);
        extern CCOperator   oGrowColor                      (Color3F c);
        extern CCOperator   oGrowColorR                     (double v);
        extern CCOperator   oGrowColorG                     (double v);
        extern CCOperator   oGrowColorB                     (double v);
        extern CCOperator   oGrowColorR                     (range v);
        extern CCOperator   oGrowColorG                     (range v);
        extern CCOperator   oGrowColorB                     (range v);
        extern CCOperator   oGrowColorRG                    (range v);
        extern CCOperator   oGrowColorRB                    (range v);
        extern CCOperator   oGrowColorGB                    (range v);
        extern CCOperator   oGrowColorRGB                   (range v);
        extern CCOperator   oGrowColorH                     (float_c0360 h);
        extern CCOperator   oGrowColorS                     (float_c01 s);
        extern CCOperator   oGrowColorV                     (float_c01 v);
        extern CCOperator   oGrowColorH                     (range v);
        extern CCOperator   oGrowColorS                     (range v);
        extern CCOperator   oGrowColorV                     (range v);
        extern CCOperator   oGrowPosition                   (float x, float y);
        extern CCOperator   oGrowRotation                   (float a);
        extern CCOperator   oGrowScaleXY                    (float x, float y);
        extern CCOperator   oGrowScaleXY                    (range x, float y);
        extern CCOperator   oGrowScaleXY                    (float x, range y);
        extern CCOperator   oGrowScaleXY                    (range x, range y);
        extern CCOperator   oGrowScaleX                     (float x);
        extern CCOperator   oGrowScaleY                     (float y);
        extern CCOperator   oGrowScale                      (float s);
        extern CCOperator   oGrowScale                      (CCPoint s);
        extern CCOperator   oGrowSkewX                      (float x);
        extern CCOperator   oGrowSkewY                      (float y);
        
        extern CCOperator   oGrowColorFromParent                          (double r, double g, double b);
        extern CCOperator   oGrowColorFromParent                          (double r, double g, double b, double a);
        extern CCOperator   oGrowColorFromParent                          (range r, double g, double b, double a = 1);
        extern CCOperator   oGrowColorFromParent                          (double r, range g, double b, double a = 1);
        extern CCOperator   oGrowColorFromParent                          (double r, double g, range b, double a = 1);
        extern CCOperator   oGrowColorFromParent                          (double r, double g, double b, range a);
        extern CCOperator   oGrowColorFromParent                          (range r, range g, double b, double a = 1);
        extern CCOperator   oGrowColorFromParent                          (range r, double g, range b, double a = 1);
        extern CCOperator   oGrowColorFromParent                          (double r, range g, range b, double a = 1);
        extern CCOperator   oGrowColorFromParent                          (range r, range g, range b, double a = 1);
        extern CCOperator   oGrowColorFromParent                          (range r, double g, double b, range a);
        extern CCOperator   oGrowColorFromParent                          (double r, range g, double b, range a);
        extern CCOperator   oGrowColorFromParent                          (double r, double g, range b, range a);
        extern CCOperator   oGrowColorFromParent                          (range r, range g, double b, range a);
        extern CCOperator   oGrowColorFromParent                          (range r, double g, range b, range a);
        extern CCOperator   oGrowColorFromParent                          (double r, range g, range b, range a);
        extern CCOperator   oGrowColorFromParent                          (range r, range g, range b, range a);

        extern CCOperator   oPickFlipX                      ();
        extern CCOperator   oPickFlipY                      ();
        extern CCOperator   oPickFlipXY                     ();
        extern CCOperator   oPickVisible                    ();
        extern CCOperator   oPickColor                      (std::vector<Color3F> colors);
        extern CCOperator   oPickColor                      (std::vector<Color4F> colors);
        
        extern CCOperator   oWalkColors                     (std::vector<Color3F> colors);
        extern CCOperator   oWalkColors                     (std::vector<Color4F> colors);

        extern CCOperator   oPick                           (std::vector<CCOperator> operators);

        extern CCOperator   oFunction                       (std::function<void ()> f);
        extern CCOperator   oFunctionOnObject               (std::function<void (CCObjectPtr)> f);
        extern CCOperator   oFunctionOnNode                 (std::function<void (CCNodePtr)> f);
        extern CCOperator   oFunctionOnSprite               (std::function<void (CCSpritePtr)> f);

        
        
#define oBlockOnObject(...)                         (CCOperandCRef p) { if (p.asCCObjectPtr())  { auto o = p.asCCObjectPtr(); __VA_ARGS__ ; return true; } return false; }
#define oBlockOnNode(...)                           (CCOperandCRef p) { if (p.asCCNodePtr())    { auto o = p.asCCNodePtr(); __VA_ARGS__ ; return true; } return false; }
#define oBlockOnSprite(...)                         (CCOperandCRef p) { if (p.asCCSpritePtr())  { auto o = p.asCCSpritePtr(); __VA_ARGS__ ; return true; } return false; }
        
#define oBlockMutableOnObject(...)                  (CCOperandCRef p) mutable { if (p.asCCObjectPtr())  { auto o = p.asCCObjectPtr(); __VA_ARGS__ ; return true; } return false; }
#define oBlockMutableOnNode(...)                    (CCOperandCRef p) mutable { if (p.asCCNodePtr())    { auto o = p.asCCNodePtr(); __VA_ARGS__ ; return true; } return false; }
#define oBlockMutableOnSprite(...)                  (CCOperandCRef p) mutable { if (p.asCCSpritePtr())  { auto o = p.asCCSpritePtr(); __VA_ARGS__ ; return true; } return false; }
        
        
        STRUCT (CCOverlay)
        {
            string              name;
            CCSpritePtr         sprite = 0;
            CCOperators         operators;
            
            ______              CCOverlay                           ()                                                              {}
            ______              CCOverlay                           (string n) : name(n)                                            {}
            ______              CCOverlay                           (string n, bool visible) : name(n)                              { operators += oVisible(visible); }
            ______              CCOverlay                           (string n, CCOperators o) : name(n), operators(o)               {}
            ______              CCOverlay                           (string n, CCSpritePtr s) : name(n), sprite(s)                  {}
            ______              CCOverlay                           (string n, CCSpritePtr s, CCOperators o) : name(n), sprite(s), operators(o)               {}
            
            virtual void        apply                               (bool clear = true);
        };
        
        
        
        STRUCT (CCRelative) {
            enum {
                ToPrevious      = -1,
                ToRoot          = 0,
                ToFirst         = 1,
                ToSecond        = 2,
                ToThird         = 3,
                ToFourth        = 4,
                ToFifth         = 5,
                ToSixth         = 6,
                ToSeventh       = 7,
                ToEights        = 8,
                ToNineth        = 9,
                
                To1 = 1,
                To2 = 2,
                To3 = 3,
                To4 = 4,
                To5 = 5,
                To6 = 6,
                To7 = 7,
                To8 = 8,
                To9 = 9,
            };
            
            int value = ToRoot;
            
            CCRelative                  () {}
            CCRelative                  (int r) : value(r) {}
            
            inline operator int                                             () const { return value; }
            
            inline bool         isRelativeToRoot                            () const { return ToRoot==value; }
            inline bool         isRelativeToFirst                           () const { return ToFirst==value; }
            inline bool         isRelativeToPrevious                        () const { return value<0; }
        };
 
        
        
        
        inline CCNodePtr        ccAttachNode                            (CCNodePtr to, CCNodePtr of, CCOperators o)         { ccAttach(to,of); o.applyToNode(of); return of; }
        inline CCSpritePtr      ccAttachSprite                          (CCNodePtr to, CCSpritePtr of, CCOperators o)       { ccAttach(to,of); o.applyToSprite(of); return of; }
        
        
        
        inline CCSpritePtr      ccSprite                                (string filename, CCOperators o)                    { auto r = ccSprite(filename); o.applyToSprite(r); return r; }
        inline CCSpritePtr      ccSprite                                (CCTexture2DPtr t, CCOperators o)                   { auto r = ccSprite(t); o.applyToSprite(r); return r; }
        inline CCSpritePtr      ccSpriteEmpty                           (CCOperators o)                                     { auto r = ccSpriteEmpty(); o.applyToSprite(r); return r; }
        inline CCSpritePtr      ccFrame                                 (string filename, CCOperators o)                    { auto r = ccFrame(filename); o.applyToSprite(r); return r; }

        
        
    }
}