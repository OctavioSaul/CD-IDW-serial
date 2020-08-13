#include "IDW.h"
#include "common.h"
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
void IDW::reset_Matrix(float **mat,int ROWS, int COLS,float val){
    for(int i=0; i<ROWS; i++)
        for(int j=0; j<COLS; j++)
            mat[i][j]=val;
}
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
void IDW::IDW_test(float req, float **cost_dist, float **&suma, int ROWS,  int COLS, float exp){
    int i,j;
    for ( i = 0; i < ROWS; i++)
        for ( j = 0; j < COLS; j++){
            if(cost_dist[i][j]>0)
                suma[i][j]+=req/pow( cost_dist[i][j],exp);
        }
}
/*
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
void IDW::IDW_cost_dist(float req,  int val_null, float **cost_dist, float **&final,float **&suma,int x_init, int y_init, int ROWS, int COLS, float exp){
    //--------------------------------------------------------------condiciones iniciales
    int total=1;
    int explorado=0;
    int fin=0;
    final[y_init][x_init]=0;//ubicación localidad
    map <int, cell> cost_map;
    map<int, cell >::iterator guardado;
    map<int, cell >::iterator actual;
    //------------------------------------------------------------------------------------------------------------------primera vez
    explorado+=movimientos(x_init, y_init,cost_dist,final,cost_map, ROWS ,COLS, val_null,explorado);
    guardado = cost_map.begin();
    while (total<=explorado){
        final[guardado->second.y][guardado->second.x]= req/pow( cost_dist[guardado->second.y][guardado->second.x],exp);
        suma[guardado->second.y][guardado->second.x]+=final[guardado->second.y][guardado->second.x];
        total++;
        guardado++;
    }
    guardado--;
    total--;
    actual = cost_map.begin();
    x_init = actual->second.x;
    y_init= actual->second.y;
    //------------------------------------------------------------------------------------------------------------------siguientes
    while(fin==0){
        explorado+=movimientos(x_init, y_init,cost_dist,final,cost_map, ROWS ,COLS, val_null,explorado);
        total++;
        guardado++;
        while (total<=explorado){
            final[guardado->second.y][guardado->second.x]= req/pow( cost_dist[guardado->second.y][guardado->second.x],exp);
            suma[guardado->second.y][guardado->second.x]+=final[guardado->second.y][guardado->second.x];
            total++;
            guardado++;
        }
        guardado--;
        total--;
        actual++;
        x_init = actual->second.x;
        y_init= actual->second.y;
        if(actual==guardado)
            fin=1;
    }
}
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
int IDW::movimientos(int x, int y, float **mat, float **&final, map <int, cell> &map_opciones, int ROWS, int COLS, int val_null,int explorado){
	int x_tmp=0, y_tmp= 0;
	int cont=1;
    cell posicion;//se crea la estructura
	for(int mov=1; mov<=8; mov++ ){//son 8 los posibles movimientos que puede hacer
		switch(mov) { //para cada movimiento se guardan las coordenas temporales x y  aunque no sufran cambios
			case 1:
				x_tmp= x ;
				y_tmp=y+1;
				break;
			case 2:
				x_tmp= x -1;
				y_tmp= y+1;
				break;
			case 3:
				x_tmp= x  -1;
				y_tmp=y;
				break;
			case 4:
				x_tmp= x -1;
				y_tmp=y-1;
				break;
			case 5:
				x_tmp= x ;
				y_tmp=y-1;
				break;
			case 6:
				x_tmp= x +1;
				y_tmp=y-1;
				break;
            case 7:
                x_tmp=x +1;
                y_tmp=y;
                break;
            case 8:
                x_tmp= x  +1 ;
                y_tmp= y + 1;
                break;
			default:
				break;
		}
        //if(x_tmp>0 && x_tmp<COLS && y_tmp>0 && y_tmp<ROWS && final[y_tmp][x_tmp]<0 && mat[y_tmp][x_tmp]!=val_null){//confirman que se pueda hacer el movimiento
        if(x_tmp>0)
            if(x_tmp<COLS)
                if(y_tmp>0)
                    if(y_tmp<ROWS)
                        if(final[y_tmp][x_tmp]<0)
                            if(mat[y_tmp][x_tmp]!=val_null){

        posicion.x = x_tmp;//guarda la posición en x del movimiento
            posicion.y = y_tmp;//guarda la posición en y del movimiento
            map_opciones.insert(pair<int, cell>(explorado+cont, posicion));//se guarda en el mapa, biomass o costo distancia como llave y la estructura con la ubicacion x y
            cont++;
        }
	}
	return (cont-1);
}
*/
