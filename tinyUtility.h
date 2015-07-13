	//
	//  CommonUtility.h
	//  productChristmasTreeForKids
	//
	//  Created by andrzej semeniuk on 12/6/12.
	//
	//

#pragma once

#include "tiny.h"

#include <tuple>
#include <list>
#include <ostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <regex>
#include <algorithm>
#include <forward_list>

#include <boost/lexical_cast.hpp>
//#include <boost/bimap.hpp>
#include <boost/any.hpp>





#define tupleGet0(TUPLE) std::get<0>( TUPLE )
#define tupleGet1(TUPLE) std::get<1>( TUPLE )
#define tupleGet2(TUPLE) std::get<2>( TUPLE )
#define tupleGet3(TUPLE) std::get<3>( TUPLE )
#define tupleGet4(TUPLE) std::get<4>( TUPLE )

#define tupleGet1st(TUPLE) std::get<0>( TUPLE )
#define tupleGet2nd(TUPLE) std::get<1>( TUPLE )
#define tupleGet3rd(TUPLE) std::get<2>( TUPLE )
#define tupleGet4th(TUPLE) std::get<3>( TUPLE )
#define tupleGet5th(TUPLE) std::get<4>( TUPLE )


namespace tiny
{
    
    
    
    
    using namespace std;
    
    
    
    
    
    typedef std::map<std::string,boost::any>                    Parameters;
    
    typedef std::pair<std::string,boost::any>                   Parameter;
    typedef std::pair<std::string,boost::any> &                 ParameterRef;
    typedef const std::pair<std::string,boost::any> &           ParameterCRef;

    
    
    
    typedef std::set<int>                                       int_set;
    typedef std::vector<int>                                    int_vector;
    typedef std::list<int>                                      int_list;
    
    
    typedef std::set<std::string>                               string_set;
    typedef std::vector<std::string>                            string_vector;
    typedef std::list<std::string>                              string_list;
    
    
    
    
    template<typename T> struct foil {
        
        inline operator bool () const {
            return 0 != data.value;
        }
        
        inline operator T& () {
            return *data.value;
        }
        
        inline operator const T& () const {
            return *data.value;
        }
        
        inline T& operator() () {
            return *data.value;
        }
        
        inline const T& operator() () const {
            return *data.value;
        }
        
        inline foil<T>& operator = (T* v) {
            if (not data.hold) {
                data.value = v;
            }
            return *this;
        }
        
        inline bool set(T* v) {
            if (not data.hold) {
                data.value = v;
                return true;
            }
            return false;
        }
        
        foil() {
        }
        
        foil(T * v) {
            data.value = v;
        }
        
        inline void clear() {
            data.value = 0;
        }
        
        inline void hold() const {
            data.hold = true;
        }
        
        inline bool isHeld() const {
            return data.hold;
        }
        
    protected:
        
        struct {
            T * value = 0;
            bool hold = false;
        } data;
        
    };
    
    
    
    
    
    
    
    
    template<typename T> struct constant {
        
        inline operator bool () const {
            return 0 != data.value;
        }
        
        inline operator T& () {
            return *data.value;
        }
        
        inline operator const T& () const {
            return *data.value;
        }
        
        inline operator T* ()  {
            return data.value;
        }
        
        inline operator const T* () const {
            return data.value;
        }
        
        inline T& operator () () {
            return *data.value;
        }
        
        inline const T& operator () () const {
            return *data.value;
        }
        
        inline constant<T>& operator = (const constant<T>& v) {
            set(v);
            return *this;
        }
        
        inline constant<T>& operator = (T* v) {
            set(v);
            return *this;
        }
        
        inline bool set(T* v) {
            if (not data.value) {
                data.value = v;
                return true;
            }
            return false;
        }
        
        constant() {
        }
        
        constant(T * v) {
            data.value = v;
        }
        
    protected:
        
        struct {
            T * value = 0;
        } data;
        
    };
    
    
    
    
    
    
    
    
    template<typename T> struct hold {
        
        inline operator bool () const {
            return data.initialized;
        }
        
        inline operator T& () {
            return data.value;
        }
        
        inline operator const T& () const {
            return data.value;
        }
        
        inline T& operator () () {
            return data.value;
        }
        
        inline const T& operator () () const {
            return data.value;
        }
        
        inline hold<T>& operator = (const hold<T>& v) {
            set(v);
            return *this;
        }
        
        inline hold<T>& operator = (const T& v) {
            set(v);
            return *this;
        }
        
        inline bool set(const T& v) {
            if (not data.initialized) {
                data.initialized = true;
                data.value = v;
                return true;
            }
            return false;
        }
        
        hold() {
            
        }
        
        hold(const T& v) {
            data.initialized = true;
            data.value = v;
        }
        
    protected:
        
        struct {
            bool initialized = false;
            T value;
        } data;
        
    };
    
    
    
    
    
    
    
    template<typename T> struct hold_ptr {
        
        inline operator bool () const {
            return data.initialized;
        }
        
        inline operator T& () {
            return data.value;
        }
        
        inline operator const T& () const {
            return data.value;
        }
        
        inline T& operator () () {
            return *data.value;
        }
        
        inline const T& operator () () const {
            return *data.value;
        }
        
        inline T& operator -> () {
            return *data.value;
        }
        
        inline const T& operator -> () const {
            return *data.value;
        }
        
        inline hold_ptr<T>& operator = (const hold_ptr<T>& v) {
            set(v);
            return *this;
        }
        
        inline hold_ptr<T>& operator = (const T& v) {
            set(v);
            return *this;
        }
        
        inline bool set(const T& v) {
            if (not data.initialized) {
                data.initialized = true;
                data.value = v;
                return true;
            }
            return false;
        }
        
        hold_ptr() {
            
        }
        
        hold_ptr(const T& v) {
            data.initialized = true;
            data.value = v;
        }
        
    protected:
        
        struct {
            bool initialized = false;
            T value = 0;
        } data;
        
    };
    
    
    
    
    
