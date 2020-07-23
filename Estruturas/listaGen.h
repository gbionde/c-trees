/*
	Autor: @Guilherme

	Estrutura de Dados
		*Lista Generalizada com Union (def. @Silvio do Lago Pereira). 
		*Auxiliares: Pilha e Fila para simular recursividade.
*/

struct regLista{
	struct listaGen *head, *tail;
};

union infoLista{
	char info[8];
	struct regLista lista;
};

struct listaGen{
	char terminal;
	union infoLista no;
};

typedef struct listaGen listaGen;


/********* AUXILIARES: 1) PILHA ******/

struct pilha{
	listaGen *info;
	struct pilha *bottom;	
};

typedef struct pilha pilha;

/*Retorna se uma pilha esta vazia ou nao.*/
char isEmptyP(pilha *p){
	return p == NULL;
}

/*Retorna o elemento  do topo da pilha (inicio da lista), sem remove-lo*/
listaGen* top(pilha *p){
	if(!isEmptyP(p))
		return p->info;	
		
	return NULL;
}

/*Insere no topo da pilha (inicio da lista)*/
void push(pilha **p, listaGen *lista){
	pilha *nova = (pilha*)malloc(sizeof(pilha));

	nova->info = lista;
	nova->bottom = *p;

	*p = nova;
}

/*Retira o elemento do topo da pilha (inicio da lista)*/
listaGen* pop(pilha **p){
	pilha *local = NULL;
	listaGen *aux = NULL;
	
	if(!isEmptyP(*p)){
		local = *p;
		aux = local->info;
		
		*p = (*p)->bottom;
		free(local);
	}
	
	return aux;
}

/********* AUXILIARES: 2) FILA ********/

struct fila{
	listaGen *info;
	struct fila *prox;
};

typedef struct fila fila;

/*Retorna se uma fila esta vazia ou nao.*/
char isEmptyF(fila *f){
	return f == NULL;
}

void enqueue(fila **f, listaGen *lista){
	fila *nova = (fila*)malloc(sizeof(fila)), *aux;
	
	nova->info = lista;
	nova->prox = NULL;
	
	if(*f == NULL)
		*f = nova;
	else{
		aux = *f;
		
		while(aux->prox != NULL)
			aux = aux->prox;
		
		aux->prox = nova;
	}
}

/*Remove e retorna o primeiro elemento da fila.*/
listaGen* dequeue(fila **f){
	fila *local = NULL;
	listaGen *aux = NULL;
	
	if(*f != NULL){
		local = *f;
		aux = local->info;
		
		*f = (*f)->prox;
		free(local);
	}
	
	return aux;
}

/********* Funcoes basicas da Lista Generalizada ********/

/*Verifica e retorna se o parametro enviado e nulo.*/
char isNull(listaGen *lista){
	return lista == NULL;
}

/*Verifica e retorna se o parametro enviado e um atomo.*/
char isAtomo(listaGen *lista){
	return !isNull(lista) && lista->terminal;	
}

/*Cria e retorna um atomo com a informacao enviada por parametro.*/
listaGen* criaT(char *info){
	listaGen *novo = (listaGen*)malloc(sizeof(listaGen));
	
	novo->terminal = 1;
	strcpy(novo->no.info, info);
	
	return novo;
}

/*Retorna a head da lista enviada por parametro.*/
listaGen* head(listaGen *lista){
	if(isNull(lista) || isAtomo(lista)){
		printf("\nHead nao pode ser nula ou atomo!");
		return NULL;
	}else
		return lista->no.lista.head;
}

/*Retorna a tail da lista enviada por parametro.*/
listaGen* tail(listaGen *lista){
	if(isNull(lista) || isAtomo(lista)){
		printf("\nTail nao pode ser nula ou atomo!");
		return NULL;
	}else
		return lista->no.lista.tail;
}

/*Constroi uma lista com uma head e uma tail, enviados por parametro.*/
listaGen* cons(listaGen *head, listaGen *tail){
	listaGen *novo;
	
	if(!isAtomo(tail)){
		novo = (listaGen*)malloc(sizeof(listaGen));
		
		novo->terminal = 0;
		novo->no.lista.head = head;
		novo->no.lista.tail = tail;
		
		return novo;		
	}
	
	printf("\n CONS: O segundo parametro nao pode ser um atomo.");
	return NULL;
}

/*Exibe uma lista enviada por parametro.*/
void exibeLista(listaGen *lista){
	if(!isNull(lista)){
		if(isAtomo(lista)){
			printf("%s,", lista->no.info);
		}else{
			printf("[");
			exibeLista(head(lista));
			exibeLista(tail(lista));
			printf("]");
		}	
	}else{
		printf("[]");
	}
}

