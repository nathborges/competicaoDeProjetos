/**
 2ECR - CHALLENGE SPRINT II
 Maria Carolina Correa Tozelli - 87086
 Antonio Mario Pio Cardoso Soares Frioli - 86639
 Lucca Juliani Pontes - 87535
 Pedro Modesto Mesquita - 87880
 Arthur Sales Guilherme - 86786
 Nathália Ferreira Borges - 88426
 */

#include <iostream>

#include<locale>

#include<cstring>

using namespace std;

#define SIZE 50

#define MAXCOMPONENTS 4

#define MAXPROJECTS 10

struct componenteModel {
  char nome[SIZE];
  char cpf[SIZE];
};

typedef struct componenteModel Componente;

struct projectModel {
  char nome[SIZE];
  char link[SIZE];
  double investimentoNecessario;
  Componente componentesDoProjeto[MAXCOMPONENTS];
  double nota1;
  double nota2;
  double nota3;
  double media;
};

typedef struct projectModel Projeto;

Projeto arrayComTodosOsProjetos[MAXPROJECTS];


// Recebe um objeto do tipo projeto, dentro de um loop pega o input de dados do componente
// retornando o mesmo projeto com os componentes alterados
Projeto criandoTodosComponentes(Projeto ProjetoNovo) {
    int i = 0;
    int next = 1;
    int qntComponentes = 6;
    
    while (qntComponentes > MAXCOMPONENTS || qntComponentes == 0) {
        cout << "\n\t\tComponentes do projeto " << ProjetoNovo.nome << "\t\t";
        cout << "\nAtenção: A quantidade máxima de componentes por projeto são 4 pessoas.";
        cout << "\nInsira a quantidade de componentes: ";
        cin >> qntComponentes;
    }
    
    cin.ignore();
    
    for (i; i < qntComponentes; i++) {
        cout << "\nComponente "<< i + 1 <<"\n";
        cout << "Insira o nome do componente: ";
        cin.getline(ProjetoNovo.componentesDoProjeto[i].nome, 100);
        
        cout << "Insira apenas os números do CPF do componente, sem pontuação: ";
        cin.getline(ProjetoNovo.componentesDoProjeto[i].cpf, 100);
    }
    
    cout << i;
    for (i; i <= MAXCOMPONENTS-1; i++) {
        strcpy(ProjetoNovo.componentesDoProjeto[i].nome, "");
        strcpy(ProjetoNovo.componentesDoProjeto[i].cpf, "0");
    }
    
    return ProjetoNovo;
}

// Recebe um objeto do tipo projeto, pega o input de notas e cálculo de média,
// retornando o mesmo projeto com as notas setadas
Projeto cadastrandoECalculandoNotas(Projeto ProjetoNovo) {
    
    cout << "\n\t\tNotas do projeto " << ProjetoNovo.nome << "\nNota 1: ";
    cin >> ProjetoNovo.nota1;
    cout << "Nota 2: ";
    cin >> ProjetoNovo.nota2;
    cout << "Nota 3: ";
    cin >> ProjetoNovo.nota3;
    
    double sum = ProjetoNovo.nota1 + ProjetoNovo.nota2 + ProjetoNovo.nota3;
    ProjetoNovo.media = sum/3.f;
    
    cout << "Média de notas: " << ProjetoNovo.media;

    return ProjetoNovo;
}

Projeto criandoUmNovoProjeto() {
    Projeto ProjetoNovo;
    
    cout << "\n\t\tREGISTRO DE NOVO PROJETO\t\t" << "\nInsira o nome do projeto: ";
    cin.getline(ProjetoNovo.nome, 100);
    
    cout << "Insira o link do projeto: ";
    cin.getline(ProjetoNovo.link, 100);
    
    cout << "Insira o investimento desejado para o projeto: ";
    cin >> ProjetoNovo.investimentoNecessario;
    
    cin.ignore();

    ProjetoNovo = criandoTodosComponentes(ProjetoNovo);
    ProjetoNovo = cadastrandoECalculandoNotas(ProjetoNovo);
    
    cout << "\n O PROJETO " << ProjetoNovo.nome << " FOI CADASTRADO COM SUCESSO! BOA SORTE!\n";
    
    return ProjetoNovo;
}

// Laco de repeticao que controla a quantidade de projetos que vão ser criados e
// aloca ele dentro da variável de registro de projetos
void loopDeRegistroDeProjetos(Projeto vetor[]) {
    int stop = 1;
    
    for (int i = 0; i < MAXPROJECTS && stop != 0; i++) {
        Projeto ProjetoNovo = criandoUmNovoProjeto();
        
        vetor[i] = ProjetoNovo;
        
        cout << "\n\nDigite [1] para cadastrar mais um projeto. \nDigite [0] para finalizar o cadastro de projetos. \nOpção desejada: ";
        cin >> stop;
        cout << "\n";
        cin.ignore();
    }
}


