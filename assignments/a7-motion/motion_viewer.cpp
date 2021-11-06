#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;
char const  *file;

class MotionViewer : public atkui::Framework
{
public:
   MotionViewer() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
      BVHReader reader;
      p = 0;
      reader.load(file, skeleton, motion);
      motion.update(skeleton, 0);
   }

   void scene() {
      if (!paused)
      {
         time += dt() * timeScale;
      }

      motion.update(skeleton, time);

      setColor(vec3(0,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }

      drawText(paused? "Paused" : "Playing", 10, 15);
      drawText("Current frame: "+std::to_string(currentFrame), 10, 35);
      drawText("Time scale: "+std::to_string(timeScale), 10, 55);
   }

   virtual void keyUp(int key, int mods) {
      if (key == '0')
      {
         time = 0;
      }

      if (key == 'P')
      {
         if (p == 0)
         {
            paused = true;
            p++;
         }else
         {
            paused = false;
            p--;
         }
      }

      if (key == '.')
      {
         if (paused)
         {

         }
      }

      if (key == ',')
      {
         if (paused)
         {

         }
      }

      if (key == ']')
      {
         timeScale = 2.0f;
      }

      if (key == '[')
      {
         timeScale = 0.5f;
      }
   }
   

private:
   Skeleton skeleton;
   int p;
   Motion motion;
   float timeScale = 1.0f;
   int currentFrame = 0; 
   bool paused = false;
   float time = 0;
};



int main(int argc, char** argv) {
   MotionViewer viewer;
   if (argc == 1)
   {
      file = "../motions/Beta/jump.bvh";
   }else
   {
      file = argv[1];
   }

   viewer.run();
}
