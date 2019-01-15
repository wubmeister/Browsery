//
//  Process.hpp
//  Browsery
//
//  Created by Wubbo Bos on 15/01/2019.
//  Copyright © 2019 Apstery. All rights reserved.
//

#ifndef Process_hpp
#define Process_hpp

namespace FourtyTwo {
    
    typedef unsigned char *u_int8_t;
    
    typedef struct _PixelData {
        int width;
        int height;
        u_int8_t *pixels;
    } PixelData;
    
    class Process {
    public:
        Process();
        ~Process();
        PixelData getPixelData();
        
    private:
        void allocatePixelData(int width, int height, PixelData *pd);
        void freePixelData(PixelData *pd);
        
        PixelData mPixelData;
    };
    
};

#endif /* Process_hpp */
