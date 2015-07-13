//
//  CommonCocos2DGeometry.h
//  productWhackyChoir
//
//  Created by andrzej semeniuk on 12/19/12.
//
//

#pragma once

#include "tinyCocos2D.h"

namespace tiny {
    namespace Cocos2D {
        namespace Geometry {
            
#define macroDefineContainersOf(NAME) \
typedef std::list< NAME > NAME##List; \
typedef std::set< NAME > NAME##Set; \
typedef std::vector< NAME > NAME##Vector; \
typedef std::list< NAME > & NAME##ListRef; \
typedef std::set< NAME > & NAME##SetRef; \
typedef std::vector< NAME > & NAME##VectorRef
            
#define macroDeclarePrimitive(NAME) \
struct NAME; \
typedef NAME * NAME##Ptr; \
typedef NAME & NAME##Ref; \
macroDefineContainersOf(NAME)
            
#define macroDefinePrimitive(NAME) \
struct NAME
            
            macroDeclarePrimitive(CCSegment);
            macroDeclarePrimitive(CCEdge);
            macroDeclarePrimitive(CCAABB);
            macroDeclarePrimitive(CCPolygon);
            macroDeclarePrimitive(CCQuadrilateral);
            macroDeclarePrimitive(CCTrapezoid);
            macroDeclarePrimitive(CCRectangle);
            macroDeclarePrimitive(CCSquare);
            macroDeclarePrimitive(CCTriangle);
            macroDeclarePrimitive(CCCircle);
            macroDeclarePrimitive(CCOval);
            macroDeclarePrimitive(CCArc);
            macroDeclarePrimitive(CCFan);
            
            
            
            
            
            macroDefineContainersOf(CCPoint);
            
            
            
            
            
            
            struct CCPoints {
                
                static float getPointDistance(const CCPoint& a, const CCPoint& b) {
                    return sqrt(powf(b.x-a.x,2) + pow(b.y-a.y,2));
                }
                
                static int getTriangleAreaSign(const CCPoint& a, const CCPoint& b, const CCPoint& c) {
                    // -1 => c is left-of ab
                    //  0 => c is collinear with ab
                    // +1 => c is right of ab
                    double area = getTriangleDoubleAreaSign(a,b,c);
                    return area < -.5 ? -1 : .5 < area ? +1 : 0;
                }
                
                static double getTriangleDoubleAreaSign(const CCPoint& a, const CCPoint& b, const CCPoint& c) {
                    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
                }
                
                static bool isPointCollinear(const CCPoint& a, const CCPoint& b, const CCPoint& c) {
                    return 0 == getTriangleAreaSign(a,b,c);
                }
                
                static bool isPointLeftOrOn(const CCPoint& a, const CCPoint& b, const CCPoint& c) {
                    return getTriangleAreaSign(a,b,c) <= 0;
                }
                
                static bool isPointLeft(const CCPoint& a, const CCPoint& b, const CCPoint& c) {
                    return getTriangleAreaSign(a,b,c) < 0;
                }
                
                static bool isPointOn(const CCPoint& a, const CCPoint& b, const CCPoint& c) {
                    return getTriangleAreaSign(a,b,c) == 0;
                }
                
                static bool isPointRight(const CCPoint& a, const CCPoint& b, const CCPoint& c) {
                    return getTriangleAreaSign(a,b,c) > 0;
                }
                
                static bool isPointRightOrOn(const CCPoint& a, const CCPoint& b, const CCPoint& c) {
                    return getTriangleAreaSign(a,b,c) >= 0;
                }
                
                static bool isPointBetween(const CCPoint& a, const CCPoint& b, const CCPoint& c) {
                    bool value = false;
                    
                    if (isPointCollinear(a,b,c ))
                    {
                        if ( not Math::equal(a.x,b.x) )
                        {
                            value = ((a.x <= c.x ) and ( c.x <= b.x )) or ((a.x >= c.x ) and ( c.x >= b.x ));
                        }
                        else
                        {
                            value = (( a.y <= c.y ) and ( c.y <= b.y )) or (( a.y >= c.y ) and ( c.y >= b.y ));
                        }
                    }
                    
                    return value;
                }
                
