    //
    //  tinyCocos2DOperator.cpp
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 9/16/14.
    //
    //



#include "tinyCocos2DOperator.h"


namespace tiny
{
    namespace Cocos2D
    {
        
        
        
        CCOperators         CCOperators::operator +      (CCOperatorsCRef p) const
        {
            CCOperators r;
            r.operators.reserve(r.operators.size()+p.operators.size());
            for(auto o:operators)
            {
                r.operators.push_back(o);
            }
            for(auto o:p.operators)
            {
                r.operators.push_back(o);
            }
            return r;
        }
        
        
        CCOperatorsRef      CCOperators::add             (CCOperatorsCRef p)
        {
            operators.reserve(operators.size()+p.operators.size());
            for(auto o:p.operators)
            {
                operators.push_back(o);
            }
            return *this;
        }
        
        
        CCOperatorsRef      CCOperators::insert          (CCOperatorsCRef p, int i)
        {
            operators.reserve(operators.size()+p.operators.size());
            operators.insert(operators.begin()+i,p.operators.begin(),p.operators.end());
            return *this;
        }
        

        bool                CCOperators::run             (CCOperandCRef p, bool continueIfFail)
        {
            bool r = true;
            for(autoRef o:operators)
            {
                if (not o(p))
                {
                    r = false;
                    if (not continueIfFail)
                    {
                        break;
                    }
                }
            }
            return r;
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        void CCOverlay::apply(bool clear)
        {
            if (sprite)
            {
                if (ccParentOf(sprite))
                {
                    ccAlign(sprite);
                }
                CCOperand o = CCOperand::createWithSprite(sprite);
                operators.run(o);
            }
            if (clear)
            {
                operators.clear();
            }
        }
        
 
        
        
        
        void         ccOperateOnNode             (CCNodePtr node, std::vector<CCOperator> o)
        {
            CCOperators(o).applyToNode(node);
        }
        
        void         ccOperateOnSprite           (CCSpritePtr node, std::vector<CCOperator> o)
        {
            CCOperators(o).applyToSprite(node);
        }
        
        void         ccOperateOnNodes            (std::vector<CCNodePtr> nodes, std::vector<CCOperator> o)
        {
            for(auto n:nodes)
            {
                ccOperateOnNode(n,o);
            }
        }
        
        void         ccOperateOnSprites          (std::vector<CCSpritePtr> nodes, std::vector<CCOperator> o)
        {
            for(auto n:nodes)
            {
                ccOperateOnSprite(n,o);
            }
        }

        void         ccOperateOnNodesExcept      (std::vector<CCNodePtr> nodes, CCNodePtr node, std::vector<CCOperator> o)
        {
            for(auto n:nodes)
            {
                if (n != node)
                {
                    ccOperateOnNode(n,o);
                }
            }
        }
        
        void         ccOperateOnSpritesExcept    (std::vector<CCSpritePtr> nodes, CCSpritePtr node, std::vector<CCOperator> o)
        {
            for(auto n:nodes)
            {
                if (n != node)
                {
                    ccOperateOnSprite(n,o);
                }
            }
        }
        
        void         ccOperateOnNodesExcept      (std::vector<CCNodePtr> nodes, CCNodePtr node, std::vector<CCOperator> o, std::vector<CCOperator> alternate)
        {
            for(auto n:nodes)
            {
                if (n != node)
                    ccOperateOnNode(n,o);
                else
                    ccOperateOnNode(node,alternate);
            }
        }
        
        void         ccOperateOnSpritesExcept    (std::vector<CCSpritePtr> nodes, CCSpritePtr node, std::vector<CCOperator> o, std::vector<CCOperator> alternate)
        {
            for(auto n:nodes)
            {
                if (n != node)
                    ccOperateOnSprite(n,o);
                else
                    ccOperateOnSprite(node,alternate);
            }
        }
        void         ccOperateOnNodesExcept      (std::vector<CCNodePtr> nodes, int index, std::vector<CCOperator> o)
        {
            loopUpTo(i,nodes.size())
            {
                if (i != index)
                {
                    ccOperateOnNode(nodes[i],o);
                }
            }
        }
        
        void         ccOperateOnSpritesExcept    (std::vector<CCSpritePtr> nodes, int index, std::vector<CCOperator> o)
        {
            loopUpTo(i,nodes.size())
            {
                if (i != index)
                {
                    ccOperateOnSprite(nodes[i],o);
                }
            }
        }
        
        void         ccOperateOnNodesExcept      (std::vector<CCNodePtr> nodes, int index, std::vector<CCOperator> o, std::vector<CCOperator> alternate)
        {
            loopUpTo(i,nodes.size())
            {
                if (i != index)
                    ccOperateOnNode(nodes[i],o);
                else
                    ccOperateOnNode(nodes[i],alternate);
            }
        }
        
        void         ccOperateOnSpritesExcept    (std::vector<CCSpritePtr> nodes, int index, std::vector<CCOperator> o, std::vector<CCOperator> alternate)
        {
            loopUpTo(i,nodes.size())
            {
                if (i != index)
                    ccOperateOnSprite(nodes[i],o);
                else
                    ccOperateOnSprite(nodes[i],alternate);
            }
        }

        
        
        
        
        void         ccOperateOnNodesExcept      (std::vector<CCNodePtr> nodes, std::set<CCNodePtr> except, std::vector<CCOperator> o)
        {
            for(auto n:nodes)
            {
                if (not contains(except,n))
                {
                    ccOperateOnNode(n,o);
                }
            }
        }
        
        void         ccOperateOnSpritesExcept    (std::vector<CCSpritePtr> nodes, std::set<CCSpritePtr> except, std::vector<CCOperator> o)
        {
            for(auto n:nodes)
            {
                if (not contains(except,n))
                {
                    ccOperateOnSprite(n,o);
                }
            }
        }
        
        void         ccOperateOnNodesExcept      (std::vector<CCNodePtr> nodes, std::set<CCNodePtr> except, std::vector<CCOperator> o, std::vector<CCOperator> alternate)
        {
            for(auto n:nodes)
            {
                if (not contains(except,n))
                    ccOperateOnNode(n,o);
                else
                    ccOperateOnNode(n,alternate);
            }
        }
        
        void         ccOperateOnSpritesExcept    (std::vector<CCSpritePtr> nodes, std::set<CCSpritePtr> except, std::vector<CCOperator> o, std::vector<CCOperator> alternate)
        {
            for(auto n:nodes)
            {
                if (not contains(except,n))
                    ccOperateOnSprite(n,o);
                else
                    ccOperateOnSprite(n,alternate);
            }
        }
        void         ccOperateOnNodesExcept      (std::vector<CCNodePtr> nodes, std::set<int> except, std::vector<CCOperator> o)
        {
            loopUpTo(i,nodes.size())
            {
                if (not contains(except,i))
                {
                    ccOperateOnNode(nodes[i],o);
                }
            }
        }
        
        void         ccOperateOnSpritesExcept    (std::vector<CCSpritePtr> nodes, std::set<int> except, std::vector<CCOperator> o)
        {
            loopUpTo(i,nodes.size())
            {
                if (not contains(except,i))
                {
                    ccOperateOnSprite(nodes[i],o);
                }
            }
        }
        
        void         ccOperateOnNodesExcept      (std::vector<CCNodePtr> nodes, std::set<int> except, std::vector<CCOperator> o, std::vector<CCOperator> alternate)
        {
            loopUpTo(i,nodes.size())
            {
                if (not contains(except,i))
                    ccOperateOnNode(nodes[i],o);
                else
                    ccOperateOnNode(nodes[i],alternate);
            }
        }
        
        void         ccOperateOnSpritesExcept    (std::vector<CCSpritePtr> nodes, std::set<int> except, std::vector<CCOperator> o, std::vector<CCOperator> alternate)
        {
            loopUpTo(i,nodes.size())
            {
                if (not contains(except,i))
                    ccOperateOnSprite(nodes[i],o);
                else
                    ccOperateOnSprite(nodes[i],alternate);
            }
        }

        
        
        
        
        static CCOperators::ExaminationPtr  __examination           = 0;
        
        static int                          __examinationStep       = 0;
        
        
        
        void CCOperators::Examination::Field::set    (range r)
        {
            this->step      = __examinationStep;
            this->assigned  = true;
            this->span      = r;
        }
        
        void CCOperators::Examination::Field::set    (float v)
        {
            this->set({v,v});
        }

        bool CCOperators::Examination::Field::get (float & v0, float d0, float & v1, float d1) const
        {
            if (assigned)
            {
                v0 = span.from;
                v1 = span.to;
            }
            else
            {
                v0 = d0;
                v1 = d1;
            }
            return assigned;
        }

        
        CCOperators::Examination CCOperators::examine(CCOperand o) const
        {
            Examination r;
            
            __examination = &r;
            
            __examinationStep = 0;
            
            for(auto operation:operators)
            {
                __examinationStep++;
                operation(o);
            }
            
            __examination = 0;
            
            return r;
        }
        

        
        
        
        
        
        
        
        
        static void __examineAlignment(float FROMX, float FROMY, float TOX, float TOY)
        {
            if (__examination)
            {
                __examination->alignment.from.x.set(FROMX);
                __examination->alignment.from.y.set(FROMY);
                __examination->alignment.to.x.set(TOX);
                __examination->alignment.to.y.set(TOY);
            }
        }

        static void __examineAlignmentX(float FROMX, float TOX)
        {
            if (__examination)
            {
                __examination->alignment.from.x.set(FROMX);
                __examination->alignment.to.x.set(TOX);
            }
        }
        
        static void __examineAlignmentY(float FROMY, float TOY)
        {
            if (__examination)
            {
                __examination->alignment.from.y.set(FROMY);
                __examination->alignment.to.y.set(TOY);
            }
        }

        static void __examineAlignment(range FROMX, range FROMY, range TOX, range TOY)
        {
            if (__examination)
            {
                __examination->alignment.from.x.set(FROMX);
                __examination->alignment.from.y.set(FROMY);
                __examination->alignment.to.x.set(TOX);
                __examination->alignment.to.y.set(TOY);
            }
        }
        
        static void __examineAlignmentX(range FROMX, range TOX)
        {
            if (__examination)
            {
                __examination->alignment.from.x.set(FROMX);
                __examination->alignment.to.x.set(TOX);
            }
        }

        static void __examineAlignmentY(range FROMY, range TOY)
        {
            if (__examination)
            {
                __examination->alignment.from.y.set(FROMY);
                __examination->alignment.to.y.set(TOY);
            }
        }
        

        CCOperator   oAlign          (CCRatio r)                                    { return [r] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineAlignment({r.x,r.x},{r.y,r.y},{r.x,r.x},{r.y,r.y});                               ccAlign(n,r,r); return true; } return false; }; }
        CCOperator   oAlign          (CCRatio from, CCRatio to)                     { return [from,to] (CCOperandCRef p)    { auto n = p.asCCNodePtr(); if (n) { __examineAlignment({from.x,from.x},{from.y,from.y},{to.x,to.x},{to.y,to.y});               ccAlign(n,from,to); return true; } return false; }; }
        CCOperator   oAlign          (pair<range,range> from, CCRatio to)           { return [from,to] (CCOperandCRef p)    { auto n = p.asCCNodePtr(); if (n) { __examineAlignment(from.first,from.second,{to.x,to.x},{to.y,to.y});                      ccAlign(n,Vec2(randomRangef(from.first),randomRangef(from.second)),to); return true; } return false; }; }
        CCOperator   oAlign          (CCRatio from, pair<range,range> to)           { return [from,to] (CCOperandCRef p)    { auto n = p.asCCNodePtr(); if (n) { __examineAlignment({from.x,from.x},{from.y,from.y},to.first,to.second);                      ccAlign(n,from,Vec2(randomRangef(to.first),randomRangef(to.second))); return true; } return false; }; }
        CCOperator   oAlign          (pair<range,range> from, pair<range,range> to) { return [from,to] (CCOperandCRef p)    { auto n = p.asCCNodePtr(); if (n) { __examineAlignment(from.first,from.second,to.first,to.second);             ccAlign(n,Vec2(randomRangef(from.first),randomRangef(from.second)),Vec2(randomRangef(to.first),randomRangef(to.second))); return true; } return false; }; }
        CCOperator   oAlign          (float x, float y)                             { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examineAlignment(x,y,x,y);                                               ccAlign(n,Vec2(x,y),Vec2(x,y)); return true; } return false; }; }
        CCOperator   oAlignTo        (float x, float y)                             { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { auto a = ccAnchor(n); __examineAlignment(a.x,a.y,x,y);                     ccAlign(n,a,Vec2(x,y)); return true; } return false; }; }
        CCOperator   oAlignX         (float from, float to)                         { return [from,to] (CCOperandCRef p)    { auto n = p.asCCNodePtr(); if (n) { __examineAlignmentX(from,to);                                              ccAlignX(n,from,to); return true; } return false; }; }
        CCOperator   oAlignY         (float from, float to)                         { return [from,to] (CCOperandCRef p)    { auto n = p.asCCNodePtr(); if (n) { __examineAlignmentY(from,to);                                              ccAlignY(n,from,to); return true; } return false; }; }
        CCOperator   oAlign          (CCAlignment v)                                { return [v] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineAlignment(v.from.x,v.from.y,v.to.x,v.to.y);                               v.apply(n); return true; } return false; }; }
        CCOperator   oAlign          ()                                             { return oAlign(Vec2(.5,.5)); }

        CCOperator   oAlignToPolar   (CCAngle angle, float distance )               { auto v = Vec2(.5,.5)+angle.asVector()*distance; return oAlign(Vec2(.5,.5),v); }
        CCOperator   oAlignToPolar   (CCAngle angle)                                { return oAlignToPolar(angle,1); }
        CCOperator   oAlignToPolar   (CCRatio from, CCAngle angle, float distance)  { auto v = Vec2(.5,.5)+angle.asVector()*distance; return oAlign(from,v); }
        
        
        
        
        
        
        
        
        
        
        static void __examineBlending(CCBlending VALUE)
        {
            if (__examination) {
                __examination->blending.set({(float)VALUE.src,(float)VALUE.dst});
            }
        }

        
        CCOperator   oBlend          (CCBlending v)
        {
            return [v] (CCOperandCRef p)
            {
                auto s = p.asCCSpritePtr();
                if (s)
                {
                    __examineBlending(v);
                    s->setBlendFunc(v);
                    return true;
                }
                return false;
            };
        }
        
            //                        const BlendFunc BlendFunc::DISABLE = {GL_ONE, GL_ZERO};
            //                        const BlendFunc BlendFunc::ALPHA_PREMULTIPLIED = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA};
            //                        const BlendFunc BlendFunc::ALPHA_NON_PREMULTIPLIED = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
            //                        const BlendFunc BlendFunc::ADDITIVE = {GL_SRC_ALPHA, GL_ONE};
        
        CCOperator   oBlending       (CCBlending p)                                 { return oBlend(p); }
        
        CCOperator   oBlendDisable                  = oBlend(BlendFunc::DISABLE);
        CCOperator   oBlendAdditive                 = oBlend(BlendFunc::ADDITIVE);
        CCOperator   oBlendAlphaPremultiplied       = oBlend(BlendFunc::ALPHA_PREMULTIPLIED);
        CCOperator   oBlendAlphaNonPremultiplied    = oBlend(BlendFunc::ALPHA_NON_PREMULTIPLIED);

        
        
        
        
        
        
        

        static void __examineAnchor(float x0, float x1, float y0, float y1)
        {
            if (__examination) {
                __examination->position.x.set({x0,x1});
                __examination->position.y.set({y0,y1});
            }
        }

        
        CCOperator   oAnchor         (CCRatio r)                        { return [r] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineAnchor(r.x,r.x,r.y,r.y);              ccAnchor(n,r); return true; } return false; }; }
        CCOperator   oAnchor         (float x, float y)                 { return oAnchor(Vec2(x,y)); }
        CCOperator   oAnchor         (range x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examineAnchor(x.from,x.to,y,y);              ccAnchor(n,Vec2(randomRangef(x),y)); return true; } return false; }; }
        CCOperator   oAnchor         (float x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examineAnchor(x,x,y.from,y.to);              ccAnchor(n,Vec2(x,randomRangef(y))); return true; } return false; }; }
        CCOperator   oAnchor         (range x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examineAnchor(x.from,x.to,y.from,y.to);      ccAnchor(n,Vec2(randomRangef(x),randomRangef(y))); return true; } return false; }; }
        CCOperator   oAnchor         ()                                 { return oAnchor(Vec2(.5,.5)); }
        
        
        
        
        
        
        
        static void __examineZ(int z)
        {
            if (__examination) {
                range r;
                r.from=z;
                r.to=z;
                __examination->z.set(r);
            }
        }
        
        static void __examineZ(int z0, int z1)
        {
            if (__examination) {
                range r;
                r.from=min(z0,z1);
                r.to=max(z0,z1);
                __examination->z.set(r);
            }
        }


        CCOperator   oZ              (int z)                            { return [z] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineZ(z);                         ccZOrder(n,z); return true; } return false; }; }
        CCOperator   oZAdd           (int z)                            { return [z] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineZ(z,ccZOrder(n)+z);           ccZOrder(n,ccZOrder(n)+z); return true; } return false; }; }
        CCOperator   oZGrow          (int z)                            { return [z] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineZ(z,ccZOrder(n)*z);           ccZOrder(n,ccZOrder(n)*z); return true; } return false; }; }
        CCOperator   oZFlip          ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCNodePtr(); if (n) { __examineZ(ccZOrder(n),-ccZOrder(n));  ccZOrder(n, - ccZOrder(n)); return true; } return false; }; }

        
        
        
        
        
        
        
        
        
        static void __examineSize(CCSize s0, CCSize s1)
        {
            if (__examination) {
                __examination->size.width.set({s0.width,s1.width});
                __examination->size.height.set({s0.height,s1.height});
            }
        }
        

        CCOperator   oSize           (CCSize size)                      { return [size] (CCOperandCRef p)       { auto n = p.asCCNodePtr(); if (n) { __examineSize(size,size);              ccSize(n,size); return true; } return false; }; }

        
        
        
        
        
        
        


        
        static void __examinePosition(float x, float y)
        {
            if (__examination) {
                __examination->position.x.set(x);
                __examination->position.y.set(y);
            }
        }
        
        static void __examinePositionX(range x)
        {
            if (__examination) {
                __examination->position.x.set(x);
            }
        }
        
        static void __examinePositionY(range y)
        {
            if (__examination) {
                __examination->position.y.set(y);
            }
        }
        
        static void __examinePositionXY(range x, range y)
        {
            if (__examination) {
                __examination->position.x.set(x);
                __examination->position.y.set(y);
            }
        }


        CCOperator   oPosition       (CCPoint v)                        { return [v] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examinePosition(v.x,v.y);                    ccPosition(n,v); return true; } return false; }; }
        CCOperator   oPosition       (float x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examinePosition(x,y);                        ccPosition(n,x,y); return true; } return false; }; }
        CCOperator   oPositionX      (float x)                          { return [x] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examinePositionX({x,x});                     ccPositionX(n,x); return true; } return false; }; }
        CCOperator   oPositionY      (float y)                          { return [y] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examinePositionY({y,y});                     ccPositionY(n,y); return true; } return false; }; }
        CCOperator   oPositionX      (range x)                          { return [x] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examinePositionX(x);                         ccPositionX(n,randomRangef(x)); return true; } return false; }; }
        CCOperator   oPositionY      (range y)                          { return [y] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examinePositionY(y);                         ccPositionY(n,randomRangef(y)); return true; } return false; }; }
        CCOperator   oPositionXY     (range x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examinePositionXY(x,{y,y});                  ccPosition(n,randomRangef(x),y); return true; } return false; }; }
        CCOperator   oPositionXY     (float x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examinePositionXY({x,x},y);                  ccPosition(n,x,randomRangef(y)); return true; } return false; }; }
        CCOperator   oPositionXY     (range x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examinePositionXY(x,y);                      ccPosition(n,randomRangef(x),randomRangef(y)); return true; } return false; }; }
        
        CCOperator   oPositionRatio  (CCRatio v)                        { return oPosition(screenGetPoint(v)); }

        
        
        
        
        
        
        
        
        
        
        static void __examineMoveBy(float x, float y)
        {
            if (__examination) {
                __examination->moveby.x.set(x);
                __examination->moveby.y.set(y);
            }
        }
        
        static void __examineMoveByX(range x)
        {
            if (__examination) {
                __examination->moveby.x.set(x);
            }
        }
        
        static void __examineMoveByY(range y)
        {
            if (__examination) {
                __examination->moveby.y.set(y);
            }
        }
        
        static void __examineMoveByXY(range x, range y)
        {
            if (__examination) {
                __examination->moveby.x.set(x);
                __examination->moveby.y.set(y);
            }
        }

        
        CCOperator   oMoveBy         (CCPoint v)                        { return [v] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineMoveBy(v.x,v.y);                  ccMoveBy(n,v);                          return true; } return false; }; }
        CCOperator   oMoveBy         (float x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examineMoveBy(x,y);                      ccMoveBy(n,Vec2(x,y));                  return true; } return false; }; }
        CCOperator   oMoveByX        (float x)                          { return [x] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineMoveByX({x,x});                   ccMoveByX(n,x);                         return true; } return false; }; }
        CCOperator   oMoveByY        (float y)                          { return [y] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineMoveByY({y,y});                   ccMoveByY(n,y);                         return true; } return false; }; }
        CCOperator   oMoveByX        (range x)                          { return [x] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineMoveByX(x);                       ccMoveByX(n,randomRangef(x));           return true; } return false; }; }
        CCOperator   oMoveByY        (range y)                          { return [y] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { __examineMoveByY(y);                       ccMoveByY(n,randomRangef(y));           return true; } return false; }; }
        CCOperator   oMoveByXY       (range x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examineMoveByXY(x,{y,y});                ccMoveBy(n,Vec2(randomRangef(x),y));    return true; } return false; }; }
        CCOperator   oMoveByXY       (float x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examineMoveByXY({x,x},y);                ccMoveBy(n,Vec2(x,randomRangef(y)));    return true; } return false; }; }
        CCOperator   oMoveByXY       (range x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { __examineMoveByXY(x,y);                    ccMoveBy(n,Vec2(randomRangef(x),randomRangef(y))); return true; } return false; }; }
        
        
        
        
        
        
        
        
        
        
        
        
        
        CCOperator   oScaleZero      ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCNodePtr(); if (n) { ccScaleZero(n); return true; } return false; }; }
        CCOperator   oScale          (float x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,x,y); return true; } return false; }; }
        CCOperator   oScale          (range x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,randomRangef(x),y); return true; } return false; }; }
        CCOperator   oScale          (float x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,x,randomRangef(y)); return true; } return false; }; }
        CCOperator   oScale          (range x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,randomRangef(x),randomRangef(y)); return true; } return false; }; }
        CCOperator   oScaleX         (float x)                          { return [x] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccScaleX(n,x); return true; } return false; }; }
        CCOperator   oScaleX         (range x)                          { return [x] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccScaleX(n,randomRangef(x)); return true; } return false; }; }
        CCOperator   oScaleY         (float y)                          { return [y] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccScaleY(n,y); return true; } return false; }; }
        CCOperator   oScaleY         (range y)                          { return [y] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccScaleY(n,randomRangef(y)); return true; } return false; }; }
        CCOperator   oScaleXY        (range s)                          { return oScale(s,s); }
        CCOperator   oScale          (float s)                          { return oScale(s,s); }
        CCOperator   oScale          (range s)                          { return [s] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccScale(n,randomRangef(s)); return true; } return false; }; }
        CCOperator   oScale          (CCPoint v)                        { return oScale(v.x,v.y); }

        CCOperator   oStretchXY      (float x, float y)                 { return [x,y] (CCOperandCRef p)
            {
                auto n = p.asCCNodePtr();
                if (n)
                {
                    auto p = ccParentOf(n);
                    if (p)
                    {
                        auto s0     = ccSize(p);
                        auto s1     = ccSize(n);
                        float sx    = s0.width / s1.width;
                        float sy    = s0.height / s1.height;
                        if (x and y)
                            ccScaleXY(n,x*sx,y*sy);
                        else if (x)
                            ccScaleX(n,x*sx);
                        else if (y)
                            ccScaleX(n,y*sy);
                        return true;
                    }
                }
                return false;
            };
        }
        
        CCOperator   oStretchXY      (CCRatio s)                        { return oStretchXY(s.x,s.y); }
        CCOperator   oStretchX       (float s)                          { return oStretchXY(s,0); }
        CCOperator   oStretchY       (float s)                          { return oStretchXY(0,s); }
        CCOperator   oStretch        (float s)                          { return oStretchXY(s,s); }

        CCOperator   oFlipX          (bool flag)                        { return [flag] (CCOperandCRef p)       { auto n = p.asCCSpritePtr(); if (n) { ccFlipX(n,flag); return true; } return false; }; }
        CCOperator   oFlipY          (bool flag)                        { return [flag] (CCOperandCRef p)       { auto n = p.asCCSpritePtr(); if (n) { ccFlipY(n,flag); return true; } return false; }; }
        CCOperator   oFlipXY         (bool x, bool y)                   { return [x,y] (CCOperandCRef p)        { auto n = p.asCCSpritePtr(); if (n) { ccFlipX(n,x); ccFlipY(n,y); return true; } return false; }; }

        CCOperator   oFlipXRandom    ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCSpritePtr(); if (n) { ccFlipX(n,randomBool()); return true; } return false; }; }
        CCOperator   oFlipYRandom    ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCSpritePtr(); if (n) { ccFlipY(n,randomBool()); return true; } return false; }; }
        CCOperator   oFlipXYRandom   ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCSpritePtr(); if (n) { ccFlipX(n,randomBool()); ccFlipY(n,randomBool()); return true; } return false; }; }
        
        CCOperator   oSkew           (float x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccSkewXY(n,x,y); return true; } return false; }; }
        CCOperator   oSkewX          (float x)                          { return [x] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccSkewX(n,x); return true; } return false; }; }
        CCOperator   oSkewY          (float y)                          { return [y] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccSkewY(n,y); return true; } return false; }; }
        
        CCOperator   oRotation       (float a)                          { return [a] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccRotation(n,a); return true; } return false; }; }
        CCOperator   oRotation       (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccRotation(n,randomRangef(v)); return true; } return false; }; }
        
        CCOperator   oOpacity        (float o)                          { return [o] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccOpacity(n,o); return true; } return false; }; }
        CCOperator   oOpacity        (range o)                          { return [o] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccOpacity(n,randomRangef(o)); return true; } return false; }; }
        
        CCOperator   oColorR         (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,v,c.g,c.b); return true; } return false; }; }
        CCOperator   oColorG         (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,v,c.b); return true; } return false; }; }
        CCOperator   oColorB         (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,c.g,v); return true; } return false; }; }
        CCOperator   oColorRG        (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,v,v,c.b); return true; } return false; }; }
        CCOperator   oColorRB        (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,v,c.g,v); return true; } return false; }; }
        CCOperator   oColorGB        (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,v,v); return true; } return false; }; }
        CCOperator   oColorR         (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,randomRangef(v),c.g,c.b); return true; } return false; }; }
        CCOperator   oColorG         (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,randomRangef(v),c.b); return true; } return false; }; }
        CCOperator   oColorB         (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,c.g,randomRangef(v)); return true; } return false; }; }
        CCOperator   oColorRG        (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto V = randomRangef(v); ccColor(n,V,V,c.b); return true; } return false; }; }
        CCOperator   oColorRB        (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto V = randomRangef(v); ccColor(n,V,c.g,V); return true; } return false; }; }
        CCOperator   oColorGB        (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto V = randomRangef(v); ccColor(n,c.r,V,V); return true; } return false; }; }
        CCOperator   oColorRGB       (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto V = randomRangef(v); ccColor(n,V,V,V); return true; } return false; }; }
        CCOperator   oColorA         (range v)                          { return oOpacity(v); }
        CCOperator   oColor          (double r, double g, double b)                 { return [r,g,b]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,r,g,b); return true; } return false; }; }
        CCOperator   oColor          (double r, double g, double b, double a)       { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,r,g,b); ccOpacity(n,a); return true; } return false; }; }
        CCOperator   oColor          (range r, double g, double b, double a)        { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,randomRangef(r),g,b); ccOpacity(n,a); return true; } return false; }; }
        CCOperator   oColor          (double r, range g, double b, double a)        { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,r,randomRangef(g),b); ccOpacity(n,a); return true; } return false; }; }
        CCOperator   oColor          (double r, double g, range b, double a)        { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,r,g,randomRangef(b)); ccOpacity(n,a); return true; } return false; }; }
        CCOperator   oColor          (double r, double g, double b, range a)        { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,r,g,b); ccOpacity(n,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColor          (range r, range g, double b, double a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,randomRangef(r),randomRangef(g),b); ccOpacity(n,a); return true; } return false; }; }
        CCOperator   oColor          (range r, double g, range b, double a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,randomRangef(r),g,randomRangef(b)); ccOpacity(n,a); return true; } return false; }; }
        CCOperator   oColor          (double r, range g, range b, double a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,r,randomRangef(g),randomRangef(b)); ccOpacity(n,a); return true; } return false; }; }
        CCOperator   oColor          (range r, range g, range b, double a)          { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,randomRangef(r),randomRangef(g),randomRangef(b)); ccOpacity(n,a); return true; } return false; }; }
        CCOperator   oColor          (range r, double g, double b, range a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,randomRangef(r),g,b); ccOpacity(n,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColor          (double r, range g, double b, range a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,r,randomRangef(g),b); ccOpacity(n,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColor          (double r, double g, range b, range a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,r,g,randomRangef(b)); ccOpacity(n,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColor          (range r, range g, double b, range a)          { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,randomRangef(r),randomRangef(g),b); ccOpacity(n,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColor          (range r, double g, range b, range a)          { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,randomRangef(r),g,randomRangef(b)); ccOpacity(n,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColor          (double r, range g, range b, range a)          { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,r,randomRangef(g),randomRangef(b)); ccOpacity(n,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColor          (range r, range g, range b, range a)           { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,randomRangef(r),randomRangef(g),randomRangef(b)); ccOpacity(n,randomRangef(a)); return true; } return false; }; }

        CCOperator   oColor3          (GLubyte r, GLubyte g, GLubyte b)            { return [r,g,b]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,Color3B(r,g,b)); return true; } return false; }; }
        CCOperator   oColor3          (spanGLub r, GLubyte g, GLubyte b)          { return [r,g,b]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,Color3B(random(r),g,b)); return true; } return false; }; }
        CCOperator   oColor3          (GLubyte r, spanGLub g, GLubyte b)          { return [r,g,b]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,Color3B(r,random(g),b)); return true; } return false; }; }
        CCOperator   oColor3          (GLubyte r, GLubyte g, spanGLub b)          { return [r,g,b]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,Color3B(r,g,random(b))); return true; } return false; }; }
        CCOperator   oColor3          (spanGLub r, spanGLub g, GLubyte b)        { return [r,g,b]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,Color3B(random(r),random(g),b)); return true; } return false; }; }
        CCOperator   oColor3          (spanGLub r, GLubyte g, spanGLub b)        { return [r,g,b]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,Color3B(random(r),g,random(b))); return true; } return false; }; }
        CCOperator   oColor3          (GLubyte r, spanGLub g, spanGLub b)        { return [r,g,b]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,Color3B(r,random(g),random(b))); return true; } return false; }; }
        CCOperator   oColor3          (spanGLub r, spanGLub g, spanGLub b)      { return [r,g,b]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,Color3B(random(r),random(g),random(b))); return true; } return false; }; }

        CCOperator   oColor          (Color3B c)                        { return [c] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,c); return true; } return false; }; }
        CCOperator   oColor          (Color3B c, double a)              { return [c,a] (CCOperandCRef p)        { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,c); ccOpacity(n,a); return true; } return false; }; }
        CCOperator   oColor          (Color3F c)                        { return [c] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,c); return true; } return false; }; }
        CCOperator   oColor          (Color3F c1, Color3F c2)           { return oColor(Range(c1.r,c2.r),Range(c1.g,c2.g),Range(c1.b,c2.b)); }
        CCOperator   oColor          (Color4F c)                        { return [c] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,c); ccOpacity(n,c.a); return true; } return false; }; }
        CCOperator   oColor          (Color4F c1, Color4F c2)           { return oColor(Range(c1.r,c2.r),Range(c1.g,c2.g),Range(c1.b,c2.b),Range(c1.a,c2.a)); }
        CCOperator   oColor          (HSV c)                            { return oColor(c.ccc3f()); }
        CCOperator   oColorGray      (double v)                         { return oColor(v,v,v); }
        CCOperator   oColorGray      (range v)                          { return oColorRGB(v); }
        CCOperator   oColor000        = oColor(0,0,0);
        CCOperator   oColor111        = oColor(1,1,1);
        CCOperator   oColor100        = oColor(1,0,0);
        CCOperator   oColor010        = oColor(0,1,0);
        CCOperator   oColor001        = oColor(0,0,1);
        CCOperator   oColor110        = oColor(1,1,0);
        CCOperator   oColor101        = oColor(1,0,1);
        CCOperator   oColor011        = oColor(0,1,1);
        
        CCOperator   oColorH         (float_c0360 h)                    { return [h] oBlockOnSprite( auto c = ccColorHSV(o); c.h = h; ccColorHSV(o,c); ); }
        CCOperator   oColorS         (float_01 s)                       { return [s] oBlockOnSprite( auto c = ccColorHSV(o); c.s = s; ccColorHSV(o,c); ); }
        CCOperator   oColorV         (float_01 v)                       { return [v] oBlockOnSprite( auto c = ccColorHSV(o); c.v = v; ccColorHSV(o,c); ); }
        CCOperator   oColorHS        (float_c0360 h,float_01 s)         { return [h,s] oBlockOnSprite( auto c = ccColorHSV(o); c.h = h; c.s = s; ccColorHSV(o,c); ); }
        CCOperator   oColorHV        (float_c0360 h,float_01 v)         { return [h,v] oBlockOnSprite( auto c = ccColorHSV(o); c.h = h; c.v = v; ccColorHSV(o,c); ); }
        
