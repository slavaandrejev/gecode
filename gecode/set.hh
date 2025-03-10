/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Guido Tack <tack@gecode.org>
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Contributing authors:
 *     Gabor Szokoli <szokoli@gecode.org>
 *
 *  Copyright:
 *     Guido Tack, 2004
 *     Christian Schulte, 2004
 *     Gabor Szokoli, 2004
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

#ifndef GECODE_SET_HH
#define GECODE_SET_HH

#include <gecode/kernel.hh>
#include <gecode/int.hh>
#include <gecode/iter.hh>

#include <functional>

/*
 * Configure linking
 *
 */
#if !defined(GECODE_STATIC_LIBS) && \
    (defined(__CYGWIN__) || defined(__MINGW32__) || defined(_MSC_VER))

#ifdef GECODE_BUILD_SET
#define GECODE_SET_EXPORT __declspec( dllexport )
#else
#define GECODE_SET_EXPORT __declspec( dllimport )
#endif

#else

#ifdef GECODE_GCC_HAS_CLASS_VISIBILITY
#define GECODE_SET_EXPORT __attribute__ ((visibility("default")))
#else
#define GECODE_SET_EXPORT
#endif

#endif

// Configure auto-linking
#ifndef GECODE_BUILD_SET
#define GECODE_LIBRARY_NAME "Set"
#include <gecode/support/auto-link.hpp>
#endif


/**
 * \namespace Gecode::Set
 * \brief Finite integer sets
 *
 * The Gecode::Set namespace contains all functionality required
 * to program propagators and branchers for finite integer sets.
 * In addition, all propagators and branchers for finite integer
 * sets provided by %Gecode are contained as nested namespaces.
 *
 */

#include <gecode/set/exception.hpp>

namespace Gecode { namespace Set {

  /// Numerical limits for set variables
  namespace Limits {
    /// Largest allowed integer in integer set
    const int max = (Gecode::Int::Limits::max / 2) - 1;
    /// Smallest allowed integer in integer set
    const int min = -max;
    /// Maximum cardinality of an integer set
    const unsigned int card = max-min+1;
    /// Check whether integer \a n is in range, otherwise throw overflow exception with information \a l
    void check(int n, const char* l);
    /// Check whether unsigned int \a n is in range for cardinality, otherwise throw overflow exception with information \a l
    void check(unsigned int n, const char* l);
    /// Check whether minimum and maximum of IntSet \a s is in range, otherwise throw overflow exception with information \a l
    void check(const IntSet& s, const char* l);
  }

}}

#include <gecode/set/limits.hpp>

#include <gecode/set/var-imp.hpp>

namespace Gecode {

  namespace Set {
    class SetView;
  }

  /**
   * \brief %Set variables
   *
   * \ingroup TaskModelSetVars
   */
  class SetVar : public VarImpVar<Set::SetVarImp> {
    friend class SetVarArray;
    friend class SetVarArgs;
    using VarImpVar<Set::SetVarImp>::x;
  public:
    /// \name Constructors and initialization
    //@{
    /// Default constructor
    SetVar(void);
    /// Initialize from set variable \a y
    SetVar(const SetVar& y);
    /// Initialize from set view \a y
    SetVar(const Set::SetView& y);

    /// Initialize variable with empty greatest lower and full least upper bound
    GECODE_SET_EXPORT SetVar(Space& home);

    /**
     * \brief Initialize variable with given bounds and cardinality
     *
     * The variable is created with
     * greatest lower bound \f$\{\mathit{glbMin},\dots,\mathit{glbMax}\}\f$,
     * least upper bound \f$\{\mathit{lubMin},\dots,\mathit{lubMax}\}\f$, and
     * cardinality minimum \a cardMin and maximum \a cardMax.
     * The following exceptions might be thrown:
     *  - If the bounds are no legal set bounds (between Set::Limits::min
     *    and Set::Limits::max), an exception of type
     *    Gecode::Set::OutOfLimits is thrown.
     *  - If the cardinality is greater than Set::Limits::max_set_size, an
     *    exception of type Gecode::Set::OutOfLimits is
     *    thrown.
     *  - If \a cardMin > \a cardMax, an exception of type
     *    Gecode::Set::VariableEmptyDomain is thrown.
     */
    GECODE_SET_EXPORT
    SetVar(Space& home,int glbMin,int glbMax,int lubMin,int lubMax,
           unsigned int cardMin = 0,
           unsigned int cardMax = Set::Limits::card);

    /**
     * \brief Initialize variable with given bounds and cardinality
     *
     * The variable is created with greatest lower bound \a glbD,
     * least upper bound \f$\{\mathit{lubMin},\dots,\mathit{lubMax}\}\f$, and
     * cardinality minimum \a cardMin and maximum \a cardMax.
     * The following exceptions might be thrown:
     *  - If the bounds are no legal set bounds (between Set::Limits::min
     *    and Set::Limits::max), an exception of type
     *    Gecode::Set::OutOfLimits is thrown.
     *  - If the cardinality is greater than Set::Limits::max_set_size, an
     *    exception of type Gecode::Set::OutOfLimits is
     *    thrown.
     *  - If \a cardMin > \a cardMax, an exception of type
     *    Gecode::Set::VariableEmptyDomain is thrown.
     */
    GECODE_SET_EXPORT
    SetVar(Space& home,const IntSet& glbD,int lubMin,int lubMax,
           unsigned int cardMin = 0,
           unsigned int cardMax = Set::Limits::card);

    /**
     * \brief Initialize variable with given bounds and cardinality
     *
     * The variable is created with
     * greatest lower bound \f$\{\mathit{glbMin},\dots,\mathit{glbMax}\}\f$,
     * least upper bound \a lubD, and
     * cardinality minimum \a cardMin and maximum \a cardMax.
     * The following exceptions might be thrown:
     *  - If the bounds are no legal set bounds (between Set::Limits::min
     *    and Set::Limits::max), an exception of type
     *    Gecode::Set::OutOfLimits is thrown.
     *  - If the cardinality is greater than Set::Limits::max_set_size, an
     *    exception of type Gecode::Set::OutOfLimits is
     *    thrown.
     *  - If \a minCard > \a maxCard, an exception of type
     *    Gecode::Set::VariableEmptyDomain is thrown.
     */
    GECODE_SET_EXPORT
    SetVar(Space& home,int glbMin,int glbMax,const IntSet& lubD,
           unsigned int cardMin = 0,
           unsigned int cardMax = Set::Limits::card);

    /**
     * \brief Initialize variable with given bounds and cardinality
     *
     * The variable is created with
     * greatest lower bound \a glbD,
     * least upper bound \a lubD, and
     * cardinality minimum \a cardMin and maximum \a cardMax.
     * The following exceptions might be thrown:
     *  - If the bounds are no legal set bounds (between Set::Limits::min
     *    and Set::Limits::max), an exception of type
     *    Gecode::Set::OutOfLimits is thrown.
     *  - If the cardinality is greater than Set::Limits::max_set_size, an
     *    exception of type Gecode::Set::OutOfLimits is
     *    thrown.
     *  - If \a minCard > \a maxCard, an exception of type
     *    Gecode::Set::VariableEmptyDomain is thrown.
     */
    GECODE_SET_EXPORT
    SetVar(Space& home,const IntSet& glbD,const IntSet& lubD,
           unsigned int cardMin = 0,
           unsigned int cardMax = Set::Limits::card);
    //@}

    /// \name Value access
    //@{
    /// Return number of elements in the greatest lower bound
    unsigned int glbSize(void) const;
    /// Return number of elements in the least upper bound
    unsigned int lubSize(void) const;
    /// Return number of unknown elements (elements in lub but not in glb)
    unsigned int unknownSize(void) const;
    /// Return cardinality minimum
    unsigned int cardMin(void) const;
    /// Return cardinality maximum
    unsigned int cardMax(void) const;
    /// Return minimum element of least upper bound
    int lubMin(void) const;
    /// Return maximum element of least upper bound
    int lubMax(void) const;
    /// Return minimum element of greatest lower bound
    int glbMin(void) const;
    /// Return maximum of greatest lower bound
    int glbMax(void) const;
    //@}

    /// \name Domain tests
    //@{
    /// Test whether \a i is in greatest lower bound
    bool contains(int i) const;
    /// Test whether \a i is not in the least upper bound
    bool notContains(int i) const;
    //@}

    /// Assignment operator
    SetVar& operator =(const SetVar&) = default;
  };

  /**
   * \defgroup TaskModelSetIter Range and value iterators for set variables
   * \ingroup TaskModelSet
   */
  //@{

