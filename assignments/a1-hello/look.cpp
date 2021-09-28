
#include "atkui/framework.h"

using namespace glm;

class Look : public atkui::Framework {
 public:
  Look() : atkui::Framework(atkui::Orthographic) {
  }
  float lwidth = width()*0.375;
  float rwidth = width()*0.625;
  virtual void setup() {
    radius = 100;
    left = vec3(lwidth, height() * 0.5, 0);
    right = vec3(rwidth, height() * 0.5, 0);
    
    leftCenter = vec3(lwidth, height() * 0.5, 0);
    rightCenter = vec3(rwidth, height() * 0.5, 0);
    vel = vec3(0.65, 0, 0);
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
  }

  virtual void scene() {
    vec3 target = vec3(_mouseX, _mouseY, 0);
    setColor(vec3(1, 0, 0));
    drawSphere(target, 5);
    setColor(vec3(1));
    drawSphere(right, radius);
    drawSphere(left,  radius);
    
    leftPupil = left + vec3(25 * cos(atan2(_mouseY - lwidth, _mouseX-height()*0.5)), 25 * sin(atan2(_mouseY-lwidth, _mouseX-height()*0.5)), 100);
    rightPupil = right + vec3(25 * cos(atan2(_mouseY - rwidth, _mouseX-height()*0.5)), 25 * sin(atan2(_mouseY-rwidth, _mouseX-height()*0.5)), 100);
    setColor(vec3(0));
    drawSphere(rightPupil, 30);
    drawSphere(leftPupil, 30); 

  }
  
  void mouseMotion(int x, int y, int dx, int dy) {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)){
      _mouseX = x;
      _mouseY = height() - y;
    }
  }

 private:
  int _mouseX;
  int _mouseY;
  vec3 right;
  vec3 left;
  vec3 rightPupil;
  vec3 leftPupil;
  vec3 vel;
  vec3 rightCenter;
  vec3 leftCenter;
  float radius;
};

int main(int argc, char** argv) {
  Look viewer;
  viewer.run();
  return 0;
}

