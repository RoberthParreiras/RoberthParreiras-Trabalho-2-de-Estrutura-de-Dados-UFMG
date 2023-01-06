#include <string>
#include <math.h>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdlib.h>

/*compara pai e filho, e substitui*/
void HeapSort(std::string dados[], std::string nomes[], int tamanho) { 
  if (tamanho <= 0) 
    throw "ERRO: Vetores vazios\n";
  
  int i = tamanho / 2, pai, filho; 
  std::string t, r;

  while(true) {
    if(i > 0) {
      i--;
      t = dados[i];
      r = nomes[i];
    } else {
      tamanho--;

      if(tamanho <= 0) 
        return;

      t = dados[tamanho];
      r = nomes[tamanho];

      dados[tamanho] = dados[0];
      nomes[tamanho] = nomes[0];
    }

    pai = i;
    filho = i * 2 + 1;

    
    while (filho < tamanho) {
      if((filho + 1 < tamanho)  &&  (dados[filho + 1] > dados[filho]))
        filho++;

      if(dados[filho] > t) {
        dados[pai] = dados[filho];
        nomes[pai] = nomes[filho];

        pai = filho;
        filho = pai * 2 + 1;
      } else {
        break;
      }
    }

    dados[pai] = t;
    nomes[pai] = r;
  }
}

/*aplica divisao e conquista no vetor*/
void QuickSort(std::string nomes[], std::string dados[], int primeiro, int ultimo) {
  if (ultimo <= 0) 
    throw "ERRO: Vetores vazios\n";
  
  int i, j;
  std::string pivo, aux, aux2;
	
  i = primeiro;
	j = ultimo - 1;
	pivo = nomes[(primeiro + ultimo) / 2];

  
	while(i <= j) {
		while(nomes[i] < pivo && i < ultimo) {
			i++;
		}
		while(nomes[j] > pivo && j > primeiro) {
			j--;
		}

		if(i <= j) {
			aux = nomes[i];
      aux2 = dados[i];
			nomes[i] = nomes[j];

      dados[i] = dados[j];
			nomes[j] = aux;
      dados[j] = aux2;
			
      i++;
			j--;
		}
	}

	if(j > primeiro)
		QuickSort(nomes, dados, primeiro, j+1);
	if(i < ultimo)
		QuickSort(nomes, dados, i, ultimo);
}

/*copia os nomes e dados de volta*/
void Juntar(std::string nomes[], std::string dados[], int ini, int meio, int fim, std::string nomesAux[], std::string dadosAux[]) {
  int esq = ini;
  int dir = meio;

  for(int i = ini; i < fim; ++i) {
    if((esq < meio) && ((dir >= fim) || (nomes[esq] < nomes[dir]))) {
      nomesAux[i] = nomes[esq];
      dadosAux[i] = dados[esq];
      ++esq;
    } else {
      nomesAux[i] = nomes[dir];
      dadosAux[i] = dados[dir];
      ++dir;
    }
  }

  
  for(int i = ini; i < fim; ++i) {
    nomes[i] = nomesAux[i];
    dados[i] = dadosAux[i];
  }
}

/*chama a si mesmo e o metodo juntar para ordenar*/
void MergeSort1(std::string nomes[], std::string dados[], int inicio, int fim, std::string nomesAux[], std::string dadosAux[]) {
  if ((fim - inicio) < 2) 
    return;
    
  int meio = ((inicio + fim)/2);
  MergeSort1(nomes, dados, inicio, meio, nomesAux, dadosAux);
  MergeSort1(nomes, dados, meio, fim, nomesAux, dadosAux);

  Juntar(nomes, dados, inicio, meio, fim, nomesAux, dadosAux);
}

/*cria nomes e dados auxiliar, como tambem o metodo MergeSort1*/
void MergeSortDefinitivo(std::string nomes[], std::string dados[], int tamanho) {
  if (tamanho <= 0) 
    throw "ERRO: Vetores vazios\n";
  
  std::string *nomesAux = (std::string*) malloc(tamanho * sizeof(std::string));
  std::string *dadosAux = (std::string*) malloc(tamanho * sizeof(std::string));

  MergeSort1(nomes, dados, 0, tamanho, nomesAux, dadosAux);

  free(nomesAux);
  free(dadosAux);
}   


  /*inicia o valor da base com 1, t.q 2^0*/
