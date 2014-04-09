//
//  NRCamera.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRCamera_h
#define NanoRay_C_NRCamera_h

#import "NRVector.h"
#import "NRRay.h"

typedef struct _NRCamera {
    NRVector position;
    NRVector g;
    NRVector u;
    NRVector v;
    CGFloat lens_radius;
    CGFloat distance;
} NRCamera;

FOUNDATION_STATIC_INLINE NRCamera NRMakeCamera(NRVector pos, NRVector lookAt, NRVector up, CGFloat angle, CGFloat aspect, CGFloat distance, CGFloat aperture) {
    NRCamera c;
    
    CGFloat temp_tan = tan((angle/2.0)*M_PI/180.0);
    
    c.position = pos;
    c.g = NRNormalizeVector(NRMinusVectors(lookAt, pos));
    c.u = NRNormalizeVector(NRCrossVectors(c.g, up));
    c.v = NRNormalizeVector(NRCrossVectors(c.u, c.g));
    c.u = NRMultiplyVector(c.u, temp_tan);
    c.v = NRMultiplyVector(c.v, temp_tan/aspect);
    
    c.lens_radius = aperture / 2.0;
    c.distance = distance;

    return c;
}

FOUNDATION_STATIC_INLINE NRRay NRCameraMakeRay(NRCamera c, CGFloat x, CGFloat y, CGFloat a, CGFloat b) {
    NRVector direction = NRAddVectors(NRAddVectors(c.g, NRMultiplyVector(c.u, x)), NRMultiplyVector(c.v, y));
//    NRNormalizeVector(direction);
//    direction = NRMultiplyVector(direction, c.distance);
//    
//    NRVector lensU = NRMultiplyVector(c.u, a * c.lens_radius);
//    NRVector lensV = NRMultiplyVector(c.v, b * c.lens_radius);
//    
//    NRVector origin = NRAddVectors(c.position, NRAddVectors(lensU, lensV));
//    direction = NRMinusVectors(direction, NRAddVectors(lensU, lensV));
//	    
//    return NRMakeRay(origin, direction);
    return NRMakeRay(c.position, direction);
}


#endif
