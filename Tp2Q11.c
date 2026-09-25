#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int ano;
    int mes;
    int dia;
} Data;

typedef struct{
    int id;
    char marca[100];
    char modelo[100];
    int ano;
    char categoria[100];
    char combustivel[3][50];
    int numCombustivel;
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

Data parseData(char *s){

    Data data;
    sscanf(s, "%d-%d-%d", &data.ano, &data.mes, &data.dia);
    return data;
}

void formatData(Data data, char *resultado){

    sprintf(resultado, "%02d/%02d/%04d", data.dia, data.mes, data.ano);
}

Veiculo *parseVeiculo(char *s){

    Veiculo *carro = (Veiculo *)malloc(sizeof(Veiculo));
    if (carro == NULL) return NULL;

    char *dados;

    dados = strtok(s, ",");
    sscanf(dados, "%d", &carro -> id);

    dados = strtok(NULL, ",");
    sprintf(carro -> marca, "%s", dados);

    dados = strtok(NULL, ",");
    sprintf(carro -> modelo, "%s", dados);

    dados = strtok(NULL, ",");
    sscanf(dados, "%d", &carro -> ano);

    dados = strtok(NULL, ",");
    sprintf(carro -> categoria, "%s", dados);

    dados = strtok(NULL, ",");
    char combTemp[100];
    sprintf(combTemp, "%s", dados);

    dados = strtok(NULL, ",");
    sscanf(dados, "%d", &carro -> cilindros);

    dados = strtok(NULL, ",");
    sscanf(dados, "%lf", &carro -> cilindrada);

    dados = strtok(NULL, ",");
    sprintf(carro -> transmissao, "%s", dados);

    dados = strtok(NULL, ",");
    sprintf(carro -> tracao, "%s", dados);

    dados = strtok(NULL, ",");
    sscanf(dados, "%lf", &carro -> consumoCidade);

    dados = strtok(NULL, ",");
    sscanf(dados, "%lf", &carro -> consumoEstrada);

    dados = strtok(NULL, ",");
    sscanf(dados, "%lf", &carro -> co2);

    dados = strtok(NULL, ",");
    if (strcmp(dados, "true") == 0){
        carro -> turbo = true;
    }
    else{
        carro -> turbo = false;
    }

    dados = strtok(NULL, ",");
    dados[10] = '\0';

    carro -> dataRegistro = parseData(dados);

    char *partes = strtok(combTemp, ";");
    carro -> numCombustivel = 0;

    while (partes != NULL){
          sprintf(carro -> combustivel[carro -> numCombustivel], "%s", partes);
          carro -> numCombustivel++;
          partes = strtok(NULL, ";");
    }

    return carro; 
}

void formatVeiculo(Veiculo* carro, char* resultado) {

    char data[20];
    formatData(carro -> dataRegistro, data);

    char combustivel[200];
    int pos = 0;
    
    sprintf(combustivel + pos, "[");
    pos ++;

    for (int i = 0; i < carro -> numCombustivel; i++) {
        if (i > 0) {
            pos += sprintf(combustivel + pos, ",%s", carro -> combustivel[i]);
        } else {
            pos += sprintf(combustivel + pos, "%s", carro -> combustivel[i]);
        }
    }
    pos += sprintf(combustivel + pos, "]");

    char turbo[10];
    if (carro -> turbo) {
        sprintf(turbo, "true");
        } else {
        sprintf(turbo, "false");
        }

    sprintf(resultado, "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1lf ## %s ## %s ## %.2lf ## %.2lf ## %.1lf ## %s ## %s]", carro -> id, carro -> marca,carro -> modelo, carro -> ano, carro -> categoria, combustivel, carro -> cilindros, carro -> cilindrada, carro -> transmissao, carro -> tracao, carro -> consumoCidade, carro -> consumoEstrada, carro -> co2, turbo, data);
}

Veiculo* lerCsv(char* caminhoArquivo, int* n) {

    FILE* arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        return NULL;
    }

    Veiculo* conjunto = (Veiculo*) malloc (500 * sizeof (Veiculo)) ;

    char linha[1024];

    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);
        free(conjunto);
        return NULL; 
    }

    *n = 0;
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Veiculo* carro = parseVeiculo(linha);
        if (carro != NULL) {
            conjunto[*n] = *carro;
            free(carro);
           (*n)++;
        }
    }

    fclose(arquivo);
    return conjunto;
}

typedef struct Celula{
    
    Veiculo veiculo;
    struct Celula* prox;
}Celula; 

typedef struct {

    Celula* primeiro;
    Celula* ultimo;

} ListaEncadeada;

Celula* novaCelula(Veiculo carro){

    Celula* nova = (Celula*) malloc (sizeof(Celula));

    nova -> veiculo = carro;
    nova -> prox = NULL;
    return nova;
}

void construtorEncadeada(ListaEncadeada* lista){

    Veiculo cabeca;
    lista -> primeiro = novaCelula(cabeca);
    lista -> ultimo = lista -> primeiro;
}

int tamanho(ListaEncadeada* lista){

    if (lista->primeiro == NULL) {
        return 0;
    }

    int tamanho = 0;
    Celula* atual = lista -> primeiro -> prox; 

    while (atual != NULL) {
        tamanho++;
        atual = atual->prox;
    }

    return tamanho;
}

