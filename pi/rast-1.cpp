#include <iostream>
#include <fstream> // input e output de arquivos
#include <string>

struct {
	std::string tipo;
	int colunas; //width = largura
	int linhas;  //height = altura
	float valorMax; // imagens p2 8 bit
} ppmImage;


int main (int argc, char* argv[]){
	std::ifstream imagemPPM;
	imagemPPM.open(argv[1]); //pego o segundo argumento que é o nosso arquivo
	//tendo certeza que o arquivo foi aberto corretamente
	if (imagemPPM.is_open()){
		std::string tipoDaImagem; //primeira linha
		std::getline(imagemPPM, tipoDaImagem);

		std::string tamanhoDaImagem; //segunda linha
		std::getline(imagemPPM, tamanhoDaImagem);
		std::cout << tamanhoDaImagem;
	}
	imagemPPM.close();
	return 0;
}