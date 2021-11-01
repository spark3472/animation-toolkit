#include "atk/toolkit.h"
#include <iostream>
using namespace atk;
using glm::vec3;

int main(int argc, char** argv)
{
   Skeleton skeleton;
   Motion motion;

   BVHReader reader;
   reader.load("../motions/Beta/idle.bvh", skeleton, motion);

   int numJoints = skeleton.getNumJoints(); 
   std::cout << "The number of joints is " << numJoints << std::endl;

   // todo: loop through and print all joint names
   for (int i = 0; i < numJoints; i++)
   {
      Joint* id = skeleton.getByID(i);
      std::string jointName = id->getName();
      std::cout << i << " " << jointName << std::endl;
   }

   // todo get root of the skeleton
   Joint* root = skeleton.getByID(0);
   std::cout << "The root joint name is: " << root->getName() << std::endl;
   std::cout << "The root joint ID is: " << root->getID() << std::endl;
   std::cout << "The root joint's number of children is: " << root->getNumChildren() << std::endl;

   // todo print the names of the children of the root
   int rootNumChildren = root->getNumChildren();
   for (int i = 0; i < rootNumChildren; i++)
   {
      Joint* child = root->getChildAt(i);

      std::string childName = child->getName();
      std::cout << childName << std::endl; 
   } 

   // Get the joint for the hand by looking up by name ("Beta:LeftHand")
   Joint* hand = skeleton.getByName("Beta:LeftHand\r");
   vec3 offset = hand->getLocalTranslation(); // todo get the local offset from the hand to its parent 
   std::cout << "The offset between the left hand and its parent is " << glm::to_string(offset) << std::endl;

   // todo: get the hand's parent joint's name
   Joint* parent = hand->getParent();
   std::string handParentName = parent->getName();
   std::cout << "The parent of the hand is " << handParentName << std::endl;
}
