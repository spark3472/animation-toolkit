#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <cmath>
#include <string>

using namespace glm;
using namespace atk;
using namespace atkui;

class Unique : public atkui::Framework
{
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   void setup()
   {
      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _motion);
      
      reader.load("../motions/Beta/walking.bvh", partner, _motion);
      _heading = 0;
      _offset = vec3(0);
      _offset[1] = _motion.getKey(0).rootPos[1];
      _time = 0;

      _reoriented = reorient(_motion, _offset, _heading);
      next = reorient(_motion, _offset, _heading + M_PI);
   }

   Motion reorient(const Motion& motion, const vec3& pos, float heading)
   {
      Motion result;
      result.setFramerate(motion.getFramerate());
      quat rotation = eulerAngleRO(XYZ, vec3(0, heading, 0));
      
      
      for(int i = 0; i < motion.getNumKeys() - 1; i++)
      {
         Pose pose = motion.getKey(i);
         
         pose.rootPos = rotation * pose.rootPos + pos;

         pose.jointRots[0] = pose.jointRots[0] * rotation;

      

         result.appendKey(pose);
      }
      
      return result;
   }

   void update()
   {
      _time += dt() * 0.5;
      next.update(partner, _time);
      _reoriented.update(_skeleton, _time);
   }

   void scene()
   {  
      update();
      SkeletonDrawer drawer;
      drawer.draw(_skeleton, *this);
      drawer.draw(partner, *this);
      if(_motion.getDuration() < _time)
      {
         _heading += M_PI/8;
         next = reorient(_motion, _offset, _heading + M_PI);
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
      }
   }

   

   Skeleton _skeleton;
   Skeleton partner;
   Motion _motion;
   Motion next;
   Motion _reoriented;
   vec3 _offset;
   float _heading;
   float _time;
};

int main(int argc, char** argv)
{
   Unique viewer;
   viewer.run();
   return 0;
}