                static bool isIntersection(const CCPoint& a,
                                           const CCPoint& b,
                                           const CCPoint& c,
                                           const CCPoint& d)
                {
                    if ( (isPointLeft(a,b,c) xor isPointLeft(a,b,d)) and (isPointLeft(c,d,a) xor isPointLeft(c,d,b)) ) {
                        return true;
                    }
                    else if (isPointBetween(a,b,c) or isPointBetween(a,b,d) or isPointBetween(c,d,a) or isPointBetween(c,d,b)) {
                        return true;
                    }
                    return false;
                }
                
                static bool isIntersectionProper(const CCPoint& a,
                                                 const CCPoint& b,
                                                 const CCPoint& c,
                                                 const CCPoint& d)
                {
                    if (isPointCollinear(a,b,c) or
                        isPointCollinear(a,b,d) or
                        isPointCollinear(c,d,a) or
                        isPointCollinear(c,d,b))
                    {
                        return false;
                    }
                    
                    return (isPointLeft(a,b,c) xor isPointLeft(a,b,d)) and (isPointLeft(c,d,a) xor isPointLeft(c,d,b));
                }
                
                static CCPointList orientCCW(const CCPointListref points) {
                    
                }
                
                static CCPointList orientCW(const CCPointListref points) {
                    
                }
                
                template<typename CONTAINER>
                static bool isOrientedCounterClockwise(CONTAINER<CCPoint>::const_iterator from, CONTAINER<CCPoint>::const_iterator to) {
                    CONTAINER<CCPoint>::const_iterator prevous = from;
                    from++;
                    CONTAINER<CCPoint>::const_iterator next = from;
                    next++;
                    while(from != to) {
                        if (not isLeftOrOn(*previous,*from,*next)) {
                            return false;
                        }
                    }
                    return true;
                }
                
            };
            
            
            
            
            
            
            
            
            
            macroDefinePrimitive (CCSegment) {
                
                static CCSegment create(const CCPoint & f, const CCPoint & t) {
                    return CCSegment(f,t);
                }
                
                bool operator < (const CCSegment& p) const {
                    return from < p.from or from == p.from and to < p.to;
                }
                
                CCPointList getPoints() const {
                    return { from, to };
                }
                
                bool isPointCollinear(const CCPoint& c) const {
                    return CCPoints::isPointCollinear(from,to,c);
                }
                
                bool isPointLeftOrOn(const CCPoint& c) const {
                    return CCPoints::isPointleftOrOn(from,to,c);
                }
                
                bool isPointLeft(const CCPoint& c) const {
                    return CCPoints::isPointLeft(from,to,c);
                }
                
                bool isPointOn(const CCPoint& c) const {
                    return CCPoints::isPointOn(from,to,c);
                }
                
                bool isPointBetween(const CCPoint& c) const {
                    return CCPoints::isPointBetween(from,to,c);
                }
                
                bool isPointRight(const CCPoint& c) const {
                    return CCPoints::isPointRight(from,to,c);
                }
                
                bool isPointRightOrOn(const CCPoint& c) const {
                    return CCPoints::isPointRightOrOn(from,to,c);
                }
                
                bool isPointBetween(const CCPoint& c) const {
                    return CCPoints::isPointBetween(from,to,c);
                }
                
                bool isIntersectionProper(const CCSegmentRef p) const {
                    return CCPoints::isIntersectionProper(from,to,p.from,p.to);
                }
                
                const CCPoint from;
                const CCPoint to;
                
            protected:
                
                CCSegment(const CCPoint & f, const CCPoint & t) : from(f), to(t) {
                    
                }
                
                
            };
            
            typedef CCSegment CCEdge;
            macroDefineContainersOf(CCEdge);
            
            
            
            
            
            
            
