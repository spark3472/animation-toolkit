#include "atkui/framework.h"
#include "spline.h"
#include "interpolator_hermite.h"
#include <iostream>

using namespace glm;

class Unique : public atkui::Framework
{
   struct CP {
    vec3 points[5];
    vec3 color;
  };
 public:
  Unique() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }
   virtual void setup()
   {
      
   }
  virtual void scene()
  {
   keys.push_back(vec3(rand()%500, rand()%500, rand()%500));
   keys.push_back(vec3(rand()%500, rand()%500, rand()%500));
   keys.push_back(vec3(rand()%500, rand()%500, rand()%500));
   keys.push_back(vec3(rand()%500, rand()%500, rand()%500));
   keys.push_back(vec3(rand()%500, rand()%500, rand()%500));
   
   setColor(vec3(rand()%10*0.05, rand()%10*0.05, rand()%10*0.05));

   InterpolatorHermite hermite;
   hermite.computeControlPoints(keys);
   vec3 temp = hermite.getControlPoint(0);
   for (int i = 0; i < 100; i++){
      float t = (float)i;
      drawLine(temp, hermite.interpolate(0, t/100));
      temp = hermite.interpolate(0, t/100);
   }
   for (int i = 0; i < 100; i++){
      float t = (float)i;
      drawLine(temp, hermite.interpolate(0, t/100));
      temp = hermite.interpolate(1, t/100);
   }
   for (int i = 0; i < 100; i++){
      float t = (float)i;
      drawLine(temp, hermite.interpolate(0, t/100));
      temp = hermite.interpolate(2, t/100);
   }
   for (int i = 0; i < 100; i++){
      float t = (float)i;
      drawLine(temp, hermite.interpolate(0, t/100));
      temp = hermite.interpolate(3, t/100);
   }
    
   keys.pop_back();
   keys.pop_back();
   keys.pop_back();
   keys.pop_back();
   keys.pop_back();
  }

   std::vector<vec3> keys;

};

int main(int argc, char **argv) {
  Unique viewer;
  viewer.run();
}