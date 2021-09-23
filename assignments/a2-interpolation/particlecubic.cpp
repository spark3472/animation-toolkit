#include "atkui/framework.h"
using namespace glm;

class ParticleCubic : public atkui::Framework {
 public:
  ParticleCubic() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
  }

  void scene() {
    vec3 temp = B0;
    for (int i = 0; i < 100; i++){
      float t = (float)i;
      setColor(vec3(0,0,1));
      position = B0*(1-t/100)*(1-t/100)*(1-t/100) + 3*t/100*(1-t/100)*(1-t/100)*B1 + 3*t/100*t/100*(1-t/100)*B2 + t/100*t/100*t/100*B3; 
      drawLine(temp, position);
      temp = position;
    }
    setColor(vec3(1, 1, 0));
    float t = fmod(elapsedTime(), 5.0f);
    vec3 move = B0*(1-t/5)*(1-t/5)*(1-t/5) + 3*t/5*(1-t/5)*(1-t/5)*B1 + 3*t/5*t/5*(1-t/5)*B2 + t/5*t/5*t/5*B3;
    drawSphere(move, 10);

  }

  private:
  vec3 position;
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
};

int main(int argc, char** argv) {
  ParticleCubic viewer;
  viewer.run();
}
