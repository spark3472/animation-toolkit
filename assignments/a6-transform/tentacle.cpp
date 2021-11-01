#include "atkui/framework.h"
#include "atk/toolkit.h"
using namespace atk;
using glm::vec3;

class Tentacle : public atkui::Framework {
public:
   Tentacle() : atkui::Framework(atkui::Perspective) {}
   virtual ~Tentacle() {}

   virtual void setup() {
      
      lookAt(vec3(200), vec3(0));

      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0,0,0));
      _tentacle.addJoint(root);

      Joint* joint1  = new Joint("joint1");
      joint1->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint1, root);


      Joint* joint2  = new Joint("joint2");
      joint2->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint2, joint1);


      Joint* joint3  = new Joint("joint3");
      joint3->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint3, joint2);


      Joint* joint4  = new Joint("joint4");
      joint4->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint4, joint3);
      // todo: add more joints
      _tentacle.fk(); // compute local2global transforms

      p1 = vec3(0);
      p2 = vec3(0);

      roottheta = 0.0f;
      j1theta = 0.0f;
      j2theta = 0.0f;
      j3theta = 0.0f;
      j4theta = 0.0f;

      thetaRate = 0.0f;
      
      iterate = 0;
   }

   virtual void scene()
   {
      // todo animate joints
      // hint: use glm::angleAxis(...) to compute quaternions for each joint
      _tentacle.fk(); // computes local2global transforms
      setColor(vec3(0,1,0));

      // todo: loop over all joints and draw
      
      for (int i = 0; i < _tentacle.getNumJoints(); i++)
      {

         Joint* joint = _tentacle.getByID(i);
         if (joint != _tentacle.getByID(0))
         {
            Joint* parent = joint->getParent();
            p1 = parent->getGlobalTranslation();
            p2 = joint->getGlobalTranslation();
            drawEllipsoid(p1, p2, 5);
            
         }
         if (joint->getID() == 0 )
         {
            roottheta += 0.01f;
            glm::quat q = glm::angleAxis(sin(roottheta), vec3(0, 0, 1));
            joint->setLocalRotation(q);
         }else if (joint->getID() == 1)
         {
            j1theta += 0.02f;
            glm::quat q = glm::angleAxis(sin(j1theta), vec3(0, 0, 1));
            joint->setLocalRotation(q);
         }
         else if (joint->getID() == 2)
         {
            j2theta += 0.03f;
            glm::quat q = glm::angleAxis(sin(j2theta), vec3(0, 0, 1));
            joint->setLocalRotation(q);
         }
         else if (joint->getID() == 3)
         {
            j3theta += 0.04f;
            glm::quat q = glm::angleAxis(sin(j3theta), vec3(0, 0, 1));
            joint->setLocalRotation(q);
         }
         
      }
   }

protected:
   Skeleton _tentacle;
   vec3 p1;
   vec3 p2;
   float roottheta;
   float j1theta;
   float j2theta;
   float j3theta;
   float j4theta;
   float theta;
   float thetaRate;
   int iterate;
   
};

int main(int argc, char** argv)
{
   Tentacle viewer;
   viewer.run();
} 

