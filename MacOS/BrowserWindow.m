//
//  BrowserWindow.m
//  Browsery
//
//  Created by Wubbo Bos on 15/01/2019.
//  Copyright © 2019 Apstery. All rights reserved.
//

#import "BrowserWindow.h"
#import "BrowserView.h"

@interface BrowserWindow ()

@end

@implementation BrowserWindow

-(id)initWithContentRect:(NSRect)contentRect styleMask:(NSWindowStyleMask)style backing:(NSBackingStoreType)backingStoreType defer:(BOOL)flag {
    self = [super initWithContentRect:contentRect styleMask:style backing:backingStoreType defer:flag];
    
    BrowserView *browserView = [[BrowserView alloc] initWithFrame:self.contentView.bounds];
    [[self contentView] addSubview:browserView];
    
    return self;
}

@end
