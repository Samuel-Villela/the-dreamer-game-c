#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>

#define MAX_SLOTS 5
#define TOP 5
#define TAM 3
#define total_insignias 4
#define ID_Penaltis 0
#define ID_Quiz 1
#define ID_Batalha 2
#define ID_Jogo_velha 3
//#define ID_Sudoku 4


typedef struct JOGADOR_ {
    char nome[21];
    int ultimoMinigame;
    int pontuacao;
    int cont;
    int insignias[total_insignias];
    // Atributos do BattleGame
    int ataque;
    int vida;
    int defesa;
} JOGADOR;

void Minigame_Penaltis(char *nome, int *escolhaMenu, int *pontuacao, JOGADOR *p);
void Minigame_ShowDoMilhao(char *nome, int *escolhaMenu, int *pontuacao, JOGADOR *p);
void Minigame_BattleGame(char *nome, int *escolhaMenu, int *pontuacao, JOGADOR *p);

void imprimirTabuleiro(char tabuleiro[TAM][TAM]);
void fazerJogada(char tabuleiro[TAM][TAM], int linha, int coluna, char jogador);
void jogarContraComputador(char *nome, int *escolhaMenu, int *pontuacao, JOGADOR *p);
void jogarContraOutroJogador(char *nome, int *escolhaMenu, int *pontuacao, JOGADOR *p);


