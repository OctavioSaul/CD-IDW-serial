#include "common.h"
#ifndef VECTORIZED_MATRIX_VECTORIZED_H
#define VECTORIZED_MATRIX_VECTORIZED_H
#endif
typedef struct cell{
    int x;
    int y;
}
        cell;
class IDW{
public:

	void reset_Matrix(float **mat,  int ROWS,  int COLS, float val);
    //si CD ya toma en cuenta la distancia de la celda a la comunidad entonces no es necesario que lo calule IDW
    //puede simplemente explorar la matriz de CD y hacer el cálculo para las celdas que sean mayores a cero
    void IDW_test(float req, float **cost_dist, float **&suma, int ROWS,  int COLS, float exp);
    //estos metodos sirven cuando CD no toma en cuenta a distancia de la celda explorada a la comunidad
    //void IDW_cost_dist(float req, int val_null, float **cost_dist, float **&final,float **&suma,int x_init,  int y_init,  int ROWS,  int COLS, float exp);
    //int movimientos(int x, int y, float **mat, float **&final, map <int, cell> &map_opciones , int ROWS, int COLS, int val_null, int explorado);

private:
};