    template <typename T> struct holder {
        holder() : _valid(false) {}
        holder(T v) : _value(v), _valid(true) {}
        holder(T v, bool val) : _value(v), _valid(val) {}
        holder<T>& operator = (const holder<T>& v) { if (v.valid()) {_value = v.value(); _valid = true;} return *this; }
        holder<T>& operator = (const T& v) { _value = v; _valid = true; return *this; }
        holder<T>& operator += (const T& v) { _value += v; _valid = true; return *this; }
        holder<T>& operator -= (const T& v) { _value -= v; _valid = true; return *this; }
        holder<T>& operator *= (const T& v) { _value *= v; _valid = true; return *this; }
        holder<T>& operator /= (const T& v) { _value /= v; _valid = true; return *this; }
            //inline void set(const T& v) { _value = v; _valid = true; }
        inline operator T () const { return _value; }
        inline const T & operator () () const { return _value; }
        inline const T & value() const { return _value; }
        inline const T & value(const T & b) const { return _valid ? _value : b; }
        inline bool valid () const { return _valid; }
        inline bool is (const T & v) const { return _valid and _value == v; }
        inline void clear() { _valid = false; }
        friend ostream& operator << (ostream& o, const holder<T>& p) { return o << '(' << (p.valid() ? boost::lexical_cast<std::string>(p.value()) : "-") << ')'; }
    protected:
        T _value;
        bool _valid = false;
    };

    typedef holder<int> holder_i;
    typedef holder<float> holder_f;
    typedef holder<double> holder_d;
    
    
    
    
    template<typename A, typename B>
    std::ostream& operator << (std::ostream& o, const std::pair<A,B>& p)
    {
        return o << '<' << p.first << ',' << p.second << '>';
	}
	
	
	template<typename T>
	std::ostream& operator << (std::ostream& o, const std::list<T>& container)
	{
		o << '(' << container.size() << '/';
		
		bool first = true;
		
		for(const T & i : container)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				o << ',';
			}
			o << i;
		}
		
		return o << ')';
	}
	
	
	template<typename T>
	std::ostream& operator << (std::ostream& o, const std::set<T>& container)
	{
		o << '{' << container.size() << '/';
		
		bool first = true;
		
		for(const auto & i : container)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				o << ',';
			}
			o << i;
		}
		
		return o << '}';
	}
	
	template<typename T>
	std::ostream& operator << (std::ostream& o, const std::vector<T>& container)
	{
		o << '[' << container.size() << '/';
		
		bool first = true;
		
		for(const auto & i : container)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				o << ',';
			}
			o << i;
		}
		
		return o << ']';
	}
	
	
	
	inline std::ostream& printPointers (std::ostream& o)
	{
		return o;
	}
	
	template<class ForwardIterator>
	std::ostream& printPointers (std::ostream& o, ForwardIterator a, ForwardIterator e)
	{
		bool first = true;
		
		while (a != e)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				o << ',';
			}
			o << **a;
			
			a++;
		}
		
		return o;
	}
	
	
	template<typename K, typename V>
	std::ostream& operator << (std::ostream& o, const std::map<K,V>& container)
	{
		o << '{' << container.size() << '/';
		
		bool first = true;
		
		for(const auto & i : container)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				o << ',';
			}
			o << '(' << i . first << ',' << i . second << ')';
		}
		
		return o << '}';
	}
	
        //        std::string sprintf(int length, std::string format, ...)
        //        {
        //            va_list ap;
        //            std::string r(length);
        //            char b[length];
        //            sprintf(b,format,ap);
        //            r = b;
        //            return r;
        //        }
	
	
	inline bool             contains        (const std::string& string, char c)                 { return std::string::npos != string.find(c); }
	
    inline bool             contains        (const std::string& target, const std::string& p)   { return target.compare(0, p.length(), p) != std::string::npos; }
    
    inline bool             startsWith      (const std::string& target, const std::string& p)   { return 0 == target.compare(0, p.length(), p); }
	
    
    
    
	inline std::string &    to_lowercase    (std::string& s)                                    { std::transform(s.begin(), s.end(), s.begin(), ::tolower); return s; }
	
    inline std::string &    to_uppercase    (std::string& s)                                    { std::transform(s.begin(), s.end(), s.begin(), ::toupper); return s; }
    
    
    
    
	inline std::string & trimLeft(std::string &s, const std::string & delimiters) {
		auto startpos = s.find_first_not_of(delimiters);
		if( string::npos != startpos )
		{
			s = s.substr( startpos );
		}
		return s;
	}
	
	inline std::string & trimRight(std::string &s, const std::string & delimiters) {
		auto endpos = s.find_last_not_of(delimiters);
		if( string::npos != endpos )
		{
			s = s.substr( 0, endpos + 1 );
		}
		return s;
	}
	
	inline std::string & trim(std::string & s, const std::string & delimiters) {
		return trimLeft(trimRight(s,delimiters),delimiters);
	}
	
	inline std::string & trimLeft(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}
	
	inline std::string & trimRight(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}
	
	inline std::string & trim(std::string &s) {
		return trimLeft(trimRight(s));
	}
	
	
	
	
	inline std::string & removeSpaces(std::string & s) {
		s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
		return s;
	}
	
    inline std::string & replaceSpaces(std::string & s, char c) {
        std::replace(s.begin(),s.end(),' ',c);
        std::replace(s.begin(),s.end(),'\t',c);
        std::replace(s.begin(),s.end(),'\n',c);
        std::replace(s.begin(),s.end(),'\r',c);
        return s;
    }
    
    inline std::string & replaceCharacter(std::string & s, char original, char substitute) {
        std::replace(s.begin(),s.end(),original,substitute);
        return s;
    }
    
	
	
	
	
	
	inline std::list<std::string> collectTextWithRegex(std::string text, std::string regex) {
		std::regex r(regex);
		std::smatch m;
		std::list<std::string> R;
            //            std::cout << "breakTextWithRegex: text:(" << text << ") regex:(" << regex << ')' << std::endl;
		while(std::regex_search(text,m,r)) {
			std::ssub_match s = m[0];
			std::string S = s.str();
			R . push_back(S);
			text = m.suffix().str();
                //                std::cout << "breakTextWithRegex: found:(" << S << ") text:(" << text << ')' << std::endl;
		}
		return R;
	}
	
	
	inline std::list<std::string> breakTextOnWhitespace     (const std::string& text)               { return collectTextWithRegex(text, "[^\\s]+"); }
	inline std::list<std::string> breakTextOnNonLetters     (const std::string& text)               { return collectTextWithRegex(text, "[a-zA-Z]+"); }
	inline std::list<std::string> collectTextAlphanumeric   (const std::string& text)               { return collectTextWithRegex(text, "\\w+"); }
	inline std::list<std::string> split                     (const std::string& text, const std::string& delimiters) { return collectTextWithRegex(text, "[^"+delimiters+"]+"); }
	inline std::list<std::string> split                     (const std::string& text)               { return breakTextOnWhitespace(text); }
    
	inline std::string            substring                 (const std::string& text, const std::string& match1, const std::string& match2) { auto p0 = text.find(match1); auto p1 = text.find(match2,p0+match1.length()); return text.substr(p0,p1-p0); }
	
	template<class T> std::string to_string                 (const T& p)                            { return boost::lexical_cast<std::string>(p); }
	template<class T> int         to_int                    (const T& p)                            { return boost::lexical_cast<int>(p); }
	template<class T> float       to_float                  (const T& p)                            { return boost::lexical_cast<float>(p); }
	inline std::string            to_string                 (std::string prefix, int number)        { return prefix + to_string(number); }
	inline std::string            to_string                 (int number, std::string suffix)        { return to_string(number) + suffix; }
	inline std::string            to_string                 (int a, std::string b, int c)           { return to_string(a) + b + to_string(c); }
    inline std::string            to_string                 (int a, std::string b, int c, std::string d, int e)           { return to_string(a) + b + to_string(c) + d + to_string(e); }
    
	inline std::string            to_string                 (std::string s1, int n1, std::string s2)                                                    { return s1 + to_string(n1) + s2; }
	inline std::string            to_string                 (std::string s1, int n1, std::string s2, int n2)                                            { return s1 + to_string(n1) + s2 + to_string(n2); }
	inline std::string            to_string                 (std::string s1, int n1, std::string s2, int n2, std::string s3)                            { return s1 + to_string(n1) + s2 + to_string(n2) + s3; }
	inline std::string            to_string                 (std::string s1, int n1, std::string s2, int n2, std::string s3, int n3)                    { return s1 + to_string(n1) + s2 + to_string(n2) + s3 + to_string(n3); }
	inline std::string            to_string                 (std::string s1, int n1, std::string s2, int n2, std::string s3, int n3, std::string s4)    { return s1 + to_string(n1) + s2 + to_string(n2) + s3 + to_string(n3) + s4; }
	
    extern std::string to_string_with_comma (int n, char c = ',');
    
