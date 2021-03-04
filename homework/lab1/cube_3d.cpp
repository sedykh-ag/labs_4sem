#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("t1");

  double lc = 1e-2;
  gmsh::model::geo::addPoint(0, 0, 0, lc, 1);
  gmsh::model::geo::addPoint(.1, 0, 0, lc, 2);
  gmsh::model::geo::addPoint(0, .1, 0, lc, 4);
  gmsh::model::geo::addPoint(.1, .1, 0, lc, 3);

  gmsh::model::geo::addPoint(0, 0, .1, lc, 5);
  gmsh::model::geo::addPoint(.1, 0, .1, lc, 6);
  gmsh::model::geo::addPoint(0, .1, .1, lc, 8);
  gmsh::model::geo::addPoint(.1, .1, .1, lc, 7);

  gmsh::model::geo::addLine(1, 2, 1);
  gmsh::model::geo::addLine(2, 3, 2);
  gmsh::model::geo::addLine(3, 4, 3);
  gmsh::model::geo::addLine(4, 1, 4);

  gmsh::model::geo::addLine(5, 6, 5);
  gmsh::model::geo::addLine(6, 7, 6);
  gmsh::model::geo::addLine(7, 8, 7);
  gmsh::model::geo::addLine(8, 5, 8);

  gmsh::model::geo::addLine(2, 6, 9);
  gmsh::model::geo::addLine(3, 7, 10);
  gmsh::model::geo::addLine(4, 8, 11);
  gmsh::model::geo::addLine(1, 5, 12);

  gmsh::model::geo::addCurveLoop({1,2,3,4},1);
  gmsh::model::geo::addCurveLoop({5,6,7,8},2);
  gmsh::model::geo::addCurveLoop({9,6,-10,-2},3);
  gmsh::model::geo::addCurveLoop({1,9,-5,-12},4);
  gmsh::model::geo::addCurveLoop({4,12,-8,-11},5);
  gmsh::model::geo::addCurveLoop({3,11,-7,-10},6);


  for (int i=1; i<=6; i++)
    gmsh::model::geo::addPlaneSurface({i}, i);


  gmsh::model::geo::addSurfaceLoop({1,2,3,4,5,6}, 1);
  gmsh::model::geo::addVolume({1});

  gmsh::model::geo::synchronize();
  gmsh::model::mesh::generate(3);

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}

