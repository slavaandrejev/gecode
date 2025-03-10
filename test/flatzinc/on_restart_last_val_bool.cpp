/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Jip J. Dekker <jip.dekker@monash.edu>
 *
 *  Copyright:
 *     Jip J. Dekker, 2023
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

#include "test/flatzinc.hh"

namespace Test { namespace FlatZinc {

  namespace {
    /// Helper class to create and register tests
    class Create {
    public:

      /// Perform creation and registration
      Create(void) {
        (void) new FlatZincTest("on_restart::last_val_bool",
R"FZN(
predicate gecode_on_restart_status(var int: s);
predicate gecode_on_restart_last_val_bool(var bool: input,var bool: out);
var -1..4: x:: output_var;
var bool: y:: output_var;
var 0..4: X_INTRODUCED_1_ ::var_is_introduced :: is_defined_var;
var 1..5: X_INTRODUCED_3_ ::var_is_introduced ;
var bool: X_INTRODUCED_4_ ::var_is_introduced :: is_defined_var;
var bool: X_INTRODUCED_5_ ::var_is_introduced ;
var bool: X_INTRODUCED_6_ ::var_is_introduced :: is_defined_var;
var bool: X_INTRODUCED_14_ ::var_is_introduced :: is_defined_var;
array [1..1] of var int: X_INTRODUCED_2_ ::var_is_introduced  = [x];
constraint int_abs(x,X_INTRODUCED_1_):: ctx_pos:: defines_var(X_INTRODUCED_1_);
constraint gecode_on_restart_status(X_INTRODUCED_3_);
constraint gecode_on_restart_last_val_bool(y,X_INTRODUCED_5_);
constraint bool_clause([],[y,X_INTRODUCED_4_]);
constraint bool_clause([X_INTRODUCED_4_,X_INTRODUCED_14_],[]);
constraint bool_not(X_INTRODUCED_5_,X_INTRODUCED_6_):: defines_var(X_INTRODUCED_6_);
constraint int_eq_reif(X_INTRODUCED_3_,1,X_INTRODUCED_4_):: defines_var(X_INTRODUCED_4_);
constraint bool_eq_reif(y,X_INTRODUCED_6_,X_INTRODUCED_14_):: defines_var(X_INTRODUCED_14_);
solve :: int_search(X_INTRODUCED_2_,input_order,indomain_min,complete) maximize X_INTRODUCED_1_;
)FZN",
R"OUT(x = -1;
y = false;
----------
x = 2;
y = true;
----------
x = 3;
y = false;
----------
x = 4;
y = true;
----------
==========
)OUT", true, {"--restart", "constant", "--restart-base", "100"});
      }
    };

    Create c;
  }

}}

// STATISTICS: test-flatzinc
