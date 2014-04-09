//
//  OpenView.m
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#import "OpenView.h"

@implementation OpenView

@synthesize pixels = _pixels;

- (id)initWithCoder:(NSCoder *)decoder
{
    self = [super initWithCoder:decoder];
    if (self) {
        _pixels.pixels = nil;
    }
    
    return self;
}

-(void)drawRect:(NSRect)bounds
{
    if(_pixels.pixels != nil){
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawPixels(bounds.size.width, bounds.size.height, GL_RGB, GL_FLOAT, _pixels.pixels);
        [[self openGLContext] flushBuffer];
    }
}

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime
{
    @autoreleasepool {
        self.needsDisplay = YES;
        return kCVReturnSuccess;
    }
}

// This is the renderer output callback function
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    CVReturn result = [(__bridge OpenView*)displayLinkContext getFrameForTime:outputTime];
    return result;
}

-(void)prepareOpenGL
{
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    // Create a display link capable of being used with all active displays
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    
    // Set the renderer output callback function
    CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, (__bridge void *)(self));
    
    // Set the display link for the current renderer
    CGLContextObj cglContext = [[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = [[self pixelFormat] CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
    
    // Activate the display link
    CVDisplayLinkStart(displayLink);
}

@end