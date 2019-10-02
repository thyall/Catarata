#include "imagem.h"

Picture cinzado_ppm(Picture foto, char *filename)
{
  int i, j, cinza;
  Picture gray;
  char formato[3];

  //alocação dinâmica da matriz que irá receber os valores dos pixels em cinza  
  gray = alocar(filename);

  for(i = 0; i < foto.altura; i++)
  {
     for(j = 0; j < foto.largura; j++)
    {   
      //convertendo os valores dos pixels para tom de cinza
      cinza = 0.3*foto.matriz[i][j].r + 0.59*foto.matriz[i][j].g + 0.11*foto.matriz[i][j].b;
      gray.matriz[i][j].r = cinza;
      gray.matriz[i][j].g = cinza;
      gray.matriz[i][j].b = cinza;
    }
  }

  return gray;
}

Picture gaussian_ppm(Picture foto, char *filename){
  //matriz de convolução
  int gauss[5][5] = {{2, 4, 5, 4, 2}, {4, 9, 12, 9, 4}, {5, 12, 15, 12, 5}, {4, 9, 12 , 9, 4}, {2, 4, 5, 4, 2}};
  int norm = 159;//valor para normalizar
  int i, j, k, l;
  float result;
  Picture blur;

  //alocação dinâmica da matriz que irá receber os novos valores
  blur = alocar(filename);

  for(i = 0; i < foto.altura; i++)
  {
    for(j = 0; j < foto.largura; j++){
      result = 0;
      for(k = 0; k < 5; k++){
        for(l = 0; l < 5; l++){
          if(((i-2+k) >= 0 && (j-2+l) >= 0) && (i+2 < foto.altura && j+2 <foto.largura)){
            result += (foto.matriz[i-2+k][j-2+l].r*gauss[k][l])/norm;
          }
        }
      }
      blur.matriz[i][j].r = result;
      blur.matriz[i][j].g = result;
      blur.matriz[i][j].b = result;
    }
  }

  return blur;
}

Picture sobel_ppm(Picture foto, char *filename, int limite)
{
  //matriz de convolução
  int gx[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
  int gy[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
  int i, j, k, l;
  int px, py, g;
  int help = 0;
  Picture sobel;

  //alocação dinâmica da matriz que irá receber os novos valores
  sobel = alocar(filename);

  for(i = 0; i < foto.altura; i++)
  {
    for(j = 0; j < foto.largura; j++)
    { 
      px = 0;
      py = 0;
      for(k = 0; k < 3; k++)
      {
        for(l = 0; l < 3; l++)
        {
          if((i == 0 || j == 0) || (i == foto.altura - 1 || j == foto.largura - 1))
          {
            px += 0;
            py += 0;
          } else {
            px += (foto.matriz[i-1+k][j-1+l].r)*(gx[k][l]);
            py += (foto.matriz[i-1+k][j-1+l].r)*(gy[k][l]);
          }
        }
      }
      g = sqrt(px*px + py*py);
      if(g > limite)
      {
        sobel.matriz[i][j].r = 255;
        sobel.matriz[i][j].g = 255;
        sobel.matriz[i][j].b = 255;
      } else {
        sobel.matriz[i][j].r = 0;
        sobel.matriz[i][j].g = 0;
        sobel.matriz[i][j].b = 0;
      }
    }
  }

  return sobel;
}
