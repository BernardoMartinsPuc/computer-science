import java.util.Scanner;
import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;

class Veiculo {
	
	private int id;
	private String marca;
	private String modelo;
	private int ano;
	private String categoria;
	private String[] combustivel;
	private int cilindros;
	private double cilindradas;
	private String transmissao;
	private String tracao;
	private double consumoCidade;
	private double consumoEstrada;
	private double co2;
	private boolean turbo;
	private Data dataRegistro;

	public Veiculo(){
	}
 
	public int getId(){
		return id;
	}

	public void setId(int id){
		this.id = id;
	}

	public String getMarca(){
		return marca;
	}

	public void setMarca(String marca){
		this.marca = marca;
	}

	public String getModelo(){
		return modelo;
	}

	public void setModelo(String modelo){
		this.modelo = modelo;
	}

	public int getAno(){
		return ano;
	}

	public void setAno(int ano){
		this.ano = ano;
	}

	public String getCategoria(){
		return categoria;
	}

	public void setCategoria(String categoria){
		this.categoria = categoria;
	}

	public String[] getCombustivel(){
		return combustivel;
	}

	public void setCombustivel(String[] combustivel){
		this.combustivel = combustivel;
	}

	public int getCilindros(){
		return cilindros;
	}

	public void setCilindros(int cilindros){
		this.cilindros = cilindros;
	}	
	
	public double getCilindradas(){
		return cilindradas;
	}

	public void setCilindradas(double cilindradas){
		this.cilindradas = cilindradas;
	}

	public String getTransmissao (){
		return transmissao;
	}

	public void setTransmissao (String transmissao){
		this.transmissao = transmissao;
	}

	public String getTracao(){
		return tracao;
	}

	public void setTracao (String tracao){
		this.tracao = tracao;
	}

	public double getConsumoCidade(){
		return consumoCidade;
	}

	public void setConsumoCidade (double consumoCidade){
		this.consumoCidade = consumoCidade;
	}

	public double getConsumoEstrada(){
		return consumoEstrada;
	}

	public void setConsumoEstrada(double consumoEstrada){
		this.consumoEstrada = consumoEstrada;
	}

	public double getCo2(){
		return co2;
	}

	public void setCo2(double co2){
		this.co2 = co2;
	}
	
	public boolean getTurbo (){
		return turbo;
	}

	public void setTurbo (boolean turbo){
		this.turbo = turbo;
	}

	public Data getData(){
		return dataRegistro; 
	}

	public void setData (Data dataRegistro){
		this.dataRegistro = dataRegistro;
	}

	public static  Veiculo parseVeiculo(String s){
		
		String dados[] = s.split(",");
		Data dataRegistro = Data.parseData(dados[14]);
		Veiculo carro = new Veiculo();

		carro.setId (Integer.parseInt (dados[0]));
	        carro.setMarca (dados[1]);
		carro.setModelo (dados[2]);
		carro.setAno (Integer.parseInt (dados[3]));
		carro.setCategoria (dados[4]);
		carro.setCombustivel(dados[5].split(";"));
		carro.setCilindros (Integer.parseInt (dados[6]));
		carro.setCilindradas (Double.parseDouble(dados[7]));
		carro.setTransmissao (dados[8]);
		carro.setTracao (dados[9]);
		carro.setConsumoCidade (Double.parseDouble(dados[10]));
		carro.setConsumoEstrada (Double.parseDouble(dados[11]));
		carro.setCo2 (Double.parseDouble (dados[12]));
		carro.setTurbo (Boolean.parseBoolean (dados[13]));
		carro.setData (dataRegistro);

		return carro;
	}

	public String format () {

		String strCombustivel = "[";

   		 for (int i = 0; i < combustivel.length; i++) {

   	     		 strCombustivel += combustivel[i];

       			 if (i < combustivel.length - 1) {

           		 strCombustivel += ",";
       			 }
   		 }

   		 strCombustivel += "]";
	
		String mensagem = String.format(Locale.US, "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %b ## %s]",
    getId(), getMarca(), getModelo(), getAno(), getCategoria(), strCombustivel, getCilindros(), getCilindradas(), 
    getTransmissao(), getTracao(), getConsumoCidade(), getConsumoEstrada(), getCo2(), getTurbo(), getData().format());
		
		return mensagem;
	}
}

class Data {

	private int ano;
	private int mes;
	private int dia;

	public Data(){
	}

	public Data (int ano, int mes, int dia){
		this.ano = ano;
		this.mes = mes;
		this.dia = dia; 
	}

	public int getAno(){
		return ano;
	}

	public void setAno(int ano){
		this.ano = ano;
	}

	public int getMes(){
                 return mes;
        }
        
       	public void setMes(int mes){
                this.mes = mes;
	}

	public int getDia(){
                 return dia;
         }
 
         public void setDia(int dia){
                 this.dia = dia;
         }
	
	public static Data parseData(String s){
		
		int dia, mes, ano;

		String[] divisao = s.split("-");

		ano = Integer.parseInt (divisao [0]);
		mes = Integer.parseInt (divisao [1]);
		dia = Integer.parseInt (divisao [2]);

		Data resultado = new Data(ano, mes, dia);
		return resultado;
	
	}

	public String format(){
		
		String mensagem = String.format ("%02d/%02d/%04d", dia, mes, ano);
		return mensagem; 
	}	
}
	
class LeitorCsv{	
	
