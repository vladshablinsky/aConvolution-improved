#include "aMyConvolution.h"
#include "aMyGrid.h"
#include <aDebug.h>

template<class T, class U>
void aMyConvolution<T,U>::make(aImage<T> &image, aImage<T> &kernel, aImage<T> &out) {
  m_isOK = true;
  int nColImage, nRowImage, nBandImage;
  int nColKernel, nRowKernel, nBandKernel;
  U Sum;
  T res;

  // create neighbour coordinates map
  aMyGridNxMxK *pGrid = new aMyGridNxMxK;
  if (pGrid == 0) {
    m_isOK      = false;
    m_lastError = "Cannot create a custom grid.";
    return;
  }

  std::cout << "Grid created\n";

  // Initialization
  nColImage  = image.getSizeX();
  nRowImage  = image.getSizeY();
  nBandImage = image.getSizeZ();

  nColKernel  = kernel.getSizeX();
  nRowKernel  = kernel.getSizeY();
  nBandKernel = kernel.getSizeZ();

  // resize out if necessary
  if (nColImage  != out.getSizeX() || nRowImage  != out.getSizeY() || nBandImage != out.getSizeZ()) {
    out.resize(nColImage, nRowImage, nBandImage);
  }

  pGrid->setGridSize(nColKernel, nRowKernel, nBandKernel);

  // 0 means to use the weight of kernel as the norm value
  if (m_normValue == 0.0) {
    T nS = 0;
    T *p2 = kernel.getPtr();
    for (int i = 0; i < kernel.getSize(); i++) {
      nS += *(p2 + i);
    }

    if (nS == (T)0) {
      m_normValue = (U)1.0;
    } else {
      m_normValue = (U)1/(U)nS;
    }
  }

  // calculate convolution
  // convj = Sum fi*gi
  intPOINT curPoint; // current point
  intPOINT curNeighbour; // neighbour point
  intPOINT imageDim(nColImage, nRowImage, nBandImage); // size of input image

  for (int k = 0; k < nBandImage; k++) {
    curPoint.z = k;
    for (int j = 0; j < nRowImage; j++) {
      curPoint.y = j;
      for (int i = 0; i < nColImage; i++) {
        curPoint.x = i;

        pGrid->calculateNeighboursInside(curPoint, imageDim);

        // calculate sum for (i,j,k) point
        Sum       = 0.0;
        int count = 0;

        int startZ = nBandKernel - 1 + std::min(k - nBandKernel / 2, 0);
        int endZ = std::max(0, (nBandKernel + 1) / 2 + k - nBandImage);

        for (int kk = startZ; kk >= endZ; kk--) {
          int startY = nRowKernel - 1 + std::min(j - nRowKernel / 2, 0);
          int endY = std::max(0, (nRowKernel + 1) / 2 + j - nRowImage);

          for (int jj = startY; jj >= endY; jj--) {
            int startX = nColKernel - 1 + std::min(i - nColKernel / 2, 0);
            int endX = std::max(0, (nColKernel + 1) / 2 + i - nColImage);

            for (int ii = startX; ii >= endX; ii--) {
              curNeighbour = pGrid->getPoint(count);
              count++;
              Sum += image.elem(curNeighbour.x, curNeighbour.y, curNeighbour.z) * kernel.elem(ii,jj,kk);
            } // end for ii
          }
        }

        // Normalise the sum, depending on the image type T.
        res = normalise(Sum);
        if (m_isLimited) {
          if (res > m_maxLimit) {
            //apply maximal limit
            out.elem(i,j,k) = m_maxLimit;
          } else {
            if (res < m_minLimit) {
              // apply minimal limit
              out.elem(i,j,k) = m_minLimit;
            }
          }
        }
        // Assitgn output image value (i,j,k)
        out.elem(i,j,k) = (T)res;

      } // end for i
    } // end for j
  } // end for k

  // Clean memory
  pGrid->release();
}//end aConvolution<T,U>::makeConvolution()

// Normalisation with round value
template<class T, class U>
T aMyConvolution<T,U>::normalise(U sum) {
  T res;
  if ( m_normValue !=1 ) {
    res = (T)(sum * m_normValue) + 0.5;
  } else {
    res = (T)sum;
  }
  return res;
}

// Normalisation for float type
template<>
float aMyConvolution<float,float>::normalise(float sum) {
  float res;
  if ( m_normValue !=1 ) {
    res = (float)(sum * m_normValue);
  } else {
    res = (float)sum;
  }
  return res;
}

// Normalisation for double type
template<>
double aMyConvolution<double,double>::normalise(double sum) {
  double res;
  if (m_normValue != 1) {
    res = (double)(sum * m_normValue);
  } else {
    res = (double)sum;
  }
  return res;
}

template class aMyConvolution<char,float>;
template class aMyConvolution<unsigned char,float>;
template class aMyConvolution<short,float>;
template class aMyConvolution<unsigned short,float>;
template class aMyConvolution<int,float>;
template class aMyConvolution<unsigned int,float>;
template class aMyConvolution<float,float>;

template class aMyConvolution<char,double>;
template class aMyConvolution<unsigned char,double>;
template class aMyConvolution<short,double>;
template class aMyConvolution<unsigned short,double>;
template class aMyConvolution<int,double>;
template class aMyConvolution<unsigned int,double>;
template class aMyConvolution<double,double>;
