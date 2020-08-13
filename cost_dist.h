//
// Created by otavio on 10/06/20.
//

#ifndef VERSION_2_RASTER_COST_DIST_H
#define VERSION_2_RASTER_COST_DIST_H
class Cost_dist {
public:

    typedef struct position{

        int x;
        int y;
        float val_fricc;

    }
            position;

    float** cost_distance(int inicio_x,int inicio_y,float **fricc,int m, int n,position array[]);
    int movimientos(int pos_x,int pos_y,float costo_acumulado,float **fricc,int m, int n,position array[]);
    int movimientos_init(int pos_x,int pos_y,float costo_acumulado,float **fricc,int m, int n,position array[]);
    float** raster_cost(position array[],float **map_cost,int count);

private:
};

#endif //VERSION_2_RASTER_COST_DIST_H
