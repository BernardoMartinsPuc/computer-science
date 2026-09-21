#include <stdio.h>
#include <string.h>

typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

typedef struct {
    int id;
    char marca[100];
    char modelo[100];
    int ano;
    char categoria[100];
    char combustivel[3][50];
    int cilindros;
    double cilindrada;
    char transmissao[50];
    char tracao[50];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    bool turbo;
    Data dataRegistro;
} Veiculo; 

Data parseData (char* s) {

    Data data;
    sscanf( s, "%d-%d-%d", &data.ano, &data.mes, &data.dia);
    return data;
}

void formatData (Data data, char* resultado){

     sprintf (resultado, "%02d/%02d/%04d", data.dia, data.mes, data.ano);
}

Veiculo* parseVeiculo (char* s){

	Veiculo *carro = (Veiculo*) malloc (sizeof(Veiculo));

	char* dados;

	dados = strtok (s, ","):
	sscanf (dados, "%d", &carro -> id);
	
	dados = strtok (NULL, ",");
    	sprintf (v -> marca, "%s", dados);

     	dados = strtok (NULL, ","); 
    	sscanf (v -> modelo, "%s", dados);

    	dados = strtok (NULL, ",");
   	sscanf (dados, "%d", &v -> ano);

     	dados = strtok (NULL, ",");
    	sprintf (v -> categoria, "%s", dados);
	
	dados = strtok (NULL, ",");
	char combTemp[100];
	ectricity") para a variável temporária

// 2. Faz o segundo fatiamento usando ';' como separador
char* subToken = strtok(combTemp, ";");

	while (subToken != NULL) {
    
   	sprintf(v->combustivel[v->numCombustiveis], "%s", subToken);
 
      	subToken = strtok(NULL, ";");
}

}
