<<<<<<< HEAD
#include "atkui/framework.h"

using namespace glm;

class Unique : public atkui::Framework
{
     
public:

   Unique() : atkui::Framework(atkui::Orthographic) {
   }
   

   virtual void setup() {
      theta = 0.0f;
      thetaRate = 0.5f;
      radius = 25;
      vel = vec3(10, 10, 0);
      firstCircle = vec3(width() * 0.55, height() * 0.5, 0);
      center = vec3(width()*0.5, height()*0.5, 0);
      setPositions();
   }

   virtual void scene() {
      theta += thetaRate * dt();
      setColor(vec3(1, 0, 0));
      //drawSphere(center, radius);
      
      setColor(vec3(0,165,227)/255.0f);
      concentric(1);
      setColor(vec3(141,215,191)/255.0f);
      concentric(50);
      setColor(vec3(255,150,197)/255.0f);
      concentric(100);
      setColor(vec3(255,87,104)/255.0f);
      concentric(150); 
      setColor(vec3(255,162,58)/255.0f);
      concentric(200);
      setColor(vec3(0,165,227)/255.0f);
      concentric(250); 
      setColor(vec3(141,215,191)/255.0f);
      concentric(300);
      setColor(vec3(255,150,197)/255.0f);
      concentric(350); 
      setColor(vec3(255,87,104)/255.0f);
      concentric(400);
      setColor(vec3(255,162,58)/255.0f);
      concentric(450);  
   }

   void concentric(float conRadius){
      for (int i = 0; i < 36; i++){
         drawSphere(circles[i], radius);
         circles[i] = center + vec3(10+ conRadius * cos(2*3.14*i/36),10 + conRadius * sin(2*3.14*i/36), 0);
         circles[i] += vec3(conRadius*cos(theta), conRadius*sin(theta), 0);
      }
   }

   void setPositions(){
      for (int i = 0; i < 36; i++){
         circles[i] = vec3(width() * 0.55, height() * 0.5, 0);
      }
   }
   float radius;
   float a;
   vec3 vel;
   vec3 circles[36];
   vec3 firstCircle;
   vec3 center;
   float theta;
   float thetaRate;


};

int main(int argc, char** argv)
{
   Unique viewer;
   viewer.run();
   return 0;
}
=======
#include "atkui/framework.h"

using namespace glm;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    // your code here!
  }

  virtual void scene() {
    // your code here!
  }
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
  return 0;
}

>>>>>>> upstream/main
