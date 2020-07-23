/* 
 *	Autor: @Guilherme.
 * 	Estrutura de Dados - ABB
 * 		+Pilha e Fila para a simulacao de recursividade.
 */

struct tree{
    int info;
    struct tree *esq, *dir;
};

typedef struct tree tree;

/************* AUXILIARES: PILHA *************/

struct pilha{
	tree *info;
	struct pilha *bottom;	
};

typedef struct pilha pilha;

/*Retorna se uma pilha esta vazia ou nao.*/
char isEmptyP(pilha *p){
	return p == NULL;
}

/*Retorna o elemento do topo da pilha (inicio da lista), sem remove-lo.*/
tree* top(pilha *p){
	if(!isEmptyP(p))
		return p->info;	
	return NULL;
}

/*Insere um elemento no topo da pilha (inicio da lista).*/
void push(pilha **p, tree *no){
	pilha *nova = (pilha*)malloc(sizeof(pilha));

	nova->info = no;
	nova->bottom = *p;

	*p = nova;
}

/*Retira o elemento do topo da pilha (inicio da lista).*/
tree* pop(pilha **p){
	pilha *local = NULL;
	tree *aux = NULL;
	
	if(!isEmptyP(*p)){
		local = *p;
		aux = local->info;
		
		*p = (*p)->bottom;
		free(local);
	}
	
	return aux;
}

/************* AUXILIARES: FILA *************/

struct fila{
	tree *info;
	struct fila *prox;
};

typedef struct fila fila;

/*Retorna se uma fila esta vazia ou nao.*/
char isEmptyF(fila *f){
	return f == NULL;
}

