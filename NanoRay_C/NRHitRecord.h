//
//  NRHitRecord.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRHitRecord_h
#define NanoRay_C_NRHitRecord_h

#import "NRRay.h"
#import "NRVector.h"
#import "NRVoxel.h"

typedef struct _NRHitRecord {
    CGFloat t;
    NRVoxel *voxel;
    NRRay *ray;
} NRHitRecord;

FOUNDATION_STATIC_INLINE NRHitRecord NRMakeHitRecord() {
    NRHitRecord hr;
    hr.t = CGFLOAT_MAX;
    hr.voxel = nil;
    hr.ray = nil;
    return hr;
}

FOUNDATION_STATIC_INLINE bool NRRecordHit(NRHitRecord *hr, CGFloat t, NRVoxel *voxel) {
    if((t > .001) && (t < hr->t)) {
		hr->t = t;
        hr->voxel = voxel;
        return true;
	}
	return false;
}

FOUNDATION_STATIC_INLINE NRHitRecord NRResetHitRecord(NRHitRecord *hr) {
    hr->t = CGFLOAT_MAX;
    hr->voxel = nil;
    hr->ray = nil;
    return *hr;
}

//struct _NRBox;
//
//typedef struct _NRHitRecord {
//    CGFloat t;
//    struct _NRBox *box;
//    NRRay *ray;
//} NRHitRecord;
//
//FOUNDATION_STATIC_INLINE NRHitRecord NRMakeHitRecord() {
//    NRHitRecord hr;
//    hr.t = CGFLOAT_MAX;
//    hr.box = nil;
//    hr.ray = nil;
//    return hr;
//}
//
//FOUNDATION_STATIC_INLINE bool NRRecordHit(NRHitRecord *hr, CGFloat t, struct _NRBox *box) {
//    if((t > .001) && (t < hr->t)) {
//		hr->t = t;
//        hr->box = box;
//        return true;
//	}
//	return false;
//}
//
//FOUNDATION_STATIC_INLINE NRHitRecord NRResetHitRecord(NRHitRecord *hr) {
//    hr->t = CGFLOAT_MAX;
//    hr->box = nil;
//    hr->ray = nil;
//    return *hr;
//}

#endif
