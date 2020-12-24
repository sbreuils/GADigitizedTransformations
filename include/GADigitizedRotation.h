

#ifndef GADIGITALTRANSFO_GADIGITIZEDROTATION_H
#define GADIGITALTRANSFO_GADIGITIZEDROTATION_H

#include <klein/klein.hpp>

/// functor defining digitized rotations in the plane
class GADigitizedRotation
{
public:

    // digitized rotation init with the rotor
    GADigitizedRotation (const double& angle)
    {
        _q = kln::rotor((float)angle, 0.0, 0.0, 1.0);
    }


    inline
    kln::point operator()( const kln::point & p ) const
    {
        kln::point pout_real= _q(p);
        kln::point pout_inte = kln::point(round(pout_real.x()),round(pout_real.y()),0.0);

        return pout_inte;
    }

private:
    kln::rotor _q;
};



#endif //GADIGITALTRANSFO_GADIGITIZEDROTATION_H
