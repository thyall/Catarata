#ifndef IMAGEM_H
#define IMAGEM_H
//blibiotecas necessarias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

//tipos de variaveis//

typedef struct Pixel
{
	int r, g, b;
} Pixel;

typedef struct Imagens
{
	int largura, altura;
	int densidade;
	Pixel **matriz;
} Picture;


//Funções para imagens PPM(P3)//

//Alocação dinâmica em 2D
Picture alocar(char *filename);

//gera imagem ppm
void escreve_ppm(Picture foto, char *filename);

//ler imagem ppm
Picture ler_ppm(char *filename);

//transforma para tons de cinza
Picture cinzado_ppm(Picture foto, char *filename);

//filtro gaussiano
Picture gaussian_ppm(Picture foto, char *filename);

//filtro sobel
Picture sobel_ppm(Picture foto, char *filename, int limite);

//hough circles
Picture hough_ppm(Picture foto, char *filename, Picture resultado, int rmin, int rtop);

#endif


