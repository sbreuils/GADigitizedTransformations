

#ifndef GADIGITALTRANSFO_GADIGITIZEDROTATION_H
#define GADIGITALTRANSFO_GADIGITIZEDROTATION_H

#include <klein/klein.hpp>
#include <e3ga/Mvec.hpp>

class GADigitizedTransformation {
 public:
  virtual ~GADigitizedTransformation(){};
  virtual kln::point operator()( const kln::point & p ) const = 0;
};


/// functor defining digitized rotations in the plane
class GADigitizedRotation : public GADigitizedTransformation
{
public:

    // digitized rotation init with the rotor
    GADigitizedRotation (const double& angle)
    {
        _q = kln::rotor((float)angle, 0.0, 0.0, 1.0);
    }


    inline
    kln::point operator()( const kln::point & p ) const override
    {
        kln::point pout_real= _q(p);
        kln::point pout_inte = kln::point(round(pout_real.x()),round(pout_real.y()),round(pout_real.z()));

        return pout_inte;
    }

private:
    kln::rotor _q;
};

/// functor defining digitized reflection defining a normal vector
class GADigitizedReflectionNormalVector : public GADigitizedTransformation
{
public:

    // digitized reflection init with normal vector coordinates
    GADigitizedReflectionNormalVector (const double& x, const double& y, const double& z)
    {
        _m[e3ga::E1] = x;
        _m[e3ga::E2] = y;
        _m[e3ga::E3] = z;
    }

    // digitized reflection init with normal vector coordinates
    GADigitizedReflectionNormalVector (const kln::point & mKlein)
    {
        _m[e3ga::E1] = mKlein.x();
        _m[e3ga::E2] = mKlein.y();
        _m[e3ga::E3] = mKlein.z();
    }

    inline
    kln::point operator()( const kln::point & p ) const override
    {
        e3ga::Mvec<double> pt;
        pt[e3ga::E1] = p.x();
        pt[e3ga::E2] = p.y();
        pt[e3ga::E3] = p.z();
        e3ga::Mvec<double> p_reflected = (-_m*pt)*_m.inv();
        kln::point pout_inte = kln::point(round(p_reflected[e3ga::E1]),round(p_reflected[e3ga::E2]),round(p_reflected[e3ga::E3]));
        return pout_inte;
    }

private:
    e3ga::Mvec<double> _m;
};


/// functor defining digitized reflection through a plane
class GADigitizedReflection : public GADigitizedTransformation
{
public:

    // digitized reflection init with normal vector coordinates
    GADigitizedReflection (const kln::plane& pl_in )
    {
        float norm = sqrt(pl_in.x()*pl_in.x() + pl_in.y()*pl_in.y() + pl_in.z()*pl_in.z());
        _plane = kln::plane(pl_in.x()/norm,pl_in.y()/norm,pl_in.z()/norm,0.0) ; // pass through origin
    }

    inline
    kln::point operator()( const kln::point & p ) const override
    {
        kln::point p_reflected = _plane(p);
        kln::point pout_inte = kln::point(round(p_reflected.x()),round(p_reflected.y()),round(p_reflected.z()));
        return pout_inte;
    }

private:
    kln::plane _plane;
};



#endif //GADIGITALTRANSFO_GADIGITIZEDROTATION_H
