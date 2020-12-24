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
    GAPixelTransformation (const double& param):_param(param)
    {
    }


    inline
    GATriplet operator()( const GATriplet & pix ) const
    {
        GADigitizedRotation transfo(_param);
        GATriplet pixel_out = {transfo(pix.klnPt),pix.val};

        return pixel_out;
    }

private:
    double _param;
};


#endif //GADIGITALTRANSFO_GAPIXELTRANSFORMATION_H
