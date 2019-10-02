#include "imagem.h"

Picture hough_ppm(Picture foto, char *filename, Picture resultado, int rmin, int rtop)
{
  int i, j, k, r, imax = 0, jmax = 0, rmax = 0, teta;	
  int ***array;
  int a, b;  
  int total = 0;
  int catarata = 0;
  int percentual;
  int imax2 = 0, jmax2 = 0, rmax2 = 0;
  int aux;

  //alocação dinâmica de uma matriz tridimensional
  array = (int ***)calloc(foto.altura, sizeof(int**));
  for (i = 0; i < foto.altura; i++) 
  {
    array[i] = (int **) calloc(foto.largura,sizeof(int *));
    for (j = 0; j < foto.largura; j++) 
    {
      array[i][j] = (int *)calloc(rtop,sizeof(int));
    }
  }


	//etapa de votacao 
  for(r = rmin ; r <= rtop ; r++)
  {
    printf("Analisando o raio %d...\nAguarde...\n", r);
    for (i = 0; i < foto.altura; i++)
    {
      for (j = 0; j < foto.largura; j++)
      {
        if(foto.matriz[i][j].r == 255)//vendo se esta na borda, que de acordo com a binarização, são os pixels com valor de 255
        {
          for (teta = 1; teta <= 360 ; teta += 2)//
          {
            a = i - r * cos(teta * M_PI / 180);//coordenada a do circulo
            b = j - r * sin(teta * M_PI / 180);//coordenada b do circulo
            if(a >= 0 && a < foto.altura && b >= 0 && b < foto.largura)
            {
              array[a][b][r] += 1;
            }
          }
        } 
      }
    }   
  }

  //Definir o centro da pupila
  int limite = 0;

  for (r = rmin; r <= rtop; r++)//para cada raio do dominio
  {
    for (i = rtop; i < foto.altura - rtop; i++)
    {
      for (j = rtop; j < foto.largura - rtop; j++)
      {
        if(array[i][j][r]  > limite){
          //gravando o segundo valor mais votado(pupila)
          aux = limite;
          imax2 = imax;
          jmax2 = jmax;
          rmax2 = rmax;
          //gravando o valor mais votado(iris)
          limite = array[i][j][r];
          imax = i;
          jmax = j;
          rmax = r;
        }
      }  
    }
  } 
   
   free(array);  

  printf("VALOR DA PUPILA\n");
  printf("Maior Voto: %d\n", aux);
  printf("Na coordenada: %d %d %d\n", imax2, jmax2, rmax2);

  printf("\n");
  printf("----------//----------\n");
  printf("\n");

  //Limitando a pupila
  Picture circulo;

  circulo = alocar(filename);
  for(i = 0; i < foto.altura; i++)
  {
    for(j = 0; j < foto.largura; j++)
    {
      if(pow(i-imax2,2) + pow(j-jmax2,2) <= pow(rmax2,2)){   
      circulo.matriz[i][j].r = resultado.matriz[i][j].r;
      circulo.matriz[i][j].g = resultado.matriz[i][j].g;
      circulo.matriz[i][j].b = resultado.matriz[i][j].b;
      } else {
  	  circulo.matriz[i][j].r = 0;
      circulo.matriz[i][j].g = 0;
      circulo.matriz[i][j].b = 0;
      }
    }
  }
	
	//contar os pixels
	for(i = 0; i < foto.altura; i++)
  {
    for(j = 0; j < foto.largura; j++)
    {
     	if(circulo.matriz[i][j].r != 0){
     		total++;
     	}
      if(circulo.matriz[i][j].b > 130 && circulo.matriz[i][j].b < 230){
        catarata++;
      }
    }
  }

  percentual = 100*catarata/total;

  printf("DIAGNÓSTICO\n");
  printf("Total de pixels: %d\n", total);
  printf("Total de pixels prejudicados: %d\n", catarata);
  printf("Percentual de comprometimento da pupila: %d\n", percentual);
  if(percentual > 60){
    printf("Possui catarata\n");
  } else {
    printf("Não possui catarata\n");
  }

 

  return circulo;
}




