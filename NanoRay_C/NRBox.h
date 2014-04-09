//
//  NRBox.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRBox_h
#define NanoRay_C_NRBox_h

#import "NRVector.h"
#import "NRRay.h"
#import "NRHitRecord.h"

struct _NRLambertianMaterial;

typedef struct _NRBox {
    NRVector min;
    NRVector max;
    struct _NRLambertianMaterial *material;
} NRBox;

FOUNDATION_STATIC_INLINE NRBox NRMakeBox(NRVector min, NRVector max, struct _NRLambertianMaterial *material) {
    NRBox b;
    b.min = min;
    b.max = max;
    b.material = material;
    return b;
}

FOUNDATION_STATIC_INLINE bool NRIntersectBox(NRBox *box, NRRay ray, NRHitRecord *hitRecord) {
    bool hasHit = false;
	CGFloat tmin, tmax, tymin, tymax, tzmin, tzmax;
    
    if (ray.direction.x >= 0)
	{
		tmin = (box->min.x - ray.origin.x) / ray.direction.x;
		tmax = (box->max.x - ray.origin.x) / ray.direction.x;
	}
	else
	{
		tmin = (box->max.x - ray.origin.x) / ray.direction.x;
		tmax = (box->min.x - ray.origin.x) / ray.direction.x;
	}
    
	if (ray.direction.y >= 0)
	{
		tymin = (box->min.y - ray.origin.y) / ray.direction.y;
		tymax = (box->max.y - ray.origin.y) / ray.direction.y;
	}
	else
	{
		tymin = (box->max.y - ray.origin.y) / ray.direction.y;
		tymax = (box->min.y - ray.origin.y) / ray.direction.y;
	}
    
	if ((tmin > tymax) || (tymin > tmax))
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
    
	if (ray.direction.z >= 0)
	{
		tzmin = (box->min.z - ray.origin.z) / ray.direction.z;
		tzmax = (box->max.z - ray.origin.z) / ray.direction.z;
	}
	else
	{
		tzmin = (box->max.z - ray.origin.z) / ray.direction.z;
		tzmax = (box->min.z - ray.origin.z) / ray.direction.z;
	}
    
	if ( (tmin > tzmax) || (tzmin > tmax) )
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
    
    if(NRRecordHit(hitRecord, tmin, box))
        hasHit = true;
    if(NRRecordHit(hitRecord, tmax, box))
        hasHit = true;
    
	return hasHit;
}

FOUNDATION_STATIC_INLINE NRVector NRBoxGetNormal(NRBox box, NRVector p) {
    CGFloat epsilon = .001;
    
    if(fabs(box.min.x - p.x) < epsilon)
        return NRMakeVector(-1, 0, 0);
	else if(fabs(box.max.x - p.x) < epsilon)
        return NRMakeVector(1, 0, 0);
	else if(fabs(box.min.y - p.y) < epsilon)
        return NRMakeVector(0, -1, 0);
	else if(fabs(box.max.y - p.y) < epsilon)
        return NRMakeVector(0, 1, 0);
	else if(fabs(box.min.z - p.z) < epsilon)
        return NRMakeVector(0, 0, -1);
	else
        return NRMakeVector(0, 0, 1);
}


#endif
