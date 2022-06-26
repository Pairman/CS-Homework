#include<stdio.h>
#include<stdlib.h>
#include<string.h>



struct BitmapFileHeader{
    // bfType          - 2 bytes - MUst be the characters "BM"(19778 in short).
    unsigned short bfType=19778;
    // bfSize          - 4 bytes - The size of the file in bytes.
    unsigned int bfSize=0;
    // bfReversed1     - 2 bytes - Unused. Must be 0.
    unsigned short bfReversed1=0;
    // bfReversed2     - 2 bytes - Unused. Must be 0.
    unsigned short bfReversed2=0;
    // bfOffBits       - 4 bytes - Byte offset to start of pixel data.
    unsigned int bfOffBits=0;
};



struct BitmapImageHeader{
    // biSize          - 4 bytes - Header size. Must be at least 40.
    unsigned int biSize=40;
    // biWidth         - 4 bytes - Image width in pixels. Must be a multiple of 4.
    unsigned int biWidth=0;
    // biHeight        - 4 bytes - Image height in pixels. Must be a multiple of 4.
    unsigned int biHeight=0;
    // biPlanes        - 2 bytes - Must be 1.
    unsigned short biPlanes=1;
    // biBitCount      - 2 bytes - Bits per pixel. 1, 4, 8, 16, 24, or 32.
    unsigned short biBitCount=24;
    // biCompression   - 4 bytes - Compression type. 0 if uncompressed.
    unsigned int biCompression=0;
    // biSizeImage     - 4 bytes - Image size aka channels*pixels. May be 0 for uncompressed images.
    unsigned int biSizeImage=0;
    // biXPelsPerMeter - 4 bytes - Preferred x resolution in pixels per meter.
    unsigned int biXPelsPerMeter=11811;
    // biYPelsPerMeter - 4 bytes - Preferred y resolution in pixels per meter.
    unsigned int biYPelsPerMeter=11811;
    // biClrUsed       - 4 bytes - Number of color map entries that are actually used.
    unsigned int biClrUsed=0;
    // biClrImportant  - 4 bytes - Number of significant colors.
    unsigned int biClrImportant=0;
};



struct BitmapColorTable{
    // 24-bit image has no color table theoreticaly.
};



struct RGBTriple{
    // Each pixel in represented bt three bytes in 24-bit images. 2 bytes each for blue, green and red intensity.
    unsigned char rgbBlue=0;
    unsigned char rgbGreen=0;
    unsigned char rgbRed=0;
};



struct BitmapPixelData{
    // Dummy. Reserved only for understanding.
    RGBTriple *bmPixelData=nullptr;
};



