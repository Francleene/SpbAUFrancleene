#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/bmp.h"

int is_number(char * str)
{
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

void check_tool(int argc, char * argv[])
{
    if (argc != 8 || strcmp(argv[1], "crop-rotate")) {
        printf("You made a mistake :(\nPlease, usage: ./main crop-rotate <in-bmp> <out-bmp> <x> <y> <w> <h>\n");
        exit(1);
    }
    for (int i = 4; i < 8; i++) {
        if(!is_number(argv[i])) {
            printf("Sorry, but %s is not a number :(\n", argv[i]);
            exit(1);
        }
    }
}

void check_size(int bmp_width, int bmp_height,
                int x, int y,
                int width, int height)
{
    if (x < 0 || y < 0) {
        printf("You entered too small start position :( But you can try again!\n");
        exit(1);
    }
    if (bmp_width <= x || bmp_height <= y) {
        printf("You entered too big start position :( But you can try again!\n");
        exit(1);
    }
    if (width < 0) {
        printf("You entered too small width :( But you can try again!\n");
        exit(1);
    }
    if (height < 0) {
        printf("You entered too small height :( But you can try again!\n");
        exit(1);
    }
    if (x + width > bmp_width) {
        printf("You entered too big width :( But you can try again!\n");
        exit(1);
    }
    if (y + height > bmp_height) {
        printf("You entered too big height :( But you can try again!\n");
        exit(1);
    }
}

int main(int argc, char ** argv)
{
    check_tool(argc, argv);

    char * src_bmp = argv[2];
    char * dist_bmp = argv[3];

    int x = atoi(argv[4]);
    int y = atoi(argv[5]);

    int width = atoi(argv[6]);
    int height = atoi(argv[7]);

    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;

    RGBTRIPLE ** image = NULL;
    load_bmp(&file_header, &info_header, &image, src_bmp);

    int bmp_width = info_header.biWidth;
    int bmp_height = info_header.biHeight;

    check_size(bmp_width, bmp_height, x, y, width, height);

    RGBTRIPLE ** croped_image = NULL;
    crop(image, &croped_image, x, y, width, height);

    free_image(image, bmp_height);

    RGBTRIPLE ** rotated_image = NULL;
    rotate(croped_image, &rotated_image, width, height);

    free_image(croped_image, height);

    change_fileheader(&file_header, height, width);
    change_infoheader(&info_header, height, width);

    save_bmp(&file_header, &info_header, rotated_image, height, width, dist_bmp);

    free_image(rotated_image, width);

    return 0;
}