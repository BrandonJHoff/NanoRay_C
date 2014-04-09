//
//  NRPoint.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 9/2/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRPoint_h
#define NanoRay_C_NRPoint_h

#import "NRVector.h"

typedef struct _NRPoint {
    bool isLight;
    NRVector position;
    NRVector color;
} NRPoint;

FOUNDATION_STATIC_INLINE NRPoint * NRMakePoint(NRVector position, NRVector color, bool isLight) {
    NRPoint *p = malloc(sizeof(NRPoint));
    p->isLight = isLight;
    p->position = position;
    p->color = color;
    return p;
}


#endif
