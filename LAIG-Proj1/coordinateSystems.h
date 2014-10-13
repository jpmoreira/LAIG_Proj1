//
//  coordinateSystems.h
//  CGRA-1
//
//  Created by José Pedro Moreira on 17/03/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __CGRA_1__coordinateSystems__
#define __CGRA_1__coordinateSystems__

#include <iostream>

#endif /* defined(__CGRA_1__coordinateSystems__) */



typedef struct CartesianPoint {
    double x;
    double y;
    double z;
    
} CartesianPoint;


typedef struct CylindricalPoint {
    double rho;
    double r;
    double y;
    
    
} CylindricalPoint;

typedef struct SphericalPoint{

    double r;
    double rho;
    double phy;

} SphericalPoint;




CartesianPoint cylindricalToCartesian(CylindricalPoint * cilPt);
CylindricalPoint cartesianToCylindrical(CartesianPoint *cartPt);

CartesianPoint sphericalToCartesian(SphericalPoint * sphPt);
SphericalPoint cartesianToSpherical(CartesianPoint * cartPt);