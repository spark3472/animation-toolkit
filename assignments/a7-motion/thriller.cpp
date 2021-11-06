#include <random>
#include <functional>
#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "agl/renderer.h"
#include "devil.h"

using namespace atk;
using namespace glm;

class Thriller : public atkui::Framework
{
public:
   Thriller() : atkui::Framework(atkui::Perspective) {}
   virtual ~Thriller() {}

   virtual void setup() {
      BVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);

      vec3 position = vec3(0);
      vec3 color = vec3(1,0,0);
      float size = 1.0f;
      _devil = Devil(position, color, size);
      for (int i = 0; i < 24; i++)
      {
         float si = (float)(rand()%4+1)/4;
         vec3 pos;
         vec3 col = vec3(rand()%10*0.05, rand()%10*0.05, rand()%10*0.05);
         if (i%2 == 0)
         {
            pos = vec3(rand()%100-50, 0, rand()*100-50);
         }else
         {
            pos = vec3(rand()%100-50, 0, rand()%100-50);
         }
         devils[i] = Devil(pos, col, si);
      }
   }

   virtual void scene() {
      if (!_paused) _motion.update(_skeleton, elapsedTime());
      //_devil.draw(_skeleton, *this);
      for (int i = 0; i < 24; i++)
      {
         devils[i].draw(_skeleton, *this);
      }
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   Devil devils[24];
   Devil _devil;
};

int main(int argc, char** argv) {
   Thriller viewer;
   viewer.run();
}

