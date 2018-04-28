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
 * @file traj.hpp
 *
 * @author Gene Merewether
 */

#ifndef __TRAJ_HPP
#define __TRAJ_HPP

#include "poly.hpp"
#include <vector>
#include <stdio.h>
#include <stdint.h>

#include "polytraj_var_size.h"

namespace polytraj
{

class Traj
{
public:
  Traj(uint32_t n_seg, double *t_transition, uint32_t n_coeff, POLYTRAJ_FLOAT *coeffs); // constructor from arrays
  ~Traj() {};

  // eval trajectory at time and derivative order - evaluates current polynomial
  double EvalTraj(double time, int order);

  void print(int order);

  int CheckContinuity(double cont_eps, double equal_eps);

  // get entire trajectory back same as was constructed; c array

  // get active trajectory segment; returns a Poly

  int GetSeg(); // get index of active trajectory segment

  void ForceReset();

  // overwrite current trajectory beginning at specified segment; from array

private:
  uint32_t n_coeff_; // number of coefficients for each polynomial segment in this trajectory (fixed)

  uint32_t seg_idx_;
  std::vector<Poly> polys_;
  // time at which to transition to the next segment
  std::vector<double> t_transition_;

  // private function to (alloc and) insert trajectory from uorb message or array
};

} // namespace polytraj
#endif // __TRAJ_HPP
