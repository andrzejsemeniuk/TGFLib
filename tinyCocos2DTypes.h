    //
    //  CommonCocos2D.h
    //  productWhackyChoir
    //
    //  Created by andrzej semeniuk on 10/22/12.
    //
    //

#pragma once

#include "cocos2d.h"
//#include "CCDrawingPrimitives.h"

#include "tiny.h"

#include <vector>
#include <list>

#define ccDeclare1(TYPE) \
typedef cocos2d:: TYPE                  CC##TYPE; \
typedef cocos2d:: TYPE *                CC##TYPE##Ptr; \
typedef const cocos2d:: TYPE *          CC##TYPE##CPtr; \
typedef cocos2d:: TYPE &                CC##TYPE##Ref; \
typedef const cocos2d:: TYPE &          CC##TYPE##CRef;

#define ccDeclare2(TYPE,NAME) \
typedef cocos2d:: TYPE                  NAME; \
typedef cocos2d:: TYPE *                NAME##Ptr; \
typedef const cocos2d:: TYPE *          NAME##CPtr; \
typedef cocos2d:: TYPE &                NAME##Ref; \
typedef const cocos2d:: TYPE &          NAME##CRef;

ccDeclare1(Acceleration);
ccDeclare1(Action);
ccDeclare1(ActionEase);
ccDeclare1(ActionInstant);
ccDeclare1(ActionInterval);
ccDeclare1(Animate);
ccDeclare1(Animation);
ccDeclare1(Application);
ccDeclare2(ValueVector,CCArray);

ccDeclare1(BezierBy);
ccDeclare1(BezierTo);
ccDeclare1(BlendFunc);
ccDeclare1(BlendProtocol);
ccDeclare2(BlendFunc,CCBlending);

ccDeclare1(DelayTime);
ccDeclare2(ValueMap,CCDictionary);
ccDeclare1(DrawNode);

ccDeclare1(EaseIn);
ccDeclare1(EaseOut);
ccDeclare1(EaseInOut);
ccDeclare1(EaseBackIn);
ccDeclare1(EaseBackOut);
ccDeclare1(EaseBackInOut);
ccDeclare1(EaseBounceIn);
ccDeclare1(EaseBounceOut);
ccDeclare1(EaseBounceInOut);
ccDeclare1(EaseElasticIn);
ccDeclare1(EaseElasticOut);
ccDeclare1(EaseElasticInOut);
ccDeclare1(EaseExponentialIn);
ccDeclare1(EaseExponentialOut);
ccDeclare1(EaseExponentialInOut);
ccDeclare1(EaseRateAction);
ccDeclare1(EaseSineIn);
ccDeclare1(EaseSineOut);
ccDeclare1(EaseSineInOut);
ccDeclare1(EaseIn);
ccDeclare1(EaseOut);
ccDeclare1(EaseInOut);
ccDeclare1(EaseBackIn);
ccDeclare1(EaseBackOut);
ccDeclare1(EaseBackInOut);
ccDeclare1(EaseBounceIn);
ccDeclare1(EaseBounceOut);
ccDeclare1(EaseBounceInOut);
ccDeclare1(EaseElasticIn);
ccDeclare1(EaseElasticOut);
ccDeclare1(EaseElasticInOut);
ccDeclare1(EaseExponentialIn);
ccDeclare1(EaseExponentialOut);
ccDeclare1(EaseExponentialInOut);
ccDeclare2(EaseRateAction,CCEaseRate);
ccDeclare1(EaseSineIn);
ccDeclare1(EaseSineOut);
ccDeclare1(EaseSineInOut);
ccDeclare1(Event);
ccDeclare1(EventListenerTouchOneByOne);

ccDeclare1(FiniteTimeAction);
ccDeclare1(FileUtils);

ccDeclare1(GLProgram);

ccDeclare1(Image);

ccDeclare1(Label);
ccDeclare1(LabelTTF);
ccDeclare1(Layer);
ccDeclare1(LayerGradient);
ccDeclare1(LayerColor);

ccDeclare1(MoveBy);
ccDeclare1(MoveTo);

ccDeclare1(Node);

ccDeclare2(Ref,CCObject);

ccDeclare1(ParticleSystem);

ccDeclare1(RenderTexture);
ccDeclare1(Repeat);
ccDeclare1(RepeatForever);

ccDeclare1(Scene);
ccDeclare1(Sequence);
ccDeclare1(Spawn);
ccDeclare1(Speed);
ccDeclare1(Sprite);
ccDeclare1(SpriteFrame);
ccDeclare1(SpriteFrameCache);
ccDeclare1(SpriteBatchNode);
ccDeclare1(Value);

ccDeclare1(TargetedAction);
ccDeclare1(Texture2D);
ccDeclare1(Touch);
ccDeclare1(TransitionScene);


ccDeclare1(CallFunc);
ccDeclare1(CallFuncN);
//ccDeclare1(CallFuncND);
//ccDeclare1(CallFuncO);

ccDeclare1(FadeIn);
ccDeclare1(FadeOut);
ccDeclare1(FadeTo);
ccDeclare2(FadeTo,CCOpacityTo);

ccDeclare1(Point);
ccDeclare2(Point,CCRatio);
ccDeclare2(Point,CCVector);
ccDeclare2(Point,CCWorldPoint);
ccDeclare2(Point,CCLocalPoint);
ccDeclare2(Point,CCWorldPoint);

ccDeclare1(Renderer);
ccDeclare1(RotateBy);
ccDeclare1(RotateTo);

ccDeclare1(Rect);

ccDeclare1(Scene);

ccDeclare1(ScaleBy);
ccDeclare1(ScaleTo);
ccDeclare1(SkewBy);
ccDeclare1(SkewTo);
ccDeclare1(Size);

ccDeclare1(TextHAlignment);
ccDeclare1(TextVAlignment);
ccDeclare1(TintBy);
ccDeclare1(TintTo);
ccDeclare2(TintBy,CCColorBy);
ccDeclare2(TintTo,CCColorTo);

ccDeclare1(Touch);

ccDeclare2(ccBezierConfig,ccBezierConfig);



typedef std::pair<CCSpritePtr,CCSpritePtr>              PairOfSprites;
typedef std::vector<CCSpritePtr>                        VectorOfSprites;
typedef std::pair<cocos2d::Point,cocos2d::Point>        PairOfPoints;
typedef std::vector<cocos2d::Point>                     VectorOfPoints;
typedef std::vector<cocos2d::Point> &                   VectorOfPointsRef;
typedef const std::vector<cocos2d::Point> &             VectorOfPointsCRef;

typedef Span<ubyte>                                     spanub;
typedef Span<GLubyte>                                   spanGLub;

typedef int pixels;
typedef int Pixels;


#define ccNodeDrawMethodDeclarationArguments            Renderer* renderer, const Mat4 &transform, uint32_t flags
#define ccNodeDrawMethodArguments                       renderer,transform,flags


