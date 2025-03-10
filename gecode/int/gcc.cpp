/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Patrick Pekczynski <pekczynski@ps.uni-sb.de>
 *     Guido Tack <tack@gecode.org>
 *
 *  Contributing authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Patrick Pekczynski, 2004
 *     Christian Schulte, 2009
 *     Guido Tack, 2006
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <gecode/int/gcc.hh>

namespace Gecode {

  namespace {

    /// Comparison operator
    template<class X>
    struct LessP {
      bool operator ()(const std::pair<X,int>& lhs,
                       const std::pair<X,int>& rhs) {
        return lhs.second < rhs.second;
      }
    };

    /// Make \a x and \a y equal
    IntVar unify(Home home, IntVar x, IntVar y) {
      rel(home, x, IRT_EQ, y);
      return x;
    }
    /// Make \a x and \a y equal
    IntSet unify(Home, const IntSet& x, const IntSet& y) {
      IntSetRanges xr(x);
      IntSetRanges yr(y);
      Iter::Ranges::Inter<IntSetRanges,IntSetRanges> i(xr,yr);
      IntSet z(i);
      return z;
    }

    /// Remove duplicate entries in \a v from both \a v and \a c
    template<class A>
    void removeDuplicates(Home home, A& c, IntArgs& v) {
      typedef typename A::value_type S;
      typedef std::pair<S,int> P;
      Region re;
      P* a = re.alloc<P>(c.size());
      for (int i=0; i<c.size(); i++)
        a[i] = P(c[i],v[i]);
      LessP<S> l;
      Support::quicksort(a,c.size(),l);
      A cc;
      IntArgs vv;
      int cur = a[0].second-1;
      for (int i=0; i<c.size(); i++) {
        if (a[i].second==cur) {
          cc[cc.size()-1] = unify(home, cc[cc.size()-1], a[i].first);
        } else {
          cc << a[i].first;
          vv << a[i].second;
          cur = a[i].second;
        }
      }
      re.free<P>(a,c.size());
      c = cc;
      v = vv;
    }

  }

  void count(Home home, const IntVarArgs& x,
             const IntVarArgs& _c, const IntArgs& _v,
             IntPropLevel ipl) {
    using namespace Int;
    IntVarArgs c(_c);
    IntArgs v(_v);
    if (v.size() != c.size())
      throw ArgumentSizeMismatch("Int::count");
    if (same(x))
      throw ArgumentSame("Int::count");

    GECODE_POST;

    removeDuplicates(home,c,v);

    ViewArray<IntView> xv(home, x);
    ViewArray<GCC::CardView> cv(home, c.size());
    // set the cardinality
    for (int i=0; i<v.size(); i++)
      cv[i].init(c[i],v[i]);
    switch (vbd(ipl)) {
    case IPL_BND:
      GECODE_ES_FAIL(
                     (GCC::Bnd<GCC::CardView>::post(home,xv,cv)));
      break;
    case IPL_DOM:
      GECODE_ES_FAIL(
                     (GCC::Dom<GCC::CardView>::post(home,xv,cv)));
      break;
    default:
      GECODE_ES_FAIL(
                     (GCC::Val<GCC::CardView>::post(home,xv,cv)));
    }
  }

  // domain is 0..|cards|- 1
  void count(Home home, const IntVarArgs& x, const IntVarArgs& c,
             IntPropLevel ipl) {
    IntArgs values(c.size());
    for (int i=0; i<c.size(); i++)
      values[i] = i;
    count(home, x, c, values, ipl);
  }

  // constant cards
  void count(Home home, const IntVarArgs& x,
             const IntSetArgs& _c, const IntArgs& _v,
             IntPropLevel ipl) {
    using namespace Int;
    IntSetArgs c(_c);
    IntArgs v(_v);
    if (v.size() != c.size())
      throw ArgumentSizeMismatch("Int::count");
    if (same(x))
      throw ArgumentSame("Int::count");
    for (int i=0; i<c.size(); i++) {
      Limits::check(v[i],"Int::count");
      Limits::check(c[i].min(),"Int::count");
      Limits::check(c[i].max(),"Int::count");
    }

    GECODE_POST;

    removeDuplicates(home,c,v);

    ViewArray<IntView> xv(home, x);

    for (int i=0; i<v.size(); i++) {
      if (c[i].ranges() > 1) {
        // Found hole, so create temporary variables
        ViewArray<GCC::CardView> cv(home, v.size());
        for (int j=0; j<v.size(); j++)
          cv[j].init(home,c[j],v[j]);
        switch (vbd(ipl)) {
        case IPL_BND:
          GECODE_ES_FAIL(
                         (GCC::Bnd<GCC::CardView>::post(home, xv, cv)));
          break;
        case IPL_DOM:
          GECODE_ES_FAIL(
                         (GCC::Dom<GCC::CardView>::post(home, xv, cv)));
          break;
        default:
          GECODE_ES_FAIL(
                         (GCC::Val<GCC::CardView>::post(home, xv, cv)));
        }
        return;
      }
    }

    // No holes: create CardConsts
    ViewArray<GCC::CardConst> cv(home, c.size());

    for (int i=0; i<c.size(); i++)
      cv[i].init(home,c[i].min(),c[i].max(),v[i]);

    switch (vbd(ipl)) {
    case IPL_BND:
      GECODE_ES_FAIL(
                     (GCC::Bnd<GCC::CardConst>::post(home, xv, cv)));
      break;
    case IPL_DOM:
      GECODE_ES_FAIL(
                     (GCC::Dom<GCC::CardConst>::post(home, xv, cv)));
      break;
    default:
      GECODE_ES_FAIL(
                     (GCC::Val<GCC::CardConst>::post(home, xv, cv)));
    }
  }

  // domain is 0..|cards|- 1
  void count(Home home, const IntVarArgs& x, const IntSetArgs& c,
             IntPropLevel ipl) {
    IntArgs values(c.size());
    for (int i=0; i<c.size(); i++)
      values[i] = i;
    count(home, x, c, values, ipl);
  }

  void count(Home home, const IntVarArgs& x,
             const IntSet& c, const IntArgs& v,
             IntPropLevel ipl) {
    IntSetArgs cards(v.size());
    for (int i=0; i<v.size(); i++)
      cards[i] = c;
    count(home, x, cards, v, ipl);
  }

}

// STATISTICS: int-post
