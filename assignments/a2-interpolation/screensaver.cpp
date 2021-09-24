#include "atkui/framework.h"
#include <list>
#include <iterator>
using namespace glm;
using namespace std;
class Screensaver : public atkui::Framework {
  struct CP {
    vec3 points[4];
    vec3 color;
  };
 public:
  Screensaver() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    for (int i = 0; i < 4; i++){
      randomCP.points[i] = vec3(rand()%500, rand()%500, rand()%500);
      randomCP2.points[i] = vec3(rand()%500, rand()%500, rand()%500);
      randomCP.color = vec3(rand()%10*0.05, rand()%10*0.05, rand()%10*0.05);
      randomCP2.color = vec3(rand()%10*0.05, rand()%10*0.05, rand()%10*0.05);
    }

  }

  void scene() {
    doLERP(randomCP);
    doLERP(randomCP2);
    float speed = 2.0f;
    float stop = 0;


    i  = fmod(elapsedTime(), 2.0f);
    if (i > 1.98f){
      for (int i = 0; i < 4; i++){
        randomCP.points[i] = randomCP2.points[i];
        randomCP2.points[i] = vec3(rand()%500, rand()%500, rand()%500);
        randomCP.color = vec3(rand()%10*0.05, rand()%10*0.05, rand()%10*0.05);
        randomCP2.color = vec3(rand()%10*0.05, rand()%10*0.05, rand()%10*0.05);
      }
    }
    intermediate.points[0] =  randomCP.points[0] * (1-(float)i/speed) + randomCP2.points[0] * (float)i/speed;
    intermediate.points[1] =  randomCP.points[1] * (1-(float)i/speed) + randomCP2.points[1] * (float)i/speed;
    intermediate.points[2] =  randomCP.points[2] * (1-(float)i/speed) + randomCP2.points[2] * (float)i/speed;
    intermediate.points[3] =  randomCP.points[3] * (1-(float)i/speed) + randomCP2.points[3] * (float)i/speed;
    intermediate.color = randomCP.color;
    
    if (curves.size() < 75){
      curves.push_front(intermediate);
    }else{
      curves.pop_back();
      curves.push_front(intermediate);
    }
    list<CP>::iterator it;
    for (it = curves.begin(); it != curves.end(); ++it) {
      doLERP(*it);
    }

  }



  void doLERP(struct CP arr){
    vec3 temp = arr.points[0];
      for (int i = 0; i < 100; i++){
        float t = (float)i;
        vec3 b10 = LERP(arr.points[0], arr.points[1], t);
        vec3 b11 = LERP(arr.points[1], arr.points[2], t);
        vec3 b12 = LERP(arr.points[2], arr.points[3], t);

        vec3 b20 = LERP(b10, b11, t);
        vec3 b21 = LERP(b11, b12, t);

        vec3 b30 = LERP(b20, b21, t);
        setColor(arr.color);
        drawLine(temp, b30);
        temp = b30;
      }
  }
  vec3 LERP(vec3 b0, vec3 b1, float t){
    return b0*(1-(t/100))+b1*(t/100);
  }

  float i = 0;
  list <CP> curves;
  CP randomCP;
  CP randomCP2;
  CP intermediate;
};

int main(int argc, char** argv) {
  Screensaver viewer;
  viewer.run();
}

