
#include "atkui/framework.h"

using glm::vec3;

class Particles : public atkui::Framework
{
 public:
  Particles() : atkui::Framework(atkui::Orthographic) {
  }
  struct data{
    vec3 position;
    vec3 startZero;
    vec3 color;
    float speed;
  };
  virtual void setup(){
    vel = vec3(1, 1, 0);
    radius = 10.0;
    setPositions(circles);
  }
  virtual void scene(){
    // draw a circles randomly
    for (int i = 0; i < 150; i++){
      setColor(circles[i].color);
      drawSphere(circles[i].position, radius);
      circles[i].position = circles[i].position + circles[i].speed * vel * dt(); 
      if (circles[i].position.b > width() || circles[i].position.g > height()){
        circles[i].position = circles[i].startZero;
      }       
    }

  }
  void setPositions(data positions[]){
    for (int i = 0; i < 150; i++){
      int x = rand()%500;
      int y = rand()%500;
      int z = 0;
      if (i < 50){
        z = -100;
      }else if (i < 100){
        z = 100;
      }else if (i < 150){
        z = 300;
      }
      positions[i].speed = rand()%40;
      positions[i].position = vec3(x, y, z);
      positions[i].color = vec3(x%10*0.05, y%10*0.05, z%10*0.05);
      if (x > y){
        positions[i].startZero = vec3(x-y, 0, z);
      }else if (y > x){
        positions[i].startZero = vec3(0, y-x, z);
      }else{
        positions[i].startZero = vec3(0, 0, z);
      }
    }
  }
  data circles[150];
  vec3 vel;
  float radius;

};

int main(int argc, char** argv) {
  Particles viewer;
  viewer.run();
  return 0;
}

