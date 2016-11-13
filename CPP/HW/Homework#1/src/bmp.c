//
// Created by Александр on 10.11.16.
//
#include <stdlib.h>
#include <stdio.h>

#include "../include/bmp.h"

void load_fileheader(PBITMAPFILEHEADER file_header,
                      FILE * file)
{
    fread(&file_header->bfType, sizeof(WORD), 1, file);
    fread(&file_header->bfSize, sizeof(DWORD), 1, file);
    fread(&file_header->bfReserved1, sizeof(WORD), 1, file);
    fread(&file_header->bfReserved2, sizeof(WORD), 1, file);
    fread(&file_header->bfOffBits, sizeof(DWORD), 1, file);
}

void load_infoheader(PBITMAPINFOHEADER info_header,
                       FILE * file)
{
    fread(&info_header->biSize, sizeof(DWORD), 1, file);
    fread(&info_header->biWidth, sizeof(LONG), 1, file);
    fread(&info_header->biHeight, sizeof(LONG), 1, file);
    fread(&info_header->biPlanes, sizeof(WORD), 1, file);
    fread(&info_header->biBitCount, sizeof(WORD), 1, file);
    fread(&info_header->biCompression, sizeof(DWORD), 1, file);
    fread(&info_header->biSizeImage, sizeof(DWORD), 1, file);
    fread(&info_header->biXPelsPerMeter, sizeof(LONG), 1, file);
    fread(&info_header->biYPelsPerMeter, sizeof(LONG), 1, file);
    fread(&info_header->biClrUsed, sizeof(DWORD), 1, file);
    fread(&info_header->biClrImportant, sizeof(DWORD), 1, file);
}

void load_rgbtriple(PRGBTRIPLE pixel,
                    FILE * file)
{
    fread(&pixel->rgbtBlue, sizeof(BYTE), 1, file);
    fread(&pixel->rgbtGreen, sizeof(BYTE), 1, file);
    fread(&pixel->rgbtRed, sizeof(BYTE), 1, file);
}

RGBTRIPLE ** get_array(LONG width,
                       LONG height)
{
    RGBTRIPLE ** image = (RGBTRIPLE **)malloc(height * sizeof(RGBTRIPLE *));
    for (LONG i = 0; i < height; i++) {
        image[i] = (RGBTRIPLE *)malloc(width * sizeof(RGBTRIPLE));
    }
    return image;
}

int get_trash_len(int width) {
    return (width % 4 ? width % 4 : 0);
}

void load_image(RGBTRIPLE ** image,
                LONG width,
                LONG height,
                FILE * file)
{
    int trash_len = get_trash_len(width);
    for (LONG i = height - 1; i >= 0; i--) {
        for (LONG j = 0; j < width; j++) {
            load_rgbtriple(&image[i][j], file);
        }
        fseek(file, trash_len, SEEK_CUR);
    }
}

void load_bmp(PBITMAPFILEHEADER file_header,
              PBITMAPINFOHEADER info_header,
              RGBTRIPLE *** image,
              const char * file_path)
{
    FILE * file = fopen(file_path, "rb");

    if (file == NULL) {
        printf("I can't open this file, sorry :( Please, check your file and try again!\n");
        exit(1);
    }

    load_fileheader(file_header, file);
    load_infoheader(info_header, file);

    fseek(file, file_header->bfOffBits, SEEK_SET);
    *image = get_array(info_header->biWidth, info_header->biHeight);

    load_image(*image, info_header->biWidth, info_header->biHeight, file);

    fclose(file);
}

void crop(RGBTRIPLE ** src,
          RGBTRIPLE *** dist,
          LONG x,
          LONG y,
          LONG width,
          LONG height)
{
    *dist = get_array(width, height);

    for (LONG i = 0; i < height; i++) {
        for (LONG j = 0; j < width; j++) {
            (*dist)[i][j] = src[y + i][x + j];
        }
    }
}

