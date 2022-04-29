#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1000
typedef struct{
	int codigo;
	char descricao[30];
	float preco;
}item;
typedef struct{
	item brinquedo[MAX];
	int tamanho;
}tabela;
FILE *registro;
FILE *tam;
void cadastraBrinquedo(tabela *t);

void visualizar(tabela *t);
void remover(tabela *t);
void remover_multiplos(tabela *t);
void atualiza(tabela *t);

void main(){
	int i,opc;
	tabela t;
	tam = fopen("tamanho.txt","r");
	if(tam == NULL){
		t.tamanho = 0;
	}else{
		fscanf(tam,"%d\n",&t.tamanho);
	}
	
	printf("1-Cadastrar\n2-Visualizar\n3-remover registro\n4-remover múltiplos registros\n5-finalizar\nInforme o modulo desejado:");
	do{
		scanf("%d",&opc);
		switch(opc){
			case 1:	
				cadastraBrinquedo(&t);	
				break;
			case 2:
				visualizar(&t);
				break;
			case 3:
				remover(&t);
				break;
			case 4:
				remover_multiplos(&t);
				break;
			case 5:
				break;
		}
	}while(opc != 5);
};

void cadastraBrinquedo(tabela *t){
	int i,aux = 0,cod_aux;
	registro = fopen("dados.txt","a");
	printf("Informe o codigo do produto: ");
	scanf("%d",&cod_aux);
	for(i = 0;i < t->tamanho;i++){
		if(t->brinquedo[i].codigo == cod_aux){
			printf("Codigo ja foi cadastrado!\n");
			aux = 0;
			break;
		}else{
			aux = 1;
		}
	}	
	if(aux == 1){
		t->brinquedo[t->tamanho].codigo = cod_aux;
		printf("Informe a descricao do produto: ");
		scanf("%s",&t->brinquedo[t->tamanho].descricao);
		printf("Informe o preco do produto: ");
		scanf("%f",&t->brinquedo[t->tamanho].preco);
		fprintf(registro,"%d %s %f\n",t->brinquedo[t->tamanho].codigo,t->brinquedo[t->tamanho].descricao,t->brinquedo[t->tamanho].preco);
		t->tamanho++;
	}
	fclose(registro);
	tam = fopen("tamanho.txt","w");
	fprintf(tam,"%d",t->tamanho);
	fclose(tam);
	printf("Produtos cadastrados: %d\n",t->tamanho);
	printf("Informe o modulo desejado: ");
	}
void visualizar(tabela *t){
int i = 0;
    registro = fopen("dados.txt", "r");

     if(registro == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }else{
        for (i = 0; i < t->tamanho; i++){
            fscanf(registro, "%d %s %f", &t->brinquedo[i].codigo, t->brinquedo[i].descricao, &t->brinquedo[i].preco);
            printf("%d, %s, %f\n", t->brinquedo[i].codigo, t->brinquedo[i].descricao, t->brinquedo[i].preco);
        }
    }
    fclose(registro);
	
    printf("\n");
    printf("Informe o modulo desejado: ");
}
void remover(tabela *t){

    int codigo, i;

    printf("\nDigite o codigo a ser retirado: ");
    scanf("%d", &codigo);


    registro = fopen("dados.txt", "r");

     if(registro == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }else{
        for(i = 0; i < t->tamanho; i++){
            fscanf(registro,"%d %s %f\n", &t->brinquedo[i].codigo, t->brinquedo[i].descricao, &t->brinquedo[i].preco);
        }
        for(i = 0; i < t->tamanho; i++){
            if(t->brinquedo[i].codigo == codigo) {
                t->brinquedo[i].codigo = t->brinquedo[t->tamanho-1].codigo;
                strcpy(t->brinquedo[i].descricao,t->brinquedo[t->tamanho-1].descricao);
				t->brinquedo[i].preco = t->brinquedo[t->tamanho-1].preco;
                t->tamanho = t->tamanho - 1;
                tam = fopen("tamanho.txt","w");
				fprintf(tam,"%d",t->tamanho);
				fclose(tam);
                break;
        }
    }
    fclose(registro);
    atualiza(t);
    
	}
	printf("Informe o modulo desejado: ");	
}

void remover_multiplos(tabela *t){
	
    float preco;
	int i,remov;

    printf("\nDigite o valor a ser retirado: ");
    scanf("%f", &preco);


    registro = fopen("dados.txt", "r");

     if(registro == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }else{
        for(i = 0; i < t->tamanho; i++){
            fscanf(registro,"%d %s %f\n", &t->brinquedo[i].codigo, t->brinquedo[i].descricao, &t->brinquedo[i].preco);
        }
        do{
        for(i = 0; i < t->tamanho; i++){
        	remov = 0;
            if(t->brinquedo[i].preco < preco){
                t->brinquedo[i].codigo = t->brinquedo[t->tamanho-1].codigo;
                strcpy(t->brinquedo[i].descricao,t->brinquedo[t->tamanho-1].descricao);
				t->brinquedo[i].preco = t->brinquedo[t->tamanho-1].preco;
                t->tamanho = t->tamanho - 1;
                remov = 1;
        		}
        	}	
		}while(remov == 1);
        tam = fopen("tamanho.txt","w");
		fprintf(tam,"%d",t->tamanho);
		fclose(tam);
    }
    fclose(registro);
    atualiza(t);
	printf("Informe o modulo desejado: ");    
	}

void atualiza(tabela *t){
	int i;
	registro = fopen("dados.txt","w");
	for(i = 0; i < t->tamanho;i++){
		fprintf(registro,"%d %s %f\n",t->brinquedo[i].codigo,t->brinquedo[i].descricao,t->brinquedo[i].preco);
	}
	fclose(registro);
}
