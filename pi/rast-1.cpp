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
		int matrixPixel[y][x]; 
		// no arquivo ppm é coluna - linha, pra colcoar na matrix invertemos
		for (int i = 0; i<y; i++){
			for (int j = 0; j<x; j++){
				std::string strTemp;
				imagemPPM >> strTemp;
				matrixPixel[i][j] = std::stoi(strTemp);
			}
		}

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