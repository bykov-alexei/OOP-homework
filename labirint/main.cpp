#include <iostream>
using namespace std;

unsigned char * read_file(int & height, int & width) {
    FILE * f = fopen("Dnk_labirint.bmp", "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);
    width = *(int *)&info[18];
    height = *(int *)&info[22];
    int size = 3 * width * height;
    unsigned char * data = new unsigned char[size];
    fread(data, sizeof(unsigned char), size, f);
    return data;
}

int ** get_field(unsigned char * data, int height, int width) {
    int ** field = new int *[height];
    for (int i = 0; i < height; i++) {
        field[i] = new int[width];
    }
    for (int i = 0; i < 3 * width * height; i = i + 3) {
        int y = (i / 3) / width;
        int x = (i / 3) % width;
        if (data[i] == 255 && data[i + 1] == 255 && data[i + 2] == 255) {
            field[y][x] = -1;
        } else if (data[i] == 0 && data[i + 1] == 0 && data[i + 2] == 0) {
            field[y][x] = -2;
        } else if (data[i + 2] > 150) {
            field[y][x] = -3;
        } else if (data[i + 1] > 150) {
            field[y][x] = 0;
        }
    }
    return field;
}

void wave(int ** field, int height, int width) {
    int checked = 0;
    int d = 0;
    while (checked != height * width) {
        checked = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (field[i][j] == -1) {
                    checked++;
                }
                if (field[i][j] == d) {
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (field[i+dy][j+dx] == -1) {
                                field[i+dy][j+dx] = d + 1;
                            }
                            if (field[i+dy][j+dx] == -3) {
                                field[i+dy][j+dx] = d + 1;
                                return;
                            }
                        }
                    }
                }
            }
        }
        d++;
    }
}

void mark_path(int ** field, int height, int width) {
    int x, y;
    int d = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (field[i][j] > d) {
                y = i;
                x = j;
                d = field[i][j];
            }
        }
    }
    while (d != 0) {
        bool found = false;
        for (int dx = -1; dx <= 1 && !found; dx++) {
            for (int dy = -1; dy <= 1 && !found; dy++) {
                if (field[y+dy][x+dx] == d - 1) {
                    field[y+dy][x+dx] = -4;
                    y += dy;
                    x += dx;
                    d--;
                    found = true;
                }
            }
        }
    }
    
}

void save_field(int ** field, int height, int width) {
    FILE * fe = fopen("Dnk_labirint.bmp", "rb");
    FILE * fo = fopen("Result.bmp", "wb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, fe);
    fwrite(info, sizeof(unsigned char), 54, fo);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char bgr[] = {255, 255, 255};
            if (field[i][j] == -2) {
                bgr[0] = 0;
                bgr[1] = 0;
                bgr[2] = 0;
            } else if (field[i][j] == -3) {
                bgr[0] = 0;
                bgr[1] = 0;
            } else if (field[i][j] == 0) {
                bgr[0] = 0;
                bgr[2] = 0;
            } else if (field[i][j] == -4) {
                bgr[1] = 0;
                bgr[2] = 0;
            }
            fwrite(bgr, sizeof(unsigned char), 3, fo);
        }
    }
    fclose(fo);
    fclose(fe);
}

int main() {
    int height, width;
    unsigned char * data = read_file(height, width);
    int ** field = get_field(data, height, width);
    wave(field, height, width);
    mark_path(field, height, width);
    save_field(field, height, width);
}