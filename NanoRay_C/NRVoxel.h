//
//  NRVoxel.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/30/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRVoxel_h
#define NanoRay_C_NRVoxel_h

#import "NRVector.h"
#import "NRPoint.h"
#import "NRRay.h"

typedef struct _NRVoxel {
    bool isLight;
    NRVector color;
    NRVector position;
    CGFloat size;
    struct _NRVoxel *children[8];
    NRPoint *point;
    uint totalPoints;
    
} NRVoxel;

FOUNDATION_STATIC_INLINE NRVoxel * NRMakeVoxel(NRVector position, float size, NRVector color, bool isLight) {
    NRVoxel *v = malloc(sizeof(NRVoxel));
    v->isLight = isLight;
    v->position = position;
    v->size = size;
    v->color = color;
    //v->innerPoints = 0;
    v->point = nil;
    v->totalPoints = 0;
    for(int i = 0; i < 8; i++){
        v->children[i] = nil;
    }
    return v;
}

FOUNDATION_STATIC_INLINE void NRVoxelUpdateColor(NRVoxel *v, NRVector c) {
    CGFloat invTotalPoints = 1.0 / (v->totalPoints + 1);
    
    v->color.x = ((v->color.x * v->totalPoints) + c.x) * invTotalPoints;
    v->color.y = ((v->color.y * v->totalPoints) + c.y) * invTotalPoints;
    v->color.z = ((v->color.z * v->totalPoints) + c.z) * invTotalPoints;
}


FOUNDATION_STATIC_INLINE NRVector NRGetVoxelNormal(NRVoxel *v, NRVector p) {
    CGFloat epsilon = .001;
    NRVector min = NRMinusVector(v->position, v->size);
    NRVector max = NRAddVector(v->position, v->size);

    if(fabs(min.x - p.x) < epsilon)
        return NRMakeVector(-1, 0, 0);
	else if(fabs(max.x - p.x) < epsilon)
        return NRMakeVector(1, 0, 0);
	else if(fabs(min.y - p.y) < epsilon)
        return NRMakeVector(0, -1, 0);
	else if(fabs(max.y - p.y) < epsilon)
        return NRMakeVector(0, 1, 0);
	else if(fabs(min.z - p.z) < epsilon)
        return NRMakeVector(0, 0, -1);
	else
        return NRMakeVector(0, 0, 1);
}

FOUNDATION_STATIC_INLINE NRVector NRGetPointOnVoxel(NRVoxel *v) {
    NRVector min = NRMinusVector(v->position, v->size);
    NRVector max = NRAddVector(v->position, v->size);
    
    CGFloat doubleSize = v->size * 2;
    int side = arc4random_uniform(6);
    
    switch (side) {
        case 0:
            return NRMakeVector(min.x, (drand48() * doubleSize) + min.y, (drand48() * doubleSize) + min.z);
            break;
        case 1:
            return NRMakeVector(max.x, (drand48() * doubleSize) + min.y, (drand48() * doubleSize) + min.z);
            break;
        case 2:
            return NRMakeVector((drand48() * doubleSize) + min.x, min.y, (drand48() * doubleSize) + min.z);
            break;
        case 3:
            return NRMakeVector((drand48() * doubleSize) + min.x, max.y, (drand48() * doubleSize) + min.z);
            break;
        case 4:
            return NRMakeVector((drand48() * doubleSize) + min.x, (drand48() * doubleSize) + min.y, min.z);
            break;
        default:
            return NRMakeVector((drand48() * doubleSize) + min.x, (drand48() * doubleSize) + min.y, max.z);
            break;
    }
}


