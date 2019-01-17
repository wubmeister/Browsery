//
//  Process.hpp
//  Browsery
//
//  Created by Wubbo Bos on 15/01/2019.
//  Copyright © 2019 Apstery. All rights reserved.
//

#ifndef Process_hpp
#define Process_hpp

#include <ft2build.h>
#include FT_FREETYPE_H

namespace FourtyTwo {
    
    typedef unsigned char u_int8_t;
    
    typedef struct _PixelData {
        int width;
        int height;
        int rowStride;
        u_int8_t *pixels = 0;
    } PixelData;
    
    class Process {
    public:
        Process();
        ~Process();
        void getPixelData(PixelData *pd);
        void setViewportSize(int width, int height, double scale);
        
    private:
        void allocatePixelData(int width, int height, PixelData *pd);
        void freePixelData(PixelData *pd);
        
        PixelData mPixelData;
        FT_Library mLibrary;
        FT_Face mFace;
    };
    
};

#endif /* Process_hpp */