void printfDL(char *texto, int delay_ms);
char lerOpcaoOuEsc(int *escolhaMenu, const char *opcoesValidas); //Funcao de ler opcoes ou esc, usada nos minigames para retornar ao menu
void mostrarMenu(char *nome, int *escolhaMenu, JOGADOR *p);
void salvarJogo(JOGADOR *p);
void carregarJogo(JOGADOR *p);
void atributos(JOGADOR *p);
void mostrarRanking();
void limparTerminal();
int contar_insignias(JOGADOR *p);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int sorteio;
    char *nome = (char *)malloc(21 * sizeof(char));
    int escolhaMenu;
    int pontuacao = 0;
    JOGADOR p;

    limparTerminal();

    printf("Escolha um nome:  ");
    fgets(nome, 21, stdin);
    nome[strcspn(nome, "\n")] = 0;

    memset(&p, 0, sizeof(JOGADOR));         // primeiro zera o struct
    strncpy(p.nome, nome, 20);              // depois copia o nome para o struct
    p.nome[20] = '\0';                      // garante terminação da string

    p.cont = 0;
    atributos(&p); // Atributos Iniciais
    p.pontuacao = 0;

    mostrarMenu(nome, &escolhaMenu, &p);

    if (escolhaMenu == 1) { //Inicio do jogo(so inicia caso o jogador selecione "Iniciar")

        srand(time(NULL));
        p.cont = p.ultimoMinigame; // aqui o contador vai sempre salvar onde o jgdr está
        int InsigniasConquistadas = contar_insignias(&p);

        limparTerminal();

        Sleep(1000);
            printfDL("\nVocê desperta em um mundo distorcido, onde o tempo se dobra e a lógica vacila.\n", 50);
            printfDL("As cores são diferentes, os sons parecem sussurros de memórias esquecidas.\n", 50);
            printfDL("Nada é certo. Nada é seguro. A realidade se fragmenta a cada passo.\n", 50);
            printfDL("Mas entre o caos, uma única verdade se destaca, pulsando como um farol na escuridão:\n", 50);
            printfDL("Para escapar, você precisará conquistar 4 insígnias ocultas, espalhadas nos cantos mais obscuros deste reino onírico...\n\n", 50);
            
            Sleep(1000);

            printfDL("Cada insígnia é guardiã de um desafio.\n", 50);
            printfDL("E a cada desafio superado, uma parte de si será posta à prova, fragmentada e reconstruída:\n", 50);
            printfDL("→ A precisão nos pênaltis, onde um erro custa mais do que um gol perdido...\n", 50);
            printfDL("→ A força em batalha, onde não vence o mais forte, mas o mais determinado...\n", 50);
            printfDL("→ A lógica no tabuleiro, onde a mente é sua única arma...\n", 50);
            printfDL("→ E a clareza no quebra-cabeça, onde até o silêncio pode conter uma pista...\n\n", 50);

            Sleep(1000);

            printfDL("Este não é apenas um jogo.\n", 50);
            printfDL("É uma jornada ao fundo da sua alma, um espelho distorcido de quem você realmente é.\n", 50);
            printfDL("O tempo não está ao seu favor. O mundo muda enquanto você hesita.\n", 50);
            
            Sleep(1000);

            printfDL("Acorde, sonhador...\n", 80);
            printfDL("Encare seus medos, abrace seus instintos, domine seus limites.\n", 80);
            printfDL("Ou permaneça perdido entre pesadelos eternos, onde o amanhã nunca chega...\n\n", 80);

        printf("Insignias conquistadas: %d de 4\n", InsigniasConquistadas);
        Sleep(2000);

        if (p.cont < total_insignias) {
            p.cont = p.ultimoMinigame;
        }

        while (p.cont < total_insignias) {

            sorteio = rand() % total_insignias;
            Sleep(3000);
            if( p.insignias[sorteio]==1){ // caso o jgdr volte ao menu apos um minigame que completou, tira o minigame da lista
                continue;
            }
            if (sorteio == ID_Penaltis) {
                p.ultimoMinigame = ID_Penaltis;
                limparTerminal();
                printfDL("\nDesafio 1 escolhido: Penaltis\n", 80);
                printfDL("Você desperta em um campo silencioso, cercado por névoa.\n", 50);
                printfDL("Um estádio vazio... apenas você e o goleiro encaram-se sob um céu sem estrelas.\n", 50);
                printfDL("A sua coragem será testada com cada chute.\n\n", 50);
                Minigame_Penaltis(nome, &escolhaMenu, &pontuacao, &p);
                p.pontuacao = pontuacao;
                
            } else if (sorteio == ID_Quiz) {
                p.ultimoMinigame = ID_Quiz;
                limparTerminal();
                printfDL("\nDesafio 2 escolhido: Show do Milhão\n", 80);
                printfDL("Você acorda em uma sala iluminada por holofotes, cercado por aplausos inexistentes.\n", 50); 
                printfDL("À sua frente, uma bancada. Uma voz invisível anuncia perguntas que desafiam sua sabedoria.\n", 50);
                printfDL("Somente a Mente afiada conseguirá sair dessa ilusão.\n\n", 50);
                Minigame_ShowDoMilhao(nome, &escolhaMenu, &pontuacao, &p);
                p.pontuacao = pontuacao;
                
            } else if (sorteio == ID_Batalha) {
                limparTerminal();
                p.ultimoMinigame = ID_Batalha;
                printfDL("\nDesafio 3 escolhido: Batalha contra Matemática Discreta\n", 80);
                printfDL("O chão treme enquanto uma criatura emerge da escuridão, olhos fixos em você.\n", 50);
                printfDL("Você empunha sua força interior, mas é a Resiliência que será sua maior arma.\n", 50);
                printfDL("A batalha começa... o medo é real, mas a superação também.\n\n", 50);
                Minigame_BattleGame(nome, &escolhaMenu, &pontuacao, &p);
                p.pontuacao = pontuacao;
                
            } else if (sorteio == ID_Jogo_velha) {
                p.ultimoMinigame = ID_Jogo_velha;
                limparTerminal();
                
                int opcao;
                printfDL("\nDesafio 4 escolhido: Jogo da Velha\n", 80);
                printfDL("Você se vê diante de um tabuleiro flutuante, as peças se movem como se tivessem vontade própria.\n", 50);
                printfDL("Cada jogada altera o ambiente ao seu redor — é um duelo de estratégia e precisão.\n", 50);
                printfDL("A Lógica será sua chave de saída deste quebra-cabeça vivo.\n\n", 50);

                printf("\nEscolha uma opcao:\n");
                printf(" Jogar contra o computador: [1]\n");
                //printf("2. Jogar contra outro jogador\n");
                scanf("%d", &opcao);

                if (opcao == 1) {
                    jogarContraComputador(nome, &escolhaMenu, &pontuacao, &p);
                //} else if (opcao == 2) {
                //    printf("modo Jogador contra outro Jogador invalido no momento, passando por manutençoes");
                //    jogarContraOutroJogador(nome, &escolhaMenu, &pontuacao, &p);
                } else {
                    printf("Opção inválida!\n");
                    return 1;
                }
                p.pontuacao = pontuacao;
            } 
            else if (escolhaMenu == 0) {
                escolhaMenu = 0;
                mostrarMenu(nome , &escolhaMenu, &p);
                break;
            }
            //else if (sorteio == 5) {
            //    limparTerminal();
            //    printfDL("\nJogo 5 escolhido:\n", 50);
            //}
            
        }
        limparTerminal();
        printfDL("Você coletou todas as 4 insígnias!\n", 50);
        printfDL("A luz rompe as trevas do pesadelo...\n", 50);
        printfDL("Você desperta do sonho com um novo olhar sobre si mesmo.\n", 50);
        printfDL("A névoa se dissipa, revelando um caminho iluminado pela coragem, sabedoria, estratégia e força...\n", 50);
        printfDL("Você não é mais o mesmo — superou seus medos e venceu o pesadelo!\n", 50);

        char temp3[101];
        sprintf(temp3,"\nParabéns, %s! Você venceu The Dreamer!\n",nome);
        printfDL(temp3, 50);
        free(nome);

        return 0;
    }
}