  /// Iterator for the greatest lower bound ranges of a set variable
  class SetVarGlbRanges {
  private:
    Set::GlbRanges<Set::SetVarImp*> iter;
  public:
    /// \name Constructors and initialization
    //@{
    /// Default constructor
    SetVarGlbRanges(void);
    /// Initialize to iterate ranges of variable \a x
    SetVarGlbRanges(const SetVar& x);
    //@}

    /// \name Iteration control
    //@{
    /// Test whether iterator is still at a range or done
    bool operator ()(void) const;
    /// Move iterator to next range (if possible)
    void operator ++(void);
    //@}

    /// \name Range access
    //@{
    /// Return smallest value of range
    int min(void) const;
    /// Return largest value of range
    int max(void) const;
    /// Return width of range (distance between minimum and maximum)
    unsigned int width(void) const;
    //@}
  };

  /// Iterator for the least upper bound ranges of a set variable
  class SetVarLubRanges {
  private:
    Set::LubRanges<Set::SetVarImp*> iter;
  public:
    /// \name Constructors and initialization
    //@{
    /// Default constructor
    SetVarLubRanges(void);
    /// Initialize to iterate ranges of variable \a x
    SetVarLubRanges(const SetVar& x);
    //@}

    /// \name Iteration control
    //@{
    /// Test whether iterator is still at a range or done
    bool operator ()(void) const;
    /// Move iterator to next range (if possible)
    void operator ++(void);
    //@}

    /// \name Range access
    //@{
    /// Return smallest value of range
    int min(void) const;
    /// Return largest value of range
    int max(void) const;
    /// Return width of range (distance between minimum and maximum)
    unsigned int width(void) const;
    //@}
  };

  /// Iterator for the unknown ranges of a set variable
  class SetVarUnknownRanges {
  private:
    Set::UnknownRanges<Set::SetVarImp*> iter;
  public:
    /// \name Constructors and initialization
    //@{
    /// Default constructor
    SetVarUnknownRanges(void);
    /// Initialize to iterate ranges of variable \a x
    SetVarUnknownRanges(const SetVar& x);
    //@}

    /// \name Iteration control
    //@{
    /// Test whether iterator is still at a range or done
    bool operator ()(void) const;
    /// Move iterator to next range (if possible)
    void operator ++(void);
    //@}

    /// \name Range access
    //@{
    /// Return smallest value of range
    int min(void) const;
    /// Return largest value of range
    int max(void) const;
    /// Return width of range (distance between minimum and maximum)
    unsigned int width(void) const;
    //@}
  };

  /// Iterator for the values in the greatest lower bound of a set variable
  class SetVarGlbValues {
  private:
    Iter::Ranges::ToValues<SetVarGlbRanges> iter;
  public:
    /// \name Constructors and initialization
    //@{
    /// Default constructor
    SetVarGlbValues(void);
    /// Initialize to iterate values of variable \a x
    SetVarGlbValues(const SetVar& x);
    //@}

    /// \name Iteration control
    //@{
    /// Test whether iterator is still at a value or done
    bool operator ()(void) const;
    /// Move iterator to next value (if possible)
    void operator ++(void);
    //@}

    /// \name Value access
    //@{
    /// Return current value
    int  val(void) const;
    //@}
  };

  /// Iterator for the values in the least upper bound of a set variable
  class SetVarLubValues {
  private:
    Iter::Ranges::ToValues<SetVarLubRanges> iter;
  public:
    /// \name Constructors and initialization
    //@{
    /// Default constructor
    SetVarLubValues(void);
    /// Initialize to iterate values of variable \a x
    SetVarLubValues(const SetVar& x);
    //@}

    /// \name Iteration control
    //@{
    /// Test whether iterator is still at a value or done
    bool operator ()(void) const;
    /// Move iterator to next value (if possible)
    void operator ++(void);
    //@}

    /// \name Value access
    //@{
    /// Return current value
    int  val(void) const;
    //@}
  };

  /// Iterator for the values in the unknown set of a set variable
  class SetVarUnknownValues {
  private:
    Iter::Ranges::ToValues<SetVarUnknownRanges> iter;
  public:
    /// \name Constructors and initialization
    //@{
    /// Default constructor
    SetVarUnknownValues(void);
    /// Initialize to iterate values of variable \a x
    SetVarUnknownValues(const SetVar& x);
    //@}

    /// \name Iteration control
    //@{
    /// Test whether iterator is still at a value or done
    bool operator ()(void) const;
    /// Move iterator to next value (if possible)
    void operator ++(void);
    //@}

    /// \name Value access
    //@{
    /// Return current value
    int  val(void) const;
    //@}
  };

  //@}

  /**
   * \brief Print set variable \a x
   * \relates Gecode::SetVar
   */
  template<class Char, class Traits>
  std::basic_ostream<Char,Traits>&
  operator <<(std::basic_ostream<Char,Traits>& os, const SetVar& x);

}

#include <gecode/set/view.hpp>

namespace Gecode {
  /**
   * \defgroup TaskModelSetArgs Argument arrays
   *
   * Argument arrays are just good enough for passing arguments
   * with automatic memory management.
   * \ingroup TaskModelSet
   */

  //@{

}

#include <gecode/set/array-traits.hpp>

namespace Gecode {

  /** \brief Passing set variables
   *
   * We could have used a simple typedef instead, but doxygen cannot
   * resolve some overloading then, leading to unusable documentation for
   * important parts of the library. As long as there is no fix for this,
   * we will keep this workaround.
   *
   */
  class SetVarArgs : public VarArgArray<SetVar> {
  public:
    /// \name Constructors and initialization
    //@{
    /// Allocate empty array
    SetVarArgs(void);
    /// Allocate array with \a n elements
    explicit SetVarArgs(int n);
    /// Initialize from variable argument array \a a (copy elements)
    SetVarArgs(const SetVarArgs& a);
    /// Initialize from variable array \a a (copy elements)
    SetVarArgs(const VarArray<SetVar>& a);
    /// Initialize from vector \a a
    SetVarArgs(const std::vector<SetVar>& a);
    /// Initialize from list \a a
    SetVarArgs(std::initializer_list<SetVar> a);
    /// Initialize from InputIterator \a first and \a last
    template<class InputIterator>
    SetVarArgs(InputIterator first, InputIterator last);
    /**
     * \brief Create an array of size \a n.
     *
     * Each variable is initialized with the bounds and cardinality as
     * given by the arguments.
     */
    GECODE_SET_EXPORT
    SetVarArgs(Space& home,int n,int glbMin,int glbMax,
               int lubMin,int lubMax,
               unsigned int minCard = 0,
               unsigned int maxCard = Set::Limits::card);
    /**
     * \brief Create an array of size \a n.
     *
     * Each variable is initialized with the bounds and cardinality as
     * given by the arguments.
     */
    GECODE_SET_EXPORT
    SetVarArgs(Space& home,int n,const IntSet& glb,
               int lubMin, int lubMax,
               unsigned int minCard = 0,
               unsigned int maxCard = Set::Limits::card);
    /**
     * \brief Create an array of size \a n.
     *
     * Each variable is initialized with the bounds and cardinality as
     * given by the arguments.
     */
    GECODE_SET_EXPORT
    SetVarArgs(Space& home,int n,int glbMin,int glbMax,
               const IntSet& lub,
               unsigned int minCard = 0,
               unsigned int maxCard = Set::Limits::card);
    /**
     * \brief Create an array of size \a n.
     *
     * Each variable is initialized with the bounds and cardinality as
     * given by the arguments.
     */
    GECODE_SET_EXPORT
    SetVarArgs(Space& home,int n,
               const IntSet& glb,const IntSet& lub,
               unsigned int minCard = 0,
               unsigned int maxCard = Set::Limits::card);
    /// Assignment operator
    SetVarArgs& operator =(const SetVarArgs&) = default;
    //@}
  };
  //@}

  /**
   * \defgroup TaskModelSetVarArrays Variable arrays
   *
   * Variable arrays can store variables. They are typically used
   * for storing the variables being part of a solution. However,
   * they can also be used for temporary purposes (even though
   * memory is not reclaimed until the space it is created for
   * is deleted).
   * \ingroup TaskModelSet
   */

