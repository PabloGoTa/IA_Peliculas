
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE * file_new(char *name, char *mode);
extern void file_num_write(FILE * file, size_t columns, long double buff[] [columns], size_t rows);
extern void writeCSV (FILE * fp, double data[], int numLines);
extern void writeResults (FILE * fp, double prom, double mediana, double moda, double desv, double dist, double rango1, double rango2);
extern void GNU_plot(void);
extern int file_num_columas(FILE *file);
extern double **crearMatriz(int reng, int colum);
extern double **getData(int colums, FILE *fp, double *data[], int reng);
extern double **llenarRandom(double *matriz[], int reng, int colums);
extern double **realizarEpoc(double *e, double *usuarioCat[], double *cates[], int numUsuarios, double *userRating[], int numRatings);
extern char **getDataUsu(int colums, FILE *fp, char *data[], int reng);
extern char **crearMatrizUsu(int colum, int reng);
extern void realizarRecomendacion(char **idPeliculas, char **idUsuarios, double **usuarioCat, double **peliCat, double **usRat, int numUsuarios, int numRat, int numPelis);
extern void peliculasIguales(char **idPeliculas, double **peliCat, int numPelis);
extern void usuariosIguales(char **idUsuarios, double **usuarioCat, int numUsuarios);

int valueinarray(int val, int *arr, int tam);


FILE * file_new(char *name, char *mode)
{
  FILE *fp;
  fp = fopen(name, mode);
  return fp;
}

void file_num_write(FILE * file, size_t columns, long double buff[] [columns], size_t rows)
{
  int i, j;
  for(i = 0; i <= rows; i++)
  {
    for(j = 0; j <= columns; j++)
    {
      fprintf(file, "%Lf \t", buff[i][j]);
    }
    fprintf(file,"\n");
  }
  return;
}

int file_num_lines(FILE * file)
{
  int i = 0, numLines, num;
  char string[200];
  fseek(file, 0, SEEK_SET);
  while(fgets(string, 200, file))
  {
    i++;
  }
  return i;
}

int file_num_columas(FILE *file)
{
  int i = 0;
  char c[1];
  fseek(file, 0, SEEK_SET);

  do{
    c[0] = fgetc(file);
    if(c[0] == ',')
    {
      i++;
    }
  }while(c[0] != '\n');
  return i;
}


void writeCSV (FILE * file, double data[], int numLines)
{
  int i;
  for(i = 0; i < numLines; i++)
  {
    fprintf(file, "%f\n", data[i]);
  }

  return;
}

void writeResults (FILE * file, double prom, double mediana, double moda, double desv, double dist, double rango1, double rango2)
{
  fprintf(file, "Promedio,%f\n", prom);
  fprintf(file, "Mediana,%f\n", mediana);
  fprintf(file, "Moda,%f\n", moda);
  fprintf(file, "DesviaciónEstandar,%f\n", desv);
  fprintf(file, "DistanciaIntercuartil,%f\n", dist);
  fprintf(file, "Rango,%f - %f\n", rango1, rango2);
}

void GNU_plot(void)
{
  FILE *pipe;
  pipe = popen("gnuplot -persist","w");

  fprintf(pipe, "plot 'error.csv' with lines\n");
  fflush(pipe);
  fclose(pipe);
}

double **crearMatriz(int reng, int colum)
{
  double **arr=(double **)malloc(sizeof(double *)*reng);
  int i,j;

  for(i = 0; i < reng; i++)
  {
    arr[i]=(double *)malloc(sizeof(double)*colum);
    //for(j = 0; j<5;j++)
    //{
    //  arr[i][j]=0;
    //}
  }
  return arr;
}

double **getData(int colums, FILE *fp, double *data[], int reng)
{
  fseek(fp, 0, SEEK_SET);
  char string[200];
  const char s[2] = ",";
  char *token, *ptr;
  int i = 0, j = 0;
  double c;


  while(fgets(string, 200, fp))
  {
      token = strtok(string, s);
      for(i = 0; i < colums; i++)
      {
        c = strtod(token, &ptr);
        data[j][i] = c;
        token = strtok(NULL, s);
      }
      j++;
    }

  return data;
}

double **llenarRandom(double *matriz[], int reng, int colums)
{
  int ran, i, j;

  for(i = 0; i < reng; i++)
  {
    for(j = 0; j < 5; j++)
    {
      matriz[i][j] = ((double)(rand() % 1000 + 1))/1000;
    }
  }
  for(i = 0; i < reng; i++)
  {
    matriz[i][0] = i +1;
  }
  return matriz;
}

