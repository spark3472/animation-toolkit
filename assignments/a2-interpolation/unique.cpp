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
class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
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
    i  = fmod(elapsedTime(), 1.0f);
    if (i > 0.981f){
      randnum1 = rand()%100;
      randnum2 = rand()%100;
      randnum3 = rand()%100;
    }
    setColor(cubes[randnum1].color);
    drawCube(cubes[randnum1].position, vec3(50));
    setColor(cubes[randnum2].color);
    drawCube(cubes[randnum2].position, vec3(50));
    setColor(cubes[randnum3].color);
    drawCube(cubes[randnum3].position, vec3(50));
    setColor(vec3(1, 0, 0));
  }
  
  cube cubes[100];
  float i;
  int randnum1;
  int randnum2;
  int randnum3;
  vec3 colorNW = vec3(1, 0, 0);
  vec3 colorNE = vec3(0, 0, 1);
  vec3 colorSW = vec3(0);
  vec3 colorSE = vec3(1);
};
int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
}