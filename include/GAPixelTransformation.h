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


    virtual ~GAPixelTransformation(){};

    virtual GADigitizedTransformation* init() const = 0;

    inline
    GATriplet operator()( const GATriplet & pix ) const
    {
        GADigitizedTransformation* GadigitizedTranfo = this->init(); // create a digitized transformation
        GATriplet pixel_out = {(*GadigitizedTranfo)(pix.klnPt),pix.val};
        delete GadigitizedTranfo;
        return pixel_out;
    }
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
