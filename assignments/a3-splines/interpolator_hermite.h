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
        vec3 p1 = getControlPoint(segment);
        vec3 pprime1 = getControlPoint(segment+getNumControlPoints()/2);
        vec3 p2 = getControlPoint(segment+1);
        vec3 pprime2 = getControlPoint(segment+getNumControlPoints()/2 + 1);
        return p1*(1.0f-3.0f*u*u+2.0f*u*u*u) + pprime1*(u-2.0f*u*u+u*u*u) + pprime2*(-u*u+u*u*u) + p2 * (3.0f*u*u-2.0f*u*u*u);
       //todo: your code here
       return glm::vec3(0);
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
        int size = keys.size();
        mCtrlPoints = keys;
        if(size >= 5){
            if (isClamped()){
                MatrixXd A(size, size);
                for (int i = 0; i < size; i++){
                    for (int j = 0; j < size; j++){
                        A(i, j) = 0;
                    if (i == 0 && j == 0){
                        A(i, j) = 1;
                    }else if (i == size-1 && j == size-1){
                        A(i, j) = 1;
                    }else if ( j == i - 1){
                        A(i, i-1) = 1;
                    }else if ( j == i){
                        A(i, i) = 4;
                    }else if ( j == i+1){
                        A(i, i+1) = 1; 
                    } 
                    } 
                }
            

            vec3 points[size];
            for ( int i = 0; i < size; i++){
                points[i] = mCtrlPoints[i];
            }

            Eigen::MatrixXd p(5, 3);
            Eigen::MatrixXd pPrime(5, 3); // slopes for each control point
            vec3 v[size];   
            for (int i = 0; i < size; i++){
                if (i == 0 || i == size-1){
                    v[i] = getClampDirection();
                }else{
                    v[i] = 3.0f * (points[i+1] - points[i-1]);
                }
            }
            for (int i = 0; i < size; i++){
                p(i, 0) = v[i].x;
                p(i, 1) = v[i].y;
                p(i, 2) = v[i].z;
            }
        
            pPrime = A.inverse() * p;
            for (int i = 0; i < 5; i++){
                mCtrlPoints.push_back(vec3(pPrime(i, 0), pPrime(i, 1), pPrime(i, 2)));
                //std::cout << "slope " << i << " = " << pPrime(i,0 ) << " " << pPrime(i,1) << std::endl;
            }
        }else{//hermite example in ~/classexample
        
        MatrixXd A(size, size);
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                A(i, j) = 0;
                if (i == 0 && j == 0){
                    A(i, j) = 2;
                }else if (i == 0 && j == 1){
                    A(i, j) = 1;
                }else if (i == size-1 && j == size-2){
                    A(i, j) = 1;
                }else if (i == size-1 && j == size-1){
                    A(i, j) = 2;
                }else if ( j == i - 1){
                    A(i, i-1) = 1;
                }else if ( j == i){
                    A(i, i) = 4;
                }else if ( j == i+1){
                    A(i, i+1) = 1; 
                }
            }
        }
        //cout << A;

        vec3 points[size];
        for ( int i = 0; i < size; i++){
            points[i] = mCtrlPoints[i];
        }
            
        // Solve the system of linear equations
        Eigen::MatrixXd p(size, 3);
        Eigen::MatrixXd pPrime(size, 3); // slopes for each control point
        vec3 v[size];   
        for (int i = 0; i < size; i++){
            if (i == 0){
                v[i] = 3.0f * (points[1] - points[0]);
            }else if (i == size-1){
                v[i] = 3.0f * (points[size-1] - points[size-2]);
            }else{
                v[i] = 3.0f * (points[i+1] - points[i-1]);
            }
        }
        for (int i = 0; i < size; i++){
            p(i, 0) = v[i].x;
            p(i, 1) = v[i].y;
            p(i, 2) = v[i].z;
        }
        
        pPrime = A.inverse() * p;
        for (int i = 0; i < 5; i++){
            mCtrlPoints.push_back(vec3(pPrime(i, 0), pPrime(i, 1), pPrime(i, 2)));
            //std::cout << "slope " << i << " = " << pPrime(i,0 ) << " " << pPrime(i,1) << std::endl;
        }
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
