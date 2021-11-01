#include "atkui/framework.h"
#include "atk/toolkit.h"
using namespace atk;
using glm::vec3;

class Unique : public atkui::Framework
{
  public:
    Unique() : atkui::Framework(atkui::Perspective) {
    }
    virtual ~Unique(){}
  
 
    virtual void setup() 
    {
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
      _tentacle.fk();

      p1 = vec3(0);
      p2 = vec3(0);



      theta = 0.0f;

      thetaRate = 0.10f;
      

      
    }
    virtual void scene()
    {

      _tentacle.fk(); 

      
      for (int i = 0; i < _tentacle.getNumJoints(); i++)
      {

         Joint* joint = _tentacle.getByID(i);
         if (joint != _tentacle.getByID(0))
         {
            Joint* parent = joint->getParent();
            p1 = parent->getGlobalTranslation();
            p2 = joint->getGlobalTranslation();
            setColor(vec3(1, 0, 0));
            drawEllipsoid(p1, p2, 5);
            
         }
        theta += thetaRate * dt();
        
        glm::quat q = glm::angleAxis(4.0f*sin(2.0f*theta), vec3(0, 0, 1));
        joint->setLocalRotation(q);
         
      }

    }

    protected:
   Skeleton _tentacle;
   vec3 p1;
   float rot;
   vec3 p2;
   float theta;
   float thetaRate;
   
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
}