  /**
   * \brief %Set variable array
   * \ingroup TaskModelSetVarArrays
   */
  class SetVarArray : public VarArray<SetVar> {
  public:
    /// \name Creation and initialization
    //@{
    /// Default constructor (array of size 0)
    SetVarArray(void);
    /// Initialize from set variable array \a a (share elements)
    SetVarArray(const SetVarArray&);
    /// Initialize from set variable argument array \a a (copy elements)
    SetVarArray(Space& home, const SetVarArgs&);
    /// Allocate array for \a n set variables (variables are uninitialized)
    GECODE_SET_EXPORT SetVarArray(Space& home, int n);
    /**
     * \brief Create an array of size \a n.
     *
     * Each variable is initialized with the bounds and cardinality as
     * given by the arguments.
     */
    GECODE_SET_EXPORT
    SetVarArray(Space& home,int n,int glbMin,int glbMax,int lubMin,int lubMax,
                unsigned int minCard = 0,
                unsigned int maxCard = Set::Limits::card);
    /**
     * \brief Create an array of size \a n.
     *
     * Each variable is initialized with the bounds and cardinality as
     * given by the arguments.
     */
    GECODE_SET_EXPORT
    SetVarArray(Space& home,int n,const IntSet& glb, int lubMin, int lubMax,
                unsigned int minCard = 0,
                unsigned int maxCard = Set::Limits::card);
    /**
     * \brief Create an array of size \a n.
     *
     * Each variable is initialized with the bounds and cardinality as
     * given by the arguments.
     */
    GECODE_SET_EXPORT
    SetVarArray(Space& home,int n,int glbMin,int glbMax,const IntSet& lub,
                unsigned int minCard = 0,
                unsigned int maxCard = Set::Limits::card);
    /**
     * \brief Create an array of size \a n.
     *
     * Each variable is initialized with the bounds and cardinality as
     * given by the arguments.
     */
    GECODE_SET_EXPORT
    SetVarArray(Space& home,int n,
                const IntSet& glb,const IntSet& lub,
                unsigned int minCard = 0,
                unsigned int maxCard = Set::Limits::card);
    /// Assignment operator
    SetVarArray& operator =(const SetVarArray&) = default;
    //@}
  };

}

#include <gecode/set/array.hpp>

namespace Gecode {

  /**
   * \brief Common relation types for sets
   *
   * The total order on sets is defined as the lexicographic
   * order on their characteristic functions, e.g.,
   * \f$x\leq y\f$ means that either \f$x\f$ is empty or
   * the minimal element of the symmetric difference
   * \f$x\ominus y\f$ is in \f$y\f$.
   *
   * \ingroup TaskModelSet
   */
  enum SetRelType {
    SRT_EQ,   ///< Equality (\f$=\f$)
    SRT_NQ,   ///< Disequality (\f$\neq\f$)
    SRT_SUB,  ///< Subset (\f$\subseteq\f$)
    SRT_SUP,  ///< Superset (\f$\supseteq\f$)
    SRT_DISJ, ///< Disjoint (\f$\parallel\f$)
    SRT_CMPL, ///< Complement
    SRT_LQ,   ///< Less or equal (\f$\leq\f$)
    SRT_LE,   ///< Less (\f$<\f$)
    SRT_GQ,   ///< Greater or equal (\f$\geq\f$)
    SRT_GR    ///< Greater (\f$>\f$)
  };

  /**
   * \brief Common operations for sets
   * \ingroup TaskModelSet
   */
  enum SetOpType {
    SOT_UNION,  ///< Union
    SOT_DUNION, ///< Disjoint union
    SOT_INTER,  ///< %Intersection
    SOT_MINUS   ///< Difference
  };

  /**
   * \defgroup TaskModelSetDom Domain constraints
   * \ingroup TaskModelSet
   *
   */
  //@{
  /// Propagates \f$ x \sim_r \{i\}\f$
  GECODE_SET_EXPORT void
  dom(Home home, SetVar x, SetRelType r, int i);
  /// Propagates \f$ x_i \sim_r \{i\}\f$ for all \f$0\leq i<|x|\f$
  GECODE_SET_EXPORT void
  dom(Home home, const SetVarArgs& x, SetRelType r, int i);
  /// Propagates \f$ x \sim_r \{i,\dots,j\}\f$
  GECODE_SET_EXPORT void
  dom(Home home, SetVar x, SetRelType r, int i, int j);
  /// Propagates \f$ x \sim_r \{i,\dots,j\}\f$ for all \f$0\leq i<|x|\f$
  GECODE_SET_EXPORT void
  dom(Home home, const SetVarArgs& x, SetRelType r, int i, int j);
  /// Propagates \f$ x \sim_r s\f$
  GECODE_SET_EXPORT void
  dom(Home home, SetVar x, SetRelType r, const IntSet& s);
  /// Propagates \f$ x \sim_r s\f$ for all \f$0\leq i<|x|\f$
  GECODE_SET_EXPORT void
  dom(Home home, const SetVarArgs& x, SetRelType r, const IntSet& s);
  /// Propagates \f$ i \leq |s| \leq j \f$
  GECODE_SET_EXPORT void
  cardinality(Home home, SetVar x, unsigned int i, unsigned int j);
  /// Propagates \f$ i \leq |s| \leq j \f$ for all \f$0\leq i<|x|\f$
  GECODE_SET_EXPORT void
  cardinality(Home home, const SetVarArgs& x, unsigned int i, unsigned int j);
  /// Post propagator for \f$ (x \sim_{rt} \{i\}) \equiv r \f$
  GECODE_SET_EXPORT void
  dom(Home home, SetVar x, SetRelType rt, int i, Reify r);
  /// Post propagator for \f$ (x \sim_{rt} \{i,\dots,j\}) \equiv r \f$
  GECODE_SET_EXPORT void
  dom(Home home, SetVar x, SetRelType rt, int i, int j, Reify r);
  /// Post propagator for \f$ (x \sim_{rt} s) \equiv r \f$
  GECODE_SET_EXPORT void
  dom(Home home, SetVar x, SetRelType rt, const IntSet& s, Reify r);
  /// Constrain domain of \a x according to domain of \a d
  GECODE_SET_EXPORT void
  dom(Home home, SetVar x, SetVar d);
  /// Constrain domain of \f$ x_i \f$ according to domain of \f$ d_i \f$ for all \f$0\leq i<|x|\f$
  GECODE_SET_EXPORT void
  dom(Home home, const SetVarArgs& x, const SetVarArgs& d);
  //@}


  /**
   * \defgroup TaskModelSetRel Relation constraints
   * \ingroup TaskModelSet
   *
   */
  //@{
  /// Post propagator for \f$ x \sim_r y\f$
  GECODE_SET_EXPORT void
  rel(Home home, SetVar x, SetRelType r, SetVar y);
  /// Post propagator for \f$ (x \sim_{rt} y) \equiv r\f$
  GECODE_SET_EXPORT void
  rel(Home home, SetVar x, SetRelType rt, SetVar y, Reify r);
  /// Post propagator for \f$ s \sim_r \{x\}\f$
  GECODE_SET_EXPORT void
  rel(Home home, SetVar s, SetRelType r, IntVar x);
  /// Post propagator for \f$ \{x\} \sim_r s\f$
  GECODE_SET_EXPORT void
  rel(Home home, IntVar x, SetRelType r, SetVar s);
  /// Post propagator for \f$ (s \sim_{rt} \{x\}) \equiv r\f$
  GECODE_SET_EXPORT void
  rel(Home home, SetVar s, SetRelType rt, IntVar x, Reify r);
  /// Post propagator for \f$ (\{x\} \sim_{rt} s) \equiv r \f$
  GECODE_SET_EXPORT void
  rel(Home home, IntVar x, SetRelType rt, SetVar s, Reify r);
  /// Post propagator for \f$|s|\geq 1 \land \forall i\in s:\ i \sim_{rt} x\f$
  GECODE_SET_EXPORT void
  rel(Home home, SetVar s, IntRelType rt, IntVar x);
  /// Post propagator for \f$|s|\geq 1 \land \forall i\in s:\ x \sim_{rt} i\f$
  void
  rel(Home home, IntVar x, IntRelType rt, SetVar s);
  /// Post reified propagator for \f$\left(|s|\geq 1 \land \forall i\in s:\ i \sim_{rt} x\right)\equiv r\f$
  GECODE_SET_EXPORT void
  rel(Home home, SetVar s, IntRelType rt, IntVar x, Reify r);
  /// Post reified propagator for \f$\left(|s|\geq 1 \land \forall i\in s:\ x \sim_{rt} i\right)\f\equiv r$
  void
  rel(Home home, IntVar x, IntRelType rt, SetVar s, Reify r);
  //@}

}

#include <gecode/set/int.hpp>

namespace Gecode {