//#define sss(VARIABLE, ...) { std::stringstream ss; ss << __VA_ARGS__ ; VARIABLE = ss.str(); }
	
	
	
	template<typename K>                bool contains           (const std::set<K>& m, const K & k)               { return m.find(k) != m.end(); }
	template<typename K>                bool contains           (const std::list<K>& m, const K & k)              { return find(m.begin(),m.end(),k) != m.end(); }
	template<typename K>                bool contains           (const std::vector<K>& m, const K & k)            { return find(m.begin(),m.end(),k) != m.end(); }
	template<typename K>                bool vectorContains     (const std::vector<K>& m, const K & k)            { return find(m.begin(),m.end(),k) != m.end(); }
	template<typename K, typename V>    bool contains           (const std::map<K,V>& m, const K & k)             { return m.find(k) != m.end(); }
	template<typename K, typename V>    bool contains           (const std::map<K,V>& m, const K & k, const V& v) { auto i = m.find(k); return i != m.end() and i->second==v; }
	
	
	
	
	template<typename K, typename V> bool get(const std::map<K,V>& m, const K & k, V& d) {
		auto i = m.find(k);
		if (i != m.end()) {
            d = i -> second;
			return true;
        }
		return false;
	}
	
	template<typename K, typename V> const V & find(const std::map<K,V>& m, const K & k, const V & d) {
		auto i = m.find(k);
		if (i != m.end())
			return i -> second;
		return d;
	}
	
	template<typename K, typename V> V& find_and_get(const std::map<K,V>& m, const K & k, V & d) {
		auto i = m.find(k);
		if (i != m.end())
			d = i -> second;
		return d;
	}
	
	template<typename K, typename V> bool find_and_assign(std::map<K,V>& m, const K & k, const V & d) {
		auto i = m.find(k);
		if (i != m.end()) {
			i -> second = d;
            return true;
        }
		return false;
	}
	
	template<typename K, typename V> bool find_and_do(const std::map<K,V>& m, const K & k, std::function<void (V &)> f) {
		auto i = m.find(k);
		if (i != m.end()) {
			f(i -> second);
            return true;
        }
		return false;
	}
	
	template<typename K, typename V> bool find_and_do(const std::map<K,V>& m, const K & k, std::function<void (const V &)> f) {
		auto i = m.find(k);
		if (i != m.end()) {
			f(i -> second);
            return true;
        }
		return false;
	}
	
	template<typename K, typename V> bool find_and_do(const std::map<K,V>& m, const K & k) {
		auto i = m.find(k);
		if (i != m.end()) {
			(i -> second)();
            return true;
        }
		return false;
	}
	
	template<typename K, typename V, typename P> bool find_and_do_with(const std::map<K,V>& m, const K & k, P & p) {
		auto i = m.find(k);
		if (i != m.end()) {
			(i -> second)(p);
            return true;
        }
		return false;
	}
	
	template<typename K, typename V, typename P> bool find_and_do_with(const std::map<K,V>& m, const K & k, const P & p) {
		auto i = m.find(k);
		if (i != m.end()) {
			(i -> second)(p);
            return true;
        }
		return false;
	}
	
	template<typename K, typename V> V& increment (std::map<K,V>& m, const K & k, const V & reset, const V & increment) {
		auto i = m.find(k);
        if (i == m.end())
        {
            return m[k] = reset + increment;
        }
        else
        {
            return (*i).second += increment;
        }
	}
    
	template<typename K, typename V> V& increment (std::map<K,V>& m, const K & k, V v = 1) {
        return increment (m,k,0,v);
    }
	
	
	
	
    
	
	
	
	
	
	template<typename K, typename V> V& get(std::vector<pair<K,V>>& m, const K & k) {
		for(auto & e:m) {
			if (e.first == k)
				return e.second;
		}
		tAssert(0);
		return m[0].second;
	}
	
	template<typename K, typename V> bool assign(std::vector<pair<K,V>>& m, const K & k, const V & v) {
		for(auto & e:m) {
			if (e.first == k) {
				e.second = v;
				return true;
			}
		}
		return false;
	}
	
	template<typename K, typename V> bool contains(const std::vector<pair<K,V>>& m, const K & k) {
		for(auto & e:m) {
			if (e.first == k) {
				return true;
			}
		}
		return false;
	}
	
	
	
	
	
	
	template<typename K, typename V> std::vector<K> keys(const std::map<K,V>& m) {
		vector<K> r;
		r.reserve(m.size());
		for(const auto & e:m) {
			r.push_back(e.first);
		}
		return r;
	}
	
	template<typename K, typename V> std::vector<V> values(const std::map<K,V>& m) {
		vector<V> r;
		r.reserve(m.size());
		for(const auto & e:m) {
			r.push_back(e.second);
		}
		return r;
	}
	
	
	
	
	
	template<typename K, typename V> K&         key         (std::pair<K,V>& p)                     { return p.first; }
	template<typename K, typename V> K&         key         (std::pair<K,V> * p)                    { return p->first; }
	template<typename K, typename V> const K &  key         (const std::pair<K,V>& p)               { return p.first; }
	template<typename K, typename V> const K &  key         (const std::pair<K,V> * p)              { return p->first; }
	
	template<typename K, typename V> V&         value       (std::pair<K,V>& p)                     { return p.second; }
	template<typename K, typename V> V&         value       (std::pair<K,V> * p)                    { return p->second; }
	template<typename K, typename V> const V &  value       (const std::pair<K,V>& p)               { return p.second; }
	template<typename K, typename V> const V &  value       (const std::pair<K,V> * p)              { return p->second; }
	
	
	
    template<typename C> struct manipulator
    {
        C & container;
        manipulator(C & c) : container(c) {}
        
        manipulator<C>& remove(const typename C::value_type& p) { erase(container,p); return *this; }
        manipulator<C>& remove(forward_list<typename C::value_type>& p) { for(auto & e:p) erase(container,e); return *this; }
        manipulator<C>& append(const typename C::value_type& p) { append(container,p); return *this; }
        manipulator<C>& append(forward_list<typename C::value_type>& p) { for(auto & e:p) append(container,e); return *this; }
            //        manipulator<C,T>& insert(forward_list<T>& p) { for(auto & e:p) container.insert(e); return *this; }
        C & operator () () { return container; }
        
        static manipulator<C> create(C & c) { return manipulator(c); }
    };

	
	
	template<typename T> bool erase(std::set<T>& s, const T& e) {
		return 0 < s.erase(e);
	}
	
	template<typename T> bool erase(std::list<T>& s, const T& e) {
		int size = (int) s.size();
        s.remove(e);
		return s.size() < size;
	}
	
	template<typename T> bool erase(std::vector<T>& s, const T& e) {
		int size = (int) s.size();
		s.erase(remove(s.begin(),s.end(),e),s.end());
		return s.size() < size;
	}
	
	template<typename K, typename V> bool erase(std::map<K,V>& s, const K & e) {
		int size = (int) s.size();
		s.erase(e);
		return s.size() < size;
	}
	
	template<typename T, class UnaryPredicate> bool remove_if(std::list<T>& s, UnaryPredicate e) {
        int size = (int) s.size();
        s.remove_if(e);
        return s.size() < size;
	}
	
    template<typename T, class UnaryPredicate> bool erase_if(std::list<T>& s, UnaryPredicate e) {
        return remove_if(s,e);
    }
    
	template<typename T, class UnaryPredicate> bool erase_if(std::vector<T>& s, UnaryPredicate e) {
		int size = (int) s.size();
		s.erase(remove_if(s.begin(),s.end(),e),s.end());
		return s.size() < size;
	}
	
	template<typename T, class UnaryPredicate> bool remove_if(std::vector<T>& s, UnaryPredicate e) {
        return erase_if(s,e);
	}
    
	template<typename T, class UnaryPredicate> bool erase_if(std::set<T>& s, UnaryPredicate e) {
		int size = (int) s.size();
        for(auto i=s.begin(); i != s.end(); )
        {
            if (e(*i))
                s.erase(i++);
            else
                i++;
        }
		return s.size() < size;
	}
    
	template<typename T, class UnaryPredicate> bool remove_if(std::set<T>& s, UnaryPredicate e) {
        return erase_if(s,e);
    }
	
	template<typename K, typename V, class UnaryPredicate> bool erase_if(std::map<K,V>& s, UnaryPredicate e) {
		int size = (int) s.size();
        
        for (auto it = s.begin(), end = s.end(); it != end; )
        {
            if (e(it))
            {
                it = s.erase(it);
            }
            else
            {
                ++it;
            }
        }

		return s.size() < size;
	}
	
	template<typename K, typename V> bool erase_with_function(std::map<K,V>& s, std::function<bool (const K&, const V&)> e) {
		int size = (int) s.size();
        
        for (auto it = s.begin(), end = s.end(); it != end; )
        {
            if (e(it->first,it->second))
            {
                it = s.erase(it);
            }
            else
            {
                ++it;
            }
        }
        
		return s.size() < size;
	}
	
    template<typename K, typename V> bool erase_all_with_value(std::map<K,V>& s, const V & v) {
        std::function<bool (const K&, const V&)> f = [v] (const K& key, const V& value) { return value==v; };
        return erase_with_function(s,f);
	}
	

    
    
    
    
    template<typename T, class UnaryPredicate> bool contains_if (std::list<T>& s, UnaryPredicate f) {
        for(autoCRef e:s) if (f(e)) return true;
        return false;
    }
    
    template<typename T, class UnaryPredicate> bool contains_if (std::vector<T>& s, UnaryPredicate f) {
        for(autoCRef e:s) if (f(e)) return true;
        return false;
    }
    
    template<typename T, class UnaryPredicate> bool contains_if (std::set<T>& s, UnaryPredicate f) {
        for(autoCRef e:s) if (f(e)) return true;
        return false;
    }
    

    
    
    
    template<typename T, class UnaryPredicate> bool find_if (std::list<T>& s, UnaryPredicate f, T& r) {
        for(autoCRef e:s) if (f(e)) { r = e; return true;};
        return false;
    }
    
    template<typename T, class UnaryPredicate> bool find_if (std::vector<T>& s, UnaryPredicate f, T& r) {
        for(autoCRef e:s) if (f(e)) { r = e; return true;};
        return false;
    }
    
    template<typename T, class UnaryPredicate> bool find_if (std::set<T>& s, UnaryPredicate f, T& r) {
        for(autoCRef e:s) if (f(e)) { r = e; return true;};
        return false;
    }
    
    
    
    
    
    
    
    template<typename T> void limit(int limit, priority_queue<T>& c)
    {
        while (limit < c.size())
            c.pop();
    }

    
    
    template<typename T> void clear(std::priority_queue<T>& p)
    {
        while(not p.empty())
            p.pop();
    }
    
    
    
    template<typename T>
	std::list<T>& append(std::list<T>& to, const std::list<T>& from) {
		to.insert(to.end(),from.begin(),from.end());
		return to;
	}
	

	
	template<typename V> void append(std::vector<V>& C, const std::list<V>& D) {
		if ((C.size()+D.size()) < C.capacity()) {
			C.reserve(C.size()+D.size());
		}
		std::copy(std::begin(D),std::end(D),std::back_inserter(C));
	}
	
	template<typename V> std::vector<V>& append(std::vector<V>& C, const V & D) {
        C.push_back(D);
        return C;
	}
	
	template<typename V> std::vector<V>& append(std::vector<V>& C, const std::vector<V>& D) {
		if ((C.size()+D.size()) < C.capacity()) {
			C.reserve(C.size()+D.size());
		}
		std::copy(std::begin(D),std::end(D),std::back_inserter(C));
        return C;
	}
	
	template<typename V> std::vector<V>& append(std::vector<V>& C, const std::set<V>& D) {
		if ((C.size()+D.size()) < C.capacity()) {
			C.reserve(C.size()+D.size());
		}
		std::copy(std::begin(D),std::end(D),std::back_inserter(C));
        return C;
	}
	
	template<typename V> std::vector<V>& append(std::vector<V>& C, const std::multiset<V>& D) {
		if ((C.size()+D.size()) < C.capacity()) {
			C.reserve(C.size()+D.size());
		}
		std::copy(std::begin(D),std::end(D),std::back_inserter(C));
        return C;
	}
	
	
	template<typename V> V& append(V& C, const V & D) {
		std::copy(std::begin(D),std::end(D),std::back_inserter(C));
        return C;
	}
    

    
    template<typename V> bool add(std::set<V>& S, const V & D) {
        int i =(int) S.size();
        S.insert(D);
        return i!=(int)S.size();
    }
    

    
    
