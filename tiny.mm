//
//  tiny.h
//  libraryTiny
//  Created by andrzej semeniuk on 8/12/12.
//
//

#pragma once

#include <stdio.h>
#include <iostream>

//using namespace std;

//#define is ==
//#define isnot !=
//#define from =
//#define to =
//#define as =
// a as 1+2

    // ______ = 'inline' filler
#define ______
#define _______

#define PIXELS
#define PIXEL
#define RADIANS
#define DEGREES
#define METERS
#define SECONDS
#define KILOGRAMS
#define RATIO

#define abstract = 0

#define autoRef auto &
#define autoCRef const auto &


#define DECLARE(NAME)               typedef NAME * NAME##Ptr; typedef const NAME * NAME##CPtr; typedef NAME & NAME##Ref; typedef const NAME & NAME##CRef

#define TYPEDEF(NAME,...)           typedef __VA_ARGS__ NAME; DECLARE(NAME)

#define STRUCT_DECLARATION(NAME)    struct NAME; DECLARE(NAME)
#define STRUCT(NAME)                STRUCT_DECLARATION(NAME); struct NAME
#define macroDefineStruct(NAME)     STRUCT( NAME )
#define GROUP STRUCT

#define DECLARE_CONTAINERS(NAME) \
    typedef std::list< NAME >       ListOf##NAME ; \
    typedef std::set< NAME >        SetOf##NAME ; \
    typedef std::vector< NAME >     VectorOf##NAME ; \
    typedef std::queue< NAME >      QueueOf##NAME ; \
    typedef std::deque< NAME >      DequeOf##NAME

#define STRUCT_WITH_CONTAINERS(NAME) struct NAME; typedef NAME * NAME##Ptr; typedef NAME & NAME##Ref; DECLARE_CONTAINERS( NAME ); DECLARE_CONTAINERS( NAME##Ptr ); struct NAME

#define DATA(NAME) struct NAME 

#define typedefVectorSet(NAME) \
typedef std::set<NAME>              NAME##Set ; \
typedef std::set<NAME> &            NAME##SetRef ; \
typedef const std::set<NAME> &      NAME##SetCRef ; \
typedef std::vector<NAME>           NAME##Chain ; \
typedef std::vector<NAME> &         NAME##ChainRef ; \
typedef const std::vector<NAME> &   NAME##ChainCRef

#define typedefWithVectorSet(TYPE,NAME) \
typedef TYPE                        NAME ; \
typedefVectorSet(NAME)


#define TEMPLATE(NAME,TYPE) template <typename TYPE > struct NAME

#define RETURN_FALSE_IF_FALSE(EXPRESSION) if ( not (EXPRESSION) ) {return false;}





#define safeDeleteNull(o) if (o) { delete o; o = 0; }

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char ubyte;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned long long ullong;
typedef long long llong;

typedef float degrees;
typedef float radians;
typedef float Seconds;

STRUCT (floats2) {
    float value1;
    float value2;
    floats2(float _1 = 0.f, float _2 = 0.f) : value1(_1), value2(_2) {
        
    }
};
STRUCT (floats3) {
    float value1;
    float value2;
    float value3;
    floats3(float _1 = 0.f, float _2 = 0.f, float _3 = 0.f) : value1(_1), value2(_2), value3(_3) {
        
    }
};
STRUCT (floats4) {
    float value1;
    float value2;
    float value3;
    float value4;
    floats4(float _1 = 0.f, float _2 = 0.f, float _3 = 0.f, float _4 = 0.f) : value1(_1), value2(_2), value3(_3), value4(_4) {
        
    }
};


