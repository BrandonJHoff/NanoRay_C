//
//  OpenView.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import <QuartzCore/CVDisplayLink.h>
#import "NRImage.h"

@interface OpenView : NSOpenGLView{
    CVDisplayLinkRef displayLink;
}

@property (nonatomic) NRImage pixels;

@end