/*Exibe somente os atomos de uma lista enviada por parametro.*/
void exibeAtomo(listaGen *lista){
	if(isAtomo(lista)){
		printf("%s", lista->no.info);
	}else{
		printf("[");
		
		while(!isNull(lista)){
			exibeAtomo(head(lista));
			
			lista = tail(lista);
			if(!isNull(lista)){
				printf(",");
			}
		}
		
		printf("]");
	}
}

/*Destroi uma lista, isto e, desaloca todos os seus membros.*/
void killLista(listaGen **lista){
	if(!isNull(*lista)){
		if(isAtomo(*lista)){
			free(*lista);
		}else{
			killLista(&(*lista)->no.lista.head);
			killLista(&(*lista)->no.lista.tail);
			free(*lista);
			
			*lista = NULL;
		}
	}
}

/*********** Funcoes extras para auxiliar e praticar a listaGen. ************/

/*Verifica e retorna se duas listas sao iguais.*/
char isEqual(listaGen *l1, listaGen *l2){
	if(isNull(l1) && isNull(l2))
		return 1;
	
	if(isNull(l1) || isNull(l2))
		return 0;
	
	if(isAtomo(l1) && isAtomo(l2))
		return !strcmp(l1->no.info, l2->no.info);
	
	if(isAtomo(l1) || isAtomo(l2)) 
		return 0;
	
	return isEqual(head(l1), head(l2)) && isEqual(tail(l1), tail(l2));
}

/*Exibe os atomos da listaGen de forma iterativa.*/
void exibe_iterativo(listaGen *l){
	pilha *p = NULL;

	if(!isNull(tail(l)))
		push(&p, tail(l));

	if(!isNull(head(l)))
		push(&p, head(l));

	printf("\n[");
	while(!isEmptyP(p)){
		l = pop(&p);
		
		if(isAtomo(l))
			printf("%s ", l->no.info);
		else{
			if(!isNull(tail(l)))
				push(&p, tail(l));

			if(!isNull(head(l)))
				push(&p, head(l));
		}
	}
	printf("]");
}

/*Conta a quantidade de atomos presentes em uma lista. Dupla recursao.*/
int contaAtomos(listaGen *l){
	if(!isNull(l)){
		if(isAtomo(l))
			return 1;
		else
			return contaAtomos(head(l)) + contaAtomos(tail(l));
	}else
		return 0;
}

/*Conta a quantidade de atomos presentes em uma lista. Recursao simples + contador iterativo.*/
int contaAtomos_hibrido(listaGen *l){
	int c = 0;
	if(!isNull(l)){
		if(isAtomo(l)){
			return 1;
		}else{
			while(!isNull(l)){
				c += contaAtomos(head(l));	
				l = tail(l);
			}	
		}
	}
	
	return c;
}

/*Conta a quantidade de atomos presentes em uma lista. Totalmente iterativo.*/
int contaAtomos_iterativo(listaGen *l){
	pilha *p = NULL;
	int c = 0;
	
	if(!isNull(l)){
		if(!isNull(tail(l)))
			push(&p, tail(l));
		if(!isNull(head(l)))
			push(&p, head(l));
			
		while(!isEmptyP(p)){
			l = pop(&p);
			
			if(isAtomo(l)){
				c++;
			}else{
				if(!isNull(tail(l)))
					push(&p, tail(l));
				if(!isNull(head(l)))
					push(&p, head(l));	
			}
		}
	}
	
	return c;
}

/*Retorna uma copia da lista enviada por parametro.*/
listaGen* duplicar(listaGen *l){
	if(isNull(l))
		return l;
	if(isAtomo(l))
		return criaT(l->no.info);
	return cons(duplicar(head(l)), duplicar(tail(l)));
}

/*Libera ("mata a lista") a memoria da listaGen.*/
void killListagen_it(listaGen **l){
	fila *f = NULL;
	listaGen *no;
	
	if(!isNull(head(*l)))
		enqueue(&f, head(*l));
		
	if(!isNull(tail(*l)))
		enqueue(&f, tail(*l));	
	
	while(!isEmptyF(f)){
		no = dequeue(&f);

		if(!isAtomo(no)){
			if(!isNull(head(no)))
				enqueue(&f, head(no));
				
			if(!isNull(tail(no)))
				enqueue(&f, tail(no));		
		}
	
		free(no);
		no = NULL;
	}
	
	*l = NULL;
}

/*Calcula o comprimento de uma listagen. Iterativo sem usar pilhas.*/
int comprimento_iterativo(listaGen* l){
	listaGen *aux;
	int c = 0, maior = 0;
	
	while(!isNull(l)){
		aux = l;	
		while(!isNull(aux)){
			if(!isAtomo(l))
				aux = tail(aux);
			else
				aux = NULL;
			c++;
		}
		
		if(c > maior)
			maior = c;
		if(!isAtomo(l))
			l = head(l);
		else
			l = NULL;
	}

	return maior;
}
