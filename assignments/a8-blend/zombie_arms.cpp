#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace glm;
using namespace atk;
using namespace atkui;

class AZombieArms : public atkui::Framework {
public:
   AZombieArms() : atkui::Framework(atkui::Perspective) {}
   virtual ~AZombieArms() {}

   void setup() {
      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _original);

      _zombieFreeze = ComputeArmFreeze(_original);
      _zombieOffset = ComputeArmOffset(_original);
   }

   Motion ComputeArmOffset(const Motion& motion) {
      quat leftLocalRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightLocalRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat elbowLocalRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Motion result;
      result.setFramerate(motion.getFramerate());
      // todo: your code here

      Transform Rji_left = leftArm->getLocal2Parent(); 
      Rji_left = Rji_left.inverse();
      quat Rji_l = Rji_left.r();

      Transform Rji_right = rightArm->getLocal2Parent(); 
      Rji_right = Rji_right.inverse();
      quat Rji_r = Rji_right.r();
      
      quat R_offset_left = leftLocalRot * Rji_l;
      quat R_offset_right = rightLocalRot * Rji_r;

      leftArm->setLocalRotation(leftLocalRot * R_offset_left);
      rightArm->setLocalRotation(rightLocalRot * R_offset_right);
      leftElbow->setLocalRotation(elbowLocalRot);
      rightElbow->setLocalRotation(elbowLocalRot);

      int LAid = 0;
      int RAid = 0;
      int LEid = 0;
      int REid = 0;

      for (int i = 0; i < _skeleton.getNumJoints(); i++)
      {
         if (_skeleton.getByID(i) == leftArm)
         {
            LAid = i;
         }else if (_skeleton.getByID(i) == rightArm)
         {
            RAid = i;
         }else if (_skeleton.getByID(i) == leftElbow)
         {
            LEid = i;
         }else if (_skeleton.getByID(i) == rightElbow)
         {
            REid = i;
         }
      }

      Pose pose = _skeleton.getPose();

      for(int i = 0; i < motion.getNumKeys() - 1; i++)
      {
         Pose pose2 = motion.getKey(i);
         for(int j = 0; j < _skeleton.getNumJoints(); j++)
         {
            if (j == LAid || j == RAid || j == LEid || j == REid)
            {
               pose2.jointRots[j] = pose.jointRots[j];
            }
         }
         result.appendKey(pose2);
      }

      return result;
   }

   Motion ComputeArmFreeze(const Motion& motion) {
      quat leftRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat elbowRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Motion result;
      result.setFramerate(motion.getFramerate());
      // todo: your code here
      leftArm->setLocalRotation(leftRot);
      rightArm->setLocalRotation(rightRot);
      leftElbow->setLocalRotation(elbowRot);
      rightElbow->setLocalRotation(elbowRot);

      int LAid = 0;
      int RAid = 0;
      int LEid = 0;
      int REid = 0;

      for (int i = 0; i < _skeleton.getNumJoints(); i++)
      {
         if (_skeleton.getByID(i) == leftArm)
         {
            LAid = i;
         }else if (_skeleton.getByID(i) == rightArm)
         {
            RAid = i;
         }else if (_skeleton.getByID(i) == leftElbow)
         {
            LEid = i;
         }else if (_skeleton.getByID(i) == rightElbow)
         {
            REid = i;
         }
      }

      Pose pose = _skeleton.getPose();

      for(int i = 0; i < motion.getNumKeys() - 1; i++)
      {
         Pose pose2 = motion.getKey(i);
         for(int j = 0; j < _skeleton.getNumJoints(); j++)
         {
            if (j == LAid || j == RAid || j == LEid || j == REid)
            {
               pose2.jointRots[j] = pose.jointRots[j];
            }
         }
         result.appendKey(pose2);
      }

      

      return result;
   }

   void update() {
      double t =  elapsedTime() * 0.5;
      if (_currentMotion == 1) {
         _zombieFreeze.update(_skeleton, t);
         drawText("Joint edit type: freeze", 10, 15);

      } else if (_currentMotion == 2) {
         _zombieOffset.update(_skeleton, t);
         drawText("Joint edit type: offset", 10, 15);

      } else {
         _original.update(_skeleton, t);
         drawText("Joint edit type: none", 10, 15);
      }
   }

   void scene() {  
      update();
      _drawer.draw(_skeleton, *this);
   }

   void keyUp(int key, int mods) {
      if (key == '1') {
          _currentMotion = 1;
      } else if (key == '2') {
          _currentMotion = 2;
      } else if (key == '0') {
          _currentMotion = 0;
      }
   }

   SkeletonDrawer _drawer;
   Skeleton _skeleton;
   Motion _original;
   Motion _zombieFreeze;
   Motion _zombieOffset;
   int _currentMotion = 0;
};

int main(int argc, char** argv) {
   AZombieArms viewer;
   viewer.run();
   return 0;
}

