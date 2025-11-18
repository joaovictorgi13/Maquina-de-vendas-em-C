#include <stdio.h>
#include <stdlib.h>


// estrutura para representar uma maquina (nome do produto, preço, quantidade)
typedef struct {
    char nome[20];
    float preco;
    int estoque;
} Produto;

// função para inserir saldo na maquina
void inserirSaldo(float *saldo){
    float notas[] = { 2.0f, 5.0f, 10.0f, 20.0f, 50.0f, 100.0f }; 
    int quantidade_de_notas = sizeof(notas) / sizeof(notas[0]); //notas disponiveis

     // mostra as opções de notas disponiveis na maquina
    for (int i = 0; i < quantidade_de_notas; i++){
        printf("%d. R$%.2f\n", i + 1, notas[i]);
    }
    printf("Escolha uma nota para inserir (0 para sair): ");
    
    int escolha;
    scanf("%d", &escolha);

    if(escolha == 0) {
        return;
        // escolha válida → adiciona o valor da nota ao saldo
    } else if (escolha >= 1 && escolha <= quantidade_de_notas) {
        *saldo += notas[escolha - 1];
    } else {
        printf("Opção Inválida!\n");
    }    
}

void exibirProdutos(Produto *maquina[], int tamanho, float saldo){
    system("cls"); //limpa a tela
    printf("=== Maquina de Vendas ===\n");
    printf("Saldo R$%.2f\n\n", saldo);

    // percorre todos os produtos e exibe suas informações
    for (int i = 0; i < tamanho; i++ ){
        printf("%d. %s\t- R$%.2f (Em estoque: %d)\n", 
          i + 1, maquina[i]->nome, maquina[i]->preco, maquina[i]->estoque);
    }
    printf("\n0.Sair\n");

}

void vender(Produto *produto, float *saldo){
    produto->estoque--; // diminui um produto do estoque
    *saldo -= produto->preco; //subtrai o preco do saldo
}

int main(){
    // lista de produtos disponíveis na máquina
    Produto itens [] = {
        { "Refrigerante", 6.0, 10 },
        { "Chocolate", 4.0, 20 },
        { "Salgadinho", 5.0, 10 },
        { "Suco", 6.0 , 8 }  
    };
    const int PRODUTOS_QTD = sizeof(itens) / sizeof(Produto); // calcula a quantidade de produtos disponiveis na maquina (evitar usar numero magico)

    // vetor de ponteiros para produtos
    Produto *maquina[PRODUTOS_QTD];
    for (int i = 0; i < PRODUTOS_QTD; i++ ){
        maquina[i] = &itens [i];
    }


    float saldo = 0.0f;

    int opcao = -1;

    // loop principal do programa
    while (opcao != 0) {
        system("cls");
        inserirSaldo(&saldo); // Usuario insere saldo 

        exibirProdutos(maquina, PRODUTOS_QTD, saldo);

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        if (opcao == 0){
            break; // sai do loop
        } else if (opcao >= 1 && opcao <= PRODUTOS_QTD){ // se o produto for valido
            vender(maquina[opcao - 1], &saldo); // realiza a vendda
        }
        
    
    }

    printf("Programa Encerrado!\n");
    return 0;
}