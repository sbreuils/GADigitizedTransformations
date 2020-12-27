//
// Created by Stéphane Breuils on 2020/12/24.
//

#ifndef GADIGITALTRANSFO_GAPIXELTRANSFORMATION_H
#define GADIGITALTRANSFO_GAPIXELTRANSFORMATION_H

#include "scene.h"
#include "GADigitizedRotation.h"

/// functor defining ga transformation of pixels
class GAPixelTransformation
{
public:

    // a reflection can be defined from the normal vector (consider that the hyperplane passes through the origin)
    // parameters have to be a transformation
//    GAPixelTransformation (const GADigitizedTransformation& transfo):_gaDigitizedTransfo(transfo)
//    {
//    }
    virtual ~GAPixelTransformation(){};

    virtual GADigitizedTransformation* init() const = 0;

    inline
    GATriplet operator()( const GATriplet & pix ) const
    {
        // GADigitizedRotation transfo(_param);
        GADigitizedTransformation* GadigitizedTranfo = this->init(); // create a digitized transformation
        GATriplet pixel_out = {(*GadigitizedTranfo)(pix.klnPt),pix.val};
        delete GadigitizedTranfo;
        return pixel_out;
    }

private:
//    GADigitizedTransformation* _gaDigitizedTransfo;
};


class GADigitizedRotationCreator : public GAPixelTransformation{
public:
    explicit GADigitizedRotationCreator(double angle):_angle(angle){}

    GADigitizedTransformation* init() const override{
        return new GADigitizedRotation(_angle);
    }
private:
    double _angle;
};


#endif //GADIGITALTRANSFO_GAPIXELTRANSFORMATION_H
