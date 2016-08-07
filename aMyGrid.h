#ifndef _A_MY_GRID_H
#define _A_MY_GRID_H

/* inludes */
#include <aImage.h>
#include <aDebug.h>
#include <aPoint.h>
#include <aGrid.h>
#include <vector>

class aMyGridNxMxK: virtual public aGrid4 {
  public:
    //! Default constructor creates 3x3x3 grid.
    aMyGridNxMxK() {
      Init(3,3,3);
    };

    //! Virtual destructor.
    virtual ~aMyGridNxMxK() {
    };

    //! Precalulate neighbourhoods of the point (x,y) for image of size dim
    void calculateNeighboursInside(const intPOINT &P, const intPOINT &dim);

    //! Set the grid size to NxMxK.
    virtual void setGridSize(int N, int M, int K) {
      Init(N,M,K);
    };

  protected:
    //! The grid size in x direction.
    int m_sizeX;
    //! The grid size in y direction.
    int m_sizeY;
    //! The grid size in z direction.
    int m_sizeZ;
    //! Central simmetry grid point in x direction.
    int m_startX;
    //! Central simmetry grid point in y direction.
    int m_startY;
    //! Central simmetry grid point in z direction.
    int m_startZ;

    void Init(int n, int m, int k) {
      aGrid4::m_gridSize = m * n * k;
      aGrid4::m_neighbours.resize(m_gridSize);
      aGrid4::m_addresses.resize(m_gridSize);
      m_sizeX  = n;
      m_sizeY  = m;
      m_sizeZ  = k;
      m_startX = (-1) * m_sizeX / 2;
      m_startY = (-1) * m_sizeY / 2;
      m_startZ = (-1) * m_sizeZ / 2;
    };

}; // end class aMyGridNxMxK definition

#endif //
