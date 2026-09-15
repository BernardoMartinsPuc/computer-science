import Java.util.Scanner;

class Veiculo {
	
	private int id;
	private String marca;
	private String modelo;
	private int ano;
	private String categoria;
	private String combustivel;
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

	public String getCombustivel(){

		String string[] = combustivel.split (";");
		if (string.length == 3){
			String mensagem = String.format ("[%s,%s,%s]", string[0], string [1], string [2]);
		}
		if (string.length == 2){
			String mensagem = String.format ("[%s,%s]", string[0], string [1]);
		}
		if (string.length == 1){
			String mensagem = String.format ("[%s]", string[0]); 
		}	
		return mensagem;
	}

	public void setCombustivel(String combustivel){
		this.combustivel = combustivel;
	}

	public int getCilindros(){
		return cilindro;
	}

	public void setCilindro(int cilindro){
		this.cilindro = cilindro;
	}	
	
	public double getCilindradas(){
		return cilindradas;
	}

	public void setCilindradadas(double cilindradas){
		this.cilindradas = cilindradas;
	}

	public String getTransmissao (){
		return transmissao;
	}

	public void setTransmissao (String trasmissao){
		this.transmissao = transmissao;
	}

	public String getTracao(){
		return tracao;
	}

	public void setTracao (String tracao){
		this.tracao = tracao;
	}

	public double getCosumoCidade(){
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
		return co2
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

		caroo.setId (Integer.parseInt (dados[0]));
	        carro.setMarca (dados[1]);
		carro.setModelo (dados[2]);
		carro.setAno (Integer.parseInt (dados[3]));
		carro.setCategoria (dados[4]);
		carro.setCombustivel(dado[5]);
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
	
		String mensagem = String.format("[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.2f ## %s ## %s ## %.2f ## %.2f ## %.2f ## %b ## %s]",
    getId(), getMarca(), getModelo(), getAno(), getCategoria(), getCombustivel(), getCilindros(), getCilindradas(), 
    getTransmissao(), getTracao(), getConsumoCidade(), getConsumoEstrada(), getCO2(), getTurbo(), getData().format());
		
		return mensagem;
	}
}

class Data {

	private int ano;
	private int mes;
	private int dia;

	public Data(){
	}

	public Data (int ano; int mes; int dia){
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

		for (int i = 0; i < 500; i++){
		
			conjunto[i] = Veiculo.veiculoParse(string)
		}
	}
}


public class Tp2Q1 {
	
	public static void main (String []args){
	
		Veiculos carros5[500] = new Veiculo[500];
		carros[] = LeitorCsv.ler(caminho);	
		Scanner scanner = new Scanner (System.in);
		int vetor[] = new int[60];
		int num = scan.nextLine();
		int i = 0;

		while ( num != -1 ){

		vetor [i] = num
		i++;
		num = scan.nextLine():
		}
	
		for (int j = 0; j < 60 ; j++){
		
			for (int k = 0; k < 500; k++){
			
				if (carros.id[k] == vetor[j]){
					
					System.out.println (carros[k].format());	
				}
			}
		}
	
	}
}
