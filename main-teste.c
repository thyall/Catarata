#include "imagem.h"

int main(int argc, char **argv)
{

	int i;
	Picture resultado;
	Picture auxiliar;
	Picture cinza;
	Picture gauss;
	Picture sobel;
	Picture hough;

	extern char *optarg;
	char arquivo[20];
	int limite, rmin, c, rtop;
	int proveuG = 0;
	int proveuRmin = 0;
	int proveuRtop = 0;
	int proveuS = 0;
	extern int opterr;
	extern int optopt;
	extern int optind;
	int exibirHelp = 0;

	opterr = 1;				//1 se quiser exibir mensagens de erro

	while((c = getopt(argc, argv, "s:g:r:t:")) != -1) {
		if(c == 's') {
			strcpy(arquivo, optarg);
			proveuS = 1;
		} else if(c == 'g') {
			limite = atoi(optarg);
			proveuG = 1;
		} else if(c == 'r') {
			rmin = atoi(optarg);
			proveuRmin = 1;
		} else if(c == 't') {
			rtop = atoi(optarg);
			proveuRtop = 1;
		} else if(c == '?') {
			if(optopt == 's')
				fprintf(stderr, "A opção -s exige um argumento.\n");
			if(optopt == 'g')
				fprintf(stderr, "A opção -g exige um argumento.\n");
			if(optopt == 'r')
				fprintf(stderr, "A opção -r exige um argumento.\n");
			if(optopt == 't')
				fprintf(stderr, "A opção -t exige um argumento.\n");
			return 1;
		}
	}
	if(!proveuS || !proveuG || !proveuRmin || !proveuRtop) {
		fprintf(stderr, "Opção -s, -g, -r ou -t não fornecida\n");
		fprintf(stderr, "Use ./a.out -s nome_do_arquivo.ppm -g limiar_da_binarizição -r raio_minimo -t raio_maximo\n");
		return 1;
	}
   
	resultado = ler_ppm(arquivo);

	//Aplicando o filtro de cinza
	cinza = cinzado_ppm(resultado, arquivo);
	escreve_ppm(cinza, "cinzado.ppm");

	//Aplicando o filtro gaussiano 3 vezes
	gauss = gaussian_ppm(cinza, "cinzado.ppm");
	escreve_ppm(gauss, "gauss.ppm");

	//Aplicando o filtro de Sobel
	sobel = sobel_ppm(gauss, "gauss.ppm", limite);
	escreve_ppm(sobel, "sobel.ppm");

	//Aplicando Hough
	hough = hough_ppm(sobel, arquivo, resultado, rmin, rtop);
	escreve_ppm(hough, "pupila.ppm");

	return 0;
}
