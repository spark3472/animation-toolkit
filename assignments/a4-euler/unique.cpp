#include "atkui/framework.h"
#include "atkmath/constants.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"
#include "atkmath/test_utils.h"
#include <iostream>

using atkmath::Matrix3;
using atkmath::Vector3;
using atkmath::Deg2Rad;
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
class Unique : public atkui::Framework
{
  public:
    Unique() : atkui::Framework(atkui::Orthographic) {
    }
   void pushEulerRotation(const Vector3& euler) {
      Vector3 anglesRad = euler * Deg2Rad;
      rotate(anglesRad[0], vec3(1, 0, 0));
      rotate(anglesRad[1], vec3(0, 1, 0));
      rotate(anglesRad[2], vec3(0, 0, 1));
      }

    virtual void setup() {
       Vector3 XYZ = rot.toEulerAnglesXYZ();
       theta = 0.0f;
       thetaRate = 20.0f;
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
      
    }
    virtual void scene() {
      theta += thetaRate * dt();
      
      for (int i = 0; i < 100; i++){
         setColor(cubes[i].color);
         push();
         translate(vec3(-3.5, 3.5, 0));
         euler = Vector3(theta, theta, theta);
         pushEulerRotation(euler);
         drawCube(cubes[i].position, vec3(25));
         pop();
      }
      
    }
   float theta;
   float thetaRate;
   Vector3 euler = Vector3();
   Matrix3 rot;
   vec3 cube = vec3(width()/2, height()/2, 0);
   struct cube cubes[100];
   vec3 colorNW = vec3(1, 1, 0);
   vec3 colorNE = vec3(0, 1, 1);
   vec3 colorSW = vec3(1, 0, 0);
   vec3 colorSE = vec3(1, 0, 1);
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
  return 0;
}

