/* Fuentebuena Guardon <tfuentebuena@est.frba.utn.edu.ar>
 * Nicolás Savinelli <rsavinelli@est.frba.utn.edu.ar>
 * José F.Terraza <jterraza@est.frba.utn.edu.ar> */


#include <iostream>
#include <fstream>

/* ARCHIVOS PARA LEER DATOS */
#define CATALOGUE_FILE "catalogue.txt"
#define PRODUCTION_FILE "production.txt"

/* MACROS DEFINIDAS SEGÚN CONSIGNA */
#define PRODUCTS 6
#define COLOURS 3

using namespace std;

int main(void)
{
    /* CATALOGO ***************************************************************
     * ************************************************************************/

    string products_and_colours[PRODUCTS + COLOURS];

    /* products_and_colours[PRODUCTS+COLOURS] almacena en un vector de strings
     * los nombres de los productos y los colores leidos del archivo
     * "catalogue.txt" de manera consecutiva.*/

    string catalogue[PRODUCTS][COLOURS];

    /* catalogue[PRODUCTS][COLOURS] almacena todas las combinaciones de
     * producto-color posibles en una matriz de strings.
     * Esto es, suponiendo la posición (i, j) tenemos:
     * products_and_colours[i][j] == "producto_i color_j"
     * ************************************************************************/

    /* DATOS DE PRODUCCIÓN ****************************************************
     * ************************************************************************/

    int production[PRODUCTS][COLOURS];

    /* production[PRODUCTS][COLOURS] almacena en una matriz de ints las 
     * cantidades producidas de cada producto en cada color. Este enfoque nos 
     * permite,independientemente del orden en que los colores aparezcan en el 
     * archivo, poder interpretar la producción.*/

    int production_batch[PRODUCTS][COLOURS];

    /* production_batch[PRODUCTS][COLOURS] almacena en una matriz de ints la
     * cantidad de lotes de producción para cada combinación producto-color. 
     * Es decir, por cada ocurrencia de "cantidad producida" de un combinación,
     * se incrementa en uno la misma significando los lotes.
     * ************************************************************************/

    return 0;
}
