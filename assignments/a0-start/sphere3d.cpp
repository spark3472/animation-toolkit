<<<<<<< HEAD
#include "atkui/framework.h"

using glm::vec3;
using namespace std;

class Sphere3D : public atkui::Framework {
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }
  virtual void setup(){
    currentPos = vec3(0);
    vel = vec3(0);
  }
  virtual void scene(){
    // update
    currentPos = currentPos + 50.0f * vel * dt();

    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));
    // draw a sphere at center of the world
    float radius = 50.0;
    drawSphere(currentPos, radius);

  }

  void keyUp(int key, int mods) {
    if (key == GLFW_KEY_SPACE) {
      vel = agl::randomUnitVector();
    }else if (key == GLFW_KEY_R) {
      currentPos = vec3(0);
      vel = vec3(0);
    }
  }
  vec3 currentPos;
  vec3 vel;
  int key;
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
=======
#include "atkui/framework.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }

  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));

    // draw a sphere at center of the world
    float radius = 50.0;
    drawSphere(vec3(0), radius);
  }
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
>>>>>>> upstream/main
