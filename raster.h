#ifndef UNTITLED_RASTER_H
#define UNTITLED_RASTER_H

#include "common.h"

class Raster {
public:
    typedef struct local{

        int x;
        int y;
        int num_local;

    }
            local;
    typedef struct tiempo{
        float CD;
        float IDW;
    }
            tiempo;

    float** read_tif_matrix(string name,int &m, int &n, int &scale,int &cell_null);
    void print_raster(float **mtt,int m, int n);
    void matrix_to_tiff(float** output_raster, int rows, int cols, int count, string name);
    void leer_localidades(float **map_local,int m, int n, map<int,local> &local_ord,int cell_null,int num_local);
    int contar_comunidades(float **mapa_local, int m, int n,int cell_null);
    int no_row(string name);
    void carga_requisitos(string name,map <int, float> &req_map);
    void guardar_tiempos(map <int, tiempo> time_ejecucion);
private:

};

#endif //UNTITLED_RASTER_H