//    template<class T> vector<T> & operator += (vector<T>& r, const T& e)            { r.push_back(e); return r; }
//    template<class T> vector<T> & operator += (vector<T>& r, const pair<T,T>& e)    { r.push_back(e.first); r.push_back(e.second); return r; }
    template<class T> vector<T> & operator += (vector<T>& r, const vector<T>& e)    { r.reserve(r.size()+e.size()); for(autoCRef t:e) r.push_back(t); return r; }
//    template<class T> vector<T> & operator += (vector<T>& r, const set<T>& e)       { r.reserve(r.size()+e.size()); for(autoCRef t:e) r.push_back(t); return r; }
//    template<class T> vector<T> & operator += (vector<T>& r, const list<T>& e)      { r.reserve(r.size()+e.size()); for(autoCRef t:e) r.push_back(t); return r; }
    
//    template<class T> list<T> & operator += (list<T>& r, const T& e)            { r.push_back(e); return r; }
//    template<class T> list<T> & operator += (list<T>& r, const pair<T,T>& e)    { r.push_back(e.first); r.push_back(e.second); return r; }
    template<class T> list<T> & operator += (list<T>& r, const vector<T>& e)    { for(autoCRef t:e) r.push_back(t); return r; }
//    template<class T> list<T> & operator += (list<T>& r, const list<T>& e)      { for(autoCRef t:e) r.push_back(t); return r; }
//    template<class T> list<T> & operator += (list<T>& r, const set<T>& e)       { for(autoCRef t:e) r.push_back(t); return r; }
    
