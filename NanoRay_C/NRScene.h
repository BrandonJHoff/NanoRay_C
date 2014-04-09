//
//  NRScene.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRScene_h
#define NanoRay_C_NRScene_h

#import "NRVector.h"
#import "NRCamera.h"
#import "NRPointLight.h"
#import "NRBox.h"
#import "NRHitRecord.h"
#import "NROctree.h"
#import "NRPoint.h"

typedef struct _NRScene {
    NROctree *octree;
    NRPoint **lights;
    int lightCount;
    NRCamera camera;
    NRVector ambient;
} NRScene;

FOUNDATION_STATIC_INLINE NRScene NRMakeScene() {
    NRScene s;
    s.lightCount = 0;
    return s;
}

FOUNDATION_STATIC_INLINE void NRSceneAddLight(NRScene *scene, NRPoint *light) {
    if(scene->lightCount == 0){
        scene->lights = malloc(1000*sizeof(NRPoint*));
    }
    
    scene->lights[scene->lightCount] = light;
    scene->lightCount = scene->lightCount + 1;
    
    if(scene->lightCount % 1000 == 0){
        NRPoint **lights = malloc((scene->lightCount+1000)*sizeof(NRPoint*));
        for(int i = 0; i < scene->lightCount; i++){
            lights[i] = scene->lights[i];
        }
        scene->lights = lights;
    }
}

FOUNDATION_STATIC_INLINE NRVector NRSceneIntersectWithRay(NRScene scene, NRRay ray, NRHitRecord *hitRecord) {
    NRVector result = NRMakeVector(0, 0, 0);
    
    hitRecord->ray = &ray;
    NRIntersectOctree(scene.octree->root, ray, hitRecord, scene.octree->maxDepth, 0, scene.octree->C);
    if(hitRecord->voxel == nil){
        return result;
    }
    
    //return hitRecord->voxel->color;
    
    if(hitRecord->voxel->isLight){
        return hitRecord->voxel->color;
    }
    
    if(drand48() >= .1){
        NRHitRecord tempRecord = NRMakeHitRecord();
        NRVector position = NRGetPositionAtTime(*hitRecord->ray, hitRecord->t);

        NRVector normal = NRGetVoxelNormal(hitRecord->voxel, position);
        CGFloat costheta = NRDotVectors(normal, hitRecord->ray->direction);

        if(costheta > 0){
            normal = NRNegateVector(normal);
        }
        
        NRVector new_direction;
        
        if(drand48() < .5){
            NRVector axis;
            if(fabs(normal.x) < fabs(normal.y) && fabs(normal.x) < fabs(normal.z)){
                axis = NRMakeVector(1, 0, 0);
            }
            else if (fabs(normal.y) < fabs(normal.z)){
                axis = NRMakeVector(0, 1, 0);
            }
            else{
                axis = NRMakeVector(0, 0, 1);
            }
            
            NRVector X = NRNormalizeVector(NRCrossVectors(normal, axis));
            NRVector Y = NRNormalizeVector(NRCrossVectors(normal, X));
            
            CGFloat u = 0;
            CGFloat v = 0;
            CGFloat u_2 = 0;
            CGFloat v_2 = 0;
            do {
                u = drand48();
                v = drand48();
                u *= 2.0;
                u -= 1.0;
                v *= 2.0;
                v -= 1.0;
                u_2 = u * u;
                v_2 = v * v;
            }
            while((u_2 + v_2) >= 1);
            
            CGFloat w = sqrt(1 - (u_2) - (v_2));
            
            new_direction = NRAddVectors(NRMultiplyVector(X, u), NRAddVectors(NRMultiplyVector(Y, v), NRMultiplyVector(normal, w)));
        }
        else {
            if(scene.octree->lightCount > 0){
                NRVoxel *light = scene.octree->lights[arc4random_uniform(scene.octree->lightCount)];
                new_direction = NRNormalizeVector(NRMinusVectors(NRGetPointOnVoxel(light), position));
            }
            else {
                return result;
            }
        }
        
        NRRay shadow_ray = NRMakeRay(position, new_direction);
        float cosphi = NRDotVectors(normal, new_direction);

        if(cosphi > 0){
            result = NRAddVectors(result, NRMultiplyVector(NRSceneIntersectWithRay(scene, shadow_ray, &tempRecord), cosphi));
        }
    }
  
    result = NRMultiplyVectors(result, hitRecord->voxel->color);
    return result;
}

FOUNDATION_STATIC_INLINE NRVector NRSceneIntersect(NRScene scene, CGFloat x, CGFloat y, CGFloat a, CGFloat b, NRHitRecord *hitRecord) {
    NRRay ray = NRCameraMakeRay(scene.camera, x, y, a, b);
    return NRSceneIntersectWithRay(scene, ray, hitRecord);
}


//FOUNDATION_STATIC_INLINE bool NRSceneIntersect(NRScene scene, CGFloat x, CGFloat y, CGFloat a, CGFloat b, NRHitRecord *hitRecord) {
//    NRRay ray = NRCameraMakeRay(scene.camera, x, y, a, b);
//    return NRSceneIntersectWithRay(scene, ray, hitRecord);
//}

#endif
