#include "cost_dist.h"
#include "common.h"
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
int cuenta_global=0;
typedef struct l_dist{

    int x;
    int y;
    float costo;

}
        l_dist;
//------------------------------------------------------------------------------------------------------------------
map<double , l_dist > costos;
int start = 0;
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
float** Cost_dist::cost_distance(int inicio_x,int inicio_y,float **fricc, int m, int n,position array[]) {
    float**map_cost = new float*[m];
    for(int i=0;i<m;i++)
        map_cost[i] = new float[n];

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            map_cost[i][j]=1000000000000;
            if(fricc[i][j] < 0.0){
                map_cost[i][j]=-9999;
            }
        }
    }
    int count = 0;
    for(int i=0;i<1;i++) {
        map_cost[inicio_y][inicio_x]=0;
        count = movimientos_init(inicio_x, inicio_y,0, fricc, m, n, array);
        raster_cost(array, map_cost, count);
    }
    //(costos.size())>5
    for(int i=0;costos.size() > 1;i++){
        map<double,l_dist>::iterator it_1=costos.begin();
        count = movimientos(it_1->second.x, it_1->second.y,it_1->second.costo, fricc, m, n, array);
        raster_cost(array, map_cost, count);
        costos.erase(it_1);
    }
    return map_cost;

}
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
int Cost_dist::movimientos(int pos_x,int pos_y,float costo_acumulado,float **fricc, int m, int n, position *array) {
    int x_temp;
    int y_temp;
    int temp_temp = 0;
    int count=0;
    int mov[2][8]={{1,1,0,-1,-1,-1,0,1},
                   {0,1,1,1,0,-1,-1,-1}};
    for(int i=1;i<9;i++){
        x_temp = mov[0][i-1]+pos_x;
        y_temp = mov[1][i-1]+pos_y;
        //printf("\nx:%d  y:%d",x_temp,y_temp);
        if(x_temp<n && x_temp>=0 && y_temp<m && y_temp>=0 && fricc[y_temp][x_temp]>0.0){
            count++;
            if(i%2!=0){
                //array[i-temp_temp].val_fricc =costo_acumulado + (fricc[pos_y][pos_x]+fricc[y_temp][x_temp])/2;
                array[i-temp_temp].val_fricc =costo_acumulado + (fricc[y_temp][x_temp]);
                array[i-temp_temp].x=x_temp;
                array[i-temp_temp].y=y_temp;
                //fricc[pos_y][pos_x]+
            }
            else{
                //array[i-temp_temp].val_fricc =costo_acumulado + sqrt(2)*(fricc[pos_y][pos_x]+fricc[y_temp][x_temp])/2;
                array[i-temp_temp].val_fricc =costo_acumulado + sqrt(2)*(fricc[y_temp][x_temp]);
                array[i-temp_temp].x=x_temp;
                array[i-temp_temp].y=y_temp;

            }
        } else{
            temp_temp ++;
        }
    }
    return count;
}
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
float** Cost_dist::raster_cost(position *array,float **map_cost,int count) {
    struct l_dist array_1;
    for(int i=1;i<=count;i++){
        start ++;
        //printf("\n%d  fricc %f\n",i,map_cost[array[i].y][array[i].x]);
        if(map_cost[array[i].y][array[i].x] >= 0 and array[i].val_fricc >= 0)
        {
            //printf("\n%d,%d, v %f ", array[i].x, array[i].y, array[i].val_fricc);
            if(map_cost[array[i].y][array[i].x] > array[i].val_fricc)
            {
                map_cost[array[i].y][array[i].x] = array[i].val_fricc;
                array_1.x=array[i].x;
                array_1.y=array[i].y;
                array_1.costo=array[i].val_fricc;
                costos[array[i].val_fricc+(0.000001*start)]=array_1;
                //cuenta_global++;
            }

        }
    }
    //print_matrix(map_cost,11,11);
    //for (map<double,l_dist>::iterator it=costos.begin(); it!=costos.end(); ++it)
    //  printf("\nkey=%f  x= %d   y=  %d   cost=%f",it->first,it->second.x,it->second.y,it->second.costo);
    //printf("\n");
}
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
int Cost_dist::movimientos_init(int pos_x,int pos_y,float costo_acumulado,float **fricc, int m, int n, position *array){
    int x_temp;
    int y_temp;
    int temp_temp=0;
    int count=0;
    int mov[2][8]={{1,1,0,-1,-1,-1,0,1},
                   {0,1,1,1,0,-1,-1,-1}};
    for(int i=1;i<9;i++){
        x_temp = mov[0][i-1]+pos_x;
        y_temp = mov[1][i-1]+pos_y;
        //printf("\nx:%d  y:%d",x_temp,y_temp);
        if(x_temp<n && x_temp>=0 && y_temp<m && y_temp>=0 && fricc[y_temp][x_temp]>0.0){
            count++;
            //printf("\n%d\n",count);
            //printf("\nx:%d  y:%d",x_temp,y_temp);
            if(i%2!=0){
                //array[i-temp_temp].val_fricc = (fricc[pos_y][pos_x]+fricc[y_temp][x_temp])/2;
                array[i-temp_temp].val_fricc = (fricc[y_temp][x_temp]);
                array[i-temp_temp].x=x_temp;
                array[i-temp_temp].y=y_temp;

            }
            else{
                //array[i-temp_temp].val_fricc = sqrt(2)*(fricc[pos_y][pos_x]+fricc[y_temp][x_temp])/2;
                array[i-temp_temp].val_fricc = sqrt(2)*(fricc[y_temp][x_temp]);  //metodo pushroom
                array[i-temp_temp].x=x_temp;
                array[i-temp_temp].y=y_temp;

            }
        } else{
            temp_temp ++;
        }
    }
    return count;
}