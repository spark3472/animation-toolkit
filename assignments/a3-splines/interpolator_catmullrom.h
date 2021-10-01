#ifndef _interpolator_catmullrom_
#define _interpolator_catmullrom_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Catmull-Rom 
//--------------------------------

class InterpolatorCatmullRom : public Interpolator
{
public:
    InterpolatorCatmullRom() : Interpolator("Catmull-Rom") {}

    virtual glm::vec3 interpolate(int segment, float u) const {
       if (segment == 0){
         return getControlPoint(segment)*(1.0f-u)*(1.0f-u)*(1.0f-u) + 3.0f*u*(1.0f-u)*(1.0f-u)*getControlPoint(segment + 3) + 3.0f*u*u*(1.0f-u)*getControlPoint(segment + 4) + u*u*u*getControlPoint(segment + 1); 
       }else{//else segment equals 1
         return getControlPoint(segment)*(1.0f-u)*(1.0f-u)*(1.0f-u) + 3.0f*u*(1.0f-u)*(1.0f-u)*getControlPoint(segment + 4) + 3.0f*u*u*(1.0f-u)*getControlPoint(segment + 5) + u*u*u*getControlPoint(segment + 1); 
       }
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       float fraction = ((float)1/(float)6);
       mCtrlPoints = keys;
       if (keys.size() < 4){
         glm::vec3 b00, b01, b02, b03;
         glm::vec3 b10, b11, b12, b13;
         b00 = mCtrlPoints[0];
         b03 = mCtrlPoints[1];
         b10 = mCtrlPoints[1];
         b13 = mCtrlPoints[2];
         
         b01 = b00 + fraction*(b03-b00);
         b02 = b03 - fraction*(b13-b00);
         b11 = b10 + fraction*(b13-b00);
         b12 = b13 - fraction*(b13-b10);
         
         mCtrlPoints.push_back(b01);
         mCtrlPoints.push_back(b02);
         mCtrlPoints.push_back(b11);
         mCtrlPoints.push_back(b12);
       }
       
       // todo: your code here
       // see: interpolator.h and writeup for details
    }
};

#endif