            macroDefinePrimitive(CCAABB) {
                
                static CCAABB create(const CCPointListRef points) {
                    CCPoint pointBottomLeft = points.front();
                    CCPoint pointBottomRight = points.front();
                    for(auto p:points) {
                        if (p.x < pointBottomLeft.y)
                            pointBottomLeft.x = p.x;
                        if (p.y < pointBottomLeft.y)
                            pointBottomLeft.y = p.y;
                        if (p.x > pointTopRight.x)
                            pointTopRight.x = p.x;
                        if (p.y > pointTopRight.y)
                            pointTopRight.y = p.y;
                    }
                    return CCAABB(pointBottomLeft,pointTopRight);
                }
                
                const CCPoint pointCenter;
                const CCPoint pointBottomLeft;
                const CCPoint pointTopRight;
                
            protected:
                
                CCAABB(CCPoint bl, CCPoint tr)  : pointBottomLeft(bl), pointTopRight(tr), pointCenter((bl.x+tr.x)/2.,(bl.y+tr.y)/2.)  {
                }
                
            };
            
            
            
            
            
            
            macroDefinePrimitive(CCPolygon) : protected CCPointList {
                // convex/concave
                // partition
                
                static bool isPointListConvex(const CCPointListRef points) {
                    
                }
                static bool isPointListConcave(const CCPointListRef points) {
                    return not isPointListConvex(points);
                }
                
                static std::pair<CCPolygon,bool> createFromPoints(const CCPointListRef points) {
                }
                
                virtual CCTriangleList partitionToTriangleList() const {
                    
                }
                
                virtual CCTrapezoidList partitionToTrapezoidList() const {
                    
                }
                
                int size() const {
                    return CCPointList::size();
                }
                
                virtual CCPointList getPoints() const {
                    return *this;
                }
                
                virtual CCAABB getAABB() const {
                    return CCAABB::create(*this);
                }
                
                virtual const CCPointRef getCentroid() const = 0;

                
            protected:
                
                CCPolygon(const CCPointList& points) : CCPointList(points) {
                }
                
            };
            
            
            
            
            
            macroDefinePrimitive(CCPolygonConvex) : public CCPolygon {

                static std::pair<CCPolygonConvex,bool> createFromPoints(const CCPointListRef points) {
                    
                }
                
                virtual CCPointList getPoints() const {
                    return *this;
                }
                
                virtual CCTriangleList partitionToTriangleList() const {
                    
                }

            };
            
            
            
            
            macroDefinePrimitive(CCBuilderOfPolygonConvex) {
                
                static CCBuilderOfPolygonConvex create(bool proper) {
                    return CCBuilderOfPolygonConvex(proper);
                }
                
                CCPolygonConvex getPolygon() const {
                    return CCPolygonConvex::createFromPoints(points).first;
                }
                
                bool addPoint(const CCPoint& p) {
                    bool r = false;
                    switch(points.size())
                    {
                        case 0:
                        case 1:
                            r = true;
                            break;
                            
                        default:
                            if (proper)
                            {
                                if (CCPoints::isLeft(beforeLast,points.back(),p)) {
                                    r = true;
                                }
                            }
                            else
                            {
                                if (CCPoints::isLeft(beforeLast,points.back(),p)) {
                                    r = true;
                                }
                            }
                    }
                    
                    if (r)
                    {
                        if (0 < points.size())
                        {
                            beforeLast = points.back();
                        }
                        points.push_back(p);
                    }
                    
                    return r;
                }
                
            protected:
                
                CCPoint beforeLast;
                CCPointList points;
                
                const bool proper;
                
                CCBuilderOfPolygonConvex(bool p) : proper(p) {
                    
                }
            };
            
            
            
            
            
            macroDefinePrimitive(CCQuadrilateral) : public CCPolygon {
                static std::pair<CCQuadrilateral,bool> createFromPoints(const CCPointListRef points) {
                    
                }
            };
            
            
            
            
            
