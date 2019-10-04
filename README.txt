# Pre-requisitos

	gcc
	gnu-make

# Como construir

	make all

# Como testar 

	make testall

# Para verificar se existem leaks

	make valg


# Como usar

	O comando `make all` cria dois binarios, um chamado `maximize` e outro
	chamado `minimize`.

	Ambos programas aceitam dois parametros (nesta ordem)

	filename:	O caminho para um arquivo que contem uma matriz qualquer
	seed:		A seed aleatorio a ser usada

	
	Macetes:
		Voce pode usar 'random' como `filename`, se fizer isso ele gera
		uma matriz 10x10 alatoria.

		Voce tambem pode usar `seed` como -1, se fizer isso ele usa uma
		seed aleatoria.


Qualquer duvidas falar com <morgado.igor@gmail.com>

	