void mostrarMenu(char *nome, int *escolhaMenu, JOGADOR *p) {
    *escolhaMenu = 0;
    printf("\nO menu irá começar em 3 segundos...\n");
    Sleep(3000);
    limparTerminal();

    while (*escolhaMenu == 0) 
    {
        printf("  _______ _            _____                                     \n");
        printf(" |__   __| |          |  __ \\                                    \n");
        printf("    | |  | |__   ___  | |  | |_ __ ___  __ _ _ __ ___   ___ _ __ \n");
        printf("    | |  | '_ \\ / _ \\ | |  | | '__/ _ \\/ _` | '_ ` _ \\ / _ \\ '__|\n");
        printf("    | |  | | | |  __/ | |__| | | |  __/ (_| | | | | | |  __/ |   \n");
        printf("    |_|  |_| |_|\\___| |_____/|_|  \\___|\\__,_|_| |_| |_|\\___|_|   \n");
        printf("                                                                 \n");



        printfDL("Bem-vindo ao mundo dos sonhos!\n", 30);
        printfDL("Escolha sua próxima aventura:\n\n", 30);

        printfDL("  1) Iniciar jornada\n", 30);
        printfDL("  2) Salvar jogo\n", 30);
        printfDL("  3) Carregar jogo\n", 30);
        printfDL("  4) Ranks\n", 30);
        printfDL("  5) Trocar nome do personagem\n", 30);
        printfDL("  6) Créditos\n", 30);
        printfDL("  7) Sair do jogo\n\n", 30);

        printf("Digite o numero da opcao desejada:\n");
        scanf(" %d", escolhaMenu);

        if(*escolhaMenu < 0 || *escolhaMenu > 7)
        {
            printf("\nOpcao invalida!\n");
            printf("Digite o número da opção desejada:\n");
            scanf(" %d",escolhaMenu);
            *escolhaMenu=0;
        }
        if (*escolhaMenu == 2) {
            limparTerminal();
            printfDL("Deseja salvar o jogo\n",50);
            printf(" 1) Sim\n");
            printf(" 2) Voltar\n");
            scanf(" %d",escolhaMenu);

            if(*escolhaMenu == 1){
                // salvar jogo
                salvarJogo(p);
            }
            else{
                limparTerminal();
            }
            *escolhaMenu = 0;
        }
        if (*escolhaMenu == 3){
            limparTerminal();
            printfDL("Deseja carregar o jogo\n",50);
            printf(" 1) Sim\n");
            printf(" 2) Voltar\n");
            scanf(" %d",escolhaMenu);

            if(*escolhaMenu == 1){
                // carregar jogo
                carregarJogo(p);
            }
            else{
                limparTerminal();
            }
         *escolhaMenu = 0;
        }
        if (*escolhaMenu == 4){
            limparTerminal();
            mostrarRanking();
            sleep(5);
            *escolhaMenu = 0;
        }
        if (*escolhaMenu == 5) {  // trocar nome
            printf("Digite o novo nome do peronagem: ");
            scanf(" %20s", nome);
            strncpy(p->nome, nome, 20);
            p->nome[20] = '\0';
            *escolhaMenu = 0;
            Sleep(3000);
            limparTerminal();
        }
        if (*escolhaMenu == 6){
            limparTerminal();
            printfDL("Créditos:\n\n",50);
            printf("Samuel da Rocha Villela\n");
            printf("Guilherme de Almeida Ribeiro Daniels\n");
            printf("Maicon Costa Kuchenbecker\n");
            printf("João Pedro de Oliveira Fernandes\n");
            
            *escolhaMenu = 0;
            Sleep(3000);
            limparTerminal();
        }
        
    }
}

char lerOpcaoOuEsc(int *escolhaMenu, const char *opcoesValidas) {
    char tecla;
    while (1) {
        tecla = _getch();

        if (tecla == 27) {
            printfDL("\n[ESC detectado] Voltando ao menu...\n", 30);
            *escolhaMenu = 0;
            return 0;
        }

        tecla = toupper(tecla);
        if (strchr(opcoesValidas, tecla)) {
            return tecla;
        }
    }
}

void limparTerminal() {
    #ifdef _WIN32
        system("cls"); // comando do Windows
    #else
        system("clear"); // comando do Linux/macOS
    #endif
}
//void limparTerminal() {
//    for (int i = 0; i < 50; i++) {
//        printf("\n");
//    }
//}

void atributos(JOGADOR *p)
{
    int atributosIniciais;  // define valores de atributos iniciais e aloca no struct
    srand(time(NULL));

    atributosIniciais = 2 + rand() % 2;
    p->ataque = atributosIniciais;

    atributosIniciais = 2 + rand() % 2;
    p->defesa = atributosIniciais;

    atributosIniciais = 8 + rand() % 3;
    p->vida = atributosIniciais;
}

