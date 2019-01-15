//
//  BrowserView.m
//  Browsery
//
//  Created by Wubbo Bos on 15/01/2019.
//  Copyright © 2019 Apstery. All rights reserved.
//

#import "BrowserView.h"

#include "../FourtyTwo/Process.hpp"

@interface BrowserView() {
    FourtyTwo::Process *process;
}
@end

@implementation BrowserView

- (id)initWithFrame:(NSRect)frameRect {
    self = [super initWithFrame:frameRect];
    
    process = new FourtyTwo::Process();
    process->setViewportSize(frameRect.size.width, frameRect.size.height);
    
    return self;
}

- (void)dealloc {
    delete process;
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
    NSLog(@"Drawing the rect");
    
    FourtyTwo::PixelData pixelData;
    process->getPixelData(&pixelData);
    
    CGContextRef curr = [[NSGraphicsContext currentContext] CGContext];
    
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, pixelData.pixels, pixelData.height * pixelData.width * 3, NULL);
    CGImageRef image = CGImageCreate(pixelData.width, pixelData.height, 8, 24, pixelData.width * 3, CGColorSpaceCreateDeviceRGB(), 0, provider, NULL, FALSE, kCGRenderingIntentDefault);
    
    CGContextDrawImage(curr, CGRectMake(0, self.bounds.size.height - pixelData.height, pixelData.width, pixelData.height), image);
    
    CGImageRelease(image);
    CGDataProviderRelease(provider);
    
}

@end
