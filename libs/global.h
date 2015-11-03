#define header "P3"

FILE *img_file;
char file_name[50], op[3];
int w, h, MAX, comp;

typedef struct {
    int r;
    int g;
    int b;
} Pixel;