void salvarJogo(JOGADOR *p)
{
    int slot;
    int algumSaveExiste = 0;
    char filename[30];

    // Verifica se existe ao menos um save
    for (int i = 1; i <= MAX_SLOTS; i++) {
        sprintf(filename, "saveTheDreamer_%d.dat", i);
        FILE *f = fopen(filename, "rb");
        if (f != NULL) {
            fclose(f);
            algumSaveExiste = 1;
            break;
        }
    }

    int decisaoSave = 1;

    if (algumSaveExiste) {
        printf("Já existe pelo menos um arquivo de save. O que voce deseja fazer?\n");
        printf(" 1) Criar novo save\n");
        printf(" 2) Substituir um save existente\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &decisaoSave);
        limparTerminal();

        if (decisaoSave != 1 && decisaoSave != 2) {
            printf("Opcao invalida. Jogo NAO foi salvo.\n");
            return;
        }
    }

    if (decisaoSave == 1) {
        printf("\nEscolha o slot para salvar (1-%d):\n", MAX_SLOTS);
    } else {
        printf("\nEscolha o slot para substituir (1-%d):\n", MAX_SLOTS);
    }

    for (int i = 1; i <= MAX_SLOTS; i++) {
        printf("  %d) Slot %d\n", i, i);
    }

    printf("Escolha: ");
    scanf("%d", &slot);

    if (slot < 1 || slot > MAX_SLOTS) {
        printf("\nSlot invalido. Cancelando salvamento.\n");
        return;
    }

    sprintf(filename, "saveTheDreamer_%d.dat", slot);
    FILE *save = fopen(filename, "wb");
    if (save) {
        fwrite(p, sizeof(JOGADOR), 1, save);
        fclose(save);
        printf("\nJogo salvo com sucesso no slot %d!\n", slot);
    } else {
        printf("\nErro ao salvar o jogo no slot %d.\n", slot);
    }
    Sleep(3000);
    limparTerminal();
}

void carregarJogo(JOGADOR *p)
{
    int slot;
    printf("\nEscolha o slot para carregar (1-%d):\n", MAX_SLOTS);
    for (int i = 1; i <= MAX_SLOTS; i++) {
        printf("  %d) Slot %d\n", i, i);
    }
    printf("Escolha: ");
    scanf("%d", &slot);

    if (slot < 1 || slot > MAX_SLOTS) {
        printf("\nSlot invalido. Cancelando carregamento.\n\n");
        return;
    }

    char filename[30];
    sprintf(filename, "saveTheDreamer_%d.dat", slot);

    FILE *save = fopen(filename, "rb");
    if (save) {
        fread(p, sizeof(JOGADOR), 1, save);
        fclose(save);
        printf("\nJogo carregado com sucesso do slot %d!\n", slot);
        printf("Nome: %s | Pontuacao: %d | Vida: %d | Ataque: %d | Defesa: %d\n",
               p->nome, p->pontuacao, p->vida, p->ataque, p->defesa);
        printf("\n");
    } 
    else {
        printf("\nSlot %d vazio ou erro ao carregar.\n", slot);
    }
    printfDL("Carregamento concluido!",50);
    Sleep(3000);
    limparTerminal();
}

void mostrarRanking() {
    JOGADOR jogadores[MAX_SLOTS];
    int count = 0;
    char filename[30];

    // Lê os arquivos de save existentes
    for (int i = 1; i <= MAX_SLOTS; i++) {
        sprintf(filename, "saveTheDreamer_%d.dat", i);
        FILE *f = fopen(filename, "rb");
        if (f) {
            fread(&jogadores[count], sizeof(JOGADOR), 1, f);
            fclose(f);
            count++;
        }
    }

    if (count == 0) {
        printf("\nNenhum jogo salvo encontrado para exibir o ranking.\n");
        return;
    }

    // Ordenação Bubble Sort (pontuação decrescente)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (jogadores[j].pontuacao < jogadores[j + 1].pontuacao) {
                JOGADOR temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }
    // Exibe o ranking
    printf("\n==== RANKING THE DREAMER ====\n");
    int limite = count < TOP ? count : TOP;
    for (int i = 0; i < limite; i++) {
        printf("%dº lugar: %s - Pontuação: %d\n", i + 1, jogadores[i].nome, jogadores[i].pontuacao);
    }
    printf("=============================\n\n");
    Sleep(3000);
    limparTerminal();
}

void printfDL(char *texto, int delay_ms) {
    while (*texto) {
        printf("%c", *texto);
        fflush(stdout);
        Sleep(delay_ms);
        texto++;
    }
}

