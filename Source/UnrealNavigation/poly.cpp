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
 * @file poly.cpp
 *
 * @author Gene Merewether
 */

#include <assert.h>
#include "poly.hpp"

namespace polytraj
{

Poly::Poly(uint32_t n_coeff, POLYTRAJ_FLOAT *coeffs)
{
	assert(coeffs);
	n_coeff_ = n_coeff;
	// TODO - mereweth@jpl.nasa.gov - watch for performance hits with this dynamic allocation
	der_coeffs_ = new POLYTRAJ_FLOAT[n_coeff_ * n_coeff_](); // initialize to zeros using value initialization

	for (int i = 0; i < n_coeff_; i++) {
		der_coeffs_[i] = coeffs[i]; // copy coefficients; the 0th order derivative
	}

	InitDers();
}

Poly::Poly(const Poly &source) // override copy constructor because using raw pointer
{
	n_coeff_ = source.n_coeff_;

	if (source.der_coeffs_) { // deep copy
		der_coeffs_ = new POLYTRAJ_FLOAT[n_coeff_ * n_coeff_](); // initialize to zeros using value initialization

		for (int i = 0; i < n_coeff_ * n_coeff_; i++) {
			der_coeffs_[i] = source.der_coeffs_[i]; // copy coefficients
		}

	} else {
		der_coeffs_ = 0;
	}
}

Poly &Poly::operator=(const Poly &source) // override assignment operator because using raw pointer
{
	if (this == &source) { // self-assigment
		return *this;
	}

	delete[] der_coeffs_; // delete memory this Poly is holding

	n_coeff_ = source.n_coeff_;

	if (source.der_coeffs_) { // deep copy
		der_coeffs_ = new POLYTRAJ_FLOAT[n_coeff_ * n_coeff_](); // initialize to zeros using value initialization

		for (int i = 0; i < n_coeff_ * n_coeff_; i++) {
			der_coeffs_[i] = source.der_coeffs_[i]; // copy coefficients
		}

	} else {
		der_coeffs_ = 0;
	}

	return *this;
}

Poly::~Poly()
{
	if (der_coeffs_) {
		delete[] der_coeffs_;
	}
}

void Poly::InitDers()
{
	for (int i = 1; i < n_coeff_; i++) { // row; which derivative
		for (int j = i; j < n_coeff_; j++) { // column; which coefficient - everything below diagonal is 0
			int power = n_coeff_ - j;
			// take element from above left, multiply by power
			der_coeffs_[i * n_coeff_ + j] = der_coeffs_[(i - 1) * n_coeff_ + (j - 1)] * power;
		}
	}
}

double Poly::EvalPoly(double time, int order)
{
	double val = 0;
	double t_pow = 1;

	// furthest-right column is 0th power of t
	// top row is 0th order derivative in der_coeffs_
	for (int j = n_coeff_ - 1; j >= order; j--) {
		val += t_pow * (double) der_coeffs_[order * n_coeff_ + j];
		t_pow *= time; // add additional power of t for next loop
	}

	return val;
}

void Poly::print(int order)
{
	// replace with ifdef QURT
	/*for (int i = 0; (i <= order) && (i < n_coeff_); i++) {
		printf("\nDerivative of order %d:\n", i);

		for (int j = i; j < n_coeff_; j++) {
			printf("%.2f * t^%d + ", der_coeffs_[i * n_coeff_ + j], n_coeff_ - j - 1);
		}
		}*/
}

} // namespace polytraj
