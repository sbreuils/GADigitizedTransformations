
#include <iostream>
#include <algorithm>

#include <vector>

#include "../include/scene.h"

/// Create a rotor representing a pi/2 rotation about the z-axis
/// Normalization is done automatically
kln::rotor R{M_PI * 0.5f, 0.f, 0.f, 1.f};




/// Create a translator that represents a translation of 1 unit
/// in the yz-direction. Normalization is done automatically.
kln::translator t{1.f, 0.f, 1.f, 1.f};






int main(){
    // define the scene
    


    // apply the digitized transformation
    // todo




    // write the resulting pixels into an image




	return 0;
}