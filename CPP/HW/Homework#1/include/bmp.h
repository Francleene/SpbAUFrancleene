//
// Created by Александр on 10.11.16.
//

#ifndef BMP_FILES_BMP_H
#define BMP_FILES_BMP_H

typedef unsigned char BYTE;
typedef int LONG;
typedef unsigned short WORD;
typedef unsigned int DWORD;

typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, * PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, * PBITMAPINFOHEADER;

typedef struct tagRGBTRIPLE {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} RGBTRIPLE, * PRGBTRIPLE;

void save_bmp(PBITMAPFILEHEADER file_header,
              PBITMAPINFOHEADER info_header,
              RGBTRIPLE ** image,
              LONG width,
              LONG height,
              char * file_path);

void save_fileheader(PBITMAPFILEHEADER file_header,
                     FILE * file);

void save_infoheader(PBITMAPINFOHEADER info_header,
                     FILE * file);

void save_rgbtriple(PRGBTRIPLE pixel,
                    FILE * file);

void save_indent(LONG lenth,
                 FILE * file);

void save_image(RGBTRIPLE ** image,
                LONG width,
                LONG height,
                FILE * file);

void load_bmp(PBITMAPFILEHEADER file_header,
              PBITMAPINFOHEADER info_header,
              RGBTRIPLE *** image,
              const char * file_path);

void load_fileheader(PBITMAPFILEHEADER file_header,
                      FILE * file);

void load_infoheader(PBITMAPINFOHEADER info_header,
                      FILE * file);

void load_rgbtriple(PRGBTRIPLE pixel,
                    FILE * file);

/*
 * Set new size and OffBits = 54.
 */

void change_fileheader(PBITMAPFILEHEADER file_header,
                       LONG width,
                       LONG height);

/*
 * Set new width, height and sizeImage, and biSize = 40
 */

void change_infoheader(PBITMAPINFOHEADER info_header,
                       LONG width,
                       LONG height);

/*
 * Crop src image and save it to new image.
 * Memory of new image is allocated by function.
 */

void crop(RGBTRIPLE ** src,
          RGBTRIPLE *** dist,
          LONG x,
          LONG y,
          LONG width,
          LONG height);

/*
 * Rotate src image and save it to new image.
 * Memory of new image is allocated by function
 */

void rotate(RGBTRIPLE ** src,
            RGBTRIPLE *** dist,
            LONG src_width,
            LONG src_height);

void free_image(RGBTRIPLE ** image,
                LONG height);

#endif //BMP_FILES_BMP_H
