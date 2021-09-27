<<<<<<< HEAD
#include "atkui/framework.h"

using glm::vec3;
using namespace std;
class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
    }
    virtual void setup() {
      radius = 100;
      right = vec3(width() * 0.35, height() * 0.5, -100);
      left = vec3(width() * 0.65, height() * 0.5, -100);
      rightPupil = vec3(width() * 0.2725, height() * 0.5, 0);
      leftPupil = vec3(width() * 0.5725, height() * 0.5, 0);
      vel = vec3(0.65, 0, 0);
    }
    virtual void scene() {
      setColor(vec3(1));
      drawSphere(right, radius);
      drawSphere(left,  radius);

      rightPupil = rightPupil + vel * sin(elapsedTime());
      leftPupil = leftPupil + vel * sin(elapsedTime());
      setColor(vec3(0));
      drawSphere(rightPupil, 30);
      drawSphere(leftPupil, 30);  


    }
    vec3 right;
    vec3 left;
    vec3 rightPupil;
    vec3 leftPupil;
    vec3 vel;
    float radius;
};

int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}
=======
#include "atkui/framework.h"

using namespace glm;
class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
    }

    virtual void scene() {
    }
};

int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}
>>>>>>> upstream/main
