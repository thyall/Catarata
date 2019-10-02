all:
	gcc imagem.c -c
	gcc filtros-teste.c -c
	gcc hough.c -c
	gcc main-teste.c imagem.o filtros-teste.o hough.o -lm
