#include <iostream>
#include <fstream> // input e output de arquivos
#include <string>
#include <vector>
#include <sstream>

struct {
	std::string tipo;
	int colunas; //width = largura
	int linhas;  //height = altura
	float valorMax; // imagens p2 8 bit
	int *matrizImagem;
} ppmImage;


void negativo (int** matrix, int linhas, int colunas){
	for(int i=0; i<linhas; i++){
		for (int j = 0; j<colunas; j++){
			matrix[i][j] = ((matrix[i][j])-255)*(-1);			
		}
	}
}

void maisContraste (int** matrix, int linhas, int colunas){
	for (int i = 0; i<linhas; i++){
		for (int j = 0; j<colunas; j++){
			if ((matrix[i][j]) < 126){
				matrix[i][j] = matrix[i][j]/1.4; 
			}
			else if (((matrix[i][j]) >= 127) && ((matrix[i][j]) <= 196)){
				matrix[i][j] = matrix[i][j]*1.15;
			}
		}
	}
}


int main (int argc, char* argv[]){
	std::ifstream imagemPPM;

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



		// no arquivo ppm é coluna - linha, pra colcoar na matrix invertemos
		for (int i = 0; i<y; i++){
			for (int j = 0; j<x; j++){
				std::string strTemp;
				imagemPPM >> strTemp;
				matrixPixel[i][j] = std::stoi(strTemp);
			}
		}

		maisContraste(matrixPixel,y,x);

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



	imagemPPM.close();
	return 0;
	}
}