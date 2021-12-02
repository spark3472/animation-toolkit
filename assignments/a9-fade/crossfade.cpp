#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <stdio.h>
#include <string.h>

using namespace atk;
using namespace atkui;
using namespace glm;

class ACrossfadeViewer : public atkui::Framework
{
public:
  ACrossfadeViewer() : atkui::Framework(atkui::Perspective) {}
  virtual ~ACrossfadeViewer() {}

  void loadMotion1(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion1_);
  }

  void loadMotion2(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion2_);
  }

  void crossfade(int numBlendFrames)
  {
    assert(motion1_.getNumKeys() > 0);
    assert(motion2_.getNumKeys() > 0);
    assert(numBlendFrames > 0);
    assert(numBlendFrames <= motion1_.getNumKeys());
    assert(numBlendFrames <= motion2_.getNumKeys());

    int start1 = motion1_.getNumKeys() - numBlendFrames;
    int start2 = 0;

    blend_.setFramerate(motion1_.getFramerate());

    for (int i = 0; i < start1; i++)
    {
      blend_.appendKey(motion1_.getKey(i));
    }

    Motion result;
    Pose last_m1 = motion1_.getKey(motion1_.getNumKeys() - 1);
    vec3 root = last_m1.rootPos;
    quat rotation = last_m1.jointRots[0];

    

    for(int i = 0; i < motion2_.getNumKeys() - 1; i++)
      {
         Pose pose = motion2_.getKey(i);
         
         pose.rootPos = pose.rootPos + root + vec3(0, -95, 0);
         //pose.rootPos = pose.rootPos + root + vec3(0, -95, 0);
         

         pose.jointRots[0] = rotation;

      

         result.appendKey(pose);
      }


    for (int i = 0; i < numBlendFrames; i++)
    {
      //motion1(i+k)(1-a)+motion2(k)(a)
      Pose pose1 = motion1_.getKey(start1 + i);
      Pose pose2 = result.getKey(i);
      Pose newPose = newPose.Lerp(pose1, pose2, i/(numBlendFrames-1));
      blend_.appendKey(newPose);
    }

    for (int i = numBlendFrames; i < result.getNumKeys(); i++)
    {
      blend_.appendKey(result.getKey(i));
    }
  


    // TODO: Your code here
  }

  void save(const std::string &filename)
  {
    BVHWriter writer;
    writer.save(filename, skeleton_, blend_);
  }

  void scene()
  {
    blend_.update(skeleton_, elapsedTime()/4);
    drawer_.draw(skeleton_, *this);
  }

private:
  Skeleton skeleton_;
  SkeletonDrawer drawer_;
  Motion motion1_;
  Motion motion2_;
  Motion blend_;
};

std::string PruneName(const std::string &name)
{
  int idx1 = name.find_last_of("/");
  int idx2 = name.find_last_of(".");
  return name.substr(idx1 + 1, idx2 - idx1 - 1);
}

int main(int argc, char **argv)
{
  std::string motion1 = "../motions/Beta/walking.bvh";
  std::string motion2 = "../motions/Beta/jump.bvh";
  

  int numFrames = 10;

  try
  {
    for (int i = 0; i < argc; i++)
    {
      if (strncmp(argv[i], "-m1", 3) == 0)
        motion1 = argv[i + 1];
      else if (strncmp(argv[i], "-m2", 3) == 0)
        motion2 = argv[i + 1];
      else if (strncmp(argv[i], "-nframes", 7) == 0)
        numFrames = std::stoi(argv[i + 1]);
    }
  }
  catch (const std::exception &e)
  {
    std::cout << "usage: crossfade -m1 <path> -m2 <path> -nframes <num frames>\n";
  }

  ACrossfadeViewer viewer;
  viewer.loadMotion1(motion1);
  viewer.loadMotion2(motion2);
  viewer.crossfade(numFrames);

  std::string saveName = "blend-" + PruneName(motion1) + PruneName(motion2);
  saveName += "-" + std::to_string(numFrames) + ".bvh";
  viewer.save(saveName);

  viewer.run();
  return 0;
}