// Realiza a ordenação do arrayComTodosOsProjetos a partir do valor de investimento, de forma crescente
void ordenacaoBubbleSort(Projeto vetor[], int n) {
    Projeto aux;
    int troca=1;
    for (int i=0; i < n-1 && troca==1; i++){
        troca=0;
        for (int j=0;j<n-i-1;j++){
            if (vetor[j].investimentoNecessario > vetor[j+1].investimentoNecessario && strcmp(vetor[j+1].nome, "") != 0 ) {
                aux=vetor[j];
                vetor[j]=vetor[j+1];
                vetor[j+1]=aux;
                troca=1;
            }
        }
    }
}

// Soma pontos aos x primeiros colocados
void somaPontosNosPrimeirosColocados(Projeto vetor[], int limiteDeColocados, double pontosAdicionados) {
    for (int i = 0; i < limiteDeColocados; i++) {
        // Verificando se a média não é 10 e se existe algum dado de projeto alocado no vetor
        if (vetor[i].media < 10 && strcmp(vetor[i].nome, "") != 0 ) {
            vetor[i].media = (vetor[i].media + pontosAdicionados);
        }
    }
}

// Após computar todas as médias deve ser apresentar a listagem com as médias e o nome de cada projeto.
void printDeTodosOsProjetosEMedias(Projeto vetor[]) {
    
    cout << "\n\t\tCONFIRA TODOS OS REGISTROS DOS PROJETOS\t\t";

    for (int i = 0; i < MAXPROJECTS; i++) {
        // Verificando se existe algum dado no vetor
        if (strcmp(vetor[i].nome, "") != 0) {
        cout << "\nProjeto " << vetor[i].nome << "\n";
        cout << "Média das notas: " << vetor[i].media << "\n";
        }
    }
}

// Printando os dados do vencedor, a partir da posicao dele dentro do array
void printDoProjeto(Projeto vetor[], int index) {
        cout << "\n\t\t Projeto " << vetor[index].nome << "\n";
        cout << "\tLink: " << vetor[index].link << "\n";
        cout << "\tInvestimento: " << vetor[index].investimentoNecessario << " reais\n";
        cout << "\tComponentes:\n";
        
        for(int i = 0; i <= 3; i++) {
            cout << "\t\t" << vetor[index].componentesDoProjeto[i].nome;
            cout << "\t" << vetor[index].componentesDoProjeto[i].cpf << "\n";
        }
        
    
        cout << "\tNota 1: " << vetor[index].nota1 << "\n";
        cout << "\tNota 2: " << vetor[index].nota2 << "\n";
        cout << "\tNota 3: " << vetor[index].nota3 << "\n";
        cout << "\tMédia das notas: " << vetor[index].media << "\n\n";

}

// Descobrindo a posicao do vencedor, ou seja, quem tem a média maior, e vendo se há empate
int descobrindoAPosicaoDoVencedor(Projeto vetor[]) {
    double vencedorMedia = 0;
    int vencedorPosicao;
    int empate[9];
    
    for (int i = 0; i < MAXPROJECTS; i++) {
        if (vetor[i].media > vencedorMedia) {
            vencedorMedia = vetor[i].media;
            vencedorPosicao = i;
        }
    }
    
    for (int i = 0; i < MAXPROJECTS; i++) {
        if (vetor[i].media == vencedorMedia && i != vencedorPosicao) {
            cout << "\n\t\tEMPATE\t\t";
            cout << "\nOcorreu um empate entre o projeto " << vetor[vencedorPosicao].nome << " e o projeto " << vetor[i].nome << "\n";
            printDoProjeto(vetor, vencedorPosicao);
            printDoProjeto(vetor, i);
            
         cout << "De acordo com as nossas regras, apenas um pode ganhar o premio. Qual será o projeto escolhido? \nDigite [" << vencedorPosicao <<"] para o projeto "
         << vetor[vencedorPosicao].nome
         << "\nDigite [" << i <<"] para o o projeto " << vetor[i].nome << "\nOpção desejada: ";
            cin >> vencedorPosicao;
        }
    }
    
    return vencedorPosicao;
}


int main()
{
    loopDeRegistroDeProjetos(arrayComTodosOsProjetos);
    
    printDeTodosOsProjetosEMedias(arrayComTodosOsProjetos);
    
    ordenacaoBubbleSort(arrayComTodosOsProjetos, 9);
    
    somaPontosNosPrimeirosColocados(arrayComTodosOsProjetos, 5, (double)0.5);
    
    int vencedorPosicao = descobrindoAPosicaoDoVencedor(arrayComTodosOsProjetos);
    
        
    int next = 0;
    cout << "\n\nDigite [1] para saber qual projeto foi o vencedor \nOpção desejada: ";
    cin >> next;
    
    if (next == 1) {
        cout << "\n\t\tPREMIAÇÃO\t\t";
        cout << "\nÉ com muito prazer que anunciamos o projeto vencedor desse ano! Que rufem os tambores...\n";
        printDoProjeto(arrayComTodosOsProjetos, vencedorPosicao);
    }
    
    return 0;
}