  /**
   * \defgroup TaskModelSetRelOp Set operation/relation constraints
   * \ingroup TaskModelSet
   *
   */
  //@{
  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Home home, SetVar x, SetOpType op, SetVar y, SetRelType r, SetVar z);
  /// Post propagator for \f$ y = \diamond_{\mathit{op}} x\f$
  GECODE_SET_EXPORT void
  rel(Home home, SetOpType op, const SetVarArgs& x, SetVar y);
  /// Post propagator for \f$ y = \diamond_{\mathit{op}} x \diamond_{\mathit{op}} z\f$
  GECODE_SET_EXPORT void
  rel(Home home, SetOpType op, const SetVarArgs& x, const IntSet& z, SetVar y);
  /// Post propagator for \f$ y = \diamond_{\mathit{op}} x \diamond_{\mathit{op}} z\f$
  GECODE_SET_EXPORT void
  rel(Home home, SetOpType op, const IntVarArgs& x, const IntSet& z, SetVar y);
  /// Post propagator for \f$ y = \diamond_{\mathit{op}} x\f$
  GECODE_SET_EXPORT void
  rel(Home home, SetOpType op, const IntVarArgs& x, SetVar y);
  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Home home, const IntSet& x, SetOpType op, SetVar y,
      SetRelType r, SetVar z);
  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Home home, SetVar x, SetOpType op, const IntSet& y,
      SetRelType r, SetVar z);
  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Home home, SetVar x, SetOpType op, SetVar y,
      SetRelType r, const IntSet& z);
  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Home home, const IntSet& x, SetOpType op, SetVar y, SetRelType r,
      const IntSet& z);
  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Home home, SetVar x, SetOpType op, const IntSet& y, SetRelType r,
      const IntSet& z);
  /** \brief Post propagator for if-then-else constraint
   *
   * Posts propagator for \f$ z = b ? x : y \f$
   */
  GECODE_SET_EXPORT void
  ite(Home home, BoolVar b, SetVar x, SetVar y, SetVar z);
  //@}


  /**
   * \defgroup TaskModelSetConvex Convexity constraints
   * \ingroup TaskModelSet
   *
   */
  //@{
  /// Post propagator that propagates that \a x is convex
  GECODE_SET_EXPORT void
  convex(Home home, SetVar x);
  /// Post propagator that propagates that \a y is the convex hull of \a x
  GECODE_SET_EXPORT void
  convex(Home home, SetVar x, SetVar y);
  //@}


  /**
   * \defgroup TaskModelSetSequence Sequence constraints
   * \ingroup TaskModelSet
   *
   */
  //@{
  /// Post propagator for \f$\forall 0\leq i< |x|-1 : \max(x_i)<\min(x_{i+1})\f$
  GECODE_SET_EXPORT void
  sequence(Home home, const SetVarArgs& x);
  /// Post propagator for \f$\forall 0\leq i< |x|-1 : \max(x_i)<\min(x_{i+1})\f$ and \f$ x = \bigcup_{i\in\{0,\dots,n-1\}} y_i \f$
  GECODE_SET_EXPORT void
  sequence(Home home, const SetVarArgs& y, SetVar x);
  //@}


  /**
   * \defgroup TaskModelSetDistinct Distinctness constraints
   * \ingroup TaskModelSet
   *
   */
  //@{
  /// Post propagator for \f$\forall 0\leq i\leq |x| : |x_i|=c\f$ and \f$\forall 0\leq i<j\leq |x| : |x_i\cap x_j|\leq 1\f$
  GECODE_SET_EXPORT void
  atmostOne(Home home, const SetVarArgs& x, unsigned int c);
  //@}

  /**
   * \defgroup TaskModelSetConnect Connection constraints to integer variables
   * \ingroup TaskModelSet
   *
   */
  /** \brief Post propagator that \a x is the minimal element of \a s and that \a s is not empty
   * \ingroup TaskModelSetConnect
   */
  GECODE_SET_EXPORT void
  min(Home home, SetVar s, IntVar x);
  /** \brief Post propagator that \a x is not the minimal element of \a s
   * \ingroup TaskModelSetConnect
   */
  GECODE_SET_EXPORT void
  notMin(Home home, SetVar s, IntVar x);
  /** \brief Post reified propagator for \a b iff \a x is the minimal element of \a s 
   * \ingroup TaskModelSetConnect
   */
  GECODE_SET_EXPORT void
  min(Home home, SetVar s, IntVar x, Reify r);
  /** \brief Post propagator that \a x is the maximal element of \a s and that \a s is not empty
   * \ingroup TaskModelSetConnect
   */
  GECODE_SET_EXPORT void
  max(Home home, SetVar s, IntVar x);
  /** \brief Post propagator that \a x is not the maximal element of \a s
   * \ingroup TaskModelSetConnect
   */
  GECODE_SET_EXPORT void
  notMax(Home home, SetVar s, IntVar x);
  /** \brief Post reified propagator for \a b iff \a x is the maximal element of \a s 
   * \ingroup TaskModelSetConnect
   */
  GECODE_SET_EXPORT void
  max(Home home, SetVar s, IntVar x, Reify r);
  /** \brief Post propagator for \f$ |s|=x \f$
   * \ingroup TaskModelSetConnect
   */
  GECODE_SET_EXPORT void
  cardinality(Home home, SetVar s, IntVar x);
  /** \brief Post reified propagator for \f$ |s|=x \equiv r\f$
   * \ingroup TaskModelSetConnect
   */
  GECODE_SET_EXPORT void
  cardinality(Home home, SetVar s, IntVar x, Reify r);
  /**
   * \brief Post propagator for \f$y = \mathrm{weight}(x)\f$
   *
   * The weights are given as pairs of elements and their weight:
   * \f$\mathrm{weight}(\mathrm{elements}_i) = \mathrm{weights}_i\f$
   *
   * The upper bound of \a x is constrained to contain only elements from
   * \a elements. The weight of a set is the sum of the weights of its
   * elements.
   *
   * \ingroup TaskModelSetConnect
   */
  GECODE_SET_EXPORT void
  weights(Home home, IntSharedArray elements, IntSharedArray weights,
          SetVar x, IntVar y);


  /**
   * \defgroup TaskModelSetChannel Channel constraints
   * \ingroup TaskModelSet
   *
   */
  //@{
  /// Post propagator for \f$x_i=j \Leftrightarrow i\in y_j\f$
  GECODE_SET_EXPORT void
  channel(Home home, const IntVarArgs& x,const SetVarArgs& y);
  /// Post propagator for \f$\{x_0,\dots,x_{n-1}\}=y\f$ and \f$x_i<x_{i+1}\f$
  GECODE_SET_EXPORT void
  channelSorted(Home home, const IntVarArgs& x, SetVar y);
  /// Post propagator for \f$x_i=1 \Leftrightarrow i\in y\f$
  GECODE_SET_EXPORT void
  channel(Home home, const BoolVarArgs& x, SetVar y);
  /// Post propagator for \f$j\in x_i \Leftrightarrow i\in y_j\f$
  GECODE_SET_EXPORT void
  channel(Home home, const SetVarArgs& x, const SetVarArgs& y);
  //@}


  /**
   * \defgroup TaskModelSetPrecede Value precedence constraints over set variables
   * \ingroup TaskModelSet
   */
  /** \brief Post propagator that \a s precedes \a t in \a x
   *
   * This constraint enforces that if there exists \f$j\f$ such that
   * \f$s\notin x_j\land t\in x_j\f$, then there exists \f$i<j\f$ such that
   * \f$s\in x_i\land t\notin x_i\f$.
   * \ingroup TaskModelSetPrecede
   */
  GECODE_SET_EXPORT void
  precede(Home home, const SetVarArgs& x, int s, int t);
  /** \brief Post propagator that successive values in \a c precede each other in \a x
   * \ingroup TaskModelSetPrecede
   */
  GECODE_SET_EXPORT void
  precede(Home home, const SetVarArgs& x, const IntArgs& c);


  /**
   * \defgroup TaskModelSetElement Element constraints
   * \ingroup TaskModelSet
   *
   * An element constraint selects zero, one or more elements out of a
   * sequence. We write \f$ \langle x_0,\dots, x_{n-1} \rangle \f$ for the
   * sequence, and \f$ [y] \f$ for the index variable.
   *
   * Set element constraints are closely related to the ::element constraint
   * on integer variables.
   */
  //@{
  /**
   * \brief Post propagator for \f$ z=\diamond_{\mathit{op}}\langle x_0,\dots,x_{n-1}\rangle[y] \f$
   *
   * If \a y is the empty set, the usual conventions for set operations apply:
   * an empty union is empty, while an empty intersection is the universe,
   * which can be given as the optional parameter \a u.
   *
   * The indices for \a y start at 0.
   */
  GECODE_SET_EXPORT void
  element(Home home, SetOpType op, const SetVarArgs& x, SetVar y, SetVar z,
    const IntSet& u = IntSet(Set::Limits::min,Set::Limits::max));
  /**
   * \brief Post propagator for \f$ z=\diamond_{\mathit{op}}\langle \{x_0\},\dots,\{x_{n-1}\}\rangle[y] \f$
   *
   * If \a y is the empty set, the usual conventions for set operations apply:
   * an empty union is empty, while an empty intersection is the universe,
   * which can be given as the optional parameter \a u.
   *
   * The indices for \a y start at 0.
   */
  GECODE_SET_EXPORT void
  element(Home home, SetOpType op, const IntVarArgs& x, SetVar y, SetVar z,
          const IntSet& u = IntSet(Set::Limits::min,Set::Limits::max));
  /**
   * \brief Post propagator for \f$ z=\diamond_{\mathit{op}}\langle x_0,\dots,x_{n-1}\rangle[y] \f$
   *
   * If \a y is the empty set, the usual conventions for set operations apply:
   * an empty union is empty, while an empty intersection is the universe,
   * which can be given as the optional parameter \a u.
   *
   * The indices for \a y start at 0.
   */
  GECODE_SET_EXPORT void
  element(Home home, SetOpType op, const IntSetArgs& x, SetVar y, SetVar z,
          const IntSet& u = IntSet(Set::Limits::min,Set::Limits::max));
  /**
   * \brief Post propagator for \f$ z=\diamond_{\mathit{op}}\langle \{x_0\},\dots,\{x_{n-1}\}\rangle[y] \f$
   *
   * If \a y is the empty set, the usual conventions for set operations apply:
   * an empty union is empty, while an empty intersection is the universe,
   * which can be given as the optional parameter \a u.
   *
   * The indices for \a y start at 0.
   */
  GECODE_SET_EXPORT void
  element(Home home, SetOpType op, const IntArgs& x, SetVar y, SetVar z,
          const IntSet& u = IntSet(Set::Limits::min,Set::Limits::max));
  /**
   * \brief Post propagator for \f$ z=\langle x_0,\dots,x_{n-1}\rangle[y] \f$
   *
   * The indices for \a y start at 0.
   */
  GECODE_SET_EXPORT void
  element(Home home, const SetVarArgs& x, IntVar y, SetVar z);
  /**
   * \brief Post propagator for \f$ z=\langle s_0,\dots,s_{n-1}\rangle[y] \f$
   *
   * The indices for \a y start at 0.
   */
  GECODE_SET_EXPORT void
  element(Home home, const IntSetArgs& s, IntVar y, SetVar z);
  /** \brief Post propagator for \f$ a_{x+w\cdot y}=z\f$
   *
   * Throws an exception of type Set::ArgumentSizeMismatch, if
   * \f$ w\cdot h\neq|a|\f$.
   */
  GECODE_SET_EXPORT void
  element(Home home, const IntSetArgs& a,
          IntVar x, int w, IntVar y, int h, SetVar z);
  /** \brief Post propagator for \f$ a_{x+w\cdot y}=z\f$
   *
   * Throws an exception of type Set::ArgumentSizeMismatch, if
   * \f$ w\cdot h\neq|a|\f$.
   */
  GECODE_SET_EXPORT void
  element(Home home, const SetVarArgs& a,
          IntVar x, int w, IntVar y, int h, SetVar z);
  //@}


  /**
   * \defgroup TaskModelSetExec Synchronized execution
   * \ingroup TaskModelSet
   *
   * Synchronized execution executes a function or a static member function
   * when a certain event happens.
   *
   * \ingroup TaskModelSet
   */
  //@{
  /// Execute \a c when \a x becomes assigned
  GECODE_SET_EXPORT void
  wait(Home home, SetVar x, std::function<void(Space& home)> c);
  /// Execute \a c when all variables in \a x become assigned
  GECODE_SET_EXPORT void
  wait(Home home, const SetVarArgs& x, std::function<void(Space& home)> c);
  //@}

}


