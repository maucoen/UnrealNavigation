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
 * @file traj.cpp
 *
 * @author Gene Merewether
 */

#include <assert.h>
#include <stdint.h>
#include <math.h>

#include "traj.hpp"

namespace polytraj
{

Traj::Traj(uint32_t n_seg, double *t_transition, uint32_t n_coeff, POLYTRAJ_FLOAT *coeffs)
{
  assert(t_transition);
  assert(coeffs);

  n_coeff_ = n_coeff;

  t_transition_.reserve(n_seg);
  polys_.reserve(n_seg);

  for (int i = 0; i < n_seg; i++) {
    t_transition_.push_back(t_transition[i]);
    polys_.push_back(Poly(n_coeff_, &coeffs[i * n_coeff_]));
    // check continuity of trajectories with Poly CanJoin method?
  }

  seg_idx_ = 0;
}

double Traj::EvalTraj(double time, int order)
{
  if (time <= 0) { // "null init" = hover at beginning position of first polynomial
    return polys_.front().EvalPoly(0.0, order);
  }

  // check if seg_idx_ needs to (and can) be advanced
  while ((seg_idx_ < polys_.size()) && (time > t_transition_[seg_idx_])) {
    seg_idx_++;
  }

  // seg_idx_ will be equal to polys_.size() when done
  if (seg_idx_ == polys_.size()) { // "null terminate" = hover at end position of final polynomial
    return polys_[seg_idx_ - 1].EvalPoly(t_transition_[seg_idx_ - 1] - t_transition_[seg_idx_ - 2], order);
  }

  if (seg_idx_ != 0) {
    return polys_[seg_idx_].EvalPoly(time - t_transition_[seg_idx_ - 1], order);

  } else {
    // the first segment starts at t=0
    return polys_[seg_idx_].EvalPoly(time, order);
  }
}

int Traj::CheckContinuity(double eps, double equal_eps)
{
  // number of free derivatives = trunc((order+1) / 2)
  int n_der = (int) (n_coeff_ / 2.0);
  // for each segment
  for (int i = 0; i < polys_.size() - 1; i++) {
    // for each free derivative
    for (int j = 0; j < n_der; j++) {
      if (fabs(polys_[i + 1].EvalPoly(t_transition_[i] + eps, j) -
               polys_[i].EvalPoly(t_transition_[i] - eps, j)) > equal_eps) {
          return i;
      }
    }
  }

  return -1;
}

int Traj::GetSeg()
{
  return seg_idx_;
}

void Traj::ForceReset()
{
  seg_idx_ = 0;
}

void Traj::print(int order)
{
  // replace with ifdef QURT
  /*printf("----------------------------------------\n");
  printf("Traj with %lu segments; at segment %d\n\n", (unsigned long) polys_.size(), seg_idx_);
  printf("Transition times: \n");

  for (int i = 0; i < t_transition_.size(); i++) {
    printf("%.2f, ", t_transition_[i]);
  }

  printf("\nPolynomial segments:\n");

  for (int i = 0; i < polys_.size(); i++) {
    printf("\n========================================\n\nSegment %d:\n", i);
    polys_[i].print(order);
  }

  printf("\n");*/
}

} // namespace polytraj
