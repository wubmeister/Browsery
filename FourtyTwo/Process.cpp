//
//  Process.cpp
//  Browsery
//
//  Created by Wubbo Bos on 15/01/2019.
//  Copyright © 2019 Apstery. All rights reserved.
//

#include "Process.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace FourtyTwo {
    
    Process::Process()
    {
        printf("Hello process");
        allocatePixelData(100, 100, &mPixelData);
    }
    
    Process::~Process()
    {
        freePixelData(&mPixelData);
    }
    
    PixelData Process::getPixelData()
    {
        return mPixelData;
    }
    
    void Process::allocatePixelData(int width, int height, PixelData *pd)
    {
        pd->width = width;
        pd->height = height;
        pd->pixels = (u_int8_t *)malloc(width * height * 4);
        memset(pd->pixels, 0xFF, width * height * 4);
    }
    
    void Process::freePixelData(PixelData *pd)
    {
        if (pd->pixels) {
            free(pd->pixels);
            pd->pixels = NULL;
        }
    }
    
}