void Minigame_Penaltis(char *nome, int *escolhaMenu, int *pontuacao, JOGADOR *p) {
    int ladoGoleiro = 0, i = 0, gols_feitos = 0, gols_desperdicados = 0;
    int passou = 0;
    char Pulo_Goleiro;

    while (passou != 1) {
        printf("\n---- HORA DOS PENALTIS ----\n");
        Sleep(2000);
        for (i = 0; i < 5; i++) {
            Sleep(2000);
            limparTerminal();
            printf("  ----------------------------------------------------- \n"
                   " |O Placar esta %d gols feitos e %d gols desperdicados |\n"
                   "  -----------------------------------------------------\n", gols_feitos, gols_desperdicados);
            printf("                    ____   \n"
                   " o__        o__     |   |\\  \n"
                   "/|          /\\      |   |X\\ \n"
                   "/ > o        <\\     |   |XX\\\n");

            char chute_Player = '\0';
            while (1) {
                printf("\nEscolha um lado para chutar no gol:  \n");
                printf("Lado Esquerdo [E], Lado Direito [D], Meio do Gol [M]:   ");

                chute_Player = lerOpcaoOuEsc(escolhaMenu, "EDM");
                printf("\n\n\n");

                if (chute_Player == 0) {
                    mostrarMenu(nome, escolhaMenu, p);
                    return;
                }

                if (chute_Player == 'E' || chute_Player == 'D' || chute_Player == 'M') {
                    break;
                }

                printf("Opcao invalida. Tente novamente.\n");
            }

            ladoGoleiro = rand() % 3;
            if (ladoGoleiro == 0) Pulo_Goleiro = 'E';
            else if (ladoGoleiro == 1) Pulo_Goleiro = 'D';
            else Pulo_Goleiro = 'M';

            if (Pulo_Goleiro == chute_Player) {
                printf("\nO GOLEIRO AGARROU SEU CHUTE!!!\n");
                gols_desperdicados++;
            } else {
                printf("\nQUE GOLACOOO!!!! %s Converte o Penalti\n", nome);
                *pontuacao += 10;
                gols_feitos++;
            }
        }

        if (gols_feitos >= 3) {
            char temp[101];
            sprintf(temp, "\n%s converteu a maior parte de seus penaltis, esta permitido ir para o proximo Desafio\n", nome);
            printfDL(temp, 50);
            p->insignias[ID_Penaltis] = 1;
            p->cont++;
            passou = 1;
        } else {
            char temp2[101];
            sprintf(temp2, "\n%s nao converteu a maior parte de seus penaltis e FALHOU NO DESAFIO DOS PENALTIS\n", nome);
            printfDL(temp2, 50);
            printfDL("Deseja voltar ao menu ou reiniciar o Desafio?: [1] [2] ", 150);
            int decisao;
            scanf("%d", &decisao);
            if (decisao == 1) {
                mostrarMenu(nome, escolhaMenu, p);
                return;
            }
            if (decisao == 2) {
                Minigame_Penaltis(nome, escolhaMenu, pontuacao, p);
                
                return;
            }
        }
    }

    printfDL("Um brilho surge no ar.\nUm fragmento flutua até sua mão — você recuperou o fragmento da Coragem.\n\n", 50);
    printfDL("Um brilho surge no ar.\nUm fragmento flutua até sua mão — você recuperou o fragmento da Coragem.\n\n", 50);
    printf("    __    \n");
    printf(" .'\".'.\"'. \n");
    printf(":._.\"\"._.:\n");
    printf(":  \\__/  :\n");
    printf(" './  \\.' \n");
    printf("    \"\"    \n");
}

