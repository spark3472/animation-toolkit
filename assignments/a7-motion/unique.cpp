#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class Unique : public atkui::Framework
{
public:
   Unique() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
      BVHReader reader;
      reader.load("../motions/Beta/gangnam_style.bvh", skeleton, motion);
      BVHReader read;
      read.load("../motions/Beta/samba_dancing.bvh", samba, dance);
      dance.update(skeleton, 0);
      motion.update(skeleton, 0);
   }

   void scene() {
      time += dt();
      

      motion.update(skeleton, time);
      dance.update(samba, time);

      setColor(vec3(0,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }
      for (int i = 0; i < samba.getNumJoints(); i++) {
         Joint* joint = samba.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }

      
   }

private:
   Skeleton skeleton;
   Skeleton samba;
   Motion motion;
   Motion dance;
   float time = 0;
};



int main(int argc, char** argv) {
   Unique viewer;
   if (argc == 1)
   viewer.run();
}
