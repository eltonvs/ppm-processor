#define header "P3"

FILE *file_img;
char file_name[50], op[3];
int w, h, MAX, comp;

typedef struct {
    int r;
    int g;
    int b;
} Pixel;
