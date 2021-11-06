#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class Butterfly : public atkui::Framework
{
public:
   Butterfly() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
      Joint* body = new Joint("Body");
      body->setLocalTranslation(vec3(1,2,1)*100.0f);
      body->setLocalRotation(glm::angleAxis(glm::radians<float>(45.0f), vec3(0,1,0)));
      skeleton.addJoint(body);

      Joint* lwing = new Joint("LWing");
      lwing->setLocalTranslation(vec3(0.1,0,0)*100.0f);
      skeleton.addJoint(lwing, body);

      Joint* blwing = new Joint("BLWing");
      blwing->setLocalTranslation(vec3(0.05, 0, 0)*100.0f);
      skeleton.addJoint(blwing, body);
      

      Joint* rwing = new Joint("RWing");
      rwing->setLocalTranslation(vec3(-0.1,0,0)*100.0f);
      skeleton.addJoint(rwing, body);

      Joint* brwing = new Joint("BRWing");
      brwing->setLocalTranslation(vec3(-0.05, 0, 0)*100.0f);
      skeleton.addJoint(brwing, body);

      skeleton.fk();
      time = 0;
   }

   void scene() {
      Joint* body = skeleton.getByName("Body");
      
      body->setLocalTranslation(vec3(1,2,1)*100.0f*sin(elapsedTime()));
      Joint* lwing = skeleton.getByName("LWing");
      lwing->setLocalRotation(glm::angleAxis(sin(elapsedTime()), vec3(0,0,1)));

      Joint* blwing = skeleton.getByName("BLWing");
      blwing->setLocalRotation(glm::angleAxis(sin(elapsedTime()), vec3(0,0,1)));

      Joint* rwing = skeleton.getByName("RWing");
      rwing->setLocalRotation(glm::angleAxis(-sin(elapsedTime()), vec3(0,0,1))); 
      skeleton.fk();

      Joint* brwing = skeleton.getByName("BRWing");
      brwing->setLocalRotation(glm::angleAxis(-sin(elapsedTime()), vec3(0,0,1)));

      // attach geometry to skeleton 
      Transform B = body->getLocal2Global(); 
      Transform LT = lwing->getLocal2Global(); 
      Transform BLT = blwing->getLocal2Global();
      Transform BRT = brwing->getLocal2Global();

      Transform RT = rwing->getLocal2Global(); 

      // draw body
      Transform bodyGeometry(
         glm::angleAxis(glm::pi<float>()*0.60f, vec3(1,0,0)), // rotation
         vec3(0), vec3(25, 200, 25)); // position, scale

      Transform lwingGeometry(
         eulerAngleRO(XYZ, vec3(0,0,0)),
         vec3(-80,0,0),
         vec3(120,20,100));

      Transform blwingGeometry(
         eulerAngleRO(XYZ, vec3(0,0.75,0)),
         vec3(-60,0,50), 
         vec3(100,40,50));

      Transform rwingGeometry(
         eulerAngleRO(XYZ, vec3(0,0,0)),
         vec3(80,0,0), 
         vec3(120,20,100));

      Transform brwingGeometry(
         eulerAngleRO(XYZ, vec3(0,-0.75,0)),
         vec3(60,0,50), 
         vec3(100,40,50));

      setColor(vec3(0.4, 0.4, 0.8));
      push();
      transform(B * bodyGeometry);
      
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0, 0, 0.8));
      push();
      transform(LT * lwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0.0, 0, 0.8));
      push();
      transform(BLT * blwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0, 0, 0.8));
      push();
      transform(RT * rwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0.0, 0, 0.8));
      push();
      transform(BRT * brwingGeometry);
      drawSphere(vec3(0), 1);
      pop();
   }

private:
   Skeleton skeleton;
   double time;
};


int main(int argc, char** argv) {
   Butterfly viewer;
   viewer.run();
}