void inserirInicio (ListaEncadeada* lista, Veiculo veiculo){

    Celula* tmp = novaCelula(veiculo);
    tmp -> prox = lista -> primeiro -> prox;
    lista -> primeiro -> prox = tmp;

    if (lista -> primeiro == lista -> ultimo){

        lista -> ultimo = tmp;

    }
    tmp = NULL;
}

void inserirFim (ListaEncadeada* lista, Veiculo veiculo){

    lista -> ultimo -> prox = novaCelula (veiculo);
    lista -> ultimo = lista -> ultimo -> prox;
}

void inserirPos (ListaEncadeada* lista, Veiculo veiculo, int pos){

    int tam = tamanho(lista);

    if (pos < 0 || pos > tam){
        exit(1);

    } else if (pos == 0){
        inserirInicio (lista, veiculo);

    } else if(pos == tam){
        inserirFim(lista, veiculo);

    }else {

        Celula* i = lista -> primeiro;
        for (int j = 0; j < pos; j++, i = i -> prox);

            Celula* tmp = novaCelula(veiculo);

            tmp -> prox = i -> prox;
            i -> prox = tmp;
    }

}

Veiculo removerInicio(ListaEncadeada* lista){

	if (lista -> primeiro == lista -> ultimo){
		exit(1);
	}

	Celula* tmp = lista -> primeiro -> prox;
	Veiculo resp = tmp -> veiculo;
	lista -> primeiro -> prox = tmp -> prox;

	if(tmp == lista -> ultimo){
	
		lista -> ultimo = lista -> primeiro;
	}

	free(tmp);
	return resp;
}

Veiculo removerFim (ListaEncadeada* lista){

	if (lista -> primeiro == lista -> ultimo){
		exit(1);
	}

	Celula* i;

	for (i = lista -> primeiro; i -> prox != lista -> ultimo; i = i -> prox);
		
	Veiculo resp = lista -> ultimo -> veiculo;
	lista -> ultimo = i;
	free(lista -> ultimo -> prox);

	lista -> ultimo = i;
	lista -> ultimo -> prox = NULL;
	return resp;
}

Veiculo removerPos (ListaEncadeada* lista, int pos){
	
	int tam = tamanho(lista);

	if (lista -> primeiro == lista -> ultimo || pos < 0 || pos >= tam) {
        	exit(1);

    	} else if (pos == 0) {

        	return removerInicio(lista);

    	} else if (pos == tam - 1) {

        	return removerFim(lista);

    	} else {
		
		Celula* i = lista -> primeiro;
		for (int j = 0; j < pos; j++, i = i -> prox);

		Celula* tmp = i -> prox;
		Veiculo resp = tmp -> veiculo;
		i -> prox = tmp -> prox;

		free(tmp);
		return resp;	
	}	
}

void mostrarLista (ListaEncadeada* lista){

	char res[500];
	for (Celula* i = lista -> primeiro -> prox; i != NULL; i = i -> prox){
		
		formatVeiculo(&i -> veiculo, res);
		printf ("%s\n", res);
	}
}

int main() {
    
    int totalVeiculos = 0;
    Veiculo* veiculos = lerCsv("/tmp/veiculos.csv", &totalVeiculos); 

    char entrada[100];
    char res[2048];
    ListaEncadeada lista;
    construtorEncadeada(&lista);


    while (scanf("%s", entrada) != EOF && atoi(entrada) != -1) {
        int id = atoi(entrada);

        for (int i = 0; i < totalVeiculos; i++) {

            if (veiculos[i].id == id) {

                inserirFim(&lista, veiculos[i]);
            }
        }
    }
	
    int numComando;
    scanf("%d", &numComando);

    for (int i = 0; i < numComando; i++){

        char comando[20];
        scanf("%s", comando);

	if (strcmp (comando, "II") == 0) {

            int idBusca;
            scanf("%d", &idBusca);

            for (int k = 0; k < totalVeiculos; k++) {

                if (veiculos[k].id == idBusca) {

                    inserirInicio(&lista, veiculos[k]);
                }
            }

        } else if (strcmp (comando, "IF") == 0) {
            int idBusca;
            scanf("%d", &idBusca);
            for (int k = 0; k < totalVeiculos; k++) {

                if (veiculos[k].id == idBusca) {

                    inserirFim(&lista, veiculos[k]);
                }
            }

        } else if (strcmp(comando, "I*") == 0) {

            int pos, idBusca;
            scanf("%d %d", &pos, &idBusca);

            for (int k = 0; k < totalVeiculos; k++) {

                if (veiculos[k].id == idBusca) {

                    inserirPos(&lista, veiculos[k], pos);
                }
            }

	} else if (strcmp(comando, "RI") == 0) {

            Veiculo removido = removerInicio(&lista);
            printf("(R)%s %s\n", removido.marca, removido.modelo);

        } else if (strcmp(comando, "RF") == 0) {

            Veiculo removido = removerFim(&lista);
            printf("(R)%s %s\n", removido.marca, removido.modelo);

        } else if (strcmp(comando, "R*") == 0) {

            int pos;
            scanf("%d", &pos);

            Veiculo removido = removerPos(&lista, pos);
            printf("(R)%s %s\n", removido.marca, removido.modelo);
        }
    }

    mostrarLista(&lista);
    free(veiculos);
}
