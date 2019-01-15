//
//  AppDelegate.m
//  Browsery
//
//  Created by Wubbo Bos on 15/01/2019.
//  Copyright © 2019 Apstery. All rights reserved.
//

#import "AppDelegate.h"
#import "BrowserWindow.h"

@interface AppDelegate ()

@property NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    NSRect frame = [[NSScreen mainScreen] frame];
    
    _window = [[BrowserWindow alloc]
               initWithContentRect:NSMakeRect((frame.size.width - 640) / 2, (frame.size.height - 480) / 2, 640, 480)
                         styleMask:NSWindowStyleMaskTitled|NSWindowStyleMaskClosable
                           backing:0
                             defer:YES];
    [_window setIsVisible:YES];
    [_window makeKeyWindow];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


@end
