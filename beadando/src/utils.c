#include "utils.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

void genGrid(double grid[60][60][2]){
    int i,j;
    double offset = 0.5f;
    double grid_i,grid_j;
    double r_o_i, r_o_j;
    for(i = 0;i < 60;i++){
        for(j = 0;j < 60;j++){
            //rácspontok elcsusztatása
            grid_i = i + offset;
            grid_j = j + offset;
            //random offset gen
            r_o_i = genGridRandomOffset();
            r_o_j = genGridRandomOffset();
            grid_i += r_o_i;
            grid_j += r_o_j;
            grid[i][j][0] = grid_i;
            grid[i][j][1] = grid_j;
            //printf("grid[%d][%d][0] = %f\n", i,j,grid_i);
            //printf("grid[%d][%d][1] = %f\n", i,j,grid_j);
        }
    }
}

double genGridRandomOffset(){
    srand(time(NULL));
    double r;
    r =  (double)rand()/RAND_MAX*1.0-0.5;
    // printf("%f\n", r);
    return r;
}