            macroDefinePrimitive(CCQuadrilateralConvex) : public CCQuadrilateral {
                struct ExceptionPointsAreTooFew {
                    
                };
                struct ExceptionSideIsNonPositive {
                    
                };
                
                static CCQuadrilateralConvex createQuadrilateralFromPoints(const CCPointListRef points) {
                    
                }
                static CCQuadrilateralConvex createTrapezoidFromSides(float sideA, float sideB, bool leftAligned) {
                    
                }
                static CCQuadrilateralConvex createTrapezoidFromPoints(const CCPointListRef points) {
                    
                }
                static CCQuadrilateralConvex createParallelogramFromPoints(const CCPointListRef points) {
                    
                }
                static CCQuadrilateralConvex createRectangleFromWidthAndHeight(float w, float h) {
                    if (0 < w and 0 < h)
                    {
                        float w2 = w/2.;
                        float h2 = h/2.;
                        return CCRectangle(CCPoint(-w2,-h2),
                                           CCPoint(w2,-h2),
                                           CCPoint(w2,h2),
                                           CCPoint(-w2,h2));
                    }
                    throw new ExceptionSideIsNonPositive();
                }
                static CCQuadrilateralConvex createRectangleFromOrigin(CCPoint origin, float w, float h) {
                    if (0 < w and 0 < h)
                    {
                        float w2 = w/2.;
                        float h2 = h/2.;
                        return CCRectangle(CCPoint(origin.x-w2,origin.y-h2),
                                           CCPoint(origin.x+w2,origin.y-h2),
                                           CCPoint(origin.x+w2,origin.y+h2),
                                           CCPoint(origin.x-w2,origin.y+h2));
                    }
                    throw new ExceptionSideIsNonPositive();
                }
                
                static CCQuadrilateralConvex createSquareFromSide(float side) {
                    if (0 < side)
                    {
                        float s = side/2.;
                        return CCSquare(CCPoint(-s,-s),
                                        CCPoint(s,-s),
                                        CCPoint(s,s),
                                        CCPoint(-s,s));
                    }
                    throw new ExceptionSideIsNonPositive();
                }
                
                static CCQuadrilateralConvex createSquareFromDiagonal(float diagonal) {
                    return createFromSide(sqrt(diagonal));
                }
                
                static CCQuadrilateralConvex createSquareFromOrigin(CCPoint origin, float side) {
                    if (0 < side)
                    {
                        float s = side/2.;
                        return CCSquare(CCPoint(origin.x-s,origin.y-s),
                                        CCPoint(origin.x+s,origin.y-s),
                                        CCPoint(origin.x+s,origin.y+s),
                                        CCPoint(origin.x-s,origin.y+s));
                    }
                    throw new ExceptionSideIsNonPositive();
                }
                
                static CCQuadrilateralConvex createSquareFromOrigin(CCPoint origin, CCPoint bottomLeft) {
                    return createFromOrigin(origin, sqrt(CCPoints::distance(origin,bottomLeft)));
                }
                
                static CCQuadrilateralConvex createSquareFromBottomLeft(CCPoint bottomLeft, float side) {
                    return createFromOrigin(bottomLeft + CCPoint(side,side),side);
                }
                
                virtual CCTriangleList partitionToTriangles() const {
                    auto p = begin();
                    CCPoint a = *p++;
                    CCPoint b = *p++;
                    CCPoint c = *p++;
                    CCPoint d = *p;
                    return {CCTriangle::create(a,b,c),CCTriangle::create(b,c,d)};
                }
                

            };
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            // constructions, transformations, partition, accessors (point,angle,side)
            