void Minigame_ShowDoMilhao(char *nome, int *escolhaMenu, int *pontuacao, JOGADOR *p)
{
    int i=0, j=0, pontuacaoTemporaria = 0;
    char r;
    char *perguntas[] = {
        "Qual dessas palavras nao tem relacao com sustentacao?\nA) Base B) Alicerce\nC) Fundamento D) Ruina",

        "D. Pedro I do Brasil foi um:\nA) Explorador B) Presidente \nC) Almirante D) Imperador",

        "O po-de-mico quando entra em contato com a pele provoca qual tipo de reacao?\nA) Tristeza B) Frio \nC) Dor D) Cosegas",

        "Qual e o principal orgao do sistema nervoso central?\nA) Coracao B) Estomago\nC) Pulmao D) Cerebro",

        "Qual foi o pais responsavel pela Revolucao Industrial no seculo XVIII?\nA) Franca B) Alemanha\nC) Inglaterra D) Estados Unidos",

        "Quem escreveu Dom Casmurro?\nA) Jose de Alencar B) Machado de Assis\nC) Clarice Lispector D) Graciliano Ramos",

        "Qual e a capital do estado de Pernambuco?\nA) Fortaleza B) Joao Pessoa\nC) Salvador D) Recife",

        "Quantos lados tem um octogono?\nA) 6 B) 7\nC) 8 D) 9",

        "Em que unidade e medida a corrente eletrica?\nA) Volt B) Ohm\nC) Watt D) Ampere",

        "Qual elemento quimico tem o simbolo Na?\nA) Nitrogenio B) Sodio\nC) Niobio D) Niquel",

        "Em que continente fica o pais do Egito?\nA) Asia B) Europa\nC) America D) Africa",

        "O que e fotossintese?\nA) Processo de digestao das plantas B) Processo de perda de folhas\nC) Processo de respiracao vegetal D) Processo de producao de alimento pelas plantas",

        "Que animal e simbolo da sabedoria na mitologia grega?\nA) Leao B) Coruja\nC) Serpente D) Cavalo",

        "Quem pintou o teto da Capela Sistina, no Vaticano?\nA) Leonardo da Vinci B) Rafael\nC) Michelangelo D) Donatello",

        "Qual e o nome da particula responsavel pela forca forte dentro do nucleo atomico?\nA) Eletron B) Gluon\nC) Proton D) Foton",

        "Em que ano aconteceu a Proclamacao da Republica no Brasil?\nA) 1822 B) 1888\nC) 1889 D) 1891",

        "Quem foi o filosofo que afirmou 'So sei que nada sei'?\nA) Platão B) Socrates\nC) Aristoteles D) Epicuro",

        "O que representa a formula E=m(c*c)?\nA) Energia = massa x velocidade B) Energia = carga eletrica ao quadrado\nC) Energia = massa x gravidade D) Energia = massa x velocidade da luz ao quadrado"
    };
    char *respostas[] = {
        "D",
        "D",
        "D",
        "D",
        "C",
        "B",
        "D",
        "C",
        "D",
        "B",
        "D",
        "D",
        "B",
        "C",
        "B",
        "C",
        "B",
        "D"
    };

    int usadas[18] = {0}; int perguntas_respondidasCertas=0, apagar=0;
        for (j = 0; j < 10; j++) {
            do {
                i = rand() % 18;
            } while (usadas[i]==1);

            usadas[i] = 1;

            printf("%s \n", perguntas[i]);
            printf("Escolha uma alternativa (A-D ou ESC para sair): ");
            r = lerOpcaoOuEsc(escolhaMenu, "ABCD");

            if (r == 0) {
                mostrarMenu(nome, escolhaMenu, p);
                return;
            }

            if (r == respostas[i][0]) {
                printfDL("\nCerta resposta!\n\n",50);
                perguntas_respondidasCertas++;
                pontuacaoTemporaria += 10;
                *pontuacao = *pontuacao+10;
            } else {
                printf("\nErrado! Resposta correta e: %c \n\n", respostas[i][0]);
            }
            apagar++;
            if(apagar>=2){
                apagar=0;
                Sleep(2000);
                limparTerminal();
            }
            
        }
    if(perguntas_respondidasCertas>=5){
        printfDL("\nVocê concluiu o Desafio da Sabedoria.\n", 100);
        printfDL("Um fragmento brilha no ar. Você conquistou a Insígnia da Sabedoria!\n\n", 100);
        printf("      ___________      \n");
        printf("     /           \\     \n");
        printf("    /   ________   \\    \n");
        printf("   |   |  ____  |   |   \n");
        printf("   |   | |    | |   |   \n");
        printf("   |   | |____| |   |   \n");
        printf("   |   |________|   |   \n");
        printf("    \\    ||||     /    \n");
        printf("     \\___________/     \n");
        printf("     /|||||||||||\\     \n");
        printf("    / ||||||||||| \\    \n");
        printf("   /__|||||||||||__\\   \n\n");

        p->insignias[ID_Quiz] =1;
        p->cont++;
    }
    else{
        char temp[101];
        sprintf(temp,"\nVocê Não concluiu o Desafio da Sabedoria.\n");
        printfDL(temp,50);
        char temp2[101];
        sprintf(temp2,"\nVocê deseja voltar ao menu ou refazer o Desafio: [1] [2]\n");
        printfDL(temp2,50);
        int decisao;
        scanf("%d",&decisao);
        if(decisao==1){
                mostrarMenu (nome, escolhaMenu, p);
                return;
        }
        else if(decisao ==2){
            Minigame_ShowDoMilhao(nome, escolhaMenu, pontuacao, p);
            return;
        }
    }
    printf("\n%s sua pontuacao foi %d\n", nome, pontuacaoTemporaria);
}

void imprimirTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf(" %c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int jogadaValida(char tabuleiro[TAM][TAM], int linha, int coluna) {
    return (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM && tabuleiro[linha][coluna] == '-');
}

void fazerJogada(char tabuleiro[TAM][TAM], int linha, int coluna, char jogador) {
    tabuleiro[linha][coluna] = jogador;
}

char verificarVencedor(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != '-') {
            return tabuleiro[i][0];
        }
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != '-') {
            return tabuleiro[0][i];
        }
    }
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != '-') {
        return tabuleiro[0][0];
    }
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != '-') {
        return tabuleiro[0][2];
    }
    return '-';
}

