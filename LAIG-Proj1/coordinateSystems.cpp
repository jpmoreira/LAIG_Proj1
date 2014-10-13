//
//  coordinateSystems.cpp
//  CGRA-1
//
//  Created by José Pedro Moreira on 17/03/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#include "coordinateSystems.h"

#define _USE_MATH_DEFINES
#include <math.h>



CartesianPoint cylindricalToCartesian(CylindricalPoint * cilPt){
    
    CartesianPoint pt;
    pt.z=cilPt->r*cos(cilPt->rho*M_PI/180.);
    pt.x=cilPt->r*sin(cilPt->rho*M_PI/180.);
    pt.y=cilPt->y;
    
    return pt;
}
CylindricalPoint cartesianToCylindrical(CartesianPoint *cartPt){
    
    CylindricalPoint pt;
    pt.y=cartPt->y;
    pt.r=sqrt(cartPt->x*cartPt->x+cartPt->z*cartPt->z);
    pt.rho=atan(cartPt->x/cartPt->z)*180./M_PI;
    return pt;
    
    
}



CartesianPoint sphericalToCartesian(SphericalPoint * sphPt){

    CartesianPoint pt;
    pt.z=sphPt->r*sin(sphPt->phy*M_PI/180.)*cos(sphPt->rho*M_PI/180.);
    pt.x=sphPt->r*sin(sphPt->phy*M_PI/180.)*sin(sphPt->rho*M_PI/180.);
    pt.y=sphPt->r*cos(sphPt->phy*M_PI/180.);
    
    return pt;

}
SphericalPoint cartesianToSpherical(CartesianPoint * cartPt){
    
    SphericalPoint pt;
    pt.r=sqrt(cartPt->x*cartPt->x+cartPt->y*cartPt->y+cartPt->z*cartPt->z);
    pt.phy=acos(cartPt->y/pt.r)*180.0/M_PI;
    pt.rho=atan(cartPt->x/pt.r)*180.0/M_PI;
    
    return pt;

}