//        CCOperator   oColorHSV       (float_c0360 h,float_01 s,float_01 v)      { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = cccHSV(randomRangef(h),s,v); ccColor(n,c.r,c.g,c.b,a); return true; } return false; }; }
        
        
        CCOperator   oColorHSV       (float_c0360 h,float_01 s,float_01 v)              { auto c = HSVtoColor3F(h,s,v); return oColor(c.r,c.g,c.b); }
        CCOperator   oColorHSV       (range h,float_01 s,float_01 v)                    { return [h,s,v]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),s,v); ccColor(n,c.r,c.g,c.b); return true; } return false; }; }
        CCOperator   oColorHSV       (float_c0360 h,range s,float_01 v)                 { return [h,s,v]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(h,randomRangef(s),v); ccColor(n,c.r,c.g,c.b); return true; } return false; }; }
        CCOperator   oColorHSV       (float_c0360 h,float_01 s,range v)                 { return [h,s,v]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(h,s,randomRangef(v)); ccColor(n,c.r,c.g,c.b); return true; } return false; }; }
        CCOperator   oColorHSV       (range h,range s,float_01 v)                       { return [h,s,v]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),randomRangef(s),v); ccColor(n,c.r,c.g,c.b); return true; } return false; }; }
        CCOperator   oColorHSV       (range h,float_01 s,range v)                       { return [h,s,v]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),s,randomRangef(v)); ccColor(n,c.r,c.g,c.b); return true; } return false; }; }
        CCOperator   oColorHSV       (float_c0360 h,range s,range v)                    { return [h,s,v]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(h,randomRangef(s),randomRangef(v)); ccColor(n,c.r,c.g,c.b); return true; } return false; }; }
        CCOperator   oColorHSV       (range h,range s,range v)                          { return [h,s,v]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),randomRangef(s),randomRangef(v)); ccColor(n,c.r,c.g,c.b); return true; } return false; }; }
        
        CCOperator   oColorHSV       (float_c0360 h,float_01 s,float_01 v, float_01 a)  { auto c = HSVtoColor3F(h,s,v); return oColor(c.r,c.g,c.b,a); }
        CCOperator   oColorHSV       (range h,float_01 s,float_01 v, float_01 a)        { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),s,v); ccColor(n,c.r,c.g,c.b,a); return true; } return false; }; }
        CCOperator   oColorHSV       (float_c0360 h,range s,float_01 v, float_01 a)     { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(h,randomRangef(s),v); ccColor(n,c.r,c.g,c.b,a); return true; } return false; }; }
        CCOperator   oColorHSV       (float_c0360 h,float_01 s,range v, float_01 a)     { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(h,s,randomRangef(v)); ccColor(n,c.r,c.g,c.b,a); return true; } return false; }; }
        CCOperator   oColorHSV       (range h,range s,float_01 v, float_01 a)           { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),randomRangef(s),v); ccColor(n,c.r,c.g,c.b,a); return true; } return false; }; }
        CCOperator   oColorHSV       (range h,float_01 s,range v, float_01 a)           { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),s,randomRangef(v)); ccColor(n,c.r,c.g,c.b,a); return true; } return false; }; }
        CCOperator   oColorHSV       (float_c0360 h,range s,range v, float_01 a)        { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(h,randomRangef(s),randomRangef(v)); ccColor(n,c.r,c.g,c.b,a); return true; } return false; }; }
        CCOperator   oColorHSV       (range h,range s,range v, float_01 a)              { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),randomRangef(s),randomRangef(v)); ccColor(n,c.r,c.g,c.b,a); return true; } return false; }; }
        
        CCOperator   oColorHSV       (float_c0360 h,float_01 s,float_01 v, range a)     { auto c = HSVtoColor3F(h,s,v); return oColor(c.r,c.g,c.b,randomRangef(a)); }
        CCOperator   oColorHSV       (range h,float_01 s,float_01 v, range a)           { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),s,v); ccColor(n,c.r,c.g,c.b,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColorHSV       (float_c0360 h,range s,float_01 v, range a)        { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(h,randomRangef(s),v); ccColor(n,c.r,c.g,c.b,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColorHSV       (float_c0360 h,float_01 s,range v, range a)        { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(h,s,randomRangef(v)); ccColor(n,c.r,c.g,c.b,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColorHSV       (range h,range s,float_01 v, range a)              { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),randomRangef(s),v); ccColor(n,c.r,c.g,c.b,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColorHSV       (range h,float_01 s,range v, range a)              { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),s,randomRangef(v)); ccColor(n,c.r,c.g,c.b,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColorHSV       (float_c0360 h,range s,range v, range a)           { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(h,randomRangef(s),randomRangef(v)); ccColor(n,c.r,c.g,c.b,randomRangef(a)); return true; } return false; }; }
        CCOperator   oColorHSV       (range h,range s,range v, range a)                 { return [h,s,v,a]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto c = HSVtoColor3F(randomRangef(h),randomRangef(s),randomRangef(v)); ccColor(n,c.r,c.g,c.b,randomRangef(a)); return true; } return false; }; }

        
        CCOperator   oColor          (HSV a, HSV b)                     { return oColorHSV({a.h,b.h},{a.s,b.s},{a.v,b.v}); }
        CCOperator   oColor          (HSV a, HSVA b)                    { return oColorHSV({a.h,b.h},{a.s,b.s},{a.v,b.v},b.a); }
        CCOperator   oColor          (HSVA a, HSV b)                    { return oColorHSV({a.h,b.h},{a.s,b.s},{a.v,b.v},a.a); }
        CCOperator   oColor          (HSVA a, HSVA b)                   { return oColorHSV({a.h,b.h},{a.s,b.s},{a.v,b.v},{a.a,b.a}); }

        
        CCOperator   oColorH         (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.h = randomRangef(v); ccColorHSV(n,c); return true; } return false; }; }
        CCOperator   oColorS         (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.s = randomRangef(v); ccColorHSV(n,c); return true; } return false; }; }
        CCOperator   oColorV         (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.v = randomRangef(v); ccColorHSV(n,c); return true; } return false; }; }

        CCOperator   oVisible        (bool f)                           { return [f] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccVisible(n,f); return true; } return false; }; }
        CCOperator   oShow           ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCNodePtr(); if (n) { ccVisible(n,true); return true; } return false; }; }
        CCOperator   oHide           ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCNodePtr(); if (n) { ccVisible(n,false); return true; } return false; }; }
        
        CCOperator   oTag            (int t)                            { return [t] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccTag(n,t); return true; } return false; }; }
        
        
        CCOperator   oAddColor       (Color3F c)                        { return [c] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,add(ccColor(n),c.r,c.g,c.b)); return true; } return false; }; }
        CCOperator   oAddColor       (Color3B c)                        { return oAddColor(ccc3f(c)); }
        CCOperator   oAddColorR      (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r+v,c.g,c.b); return true; } return false; }; }
        CCOperator   oAddColorG      (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,c.g+v,c.b); return true; } return false; }; }
        CCOperator   oAddColorB      (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,c.g,c.b+v); return true; } return false; }; }
        CCOperator   oAddColorR      (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r+randomRangef(v),c.g,c.b); return true; } return false; }; }
        CCOperator   oAddColorG      (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,c.g+randomRangef(v),c.b); return true; } return false; }; }
        CCOperator   oAddColorB      (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,c.g,c.b+randomRangef(v)); return true; } return false; }; }
        CCOperator   oAddColorRG     (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r+a,c.g+a,c.b); return true; } return false; }; }
        CCOperator   oAddColorRB     (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r+a,c.g,c.b+a); return true; } return false; }; }
        CCOperator   oAddColorGB     (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r,c.g+a,c.b+a); return true; } return false; }; }
        CCOperator   oAddColorRGB    (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r+a,c.g+a,c.b+a); return true; } return false; }; }
        CCOperator   oAddColorH      (float_c0360 v)                    { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.h += (v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oAddColorS      (float_c01 v)                      { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.s += (v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oAddColorV      (float_c01 v)                      { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.v += (v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oAddColorH      (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.h += randomRangef(v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oAddColorS      (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.s += randomRangef(v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oAddColorV      (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.v += randomRangef(v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oAddOpacity     (float o)                          { return [o] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccOpacity(n,ccOpacity(n)+o); return true; } return false; }; }
        CCOperator   oAddOpacity     (range o)                          { return [o] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccOpacity(n,ccOpacity(n)+randomRangef(o)); return true; } return false; }; }
        CCOperator   oAddColorA      (range v)                          { return oAddOpacity(v); }
        CCOperator   oAddRotation    (float r)                          { return [r] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccRotation(n,ccRotation(n)+r); return true; } return false; }; }
        CCOperator   oAddRotation    (range r)                          { return [r] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccRotation(n,ccRotation(n)+randomRangef(r)); return true; } return false; }; }
        CCOperator   oAddPosition    (float x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { auto w = ccPosition(n); ccPosition(n,w.x+x,w.y+y); return true; } return false; }; }
        CCOperator   oAddPosition    (range x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { auto w = ccPosition(n); ccPosition(n,w.x+randomRangef(x),w.y+y); return true; } return false; }; }
        CCOperator   oAddPosition    (float x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { auto w = ccPosition(n); ccPosition(n,w.x+x,w.y+randomRangef(y)); return true; } return false; }; }
        CCOperator   oAddPosition    (range x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { auto w = ccPosition(n); ccPosition(n,w.x+randomRangef(x),w.y+randomRangef(y)); return true; } return false; }; }
        CCOperator   oAddScaleXY     (float x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,ccScaleX(n)+x,ccScaleY(n)+y); return true; } return false; }; }
        CCOperator   oAddScaleXY     (range x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,ccScaleX(n)+randomRangef(x),ccScaleY(n)+y); return true; } return false; }; }
        CCOperator   oAddScaleXY     (float x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,ccScaleX(n)+x,ccScaleY(n)+randomRangef(y)); return true; } return false; }; }
        CCOperator   oAddScaleXY     (range x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,ccScaleX(n)+randomRangef(x),ccScaleY(n)+randomRangef(y)); return true; } return false; }; }
        CCOperator   oAddScaleX      (float x)                          { return [x] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccScaleX(n,ccScaleX(n)+x); return true; } return false; }; }
        CCOperator   oAddScaleY      (float y)                          { return [y] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccScaleY(n,ccScaleY(n)+y); return true; } return false; }; }
        CCOperator   oAddScale       (float s)                          { return oAddScaleXY(s,s); }
        CCOperator   oAddScale       (CCPoint s)                        { return oAddScaleXY(s.x,s.y); }
        
        CCOperator   oGrowOpacity    (float o)                          { return [o] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccOpacity(n,ccOpacity(n)*o); return true; } return false; }; }
        CCOperator   oGrowOpacity    (range o)                          { return [o] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccOpacity(n,ccOpacity(n)*randomRangef(o)); return true; } return false; }; }
        CCOperator   oGrowColor      (Color3F c)                      { return [c] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { ccColor(n,multiply(ccColor(n),c.r,c.g,c.b)); return true; } return false; }; }
        CCOperator   oGrowColorR     (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r*v,c.g,c.b); return true; } return false; }; }
        CCOperator   oGrowColorG     (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,c.g*v,c.b); return true; } return false; }; }
        CCOperator   oGrowColorB     (double v)                         { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); ccColor(n,c.r,c.g,c.b*v); return true; } return false; }; }
        CCOperator   oGrowColorR     (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r*a,c.g,c.b); return true; } return false; }; }
        CCOperator   oGrowColorG     (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r,c.g*a,c.b); return true; } return false; }; }
        CCOperator   oGrowColorB     (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r,c.g,c.b*a); return true; } return false; }; }
        CCOperator   oGrowColorRG    (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r*a,c.g*a,c.b); return true; } return false; }; }
        CCOperator   oGrowColorRB    (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r*a,c.g,c.b*a); return true; } return false; }; }
        CCOperator   oGrowColorGB    (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r,c.g*a,c.b*a); return true; } return false; }; }
        CCOperator   oGrowColorRGB   (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColor(n); auto a=randomRangef(v); ccColor(n,c.r*a,c.g*a,c.b*a); return true; } return false; }; }
        CCOperator   oGrowColorH     (float_c0360 v)                    { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.h *= (v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oGrowColorS     (float_c01 v)                      { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.s *= (v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oGrowColorV     (float_c01 v)                      { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.v *= (v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oGrowColorH     (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.h *= randomRangef(v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oGrowColorS     (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.s *= randomRangef(v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oGrowColorV     (range v)                          { return [v] (CCOperandCRef p)          { auto n = p.asCCSpritePtr(); if (n) { auto c = ccColorHSV(n); c.v *= randomRangef(v); ccColor(n,c); return true; } return false; }; }
        CCOperator   oGrowPosition   (float x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { auto w = ccPosition(n); ccPosition(n,w.x*x,w.y*y); return true; } return false; }; }
        CCOperator   oGrowRotation   (float a)                          { return [a] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccRotation(n,ccRotation(n)*a); return true; } return false; }; }
        CCOperator   oGrowScaleXY    (float x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,ccScaleX(n)*x,ccScaleY(n)*y); return true; } return false; }; }
        CCOperator   oGrowScaleXY    (range x, float y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,ccScaleX(n)*randomRangef(x),ccScaleY(n)*y); return true; } return false; }; }
        CCOperator   oGrowScaleXY    (float x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,ccScaleX(n)*x,ccScaleY(n)*randomRangef(y)); return true; } return false; }; }
        CCOperator   oGrowScaleXY    (range x, range y)                 { return [x,y] (CCOperandCRef p)        { auto n = p.asCCNodePtr(); if (n) { ccScaleXY(n,ccScaleX(n)*randomRangef(x),ccScaleY(n)*randomRangef(y)); return true; } return false; }; }
        CCOperator   oGrowScaleX     (float x)                          { return [x] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccScaleX(n,ccScaleX(n)*x); return true; } return false; }; }
        CCOperator   oGrowScaleY     (float y)                          { return [y] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccScaleY(n,ccScaleY(n)*y); return true; } return false; }; }
        CCOperator   oGrowScale      (float s)                          { return oGrowScaleXY(s,s); }
        CCOperator   oGrowScale      (CCPoint s)                        { return oGrowScaleXY(s.x,s.y); }
        CCOperator   oGrowSkewX      (float x)                          { return [x] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccSkewX(n,ccSkewX(n)*x); return true; } return false; }; }
        CCOperator   oGrowSkewY      (float y)                          { return [y] (CCOperandCRef p)          { auto n = p.asCCNodePtr(); if (n) { ccSkewY(n,ccSkewY(n)*y); return true; } return false; }; }

        
        CCOperator   oGrowColorFromParent          (double r, double g, double b)                 { return [r,g,b]    (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*r,C.g*g,C.b*b); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (double r, double g, double b, double a)       { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*r,C.g*g,C.b*b);                                            ccOpacity(n,a*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (range r, double g, double b, double a)        { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*randomRangef(r),C.g*g,C.b*b);                              ccOpacity(n,a*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (double r, range g, double b, double a)        { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*r,C.g*randomRangef(g),C.b*b);                              ccOpacity(n,a*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (double r, double g, range b, double a)        { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*r,C.g*g,C.b*randomRangef(b));                              ccOpacity(n,a*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (double r, double g, double b, range a)        { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*r,C.g*g,C.b*b);                                            ccOpacity(n,randomRangef(a)*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (range r, range g, double b, double a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*randomRangef(r),C.g*randomRangef(g),C.b*b);                ccOpacity(n,a*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (range r, double g, range b, double a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*randomRangef(r),C.g*g,C.b*randomRangef(b));                ccOpacity(n,a*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (double r, range g, range b, double a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*r,C.g*randomRangef(g),C.b*randomRangef(b));                ccOpacity(n,a*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (range r, range g, range b, double a)          { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*randomRangef(r),C.g*randomRangef(g),C.b*randomRangef(b));  ccOpacity(n,a*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (range r, double g, double b, range a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*randomRangef(r),C.g*g,C.b*b);                              ccOpacity(n,randomRangef(a)*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (double r, range g, double b, range a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*r,C.g*randomRangef(g),C.b*b);                              ccOpacity(n,randomRangef(a)*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (double r, double g, range b, range a)         { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*r,C.g*g,C.b*randomRangef(b));                              ccOpacity(n,randomRangef(a)*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (range r, range g, double b, range a)          { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*randomRangef(r),C.g*randomRangef(g),C.b*b);                ccOpacity(n,randomRangef(a)*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (range r, double g, range b, range a)          { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*randomRangef(r),C.g*g,C.b*randomRangef(b));                ccOpacity(n,randomRangef(a)*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (double r, range g, range b, range a)          { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*r,C.g*randomRangef(g),C.b*randomRangef(b));                ccOpacity(n,randomRangef(a)*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }
        CCOperator   oGrowColorFromParent          (range r, range g, range b, range a)           { return [r,g,b,a]  (CCOperandCRef p)      { auto n = p.asCCSpritePtr(); if (n) { auto C = ccColor((CCSpritePtr)ccParentOf(n));  ccColor(n,C.r*randomRangef(r),C.g*randomRangef(g),C.b*randomRangef(b));  ccOpacity(n,randomRangef(a)*ccOpacity((CCSpritePtr)ccParentOf(n))); return true; } return false; }; }

        
        CCOperator   oPickFlipX      ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCSpritePtr();   if (n) { ccFlipX(n,randomBool()); return true; } return false; }; }
        CCOperator   oPickFlipY      ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCSpritePtr();   if (n) { ccFlipY(n,randomBool()); return true; } return false; }; }
        CCOperator   oPickFlipXY     ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCSpritePtr();   if (n) { ccFlipX(n,randomBool()); ccFlipY(n,randomBool()); return true; } return false; }; }
        CCOperator   oPickVisible    ()                                 { return [] (CCOperandCRef p)           { auto n = p.asCCNodePtr();     if (n) { ccVisible(n,randomBool()); return true; } return false; }; }
        
        CCOperator   oPickColor      (std::vector<Color3F> colors)      { return [colors] (CCOperandCRef p)     { auto n = p.asCCSpritePtr();   if (n) { ccColor(n,pick(colors)); return true; } return false; }; }
        CCOperator   oPickColor      (std::vector<Color4F> colors)      { return [colors] (CCOperandCRef p)     { auto n = p.asCCSpritePtr();   if (n) { ccColor(n,pick(colors)); return true; } return false; }; }

        
        static struct {
            std::map<int,int>   value;
            int                 variable = 0;
        } kit;
        
        CCOperator   oWalkColors     (std::vector<Color3F> colors)      {
            kit.variable        %= 999;
            int variable        = kit.variable++;
            kit.value[variable] = 0;
            return [colors,variable] (CCOperandCRef p) {
                auto n = p.asCCSpritePtr();
                if (n) {
                    autoRef value = kit.value[variable];
                    value %= colors.size();
                    ccColor(n,colors[value++]);
                    return true;
                }
                return false;
            };
        }
        CCOperator   oWalkColors     (std::vector<Color4F> colors)      {
            kit.variable        %= 999;
            int variable        = kit.variable++;
            kit.value[variable] = 0;
            return [colors,variable] (CCOperandCRef p) {
                auto n = p.asCCSpritePtr();
                if (n) {
                    autoRef value = kit.value[variable];
                    value %= colors.size();
                    ccColor(n,colors[value++]);
                    return true;
                }
                return false;
            };
        }

        
        
        CCOperator   oPick          (std::vector<CCOperator> o)         {
            if (o.size())
            {
                return [o] (CCOperandCRef p) mutable { return pick(o)(p); };
            }
            return [] (CCOperandCRef p) { return false; };
        }
        
         
        
        CCOperator   oFunction           (std::function<void ()> f)                     { return [f] (CCOperandCRef p)           { if (f) f(); return true; }; }
        CCOperator   oFunctionOnObject   (std::function<void (CCObjectPtr)> f)          { return [f] (CCOperandCRef p)           { auto n = p.asCCObjectPtr();  if (n) { if (f) f(n); return true; } return false; }; }
        CCOperator   oFunctionOnNode     (std::function<void (CCNodePtr)> f)            { return [f] (CCOperandCRef p)           { auto n = p.asCCNodePtr();    if (n) { if (f) f(n); return true; } return false; }; }
        CCOperator   oFunctionOnSprite   (std::function<void (CCSpritePtr)> f)          { return [f] (CCOperandCRef p)           { auto n = p.asCCSpritePtr();  if (n) { if (f) f(n); return true; } return false; }; }

        
        
    }
}