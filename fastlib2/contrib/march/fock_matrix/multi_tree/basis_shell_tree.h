/*
 *  basis_shell_tree.h
 *  
 *
 *  Created by William March on 8/19/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BASIS_SHELL_TREE_H
#define BASIS_SHELL_TREE_H

//#include "contrib/march/fock_matrix/fock_impl/basis_shell.h"
#include "contrib/march/fock_matrix/fock_impl/eri.h"
#include "fastlib/fastlib.h"

class BasisShellTree {
  
private:
  
  // children
  BasisShellTree* left_;
  BasisShellTree* right_;
  
  // size of contents
  index_t num_shells_;
  index_t num_functions_;
  
  // the start index in the master list of shells
  // these will be permuted to be in order - like the columns of the matrix
  index_t start_index_;
  
  // bounds
  // first three dimensions are spatial, next two are exponents and momenta
  // IMPORTANT: can't do this, will screw up distance bounds
  DHrectBound<2> bound_;
  
  //// stats ////
  // maybe make these DRanges or something?
  
  DRange exponents_;
  double min_exponent_;
  double max_exponent_;

  DRange momenta_;
  
  double min_normalization_;
  double max_normalization_;
  
  bool single_momentum_;
  
public:
  
  void Init(index_t begin, index_t count) { 
    
    DEBUG_ASSERT(count > 0);
    DEBUG_ASSERT(begin >= 0);
    
    // assume ranges are set
    single_momentum_ = (momenta_.width() == 0.0);
    start_index_ = begin;
    num_shells_ = count;
    
  } // Init()
  
  index_t count() {
    return num_shells_;
  }
  
  index_t begin() {
    return start_index_;
  }
  
  bool single_momentum() const {
    return single_momentum_;
  }
  
  DHrectBound<2>& bound() {
    return bound_;
  }
  
  DRange& exponents() {
    return exponents_;
  }
  
  DRange& momenta() {
    return momenta_;
  }
  
  bool is_leaf() {
    return (left_ == NULL);
  }
  
  void set_children(BasisShellTree* left, BasisShellTree* right) {
   
    left_ = left;
    right_ = right;
    
  }
  
  void Print() {
   
    printf("Node: Start: %d, Count: %d\n", start_index_, num_shells_);
    printf("Spatial dimensions: {(%g, %g), (%g, %g), (%g, %g)\n}",
           bound_.get(0).lo, bound_.get(0).hi,
           bound_.get(1).lo, bound_.get(1).hi,
           bound_.get(2).lo, bound_.get(2).hi);
    printf("Exponents: (%g, %g)\n", exponents_.lo, exponents_.hi);
    printf("Momenta: (%g, %g)\n", momenta_.lo, momenta_.hi);
    printf("\n");
    if (left_) {
      left_->Print();
      right_->Print();
    }
    
  }
  
}; // BasisShellTree

#endif
