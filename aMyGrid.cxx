#include "aMyGrid.h"

void aMyGridNxMxK::calculateNeighboursInside(const intPOINT &P, const intPOINT &dim) {
  intPOINT p;
  int x = P.x;
  int y = P.y;
  int z = P.z;

  //std::cout << "NEIGHBOURS OF " << x << " " << y << " " << z << " are:\n";

  int count = 0;
  // Iterate through all the z-coordinates inside image bounds
  for (int k = std::max(0, z + m_startZ); k < std::min(dim.z, z + m_startZ + m_sizeZ); ++k) {
    p.z = k;
    // Iterate through all the y-coordinates inside image bounds
    for (int j = std::max(0, y + m_startY); j < std::min(dim.y, y + m_startY + m_sizeY); ++j) {
      p.y = j;
      // Iterate through all the x-coordinates inside image bounds
      for (int i = std::max(0, x + m_startX); i < std::min(dim.x, x + m_startX + m_sizeX); ++i) {
        p.x = i;
        //std::cout << i << " " << j << " " << k << "\n";
        m_neighbours[count++] = p;
      }
    }
  }
} // end aMyGridNxMxK::calculateNeighbours()
