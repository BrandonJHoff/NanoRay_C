//
//  NRImage.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#ifndef NanoRay_C_NRImage_h
#define NanoRay_C_NRImage_h

#import "NRVector.h"

typedef struct _NRImage {
    float *pixels;
    int *hit_counts;
    bool *render;
    int renderCount;
    int *zero_count;
} NRImage;

FOUNDATION_STATIC_INLINE NRImage NRMakeImage(int width, int height) {
    NRImage img;
    img.pixels = malloc(width*height*3*sizeof(float));
    img.hit_counts = malloc(width*height*sizeof(int));
    img.render = malloc(width*height*sizeof(bool));
    img.zero_count = malloc(width*height*sizeof(int));
    
    long size = width*height*3;
    for(int i = 0; i < size; i++){
        img.pixels[i] = 0;
    }
    int counts = width*height;
    for(int j = 0; j < counts; j++){
        img.hit_counts[j] = 0;
    }
    for(int i = 0; i < counts; i++){
        img.render[i] = true;
    }
    for(int i = 0; i < counts; i++){
        img.zero_count[i] = 0;
    }
    img.renderCount = counts;
    
    return img;
}

//FOUNDATION_STATIC_INLINE void NRImageInsert(NRImage *image, float r, float g, float b, int index) {
//    image->hit_counts[index]++;
//    
//    index *= 3;
//    image->pixels[index] = ((image->pixels[index] * (image->hit_counts[index] - 1)) + r) / image->hit_counts[index];
//    image->pixels[index+1] = ((image->pixels[index+1] * (image->hit_counts[index] - 1)) + g) / image->hit_counts[index];
//    image->pixels[index+2] = ((image->pixels[index+2] * (image->hit_counts[index] - 1)) + b) / image->hit_counts[index];
//}

FOUNDATION_STATIC_INLINE void NRImageInsertColor(NRImage *image, NRVector color, int index) {
    
    if(color.x == 0 && color.y == 0 && color.z == 0){
        image->zero_count[index]++;
        if(image->zero_count[index] > 10){
            int pixel_index = index * 3;
            if(image->pixels[pixel_index] == 0 && image->pixels[pixel_index+1] == 0 && image->pixels[pixel_index+2] == 0){
                image->pixels[pixel_index] = 1;
                image->pixels[pixel_index+1] = 1;
                image->pixels[pixel_index+2] = 0;
                image->render[index] = false;
                image->renderCount--;
            }
        }
        return;
    }
        
    CGFloat invCount = 1.0 / (image->hit_counts[index] + 1);
    
    int pixel_index = index * 3;
    image->pixels[pixel_index] = ((image->pixels[pixel_index] * image->hit_counts[index]) + color.x) * invCount;
    image->pixels[pixel_index+1] = ((image->pixels[pixel_index+1] * image->hit_counts[index]) + color.y) * invCount;
    image->pixels[pixel_index+2] = ((image->pixels[pixel_index+2] * image->hit_counts[index]) + color.z) * invCount;
    
    image->hit_counts[index]++;
    
    if(image->hit_counts[index] > 5){
    
        float d = sqrtf(pow(image->pixels[pixel_index] - color.x, 2) + pow(image->pixels[pixel_index+1] - color.y, 2) + pow(image->pixels[pixel_index+2] - color.z, 2));
        
        if(d < .01){
            image->pixels[pixel_index] = 1;
            image->pixels[pixel_index+1] = 0;
            image->pixels[pixel_index+2] = 1;
            image->render[index] = false;
            image->renderCount--;
        }
    }
}


#endif
