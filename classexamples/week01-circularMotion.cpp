#include "atkui/framework.h"

using glm::vec3;

class Example : public atkui::Framework {
 public:
  Example() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
      theta = 0.0f;
      thetaRate = 0.2f;
      r = 200.0;
      currentPos = vec3(r*cos(theta), r*sin(theta), 0);

  }

  virtual void scene() {
    //compute the next postion
    theta += thetaRate * dt();
    float px = r * cos(theta) + 0.5 * width();
    float py = r * sin(theta) + 0.5 * height();
    //draw sphere
    setColor(vec3(1, 0, 0));
    drawSphere(vec3(px, py, 0), 100);
  }
  private:
    vec3 currentPos;
    float theta;
    float thetaRate;
    float r;
};

int main(int argc, char** argv) {
  Example example;
  example.run();
}