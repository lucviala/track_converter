#include<stdint.h>
#include<stdlib.h>
#ifndef LFS_TRACK_H_INCLUDED
#define LFS_TRACK_H_INCLUDED

typedef struct header_smx_track{
    char lfssmx[6];
    uint8_t version;
    uint8_t revision;
    uint8_t smx_version;
    uint8_t dimensions;
    uint8_t resolution;
    uint8_t vertex_color;
    uint8_t empty1[4];
    char track_name[32];
    uint8_t ground_col_R;
    uint8_t ground_col_G;
    uint8_t ground_col_B;
    uint8_t empty2[9];
    int nb_objects;
}header_smx_track;

typedef struct object_smx_track{
    int centerX;
    int centerY;
    int centerZ;
    int radius;
    int nb_points;
    int nb_triangles;
}object_smx_track;

typedef struct point_smx_track{
    int X;
    int Y;
    int Z;
    int color;
}point_smx_track;

typedef struct triangle_smx_track{
    uint16_t vertexA;
    uint16_t vertexB;
    uint16_t vertexC;
    uint16_t empty1;
}triangle_smx_track;

typedef struct footer_smx_track{
    int nb_cp_objects;
}footer_smx_track;


#endif // LFS_TRACK_H_INCLUDED
