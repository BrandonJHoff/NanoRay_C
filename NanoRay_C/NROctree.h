//
//  NROctree.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/28/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NROctree_h
#define NanoRay_C_NROctree_h

#import "NRVector.h"
#import "NRHitRecord.h"
#import "NRVoxel.h"
#import "NRPoint.h"

struct _NRLambertianMaterial;

typedef struct _NROctree {
    NRVoxel *root;
    NRVoxel **lights;
    int lightCount;
    int maxLightCount;
    int maxDepth;
    CGFloat C;
} NROctree;

FOUNDATION_STATIC_INLINE NROctree * NRMakeOctree(NRVector position, CGFloat size) {
    NROctree *o = malloc(sizeof(NROctree));
    o->root = NRMakeVoxel(position, size, NRMakeVector(0, 0, 0), false);
    o->maxDepth = 0;
    o->lightCount = 0;
    o->maxLightCount = 0;
    return o;
}

FOUNDATION_STATIC_INLINE int NROctreePointInsideChild(NRVoxel *voxel, NRPoint *point) {
    CGFloat child_size = voxel->size / 2.0;
    
    if((voxel->position.x - voxel->size) <= point->position.x && voxel->position.x >= point->position.x
       && (voxel->position.y - voxel->size) <= point->position.y && voxel->position.y >= point->position.y
       && (voxel->position.z - voxel->size) <= point->position.z && voxel->position.z >= point->position.z){
        if(voxel->children[0] == nil){
            voxel->children[0] = NRMakeVoxel(NRMakeVector(voxel->position.x - child_size, voxel->position.y - child_size, voxel->position.z - child_size), child_size, NRMakeVector(0, 0, 0), false);
        }
        return 0;
    }
    if((voxel->position.x - voxel->size) <= point->position.x && voxel->position.x >= point->position.x
       && (voxel->position.y - voxel->size) <= point->position.y && voxel->position.y >= point->position.y
       && voxel->position.z <= point->position.z && (voxel->position.z + voxel->size) >= point->position.z){
        if(voxel->children[1] == nil){
            voxel->children[1] = NRMakeVoxel(NRMakeVector(voxel->position.x - child_size, voxel->position.y - child_size, voxel->position.z + child_size), child_size, NRMakeVector(0, 0, 0), false);
        }
        return 1;
    }
    if((voxel->position.x - voxel->size) <= point->position.x && voxel->position.x >= point->position.x
       && voxel->position.y <= point->position.y && (voxel->position.y + voxel->size) >= point->position.y
       && (voxel->position.z - voxel->size) <= point->position.z && voxel->position.z >= point->position.z){
        if(voxel->children[2] == nil){
            voxel->children[2] = NRMakeVoxel(NRMakeVector(voxel->position.x - child_size, voxel->position.y + child_size, voxel->position.z - child_size), child_size, NRMakeVector(0, 0, 0), false);
        }
        return 2;
    }
    if((voxel->position.x - voxel->size) <= point->position.x && voxel->position.x >= point->position.x
       && voxel->position.y <= point->position.y && (voxel->position.y + voxel->size) >= point->position.y
       && voxel->position.z <= point->position.z && (voxel->position.z + voxel->size) >= point->position.z){
        if(voxel->children[3] == nil){
            voxel->children[3] = NRMakeVoxel(NRMakeVector(voxel->position.x - child_size, voxel->position.y + child_size, voxel->position.z + child_size), child_size, NRMakeVector(0, 0, 0), false);
        }
        return 3;
    }
    if(voxel->position.x <= point->position.x && (voxel->position.x + voxel->size) >= point->position.x
       && (voxel->position.y - voxel->size) <= point->position.y && voxel->position.y >= point->position.y
       && (voxel->position.z - voxel->size) <= point->position.z && voxel->position.z >= point->position.z){
        if(voxel->children[4] == nil){
            voxel->children[4] = NRMakeVoxel(NRMakeVector(voxel->position.x + child_size, voxel->position.y - child_size, voxel->position.z - child_size), child_size, NRMakeVector(0, 0, 0), false);
        }
        return 4;
    }
    if(voxel->position.x <= point->position.x && (voxel->position.x + voxel->size) >= point->position.x
       && (voxel->position.y - voxel->size) <= point->position.y && voxel->position.y >= point->position.y
       && voxel->position.z <= point->position.z && (voxel->position.z + voxel->size) >= point->position.z){
        if(voxel->children[5] == nil){
            voxel->children[5] = NRMakeVoxel(NRMakeVector(voxel->position.x + child_size, voxel->position.y - child_size, voxel->position.z + child_size), child_size, NRMakeVector(0, 0, 0), false);
        }
        return 5;
    }
    if(voxel->position.x <= point->position.x && (voxel->position.x + voxel->size) >= point->position.x
       && voxel->position.y <= point->position.y && (voxel->position.y + voxel->size) >= point->position.y
       && (voxel->position.z - voxel->size) <= point->position.z && voxel->position.z >= point->position.z){
        if(voxel->children[6] == nil){
            voxel->children[6] = NRMakeVoxel(NRMakeVector(voxel->position.x + child_size, voxel->position.y + child_size, voxel->position.z - child_size), child_size, NRMakeVector(0, 0, 0), false);
        }
        return 6;
    }
    if(voxel->position.x <= point->position.x && (voxel->position.x + voxel->size) >= point->position.x
       && voxel->position.y <= point->position.y && (voxel->position.y + voxel->size) >= point->position.y
       && voxel->position.z <= point->position.z && (voxel->position.z + voxel->size) >= point->position.z){
        if(voxel->children[7] == nil){
            voxel->children[7] = NRMakeVoxel(NRMakeVector(voxel->position.x + child_size, voxel->position.y + child_size, voxel->position.z + child_size), child_size, NRMakeVector(0, 0, 0), false);
        }
        return 7;
    }
    
    return -1;
}