FOUNDATION_STATIC_INLINE CGFloat NRIntersectVoxel(NRVoxel *voxel, NRRay ray) {
    CGFloat t = -1;
	CGFloat tmin, tmax, tymin, tymax, tzmin, tzmax;
    NRVector min = NRMinusVector(voxel->position, voxel->size);
    NRVector max = NRAddVector(voxel->position, voxel->size);
    
    if (ray.direction.x >= 0){
		tmin = (min.x - ray.origin.x) * ray.inverse_direction.x;
		tmax = (max.x - ray.origin.x) * ray.inverse_direction.x;
	}
	else{
		tmin = (max.x - ray.origin.x) * ray.inverse_direction.x;
		tmax = (min.x - ray.origin.x) * ray.inverse_direction.x;
	}
    
	if (ray.direction.y >= 0){
		tymin = (min.y - ray.origin.y) * ray.inverse_direction.y;
		tymax = (max.y - ray.origin.y) * ray.inverse_direction.y;
	}
	else{
		tymin = (max.y - ray.origin.y) * ray.inverse_direction.y;
		tymax = (min.y - ray.origin.y) * ray.inverse_direction.y;
	}
    
	if ((tmin > tymax) || (tymin > tmax))
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
    
	if (ray.direction.z >= 0){
		tzmin = (min.z - ray.origin.z) * ray.inverse_direction.z;
		tzmax = (max.z - ray.origin.z) * ray.inverse_direction.z;
	}
	else{
		tzmin = (max.z - ray.origin.z) * ray.inverse_direction.z;
		tzmax = (min.z - ray.origin.z) * ray.inverse_direction.z;
	}
    
	if ((tmin > tzmax) || (tzmin > tmax))
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
    
    if(tmin > .001 && tmin <= tmax){
        t = tmin;
    }
    else if(tmax > .001){
        t = tmax;
    }
    
    return t;
}


FOUNDATION_STATIC_INLINE bool NRVoxelsEqual(NRVoxel *v1, NRVoxel *v2) {
    if(v1->isLight != v2->isLight){
        return false;
    }
    
    if(!NRVectorsEqual(v1->color, v2->color)){
        return false;
    }
    
    if(!NRVectorsEqual(v1->position, v2->position)){
        return false;
    }
    
    if(v1->size != v2->size){
        return false;
    }
    
    return true;
}


//struct _NRLambertianMaterial;
//
//typedef struct _NRVoxel {
//    char type;
//    bool isLight;
//    NRVector *color;
//    //struct _NRLambertianMaterial *material;
//    int x, y, z;
//    int size;
//    struct _NRVoxel *children[8];
//} NRVoxel;
//
//FOUNDATION_STATIC_INLINE NRVoxel * NRMakeVoxel(int x, int y, int z, int size, char type, NRVector *color, bool isLight) {
//    NRVoxel *v = malloc(sizeof(NRVoxel));
//    v->type = type;
//    v->isLight = isLight;
//    v->x = x;
//    v->y = y;
//    v->z = z;
//    v->size = size;
//    v->color = color;
//    for(int i = 0; i < 8; i++){
//        v->children[i] = nil;
//    }
//    return v;
//}
//
//FOUNDATION_STATIC_INLINE NRVector NRGetVoxelNormal(NRVoxel *v, NRVector p) {
//    CGFloat epsilon = .001;
//    NRVector min = NRMakeVector(v->x, v->y, v->z);
//    NRVector max = NRAddVector(min, v->size);
//    
//    if(fabs(min.x - p.x) < epsilon)
//        return NRMakeVector(-1, 0, 0);
//	else if(fabs(max.x - p.x) < epsilon)
//        return NRMakeVector(1, 0, 0);
//	else if(fabs(min.y - p.y) < epsilon)
//        return NRMakeVector(0, -1, 0);
//	else if(fabs(max.y - p.y) < epsilon)
//        return NRMakeVector(0, 1, 0);
//	else if(fabs(min.z - p.z) < epsilon)
//        return NRMakeVector(0, 0, -1);
//	else
//        return NRMakeVector(0, 0, 1);
//}
//
//
//FOUNDATION_STATIC_INLINE void NRDeleteVoxel(NRVoxel *v) {
//    free(v->color);
//    for(int i = 0; i < 8; i++){
//        if(v->children[i] != nil){
//            NRDeleteVoxel(v->children[i]);
//        }
//        free(v->children[i]);
//    }
//}


#endif