double **realizarEpoc(double *e, double *usuarioCat[], double *cates[], int numUsuarios, double *userRating[], int numRatings)
{
  int i ,j, k, idUsu, idPeli;
  double pp = 0, error = 0, eTotal = 0, n = 0.05;

  for(i = 0; i < numRatings; i++)
  {
    pp = 0;
    idUsu = userRating[i][0];
    idPeli = userRating[i][1];
    for(j = 1; j < 5; j++)
    {
      pp = pp + (usuarioCat[idUsu - 1][j] * cates[idPeli -1][j]);
    }
            //numero del 1 al 100
    error = (userRating[i][2]/100) - (pp/10);

    for(k = 1; k < 5; k++)
    {
      usuarioCat[idUsu -1][k] = usuarioCat[idUsu -1][k] + (n * error * cates[idPeli -1][k]);
    }

    eTotal += error;
  }
  *e = eTotal;
  return usuarioCat;
}

char **crearMatrizUsu(int colum, int reng)
{
  char **arr=(char **)malloc(sizeof(char *)*reng);
  int i,j;

  for(i = 0; i < reng; i++)
  {
    arr[i]=(char *)malloc(sizeof(char)*colum);
  }
  return arr;
}

char **getDataUsu(int colums, FILE *fp, char *data[], int reng)
{
  fseek(fp, 0, SEEK_SET);
  int i = 0;
  while(!feof(fp))
  {
    fscanf(fp, "%s", data[i]);
    i++;
  }

  return data;
}

void realizarRecomendacion(char **idPeliculas, char **idUsuarios, double **usuarioCat, double **peliCat, double **usRat, int numUsuarios, int numRat, int numPelis)
{
  int i, j = 0, k, l, m;
  double id, pp;
  int vistas[10];
  int idRec[10];
  int flag = 3;

  printf("\n¿A qué usuario quieres realizar una recomendación?:\n");
  for(i = 0; i < numUsuarios; i++)
  {
    printf("%i -- %s\n", i+1, idUsuarios[i]);
  }
  printf("\n");
  scanf("%lf", &id);

  for(i = 0; i < numRat; i++)
  {
    if(usRat[i][0] == id)
    {
      vistas[j] = usRat[i][1];
      j++;
    }
  }
  //hasta aqui jala bien

  printf("\nPelículas recomendadas:\n");

  for(i = 0; i < numPelis; i++)
  {
    flag = 0;
    pp = 0;
    for(m = 0; m < j; m++)
    {
      if(vistas[m] == i + 1)
      {
        flag = 1;
      }
    }
    if(flag == 1)
    {
      continue;
    }
    for(k = 1; k < 5; k++)
    {
      pp = pp + (usuarioCat[(int)id - 1][k] * peliCat[i][k]);
    }
    //printf("pp: %f\n", pp);
    if(pp > 7.5)
    {
      printf("- %s\n", idPeliculas[i]);
    }
  }
  return;
}

void peliculasIguales(char **idPeliculas, double **peliCat, int numPelis)
{
  int i, id, j;
  double pp = 0;
  printf("\nVer películas similares a:\n");
  for(i = 0; i < numPelis; i++)
  {
    printf("%i -- %s\n", i+1, idPeliculas[i]);
  }
  scanf("%i", &id);
  for(i = 0; i < numPelis; i++)
  {
    pp = 0;
    if(id == i +1)
    {
      continue;
    }
    for(j = 1; j < 5; j++)
    {
      pp = pp + (peliCat[id - 1][j] * peliCat[i][j]);
    }
    if(pp > 1.5)
    {
      printf("- %s\n", idPeliculas[i]);
    }
  }
  printf("\n");
  return;
}


void usuariosIguales(char **idUsuarios, double **usuarioCat, int numUsuarios)
{
  int i, id, j;
  double pp = 0;
  printf("\nVer usuarios similares a:\n");
  for(i = 0; i < numUsuarios; i++)
  {
    printf("%i -- %s\n", i+1, idUsuarios[i]);
  }

  scanf("%i", &id);
  for(i = 0; i < numUsuarios; i++)
  {
    pp = 0;
    if(id == i +1)
    {
      continue;
    }
    for(j = 1; j < 5; j++)
    {
      pp = pp + (usuarioCat[id - 1][j] * usuarioCat[i][j]);
    }
    if(pp > 40)
    {
      printf("%s\n", idUsuarios[i]);
    }
  }
  return;
}
