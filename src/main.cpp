
#include <iostream>
#include <algorithm>

#include <klein/klein.hpp>
#include <vector>


/// Create a rotor representing a pi/2 rotation about the z-axis
/// Normalization is done automatically
kln::rotor R{M_PI * 0.5f, 0.f, 0.f, 1.f};




/// Create a translator that represents a translation of 1 unit
/// in the yz-direction. Normalization is done automatically.
kln::translator t{1.f, 0.f, 1.f, 1.f};





/// interpolation between two points and rotation versors with a parameter t in the range [0 , 1]
kln::motor interpolateRotation(kln::rotor a, kln::rotor b, float w){
    // delta rotor
    kln::line deltaRot = log(b*(~a));

    // interpolation
    deltaRot *= w;

    kln::motor Rw = exp(deltaRot)*a;

    return Rw;


}


/// Blend between two motors with a parameter t in the range [0, 1]
kln::motor blend_motors(kln::motor const& a, kln::motor const& b, float t)
{
    // Starting from a, the motor needed to get to b is b * ~a.
    // To perform this motion continuously, we can take the principal
    // branch of the logarithm of b * ~a, and subdivide it before
    // re-exponentiating it to produce a motor again.

    // In practice, this should be cached whenever possible.
    kln::line motor_step = log(b * ~a);

    // exp(log(m)) = exp(t*log(m) + (1 - t)*log(m))
    // = exp(t*(log(m))) * exp((1 - t)*log(m))
    motor_step *= t;

    // The exponential of the step here can be cached if the blend occurs
    // with fixed steps toward the final motor. Compose the interpolated
    // result with the start motor to produce the intermediate blended
    // motor.
    return exp(motor_step) * a;
}


/// define the scenes at time t and t+1
/// N is the number of points
std::vector<std::vector<kln::point>> geometryScene(const int N){

    std::vector<kln::point> sceneAtTimeT;
    for(unsigned int i=0;i<N;++i){
        sceneAtTimeT.emplace_back(kln::point( (float)i,0.0,0.0));
    }

    std::vector<kln::point> sceneAtTimeTpp;
    for(unsigned int i=0;i<N;++i){
        sceneAtTimeT.emplace_back(kln::point( 0.0, (float)i,0.0));
    }

    return {sceneAtTimeT,sceneAtTimeTpp};
}




int main(){


    std::cout << "start transformation example." << std::endl;

    // define a point
    kln::point pti{1,0,0};
    std::cout<< "pti = (" << pti.x() << ", " <<pti.y() << ", " <<pti.z() << ")" <<std::endl;

    // transform the object about the z axis
    kln::rotor Ro{0.0, 0.f, 0.f, -1.f}; // identity rotation
    kln::rotor Ri{M_PI * 0.5f, 0.f, 0.f, -1.f};
    kln::point ptr = Ro(pti);
    std::cout<< "ptr = (" << ptr.x() << ", " <<ptr.y() << ", " <<ptr.z() << ")" <<std::endl;

    // transform the object with a translation of vector (1,1,0)
    kln::translator Ti{static_cast<float>(sqrt(2.0)),1.0,1.0,0.0};
    kln::point ptrt = Ti(ptr);

    std::cout<< "ptrt = (" << ptrt.x() << ", " <<ptrt.y() << ", " <<ptrt.z() << ")" <<std::endl;


    // interpolate, at a weight of w = 0.5, the rotation rotor
    float w = 0.5;
    kln::motor rot_i = interpolateRotation(Ro, Ri, w);
    kln::point p_interp = rot_i(pti);

    std::cout << "interpolated point is (" << p_interp.x() << ", " <<p_interp.y() << ", " <<p_interp.z() << ")" <<std::endl;

	return 0;
}