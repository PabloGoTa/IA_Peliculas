//
//  files.h
//
//
//  Created by Cesar Angeles on 07/09/2020.
//

#ifndef files_h
#define files_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef files_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/* files.h -- Function prototypes */

/**
 * Instanciates a new file pointer identified via its name and mode.
 * @param
 *  name (char *):
 *      Name of the file
 *  mode (char *):
 *      Mode of file to be opened {r, rb, a, ab, w, wb}
 *
 * @return FILE * opened_file.
*/
EXTERN FILE * file_new(char *name, char *mode);



/**
 * Writes a bidimensional buffer array into a file.
 * @param
 *  file (FILE *):
 *      Storage file
 *  columns (size_t ):
 *      length of the buffer array
 *  buff [ ][columns] (long double):
 *      RAM matrix
 *  rows (size_t):
 *      width of the storage buffer
 *
 * @return void.
*/

EXTERN void file_num_write(FILE * file, size_t columns, long double buff[] [columns], size_t rows);

/**
 * Created by Pablo Gómez Tagle
 * Reads a file and returns the number of lines
 * @param
 *  file (FILE *):
 *      Storage file
 *
 *
 * @return int.
        Number of lines
*/
EXTERN int file_num_lines(FILE * file);

/**
 * Created by Pablo Gómez Tagle
 * Writes a file from an array
 * @param
 *  file (FILE *):
 *      Storage file
 *  data[] (double)
 *      Array of numbers
 *  numLines(int):
 *      Number of numbers
 *
 *
 * @return int.
        Number of lines
*/
EXTERN void writeCSV (FILE * fp, double data[], int numLines);
/**
 * Created by Pablo Gómez Tagle
 * Writes a file from an array
 * @param
 *  fp (FILE *):
 *      Storage file
 *  prom (double)
 *      Double number
 *  mediana (double)
 *      Double number
 *  moda (double)
 *     Double number
 *  desv (double)
 *      Double number
 *  dist (double)
 *      Double number
 *  rango1 (double)
 *      Double number
 *  rango2 (double)
 *      Double number
 *
 *
 * @return void.
*/

EXTERN void writeResults (FILE * fp, double prom, double mediana, double moda, double desv, double dist, double rango1, double rango2);

/**
 * Created by Pablo Gómez Tagle
 * Opens a pipe to gnuplot and genetates a graph
 * @param
 *    void
 * @return void.
*/
EXTERN void GNU_plot(void);
/**
 * Created by Pablo Gómez Tagle
 * Counts the number of ',' in a single line of a csv file.
 * @param
 *    file (FILE)
 * @return int: number of ','.
*/
EXTERN int file_num_columas(FILE *file);


/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos, Giovanni Josue Venegas
 * Creates matrix of size [colum][reng].
 * @param
 *    reng (int)
 *    colum(int)
 * @return double**: matrix.
*/
EXTERN double **crearMatriz(int reng, int colum);

/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos, Giovanni Josue Venegas
 * Gets numbers from a CSV file and saves them into a matrix of size [colum][reng].
 * @param
 *    reng (int)
 *    colum(int)
 *    fp(FILE)
 *    data(double)
 * @return double**: matrix.
*/

EXTERN double **getData(int colums, FILE *fp, double *data[], int reng);

/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos
 * Llena una matriz de número aleatorios.
 * @param
 *    *matriz[] (double)
 *    colum(int)
 *    reng(int)
 * @return double**: matrix.
*/
EXTERN double **llenarRandom(double *matriz[], int reng, int colums);


/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos
 * Entrena el algoritmo una vez.
 * @param
 *    *e (double)
 *      error de la iteración
 *    *usuarioCat[] (double)
 *      matriz de usuarios y sus afinidades
 *    *cates[] (double)
 *      matriz de películas y sus categorías
 *    numUsuarios (int)
 *      número de usuarios
 *    *userRating (double)
 *      matriz de usuarios y ratings a peliculas
 *    numRat (int)
 *      numero de ratings que hay
 * @return double**: matrix.
*/
EXTERN double **realizarEpoc(double *e, double *usuarioCat[], double *cates[], int numUsuarios, double *userRating[], int numRatings);

/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos
 * Crea una matriz de tipo char
 * @param
 *    colum(int)
 *    reng(int)
 * @return double**: matrix.
*/
EXTERN char **crearMatrizUsu(int reng, int colum);

/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos.
 * Gets numbers from a text file and saves them into a matrix of size [colum][reng].
 * @param
 *    reng (int)
 *    colum(int)
 *    fp(FILE)
 *    data(double)
 * @return double**: matrix.
*/
EXTERN char **getUsuarios(int colums, FILE *fp, char *data[], int reng);

/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos.
 * Gets numbers from a text file and saves them into a matrix of size [colum][reng].
 * @param
 *    reng (int)
 *    colum(int)
 *    fp(FILE)
 *    data(double)
 * @return double**: matrix.
*/
EXTERN char **getDataUsu(int colums, FILE *fp, char *data[], int reng);

/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos.
 * Gets numbers from a text file and saves them into a matrix of size [colum][reng].
 * @param
 *    reng (int)
 *    colum(int)
 *    fp(FILE)
 *    data(double)
 * @return double**: matrix.
*/
EXTERN char **crearMatrizUsu(int colum, int reng);

/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos.
 * Recomienda una película a un usuario.
*/
EXTERN void realizarRecomendacion(char **idPeliculas, char **idUsuarios, double **usuarioCat, double **peliCat, double **usRat, int numUsuarios, int numRat, int numPelis);

/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos.
 * Relaciona películas
 *  @param
 *   **idPeliculas (char)
 *   ** peliCat(double)
 *   numPelis(int)
*/
EXTERN void peliculasIguales(char **idPeliculas, double **peliCat, int numPelis);

/**
 * Created by Pablo Gómez Tagle, Axel Alejandro Campos.
 * Relaciona películas
 *  @param
 *   **idUsuarios (char)
 *   **usuarioCat(double)
 *   numUsuarios(int)
*/
EXTERN void usuariosIguales(char **idUsuarios, double **usuarioCat, int numUsuarios);


#undef files_IMPORT
#undef EXTERN



#endif /* files_h */