int BinaryToDecimal(std::string n) {
  std::string num = n;
  int dec_value = 0;
  int base = 1;
 
  int len = num.length();
  for(int i = len - 1; i >= 0; i--) {
    if(num[i] == '1')
      dec_value += base;
  
    base = base * 2;
  }
 
  return dec_value;
}

/*transforma os binarios em inteiros para ordenar e depois transforma de volta em binario*/
void RadixSort(std::string dados[], std::string nomes[], int tamanho) {
  if (tamanho <= 0) 
    throw "ERRO: Vetores vazios\n";
  
  int tamanhoAux = tamanho;
  int i = 0;

  /*criando vetores auxiliares*/
  int *a = (int*) malloc(tamanho * sizeof(int));
  std::string *aAux = (std::string*) malloc(tamanho * sizeof(std::string));
  int *b = (int*) malloc(tamanho * sizeof(int));
  std::string *bAux = (std::string*) malloc(tamanho * sizeof(std::string));

  /*transforma os binarios em inteiros*/
  while(tamanhoAux > 0) {
    a[i] = BinaryToDecimal(dados[i]); 
    aAux[i] = nomes[i];
    i++;
    tamanhoAux--;
  }
    

  int maior = a[0];
  int exp = 1;

  for(i = 0; i < tamanho; i++) 
    if(a[i] > maior)
      maior = a[i];
  

  while(maior/exp > 0) {
    int bucket[10] = { 0 };
    int bucketAux[10] = { 0 };
    	
    for(i = 0; i < tamanho; i++) {
    	bucket[(a[i] / exp) % 10]++;
      bucketAux[(a[i] / exp) % 10]++;
    }
    	
    for(i = 1; i < 10; i++) {
    	bucket[i] += bucket[i - 1];
      bucketAux[i] += bucketAux[i - 1];
    }
    for(i = tamanho - 1; i >= 0; i--) {
    	b[--bucket[(a[i] / exp) % 10]] = a[i];

      bAux[--bucketAux[(a[i] / exp) % 10]] = aAux[i];
    }
    
    for(i = 0; i < tamanho; i++) {
    	a[i] = b[i];
      aAux[i] = bAux[i];
    }
    	
    exp *= 10;
  }
    
  i = 0;
  while(tamanho > i) {
    dados[i] = std::bitset<8>(a[i]).to_string();  
    nomes[i] = aAux[i];
    i++;
  }
  
  free(a);
  free(b);
  free(aAux);
  free(bAux);
    
}


/*checa todas as configuracoes com o arquivo de entrada*/
int main(int argc, char* argv[]) {    
  std::fstream file(argv[1]);
  char *configuracao = argv[2];
  char *tamanhoDeEntrada = argv[3];
  int tamanho = atoi(tamanhoDeEntrada);
  int i = 0;

  std::string *nomes = (std::string*) malloc(tamanho * sizeof(std::string));
  std::string *dados = (std::string*) malloc(tamanho * sizeof(std::string));
  std::string palavra;
    

  if(!file) 
    printf("arquivo nao encontrado\n");
    

    
  while(file >> palavra) {
    if(i == tamanho)
      break;
      
    nomes[i] = palavra;
    file >> palavra;
    dados[i] = palavra;
    ++i;
  }

  if(*configuracao == '1') {
      HeapSort(dados, nomes, tamanho);                         
      QuickSort(nomes, dados, 0, tamanho);                   
  } else if(*configuracao == '2') {
      RadixSort(dados, nomes, tamanho);                    
      QuickSort(nomes, dados, 0, tamanho);                
  } else if(*configuracao == '3') {
      HeapSort(dados, nomes, tamanho);                 
      MergeSortDefinitivo(nomes, dados, tamanho);     
  } else if(*configuracao == '4') {               
      RadixSort(dados, nomes, tamanho);              
      MergeSortDefinitivo(nomes, dados, tamanho);   
  }
  
    
  for(i = 0; i < tamanho; ++i)
    std::cout << nomes[i] << " " <<  dados[i] << std::endl;
    

  free(nomes);
  free(dados);

  return 0;
}