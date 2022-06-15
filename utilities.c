
#include "utilities.h"

// Get .bin file length:
Uint32 GetBinLen(const char *path)
{
    Uint32 length;
    // char c;
    FILE *fp;
    /* Open file for both reading and writing */
    fp = fopen(path, "rb");
    /* Seek to the beginning of the file */
    fseek(fp, SEEK_SET, 0);
    length=0;
    /*get the length of the text*/
    while (1){
           fgetc(fp);
           if(feof(fp)){
               break;
           }
           length++;
    }
    fclose(fp);
return length;
}
//Save file to .bin file
Uint16 ExportFile(const char *path, Uint32 binLen, Int16 *p_buffer_data )
{
    FILE *fp ;
    Uint32 i ;
    Int8 temp;
    fp = fopen(path,"wb") ;
    if ( fp == (FILE*) NULL)
    {
        return 1 ;
    }
    for (i = 0; i < binLen; i++ )
    {
        p_buffer_data[i] = p_buffer_data[i] & 0xFFFF;
        temp = p_buffer_data[i] >> 8;
        fputc(temp, fp);
        temp = p_buffer_data[i] & 0xFF;
        fputc(temp, fp);
    }
    fclose(fp) ;
    return 0 ;
}

// Load data from .bin file:
Uint16 ImportFile(const char *path, Uint32 binLen, Int16 *p_buffer_data )
{
    FILE *fp ;
    Int16 data , pdata[1] ;
    Uint16 i ;
    fp = fopen(path,"rb") ;
    if ( fp == (FILE*)NULL)
    {
        return 1 ;
    }
    for( i = 0 ; i < binLen; i++ )
    {
       fread(pdata, 1, 1, fp);
       data = *(pdata);
       p_buffer_data[i] = data ;
    }
    fclose(fp) ;
    return 0;
}
