#ifndef _PNGLOAD_HH_
#define _PNGLOAD_HH_

#include <png.h>

int pngLoad(const char *file, unsigned long *pwidth, 
            unsigned long *pheight, unsigned char **image_data_ptr, bool &alpha);

#endif