FOUNDATION_STATIC_INLINE void NROctreeAddLight(NROctree *o, NRVoxel *light) {
    if(o->maxLightCount == 0){
        o->lights = malloc((1000)*sizeof(NRVoxel*));
        o->maxLightCount = 1000;
    }
    
    if(o->lightCount == o->maxLightCount){
        NRVoxel **lights = malloc((o->lightCount+1000)*sizeof(NRVoxel*));
        for(int i = 0; i < o->lightCount; i++){
            lights[i] = o->lights[i];
        }
        o->lights = lights;
        o->maxLightCount = o->lightCount + 1000;
    }
    
    o->lights[o->lightCount] = light;
    o->lightCount = o->lightCount + 1;
}

FOUNDATION_STATIC_INLINE void NROctreeRemoveLight(NROctree *o, NRVoxel *light) {
    for(int i = 0; i < o->lightCount; i++){
        if(NRVoxelsEqual(o->lights[i], light)){
            NRVoxel **lights = malloc((o->lightCount)*sizeof(NRVoxel*));
            for(int j = 0; j < i; j++){
                lights[j] = o->lights[j];
            }
            for(int j = i + 1; j < o->lightCount; j++){
                lights[j - 1] = o->lights[j];
            }
            o->lights = lights;
            o->maxLightCount = o->lightCount;
            o->lightCount = o->lightCount - 1;
            return;
        }
    }
}


FOUNDATION_STATIC_INLINE bool NROctreeAddPoint(NROctree *o, NRVoxel *voxel, NRPoint *point) {
    NRVector min = NRMinusVector(voxel->position, voxel->size);
    NRVector max = NRAddVector(voxel->position, voxel->size);
    
    if(min.x <= point->position.x && max.x >= point->position.x && min.y <= point->position.y && max.y >= point->position.y && min.z <= point->position.z && max.z >= point->position.z){
        
        if(voxel->totalPoints == 0){
            voxel->point = point;
            if(point->isLight){
                NROctreeAddLight(o, voxel);
            }
        }
        else{
                 
            if(voxel->totalPoints == 1){
                if(voxel->point->position.x == point->position.x
                   && voxel->point->position.y == point->position.y
                   && voxel->point->position.z == point->position.z){
                    return false;
                }
                int child_index = NROctreePointInsideChild(voxel, voxel->point);
                if(child_index >= 0){
                    if(voxel->point->isLight){
                        NROctreeRemoveLight(o, voxel);
                    }
                    NROctreeAddPoint(o, voxel->children[child_index], voxel->point);
                    voxel->point = nil;
                }
            }
            
            int child_index = NROctreePointInsideChild(voxel, point);
            if(child_index >= 0){
                NROctreeAddPoint(o, voxel->children[child_index], point);
            }
        }
        
        if(!voxel->isLight && point->isLight){
            voxel->isLight = point->isLight;
        }
        NRVoxelUpdateColor(voxel, point->color);
        voxel->totalPoints++;
        return true;
    }
    
    return false;
}


FOUNDATION_STATIC_INLINE bool NRIntersectOctree(NRVoxel *voxel, NRRay ray, NRHitRecord *hitRecord, int maxDepth, int currentDepth, CGFloat C) {
    if(voxel == nil || voxel->totalPoints == 0){
        return false;
    }
    
    CGFloat t = NRIntersectVoxel(voxel, ray);
    
    if(currentDepth >= maxDepth || voxel->totalPoints == 1 || voxel->size <= t*C){
        return NRRecordHit(hitRecord, t, voxel);
    }
    
    bool hasHit = false;
    
    if(t > 0 && t < hitRecord->t){
        for(int i = 0; i < 8; i++){
            if(voxel->children[i] != nil && voxel->children[i]->totalPoints > 0){
                if(NRIntersectOctree(voxel->children[i], ray, hitRecord, maxDepth, currentDepth + 1, C)){
                    hasHit = true;
                }
            }
        }
    }
    
    return hasHit;
}

//FOUNDATION_STATIC_INLINE void NRDeleteOctree(NROctree *o) {
//    NRDeleteVoxel(o->root);
//}


#endif