STRUCT (XYZ) {
	float x = 0;
	float y = 0;
	float z = 0;
	XYZ() {}
	XYZ(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
};


STRUCT (Dimension) {
	uint across = 0;
	uint down = 0;
    Dimension() {}
    Dimension(uint a, uint d) : across(a), down(d) {}
};

STRUCT (Cell) {
	int row = 0;
	int column = 0;
    Cell() {}
    Cell(int r, int c) : row(r), column(c) {}
};


template<typename T> struct Span {
    T from;
    T to;
    Span() {}
    Span(const T& a, const T& b) : from(a),to(b) {}
};

typedef Span<float> fSpan;
typedef Span<float> Spanf;
typedef Span<int> iSpan;
typedef Span<int> Spani;
typedef Span<Seconds> SecondsSpan;

template<typename T> struct values2 {
    T value1;
    T value2;
    values2() {}
    values2(const T& a, const T& b) : value1(a),value2(b) {}
};

template<typename T> struct values3 {
    T value1;
    T value2;
    T value3;
    values3() {}
    values3(const T& a, const T& b, const T& c) : value1(a),value2(b),value3(c) {}
};

template<typename T> struct values4 {
    T value1;
    T value2;
    T value3;
    T value4;
    values4() {}
    values4(const T& a, const T& b, const T& c, const T& d) : value1(a),value2(b),value3(c),value4(d) {}
};


inline int pick01(bool p) { return p ? 1 : 0; }
inline int pick10(bool p) { return p ? 0 : 1; }

template<typename T> T oppositeSign(T p) { return p < 0 ? 1 : -1; }
template<typename T> T signOpposite(T p) { return p < 0 ? 1 : -1; }

template<typename T> bool same(const T & a, const T &  b)                           { return a == b; }
template<typename T> bool same(const T & a, const T &  b, const T & delta)          { return (a-delta)<b and b<(a+delta); }
template<typename T> bool different(const T &  a, const T & b)                      { return not (a == b); }
template<typename T> bool different(const T &  a, const T & b, const T & delta)     { return not same(a,b,delta); }

typedef std::function<void ()>          Function;
typedef std::function<bool ()>          Question;
typedef std::function<void (int)>       Informant;
typedef std::function<void (int)>       Listener;

#define BLOCK while(0)

#define loopOverVector(IDENTIFIER,VECTOR)                   for(int IDENTIFIER = 0, LIMIT = (int)(VECTOR).size(); IDENTIFIER < LIMIT; IDENTIFIER ++ )
#define loopUpTo(IDENTIFIER,COUNT)                          for(int IDENTIFIER = 0, LIMIT = (int)(COUNT); IDENTIFIER < LIMIT; IDENTIFIER ++ )
#define loopUpFromToInclusive(IDENTIFIER,FROM,TO)           for(int IDENTIFIER = (FROM); IDENTIFIER <= (TO); IDENTIFIER ++ )
#define loopUpFromTo(IDENTIFIER,FROM,TO)                    for(int IDENTIFIER = (FROM); IDENTIFIER < (TO); IDENTIFIER ++ )
#define loopDownFromTo(IDENTIFIER,FROM,TO)                  for(int IDENTIFIER = (TO); IDENTIFIER > (TO); IDENTIFIER -- )
#define loopDownFromCount(COUNT)                            loopDownFromTo(____i____,(COUNT),0)
#define loopDownFromDownToInclusive(IDENTIFIER,FROM,TO)     for(int IDENTIFIER = (FROM); IDENTIFIER >= (TO); IDENTIFIER -- )
#define loopCount(COUNT)                                    loopUpTo(____i____,(COUNT))
#define loopForever                                         for(;;)

#define iterateOverContainer(ITERATOR,CONTAINER)                          for(auto ITERATOR = (CONTAINER).begin(); ITERATOR != (CONTAINER).end(); ITERATOR ++)
#define iterateOverContainerForward(ITERATOR,CONTAINER)                   for(auto ITERATOR = (CONTAINER).begin(); ITERATOR != (CONTAINER).end(); ITERATOR ++)
#define iterateOverContainerBackward(ITERATOR,CONTAINER)                  for(auto ITERATOR = (CONTAINER).rbegin(); ITERATOR != (CONTAINER).rend(); ITERATOR ++)
#define iterateOverContainerDontIncrement(ITERATOR,CONTAINER)             for(auto ITERATOR = (CONTAINER).begin(); ITERATOR != (CONTAINER).end(); )

inline bool tFlip(bool & p) { return p = not p; }

#ifdef DEBUG

#define tDebugOn                    true
#define tDebug(...)                 do { __VA_ARGS__ ; } while(0)
#define tRelease(...)
#define tLog(...)                   do { std::cerr << __VA_ARGS__ << std::endl; } while(0)
#define tAssert(CONDITION)          do { if (!(CONDITION)) { fprintf (stderr, "error: in %s, line %d.", __FILE__ , __LINE__ ); assert(0); } } while(0)
#define tAssertive(CONDITION,...)   do { if (!(CONDITION)) { tLog(__VA_ARGS__); fprintf (stderr, "error: in %s, line %d.", __FILE__ , __LINE__ ); assert(0); } } while(0)
#define tAssertFail                 tAssert(0)

#else

#define tDebugOn                    false
#define tDebug(...)
#define tRelease(...)               do { __VA_ARGS__ ; } while(0)
    //#define tLog(...)                   do { std::cout << __VA_ARGS__ << std::endl; } while(0)
#define tLog(...)
    //#define tAssert(CONDITION) assert(CONDITION)
    //#define tAssertive(CONDITION,...) assert(CONDITION)
#define tAssert(CONDITION)          do { if (!(CONDITION)) { fprintf (stderr, "error: in %s, line %d.", __FILE__ , __LINE__ ); exit(1); } } while(0)
#define tAssertive(CONDITION,...)   do { if (!(CONDITION)) { tLog(__VA_ARGS__); fprintf (stderr, "error: in %s, line %d.", __FILE__ , __LINE__ ); exit(1); } } while(0)
#define tAssertFail                 tAssert(0)

#endif



#define assignIfLess(A,B)       do { if ((A) < (B)) { A = (B); } } while(0)
#define assignIfGreater(A,B)    do { if ((A) > (B)) { A = (B); } } while(0)
#define doIf(A,...)             do { if ( (A) ) { __VA_ARGS__ ; } while(0)
#define doIfNot(A,...)          do { if ( not (A) ) { __VA_ARGS__ ; } while(0)


struct Cardinality {
    enum {
        None = 0, // exactly 0
        One, // exactly 1
        Any, // zero or more
        Many, // one or more
        All // exactly all
    };
};


//#define ref(...)               __VA_ARGS__ &
#define CRef(...)              const __VA_ARGS__ &

#define vectorRef(...)         std::vector< __VA_ARGS__ > &
#define vectorCRef(...)        const std::vector< __VA_ARGS__ > &
#define listRef(...)           std::list< __VA_ARGS__ > &
#define listCRef(...)          const std::list< __VA_ARGS__ > &
#define setRef(...)            std::set< __VA_ARGS__ > &
#define setCRef(...)           const std::set< __VA_ARGS__ > &
#define mapRef(KEY,VALUE)      std::map< KEY,VALUE > &
#define mapCRef(KEY,VALUE)     const std::map< KEY,VALUE > &

inline bool is_odd (long a)          { return a%2L==1L; }
inline bool is_even(long a)          { return a%2L==0L; }
inline bool is_nth (long a, long n)  { return a%n==0L; }

template<class A, class B>
bool less2   (CRef(A) a0, CRef(A) a1,
              CRef(B) b0, CRef(B) b1)
{
    return a0 < a1 or (a0 == a1 and b0 < b1);
}


template<class A, class B, class C>
bool less3   (CRef(A) a0, CRef(A) a1,
              CRef(B) b0, CRef(B) b1,
              CRef(C) c0, CRef(C) c1)
{
    return a0 < a1 or (a0 == a1 and (b0 < b1 or (b0 == b1 and c0 < c1)));
}

template<class A, class B, class C, class D>
bool less4   (CRef(A) a0, CRef(A) a1,
              CRef(B) b0, CRef(B) b1,
              CRef(C) c0, CRef(C) c1,
              CRef(D) d0, CRef(D) d1)
{
    return a0 < a1 or (a0 == a1 and (b0 < b1 or (b0 == b1 and (c0 < c1 or (c0 == c1 and d0 < d1)))));
}

