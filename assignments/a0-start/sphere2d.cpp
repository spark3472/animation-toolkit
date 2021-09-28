#include "atkui/framework.h"

using glm::vec3;

class Sphere2D : public atkui::Framework {
 public:
  Sphere2D() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void scene() {

    // draw a sphere at center of screen
    vec3 smallCircle = vec3(width() * 0.5, height() * 0.5, 0);
    vec3 bigCircle = vec3(width() * 0.5, height() * 0.5, -100);
    double radius = 100; 
    double bigRadius = 200;
    setColor(vec3(0,1,0));
    drawSphere(smallCircle, radius);
    setColor(vec3(1,0,0));
    drawSphere(bigCircle,  bigRadius);

    // colors are RGB triplets in range [0,1]

  }
};

int main(int argc, char** argv)
{
  Sphere2D viewer;
  viewer.run();
  return 0;
}
