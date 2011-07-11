/* $Id$ */
# ifndef CPPAD_MEMORY_LEAK_INCLUDED
# define CPPAD_MEMORY_LEAK_INCLUDED

/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-11 Bradley M. Bell

CppAD is distributed under multiple licenses. This distribution is under
the terms of the 
                    Common Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */
/*
$begin memory_leak$$
$spell
	hpp
	bool
	inuse
$$

$section Memory Leak Detection$$
$index memory_leak$$
$index leak, memory$$
$index check, memory leak$$

$head Syntax$$
$icode%flag% = %memory_leak()%$$

$head flag$$
The return value $icode flag$$ has prototype
$codei%
	bool %flag%
%$$

$head Purpose$$
This routine check for leaks in the $cref/omp_alloc/$$ memory allocation
routines. The deprecated $cref/TrackNewDel/$$ routines are also checked.

$head NDEBUG$$
If $code NDEBUG$$ is defined,
this routine returns true.
Otherwise it returns true unless one of the conditions below occurs.

$head inuse$$
When this routine is called, it is assumed that no memory
should be $cref/inuse/$$ for any thread.
If it is, a message is printed and this routine returns false.

$head available$$
This routine calls $cref/free_available/$$ for all the threads
and then checks that no memory is left $cref/available/$$ for any thread;
i.e., it all has been returned to the system.
If there is memory still available for this thread,
this routine returns false. 

$head TRACK_COUNT$$
if $cref/TrackCount/TrackNewDel/TrackCount/$$ returns a non-zero value,
this routine returns false.

$head Error Message$$
If this routine returns false, it prints a message
to standard output describing the condition before returning false.

$head OpenMP$$
This routine cannot be used $cref/in_parallel/$$
execution mode.

$end
*/

# include <iostream>
# include <cppad/local/define.hpp>
# include <cppad/omp_alloc.hpp>
# include <cppad/track_new_del.hpp>

CPPAD_BEGIN_NAMESPACE
/*!
\file memory_leak.hpp
File that implements a memory check at end of a CppAD program
*/

/*!
Function that check both the old memory allocator defined in track_new_del.hpp
and the new allocator \c omp_alloc for misuse that results in memory leaks:

\return
returns \c true, if no error is detected and \c false otherwise.

\par
If an error is detected, diagnostic information is printed to standard
output.
*/
inline bool memory_leak(void)
{
	CPPAD_ASSERT_KNOWN(
		! omp_alloc::in_parallel(),
		"attempt to use memory_leak in parallel execution mode."
	);
	bool leak = false;
	using std::cout;
	using std::endl;

	using CppAD::omp_alloc;
	size_t thread;
	for(thread = 0; thread < CPPAD_MAX_NUM_THREADS; thread++)
	{
		// check that no memory is currently in use for this thread
		size_t num_bytes = omp_alloc::inuse(thread);
		if( num_bytes != 0 )
		{	leak = true;
			cout << "omp_alloc::inuse(thread) = " << num_bytes << endl;
		}
		// dump the available memory pool being held for this thread
		omp_alloc::free_available(thread);
		num_bytes = omp_alloc::available(thread);
		if( num_bytes != 0 )
		{	leak = true;
			cout << "omp_alloc::available(thread) = " << num_bytes << endl;
		}
	}

	if( CPPAD_TRACK_COUNT() != 0 )
	{	leak = true;
		CppAD::TrackElement::Print();
	}

	return leak;
}

CPPAD_END_NAMESPACE
# endif
