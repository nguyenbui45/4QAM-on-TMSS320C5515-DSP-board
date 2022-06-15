
#ifndef UTILITIES_H_
#define UTILITIES_H_
#include "usbstk5515.h"
#include "stdio.h"

Uint32 GetBinLen(const char *path);
Uint16 ExportFile(const char *path, Uint32 binLen, Int16 *p_buffer_data );
Uint16 ImportFile(const char *path, Uint32 binLen, Int16 *p_buffer_data );


#endif /* UTILITIES_H_ */
