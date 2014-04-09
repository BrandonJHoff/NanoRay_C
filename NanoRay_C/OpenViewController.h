//
//  OpenViewController.h
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import "OpenView.h"
#import "NRVector.h"
#import "NRImage.h"
#import "NRRay.h"
#import "NRCamera.h"
#import "NRPointLight.h"
#import "NRBox.h"
#import "NRScene.h"
#import "NRHitRecord.h"
#import "NRLambertianMaterial.h"
#import "NROctree.h"

@interface OpenViewController : NSViewController

@property (assign) IBOutlet OpenView *view;
@property (nonatomic) NRImage pixels;
@property (nonatomic) double xres;
@property (nonatomic) double yres;
@property (nonatomic) NRScene scene;

-(void)render;
-(void)loadOctree;

@end
