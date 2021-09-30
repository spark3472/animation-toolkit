#ifndef _interpolator_hermite_
#define _interpolator_hermite_

#include <string>
#include <vector>
#include <Eigen/Dense>
#include "interpolator.h"

using namespace Eigen;
using namespace std;
using namespace glm;

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
        int size = keys.size();
        mCtrlPoints = keys;
        mCtrlPoints[1];



        MatrixXd A(5, 5);
        A(0,0) =  2; A(0,1) = 1; A(0,2) = 0; A(0,3) = 0; A(0,4) = 0;
        A(1,0) =  1; A(1,1) = 4; A(1,2) = 1; A(1,3) = 0; A(1,4) = 0;
        A(2,0) =  0; A(2,1) = 1; A(2,2) = 4; A(2,3) = 1; A(2,4) = 0;
        A(3,0) =  0; A(3,1) = 0; A(3,2) = 1; A(3,3) = 4; A(3,4) = 1;
        A(4,0) =  0; A(4,1) = 0; A(4,2) = 0; A(4,3) = 1; A(4,4) = 2;

        if (isClamped()){
            vec3 p0 = mCtrlPoints[0];
            vec3 p1 = mCtrlPoints[1];
            vec3 p2 = mCtrlPoints[2];
            vec3 p3 = mCtrlPoints[3];
            vec3 p4 = mCtrlPoints[4];

            Eigen::MatrixXd p(5, 3);
            Eigen::MatrixXd pPrime(5, 3); // slopes for each control point
            
            vec3 v0 = getClampDirection();
            vec3 v1 = 3.0f *(p2 - p0);
            vec3 v2 = 3.0f *(p3 - p1);
            vec3 v3 = 3.0f *(p4 - p2);
            vec3 v4 = getClampDirection();

            p(0,0) = v0[0]; p(0,1) = v0[1]; p(0,2) = v0[2]; 
            p(1,0) = v1[0]; p(1,1) = v1[1]; p(1,2) = v1[2]; 
            p(2,0) = v2[0]; p(2,1) = v2[1]; p(2,2) = v2[2]; 
            p(3,0) = v3[0]; p(3,1) = v3[1]; p(3,2) = v3[2]; 
            p(4,0) = v4[0]; p(4,1) = v4[1]; p(4,2) = v4[2]; 
            
            pPrime = A.inverse() * p;
            for (int i = 0; i < 5; i++){
                mCtrlPoints.push_back(vec3(pPrime(i, 0), pPrime(i, 1), pPrime(i, 2)));
                //std::cout << "slope " << i << " = " << pPrime(i,0 ) << " " << pPrime(i,1) << std::endl;
            }
        }else{//hermite example in ~/classexample
            vec3 p0 = mCtrlPoints[0];
            vec3 p1 = mCtrlPoints[1];
            vec3 p2 = mCtrlPoints[2];
            vec3 p3 = mCtrlPoints[3];
            vec3 p4 = mCtrlPoints[4];
            
            // Solve the system of linear equations
            Eigen::MatrixXd p(5, 3);
            Eigen::MatrixXd pPrime(5, 3); // slopes for each control point
            
            vec3 v0 = 3.0f *(p1 - p0);
            vec3 v1 = 3.0f *(p2 - p0);
            vec3 v2 = 3.0f *(p3 - p1);
            vec3 v3 = 3.0f *(p4 - p2);
            vec3 v4 = 3.0f *(p4 - p3);


            p(0,0) = v0[0]; p(0,1) = v0[1]; p(0,2) = v0[2]; 
            p(1,0) = v1[0]; p(1,1) = v1[1]; p(1,2) = v1[2]; 
            p(2,0) = v2[0]; p(2,1) = v2[1]; p(2,2) = v2[2]; 
            p(3,0) = v3[0]; p(3,1) = v3[1]; p(3,2) = v3[2]; 
            p(4,0) = v4[0]; p(4,1) = v4[1]; p(4,2) = v4[2]; 
            
            pPrime = A.inverse() * p;
            for (int i = 0; i < 5; i++){
                //std::cout << "slope " << i << " = " << pPrime(i,0 ) << " " << pPrime(i,1) << std::endl;
            }
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