int tabuleiroCheio(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == '-') {
                return 0;
            }
        }
    }
    return 1;
}

void jogarContraComputador(char *nome, int *escolhaMenu, int *pontuacao, JOGADOR *p) {
    char tabuleiro[TAM][TAM];
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = '-';
        }
    }

    srand(time(NULL));

    while (1) {
        limparTerminal();
        imprimirTabuleiro(tabuleiro);
        int linha, coluna;

        printf("Pressione qualquer letra para jogar ou ESC para sair: ");
        int r = lerOpcaoOuEsc(escolhaMenu, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        if (r == 0) {
            printf("[ESC detectado] Voltando ao menu...\n");
            mostrarMenu(nome, escolhaMenu, p);
            return;
        
        }
        printf("\n");

        printf("Jogador, digite linha e coluna (0 a 2): ");    
        scanf("%d %d", &linha, &coluna);
        if (!jogadaValida(tabuleiro, linha, coluna)) {
            printf("Jogada inválida! Tente novamente.\n\n");
            continue;
        }
        fazerJogada(tabuleiro, linha, coluna, 'X');

        char vencedor = verificarVencedor(tabuleiro);
        if (vencedor != '-') {
            imprimirTabuleiro(tabuleiro);
            printf("Jogador venceu!\n");
            printfDL("Um fragmento brilha no ar. Você conquistou a Insígnia da resiliencia!\n\n", 100);
            printf("      ___________      \n");
            printf("     /           \\     \n");
            printf("    /   ~~~~~~~~  \\    \n");
            printf("   |   (  () ()  ) |   \n");
            printf("   |   (   ^^^^   ) |  \n");
            printf("    \\   \\_____/  /    \n");
            printf("     \\___________/     \n");
            printf("     /|||||||||||\\     \n");
            printf("    / ||||||||||| \\    \n");
            printf("   /__|||||||||||__\\   \n\n");
            p->cont++;
            p-> insignias[ID_Jogo_velha] =1;
            *pontuacao = *pontuacao+10;
            return;
        }

        if (tabuleiroCheio(tabuleiro)) {
            imprimirTabuleiro(tabuleiro);
            printf("Empate!\n");
            printfDL("Deseja tentar novamente [1] ou voltar ao menu [2]?\n", 50);
            int op;
            scanf("%d", &op);
            if(op == 1){
                jogarContraComputador(nome, escolhaMenu, pontuacao, p);
                return;
            } else {
                mostrarMenu(nome, escolhaMenu, p);
                return;
            }
        }

        printf("Vez do computador:\n");
        do {
            linha = rand() % TAM;
            coluna = rand() % TAM;
        } while (!jogadaValida(tabuleiro, linha, coluna));
        fazerJogada(tabuleiro, linha, coluna, 'O');

        vencedor = verificarVencedor(tabuleiro);
        if (vencedor != '-') {
            imprimirTabuleiro(tabuleiro);
            printf("Computador venceu!\n");
            printfDL("\nO tabuleiro se apaga... A máquina foi mais precisa desta vez.\n", 50);
            printfDL("Você sente o mundo se desfazer ao seu redor. A lógica te derrotou — mas ainda há tempo para tentar novamente.\n", 50);
            printfDL("Deseja tentar novamente [1] ou voltar ao menu [2]?\n", 50);
            int op;
            scanf("%d", &op);
            if(op == 1){
                jogarContraComputador(nome, escolhaMenu, pontuacao, p);
                return;
            } else {
                mostrarMenu(nome, escolhaMenu, p);
                return;
            }
            break;
        }
        
    }
}

void jogarContraOutroJogador(char *nome, int *escolhaMenu, int *pontuacao, JOGADOR *p) {
    char tabuleiro[TAM][TAM];
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = '-';
        }
    }

    char jogadorAtual = 'X';

    while (1) {
        limparTerminal();
        imprimirTabuleiro(tabuleiro);
        int linha, coluna;
        printf("Pressione qualquer letra para jogar ou ESC para sair: ");
        int r = lerOpcaoOuEsc(escolhaMenu, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        if (r == 0) {
            printf("[ESC detectado] Voltando ao menu...\n");
            mostrarMenu(nome, escolhaMenu, p);
            return;
        
        }
        printf("\n");

        printf("Jogador %c, digite linha e coluna (0 a 2): ", jogadorAtual);
        scanf("%d %d", &linha, &coluna);
        if (!jogadaValida(tabuleiro, linha, coluna)) {
            printf("Jogada inválida! Tente novamente.\n\n");
            continue;
        }
        fazerJogada(tabuleiro, linha, coluna, jogadorAtual);

        char vencedor = verificarVencedor(tabuleiro);
        if (vencedor != '-') {
            imprimirTabuleiro(tabuleiro);
            printf("Jogador %c venceu!\n", vencedor);
            *pontuacao = *pontuacao+10;
            break;
        }

        if (tabuleiroCheio(tabuleiro)) {
            imprimirTabuleiro(tabuleiro);
            printf("Empate!\n");
            break;
        }

        jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
    }
}

