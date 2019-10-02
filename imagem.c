#include "imagem.h"

Picture ler_ppm(char *filename)
{
  //após estudos descobrimos que são reservados 3 bytes para o cabeçalho da ppm //
  char formato[3];
  int densidade;
  int i, j;
  FILE *aux;
  Picture *foto;

  aux = fopen(filename, "r");
  foto = malloc(sizeof(Picture));

  //Verificar o tipo da imagem
  fgets(formato, 3, aux);
  if( !(formato[0] == 'P' && formato[1] == '3') )
  {
  	fprintf(stderr, "ERRO -> Imagem fornecida nao possui formato P3. \n");
  	exit(1);
  }

  //Verificar a leitura dos parâmetros do cabeçalho
  fscanf(aux, "%d %d", &foto->largura, &foto->altura);

  //Verificar a intensidade
  fscanf(aux, "%d", &foto->densidade);
  
  //Alocar dinamicamente o tamanho da imagem
  foto->matriz = (Pixel **) malloc(sizeof(Pixel*)*foto->altura);
	for(i = 0; i < foto->altura; i++)
	{
		foto->matriz[i] = malloc(sizeof(Pixel)*foto->largura);
	}

  //Ler a Imagem
  for(i = 0; i < foto->altura; i++) {
    for(j = 0; j < foto->largura; j++) {
      fscanf(aux, "%i %i %i", &foto->matriz[i][j].r, &foto->matriz[i][j].g, &foto->matriz[i][j].b);
    }
  }

  fclose(aux);
  
  return *foto;  
}

void escreve_ppm(Picture foto, char *filename)
{
  FILE *pont;
  int i, j;
  pont = fopen(filename, "w");

  //inserindo o cabeçalho da imagem
  fprintf(pont, "P3\n");
  fprintf(pont, "%d %d\n", foto.largura, foto.altura);
  fprintf(pont, "%d\n", foto.densidade);

  //Inserindo os valores de cada RGB de cada pixel
  for(i = 0; i < foto.altura; i++)
  {
    for(j = 0; j < foto.largura; j++)
    { 
      fprintf(pont, "%i %i %i ", foto.matriz[i][j].r, foto.matriz[i][j].g, foto.matriz[i][j].b);
    }
    fprintf(pont, "\n");
  }

  fclose(pont);
}

Picture alocar(char *filename){
  Picture *gray;
  FILE *aux;
  int i, j, cinza;
  char formato[3];

  aux = fopen(filename, "r");
  gray = malloc(sizeof(Picture));

  //Adicionando os parâmetros do cabeçalho
  fgets(formato, 3, aux);
  fscanf(aux, "%d %d", &gray->largura, &gray->altura);

  //Adicionando a intensidade
  fscanf(aux, "%d", &gray->densidade);

  //Alocar dinamicamente o tamanho da imagem
  gray->matriz = (Pixel **) malloc(sizeof(Pixel*)*gray->altura);
  for(i = 0; i < gray->altura; i++)
  {
    gray->matriz[i] = malloc(sizeof(Pixel)*gray->largura);
  }

  return *gray;
}