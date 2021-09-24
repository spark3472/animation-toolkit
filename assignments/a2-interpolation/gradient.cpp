#include <iostream>
#include "atkui/framework.h"
using namespace glm;
struct cube{
    vec3 position;
    int x;
    int y;
    int z;
    vec3 color;
    vec3 colorx0;
    vec3 colorx1;
  };
class Gradient : public atkui::Framework {
 public:
  Gradient() : atkui::Framework(atkui::Orthographic) {
  }

  void scene() {
    setWindowSize(500, 500);
    //northeast starting position
    int x = 25;
    int y = 25;
    int count = 0;
    for (int i = 0; i < 10; i++){
      for (int j = 0; j < 10;j++){
        cubes[count].x = x + j*50;
        cubes[count].y = y  + i*50;
        cubes[count].z = 0;
        cubes[count].position = vec3(x+j*50, y+i*50, 0);
        count++;
      }
    }
    for (int i = 0; i < 100; i++){
      cubes[i].colorx0 = colorNW * (1-(float)cubes[i].x/width()) + colorNE * (float)cubes[i].x/width();
      cubes[i].colorx1 = colorSW * (1-(float)cubes[i].x/width()) + colorSE * (float)cubes[i].x/width();
      cubes[i].color = cubes[i].colorx1 * (1-(float)cubes[i].y/height()) + cubes[i].colorx0 * (float)cubes[i].y/height();
    }
    setColor(vec3(1, 0, 0));
    for (int i = 0; i < 100; i++){
      setColor(cubes[i].color);
      drawCube(cubes[i].position, vec3(50));
    }
  }
  
  cube cubes[100];
  vec3 colorNW = vec3(1, 1, 0);
  vec3 colorNE = vec3(0, 1, 1);
  vec3 colorSW = vec3(1, 0, 0);
  vec3 colorSE = vec3(1, 0, 1);
};

int main(int argc, char **argv) {
  Gradient viewer;
  viewer.run();
}
