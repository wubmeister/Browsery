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
    }
    
    Process::~Process()
    {
        freePixelData(&mPixelData);
    }
    
    void Process::getPixelData(PixelData *pd)
    {
		pd->width = mPixelData.width;
		pd->height = mPixelData.height;
		pd->pixels = mPixelData.pixels;
    }
    
    void Process::setViewportSize(int width, int height)
    {
        freePixelData(&mPixelData);
        allocatePixelData(width, height, &mPixelData);
    }
    
    void Process::allocatePixelData(int width, int height, PixelData *pd)
    {
		int x, y, offset, scanlineSize;

#if defined(_WIN64) || defined(_WIN32)
		scanlineSize = width * 3 + ((4 - ((width * 3) % 4)) % 4);
#else
		scanlineSize = width * 3;
#endif

        pd->width = width;
        pd->height = height;
        pd->pixels = (u_int8_t *)malloc(scanlineSize * height);

		if (!pd->pixels) {
			return;
		}
        memset(pd->pixels, 0x00, scanlineSize * height);

		for (y = 0; y < height; y++) {
			for (x = 0; x < width; x++) {
				offset = y * scanlineSize + x * 3;
				pd->pixels[offset] = 0xFF;
				pd->pixels[offset+1] = 0x99;
				pd->pixels[offset+2] = 0x00;
			}
		}
    }
    
    void Process::freePixelData(PixelData *pd)
    {
        if (pd->pixels) {
            free(pd->pixels);
            pd->pixels = NULL;
        }
    }
    
}