            macroDefinePrimitive(CCTriangle) : public CCPolygonConvex {
                
                struct ExceptionPointsAreCollinear {
                    
                };
                
                struct ExceptionPointsAreTooFew {
                    
                };
                
                static CCTriangle create(CCPoint a, CCPoint b, CCPoint c) {
                    if (CCPoints::isPointCollinear(a,b,c) or CCPoints::isLeftOrOn(a,b,c)) {
                        throw new ExceptionPointsAreCollinear();
                    }
                    else {
                        return CCTriangle(a,b,c);
                    }
                }
                
                static CCTriangle createFromPoints(const CCPointListRef points) {
                    if (points.size() < 3) {
                        throw new ExceptionPointsAreTooFew();
                    }
                    auto p = points.begin();
                    return create(*p++,*p++,*p);
                }

                
                CCTriangle transformRotate(CCPoint point, float angle) const {
                    
                }
                CCTriangle transformScale(CCPoint point, float scale) const {
                    
                }
                CCTriangle transformScale(float scaleX, float scaleY) const {
                    
                }
                CCTriangle transformTranslate(float x, float y) const {
                    
                }
                

                Description getDescription() const {
                    return CCDescription(*this);
                }
                
            protected:
                
                CCTriangle(const CCPoint & a, const CCPoint & b, const CCPoint & c) : CCPolygonConvex({a,b,c}) {
                }
                
            public:
                
                macroDefineStruct(Description) {
                    
                    const CCPointRef getPointA() const { return pointA; }
                    const CCPointRef getPointB() const { return pointB; }
                    const CCPointRef getPointC() const { return pointC; }
                    const CCPointRef getCentroid() const { return pointCentroid; }
                    
                    bool isScalene() const {
                        return angleABC < Math::Angle::Pi and angleBCA < Math::Angle::Pi and angleCAB < Math::Angle::Pi;
                    }
                    
                    bool isIsosceles() const {
                        return Math::equal(angleABC,angleBCA) or Math::equal(angleABC,angleCAB) or Math::equal(angleBCA,angleCAB);
                    }
                    
                    bool isEquilateral() const {
                        return Math::equal(angleABC,angleBCA) and Math::equal(angleABC,angleCAB);
                    }
                    
                    float getAngleCAB() const {
                        return angleCAB;
                    }
                    
                    float getAngleBCA() const {
                        return angleBCA;
                    }
                    
                    float getAngleABC() const {
                        return angleABC;
                    }
                    
                    float getDistanceAB() const {
                        return distanceAB;
                    }
                    
                    float getDistanceBC() const {
                        return distanceBC;
                    }
                    
                    float getDistanceCA() const {
                        return distanceCA;
                    }
                    

                    Description(const CCTriangle& triangle)
                    {
                        auto points = triangle.getPoints();
                        auto p = points.begin();
                        pointA = *p++;
                        pointB = *p++;
                        pointC = *p;
                        distanceAB = CCPoints::getPointDistance(a,b);
                        distanceBC = CCPoints::getPointDistance(b,c);
                        distanceCA = CCPoints::getPointDistance(c,a);
                        angleCAB = getAngle(distanceCA,distanceAB,distanceBC);
                        angleABC = getAngle(distanceAB,distanceBC,distanceCA);
                        angleBCA = getAngle(distanceBC,distanceCA,distanceAB);
                    }
                    
                protected:
                    
                    float distanceAB, distanceBC, distanceCA;
                    float angleCAB, angleABC, angleBCA;
                    CCPoint pointA;
                    CCPoint pointB;
                    CCPoint pointC;
                    
                    
                };

            };
            
            
            macroDefinePrimitive(CCOval) : public CCPolygonConvex {
                
                static CCOval createWithWidthAndHeight(float w, float h) {
                    
                }
                
                static CCOval createWithOrigin(CCPoint origin, float w, float h) {
                    
                }
                
                virtual CCPointList getPoints(int count) const {
                    
                }
            };
            
            
            
            
            macroDefinePrimitive(CCCircle) : public CCPolygonConvex {
                
                static CCCircle create(float radius) {
                    
                }
                
                static CCCircle createWithOrigin(CCPoint origin, float radius) {
                    
                }
                
                virtual CCPointList getPoints(int count) const {
                    
                }
                
                static CCPoint centerCalculate(CCPoint A, CCPoint B, CCPoint C) {
                    float yDelta_a = B.y - A.y;
                    float xDelta_a = B.x - A.x;
                    float yDelta_b = C.y - B.y;
                    float xDelta_b = C.x - B.x;
                    CCPoint center = Vec2(0,0);
                    float aSlope = yDelta_a/xDelta_a;
                    float bSlope = yDelta_b/xDelta_b;
                    center.x = (aSlope*bSlope*(A.y - C.y) + bSlope*(A.x + B.x) - aSlope*(B.x+C.x) )/(2* (bSlope-aSlope) );
                    if (aSlope)
                        center.y = -1 * (center.x - (A.x + B.x) / 2) / aSlope + (A.y + B.y)/2;
                    else
                        center.y = -1 * (center.x - (B.x + C.x) / 2) / bSlope + (B.y + C.y) / 2;
                    return center;
                }

            };
            
            
            
            
            macroDefinePrimitive(CCArc) : protected CCPointList {
                
                static CCArc create(float radius, float angle) {
                    
                }
                
                static CCArc createWithOrigin(CCPoint origin, float radius, float angle0, float angle1) {
                    
                }
                
                virtual CCPointList getPoints(int count) const {
                    
                }
            };
            
            
            
            
            macroDefinePrimitive(CCFan) {
                
            };
            
            
            
            
            macroDefinePrimitive(CCStrip) {
                
            };
            
            
            
            
        }
    }
}