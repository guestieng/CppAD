# ifndef CPPAD_LOCAL_SPARSE_BINARY_OP_HPP
# define CPPAD_LOCAL_SPARSE_BINARY_OP_HPP
/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-19 Bradley M. Bell

CppAD is distributed under the terms of the
             Eclipse Public License Version 2.0.

This Source Code may also be made available under the following
Secondary License when the conditions for such availability set forth
in the Eclipse Public License, Version 2.0 are satisfied:
      GNU General Public License, Version 2.0 or later.
---------------------------------------------------------------------------- */

namespace CppAD { namespace local { // BEGIN_CPPAD_LOCAL_NAMESPACE
/*!
\file sparse_binary_op.hpp
Forward and reverse mode sparsity patterns for binary operators.
*/


/*!
Forward mode Jacobian sparsity pattern for all binary operators.

The C++ source code corresponding to a binary operation has the form
\verbatim
    z = fun(x, y)
\endverbatim
where fun is a C++ binary function and both x and y are variables,
or it has the form
\verbatim
    z = x op y
\endverbatim
where op is a C++ binary unary operator and both x and y are variables.

\tparam Vector_set
is the type used for vectors of sets. It can be either
sparse_pack or sparse_list.

\param i_z
variable index corresponding to the result for this operation;
i.e., z.

\param arg
 arg[0]
variable index corresponding to the left operand for this operator;
i.e., x.
\n
\n arg[1]
variable index corresponding to the right operand for this operator;
i.e., y.

\param sparsity
\b Input:
The set with index arg[0] in sparsity
is the sparsity bit pattern for x.
This identifies which of the independent variables the variable x
depends on.
\n
\n
\b Input:
The set with index arg[1] in sparsity
is the sparsity bit pattern for y.
This identifies which of the independent variables the variable y
depends on.
\n
\n
\b Output:
The set with index i_z in sparsity
is the sparsity bit pattern for z.
This identifies which of the independent variables the variable z
depends on.

\par Checked Assertions:
\li arg[0] < i_z
\li arg[1] < i_z
*/

template <class Vector_set>
void forward_sparse_jacobian_binary_op(
    size_t            i_z           ,
    const addr_t*     arg           ,
    Vector_set&       sparsity      )
{
    // check assumptions
    CPPAD_ASSERT_UNKNOWN( size_t(arg[0]) < i_z );
    CPPAD_ASSERT_UNKNOWN( size_t(arg[1]) < i_z );

    sparsity.binary_union(i_z, size_t(arg[0]), size_t(arg[1]), sparsity);

    return;
}

/*!
Reverse mode Jacobian sparsity pattern for all binary operators.

The C++ source code corresponding to a unary operation has the form
\verbatim
    z = fun(x, y)
\endverbatim
where fun is a C++ unary function and x and y are variables,
or it has the form
\verbatim
    z = x op y
\endverbatim
where op is a C++ bianry operator and x and y are variables.

This routine is given the sparsity patterns
for a function G(z, y, x, ... )
and it uses them to compute the sparsity patterns for
\verbatim
    H( y, x, w , u , ... ) = G[ z(x,y) , y , x , w , u , ... ]
\endverbatim

\tparam Vector_set
is the type used for vectors of sets. It can be either
sparse_pack or sparse_list.

\param i_z
variable index corresponding to the result for this operation;
i.e., z.

\param arg
 arg[0]
variable index corresponding to the left operand for this operator;
i.e., x.

\n
\n arg[1]
variable index corresponding to the right operand for this operator;
i.e., y.

\param sparsity
The set with index i_z in sparsity
is the sparsity pattern for z corresponding ot the function G.
\n
\n
The set with index arg[0] in sparsity
is the sparsity pattern for x.
On input, it corresponds to the function G,
and on output it corresponds to H.
\n
\n
The set with index arg[1] in sparsity
is the sparsity pattern for y.
On input, it corresponds to the function G,
and on output it corresponds to H.
\n
\n

\par Checked Assertions:
\li arg[0] < i_z
\li arg[1] < i_z
*/
template <class Vector_set>
void reverse_sparse_jacobian_binary_op(
    size_t              i_z           ,
    const addr_t*       arg           ,
    Vector_set&         sparsity      )
{
    // check assumptions
    CPPAD_ASSERT_UNKNOWN( size_t(arg[0]) < i_z );
    CPPAD_ASSERT_UNKNOWN( size_t(arg[1]) < i_z );

    sparsity.binary_union( size_t(arg[0]), size_t(arg[0]), i_z, sparsity);
    sparsity.binary_union( size_t(arg[1]), size_t(arg[1]), i_z, sparsity);

    return;
}
// ---------------------------------------------------------------------------
/*!
Reverse mode Hessian sparsity pattern for add and subtract operators.

The C++ source code corresponding to a unary operation has the form
\verbatim
    z = x op y
\endverbatim
where op is + or - and x, y are variables.

\copydetails CppAD::local::reverse_sparse_hessian_binary_op
*/
template <class Vector_set>
void reverse_sparse_hessian_addsub_op(
    size_t               i_z                ,
    const addr_t*        arg                ,
    bool*                jac_reverse        ,
    const Vector_set&    for_jac_sparsity   ,
    Vector_set&          rev_hes_sparsity   )
{
    // check assumptions
    CPPAD_ASSERT_UNKNOWN( size_t(arg[0]) < i_z );
    CPPAD_ASSERT_UNKNOWN( size_t(arg[1]) < i_z );

    // check for no effect
    if( ! jac_reverse[i_z] )
        return;

    // propagate hessian sparsity from i_z to arg[0] and arg[1]
    rev_hes_sparsity.binary_union(
        size_t(arg[0]), size_t(arg[0]), i_z, rev_hes_sparsity
    );
    rev_hes_sparsity.binary_union(
        size_t(arg[1]), size_t(arg[1]), i_z, rev_hes_sparsity
    );

    jac_reverse[arg[0]] = true;
    jac_reverse[arg[1]] = true;

    return;
}

/*!
Reverse mode Hessian sparsity pattern for multiplication operator.

The C++ source code corresponding to a unary operation has the form
\verbatim
    z = x * y
\endverbatim
where x and y are variables.

\copydetails CppAD::local::reverse_sparse_hessian_binary_op
*/
template <class Vector_set>
void reverse_sparse_hessian_mul_op(
    size_t               i_z                ,
    const addr_t*        arg                ,
    bool*                jac_reverse        ,
    const Vector_set&    for_jac_sparsity   ,
    Vector_set&          rev_hes_sparsity   )
{
    // check assumptions
    CPPAD_ASSERT_UNKNOWN( size_t(arg[0]) < i_z );
    CPPAD_ASSERT_UNKNOWN( size_t(arg[1]) < i_z );

    // check for no effect
    if( ! jac_reverse[i_z] )
        return;

    // progagate hessian sparsity from i_z to arg[0] and arg[1]
    rev_hes_sparsity.binary_union(
        size_t(arg[0]), size_t(arg[0]), i_z, rev_hes_sparsity
    );
    rev_hes_sparsity.binary_union(
        size_t(arg[1]), size_t(arg[1]), i_z, rev_hes_sparsity
    );

    // new hessian sparsity terms between i_z and arg[0], arg[1]
    rev_hes_sparsity.binary_union(
        size_t(arg[0]), size_t(arg[0]), size_t(arg[1]), for_jac_sparsity
    );
    rev_hes_sparsity.binary_union(
        size_t(arg[1]), size_t(arg[1]), size_t(arg[0]), for_jac_sparsity
    );

    jac_reverse[arg[0]] = true;
    jac_reverse[arg[1]] = true;
    return;
}

/*!
Reverse mode Hessian sparsity pattern for division operator.

The C++ source code corresponding to a unary operation has the form
\verbatim
    z = x / y
\endverbatim
where x and y are variables.

\copydetails CppAD::local::reverse_sparse_hessian_binary_op
*/
template <class Vector_set>
void reverse_sparse_hessian_div_op(
    size_t               i_z                ,
    const addr_t*        arg                ,
    bool*                jac_reverse        ,
    const Vector_set&    for_jac_sparsity   ,
    Vector_set&          rev_hes_sparsity   )
{
    // check assumptions
    CPPAD_ASSERT_UNKNOWN( size_t(arg[0]) < i_z );
    CPPAD_ASSERT_UNKNOWN( size_t(arg[1]) < i_z );

    // check for no effect
    if( ! jac_reverse[i_z] )
        return;

    // propagate hessian sparsity from i_z to arg[0] and arg[1]
    rev_hes_sparsity.binary_union(
        size_t(arg[0]), size_t(arg[0]), i_z, rev_hes_sparsity
    );
    rev_hes_sparsity.binary_union(
        size_t(arg[1]), size_t(arg[1]), i_z, rev_hes_sparsity
    );

    // new hessian sparsity terms between i_z and arg[0], arg[1]
    rev_hes_sparsity.binary_union(
            size_t(arg[0]), size_t(arg[0]), size_t(arg[1]), for_jac_sparsity
    );
    rev_hes_sparsity.binary_union(
            size_t(arg[1]), size_t(arg[1]), size_t(arg[0]), for_jac_sparsity
    );
    rev_hes_sparsity.binary_union(
            size_t(arg[1]), size_t(arg[1]), size_t(arg[1]), for_jac_sparsity
    );

    jac_reverse[arg[0]] = true;
    jac_reverse[arg[1]] = true;
    return;
}

/*!
Reverse mode Hessian sparsity pattern for power function.

The C++ source code corresponding to a unary operation has the form
\verbatim
    z = pow(x, y)
\endverbatim
where x and y are variables.

\copydetails CppAD::local::reverse_sparse_hessian_binary_op
*/
template <class Vector_set>
void reverse_sparse_hessian_pow_op(
    size_t               i_z                ,
    const addr_t*        arg                ,
    bool*                jac_reverse        ,
    const Vector_set&    for_jac_sparsity   ,
    Vector_set&          rev_hes_sparsity   )
{
    // check assumptions
    CPPAD_ASSERT_UNKNOWN( size_t(arg[0]) < i_z );
    CPPAD_ASSERT_UNKNOWN( size_t(arg[1]) < i_z );

    // check for no effect
    if( ! jac_reverse[i_z] )
        return;

    // propigate hessian sparsity from i_z to arg[0] and arg[1]
    rev_hes_sparsity.binary_union(
        size_t(arg[0]), size_t(arg[0]), i_z, rev_hes_sparsity
    );
    rev_hes_sparsity.binary_union(
        size_t(arg[1]), size_t(arg[1]), i_z, rev_hes_sparsity
    );

    // new hessian sparsity terms between i_z and arg[0], arg[1]
    rev_hes_sparsity.binary_union(
        size_t(arg[0]), size_t(arg[0]), size_t(arg[0]), for_jac_sparsity
    );
    rev_hes_sparsity.binary_union(
        size_t(arg[0]), size_t(arg[0]), size_t(arg[1]), for_jac_sparsity
    );
    rev_hes_sparsity.binary_union(
        size_t(arg[1]), size_t(arg[1]), size_t(arg[0]), for_jac_sparsity
    );
    rev_hes_sparsity.binary_union(
        size_t(arg[1]), size_t(arg[1]), size_t(arg[1]), for_jac_sparsity
    );

    // I cannot think of a case where this is necessary, but it including
    // it makes it like the other cases.
    jac_reverse[arg[0]] = true;
    jac_reverse[arg[1]] = true;
    return;
}
// ---------------------------------------------------------------------------
/*
$begin for_hes_sparse_nl_binary_op$$
$spell
    hes
    div
    op
    np
    numvar
    Jacobian
    arg
    mul
$$

$section Forward Hessian Sparsity for Nonlinear Binary Operators$$

$head for_hes_sparse_mul_op$$

$subhead Syntax$$
$codei%local::for_hes_sparse_mul_op(%i_v%, %np1%, %numvar%, %for_sparsity%)%$$

$subhead Prototype$$
$srcfile%include/cppad/local/sparse_binary_op.hpp%
    0%// BEGIN_for_hes_sparse_mul_op%// END_for_hes_sparse_mul_op%1
%$$

$head for_hes_sparse_div_op$$

$subhead Syntax$$
$codei%local::for_hes_sparse_div_op(%i_v%, %np1%, %numvar%, %for_sparsity%)%$$

$subhead Prototype$$
$srcfile%include/cppad/local/sparse_binary_op.hpp%
    0%// BEGIN_for_hes_sparse_div_op%// END_for_hes_sparse_div_op%1
%$$

$head for_hes_sparse_pow_op$$

$subhead Syntax$$
$codei%local::for_hes_sparse_pow_op(%i_v%, %np1%, %numvar%, %for_sparsity%)%$$

$subhead Prototype$$
$srcfile%include/cppad/local/sparse_binary_op.hpp%
    0%// BEGIN_for_hes_sparse_pow_op%// END_for_hes_sparse_pow_op%1
%$$

$head C++ Source$$
The C++ source code corresponding to this operation is
$codei%
        %w% = %v0% * %v1%
        %w% = %v0% / %v1%
        %w% = pow(%v0% , %v1%)
%$$

$head np1$$
This is the number of independent variables plus one;
i.e. size of $icode x$$ plus one.

$head numvar$$
This is the total number of variables in the tape.

$head arg$$
is the index of the argument vector for the nonlinear binary operation; i.e.,
$icode%arg%[0]%$$, $icode%arg%[1]%$$ are the left and right operands; i.e.,
corresponding to $icode v0$$, $icode v1$$.

$head for_sparsity$$
We have the conditions $icode%np1% = %for_sparsity%.end()%$$
and $icode%for_sparsity%.n_set() = %np1% + %numvar%$$.

$subhead Jacobian Sparsity$$
For $icode%i%= 1, ..., %numvar%$$,
the $th np1+i$$ row of $icode for_sparsity$$ is the Jacobian sparsity
for the $th i$$ variable.
These values do not change.

$subhead Input Hessian Sparsity$$
For $icode%i%=1, ..., %n%$$,
the $th i$$ row of $icode for_sparsity$$ is the Hessian sparsity
before including the function $latex w(x)$$.

$subhead Output Hessian Sparsity$$
For $icode%i%=1, ..., %n%$$,
the $th i$$ row of $icode for_sparsity$$ is the Hessian sparsity
after including the function $latex w(x)$$.

$end
*/
// BEGIN_for_hes_sparse_mul_op
template <class Vector_set>
void for_hes_sparse_mul_op(
    size_t              np1           ,
    size_t              numvar        ,
    const addr_t*       arg           ,
    Vector_set&         for_sparsity  )
// END_for_hes_sparse_mul_op
{   //
    CPPAD_ASSERT_UNKNOWN( for_sparsity.end() == np1 );
    CPPAD_ASSERT_UNKNOWN( for_sparsity.n_set() == np1 + numvar );
    //
    size_t i_v0 = size_t(arg[0]);
    size_t i_v1 = size_t(arg[1]);
    CPPAD_ASSERT_UNKNOWN( i_v0 < numvar );
    CPPAD_ASSERT_UNKNOWN( i_v1 < numvar );

    // --------------------------------------------------
    // set of independent variables that v0 depends on
    typename Vector_set::const_iterator itr_0(for_sparsity, i_v0 + np1);

    // loop over independent variables non-zero partial for v0
    size_t i_x = *itr_0;
    while( i_x < np1 )
    {   // N(i_x) = N(i_x) union J(v1)
        for_sparsity.binary_union(i_x, i_x, i_v1 + np1, for_sparsity);
        i_x = *(++itr_0);
    }
    // --------------------------------------------------
    // set of independent variables that v1 depends on
    typename Vector_set::const_iterator itr_1(for_sparsity, i_v1 + np1);

    // loop over independent variables with non-zero partial for v1
    i_x = *itr_1;
    while( i_x < np1 )
    {   // N(i_x) = N(i_x) union J(v0)
        for_sparsity.binary_union(i_x, i_x, i_v0 + np1, for_sparsity);
        i_x = *(++itr_1);
    }
    return;
}
// BEGIN_for_hes_sparse_div_op
template <class Vector_set>
void for_hes_sparse_div_op(
    size_t              np1           ,
    size_t              numvar        ,
    const addr_t*       arg           ,
    Vector_set&         for_sparsity  )
// END_for_hes_sparse_div_op
{   //
    CPPAD_ASSERT_UNKNOWN( for_sparsity.end() == np1 );
    CPPAD_ASSERT_UNKNOWN( for_sparsity.n_set() == np1 + numvar );
    //
    size_t i_v0 = size_t(arg[0]);
    size_t i_v1 = size_t(arg[1]);
    CPPAD_ASSERT_UNKNOWN( i_v0 < numvar );
    CPPAD_ASSERT_UNKNOWN( i_v1 < numvar );

    // --------------------------------------------------
    // set of independent variables that v0 depends on
    typename Vector_set::const_iterator itr_0(for_sparsity, i_v0 + np1);

    // loop over independent variables non-zero partial for v0
    size_t i_x = *itr_0;
    while( i_x < np1 )
    {   // N(i_x) = N(i_x) union J(v1)
        for_sparsity.binary_union(i_x, i_x, i_v1 + np1, for_sparsity);
        i_x = *(++itr_0);
    }
    // --------------------------------------------------
    // set of independent variables that v1 depends on
    typename Vector_set::const_iterator itr_1(for_sparsity, i_v1 + np1);

    // loop over independent variables with non-zero partial for v1
    i_x = *itr_1;
    while( i_x < np1 )
    {   // N(i_x) = N(i_x) union J(v0)
        for_sparsity.binary_union(i_x, i_x, i_v0 + np1, for_sparsity);
        // N(i_x) = N(i_x) union J(v1)
        for_sparsity.binary_union(i_x, i_x, i_v1 + np1, for_sparsity);
        i_x = *(++itr_1);
    }
    return;
}
// BEGIN_for_hes_sparse_pow_op
template <class Vector_set>
void for_hes_sparse_pow_op(
    size_t              np1           ,
    size_t              numvar        ,
    const addr_t*       arg           ,
    Vector_set&         for_sparsity  )
// END_for_hes_sparse_pow_op
{   //
    CPPAD_ASSERT_UNKNOWN( for_sparsity.end() == np1 );
    CPPAD_ASSERT_UNKNOWN( for_sparsity.n_set() == np1 + numvar );
    //
    size_t i_v0 = size_t(arg[0]);
    size_t i_v1 = size_t(arg[1]);
    CPPAD_ASSERT_UNKNOWN( i_v0 < numvar );
    CPPAD_ASSERT_UNKNOWN( i_v1 < numvar );

    // --------------------------------------------------
    // set of independent variables that v0 depends on
    typename Vector_set::const_iterator itr_0(for_sparsity, i_v0 + np1);

    // loop over independent variables non-zero partial for v0
    size_t i_x = *itr_0;
    while( i_x < np1 )
    {   // N(i_x) = N(i_x) union J(v0)
        for_sparsity.binary_union(i_x, i_x, i_v0 + np1, for_sparsity);
        // N(i_x) = N(i_x) union J(v1)
        for_sparsity.binary_union(i_x, i_x, i_v1 + np1, for_sparsity);
        i_x = *(++itr_0);
    }
    // --------------------------------------------------
    // set of independent variables that v1 depends on
    typename Vector_set::const_iterator itr_1(for_sparsity, i_v1 + np1);

    // loop over independent variables with non-zero partial for v1
    i_x = *itr_1;
    while( i_x < np1 )
    {   // N(i_x) = N(i_x) union J(v0)
        for_sparsity.binary_union(i_x, i_x, i_v0 + np1, for_sparsity);
        // N(i_x) = N(i_x) union J(v1)
        for_sparsity.binary_union(i_x, i_x, i_v1 + np1, for_sparsity);
        i_x = *(++itr_1);
    }
    return;
}
// ---------------------------------------------------------------------------
} } // END_CPPAD_LOCAL_NAMESPACE
# endif
