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
        int error;
#ifdef __APPLE__
        char fontfile[] = "/Library/Fonts/Times New Roman.ttf";
#endif
#if defined(_WIN64) || defined(_WIN32)
        char fontfile[] = "C:\\Windows\\Fonts\\Arial.ttf";
#endif
        
        error = FT_Init_FreeType(&mLibrary);
        if (error) {
            printf("Could not init FreeType\n");
        }
        
        error = FT_New_Face(mLibrary, fontfile, 0, &mFace);
        if (error == FT_Err_Unknown_File_Format) {
            printf("Invald file format\n");
        }
        else if (error) {
            printf("Unknown error loading font\n");
        }
    }
    
    Process::~Process()
    {
        FT_Done_FreeType(mLibrary);
        freePixelData(&mPixelData);
    }
    
    void Process::getPixelData(PixelData *pd)
    {
        memcpy(pd, &mPixelData, sizeof(PixelData));
    }
    
    void Process::setViewportSize(int width, int height, double scale)
    {
        FT_Set_Char_Size(mFace, 0, 16 * 64, 72 * scale, 72 * scale);
        freePixelData(&mPixelData);
        allocatePixelData(width * scale, height * scale, &mPixelData);
    }
    
    void Process::allocatePixelData(int width, int height, PixelData *pd)
    {
		int x, y, xx, yy, offset, scanlineSize, i;
        char string[] = "Hello world";
        FT_GlyphSlot slot = mFace->glyph;
        unsigned char pixel;
        unsigned int comp;
        u_int8_t *cbuf;

#if defined(_WIN64) || defined(_WIN32)
		scanlineSize = width * 3 + ((4 - ((width * 3) % 4)) % 4);
#else
		scanlineSize = width * 3;
#endif

        pd->width = width;
        pd->height = height;
        pd->rowStride = scanlineSize;
        pd->pixels = (u_int8_t *)malloc(scanlineSize * height);

		if (!pd->pixels) {
			return;
		}
        memset(pd->pixels, 0x00, scanlineSize * height);

		for (y = 0; y < height; y++) {
			for (x = 0; x < width; x++) {
				offset = y * scanlineSize + x * 3;
#if defined(_WIN64) || defined(_WIN32)
				pd->pixels[offset] = 0xFF;
				pd->pixels[offset+1] = 0x99;
				pd->pixels[offset+2] = 0x00;
#else
                pd->pixels[offset] = 0x00;
                pd->pixels[offset+1] = 0x99;
                pd->pixels[offset+2] = 0xFF;
#endif
			}
		}
        
        // Render hello world
        x = 101;
        y = 101;
        for (i = 0; string[i] != 0; i++) {
            FT_Load_Char(mFace, string[i], FT_LOAD_DEFAULT);
            FT_Render_Glyph(mFace->glyph, FT_RENDER_MODE_NORMAL);
            cbuf = (u_int8_t*)slot->bitmap.buffer;
            for (yy = 0; yy < slot->bitmap.rows; yy++) {
                for (xx = 0; xx < slot->bitmap.width; xx++) {
                    offset = (y + yy - slot->bitmap_top) * scanlineSize + (x + xx + slot->bitmap_left) * 3;
                    pixel = cbuf[yy*slot->bitmap.pitch+xx];
                    comp = ((255 - pixel) * pd->pixels[offset] + pixel * 255) >> 8;
                    pd->pixels[offset] = comp;
                    comp = ((255 - pixel) * pd->pixels[offset+1] + pixel * 255) >> 8;
                    pd->pixels[offset+1] = comp;
                    comp = ((255 - pixel) * pd->pixels[offset+2] + pixel * 255) >> 8;
                    pd->pixels[offset+2] = comp;
                }
            }
            x += slot->advance.x >> 6;
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
