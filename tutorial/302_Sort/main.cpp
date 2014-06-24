#include <igl/readOFF.h>
#include <igl/slice_into.h>
#include <igl/colon.h>
#include <igl/sortrows.h>
#include <igl/barycenter.h>
#include <igl/jet.h>
#include <igl/viewer/Viewer.h>
#include <iostream>

int main(int argc, char *argv[])
{
  using namespace Eigen;
  using namespace std;
  MatrixXd V;
  MatrixXi F;
  igl::readOFF("../shared/decimated-knight.off",V,F);

  // Sort barycenters lexicographically
  MatrixXd BC,sorted_BC;
  igl::barycenter(V,F,BC);
  VectorXi I,J;
  igl::sortrows(BC,true,sorted_BC,I);
  // Get sorted "place" from sorted indices
  J.resize(I.rows());
  // J(I) = 1:numel(I)
  igl::slice_into(igl::colon<int>(0,I.size()-1),I,J);

  // Pseudo-color based on sorted place
  MatrixXd C;
  igl::jet(J,true,C);

  // Plot the mesh with pseudocolors
  igl::Viewer viewer;
  viewer.set_mesh(V, F);
  viewer.set_colors(C);
  viewer.launch();
}