void rotate(RGBTRIPLE ** src,
            RGBTRIPLE *** dist,
            LONG src_width,
            LONG src_height)
{
    *dist = get_array(src_height, src_width);

    for (LONG i = 0; i < src_width; i++) {
        for (LONG j = 0; j < src_height; j++) {
            (*dist)[i][j] = src[src_height - j - 1][i];
        }
    }
}

LONG get_indent(LONG width) {
    return (3 * width % 4) ? (4 - 3 * width % 4) : 0;
}

DWORD get_sizeof_image(LONG width,
                       LONG height)
{
    return (DWORD)(width + get_indent(width)) * height;
}

void change_fileheader(PBITMAPFILEHEADER file_header,
                       LONG width,
                       LONG height)
{
    file_header->bfSize = 54 + get_sizeof_image(width, height);
    file_header->bfOffBits = 54;
}

void change_infoheader(PBITMAPINFOHEADER info_header,
                       LONG width,
                       LONG height)
{
    info_header->biSize = 40;
    info_header->biWidth = width;
    info_header->biHeight = height;
    info_header->biSizeImage = get_sizeof_image(width, height);
}

void save_bmp(PBITMAPFILEHEADER file_header,
              PBITMAPINFOHEADER info_header,
              RGBTRIPLE ** image,
              LONG width,
              LONG height,
              char * file_path)
{
    FILE * file = fopen(file_path, "wb");

    if (file == NULL) {
        printf("I can't save this file, sorry :( But you can try again!\n");
    }

    save_fileheader(file_header, file);
    save_infoheader(info_header, file);
    save_image(image, width, height, file);

    fclose(file);
}

void save_fileheader(PBITMAPFILEHEADER file_header,
                     FILE * file)
{
    fwrite(&file_header->bfType, sizeof(WORD), 1, file);
    fwrite(&file_header->bfSize, sizeof(DWORD), 1, file);
    fwrite(&file_header->bfReserved1, sizeof(WORD), 1, file);
    fwrite(&file_header->bfReserved2, sizeof(WORD), 1, file);
    fwrite(&file_header->bfOffBits, sizeof(DWORD), 1, file);
}

void save_infoheader(PBITMAPINFOHEADER info_header,
                     FILE * file)
{
    fwrite(&info_header->biSize, sizeof(DWORD), 1, file);
    fwrite(&info_header->biWidth, sizeof(LONG), 1, file);
    fwrite(&info_header->biHeight, sizeof(LONG), 1, file);
    fwrite(&info_header->biPlanes, sizeof(WORD), 1, file);
    fwrite(&info_header->biBitCount, sizeof(WORD), 1, file);
    fwrite(&info_header->biCompression, sizeof(DWORD), 1, file);
    fwrite(&info_header->biSizeImage, sizeof(DWORD), 1, file);
    fwrite(&info_header->biXPelsPerMeter, sizeof(LONG), 1, file);
    fwrite(&info_header->biYPelsPerMeter, sizeof(LONG), 1, file);
    fwrite(&info_header->biClrUsed, sizeof(DWORD), 1, file);
    fwrite(&info_header->biClrImportant, sizeof(DWORD), 1, file);
}

void save_rgbtriple(PRGBTRIPLE pixel,
                    FILE * file)
{
    fwrite(&pixel->rgbtBlue, sizeof(BYTE), 1, file);
    fwrite(&pixel->rgbtGreen, sizeof(BYTE), 1, file);
    fwrite(&pixel->rgbtRed, sizeof(BYTE), 1, file);
}

void save_indent(LONG length,
                 FILE * file)
{
    BYTE zero = 0;
    for (int i = 0; i < length; i++) {
        fwrite(&zero, sizeof(BYTE), 1, file);
    }
}

void save_image(RGBTRIPLE ** image,
                LONG width,
                LONG height,
                FILE * file)
{
    LONG indent = get_indent(width);

    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            save_rgbtriple(&image[i][j], file);
        }
        save_indent(indent, file);
    }
}

void free_image(RGBTRIPLE ** image,
                LONG height)
{
    for (int i = 0; i < height; i++) {
        free(image[i]);
    }
    free(image);
}
