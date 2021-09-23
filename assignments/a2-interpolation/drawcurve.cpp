#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class DrawCubic : public atkui::Framework
{
 public:
  DrawCubic() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  virtual void scene()
  {
    setColor(vec3(0,0,1));
    drawSphere(B0, 10);
    drawSphere(B3, 10);

    setColor(vec3(1,1,0));
    drawSphere(B1, 10);
    drawSphere(B2, 10);

    if (bern > 0){
      vec3 temp = B0;
      for (int i = 0; i < 100; i++){
        float t = (float)i;
        setColor(vec3(0,0,1));
        vec3 position = B0*(1-t/100)*(1-t/100)*(1-t/100) + 3*t/100*(1-t/100)*(1-t/100)*B1 + 3*t/100*t/100*(1-t/100)*B2 + t/100*t/100*t/100*B3; 
        drawLine(temp, position);
        temp = position;
      } 
    }

    if (castel > 0){
      vec3 temp = B0;
      for (int i = 0; i < 100; i++){
        float t = (float)i;
        vec3 b10 = LERP(B0, B1, t);
        vec3 b11 = LERP(B1, B2, t);
        vec3 b12 = LERP(B2, B3, t);

        vec3 b20 = LERP(b10, b11, t);
        vec3 b21 = LERP(b11, b12, t);

        vec3 b30 = LERP(b20, b21, t);

        setColor(vec3(1,0,0));
        drawLine(temp, b30);
        temp = b30;

      }

    }

  }

  vec3 LERP(vec3 b0, vec3 b1, float t){
    return b0*(1-(t/100))+b1*(t/100);
  }

  void keyUp(int key, int mod) {
    if (key == GLFW_KEY_1) {
      bern++;
    }
    else if (key == GLFW_KEY_2) {
      castel++;
    }
  }

  private:
  int bern = 0;
  int castel = 0;
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
};

int main(int argc, char **argv) {
  DrawCubic viewer;
  viewer.run();
}
