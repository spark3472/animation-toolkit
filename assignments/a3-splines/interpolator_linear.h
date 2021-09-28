#ifndef _interpolator_linear_H_
#define _interpolator_linear_H_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Linear 
//--------------------------------

class InterpolatorLinear : public Interpolator
{
public:
    InterpolatorLinear() : Interpolator("Linear") {}
    virtual glm::vec3 interpolate(int segment, float u) const {
      return (getControlPoint(segment) * (1.0f-u) + getControlPoint(segment+1) * u); 
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       mCtrlPoints = keys;
    }
};

#endif
