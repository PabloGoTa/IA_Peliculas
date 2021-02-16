#include "files.h"

// comedia, accion, drama, fantasia


int main(void)
{
  FILE *fp, *fr, *fu, *fd, *fa;
  int reng, colum, i, j, numUsuarios, numPelis, k, op;
  double **peliCat;
  double **usRat;
  double **usuarioCat;
  double e = 1, pp = 0;
  char **idUsuarios;
  char **idPeliculas;
  double arrayError[500];

  //Matriz de usuarios y su ID
  fu = file_new("Usuarios.txt", "r");
  numUsuarios = file_num_lines(fu);
  idUsuarios = crearMatrizUsu(10 ,numUsuarios);
  idUsuarios = getDataUsu(10, fu, idUsuarios, numUsuarios);
  printf("\nSe creó la lista de usuarios\n");

  //Matriz de peliculas y su ID
  fd = file_new("idPeliculas.txt", "r");
  numPelis = file_num_lines(fd);
  idPeliculas = crearMatrizUsu(100, numUsuarios);
  idPeliculas = getDataUsu(100, fd, idPeliculas, numPelis);
  printf("\nSe creó la lista de películas\n");

  //Matriz de pelicula vs categorias (Feature de peliculas)
  fp = file_new("peliVsCat.txt", "r");
  numPelis = file_num_lines(fp);
  colum = file_num_columas(fp);
  peliCat = crearMatriz(numPelis, 5);
  peliCat = getData(5, fp, peliCat, numPelis);
  printf("Se creó la matriz de Features de peliculas\n");

  //Matriz de usuarios vs rating de pelicula
  fr = file_new("ratingsUsuarios.txt", "r");
  reng = file_num_lines(fr);
  colum = file_num_columas(fr);
  usRat = crearMatriz(reng, 3);
  usRat = getData(colum, fr, usRat, reng);
  printf("Se creó la matriz de usuarios y ratings de peliculas\n");

  //Matriz de usuario con afinidada categorias (Feature de usuarios)
  usuarioCat = crearMatriz(numUsuarios, 5);
  usuarioCat = llenarRandom(usuarioCat, numUsuarios, 5);
  printf("Se creó la matriz de usuarios y categoría con contenido aleatorio\n");

  //Ralizar epocs
  for(i = 0; i < 500; i++)
  {
    usuarioCat = realizarEpoc(&e, usuarioCat, peliCat, numUsuarios, usRat, reng);
    arrayError[i] = e;
    //printf("\nError en el Epoc %i :%f\n",i, e);
  }
  /*sfor(i = 0; i < numUsuarios; i++)
  {
    for(j = 0; j < 5; j++)
    {
      printf("%f, ", usuarioCat[i][j]);
    }
    printf("\n");
  }*/
  printf("\n\n\nEl algotitmo está entrenado.\n");

  while(op != 4)
  {
    printf("1 -- Realizar recomendación\n");
    printf("2 -- Ver usuarios similares\n");
    printf("3 -- Ver películas similares\n");
    printf("4 -- Salir del programa\n");
    scanf("%i", &op);
    if(op == 1)
    {
      realizarRecomendacion(idPeliculas, idUsuarios, usuarioCat, peliCat, usRat, numUsuarios, reng, numPelis);
    }
    if(op == 2)
    {
      usuariosIguales(idUsuarios, usuarioCat, numUsuarios);
    }
    if(op == 3)
    {
      peliculasIguales(idPeliculas, peliCat, numPelis);
    }
  }
  fa = file_new("error.csv", "w");
  writeCSV(fa, arrayError, 500);
  GNU_plot();

  fclose(fp);
  fclose(fr);
  fclose(fu);
  fclose(fa);
  free(peliCat);
  free(usRat);
  free(usuarioCat);
  free(idUsuarios);
  free(idPeliculas);
}
