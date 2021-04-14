
#pragma once
#include <iostream>


#include <klein/klein.hpp>
#include <vector>
#include <tuple> 

constexpr double pi = 3.14159265358979323846;


// bounds of the targeted region in the sphere (min,max lattitude and min,max longitude ) 
typedef std::tuple<float, float, float, float> TransformationDomain;


/// generate a set of transformations in a considered range, e.g. slant are considered for digitized reflections

class GATransformationsGeneration {
 public:
  virtual ~GATransformationsGeneration(){};
  // length and domain definition
  virtual std::vector<kln::plane> operator()( const int N, const TransformationDomain angleRegion) const = 0;
};

/// generation of planes for digitized reflections inside the domain defined by region 
class GAPlanesGeneration : public GATransformationsGeneration
{
public:

    inline
    std::vector<kln::plane> operator()( const int N, const TransformationDomain angleRegion ) const override
    {
        std::vector<kln::plane> planesVector;


        for(int u= 0 ; u<N ; ++u ){
            for(int v=1 ; v<N ; ++v){
                float phi = std::get<0>(angleRegion) + (std::get<1>(angleRegion) - std::get<0>(angleRegion)) * v/(N-1); //(pi/4.0) * v/(N-1); // latitude
                float theta = std::get<2>(angleRegion) + (2*std::get<3>(angleRegion) - std::get<2>(angleRegion)) * u/(N-1); //(pi/2.0) * u/(N-1); // longitude
 
                float x = cos(theta)*sin(phi);
                float y = sin(theta)*sin(phi);
                float z = cos(phi);

                // std::cout << "Plane : x="<<x<<", y="<<y<<", z="<<z<<std::endl;

                if((x+y)<=z)
                    planesVector.push_back(kln::plane(x,y,z,0.0f));

            }
        }

        // planesVector.push_back(kln::plane(-3.0, 4.0, 7.0, 0.0));
        return planesVector;
    }

};








                                    


