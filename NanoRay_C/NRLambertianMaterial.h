//
//  NRLambertianMaterial.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRLambertianMaterial_h
#define NanoRay_C_NRLambertianMaterial_h

#import <CoreGraphics/CoreGraphics.h>
#import "NRVector.h"
#import "NRScene.h"
#import "NRHitRecord.h"
#import "NRBox.h"
#import "NROctree.h"

typedef struct _NRLambertianMaterial{
    NRVector color;
    CGFloat kd;
    CGFloat ka;
} NRLambertianMaterial;

FOUNDATION_STATIC_INLINE NRLambertianMaterial NRMakeLambertianMaterial(NRVector color, CGFloat kd, CGFloat ka) {
    NRLambertianMaterial lm;
    lm.color = color;
    lm.kd = kd;
    lm.ka = ka;
    return lm;
}

//FOUNDATION_STATIC_INLINE NRVector NRShadeWithMaterial(NRLambertianMaterial lm, NRScene scene, NRHitRecord record) {
//    NRHitRecord tempRecord = NRMakeHitRecord();
//	NRVector position = NRGetPositionAtTime(*record.ray, record.t);
//
//	NRVector normal = NRGetVoxelNormal(record.voxel, position);
//	CGFloat costheta = NRDotVectors(normal, record.ray->direction);
//
//	if(costheta > 0){
//        normal = NRNegateVector(normal);
//	}
//
//	NRVector result = NRMultiplyVector(scene.ambient, lm.ka);
//
//	for(int i = 0; i < 10; i++){
//        if(scene.lights[i] != nil){
//            NRPointLight light = *scene.lights[i];
//            NRVector light_direction = NRNormalizeVector(NRMinusVectors(*light.position, position));
//            NRRay shadow_ray = NRMakeRay(position, light_direction);
//            float cosphi = NRDotVectors(normal, light_direction);
//            
//            NRResetHitRecord(&tempRecord);
//            tempRecord.t = NRGetTimeAtPosition(position, *light.position);
//
//            if(cosphi > 0){
////                if(!NRSceneIntersectWithRay(scene, shadow_ray, &tempRecord)){
////                    result = NRAddVectors(result, NRMultiplyVector(*light.color, (lm.kd * cosphi)));
////                }
//            }
//        }
//	}
//
//    result = NRMultiplyVectors(result, lm.color);
//    return result;
//}


//FOUNDATION_STATIC_INLINE NRVector NRShadeWithMaterial(NRLambertianMaterial lm, NRScene scene, NRHitRecord record) {
//    NRHitRecord tempRecord = NRMakeHitRecord();
//	NRVector position = NRGetPositionAtTime(*record.ray, record.t);
//	
//	NRVector normal = NRBoxGetNormal(*record.box, position);
//	CGFloat costheta = NRDotVectors(normal, record.ray->direction);
//	
//	if(costheta > 0){
//        normal = NRNegateVector(normal);
//	}
//	
//	NRVector result = NRMultiplyVector(scene.ambient, lm.ka);
//	
//	for(int i = 0; i < 10; i++){
//        if(scene.lights[i] != nil){
//            NRPointLight light = *scene.lights[i];
//            
//            NRVector light_direction = NRNormalizeVector(NRMinusVectors(*light.position, position));
//            NRRay shadow_ray = NRMakeRay(position, light_direction);
//            float cosphi = NRDotVectors(normal, light_direction);
//            
//            if(cosphi > 0){
//                if(!NRSceneIntersectWithRay(scene, shadow_ray, &tempRecord)){
//                    result = NRAddVectors(result, NRMultiplyVector(*light.color, (lm.kd * cosphi)));
//                }
//            }
//        }
//	}
//    
//    result = NRMultiplyVectors(result, lm.color);
//    return result;
//}


#endif