namespace Gecode {

  /**
   * \defgroup TaskModelSetBranch Branching
   * \ingroup TaskModelSet
   */

  /**
   * \brief Branch filter function type for set variables
   *
   * The variable \a x is considered for selection and \a i refers to the
   * variable's position in the original array passed to the brancher.
   *
   * \ingroup TaskModelSetBranch
   */
  typedef std::function<bool(const Space& home, SetVar x, int i)>
    SetBranchFilter;
  /**
   * \brief Branch merit function type for set variables
   *
   * The function must return a merit value for the variable
   * \a x.
   * The value \a i refers to the variable's position in the original array
   * passed to the brancher.
   *
   * \ingroup TaskModelSetBranch
   */
  typedef std::function<double(const Space& home, SetVar x, int i)>
    SetBranchMerit;

  /**
   * \brief Branch value function type for set variables
   *
   * Returns a value for the variable \a x that is to be used in the
   * corresponding branch commit function. The integer \a i refers
   * to the variable's position in the original array passed to the
   * brancher.
   *
   * \ingroup TaskModelSetBranch
   */
  typedef std::function<int(const Space& home, SetVar x, int i)>
    SetBranchVal;

  /**
   * \brief Branch commit function type for set variables
   *
   * The function must post a constraint on the variable \a x which
   * corresponds to the alternative \a a. The integer \a i refers
   * to the variable's position in the original array passed to the
   * brancher. The value \a n is the value
   * computed by the corresponding branch value function.
   *
   * \ingroup TaskModelSetBranch
   */
  typedef std::function<void(Space& home, unsigned int a,
                             SetVar x, int i, int n)>
    SetBranchCommit;

}

#include <gecode/set/branch/traits.hpp>

namespace Gecode {

  /**
   * \brief Recording AFC information for set variables
   *
   * \ingroup TaskModelSetBranch
   */
  class SetAFC : public AFC {
  public:
    /**
     * \brief Construct as not yet initialized
     *
     * The only member functions that can be used on a constructed but not
     * yet initialized AFC storage is init or the assignment operator.
     *
     */
    SetAFC(void);
    /// Copy constructor
    SetAFC(const SetAFC& a);
    /// Assignment operator
    SetAFC& operator =(const SetAFC& a);
    /**
     * \brief Initialize for set variables \a x and decay factor \a d
     *
     * If several AFC objects are created for a space or its clones,
     * the AFC values are shared between spaces. If the values should
     * not be shared, \a share should be false.
     */
    SetAFC(Home home, const SetVarArgs& x, double d=1.0, bool share=true);
    /**
     * \brief Initialize for set variables \a x with decay factor \a d
     *
     * This member function can only be used once and only if the
     * AFC storage has been constructed with the default constructor.
     *
     * If several AFC objects are created for a space or its clones,
     * the AFC values are shared between spaces. If the values should
     * not be shared, \a share should be false.
     */
    void init(Home home, const SetVarArgs& x, double d=1.0, bool share=true);
  };

}

#include <gecode/set/branch/afc.hpp>

namespace Gecode {


  /**
   * \brief Recording actions for set variables
   *
   * \ingroup TaskModelSetBranch
   */
  class SetAction : public Action {
  public:
    /**
     * \brief Construct as not yet initialized
     *
     * The only member functions that can be used on a constructed but not
     * yet initialized action storage is init or the assignment operator.
     *
     */
    SetAction(void);
    /// Copy constructor
    SetAction(const SetAction& a);
    /// Assignment operator
    SetAction& operator =(const SetAction& a);
    /**
     * \brief Initialize for set variables \a x with decay factor \a d
     *
     * Counts propagation if \a p is true and failure if \a f is true.
     *
     * If the branch merit function \a bm is different from nullptr, the
     * action for each variable is initialized with the merit returned
     * by \a bm.
     *
     */
    GECODE_SET_EXPORT
    SetAction(Home home, const SetVarArgs& x, double d=1.0,
              bool p=true, bool f=true,
              SetBranchMerit bm=nullptr);
    /**
     * \brief Initialize for set variables \a x with decay factor \a d
     *
     * Counts propagation if \a p is true and failure if \a f is true.
     *
     * If the branch merit function \a bm is different from nullptr, the
     * action for each variable is initialized with the merit returned
     * by \a bm.
     *
     * This member function can only be used once and only if the
     * action storage has been constructed with the default constructor.
     *
     */
    GECODE_SET_EXPORT void
    init(Home home, const SetVarArgs& x, double d=1.0,
         bool p=true, bool f=true,
         SetBranchMerit bm=nullptr);
  };

}

#include <gecode/set/branch/action.hpp>

namespace Gecode {