	public static Veiculo[] ler(String caminhoArquivo){

	Veiculo conjunto[] = new Veiculo[500];

	try {
		File arquivo = new File(caminhoArquivo);
		Scanner scanner = new Scanner (arquivo);
		
		if (scanner.hasNextLine()){
			scanner.nextLine();
		}
			
		for (int i = 0; i < 500; i++){
			
			if(scanner.hasNextLine()){
		
				String string = scanner.nextLine();
				conjunto[i] = Veiculo.parseVeiculo(string);
			}
		}	
	
	}

	catch (FileNotFoundException e){
		System.out.println ("Erro ao abrir o arquivo" + caminhoArquivo);
	}

	return conjunto;
	}
}	

class Lista {

    private Veiculo[] listaVeiculos;
    private int n;

    public Lista() {
        this(100);
    }

    public Lista(int tamanho) {

        listaVeiculos = new Veiculo[tamanho];
        n = 0;
    }

    public void inserirInicio(Veiculo veiculo) throws Exception {

        if (n >= listaVeiculos.length) {

            throw new Exception("Lista cheia");
        }

	for (int i = n; i > 0; i--) {

            listaVeiculos[i] = listaVeiculos[i - 1];
        }

        listaVeiculos[0] = veiculo;
        n++;
    }

    public void inserirPos(Veiculo veiculo, int pos) throws Exception {

        if (n >= listaVeiculos.length) {

            throw new Exception("Lista cheia");
        }

        if (pos < 0 || pos > n) {

            throw new Exception("Posição inválida");
        }

 	for (int i = n; i > pos; i--) {
            listaVeiculos[i] = listaVeiculos[i - 1];
        }

        listaVeiculos[pos] = veiculo;
        n++;
    
    }

    public void inserirFim(Veiculo veiculo) throws Exception {

        if (n >= listaVeiculos.length){

	       	throw new Exception("Lista cheia");
	}

        listaVeiculos[n] = veiculo;
        n++;
    }

    public Veiculo removerInicio() throws Exception {
        if (n == 0) {

            throw new Exception("Lista vazia");
	}

        Veiculo resp = listaVeiculos [0];
        n--;

	for (int i = 0; i < n; i++) {

            listaVeiculos[i] = listaVeiculos [i + 1];
        }

        return resp;
    }

    public Veiculo removerPos(int pos) throws Exception {

        if (n == 0) {

            throw new Exception("Lista vazia");
        }
        if (pos < 0 || pos >= n) {

            throw new Exception("Posição inválida");
        }

        Veiculo resp = listaVeiculos[pos];
        n--;

        for (int i = pos; i < n; i++) {

            listaVeiculos[i] = listaVeiculos[i + 1];
        }

        return resp;
    }

    public Veiculo removerFim() throws Exception {
        
	if (n == 0) {

            throw new Exception("Lista vazia");
        }
	
	n--;
        Veiculo res = listaVeiculos[n];

	return res;
    }

    public void mostrar() {

        for (int i = 0; i < n; i++) {

            System.out.println(listaVeiculos[i].format());
        }
    }
}



public class Tp2Q9 {
	
	public static void main (String []args){
		
		Lista lista = new Lista(1000);
		Veiculo carros[] = new Veiculo[500];
		carros = LeitorCsv.ler("/tmp/veiculos.csv");	
		Scanner scan = new Scanner (System.in);
		Veiculo id_encontrado[] = new Veiculo [100];
		int qtdEncontrado = 0;
		int contador = 0;

		int vetor[] = new int[500];
		int num = Integer.parseInt (scan.nextLine());
		int i = 0;

		while ( num != -1 ){

			vetor [i] = num;
			i++;
			num = Integer.parseInt (scan.nextLine());
			contador++;
		}
	
		for (int j = 0; j < contador ; j++){
		
			for (int k = 0; k < 500; k++){
			
				if (carros[k].getId() == vetor[j]){
					
					id_encontrado[qtdEncontrado] = carros[k];
					qtdEncontrado++;
					try {
                        			lista.inserirFim(carros[k]);
                    			} catch (Exception e) {}	
				}
			}
		}

		int numComando;
		numComando = scan.nextInt();
		scan.nextLine();

		for (int l = 0; l < numComando; l++){

			String linha = scan.nextLine();

			String[] comando = linha.split(" ");
			
			try{ 

			if (comando[0].compareTo("I*") == 0){

				for (int idx = 0; idx < 500; idx++){
					if (carros[idx].getId() == Integer.parseInt (comando[2])){
						
						lista.inserirPos (carros[idx], Integer.parseInt(comando[1]));
					}
				}	
			}

			if (comando[0].compareTo("II") == 0){

                                 for (int idx = 0; idx < 500; idx++){
                                         if (carros[idx].getId() == Integer.parseInt (comando[1])){

                                                 lista.inserirInicio (carros[idx]);
                                         }
                                 }
                         }

			if (comando[0].compareTo("IF") == 0){

                                  for (int idx = 0; idx < 500; idx++){
                                          if (carros[idx].getId() == Integer.parseInt (comando[1])){
                                                 lista.inserirFim(carros[idx]);
                                          }
                                  }
                          }

			if (comando[0].compareTo("R*") == 0){

                              Veiculo removido = lista.removerPos (Integer.parseInt(comando[1]));
			      System.out.println ("(R)" + removido.getMarca() + " " + removido.getModelo());
                        }

			if (comando[0].compareTo("RI") == 0){
				
				Veiculo removido = lista.removerInicio();
				System.out.println ("(R)" + removido.getMarca() + " " + removido.getModelo());
			}

			if (comando[0].compareTo("RF") == 0){
				
				Veiculo removido = lista.removerFim();
				System.out.println ("(R)" + removido.getMarca()+ " " + removido.getModelo());
			}
			}catch (Exception e){
				System.out.println (e.getMessage());
			}
		}

		lista.mostrar();
	}
}
