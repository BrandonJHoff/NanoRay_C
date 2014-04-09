//
//  NRVector.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRVector_h
#define NanoRay_C_NRVector_h

typedef struct _NRVector {
    CGFloat x;
    CGFloat y;
    CGFloat z;
} NRVector;

FOUNDATION_STATIC_INLINE NRVector NRMakeVector(CGFloat x, CGFloat y, CGFloat z) {
    NRVector v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

FOUNDATION_STATIC_INLINE NRVector NRNormalizeVector(NRVector v) {
    if(v.x == 0 && v.y == 0 && v.z == 0)
        return v;
    CGFloat length = 1 / sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    v.x *= length;
    v.y *= length;
    v.z *= length;
    return v;
}

FOUNDATION_STATIC_INLINE NRVector NRNegateVector(NRVector v) {
    v.x = -v.x;
    v.y = -v.y;
    v.z = -v.z;
    return v;
}


FOUNDATION_STATIC_INLINE NRVector NRAddVectors(NRVector v1, NRVector v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

FOUNDATION_STATIC_INLINE NRVector NRAddVector(NRVector v, CGFloat t) {
    v.x += t;
    v.y += t;
    v.z += t;
    return v;
}

FOUNDATION_STATIC_INLINE NRVector NRMinusVectors(NRVector v1, NRVector v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

FOUNDATION_STATIC_INLINE NRVector NRMinusVector(NRVector v, CGFloat t) {
    v.x -= t;
    v.y -= t;
    v.z -= t;
    return v;
}

FOUNDATION_STATIC_INLINE NRVector NRMultiplyVectors(NRVector v1, NRVector v2) {
    v1.x *= v2.x;
    v1.y *= v2.y;
    v1.z *= v2.z;
    return v1;
}

FOUNDATION_STATIC_INLINE NRVector NRMultiplyVector(NRVector v, CGFloat t) {
    v.x *= t;
    v.y *= t;
    v.z *= t;
    return v;
}

FOUNDATION_STATIC_INLINE NRVector NRCrossVectors(NRVector v1, NRVector v2) {
    NRVector v;
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return v;
}

FOUNDATION_STATIC_INLINE CGFloat NRDotVectors(NRVector v1, NRVector v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

FOUNDATION_STATIC_INLINE bool NRVectorsEqual(NRVector v1, NRVector v2) {
    if(v1.x == v2.x && v1.y == v2.y && v1.z == v2.z){
        return true;
    }
    return false;
}

#endif