  /**
   * \brief Recording CHB for set variables
   *
   * \ingroup TaskModelSetBranch
   */
  class SetCHB : public CHB {
  public:
    /**
     * \brief Construct as not yet initialized
     *
     * The only member functions that can be used on a constructed but not
     * yet initialized CHB storage is init or the assignment operator.
     *
     */
    SetCHB(void);
    /// Copy constructor
    SetCHB(const SetCHB& chb);
    /// Assignment operator
    SetCHB& operator =(const SetCHB& chb);
   /**
     * \brief Initialize for set variables \a x
     *
     * If the branch merit function \a bm is different from nullptr, the
     * action for each variable is initialized with the merit returned
     * by \a bm.
     *
     */
    GECODE_SET_EXPORT
    SetCHB(Home home, const SetVarArgs& x, SetBranchMerit bm=nullptr);
   /**
     * \brief Initialize for set variables \a x
     *
     * If the branch merit function \a bm is different from nullptr, the
     * action for each variable is initialized with the merit returned
     * by \a bm.
     *
     * This member function can only be used once and only if the
     * action storage has been constructed with the default constructor.
     *
     */
    GECODE_SET_EXPORT void
    init(Home home, const SetVarArgs& x, SetBranchMerit bm=nullptr);
  };

}

#include <gecode/set/branch/chb.hpp>

namespace Gecode {

  /// Function type for printing branching alternatives for set variables
  typedef std::function<void(const Space &home, const Brancher& b,
                             unsigned int a,
                             SetVar x, int i, const int& n,
                             std::ostream& o)>
    SetVarValPrint;

}

namespace Gecode {

  /**
   * \brief Which variable to select for branching
   *
   * \ingroup TaskModelSetBranch
   */
  class SetVarBranch : public VarBranch<SetVar> {
  public:
    /// Which variable selection
    enum Select {
      SEL_NONE = 0,        ///< First unassigned
      SEL_RND,             ///< Random (uniform, for tie breaking)
      SEL_MERIT_MIN,       ///< With least merit
      SEL_MERIT_MAX,       ///< With highest merit
      SEL_DEGREE_MIN,      ///< With smallest degree
      SEL_DEGREE_MAX,      ///< With largest degree
      SEL_AFC_MIN,         ///< With smallest accumulated failure count
      SEL_AFC_MAX,         ///< With largest accumulated failure count
      SEL_ACTION_MIN,      ///< With lowest action
      SEL_ACTION_MAX,      ///< With highest action
      SEL_CHB_MIN,         ///< With lowest CHB Q-score
      SEL_CHB_MAX,         ///< With highest CHB Q-score
      SEL_MIN_MIN,         ///< With smallest minimum unknown element
      SEL_MIN_MAX,         ///< With largest minimum unknown element
      SEL_MAX_MIN,         ///< With smallest maximum unknown element
      SEL_MAX_MAX,         ///< With largest maximum unknown element
      SEL_SIZE_MIN,        ///< With smallest unknown set
      SEL_SIZE_MAX,        ///< With largest unknown set
      SEL_DEGREE_SIZE_MIN, ///< With smallest degree divided by domain size
      SEL_DEGREE_SIZE_MAX, ///< With largest degree divided by domain size
      SEL_AFC_SIZE_MIN,    ///< With smallest accumulated failure count divided by domain size
      SEL_AFC_SIZE_MAX,    ///< With largest accumulated failure count divided by domain size
      SEL_ACTION_SIZE_MIN, ///< With smallest action divided by domain size
      SEL_ACTION_SIZE_MAX, ///< With largest action divided by domain size
      SEL_CHB_SIZE_MIN,    ///< With smallest CHB Q-score divided by domain size
      SEL_CHB_SIZE_MAX     ///< With largest CHB Q-score divided by domain size
    };
  protected:
    /// Which variable to select
    Select s;
  public:
    /// Initialize with strategy SEL_NONE
    SetVarBranch(void);
    /// Initialize with random number generator \a r
    SetVarBranch(Rnd r);
    /// Initialize with selection strategy \a s and tie-break limit function \a t
    SetVarBranch(Select s, BranchTbl t);
    /// Initialize with selection strategy \a s, decay factor \a d, and tie-break limit function \a t
    SetVarBranch(Select s, double d, BranchTbl t);
    /// Initialize with selection strategy \a s, afc \a a, and tie-break limit function \a t
    SetVarBranch(Select s, SetAFC a, BranchTbl t);
    /// Initialize with selection strategy \a s, action \a a, and tie-break limit function \a t
    SetVarBranch(Select s, SetAction a, BranchTbl t);
    /// Initialize with selection strategy \a s, CHB \a c, and tie-break limit function \a t
    SetVarBranch(Select s, SetCHB c, BranchTbl t);
    /// Initialize with selection strategy \a s, branch merit function \a mf, and tie-break limit function \a t
    SetVarBranch(Select s, SetBranchMerit mf, BranchTbl t);
    /// Return selection strategy
    Select select(void) const;
    /// Expand AFC, action, and CHB
    void expand(Home home, const SetVarArgs& x);
  };

  /**
   * \defgroup TaskModelSetBranchVar Selecting set variables
   * \ingroup TaskModelSetBranch
   */
  //@{
  /// Select first unassigned variable
  SetVarBranch SET_VAR_NONE(void);
  /// Select random variable (uniform distribution, for tie breaking)
  SetVarBranch SET_VAR_RND(Rnd r);
  /// Select variable with least merit according to branch merit function \a bm
  SetVarBranch SET_VAR_MERIT_MIN(SetBranchMerit bm, BranchTbl tbl=nullptr);
  /// Select variable with highest merit according to branch merit function \a bm
  SetVarBranch SET_VAR_MERIT_MAX(SetBranchMerit bm, BranchTbl tbl=nullptr);
  /// Select variable with smallest degree
  SetVarBranch SET_VAR_DEGREE_MIN(BranchTbl tbl=nullptr);
  /// Select variable with largest degree
  SetVarBranch SET_VAR_DEGREE_MAX(BranchTbl tbl=nullptr);
  /// Select variable with smallest accumulated failure count with decay factor \a d
  SetVarBranch SET_VAR_AFC_MIN(double d=1.0, BranchTbl tbl=nullptr);
  /// Select variable with smallest accumulated failure count
  SetVarBranch SET_VAR_AFC_MIN(SetAFC a, BranchTbl tbl=nullptr);
  /// Select variable with largest accumulated failure count with decay factor \a d
  SetVarBranch SET_VAR_AFC_MAX(double d=1.0, BranchTbl tbl=nullptr);
  /// Select variable with largest accumulated failure count
  SetVarBranch SET_VAR_AFC_MAX(SetAFC a, BranchTbl tbl=nullptr);
  /// Select variable with lowest action with decay factor \a d
  SetVarBranch SET_VAR_ACTION_MIN(double d=1.0, BranchTbl tbl=nullptr);
  /// Select variable with lowest action
  SetVarBranch SET_VAR_ACTION_MIN(SetAction a, BranchTbl tbl=nullptr);
  /// Select variable with highest action with decay factor \a d
  SetVarBranch SET_VAR_ACTION_MAX(double d=1.0, BranchTbl tbl=nullptr);
  /// Select variable with highest action
  SetVarBranch SET_VAR_ACTION_MAX(SetAction a, BranchTbl tbl=nullptr);
  /// Select variable with lowest CHB Q-score
  SetVarBranch SET_VAR_CHB_MIN(BranchTbl tbl=nullptr);
  /// Select variable with lowest CHB Q-score
  SetVarBranch SET_VAR_CHB_MIN(SetCHB c, BranchTbl tbl=nullptr);
  /// Select variable with highest CHB Q-score
  SetVarBranch SET_VAR_CHB_MAX(BranchTbl tbl=nullptr);
  /// Select variable with highest CHB Q-score
  SetVarBranch SET_VAR_CHB_MAX(SetCHB c, BranchTbl tbl=nullptr);
  /// Select variable with smallest minimum unknown element
  SetVarBranch SET_VAR_MIN_MIN(BranchTbl tbl=nullptr);
  /// Select variable with largest minimum unknown element
  SetVarBranch SET_VAR_MIN_MAX(BranchTbl tbl=nullptr);
  /// Select variable with smallest maximum unknown element
  SetVarBranch SET_VAR_MAX_MIN(BranchTbl tbl=nullptr);
  /// Select variable with largest maximum unknown element
  SetVarBranch SET_VAR_MAX_MAX(BranchTbl tbl=nullptr);
  /// Select variable with smallest unknown set
  SetVarBranch SET_VAR_SIZE_MIN(BranchTbl tbl=nullptr);
  /// Select variable with largest  unknown set
  SetVarBranch SET_VAR_SIZE_MAX(BranchTbl tbl=nullptr);
  /// Select variable with smallest degree divided by domain size
  SetVarBranch SET_VAR_DEGREE_SIZE_MIN(BranchTbl tbl=nullptr);
  /// Select variable with largest degree divided by domain size
  SetVarBranch SET_VAR_DEGREE_SIZE_MAX(BranchTbl tbl=nullptr);
  /// Select variable with smallest accumulated failure count divided by domain size with decay factor \a d
  SetVarBranch SET_VAR_AFC_SIZE_MIN(double d=1.0, BranchTbl tbl=nullptr);
  /// Select variable with smallest accumulated failure count divided by domain size
  SetVarBranch SET_VAR_AFC_SIZE_MIN(SetAFC a, BranchTbl tbl=nullptr);
  /// Select variable with largest accumulated failure count divided by domain size with decay factor \a d
  SetVarBranch SET_VAR_AFC_SIZE_MAX(double d=1.0, BranchTbl tbl=nullptr);
  /// Select variable with largest accumulated failure count divided by domain size
  SetVarBranch SET_VAR_AFC_SIZE_MAX(SetAFC a, BranchTbl tbl=nullptr);
  /// Select variable with smallest action divided by domain size with decay factor \a d
  SetVarBranch SET_VAR_ACTION_SIZE_MIN(double d=1.0, BranchTbl tbl=nullptr);
  /// Select variable with smallest action divided by domain size
  SetVarBranch SET_VAR_ACTION_SIZE_MIN(SetAction a, BranchTbl tbl=nullptr);
  /// Select variable with largest action divided by domain size with decay factor \a d
  SetVarBranch SET_VAR_ACTION_SIZE_MAX(double d=1.0, BranchTbl tbl=nullptr);
  /// Select variable with largest action divided by domain size
  SetVarBranch SET_VAR_ACTION_SIZE_MAX(SetAction a, BranchTbl tbl=nullptr);
  /// Select variable with smallest CHB Q-score divided by domain size
  SetVarBranch SET_VAR_CHB_SIZE_MIN(BranchTbl tbl=nullptr);
  /// Select variable with smallest CHB Q-score divided by domain size
  SetVarBranch SET_VAR_CHB_SIZE_MIN(SetCHB c, BranchTbl tbl=nullptr);
  /// Select variable with largest CHB Q-score divided by domain size
  SetVarBranch SET_VAR_CHB_SIZE_MAX(BranchTbl tbl=nullptr);
  /// Select variable with largest CHB Q-score divided by domain size
  SetVarBranch SET_VAR_CHB_SIZE_MAX(SetCHB c, BranchTbl tbl=nullptr);
  //@}

}

