//
// Created by otavio on 05/03/20.
//
#include "raster.h"
#include "common.h"
typedef struct local{

    int x;
    int y;

}
        local;

using namespace std;
//-------------------------------------------------------------------------------------------------------------------------
int ROWS,COLS;
float** fricc;
double adfGeoTransform[6];
//-------------------------------------------------------------------------------------------------------------------------
float** Raster::read_tif_matrix(std::string file,int &m, int &n, int &scale,int &cell_null)
{
    //printf("leyendo tiff \n");
    GDALDataset *dataset;
    char **MD;
    char *info;
    GDALAllRegister();
    string ds = file;
    dataset = (GDALDataset *) GDALOpen(ds.c_str(), GA_ReadOnly);
    GDALRasterBand  *poBand;

    poBand = dataset->GetRasterBand(1);
    dataset->GetGeoTransform( adfGeoTransform );

    int nXSize = poBand->GetXSize();
    int nYSize = poBand->GetYSize();
    scale = adfGeoTransform[1];

    m = nYSize;
    n = nXSize;

    dataset->GetGeoTransform( adfGeoTransform );
    scale = adfGeoTransform[1];
    cell_null = poBand->GetNoDataValue();  //read null value of cell

    ROWS = nYSize; COLS = nXSize;
    fricc = new float*[ROWS];
    for(int i = 0; i< ROWS; ++i) {
        //costosAux[i] = new int[COLS];
        fricc[i] = new float[COLS];
    }

    //GDALDataType dataType = poBand->GetRasterDataType();
    float *pBuf = new float[nYSize * nXSize];

    poBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize, pBuf, nXSize, nYSize, GDT_Float32, 0, 0);

    int location;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++){
            location = (nXSize * (i)) + j;
            fricc[i][j] = *(pBuf+location);
        }
    }

    return fricc;
}
//-------------------------------------------------------------------------------------------------------------------------
void Raster::print_raster(float **mtt, int m, int n) {
    printf("imprimiento raster \n");
    for(int i=0; i< m; i++){
        for(int j =0; j < n; j++){
            printf(" %f ",mtt[i][j]);
        }
        printf("\n");
    }
}
//-------------------------------------------------------------------------------------------------------------------------
void Raster::matrix_to_tiff(float **output_raster, int rows, int cols, int count,string name) {
    //printf("convirtiendo matriz a tiff\n");
    GDALDataset *poDstDS;

    GDALDriver *poDriver;
    OGRSpatialReference oSRS;
    string fileName = name + to_string(count) + ".tif";
    cout << fileName << endl;
    poDriver = GetGDALDriverManager()->GetDriverByName("Gtiff");
    poDstDS = poDriver->Create( fileName.c_str(), cols, rows, 1, GDT_Float32, NULL);

    GDALRasterBand *poBand;
    float *pBuf = new float[rows * cols], maxVal = 0;
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pBuf[i * cols + j] = output_raster[i][j];
            if(output_raster[i][j] <=0)
                pBuf[i * cols + j] = -9999;
            if(output_raster[i][j] > maxVal)
                maxVal = output_raster[i][j];
        }
    }

    poBand = poDstDS->GetRasterBand(1);
    poDstDS->GetRasterBand(1)->SetNoDataValue(-9999);
    poBand->RasterIO( GF_Write, 0, 0, cols, rows,
                      pBuf, cols, rows, GDT_Float32, 0, 0 );
    GDALClose( (GDALDatasetH) poDstDS );
   // cout << fixed << "Max Val: " << maxVal << endl;
}
//-------------------------------------------------------------------------------------------------------------------------
void Raster::leer_localidades(float **map_local,int m, int n, map<int,local> &local_ord,int cell_null,int num_local) {
    struct local array;
    int local_1=0;
    //printf("\nleyendo comunidades \n");

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(map_local[i][j] != cell_null) {
                array.x = j;
                array.y = i;
                local_ord[(int)map_local[i][j]] = array;
                local_1 ++ ;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------
int Raster::contar_comunidades(float **mapa_local, int m, int n,int cell_null) {
    int count=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(mapa_local[i][j] != cell_null) {
                count++;
            }
        }
    }
    printf("el total de comunidades es %d\n",count);
    return count;
}
//-------------------------------------------------------------------------------------------------------------------------
int Raster::no_row(string name){
    int counter = 0;
    ifstream file(name.c_str());
    string data;
    while(getline(file,name))
        counter++;
    return counter;
}
//-------------------------------------------------------------------------------------------------------------------------
void Raster::carga_requisitos(string name,map <int, float> &req_map){

    int cont;
    ifstream file(name.c_str());
    stringstream buffer;
    buffer << file.rdbuf();
    string key;
    string val;
    //no nos interesa cargar los titulos de la tabla
    getline(buffer,key,',');
    getline(buffer, val, '\n');
    cont=no_row(name);
    cont--;
    while(cont>0) {
        getline(buffer,key,',');
        getline(buffer, val, '\n');
        req_map.insert(pair<int, float>(atof(key.c_str()),atof(val.c_str())));//se guarda en el mapa, el no. de localidad como llave y el requisito de biomasa
        cont--;
    }
}
//-------------------------------------------------------------------------------------------------------------------------
void Raster::guardar_tiempos(map <int, tiempo> time_ejecucion){
    float time_final_cost_dist=0,time_final_IDW=0;
    float cont=0;
    FILE *fichero;
    fichero = fopen("tiempos.csv", "at");
    fprintf (fichero, "No_localidad,tiempo_CD,tiempo_IDW\n");
    map<int, tiempo >::iterator s = time_ejecucion.begin();
    while (s != time_ejecucion.end() ) {
        fprintf (fichero, "%d,%f,%f\n",s->first, s->second.CD, s->second.IDW);
        time_final_cost_dist+= s->second.CD;
        time_final_IDW +=s->second.IDW;
        s++;
        cont++;
    }
    fclose(fichero);
    cout <<"-------------------------------------"<< endl;
    printf("El total de localidades exploradas cuyos requisitos son distintos a cero son: %f\n",cont);
    printf("tiempo promedio costo distancia:%f segundos \n",time_final_cost_dist/cont);
    printf("tiempo costo distancia total:%f segundos\n",time_final_cost_dist);
    printf("tiempo promedio de IDW: %f segundos\n", time_final_IDW/cont);
    printf("tiempo IDW final: %f segundos\n", time_final_IDW);
}