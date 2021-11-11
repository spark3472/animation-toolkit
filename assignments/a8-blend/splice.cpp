#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace atkui;
using namespace glm;

class ASplice : public atkui::Framework
{
public:
   ASplice() : atkui::Framework(atkui::Perspective) {}
   virtual ~ASplice() {}

   void setup()
   {
      _alpha = 0;

      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _lower);
      reader.load("../motions/Beta/gangnam_style.bvh", _skeleton, _upper);
      _splice = spliceUpperBody(_lower, _upper, _alpha);
   }

   Motion spliceUpperBody(const Motion& lower, const Motion& upper, float alpha)
   {
      Motion result;
       
      result.setFramerate(lower.getFramerate());
      // todo: your code here

      int id = 0;
      for (int i = 0; i < _skeleton.getNumJoints(); i++)
      {
         if (_skeleton.getByID(i) == _skeleton.getByName("Beta:Spine1"))
         {
            id = i;
         }
      }
      Joint* spine1 = _skeleton.getByName("Beta:Spine1");
      int numChild = spine1->getNumChildren();
      int numJoints = _skeleton.getNumJoints();
      
      
      for(int i = 0; i < lower.getNumKeys() -1; i++)
      {
         Pose pose = upper.getKey(120+i);
         Pose pose2 = lower.getKey(i);
         Pose newpose = pose2;
         for (int j = 0; j < numJoints; j++)
         {
            if( j >= 2 && j <= 55)
            {
               //newpose.jointRots[j] = pose.jointRots[j];
               newpose.jointRots[j] = slerp(pose2.jointRots[j], pose.jointRots[j], alpha);
            }
         }
         result.appendKey(newpose);
      }
      return result;
   }

   void scene()
   {  
      _splice.update(_skeleton, elapsedTime() * 0.5);
      SkeletonDrawer drawer;
      drawer.draw(_skeleton, *this);
      drawText("alpha: "+std::to_string(_alpha), 10, 15);
   }

   void keyUp(int key, int mods) 
   {
      if (key == GLFW_KEY_UP)
      {
         _alpha = std::min(_alpha+0.05, 1.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
      else if (key == GLFW_KEY_DOWN)
      {
         _alpha = std::max(_alpha-0.05, 0.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
   }

   Skeleton _skeleton;
   Motion _upper;
   Motion _lower;
   Motion _splice;
   float _alpha;
};

int main(int argc, char** argv)
{
   ASplice viewer;
   viewer.run();
   return 0;
}