void Minigame_BattleGame(char *nome, int *escolhaMenu, int *pontuacao, JOGADOR *p)
{
    typedef struct BOSS_
    {
        int vida;
        int ataque;
        int defesa;
    }BOSS;

    BOSS m[10];
    char acao_personagem;
    int fugir=0, ataque_especial_mob=0;
    int i,z; //z e o aleatorio
    int quant_batalhas=0;
    int passou =0;

    srand(time(NULL));

    printfDL("A batalha está preste a começar, se prepare\n",50);
    while (passou!=1) // só faça passou =1 quando termianr todas as batalhas
    {
        i=1;
        m[i].vida=5+quant_batalhas; m[i].ataque=2+quant_batalhas; m[i].defesa=2+quant_batalhas;

        while(p->vida>0 && m[i].vida>0 && fugir==0)  //Batalha entre personagem e mob
        {
            //Menu batalhas
            //printf("imagem da batalha");
            printf(" ______________\n");
            printf("| Atacar = A   |\n");
            printf("| Defender = D |\n");
            printf("| Fugir = F    |\n");
            printf("|______________|\n");

            printf("\nEscolha sua acao: ");

            acao_personagem = lerOpcaoOuEsc(escolhaMenu, "ADF");
        
            if(acao_personagem == 0){
                printf("[ESC detectado] Voltando ao menu...\n");
                mostrarMenu(nome, escolhaMenu, p);
                return;
            } //Parte do personagem
            else if(acao_personagem == 'A'){
                m[i].vida = m[i].vida - p->ataque;
                printfDL("Voce atacou o BOSS\n",50);
            }
            else if(acao_personagem == 'D'){
                p->vida = p->vida - (m[i].ataque - p->defesa);
                printfDL("Voce se defendeu\n",50);
            }
            else if(acao_personagem == 'F'){
                fugir=1;
                printfDL("Seu personagem fugiu\n",50);
            }
            printf("\n");
            //Parte do personagem
            z=1+rand()%3;

            if(ataque_especial_mob==1){  //Ataque especial
                p->vida = p->vida - m[i].ataque;  //Ataque com o buff
                m[i].ataque = m[i].ataque/2;
                ataque_especial_mob=0;
            }
            else if(z==1){ //Ataque
                p->vida = p->vida - m[i].ataque;
                printfDL("O BOSS Matématica Discreta te atacou com a Prova 1\n",50);
            }
            else if(z==2){ //Defesa
                m[i].vida = m[i].vida - (p->ataque - m[1].defesa);
                printfDL("O monstro se defendeu com lógica de enunciados e analise combinatoria\n",50);
            }
            else if(z==3){//Ataque especial
                ataque_especial_mob=1;
                m[i].ataque = m[i].ataque*2;
                printfDL("O BOSS esta carregando um golpe especial!, A Prova Optativa está vindo!!!\n",50);
            }
            printf("Sua vida atual e: %d \n",p->vida);
            printf("A vida atual do MOB e: %d \n\n",m[i].vida);
        }
        if(p->vida <= 0){
            printfDL("Voce perdeu! e observa aos poucos a esperança sucumbir aos seus medos mais profundos\n",50);
            printfDL("Voce deseja tentar denovo?: sim[1] nao[2]  ",50);
            int n;
            scanf("%d",&n);
            if(n==1){
                printfDL("recomeçando o desafio",50);
                p->vida=10;
                Minigame_BattleGame(nome,escolhaMenu,pontuacao,p);
                return;
            }
            if(n==2){
                mostrarMenu(nome, escolhaMenu, p);
                return;            
            }

        }
        else{
            printf("Voce venceu!\n");
            printfDL("Um fragmento brilha no ar. Você conquistou a Insígnia da coragem!\n", 100);
            printf("      _______      \n");
            printf("     /       \\     \n");
            printf("    /  *****   \\    \n");
            printf("   |  * *** *  |   \n");
            printf("   |   *****   |   \n");
            printf("    \\   ***   /    \n");
            printf("     \\_______/     \n");
            printf("     /|||||||\\     \n");
            printf("    / ||||| \\ \\   \n");
            printf("   /__|||||__\\_\\  \n");    
            *pontuacao = *pontuacao+10;
            p-> cont++;
            
            quant_batalhas++;
            p->insignias[ID_Batalha] =1;
            passou =1;
        }
    }
}

int contar_insignias(JOGADOR *p){
    int i=0, total =0;
    for( i=0; i<total_insignias;i++){
        if( p->insignias[i] ==1){
            total++;
        }
    }
    return total;
}