/*Insere um elemento no fim da fila.*/
void enqueue(fila **f, tree *no){
	fila *nova = (fila*)malloc(sizeof(fila)), *aux;
	
	nova->info = no;
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

/*Retira um elemento do inicio da fila.*/
tree* dequeue(fila **f){
	fila *local = NULL;
	tree *aux = NULL;
	
	if(*f != NULL){
		local = *f;
		aux = local->info;
		
		*f = (*f)->prox;
		free(local);
	}
	
	return aux;
}

/************ ARVORE BINARIA DE BUSCA *******/

/*Inicializa a arvore com um valor nulo.*/
void inicializar(tree **raiz){
    *raiz = NULL;
}

/*Cria e retorna um novo node contendo a informacao especificada.*/
tree* criarNode(int info){
    tree *novo = (tree*)malloc(sizeof(tree));

    novo->info = info;
    novo->esq = novo->dir = NULL;

    return novo;
}

/*Desaloca ("mata a arvore") todos os nodes da arvore.*/
void killTree(tree **raiz){
	if(*raiz != NULL){
		killTree(&(*raiz)->esq);
		killTree(&(*raiz)->dir);
		free(*raiz);
		
		*raiz = NULL;
	}
}

/*Busca um node especifico na arvore e o retorna por parametro na variavel out.*/
void buscarNodeABB(tree *raiz, tree **out, int chave){
    if(raiz != NULL){
        if(chave == raiz->info)
            *out = raiz;
        else if(chave < raiz->info)
            buscarNodeABB(raiz->esq, &(*out), chave);
        else 
            buscarNodeABB(raiz->dir, &(*out), chave);
    }
}

/*Busca um node de forma iterativa, salva o resultado no out.*/
void buscarNodeABB_iterativo(tree *raiz, tree **out, int chave){
    while(raiz != NULL && chave != raiz->info){
        if(chave < raiz->info)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    
    *out = raiz;
}

/*Busca o pai de um node e o salva na variavel out enviada por parametro.*/
void buscarPaiABB(tree *raiz, tree **out, int chave){
    if(raiz != NULL){
        if(raiz->info == chave)
            *out = raiz;
        else 
			if(raiz->dir != NULL && raiz->dir->info == chave)
        	    *out = raiz;
    	else 
			if(raiz->esq != NULL && raiz->esq->info == chave)
        		*out = raiz;
		else 
			if(chave < raiz->info)
    			buscarPaiABB(raiz->esq, &(*out), chave);
			else
    			buscarPaiABB(raiz->dir, &(*out), chave);
    }else
    	*out = NULL;
}

/*Busca o pai de um node e salva na variavel out enviada por parametro, de forma iterativa.*/
void buscarPaiABB_iterativo(tree *raiz, tree **out, int chave){
    *out = NULL;    
    
	while(raiz != NULL && *out == NULL){
        if(raiz->dir != NULL && raiz->dir->info == chave)
            *out = raiz;
        else 
            if(raiz->esq != NULL && raiz->esq->info == chave)
                *out = raiz;
    }
}

/*Obtem e retorna por parametro o menor elemento da subarvore direita.*/
void getMenorDireita(tree *raiz, tree **out){
    if(raiz->dir != NULL){
        *out = raiz->dir;
    
        while((*out)->esq != NULL){
            *out = (*out)->esq;
        }
    }    
}

/*Busca um pai e um filho, retorna os nodes por parametro.*/
void buscarPaiFilhoABB(tree *raiz, int info, tree **filho, tree **pai){

    buscarPaiABB(raiz, &*pai, info);   
    if(*pai != NULL){
        if((*pai)->info == info)    
            *filho = *pai;
        else
            if(info < (*pai)->info)
                *filho = (*pai)->esq;
            else
                *filho = (*pai)->dir;   
    }else
        *filho = *pai;
}

/*Insere na arvore binaria de forma recursiva.*/
void inserirABB(tree **raiz, int info){
    if(*raiz == NULL){
        *raiz = criarNode(info);
    }else{
        if(info < (*raiz)->info)
            inserirABB(&(*raiz)->esq, info);
        else
            inserirABB(&(*raiz)->dir, info);
    }
}

/*Insere na arvore binaria de forma recursiva.*/
void inserirABB_dois(tree **raiz, int info){
    if(*raiz == NULL){
        *raiz = criarNode(info);
    }else{
        if(info < (*raiz)->info){
            if((*raiz)->esq != NULL)
                inserirABB(&(*raiz)->esq, info);
            else
                (*raiz)->esq = criarNode(info);
        }else{
            if((*raiz)->dir != NULL)
                inserirABB(&(*raiz)->dir, info);
            else
                (*raiz)->dir = criarNode(info);
        }
    }
}

/*Insere na arvore binaria de forma iterativa.*/
void inserirABB_it(tree **raiz, int info){
    tree *aux, *ant;

    if(*raiz == NULL)
        *raiz = criarNode(info);
    else{
        aux = *raiz;
        while(aux != NULL){
            ant = aux;
            if(info < aux->info)
                aux = aux->esq;
            else
                aux = aux->dir;
        }

        if(info < ant->info)
            ant->esq = criarNode(info);
        else
            ant->dir = criarNode(info);
    }
}

/*Percorre a arvore em pre-ordem.*/
void preOrdem(tree *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->info);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

/*Percorre a arvore em in-ordem.*/
void inOrdem(tree *raiz){
    if(raiz != NULL){
        inOrdem(raiz->esq);
        printf("%d", raiz->info);
        inOrdem(raiz->dir);
    }
}

/*Percorre a arvore em pos-ordem.*/
void posOrdem(tree *raiz){
    if(raiz != NULL){
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->info);
    }
}

/*Conta a quantidade de nodes na arvore*/
void contarNos(tree *raiz, int *qtd){
    if(raiz != NULL){
        *qtd += 1;
        contarNos(raiz->dir, &*qtd); 
        contarNos(raiz->esq, &*qtd);
    }
}

/* -------> EXCLUSAO BALANCEADA COM SUBSTITUTO <-------- */

/*TERCEIRA PARTE: Efetua a exclusao de um node da arvore. Recebe o '@e' (elemento) a ser excluido e o @pai do mesmo.*/
void excluirABB_remover(tree **raiz, tree *e, tree *pai, char lado){
    tree *sub, *paiSub;
    int aux;

    if(e->esq == NULL && e->dir == NULL){   /*Elemento a ser removido eh uma folha*/   
        if(e != pai){
            if(e->info > pai->info)         /*..Eh a folha direita.*/
                pai->dir = NULL;
            else
                pai->esq = NULL;            /*..Eh a folha esquerda.*/
        }else
            *raiz = NULL;
    	free(e);
    }else{
        if(e->esq == NULL || e->dir == NULL){   /*Nao eh uma folha, possui um filho.*/
            if(e != pai){                       /*O elemento nao ocupa a mesma posicao que o pai.*/
                if(e->info > pai->info){        /*Verifica a posicao do node*/
                    if(e->esq != NULL)
                        pai->dir = e->esq;
                	else
					   	pai->dir = e->dir;
                }else{
                    if(e->esq != NULL)
                        pai->esq = e->esq;
                    else
					   	pai->esq = e->dir;
                }
            }else
                if(e->esq != NULL)
                    *raiz = e->esq;
                else
                    *raiz = e->dir;
            free(e);
		}else{      /*Possui os dois filhos.*/
            paiSub = e;
            if(lado == 'd'){    
                sub = e->dir;
                while(sub->esq != NULL){    /*Buscando o node substituto. Menor node da subárvore.*/
                    paiSub = sub;
                    sub = sub->esq;
                }
            }else{
                sub = e->esq;
                while(sub->dir != NULL){    /*Buscando o node substituto. Menor node da subárvore.*/
                    paiSub = sub;
                    sub = sub->dir;
                }
            }
			
            aux = sub->info;
            excluirABB_remover(&*raiz, sub, paiSub, lado);    /*Chamada recursiva para remover o node.*/
            e->info = aux;
        }
    }
}

/*SEGUNDA PARTE: Verifica se a arvore esta balanceada, se nao, realiza a exclusao com balanceamento.*/
void excluirABB_balancear(tree **raiz, tree *no){
    int qtd, qte, aux, FB;
    tree *e = NULL, *pai = NULL;
    
    do{
        qtd = qte = 0;
        contarNos(no->dir, &qtd);
        contarNos(no->esq, &qte);

        FB = qtd - qte;
        if(FB < -1 || FB > 1){  /*Verifica se a arvore esta desbalanceada.*/
            aux = no->info;

            if(no->esq == NULL)  /*Caso seja o ultimo node, setar nulo.*/
                no = no->dir;
            else
                if(no->dir == NULL)
                    no = no->esq;

            buscarPaiFilhoABB(*raiz, aux, &e, &pai);    /*Busca o elemento a ser excluido e o pai do mesmo.*/
            
        	if(FB > 0)
                excluirABB_remover(&*raiz, e, pai, 'd');
            else
	            excluirABB_remover(&*raiz, e, pai, 'e');
            
            inserirABB(&*raiz, aux); 	/*Reinsere o elemento excluido na arvore.*/
        }
    }while(FB < -1 || FB > 1);  /*Loop enquanto a arvore estiver desbalanceada.*/
}

/*PRIMEIRA PARTE: Percorre a arvore em nivel chamando os métodos de balanceamento e exclusao.*/
void excluirBalancearABB(tree **raiz, int info){
    tree *filho, *pai, *no;
    fila *f = NULL;

	filho = pai = no = NULL;
    enqueue(&f, *raiz);
    while(!isEmptyF(f)){    /*Andando a arvore em nivel.*/
        no = dequeue(&f);
        excluirABB_balancear(&*raiz, no);

        if(no->esq != NULL)
            enqueue(&f, no->esq);
        if(no->dir != NULL)
            enqueue(&f, no->dir);
    }
}
