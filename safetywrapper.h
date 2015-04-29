#ifndef SAFETYWRAPPER_H
#define SAFETYWRAPPER_H

/** This is from http://www.stroustrup.com/wrapper.pdf */

#include <iostream>
#include <ctime>
using namespace std;

std::clock_t prefix();
void suffix(std::clock_t start);

template<class T> class SafetyWrap;

template<class T>
class SuffixWrapper
{
        T* p;
        mutable bool own;
        std::clock_t start;

        SuffixWrapper(T* p, std::clock_t start): p(p), own(true), start(start) {};
        SuffixWrapper(const SuffixWrapper& a): p(a.p), own(true), start(a.start) { a.own=false; };
        SuffixWrapper& operator=(const SuffixWrapper&);

        public:
        template<class U>friend class SafetyWrap;

        ~SuffixWrapper() { if(own) suffix(start); };

        T* operator->() const { return p; }
};

template<class T>
class SafetyWrap
{
    T*p;
    int* owned;
    void incr_owned() const { if(owned) ++*owned; }
    void decr_owned() const { if(owned && --*owned==0) { delete p; delete owned; } }
public:
    SafetyWrap(T& p): p(p), owned(0) { }
    SafetyWrap(T* p) : p(p), owned(new int(1)) { }

    SafetyWrap(const SafetyWrap& p) :p(p.p), owned(p.owned) { incr_owned(); }

    SafetyWrap& operator=(const SafetyWrap& a)
    {
        a.incr_owned();
        decr_owned();
        p = a.p;
        owned = a.owned;
        return *this;
    }

    ~SafetyWrap() { decr_owned(); }

    SuffixWrapper<T> operator->() { std::clock_t start = prefix(); return SuffixWrapper<T>(p, start); }

    T* direct() const { return p; }
};

#endif // SAFETYWRAPPER_H
