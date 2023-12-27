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

int* getTamanhoImagem (std::string str, int*vetor){
	std::string stringTemp;
	std::stringstream ss(str);


	getline(ss, stringTemp,' ');
	vetor[0] = std::stoi(stringTemp);
	getline(ss, stringTemp,' ');
	vetor[1] = std::stoi(stringTemp);

	return vetor;
}


/* PRECISO CRIAR UMA FORMA DE PEGAR OS PIXELS DA IMAGEM LIDA 
E ARMAZENAR NA NOSSA MATRIZ CRIADA 
função acima pode ser uma forma de como fazer...
*/


int main (int argc, char* argv[]){
	std::ifstream imagemPPM;

	imagemPPM.open(argv[1]); //pego o segundo argumento que é o nosso arquivo
	
	//tendo certeza que o arquivo foi aberto corretamente
	if (imagemPPM.is_open()){

		std::string tipoDaImagem; //primeira linha
		std::getline(imagemPPM, tipoDaImagem);

		std::string tamanhoDaImagem; //segunda linha
		std::getline(imagemPPM, tamanhoDaImagem); // peguei a dupla width e height (precisa ser separado)
		
		// nesse vetor é armazenado o numero de colunas e linhas da nossa matriz(imagem)
		int vetorTamanho[2];
		getTamanhoImagem(tamanhoDaImagem, vetorTamanho);

		std::string valorMaxCor;
		std::getline(imagemPPM,valorMaxCor);
		int valorCor = std::stoi(valorMaxCor);

		//criada a matriz que vai armazenar os pixels da nossa imagem
		int matrizTeste[vetorTamanho[0]][vetorTamanho[1]];
	}

	imagemPPM.close();
	return 0;
}