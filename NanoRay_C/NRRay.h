//
//  NRRay.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRRay_h
#define NanoRay_C_NRRay_h

#import "NRVector.h"

typedef struct _NRRay {
    NRVector origin;
    NRVector direction;
    NRVector inverse_direction;
} NRRay;

FOUNDATION_STATIC_INLINE NRRay NRMakeRay(NRVector o, NRVector d) {
    NRRay r;
    r.origin = o;
    r.direction = NRNormalizeVector(d);
    r.inverse_direction = NRMakeVector(1/r.direction.x, 1/r.direction.y, 1/r.direction.z);
    return r;
}

FOUNDATION_STATIC_INLINE NRVector NRGetPositionAtTime(NRRay r, CGFloat t) {
    return NRAddVectors(r.origin, NRMultiplyVector(r.direction, t));
}

FOUNDATION_STATIC_INLINE CGFloat NRGetTimeAtPosition(NRVector p1, NRVector p2) {
    CGFloat x = p2.x - p1.x;
	CGFloat y = p2.y - p1.y;
	CGFloat z = p2.z - p1.z;
	return sqrt(x*x + y*y + z*z);
}

#endif
