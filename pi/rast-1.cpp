#include <iostream>
#include <fstream> // input e output de arquivos
#include <string>
#include <vector>
#include <sstream>
/*
struct {
	std::string tipo;
	int colunas; //width = largura
	int linhas;  //height = altura
	float valorMax; // imagens p2 8 bit
	int *matrizImagem;
} ppmImage;

*/


void negativo (int** matrix, int linhas, int colunas){
	for(int i=0; i<linhas; i++){
		for (int j = 0; j<colunas; j++){
			matrix[i][j] = ((matrix[i][j])-255)*(-1);			
		}
	}
}

void limiar (int** matrix, int linhas, int colunas, int limite){
	for (int i = 0; i<linhas; i++){
		for (int j = 0; j<colunas; j++){
			if ((matrix[i][j]) < limite){
				matrix[i][j] = 0;
			}
			else {
				matrix[i][j] = 255;
			}
		}
	}
}

int* gerarHistograma(int** matrix, int linhas, int colunas){
	int *arrayHistograma = new int [255];
	for (int i = 0; i<256; i++){
		arrayHistograma[i] = 0;
	}
	for(int i= 0; i<linhas; i++){
		for(int j=0; j<colunas; j++){
			arrayHistograma[matrix[i][j]]++;
		}
	}
	return arrayHistograma;
}


int main (int argc, char* argv[]){
	std::ifstream imagemPPM;

	int limite_limiar = std::stoi(argv[2]);
	imagemPPM.open(argv[1]); //pego o segundo argumento que é o nosso arquivo
	
	//tendo certeza que o arquivo foi aberto corretamente
	if (imagemPPM.is_open()){
		//Armazeno o tipo da imagem
		std::string tipoImagem;
		imagemPPM >> tipoImagem;
		//Armazeno o tamanho da imagem
		std::string colunas, linhas;
		imagemPPM >> colunas;
		imagemPPM >> linhas;
		//Armazeno o valor maximo de tom
		std::string valorMaximo;
		imagemPPM >> valorMaximo;
		//Transformo esses valores em inteiros, para criar a matriz dos pixels
		int x, y;
		x = std::stoi(colunas);
		y = std::stoi(linhas);


		// explicação no whatsapp de o porquê a matrix ser construída assim
		int **matrixPixel= new int*[y];
		for(int i = 0; i <y; i++){
			matrixPixel[i]= new int[x];
		} 



		// no arquivo ppm é coluna - linha, pra colocoar na matrix invertemos
		for (int i = 0; i<y; i++){
			for (int j = 0; j<x; j++){
				std::string strTemp;
				imagemPPM >> strTemp;
				matrixPixel[i][j] = std::stoi(strTemp);
			}
		}

		//limiar(matrixPixel,y,x,limite_limiar);
		

		//crio o novo arquivo
		std::ofstream novaImagem;
		novaImagem.open("novaImagem.ppm");

		//crio as variáveis pra essa imagem
		std::string tipoNI, colunasNI, linhasNI, valorMaximoNI;
		
		tipoNI.assign(tipoImagem);
		colunasNI.assign(colunas);
		linhasNI.assign(linhas);
		valorMaximoNI.assign(valorMaximo);


		//escrevo no novo arquivo

		novaImagem << tipoNI << std::endl;
		novaImagem << colunasNI << " " << linhasNI << std::endl;
		novaImagem << valorMaximoNI << std::endl;

		// escrevo os pixels
		for (int i = 0; i<y; i++){
			for (int j = 0; j<x; j++){
				std::string pixelTemp;
				pixelTemp = std::to_string(matrixPixel[i][j]);
				novaImagem << pixelTemp << std::endl;
			}
		}

		int* histograma = gerarHistograma(matrixPixel, y, x);
		//crio arquivo pro histograma
		std::ofstream novaImagemHistograma;
		novaImagemHistograma.open("histograma.txt");

		for(int i = 0; i<256; i++){
			std::string temp, posicao;
			temp = std::to_string(histograma[i]);
			posicao = std::to_string(i);
			novaImagemHistograma << posicao << ':' << temp << std::endl;
		}



	imagemPPM.close();
	return 0;
	}
}