//    template<class T> set<T> & operator += (set<T>& r, const T& e)            { r.insert(e); return r; }
//    template<class T> set<T> & operator += (set<T>& r, const pair<T,T>& e)    { r.insert(e.first); r.insert(e.second); return r; }
    template<class T> set<T> & operator += (set<T>& r, const vector<T>& e)    { for(autoCRef t:e) r.insert(t); return r; }
//    template<class T> set<T> & operator += (set<T>& r, const set<T>& e)       { for(autoCRef t:e) r.insert(t); return r; }
//    template<class T> set<T> & operator += (set<T>& r, const list<T>& e)      { for(autoCRef t:e) r.insert(t); return r; }
    

    template<class K, class V> map<K,V> & operator +=       (map<K,V>& r, const map<K,V>& from)    { for(autoCRef e:from) r[e.first]=e.second; return r; }
    template<class K, class V> map<K,V> & map_add           (map<K,V>& r, const map<K,V>& from)    { for(autoCRef e:from) r[e.first]=e.second; return r; }
	
    
    
    
    
    template<typename E> bool insert(std::set<E>& c, const E& e) {
        int s = (int) c.size();
        c.insert(e);
        return s != (int)c.size();
    }
    
	template<typename V> V& insert(V& C, const V & D) {
		for(const auto & d:D)
			C.insert(d);
        return C;
	}
	
    
    template<typename T> setRef(T) set_union        (setRef(T) a, setCRef(T) b) { for(const T & e:b) a.insert(e); return a; }
    template<typename T> setRef(T) set_difference   (setRef(T) a, setCRef(T) b) { for(const T & e:b) a.erase(e); return a; }
    template<typename T> setRef(T) set_intersection (setRef(T) a, setCRef(T) b) {
        for(auto i = begin(a); i != end(a); )
            if (contains(b,*i))
                i++;
            else
                i = a.erase(i);
        return a;
    }
    
    template<typename T> set<T>     operator  + (setCRef(T) a, setCRef(T) b)    { auto r = a; return set_union(r,b); }
    
    template<typename T> setRef(T)  operator += (setRef(T) a, setCRef(T) b)     { return set_union(a,b); }
    template<typename T> setRef(T)  operator -= (setRef(T) a, setCRef(T) b)     { return set_difference(a,b); }
    template<typename T> setRef(T)  operator *= (setRef(T) a, setCRef(T) b)     { return set_intersection(a,b); }
    
    template<typename T> bool set_is_subset_of (setCRef(T) a, setCRef(T) b) {
        if (b.size() < a.size()) return false;
        for(auto i = begin(a); i != end(a); i++) {
            if (not contains(b,*i))
                return false;
        }
        return true;
    }

    
    
    
    template<typename V> std::vector<V *>& append(std::vector<V *>& C, V * D) {
        if (D) {
            C.push_back(D);
        }
        return C;
	}
	
    template<typename V> std::list<V *>& append(std::list<V *>& C, V * D) {
        if (D) {
            C.push_back(D);
        }
        return C;
	}
	

    
	
	
	template<typename T, typename C> struct appender {
		appender(C& c) : container(c) {}
		
		void append(const T& p) { append(container,p); }
		
	private:
		C& container;
	};
	
	template<typename T> struct list_appender : public appender<list<T>,T> {
		list_appender(list<T>& c) : appender<list<T>,T>(c) {}
	};
	
	template<typename T> struct vector_appender : public appender<vector<T>,T> {
		vector_appender(vector<T>& c) : appender<vector<T>,T>(c) {}
	};
	
	
    
    
    
	
	template<typename T> std::list<T> to_list(const std::set<T>& p) {
		list<T> r;
        for(autoCRef e:p) r.push_back(e);
		return r;
	}
	
	template<typename T> std::list<T> to_list(const std::vector<T>& p) {
		list<T> r;
        for(autoCRef e:p) r.push_back(e);
		return r;
	}
	
	template<typename T> std::vector<T> to_vector(const std::list<T>& p) {
		vector<T> r;
        r.reserve(p.size());
        for(autoCRef e:p) r.push_back(e);
		return r;
	}
	
	template<typename T> std::vector<T> to_vector(const std::set<T>& p) {
		vector<T> r;
        r.reserve(p.size());
        for(autoCRef e:p) r.push_back(e);
		return r;
	}
	
	template<typename T> std::vector<T> to_vector(const multiset<T>& p) {
		vector<T> r;
        r.reserve(p.size());
        for(autoCRef e:p) r.push_back(e);
		return r;
	}
	
	template<typename T> std::set<T> to_set(const std::list<T>& p) {
		set<T> r;
        for(autoCRef e:p) r.insert(e);
		return r;
	}
	
	template<typename T> std::set<T> to_set(const std::vector<T>& p) {
		set<T> r;
        for(autoCRef e:p) r.insert(e);
		return r;
	}
    
    
    
    
    template<typename T> int index_of(const std::vector<T>& p, const T& v, int r = -1) {
        loopUpTo(i,p.size()) if (p[i]==v) return i;
        return r;
    }
    
    template<typename T> int index_of(const std::list<T>& p, const T& v, int r = -1) {
        int i = 0;
        for(auto t=p.begin(); t != p.end(); t++,i++) if ((*t)==v) return i;
        return r;
    }
    
    template<typename T> int index_of(const std::set<T>& p, const T& v, int r = -1) {
        return index_of(to_vector(p),v,r);
    }
    
    
    
    
    
