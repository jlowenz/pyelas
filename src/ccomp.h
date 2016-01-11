#pragma once
#ifndef __CCOMP__H
#define __CCOMP__H

#include <cstring>
#include <cstdlib>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <iterator>

// struct pix {
//   int i, j;

//   pix(int i_, int j_) : i(i_), j(j_) {}
//   pix(const pix& p) : i(p.i), j(p.j) {}  

//   bool operator<(const pix& p) { 
//     if (i < p.i) 
//       return true;
//     else if (i == p.i)
//       return j < p.j;
//     else 
//       return false;
//   }
//   bool operator==(const pix& p) {
//     return i == p.i && j == p.j;
//   }
// };

template<typename T>
struct ufroot
{
  ufroot<T>* parent;
  int rank;
  T val;

  ufroot() : val(T()) {
    parent = this;
    rank = 0;
  }
  ufroot(T val_) : val(val_) {
    parent = this;
    rank = 0;
  }

  inline bool is_root() const
  {
    return parent == this;
  }
};

typedef ufroot<int> pixroot;

#ifdef __cplusplus
extern "C" {
#endif


int compute_connected_components(float* disp, int drows, int dcols, 
				 int* out_labels, int lrows, int lcols,
				 float d_thresh);

#ifdef __cplusplus
}
#endif

#endif
