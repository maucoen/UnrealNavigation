/****************************************************************************
 *
 *   Copyright (c) Jet Propulsion Laboratory/Caltech - Gene Merewether. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file poly.hpp
 *
 * @author Gene Merewether
 */

#ifndef __POLY_HPP
#define __POLY_HPP

#include <stdio.h>
#include <stdint.h>

#include "polytraj_var_size.h"

namespace polytraj
{

class Poly
{
public:
	Poly(uint32_t n_coeff, POLYTRAJ_FLOAT *coeffs); // constructor calculates derivatives up to max order
	Poly(const Poly &source); // override copy constructor because using raw pointer
	Poly &operator=(const Poly &source); // override assignment operator because using raw pointer
	~Poly();

	// all polynomials start at time 0; Traj class handles the offset

	double EvalPoly(double time, int order); // eval at time and derivative order

	void print(int order);

private:
	uint32_t n_coeff_;        // number of coefficients in each polynomial
	POLYTRAJ_FLOAT *der_coeffs_; // polynomial coefficients and derivatives

	void InitDers();     // initialize derivatives
};

} // namespace PolyTraj

#endif // __POLY_HPP
