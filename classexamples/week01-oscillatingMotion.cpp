
#include "atkui/framework.h"

using glm::vec3;

class Example : public atkui::Framework {
 public:
  Example() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
      theta = 0.0f;
      thetaRate = 0.5f;

  }

  virtual void scene() {
    //compute the next postion
    theta += thetaRate * dt();
    float px = 0.5 * width();
    float py = 200.0f + sin(theta) + 0.5 * height();
    //draw sphere
    setColor(vec3(1, 0, 0));
    drawSphere(vec3(px, py, 0), 100);
  }
  private:
    float theta;
    float thetaRate;
};

int main(int argc, char** argv) {
  Example example;
  example.run();