#include <gecode/set/branch/var.hpp>

namespace Gecode {

  /**
   * \brief Which values to select for branching first
   *
   * \ingroup TaskModelSetBranch
   */
  class SetValBranch : public ValBranch<SetVar> {
  public:
    /// Which value selection
    enum Select {
      SEL_MIN_INC,   ///< Include smallest element
      SEL_MIN_EXC,   ///< Exclude smallest element
      SEL_MED_INC,   ///< Include median element (rounding downwards)
      SEL_MED_EXC,   ///< Exclude median element (rounding downwards)
      SEL_MAX_INC,   ///< Include largest element
      SEL_MAX_EXC,   ///< Exclude largest element
      SEL_RND_INC,   ///< Include random element
      SEL_RND_EXC,   ///< Exclude random element
      SEL_VAL_COMMIT ///< Select value according to user-defined functions
    };
  protected:
    /// Which value to select
    Select s;
  public:
    /// Initialize with selection strategy \a s
    SetValBranch(Select s = SEL_MIN_INC);
    /// Initialize with random number generator \a r
    SetValBranch(Select s, Rnd r);
    /// Initialize with value function \a f and commit function \a c
    SetValBranch(SetBranchVal v, SetBranchCommit c);
    /// Return selection strategy
    Select select(void) const;
  };

  /**
   * \defgroup TaskModelSetBranchVal Value selection for set variables
   * \ingroup TaskModelSetBranch
   */
  //@{
  /// Include smallest element
  SetValBranch SET_VAL_MIN_INC(void);
  /// Exclude smallest element
  SetValBranch SET_VAL_MIN_EXC(void);
  /// Include median element (rounding downwards)
  SetValBranch SET_VAL_MED_INC(void);
  /// Exclude median element (rounding downwards)
  SetValBranch SET_VAL_MED_EXC(void);
  /// Include largest element
  SetValBranch SET_VAL_MAX_INC(void);
  /// Exclude largest element
  SetValBranch SET_VAL_MAX_EXC(void);
  /// Include random element
  SetValBranch SET_VAL_RND_INC(Rnd r);
  /// Exclude random element
  SetValBranch SET_VAL_RND_EXC(Rnd r);
  /**
   * \brief Select value as defined by the value function \a v and commit function \a c
   *
   * The default commit function posts the constraint that the value \a n
   * must be included in the set variable \a x for the first alternative,
   * and that \a n must be excluded from \a x otherwise.
   */
  SetValBranch SET_VAL(SetBranchVal v, SetBranchCommit c=nullptr);
  //@}

}

#include <gecode/set/branch/val.hpp>

namespace Gecode {

  /**
   * \brief Which value to select for assignment
   *
   * \ingroup TaskModelSetBranch
   */
  class SetAssign : public ValBranch<SetVar> {
  public:
    /// Which value selection
    enum Select {
      SEL_MIN_INC,   ///< Include smallest element
      SEL_MIN_EXC,   ///< Exclude smallest element
      SEL_MED_INC,   ///< Include median element (rounding downwards)
      SEL_MED_EXC,   ///< Exclude median element (rounding downwards)
      SEL_MAX_INC,   ///< Include largest element
      SEL_MAX_EXC,   ///< Exclude largest element
      SEL_RND_INC,   ///< Include random element
      SEL_RND_EXC,   ///< Exclude random element
      SEL_VAL_COMMIT ///< Select value according to user-defined functions
    };
  protected:
    /// Which value to select
    Select s;
  public:
    /// Initialize with selection strategy \a s
    SetAssign(Select s = SEL_MIN_INC);
    /// Initialize with random number generator \a r
    SetAssign(Select s, Rnd r);
    /// Initialize with value function \a f and commit function \a c
    SetAssign(SetBranchVal v, SetBranchCommit c);
    /// Return selection strategy
    Select select(void) const;
  };

  /**
   * \defgroup TaskModelSetBranchAssign Assigning set variables
   * \ingroup TaskModelSetBranch
   */
  //@{
  /// Include smallest element
  SetAssign SET_ASSIGN_MIN_INC(void);
  /// Exclude smallest element
  SetAssign SET_ASSIGN_MIN_EXC(void);
  /// Include median element (rounding downwards)
  SetAssign SET_ASSIGN_MED_INC(void);
  /// Exclude median element (rounding downwards)
  SetAssign SET_ASSIGN_MED_EXC(void);
  /// Include largest element
  SetAssign SET_ASSIGN_MAX_INC(void);
  /// Exclude largest element
  SetAssign SET_ASSIGN_MAX_EXC(void);
  /// Include random element
  SetAssign SET_ASSIGN_RND_INC(Rnd r);
  /// Exclude random element
  SetAssign SET_ASSIGN_RND_EXC(Rnd r);
  /**
   * \brief Select value as defined by the value function \a v and commit function \a c
   *
   * The default commit function posts the constraint that the value \a n
   * must be included in the set variable \a x.
   */
  SetAssign SET_ASSIGN(SetBranchVal v, SetBranchCommit c=nullptr);
  //@}

}

#include <gecode/set/branch/assign.hpp>

namespace Gecode {

  /**
   * \brief Branch over \a x with variable selection \a vars and value selection \a vals
   *
   * \ingroup TaskModelSetBranch
   */
  GECODE_SET_EXPORT void
  branch(Home home, const SetVarArgs& x,
         SetVarBranch vars, SetValBranch vals,
         SetBranchFilter bf=nullptr,
         SetVarValPrint vvp=nullptr);
  /**
   * \brief Branch over \a x with tie-breaking variable selection \a vars and value selection \a vals
   *
   * \ingroup TaskModelSetBranch
   */
  GECODE_SET_EXPORT void
  branch(Home home, const SetVarArgs& x,
         TieBreak<SetVarBranch> vars, SetValBranch vals,
         SetBranchFilter bf=nullptr,
         SetVarValPrint vvp=nullptr);
  /**
   * \brief Branch over \a x with value selection \a vals
   *
   * \ingroup TaskModelSetBranch
   */
  GECODE_SET_EXPORT void
  branch(Home home, SetVar x, SetValBranch vals,
         SetVarValPrint vvp=nullptr);

