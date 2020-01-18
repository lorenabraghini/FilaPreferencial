#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->idade = -1;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->ant;
	}
	printf("\n\n");
}


int consultarIdade(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->idade;
		atual = atual->prox;
	}
	return -1;
}



bool inserirPessoaNaFila(PFILA f, int id, int idade){
	PONT teste = buscarID(f, id);
	if(id<0 || idade<0 || teste!= NULL) return false;

	PONT pessoa = (PONT) malloc(sizeof(ELEMENTO));
	pessoa->id = id;
	pessoa->idade = idade;

	if(idade >= IDADEPREFERENCIAL){
		if(f->cabeca->prox == f->cabeca){
			f->cabeca->prox = pessoa;
			f->cabeca->ant = pessoa;
			pessoa->ant = f->cabeca;
			pessoa->prox = f->cabeca;
		}
		else if(f->cabeca->prox == f->inicioNaoPref){
			f->inicioNaoPref->ant = pessoa;
			f->cabeca->prox = pessoa;
			pessoa->prox = f->inicioNaoPref;
			pessoa->ant = f->cabeca;
		}
		else if(f->inicioNaoPref == f->cabeca){
			pessoa->ant = f->cabeca->ant;
			pessoa->prox = f->cabeca;
			f->cabeca->ant->prox = pessoa;
			f->cabeca->ant = pessoa;
		}
		else{
			pessoa->ant = f->inicioNaoPref->ant;
			pessoa->prox = f->inicioNaoPref;
			f->inicioNaoPref->ant->prox = pessoa;
			f->inicioNaoPref->ant = pessoa;

		}
	}

	else{
		if(f->cabeca->prox == f->cabeca){
			pessoa->prox = f->cabeca;
			pessoa->ant = f->cabeca;
			f->inicioNaoPref = pessoa;
			f->cabeca->prox = pessoa;
			f->cabeca->ant = pessoa;
		}
		else if(f->inicioNaoPref == f->cabeca){
			pessoa->ant = f->cabeca->ant;
			pessoa->prox = f->cabeca;
			f->cabeca->ant->prox = pessoa;
			f->cabeca->ant = pessoa;
			f->inicioNaoPref = pessoa;
		}
		else{
			pessoa->ant = f->cabeca->ant;
			pessoa->prox = f->cabeca;
			f->cabeca->ant->prox = pessoa;
			f->cabeca->ant = pessoa;
		}
	}

	return true;
}

bool atenderPrimeiraDaFila(PFILA f, int* id){

	if(f->cabeca->prox == f->cabeca) return false;
	PONT pessoa = f->cabeca->prox;
	*id = pessoa->id;
	
	pessoa->prox->ant = pessoa->ant;
	pessoa->ant->prox = pessoa->prox;

	if(pessoa->idade < IDADEPREFERENCIAL) f->inicioNaoPref = pessoa->prox;	

	free(pessoa);
	return true;
}


bool desistirDaFila(PFILA f, int id){

	PONT pessoa = buscarID(f, id);
	if(!pessoa) return false;
	pessoa->prox->ant = pessoa->ant;
	pessoa->ant->prox = pessoa->prox;

	if(pessoa->idade < IDADEPREFERENCIAL) f->inicioNaoPref = pessoa->prox;	

	free(pessoa);
	return true;

}