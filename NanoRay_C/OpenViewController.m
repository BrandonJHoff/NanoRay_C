//
//  OpenViewController.m
//  NanoRay_C
//
//  Created by Brandon Hoff on 8/19/12.
//  Copyright (c) 2012 Brandon Hoff. All rights reserved.
//

#import "OpenViewController.h"

@implementation OpenViewController

@synthesize view = _view;
@synthesize pixels = _pixels;
@synthesize xres = _xres;
@synthesize yres = _yres;
@synthesize scene = _scene;

- (id)initWithCoder:(NSCoder *)decoder
{
    self = [super initWithCoder:decoder];
    if (self) {
        _scene = NRMakeScene();
        _scene.octree = NRMakeOctree(NRMakeVector(300, 300, 300), 300);
        dispatch_async(dispatch_get_global_queue(0, 0),^{[self render];});
    }
    
    return self;
}

-(void)loadOctree
{

}


-(void)render
{
    while(true){
        if(_view != nil){
            _pixels = NRMakeImage(_view.bounds.size.width, _view.bounds.size.height);
            _view.pixels = _pixels;
            break;
        }
        [NSThread sleepForTimeInterval:0.1];
    }

    _xres = _view.bounds.size.width;
    _yres = _view.bounds.size.height;
    
    
    
    
    
    
    
    
    
    
//    //[NSApp terminate:self];
//    
//    NSMutableString *mutstr = [[NSMutableString alloc] init];
//    int numPoints = 0;
//
//    // light
//    for(CGFloat m = 213; m <= 343; m++){
//        for(CGFloat n = 227; n <= 332; n++){
//            [mutstr appendFormat:@"%f %f %f %f %f %f %i\n", m, 540.0, n, 0.9, 0.9, 0.9, true];
//            numPoints++;
//        }
//    }
//
//    // back wall
//    for(CGFloat m = 0; m <= 556; m++){
//        for(CGFloat n = 0; n <= 549; n++){
//            [mutstr appendFormat:@"%f %f %f %f %f %f %i\n", m, n, 560.0, 0.95, 0.95, 0.85, false];
//            numPoints++;
//        }
//    }
//
//    // left wall
//    for(CGFloat m = 0; m <= 570; m++){
//        for(CGFloat n = 0; n <= 549; n++){
//            [mutstr appendFormat:@"%f %f %f %f %f %f %i\n", 556.0, n, m, .5, 0.0, 0.0, false];
//            numPoints++;
//        }
//    }
//
//    // right wall
//    for(CGFloat m = 0; m <= 560; m++){
//        for(CGFloat n = 0; n <= 549; n++){
//            [mutstr appendFormat:@"%f %f %f %f %f %f %i\n", 0.0, n, m, 0.25, 0.95, 0.25, false];
//            numPoints++;
//        }
//    }
//
//    // ceiling
//    for(CGFloat m = 0; m <= 556; m++){
//        for(CGFloat n = 0; n <= 560; n++){
//            if(!(m >= 213 && m <= 343 && n >= 227 && n <= 332)){
//                [mutstr appendFormat:@"%f %f %f %f %f %f %i\n", m, 549.0, n, 0.95, 0.95, 0.85, false];
//                numPoints++;
//            }
//        }
//    }
//
//    // floor
//    for(CGFloat m = 0; m <= 556; m++){
//        for(CGFloat n = 0; n <= 560; n++){
//            [mutstr appendFormat:@"%f %f %f %f %f %f %i\n", m, 0.0, n, 0.95, 0.95, 0.85, false];
//            numPoints++;
//        }
//    }
//
//    // small box
//    for(CGFloat l = 130; l <= 290; l++){
//        for(CGFloat m = 114; m <= 272; m++){
//            for(CGFloat n = 0; n <= 80; n++){
//                [mutstr appendFormat:@"%f %f %f %f %f %f %i\n", l, n, m, 0.25, 0.25, 0.95, false];
//                numPoints++;
//            }
//        }
//    }
//    
//    NSMutableString *header = [[NSMutableString alloc] init];
//    [header appendFormat:@"# .PCD v.5 - Point Cloud Data file format\n"];
//    [header appendFormat:@"VERSION .5\n"];
//    [header appendFormat:@"FIELDS x y z r g b light\n"];
//    [header appendFormat:@"SIZE 4 4 4\n"];
//    [header appendFormat:@"TYPE F F F\n"];
//    [header appendFormat:@"COUNT 1 1 1\n"];
//    [header appendFormat:@"WIDTH %d\n", numPoints];
//    [header appendFormat:@"HEIGHT 1\n"];
//    [header appendFormat:@"POINTS %d\n", numPoints];
//    [header appendFormat:@"DATA ascii\n"];
//    
//    [mutstr insertString:header atIndex:0];
//    
//    NSError *error;
//    NSArray *pathArray = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString *documentsDirectory = [pathArray objectAtIndex:0];
//    NSString *textPath = [documentsDirectory stringByAppendingPathComponent:@"box.txt"];
//    [mutstr writeToFile:textPath atomically:YES encoding:NSASCIIStringEncoding error:&error];
//    
//    [NSApp terminate:self];

    
    
    NRVector red = NRMakeVector(.5, 0, 0);
    NRVector white = NRMakeVector(0.95, 0.95, 0.85);
    NRVector green = NRMakeVector(0.25, 0.95, 0.25);
    NRVector blue = NRMakeVector(0.25, 0.25, 0.95);
    NRVector light = NRMakeVector(.9, .9, .9);
    
    // light
    for(int m = 213; m <= 343; m++){
        for(int n = 227; n <= 332; n++){
            NROctreeAddPoint(_scene.octree, _scene.octree->root, NRMakePoint(NRMakeVector(m, 549, n), light, true));
        }
    }
    
    // back wall
    for(int m = 0; m <= 556; m++){
        for(int n = 0; n <= 549; n++){
            NROctreeAddPoint(_scene.octree, _scene.octree->root, NRMakePoint(NRMakeVector(m, n, 560), white, false));
        }
    }
    
    // left wall
    for(int m = 0; m <= 570; m++){
        for(int n = 0; n <= 549; n++){
            NROctreeAddPoint(_scene.octree, _scene.octree->root, NRMakePoint(NRMakeVector(556, n, m), red, false));
        }
    }
    
    // right wall
    for(int m = 0; m <= 560; m++){
        for(int n = 0; n <= 549; n++){
            NROctreeAddPoint(_scene.octree, _scene.octree->root, NRMakePoint(NRMakeVector(0, n, m), green, false));
        }
    }
    
    // ceiling
    for(int m = 0; m <= 556; m++){
        for(int n = 0; n <= 560; n++){
            if(!(m >= 213 && m <= 343 && n >= 227 && n <= 332)){
                NROctreeAddPoint(_scene.octree, _scene.octree->root, NRMakePoint(NRMakeVector(m, 549, n), white, false));
            }
        }
    }
    
    // floor
    for(int m = 0; m <= 553; m++){
        for(int n = 0; n <= 560; n++){
            NROctreeAddPoint(_scene.octree, _scene.octree->root, NRMakePoint(NRMakeVector(m, 0, n), white, false));
        }
    }
    
    // small box
    for(int l = 130; l <= 290; l++){
        for(int m = 114; m <= 272; m++){
            for(int n = 0; n <= 80; n++){
                NROctreeAddPoint(_scene.octree, _scene.octree->root, NRMakePoint(NRMakeVector(l, n, m), blue, false));
            }
        }
    }

    
    _scene.octree->maxDepth = 10;
    _scene.octree->C = 32 / ((_xres*_yres/2.0)/tan(39/2.0));
    //_scene.octree->C = .001;
    //_scene.octree->C = 100 / ((2*M_PI)/tan((39/2.0)));
    
    _scene.ambient = NRMakeVector(.6, .6, .6);
    _scene.camera = NRMakeCamera(NRMakeVector(278, 273, -800), NRMakeVector(278, 273, 0), NRMakeVector(0, 1, 0), 39, (float)(_xres/_yres), 35, 2);
    
    NRHitRecord hitRecord = NRMakeHitRecord();
    
    while(_pixels.renderCount > 0){
        
        for(double j = 0; j < _yres; j++){
            for(double i = 0; i < _xres; i++){

//        for(double j = _yres - 1; j > -1; j--){
//            for(double i = _xres - 1 ; i > -1; i--){
                
                
//                double i = arc4random_uniform(_xres);
//                double j = arc4random_uniform(_yres);
        
//                double i = 150;
//                double j = 100;
        
                int index = (j*_yres) + i;
                
                if(_pixels.render[index]){
        
                    //for(int k = 0; k < 10; k++){
                        double x = 2 * (i - _xres/2. + drand48())/_xres;
                        double y = 2 * (j - _yres/2. + drand48())/_yres;
                        
                        NRResetHitRecord(&hitRecord);
                        NRImageInsertColor(&_pixels, NRSceneIntersect(_scene, x, y, 0.5, 0.5, &hitRecord), index);
                    //}
                }
                
            }
        }

        
    }

    
    
    [NSApp terminate:self];

}


@end
