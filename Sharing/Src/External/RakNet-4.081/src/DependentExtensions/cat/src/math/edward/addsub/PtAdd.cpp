// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

/*

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#include <cat/math/BigTwistedEdwards.hpp>
using namespace cat;

#if defined(EXTENDED_T)
# undef PT_FN
# define PT_FN PtEAdd /* Version that does produce the T coord */
#else
# define EXTENDED_T
# include "PtAdd.cpp"
# undef PT_FN
# define PT_FN PtAdd /* Version that does not produce the T coord */
#endif

/*
	The group laws used for point addition/doubling are the best in the
	literature at this time, requiring no branches just a straight shot
	through field operations.

	I have tweaked the order of operations to improve cache locality.

	On 32-bit platforms CPU time is broken down as:
	[PtAdd] time spent in misc operations: 1882
	[PtAdd] time spent in multiplies: 6240
*/

#include <cat/time/Clock.hpp>
#include <iostream>
using namespace std;

// Extended Twisted Edwards Unified Addition Formula (works when both inputs are the same) in 8M 1D 9a
void BigTwistedEdwards::PT_FN(const Leg *in_a, const Leg *in_b, Leg *out)
{
    // A = (Y1 - X1) * (Y2 - X2)
    MrSubtract(in_a+YOFF, in_a+XOFF, C);
    MrSubtract(in_b+YOFF, in_b+XOFF, D);
	MrMultiply(C, D, A);

    // B = (Y1 + X1) * (Y2 + X2)
    MrAdd(in_a+YOFF, in_a+XOFF, G);
    MrAdd(in_b+YOFF, in_b+XOFF, H);
	MrMultiply(G, H, B);

    // C = 2 * d * T1 * T2 (can remove multiplication by d if inputs are known to be different)
    MrMultiply(in_a+TOFF, in_b+TOFF, C);
	MrMultiplyX(C, curve_d * 2, C);

    // D = 2 * Z1 * Z2
    MrMultiply(in_a+ZOFF, in_b+ZOFF, D);
	MrDouble(D, D);

    // E = B - A, F = D - C, G = D + C, H = B + A
    MrSubtract(B, A, E);
    MrSubtract(D, C, F);
    MrAdd(D, C, G);
    MrAdd(B, A, H);

    // X3 = E * F, Y3 = G * H, T3 = E * H, Z3 = F * G
    MrMultiply(E, F, out+XOFF);
    MrMultiply(G, H, out+YOFF);
#if defined(EXTENDED_T)
    MrMultiply(E, H, out+TOFF);
#endif
    MrMultiply(F, G, out+ZOFF);
}

#undef EXTENDED_T
