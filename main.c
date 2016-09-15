#include <stdio.h>
#include <stdlib.h>
#include "lfs_track.h"

FILE *input_file;
FILE *output_file;

int main()
{
    struct header_smx_track header;
    int selected_track = selectTrack();
    printf("---------------------------\n");
    switch(selected_track){
        case 1:
            printf("You choose Blackwood!\n");
            input_file = fopen("Blackwood_3DH.smx", "r+");
            output_file = fopen("Blackwood_3DH.obj", "w");
            break;
        case 2:
            printf("You choose Aston\n");
            input_file = fopen("Aston_3DH.smx", "r+");
            output_file = fopen("Aston_3DH.obj", "w");
            break;
        case 3:
            printf("You choose Autocross\n");
            input_file = fopen("Autocross_3DH.smx", "r+");
            output_file = fopen("Autocross_3DH.obj", "w");
            break;
        case 4:
            printf("You choose Fern Bay\n");
            input_file = fopen("Fern Bay_3DH.smx", "r+");
            output_file = fopen("Fern Bay_3DH.obj", "w");
            break;
        case 5:
            printf("You choose Kyoto\n");
            input_file = fopen("Kyoto_3DH.smx", "r+");
            output_file = fopen("Kyoto_3DH.obj", "w");
            break;
        case 6:
            printf("You choose South City\n");
            input_file = fopen("South City_3DH.smx", "r+");
            output_file = fopen("South City_3DH.obj", "w");
            break;
        case 7:
            printf("You choose Westhill\n");
            input_file = fopen("Westhill_3DH.smx", "r+");
            output_file = fopen("Westhill_3DH.obj", "w");
            break;
        default:
            printf("You choose Blackwood\n");
            input_file = fopen("Blackwood_3DH.smx", "r+");
            output_file = fopen("Blackwood_3DH.obj", "w");
            break;
    }
    if(!input_file){
        printf("Unable to access file!\n");
        return 1;
    }
    fread(&header, sizeof(struct header_smx_track), 1, input_file);
    printf("lfssmx: %s\n", header.lfssmx);
    printf("track name: %s\n", header.track_name);
    printf("dimension: %d\n", header.dimensions);
    printf("version: %d\n", header.version);
    printf("vertex_color: %d\n", header.vertex_color);
    printf("revision: %d\n", header.revision);
    printf("nb objects: %d\n", header.nb_objects);
    printf("col R: %d\n", header.ground_col_R);
    printf("col G: %d\n", header.ground_col_G);
    printf("col B: %d\n", header.ground_col_B);
    int i = 0, j = 0, k = 0;
    for(i = 0; i < 5 /*header.nb_objects*/; i++){
        struct object_smx_track object;
        //fseek(input_file,sizeof(struct object_smx_track)*i,SEEK_SET);
        fread(&object, sizeof(struct object_smx_track), 1, input_file);
        printf("Object n°%d\n", i);
        printf("center X: %.5f\n", (float)object.centerX/65536);
        printf("center Y: %.5f\n", (float)object.centerY/65536);
        printf("center Z: %.5f\n", (float)object.centerZ/65536);
        printf("radius: %.5f\n", (float)object.radius/65536);
        printf("nb points: %d\n", object.nb_points);
        printf("nb triangles: %d\n", object.nb_triangles);

        /*
        * Lecture des vertexes
        */
        struct point_smx_track *point;
        point = malloc(object.nb_points * sizeof(struct point_smx_track));
        printf("sizeof point struct: %d\n", sizeof(struct point_smx_track));
        // Je devrais lire grâce à la fonction fread object.nb_points de taille struct point_smx_track
        int nb_points_read = fread(point, sizeof(struct point_smx_track), object.nb_points, input_file);
        if(object.nb_points > nb_points_read){
            perror("Error ");
        }
        // Or la fonction renvoie quasiment tout le temps un nombre inférieur d'élements lus.
        printf("number of points read: %d\n", nb_points_read);
        fprintf(output_file, "o object%d\n", i);
        for(j = 0; j < object.nb_points; j++){
            printf("index point: %d\n", j);
            printf("X: %.5f\n", (float)point[j].X/65536);
            printf("Y: %.5f\n", (float)point[j].Y/65536);
            printf("Z: %.5f\n", (float)point[j].Z/65536);
            printf("color: %#x\n", point[j].color);
            fprintf(output_file, "v %.10f %.10f %.10f\n", (float)point[j].X/65536, (float)point[j].Y/65536, (float)point[j].Z/65536);
        }

        /*
        * Lecture des triangles
        */
        struct triangle_smx_track *triangle;
        triangle = malloc(object.nb_triangles * sizeof(triangle_smx_track));
        printf("sizeof triangles struct: %d\n", sizeof(struct triangle_smx_track));
        int nb_triangles_read = fread(triangle, sizeof(struct triangle_smx_track), object.nb_triangles, input_file);
        if(object.nb_triangles > nb_triangles_read){
            perror("Error ");
        }
        // Or la fonction renvoie quasiment tout le temps un nombre inférieur d'élements lus.
        printf("number of triangles read: %d\n", nb_triangles_read);
        for(j = 0; j < object.nb_triangles; j++){
            printf("index triangle: %d\n", j);
            printf("vertex A: %d\n", triangle[j].vertexA);
            printf("vertex B: %d\n", triangle[j].vertexB);
            printf("vertex C: %d\n", triangle[j].vertexC);
            fprintf(output_file, "f %d %d %d\n", triangle[j].vertexA + 1, triangle[j].vertexB + 1, triangle[j].vertexC + 1);
        }
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}

int selectTrack(){
    int selected_track = 0;
    printf("Welcome to track converter!\n");
    printf("---------------------------\n");
    printf("Select the track :\n");
    printf("   1 - Blackwood\n");
    printf("   2 - Aston\n");
    printf("   3 - Autocross\n");
    printf("   4 - Fern Bay\n");
    printf("   5 - Kyoto\n");
    printf("   6 - South City\n");
    printf("   7 - Westhill\n");
    scanf("%d", &selected_track);
    if(selected_track <= 0 || selected_track > 7){
        return selectTrack();
    }
    else{
        return selected_track;
    }
}