int main(int argc, char *argv[]){
    // Check the command.
    if(argc==1||strcmp(argv[1],"-h")==0){
        printf("BitmapZoomer 1.0.1 (2022/Jun/22) - Zoomer for 24-bit bitmaps!\nUsage: bmzoomer -h                                    show help\n       bmzoomer -z [file] [percent] [file] (--debug)  zoom the first image by given percent(s) and save to the second.\n                                                      \"--debug\" enables debugging mode\n");
        return 0;
    }
    if(strcmp(argv[1],"-z")){
        printf("Unknown command! Please check \"bmzoomer -h\" for usage!\n");
        return -1;
    }
    if(argc>6){
        printf("Too many parameters! Please check \"bmzoomer -h\" for usage!\n");
        return -1;
    }
    if(argc<5){
        printf("Not Enough parameters! Please check \"bmzoomer -h\" for usage!\n");
        return -1;
    }
    int DEBUGGING=0;
    if(argc==6){
        if(strcmp(argv[5],"--debug")==0){
            DEBUGGING=1;
        }
        else{
            printf("Unknown command! Please check \"bmzoomer -h\" for usage!\n");
        }
    }



    // Open the original image.
    FILE *file=fopen(argv[2],"rb");
    if(file==NULL){
        printf("No such file or directory! Please check \"bmzoomer -h\" for usage!\n");
        fclose(file);
        return -1;
    }



    // Read the bitmap's file header.
    BitmapFileHeader bmFileHeader;
    fread(&bmFileHeader.bfType,1,sizeof(unsigned short),file);
    if(bmFileHeader.bfType!=0x4D42){
        printf("Wrong File Type! Please check \"bmzoomer -h\" for usage!\n");
        fclose(file);
        return -1;
    }
    fread(&bmFileHeader.bfSize,1,sizeof(unsigned int),file);
    fread(&bmFileHeader.bfReversed1,1,sizeof(unsigned short),file);
    fread(&bmFileHeader.bfReversed2,1,sizeof(unsigned short),file);
    fread(&bmFileHeader.bfOffBits,1,sizeof(unsigned int),file);
    if(DEBUGGING){
        printf("\033[47;30mBitmapFileHeader\033[0m\n");
        printf("bfType %02X %c%c\n",bmFileHeader.bfType,bmFileHeader.bfType%256,bmFileHeader.bfType/256);
        printf("bfSize %04X %d %.1f\n",bmFileHeader.bfSize,bmFileHeader.bfSize,(float)bmFileHeader.bfSize/1024);
        printf("bfReversed1 %02X\n",bmFileHeader.bfReversed1);
        printf("bfReversed2 %02X\n",bmFileHeader.bfReversed2);
        printf("bfOffBits %04X %d\n",bmFileHeader.bfOffBits,bmFileHeader.bfOffBits);
    }



    // Read the bitmap's image header.
    BitmapImageHeader bmImageHeader;
    fread(&bmImageHeader.biSize,1,sizeof(bmImageHeader.biSize),file);
    fread(&bmImageHeader.biWidth,1,sizeof(bmImageHeader.biWidth),file);
    fread(&bmImageHeader.biHeight,1,sizeof(bmImageHeader.biHeight),file);
    fread(&bmImageHeader.biPlanes,1,sizeof(bmImageHeader.biPlanes),file);
    fread(&bmImageHeader.biBitCount,1,sizeof(bmImageHeader.biBitCount),file);
    fread(&bmImageHeader.biCompression,1,sizeof(bmImageHeader.biCompression),file);
    fread(&bmImageHeader.biSizeImage,1,sizeof(bmImageHeader.biSizeImage),file);
    fread(&bmImageHeader.biXPelsPerMeter,1,sizeof(bmImageHeader.biXPelsPerMeter),file);
    fread(&bmImageHeader.biYPelsPerMeter,1,sizeof(bmImageHeader.biYPelsPerMeter),file);
    fread(&bmImageHeader.biClrUsed,1,sizeof(bmImageHeader.biClrUsed),file);
    fread(&bmImageHeader.biClrImportant,1,sizeof(bmImageHeader.biClrImportant),file);
    if(DEBUGGING){
        printf("\033[47;30mBitmapImageHeader\033[0m\n");
        printf("biSize %04X %d\n",bmImageHeader.biSize,bmImageHeader.biSize);
        printf("biWidth %04X %d\n",bmImageHeader.biWidth,bmImageHeader.biWidth);
        printf("biHeight %04X %d\n",bmImageHeader.biHeight,bmImageHeader.biHeight);
        printf("biPlanes %02X\n",bmImageHeader.biPlanes);
        printf("biBitCount %02X %d\n",bmImageHeader.biBitCount,bmImageHeader.biBitCount);
        printf("biCompression %04X\n",bmImageHeader.biCompression);
        printf("biSizeImage %04X %d\n",bmImageHeader.biSizeImage,bmImageHeader.biSizeImage);
        printf("biXPelsPerMeter %04X %d\n",bmImageHeader.biXPelsPerMeter,bmImageHeader.biXPelsPerMeter);
        printf("biYpelsPerMeter %04X %d\n",bmImageHeader.biYPelsPerMeter,bmImageHeader.biYPelsPerMeter);
        printf("biClrUsed %04X\n",bmImageHeader.biClrUsed);
        printf("biClrImportant %04X\n",bmImageHeader.biClrImportant);
    }
    if(bmImageHeader.biBitCount!=0x0018){
        printf("Unsupported Color Space! Please check \"bmzoomer -h\" for usage!\n");
        fclose(file);
        return -1;
    }



    //Read the bitmap's color table. Only readable on Linux.
    unsigned char bmColorTable[256]={0},tempColorTable=0;
    fread(&bmColorTable,1,bmFileHeader.bfOffBits-54,file);
    if(DEBUGGING){
        printf("\033[47;30mBitmapColorTable\033[0m\n");
        printf("bmColorTable %d ",bmFileHeader.bfOffBits-54);
        for(int i=0;i<bmFileHeader.bfOffBits-54;++i){printf("%02X",bmColorTable[i]);}
        printf("\n");
    }



    // Read the pixel data.
    RGBTriple *bmPixelData=(RGBTriple*)calloc(bmImageHeader.biWidth*bmImageHeader.biHeight,sizeof(RGBTriple));
    unsigned char tempColor=0;
    for(int i=0;i<bmImageHeader.biWidth*bmImageHeader.biHeight;++i){
        fread(&tempColor,1,sizeof(unsigned char),file);
        bmPixelData[i].rgbBlue=tempColor;
        fread(&tempColor,1,sizeof(unsigned char),file);
        bmPixelData[i].rgbGreen=tempColor;
        fread(&tempColor,1,sizeof(unsigned char),file);
        bmPixelData[i].rgbRed=tempColor;
    }
    if(DEBUGGING){
        printf("\033[47;30mBitmapPixelData\033[0m\n");
        for(int y=0;y<bmImageHeader.biHeight;++y){
            for(int x=0;x<bmImageHeader.biWidth;++x){
                int offset=y*bmImageHeader.biWidth+x;
                printf("    xy %4d %4d    o %4d    c %02X%02X%02X\n",x,y,offset,bmPixelData[offset].rgbBlue,bmPixelData[offset].rgbGreen,bmPixelData[offset].rgbRed);
            }
        }
        printf("\n");
    }



    // Get the target file header.
    BitmapFileHeader bmFileHeaderNew=bmFileHeader;
    bmFileHeaderNew.bfOffBits=54;

    if(DEBUGGING){
        printf("checking zoom\n");
    }
    // Check the zoom percents.
    int zoom=atoi(argv[3]);
    if(zoom<=0){
        printf("Invalid zoom percents! Please check \"bmzoomer -h\" for usage!\n");
        fclose(file);
        free(bmPixelData);
        return -1;
    }
    if(DEBUGGING){
        printf("zoom checked %d\n",zoom);
    }



    if(DEBUGGING){
        printf("creating\n");
    }
    // Create the target image header and pixel data.
    BitmapImageHeader bmImageHeaderNew=bmImageHeader;
    // double pzoom=(double)zoom/(double)100;
    bmImageHeaderNew.biWidth=((unsigned int)((double)zoom/(double)100*bmImageHeader.biWidth)+3)/4*4;
    bmImageHeaderNew.biHeight=((unsigned int)((double)zoom/(double)100*bmImageHeader.biHeight)+3)/4*4;
    bmFileHeaderNew.bfSize=bmFileHeaderNew.bfOffBits+3*bmImageHeaderNew.biWidth*bmImageHeaderNew.biHeight;
    RGBTriple *bmPixelDataNew=(RGBTriple*)calloc(bmImageHeaderNew.biWidth*bmImageHeaderNew.biHeight,sizeof(RGBTriple));
    if(DEBUGGING){
        printf("created width %d height %d\n",bmImageHeaderNew.biWidth,bmImageHeaderNew.biHeight);
        printf("sizeof(RGBTriple) %d\n",sizeof(RGBTriple));
    }



    if(DEBUGGING){
        printf("zooming\n");
    }
    // Do the zoom work.
    int xNew=0,x=0,yNew=0,y=0,offsetNew=0,offset=0;
    for(int yNew=0;yNew<bmImageHeaderNew.biHeight;++yNew){
        for(int xNew=0;xNew<bmImageHeaderNew.biWidth;++xNew){
            // Get the offset of the pixel in the new image and in the original image.
            offset=y*bmImageHeader.biWidth+x;
            offsetNew=yNew*bmImageHeaderNew.biWidth+xNew;
            x=(int)xNew/((double)zoom/(double)100);
            y=(int)yNew/((double)zoom/(double)100);
            // Fix overflow occured when rounding.
            if(x>=bmImageHeader.biWidth){
                x=bmImageHeader.biWidth-1;
            }
            if(y>=bmImageHeader.biHeight){
                y=bmImageHeader.biHeight-1;
            }
            // Write to the new image.
            bmPixelDataNew[offsetNew].rgbBlue=bmPixelData[offset].rgbBlue;
            bmPixelDataNew[offsetNew].rgbGreen=bmPixelData[offset].rgbGreen;
            bmPixelDataNew[offsetNew].rgbRed=bmPixelData[offset].rgbRed;
        }
    }
    if(DEBUGGING){
        for(int yNew=0;yNew<bmImageHeaderNew.biHeight;++yNew){
            for(int xNew=0;xNew<bmImageHeaderNew.biWidth;++xNew){
                offset=y*bmImageHeader.biWidth+x;
                offsetNew=yNew*bmImageHeaderNew.biWidth+xNew;
                x=(int)xNew/((double)zoom/(double)100);
                y=(int)yNew/((double)zoom/(double)100);
                printf("    xyN %4d %4d    xy %4d %4d    oN %4d o %4d    cN %02X%02X%02X c %02X%02X%02X\n",xNew,yNew,x,y,offsetNew,offset,bmPixelDataNew[offsetNew].rgbBlue,bmPixelDataNew[offsetNew].rgbGreen,bmPixelDataNew[offsetNew].rgbRed,bmPixelData[offset].rgbBlue,bmPixelData[offset].rgbGreen,bmPixelData[offset].rgbRed);
            }
        }
        printf("zoomed\n");
    }



    if(DEBUGGING){
        printf("savinvg\n");
    }
    // Create the new image.
    FILE *fileNew=fopen(argv[4],"wb");
    if(fileNew==NULL){
        printf("Unable to save the processed image! Please check \"bmzoomer -h\" for usage!\n");
        fclose(file);
        fclose(fileNew);
        free(bmPixelData);
        free(bmPixelDataNew);
        return -1;
    }



    if(DEBUGGING){
        printf("writing file header\n");
    }
    // Write the file header
    fwrite(&bmFileHeaderNew.bfType,sizeof(bmFileHeaderNew.bfType),1,fileNew);
    fwrite(&bmFileHeaderNew.bfSize,sizeof(bmFileHeaderNew.bfSize),1,fileNew);
    fwrite(&bmFileHeaderNew.bfReversed1,sizeof(bmFileHeaderNew.bfReversed1),1,fileNew);
    fwrite(&bmFileHeaderNew.bfReversed2,sizeof(bmFileHeaderNew.bfReversed2),1,fileNew);
    fwrite(&bmFileHeaderNew.bfOffBits,sizeof(bmFileHeaderNew.bfOffBits),1,fileNew);
    if(DEBUGGING){
        printf("file header written\n");
    }



    if(DEBUGGING){
        printf("writing image header\n");
    }
    // Write the image header.
    fwrite(&bmImageHeaderNew.biSize,sizeof(bmImageHeaderNew.biSize),1,fileNew);
    fwrite(&bmImageHeaderNew.biWidth,sizeof(bmImageHeaderNew.biWidth),1,fileNew);
    fwrite(&bmImageHeaderNew.biHeight,sizeof(bmImageHeaderNew.biHeight),1,fileNew);
    fwrite(&bmImageHeaderNew.biPlanes,sizeof(bmImageHeaderNew.biPlanes),1,fileNew);
    fwrite(&bmImageHeaderNew.biBitCount,sizeof(bmImageHeaderNew.biBitCount),1,fileNew);
    fwrite(&bmImageHeaderNew.biCompression,sizeof(bmImageHeaderNew.biCompression),1,fileNew);
    fwrite(&bmImageHeaderNew.biSizeImage,sizeof(bmImageHeaderNew.biSizeImage),1,fileNew);
    fwrite(&bmImageHeaderNew.biXPelsPerMeter,sizeof(bmImageHeaderNew.biXPelsPerMeter),1,fileNew);
    fwrite(&bmImageHeaderNew.biYPelsPerMeter,sizeof(bmImageHeaderNew.biYPelsPerMeter),1,fileNew);
    fwrite(&bmImageHeaderNew.biClrUsed,sizeof(bmImageHeaderNew.biClrUsed),1,fileNew);
    fwrite(&bmImageHeaderNew.biClrImportant,sizeof(bmImageHeaderNew.biClrImportant),1,fileNew);
    if(DEBUGGING){
        printf("image header written\n");
    }



    if(DEBUGGING){
        printf("writing color table\n");
    }
    // Skip writing color table for 24-bit bitmaps.
    if(DEBUGGING){
        printf("color table skipped\n");
    }



    if(DEBUGGING){
        printf("writing pixel data\n");
    }
    // Write the pixel data.
    unsigned char tempColorNew=0;
    for(int i=0;i<bmImageHeaderNew.biWidth*bmImageHeaderNew.biHeight;++i){
        tempColorNew=bmPixelDataNew[i].rgbBlue;
        fwrite(&tempColorNew,sizeof(tempColorNew),1,fileNew);
        tempColorNew=bmPixelDataNew[i].rgbGreen;
        fwrite(&tempColorNew,sizeof(tempColorNew),1,fileNew);
        tempColorNew=bmPixelDataNew[i].rgbRed;
        fwrite(&tempColorNew,sizeof(tempColorNew),1,fileNew);
    }
    if(DEBUGGING){
        printf("pixel data written\n");
        printf("saved\n");
    }



    if(DEBUGGING){
        printf("exiting\n");
    }
    // Exit the program.
    fclose(file);
    fclose(fileNew);
    free(bmPixelData);
    free(bmPixelDataNew);
    if(DEBUGGING){
        printf("success!\n");
    }
    return 0;
}
