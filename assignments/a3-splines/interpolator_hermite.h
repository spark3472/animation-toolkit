#ifndef _interpolator_hermite_
#define _interpolator_hermite_

#include <string>
#include <vector>
#include <Eigen/Dense>
#include "interpolator.h"

using namespace Eigen;
using namespace std;

//--------------------------------
// Hermite 
//--------------------------------

class InterpolatorHermite : public Interpolator
{
public:
    InterpolatorHermite() : Interpolator("Hermite"), mClampDir(glm::vec3(1,0,0)) {}

    virtual glm::vec3 interpolate(int segment, float u) const {

       // todo: your code here
       return glm::vec3(0);
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {

        mCtrlPoints = keys;
        mCtrlPoints[1];
        MatrixXf A(5, 5);
        A(0, 0) = 2;
        A(1, 0) = 1;
        A(2, 0) = 0;
        A(3, 0) = 0;
        A(4, 0) = 0;
        A(0, 1) = 1;
        A(1, 1) = 4;
        A(2, 1) = 1;
        A(3, 1) = 0;
        A(4, 1) = 0;
        A(0, 2) = 0;
        A(1, 2) = 1;
        A(2, 2) = 4;
        A(3, 2) = 1;
        A(4, 2) = 0;
        A(0, 3) = 0;
        A(1, 3) = 0;
        A(2, 3) = 1;
        A(3, 3) = 4;
        A(4, 3) = 1;
        A(0, 4) = 0;
        A(1, 4) = 0;
        A(2, 4) = 0;
        A(3, 4) = 1;
        A(4, 4) = 2;

        if (isClamped()){
            glm::vec3 v0, v1, v2, v3;
            v0 = getClampDirection();
            
            MatrixXf b(5, 3);
            b(0, 0) = v0.x;
            b(0, 1) = v0.y;
            b(0, 2) = v0.z;
            b(1, 0) = (3.0f*(mCtrlPoints[2] - mCtrlPoints[0]).x);
            b(1, 1) = (3.0f*(mCtrlPoints[2] - mCtrlPoints[0]).y);
            b(1, 2) = (3.0f*(mCtrlPoints[2] - mCtrlPoints[0]).z);
            b(2, 0) = (3.0f*(mCtrlPoints[3] - mCtrlPoints[1]).x);
            b(2, 1) = (3.0f*(mCtrlPoints[3] - mCtrlPoints[1]).y);
            b(2, 2) = (3.0f*(mCtrlPoints[3] - mCtrlPoints[1]).z);
            b(3, 0) = (3.0f*(mCtrlPoints[4] - mCtrlPoints[2]).x);
            b(3, 1) = (3.0f*(mCtrlPoints[4] - mCtrlPoints[2]).y);
            b(3, 2) = (3.0f*(mCtrlPoints[4] - mCtrlPoints[2]).z);
            b(4, 0) = v0.x;
            b(4, 1) = v0.y;
            b(4, 2) = v0.z;

            MatrixXf x = A.llt().solve(b);
            cout << A << endl;
            cout << b << endl;
            cout << x << endl;
            
            

       }
        
       // todo: your code here
    }

    void setClamped(bool c) { mIsClamped = c; }
    bool isClamped() const { return mIsClamped; }

    void setClampedDirection(const glm::vec3& v) { mClampDir = v; }
    glm::vec3 getClampDirection() const { return mClampDir; }

private:
    bool mIsClamped = true;
    glm::vec3 mClampDir;
};

#endif