  /**
   * \brief Assign all \a x with variable selection \a vars and value selection \a vals
   *
   * \ingroup TaskModelSetBranch
   */
  GECODE_SET_EXPORT void
  assign(Home home, const SetVarArgs& x,
         SetVarBranch vars, SetAssign vals,
         SetBranchFilter bf=nullptr,
         SetVarValPrint vvp=nullptr);
  /**
   * \brief Assign all \a x with tie-breaking variable selection \a vars and value selection \a vals
   *
   * \ingroup TaskModelSetBranch
   */
  GECODE_SET_EXPORT void
  assign(Home home, const SetVarArgs& x,
         TieBreak<SetVarBranch> vars, SetAssign vals,
         SetBranchFilter bf=nullptr,
         SetVarValPrint vvp=nullptr);
  /**
   * \brief Assign \a x with value selection \a vals
   *
   * \ingroup TaskModelSetBranch
   */
  GECODE_SET_EXPORT void
  assign(Home home, SetVar x, SetAssign vals,
         SetVarValPrint vvp=nullptr);

}

namespace Gecode {

  /**
   * \brief Branch over \a x with value selection \a vals
   *
   * \ingroup TaskModelSetBranch
   */
  void
  branch(Home home, const SetVarArgs& x,
         SetValBranch vals,
         SetBranchFilter bf=nullptr,
         SetVarValPrint vvp=nullptr);

  /**
   * \brief Assign all \a x with value selection \a vals
   *
   * \ingroup TaskModelSetBranch
   */
  void
  assign(Home home, const SetVarArgs& x,
         SetAssign vals,
         SetBranchFilter bf=nullptr,
         SetVarValPrint vvp=nullptr);

}

#include <gecode/set/branch.hpp>

// LDSB-related declarations.
namespace Gecode {
  /// Variables in \a x are interchangeable
  GECODE_SET_EXPORT SymmetryHandle VariableSymmetry(const SetVarArgs& x);
  /**
   * \brief Variable sequences in \a x of size \a ss are interchangeable
   *
   * The size of \a x must be a multiple of \a ss.
   */
  GECODE_SET_EXPORT
  SymmetryHandle VariableSequenceSymmetry(const SetVarArgs& x, int ss);
  /**
   * \brief Branch over \a x with variable selection \a vars and value
   * selection \a vals with symmetry breaking
   *
   * \ingroup TaskModelSetBranch
   */
  GECODE_SET_EXPORT void
  branch(Home home, const SetVarArgs& x,
         SetVarBranch vars, SetValBranch vals,
         const Symmetries& syms,
         SetBranchFilter bf=nullptr,
         SetVarValPrint vvp=nullptr);
  /**
   * \brief Branch over \a x with tie-breaking variable selection \a
   * vars and value selection \a vals with symmetry breaking
   *
   * \ingroup TaskModelSetBranch
   */
  GECODE_SET_EXPORT void
  branch(Home home, const SetVarArgs& x,
         TieBreak<SetVarBranch> vars, SetValBranch vals,
         const Symmetries& syms,
         SetBranchFilter bf=nullptr,
         SetVarValPrint vvp=nullptr);
}

namespace Gecode {

  /*
   * \brief Relaxed assignment of variables in \a x from values in \a sx
   *
   * The variables in \a x are assigned values from the assigned variables
   * in the solution \a sx with a relaxation probability \a p. That is,
   * if \f$p=0.1\f$ approximately 10% of the variables in \a x will be
   * assigned a value from \a sx.
   *
   * The random numbers are generated from the generator \a r. At least
   * one variable will not be assigned: in case the relaxation attempt
   * would suggest that all variables should be assigned, a single
   * variable will be selected randomly to remain unassigned.
   *
   * Throws an exception of type Set::ArgumentSizeMismatch, if \a x and
   * \a sx are of different size.
   *
   * Throws an exception of type Set::OutOfLimits, if \a p is not between
   * \a 0.0 and \a 1.0.
   *
   * \ingroup TaskModeSet
   */
  GECODE_SET_EXPORT void
  relax(Home home, const SetVarArgs& x, const SetVarArgs& sx,
        Rnd r, double p);

}

#include <gecode/set/trace/trace-view.hpp>

namespace Gecode {

  /**
   * \defgroup TaskSetTrace Tracing for set variables
   * \ingroup TaskTrace
   */

  /**
   * \brief Trace delta information for set variables
   * \ingroup TaskSetTrace
   */
  class SetTraceDelta {
  protected:
    ///
  public:
    /// Delta for the greatest lower bound
    class Glb
      : public Iter::Ranges::Diff<Set::GlbRanges<Set::SetView>,
                                  Iter::Ranges::RangeList> {
    protected:
      /// Iterator over old glb
      Iter::Ranges::RangeList o;
      /// Iterator over new glb
      Set::GlbRanges<Set::SetView> n;
    public:
      /// \name Constructors and initialization
      //@{
      /// Initialize with old glb and new glb
      Glb(RangeList* o, Set::SetView n);
      //@}
    };
    Glb _glb;
    /// Delta for the least upper bound
    class Lub
      : public Iter::Ranges::Diff<Iter::Ranges::RangeList,
                                  Set::LubRanges<Set::SetView> > {
    protected:
      /// Iterator over old lub
      Iter::Ranges::RangeList o;
      /// Iterator over new lub
      Set::LubRanges<Set::SetView> n;
    public:
      /// \name Constructors and initialization
      //@{
      /// Initialize with old lub \a o and new lub \a n
      Lub(RangeList* o, Set::SetView n);
      //@}
    };
    Lub _lub;
    /// \name Constructor
    //@{
    /// Initialize with old trace view \a o, new view \a n, and delta \a d
    SetTraceDelta(Set::SetTraceView o, Set::SetView n, const Delta& d);
    //@}
    /// \name Access to delta iterators
    //@{
    /// Give access to iterator for delta in greatest lower bound (values that have been included)
    Glb& glb(void);
    /// Give access iterator for delta in least bound (values that have been removed)
    Lub& lub(void);
    //@}
  };

}

#include <gecode/set/trace/delta.hpp>

#include <gecode/set/trace/traits.hpp>

namespace Gecode {

  /**
   * \brief Tracer for set variables
   * \ingroup TaskSetTrace
   */
  typedef ViewTracer<Set::SetView> SetTracer;
  /**
   * \brief Trace recorder for set variables
   * \ingroup TaskSetTrace
   */
  typedef ViewTraceRecorder<Set::SetView> SetTraceRecorder;

  /**
   * \brief Standard set variable tracer
   * \ingroup TaskSetTrace
   */
  class GECODE_SET_EXPORT StdSetTracer : public SetTracer {
  protected:
    /// Output stream to use
    std::ostream& os;
  public:
    /// Initialize with output stream \a os0
    StdSetTracer(std::ostream& os0 = std::cerr);
    /// Print init information
    virtual void init(const Space& home, const SetTraceRecorder& t);
    /// Print prune information
    virtual void prune(const Space& home, const SetTraceRecorder& t,
                       const ViewTraceInfo& vti, int i, SetTraceDelta& d);
    /// Print fixpoint information
    virtual void fix(const Space& home, const SetTraceRecorder& t);
    /// Print failure information
    virtual void fail(const Space& home, const SetTraceRecorder& t);
    /// Print that trace recorder is done
    virtual void done(const Space& home, const SetTraceRecorder& t);
    /// Default tracer (printing to std::cerr)
    static StdSetTracer def;
  };


  /**
   * \brief Create a tracer for set variables
   * \ingroup TaskSetTrace
   */
  GECODE_SET_EXPORT void
  trace(Home home, const SetVarArgs& x,
        TraceFilter tf,
        int te = (TE_INIT | TE_PRUNE | TE_FIX | TE_FAIL | TE_DONE),
        SetTracer& t = StdSetTracer::def);
  /**
   * \brief Create a tracer for set variables
   * \ingroup TaskSetTrace
   */
  void
  trace(Home home, const SetVarArgs& x,
        int te = (TE_INIT | TE_PRUNE | TE_FIX | TE_FAIL | TE_DONE),
        SetTracer& t = StdSetTracer::def);

}

#include <gecode/set/trace.hpp>

#endif

// IFDEF: GECODE_HAS_SET_VARS
// STATISTICS: set-post
