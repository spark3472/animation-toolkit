#include "atkui/framework.h"
using namespace glm;

class Screensaver : public atkui::Framework {
 public:
  Screensaver() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    for (int i = 0; i < 4; i++){
      randomCP[i] = vec3(rand()%500, rand()%500, rand()%500);
      randomCP2[i] = vec3(rand()%500, rand()%500, rand()%500);
    }

  }

  void scene() {
    doLERP(randomCP);
    doLERP(randomCP2);
  }

  void doLERP(vec3 arr[]){
    vec3 temp = arr[0];
      for (int i = 0; i < 100; i++){
        float t = (float)i;
        vec3 b10 = LERP(arr[0], arr[1], t);
        vec3 b11 = LERP(arr[1], arr[2], t);
        vec3 b12 = LERP(arr[2], arr[3], t);

        vec3 b20 = LERP(b10, b11, t);
        vec3 b21 = LERP(b11, b12, t);

        vec3 b30 = LERP(b20, b21, t);

        setColor(vec3(1, 1, 0));
        drawLine(temp, b30);
        temp = b30;
      }
  }
  vec3 LERP(vec3 b0, vec3 b1, float t){
    return b0*(1-(t/100))+b1*(t/100);
  }

  vec3 randomCP[4];
  vec3 randomCP2[4];
};

int main(int argc, char** argv) {
  Screensaver viewer;
  viewer.run();
}

