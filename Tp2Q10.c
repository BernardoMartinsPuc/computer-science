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

typedef struct {

 	Veiculo filaVeiculos[6];
	int primeiro, ultimo;
}FilaCircular;

void construtorFila (FilaCircular *fila) {
	
	fila -> primeiro = 0;
	fila -> ultimo = 0;
	
}

Veiculo desenfileirar(FilaCircular* fila) {

    if (fila -> primeiro == fila -> ultimo) {
       exit(1);
    }

    Veiculo resp = fila -> filaVeiculos[fila -> primeiro];
    fila -> primeiro = (fila -> primeiro + 1) % 6;
    return resp;
}

void enfileirar(FilaCircular* fila, Veiculo veiculo) {
   
    if ((fila -> ultimo + 1) % 6 == fila -> primeiro) {

        Veiculo removido = desenfileirar(fila);
        printf("(R)%s %s\n", removido.marca, removido.modelo);
    }

    fila -> filaVeiculos [fila -> ultimo] = veiculo;
    fila -> ultimo = (fila -> ultimo + 1) % 6;
}

void mostrarFila(FilaCircular* fila) {

    int i = fila -> primeiro;
    char res[500];

    while (i != fila -> ultimo) {
        formatVeiculo (fila -> filaVeiculos[i], res);
        printf ("%s\n", res);
        i = (i + 1) % 6;
    }
}


int main() {
    
    int totalVeiculos = 0;
    Veiculo* veiculos = lerCsv("/tmp/veiculos.csv", &totalVeiculos); 

    char entrada[100];
    FilaCircular fila;
    construtorFila(&fila);

    while (scanf("%s", entrada) != EOF && atoi(entrada) != -1) {

        int id = atoi(entrada);

        for (int i = 0; i < totalVeiculos; i++) {

            if (veiculos[i].id == id) {
            
                enfileirar(&fila, veiculos[i]);
            }
        }
    }

    int numComando;
    scanf("%d", &numComando);

    for (int i = 0; i < numComando; i++){

        char comando[20];
        scanf("%s", comando);

        if (strcmp(comando, "I") == 0){

            int idBusca;
            scanf("%d", &idBusca);

            for (int idx = 0; idx < totalVeiculos; idx++){

                if (veiculos[idx].id == idBusca){

                    enfileirar(&fila, veiculos[idx]);
                }

            }
        }

        if (strcmp(comando, "R") == 0){

                Veiculo removido = desenfileirar(&fila);
                printf("(R)%s %s\n", removido.marca, removido.modelo);
        }

    }

    mostrarFila(&fila);

    free(veiculos);
}
