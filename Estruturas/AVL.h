/* 
 *	Autor: @Guilherme.
 * 	Estrutura de Dados - AVL
 */

struct tree{
    int info;
    struct tree *esq, *dir;
};

typedef struct tree tree;

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

/*Rotaciona a arvore para a esquerda.*/
void rotacionarEsq(tree **raiz){
	tree *q, *temp;

	q = (*raiz)->dir;
	temp = q->esq;
	q->esq = *raiz;
	
	(*raiz)->dir = temp;
	*raiz = q;
}

/*Rotaciona a arvore para a direita.*/
void rotacionarDir(tree **raiz){
	tree *q, *temp;
	
	q = (*raiz)->esq;
	temp = q->dir;
	q->dir = *raiz;

	(*raiz)->dir = temp;
	*raiz = q;
}

/*Calcula a altura de um node.*/
int altura(tree *raiz) {
   int esq = 0, dir = 0;
   
   if(raiz != NULL){
      esq = altura(raiz->esq);
      dir = altura(raiz->dir);
      
	  if(esq < dir) 
	  	return dir+1;
	  return esq+1;
   }else
		return 0;
}

/*Insere e realiza o balanceamento. Recursivo.
  @rot: indica se houve rotacao de balanceamento na arvore.
*/
void inserirAVL(tree **raiz, int info, char *rot){
	int FB, FBfilho;

    /*Busca a posicao para inserir o node.*/
	if(*raiz == NULL){
		*raiz = criarNode(info);
		*rot = 0;
	}else
		if(info < (*raiz)->info)
			inserirAVLR(&(*raiz)->esq, info, &*rot);
		else
			inserirAVLR(&(*raiz)->dir, info, &*rot);

    /*Procedimento de balanceamento.*/    
    if(!*rot){
		FB = altura((*raiz)->dir) - altura((*raiz)->esq);   /*Calcula o fator de balanceamento.*/
		
		if(FB == 2 || FB == -2){	                        /*Desbalanceado.*/
			*rot = 1;
			
			if(FB == 2){
				FBfilho = altura((*raiz)->dir->dir) - altura((*raiz)->dir->esq);
			
				if(FBfilho == 1){	                        /*FB 2, 1.*/
					rotacionarEsq(&*raiz);
				}else{				                        /*FB 2, -1.*/
					rotacionarDir(&(*raiz)->dir);
					rotacionarEsq(&*raiz);
				}
			
			}else{					
				FBfilho = altura((*raiz)->esq->dir) - altura((*raiz)->esq->esq);
			
				if(FBfilho == 1){	                        /*FB -2, 1.*/
					rotacionarEsq(&(*raiz)->esq);
					rotacionarDir(&*raiz);
				}else{				                        /*FB -2, -1.*/
					rotacionarDir(&*raiz);
				}
			}
		}
	}		
}
