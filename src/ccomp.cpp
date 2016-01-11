#include "ccomp.h"
#include <math.h>



pixroot* pixfind(pixroot* p)
{
  if (p->parent != p) 
    p->parent = pixfind(p->parent);
  return p->parent;
}

void pixunion(pixroot* a, pixroot* b)
{
  // find parts
  pixroot* aroot = pixfind(a);
  pixroot* broot = pixfind(b);

  if (aroot == broot) return;

  if (aroot->rank < broot->rank) {
    aroot->parent = broot;
  }
  else if (aroot->rank > broot->rank) {
    broot->parent = aroot;
  } else {
    broot->parent = aroot;
    aroot->rank += 1;
  }
}

inline 
int idx(int i, int j, int cols) 
{
  return cols * i  + j;
}

#ifdef __cplusplus
extern "C" {
#endif

int compute_connected_components(float* disp, int drows, int dcols, 
				 int* out_labels, int lrows, int lcols,
				 float d_thresh)
{
  int num_pixels = drows * dcols;
  pixroot* comps = new pixroot[num_pixels];
  // initialize the components
  for (int i = 0; i < drows; ++i) {
    for (int j = 0; j < dcols; ++j) {
      comps[idx(i,j,dcols)].val = idx(i,j,dcols);
    }
  }
  
  // initialize the out_label matrix
  std::fill(out_labels, out_labels+num_pixels, -1);

  // construct the connectivity matrix
  for (int i = 0; i < drows; ++i) {
    for (int j = 0; j < dcols; ++j) {
      // skip invalid pixels
      if (disp[idx(i,j,dcols)] == 0.0) continue;

      // iterate over the neighborhood
      for (int k = -1; k < 2; ++k) {
	for (int l = -1; l < 2; ++l) {
	  int ik = i+k;
	  int jl = j+l;
	  if (ik < 0 || ik >= drows) continue;
	  if (jl < 0 || jl >= dcols) continue;
	  if (ik == i && jl == j) continue;
	  if (fabs(disp[idx(i,j,dcols)] - disp[idx(ik,jl,dcols)]) < d_thresh) {
	    pixunion(&comps[idx(i,j,dcols)], &comps[idx(ik,jl,dcols)]);
	  }
	}
      }
    }
  }
  // relabel roots
  int k = 0;
  for (int i = 0; i < num_pixels; ++i) {
    if (comps[i].is_root()) {
      comps[i].rank = k++;
    }
  }
  // generate labels
  for (int i = 0; i < num_pixels; ++i) {
    out_labels[i] = pixfind(&comps[i])->rank;
  }
  // clean up memory
  delete [] comps;
  return k;
}

#ifdef __cplusplus
}
#endif