#define std_vectorWithCapacity(NAME,TYPE,CAPACITY)  std::vector< TYPE > NAME; NAME . reserve( CAPACITY )
#define std_VectorWithSize(NAME,TYPE,CAPACITY)      std::vector< TYPE > NAME; NAME . resize( CAPACITY )
	
    template<typename T> std::vector<T> filter_vector(const std::vector<T>& p, std::function<bool (const T &)> f)   { std_vectorWithCapacity(r, T , p.size()); for(const T &e:p) if (f(e)) r.push_back(e); return r; }
    template<typename T> std::set<T>    filter_set   (const std::set<T>& p, std::function<bool (const T &)> f)      { std::set<T> r; for(const T &e:p) if (f(e)) r.insert(e); return r; }
	
	

	
    
    template<class T> std::vector<T> make_vector(const std::vector<T>& p) { return p; }
    template<class T> std::set<T> make_set(const std::set<T>& p) { return p; }

    
    
    
    
    
    template<class T> std::vector<T> every_nth(const std::vector<T>& p, int nth)
    {
        std::vector<T> r;
        r.reserve(p.size()/nth+1);
        
        loopUpTo(i,p.size()) {
            if (is_nth(i,nth)) {
                r.push_back(p[i]);
            }
        }
        return p;
    }

	


    template<class T> std::vector<T> every_nth_from(const std::vector<T>& p, int nth, int from)
    {
        std::vector<T> r;
        r.reserve(p.size()/nth+1);
        
        loopUpFromTo(i,from,p.size()) {
            if (is_nth(i-from,nth)) {
                r.push_back(p[i]);
            }
        }
        return p;
    }
    
    
    
    

    
    
    template<typename F, typename S> std::vector<F> extract_first(const std::vector<pair<F,S>>& p) {
        std::vector<F> r;
        r.reserve(p.size());
        for(auto & e:p) {
            r.push_back(e.first);
        }
        return r;
	}
	
    template<typename F, typename S> std::vector<S> extract_second(const std::vector<pair<F,S>>& p) {
        std::vector<S> r;
        r.reserve(p.size());
        for(auto & e:p) {
            r.push_back(e.second);
        }
        return r;
	}
	
    template<typename F, typename S, typename T> std::vector<F> extract_first(const std::vector<tuple<F,S,T>>& p) {
        std::vector<F> r;
        r.reserve(p.size());
        for(auto & e:p) {
            r.push_back(std::get<0>(e));
        }
        return r;
	}
	

	
	
	
	
	template<typename A, typename B> std::list<tuple<A,B>> cross(const std::list<A>& a, const std::list<B>& b) {
		list<tuple<A,B>> r;
		for(auto i:a) {
			for(auto ii:b) {
				r.push_back({i,ii});
			}
		}
		return r;
	}
	
	template<typename A, typename B, typename C> std::list<tuple<A,B,C>> cross(const std::list<A>& a, const std::list<B>& b, const std::list<C>& c) {
		list<tuple<A,B,C>> r;
		for(auto i:a) {
			for(auto ii:b) {
				for(auto iii:c) {
					r.push_back({i,ii,iii});
				}
			}
		}
		return r;
	}
	
	
	
    
    
    template<typename Iterator, typename T>     void        execute_on_first_of     (Iterator begin, Iterator end, std::function<bool (const T&)> f)    { for(auto i = begin; i != end; i++) if (f(*i)) break; }
    template<typename Iterator, typename T>     void        execute_on_all_of       (Iterator from, Iterator to, std::function<void (const T&)> f)      { for(auto i = from; i != to; i++) { f(*i); } }
    template<typename Iterator, typename T>     void        execute_on_all_of       (Iterator from, Iterator to, std::function<void (T)> f)             { for(auto i = from; i != to; i++) { f(*i); } }
    template<typename T>                        void        execute_on_first_of     (vectorCRef(T) elements, std::function<bool (const T&)> f)          { execute_on_first_of(elements.begin(),elements.end()); }
    template<typename T>                        void        execute_on_all_of       (vectorCRef(T) elements, std::function<void (const T&)> f)          { for(autoCRef t:elements) { f(t); } }
    template<typename T>                        void        execute_on_all_of       (vectorCRef(T) elements, std::function<void (T)> f)                 { for(autoCRef t:elements) { f(t); } }
    
    
	
	
	
	
	
	template<typename T> bool any_of(const T& a, const std::vector<T>& c) {
		for(const T& i:c) {
			if (i == a)
				return true;
		}
		return false;
	}
	
	template<typename T> bool all_of(const T& a, const std::vector<T>& c) {
		for(const T& i:c) {
			if (i != a)
				return false;
		}
		return true;
	}
	
	
	
	
	
	
	inline bool any_of(const std::vector<bool>& p) {
		for(bool i:p)
			if (i) return true;
		return false;
	}
	
	inline bool all_of(const std::vector<bool>& p) {
		for(bool i:p)
			if (not i) return false;
		return true;
	}
	
	inline bool none_of(const std::vector<bool>& p) {
		for(bool i:p)
			if (i) return false;
		return true;
	}
	
	inline bool one_of(const std::vector<bool>& p) {
		bool found = false;
		for(bool i:p)
			if (i) {
				if (found)
					return false;
				found = true;
			}
		return found;
	}
	
	inline bool n_of(unsigned int n, const std::vector<bool>& p) {
		for(bool i:p)
			if (i) {
				if (0 == n)
					return false;
				n--;
			}
		return 0 == n;
	}
	
	inline bool n_not_of(unsigned int n, const std::vector<bool>& p) {
		for(bool i:p)
			if (not i) {
				if (0 == n)
					return false;
				n--;
			}
		return 0 == n;
	}
	
	
	
	
	
	
	template <typename E>
	typename std::underlying_type<E>::type underlying(E e) {
		return static_cast<typename std::underlying_type<E>::type>(e);
	}
	
	
	
    
    
    
    
    
    template<typename T> struct exclusive_set
    {
        exclusive_set() {}
        exclusive_set(vectorCRef(setCRef(T)) r) {
            for(autoCRef group:r) {
                for(autoCRef element:group) {
                    autoRef others = rules[element];
                    others = group;
                    others -= {element};
                }
            }
        }
        void insert(const T & p) {
            std::set<T> others;
            if (get(rules,p,others)) {
                set_difference(all,others);
            }
            all += {p};
        }
        inline exclusive_set & operator = (const T & p) { insert(p); return *this; }
        
        inline bool         has             (const T & p) const     { return contains(all,p); }
        inline setCRef(T)   values          () const        { return all; }
        
        protected:
            std::set<T> all;
            std::map<T,std::set<T>> rules;
    };
    

    
    
    
    
    inline double                   maximum (std::vector<double> p)             { return * std::max_element(p.begin(),p.end()); }
    inline double                   minimum (std::vector<double> p)             { return * std::max_element(p.begin(),p.end()); }
	
    template<class Compare> double  maximum (std::vector<double> p, Compare c)  { return * std::max_element(p.begin(),p.end(),c); }
    template<class Compare> double  minimum (std::vector<double> p, Compare c)  { return * std::min_element(p.begin(),p.end(),c); }
	
    template<class T> std::pair<T,T> minmax  (const std::pair<T,T> & p)         { return make_pair(std::min(p.first,p.second),std::max(p.first,p.second)); }
    template<class T> std::pair<T,T> order   (T a, T b)                         { return make_pair(std::min(a,b),std::max(a,b)); }
    
    
    
    
    STRUCT (FlagsWithHistory)
    {
        FlagsWithHistory(const std::vector<bool> & v, int history = 2) {
            tAssert(2 <= history);
            states.reserve(history);
            states.push_back(v);
        }
        
        FlagsWithHistory(int count, int history = 2) {
            tAssert(2 <= history);
            states.reserve(history);
            states.push_back(std::vector<bool>(count,false));
        }
        
        typedef std::function<void (FlagsWithHistoryRef,int,bool)> Listener;
        
        bool flagSet    (int index, bool flag)
        {
            autoRef last = states.back();
            if (last[index] xor flag)
            {
                if (states.capacity() <= states.size())
                {
                    states.front() = states.back();
                    std::rotate(states.begin(),states.begin()+1,states.end());
                }
                else
                {
                    states.push_back(states.back());
                }
                autoRef current = states.back();
                current[index] = flag;
                if (listener) listener(*this,index,flag);
                return true;
            }
            return false;
        }
        
        inline bool                 flagSetOn       (int index)         { return flagSet(index,true); }
        inline bool                 flagSetOff      (int index)         { return flagSet(index,false); }
        inline bool                 flagIsOn        (int index) const   { return states.back()[index]; }
        
        inline std::vector<bool>    stateGet        (int index) const   { return states[states.size()-1-index]; }
        inline std::vector<bool>    stateGetCurrent () const            { return stateGet(0); }
        
        inline void                 listenerSet     (Listener p)        { listener = p; }
        
    private:
        
        Listener listener = 0;
        std::vector<std::vector<bool>> states;
    };
    
    
    
    
    
    template<typename T> std::list<T> &     reverse     (std::list<T> & p)
    {
        std::reverse(p.begin(),p.end());
        return p;
    }
    
    template<typename T> std::vector<T> &   reverse     (std::vector<T> & p)
    {
        std::reverse(p.begin(),p.end());
        return p;
    }


    template<typename T> std::list<T>       reversed    (const std::list<T> & p)
    {
        auto d = p;
        std::reverse(d.begin(),d.end());
        return d;
    }
    
    template<typename T> std::vector<T>     reversed    (const std::vector<T> & p)
    {
        auto d = p;
        std::reverse(d.begin(),d.end());
        return d;
    }
    
    
    

    
    template<class T> std::vector<T>                apply               (std::vector<T> p, std::function<void (T&)> f)
    {
        for(autoRef i:p) { f(i); }
        
        return p;
    }
    
    template<class T> std::vector<T>                combine             (std::vector<T> a, std::vector<T> b)
    {
        a.reserve(a.size()+b.size());
        
        for(autoCRef i:b) a.push_back(i);
        
        return a;
    }
    

    
    
    
    template<typename T> std::vector<T> &   shuffle         (std::vector<T> & p)
    {
        std::random_shuffle (p.begin(),p.end());
        
        return p;
    }
    
    
    template<typename T> std::vector<T>     shuffled        (const std::vector<T> & p)
    {
        auto d = p;
        
        return shuffle(d);
    }
    


    
    
    
    
    
    template<class A, class B> bool setIfDifferent (A & a, const B & b)
    {
        if (a != b)
        {
            a = b;
            return true;
        }
        return false;
    }

    

    
    
    
}