//
//  NRPointLight.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRPointLight_h
#define NanoRay_C_NRPointLight_h

#import "NRVector.h"

typedef struct _NRPointLight {
    NRVector *position;
    NRVector *color;
} NRPointLight;

FOUNDATION_STATIC_INLINE NRPointLight * NRMakePointLight(NRVector *p, NRVector *c) {
    NRPointLight *pl = malloc(sizeof(NRPointLight));
    pl->position = p;
    pl->color = c;
    return pl;
}

#endif
