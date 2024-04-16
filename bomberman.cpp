/**
    Estrutura inicial para um jogo
    versão: 0.1 (Prof. Alex,  Adaptado Prof. Felski)
*/
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

struct inimigo
{
    int x, xAnterior;
    int y, yAnterior;
    int matriz = 4;

    void direcao(int direcao) {
        switch (direcao) {
        case 1:
            x++;
            break;
        case 2:
            x--;
            break;
        case 3:
            y++;
            break;
        case 4:
            y--;
            break;
        }
    }
};

struct Bomba
{
    int x;
    int y;
    time_t tempoBomba, tempoBombaMapa;
};

void printMenu() {
    system("cls");
    cout << "__              _.                                       " << endl;
    cout << "\\_   \\ _   _\\ |   __  _ _    __  " << endl;
    cout << " |    |  //  _ \\ /     \\| _ \\/ _ \\_  _ \\/     \\\\_  \\  /    \\ " << endl;
    cout << " |    |   (  <> )  Y Y  \\ \\\\ \\  /|  | \\/  Y Y  \\/ _ \\|   |  \\" << endl;
    cout << " |_  /\\/|||  /_  /\\_  >|  |||  (_  /_|  /" << endl;
    cout << "        \\/             \\/    \\/     \\/            \\/     \\/     \\/ " << endl;
    cout << "1. Iniciar jogo" << endl;
    cout << "2. Sair" << endl;
    cout << "Escolha uma opcao: ";
}

void duplaAtribuicao(int &x, int &y, int xAterior, int yAnterior){
    x = xAterior;
    y = yAnterior;
}


void gameOverMenu() {
    cout << "\nVoce perdeu!" << endl;
    cout << "Deseja continuar?" << endl;
    cout << "1. Sim" << endl;
    cout << "2. Nao" << endl;
    cout << "Escolha uma opcao: ";
}

int main()
{
    char choice;
    do {
        printMenu();
        cin >> choice;



        if (choice == '1') {
            system("cls");
            ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, A SEGUIR.
            //INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO     cursorInfo;
            GetConsoleCursorInfo(out, &cursorInfo);
            cursorInfo.bVisible = false; // set the cursor visibility
            SetConsoleCursorInfo(out, &cursorInfo);
            //FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
            //INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
            short int CX=0, CY=0;
            COORD coord;
            coord.X = CX;
            coord.Y = CY;
            //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
            ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.

            //MAPA
            int m[17][17]={  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,1,
                1,0,1,0,0,2,1,2,1,2,1,2,1,2,1,0,1,
                1,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,1,
                1,2,1,0,0,0,1,2,1,0,1,2,1,0,1,2,1,
                1,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,1,
                1,2,1,2,1,2,1,0,1,2,1,2,1,2,1,2,1,
                1,0,2,0,0,0,2,0,0,0,0,0,2,0,0,0,1,
                1,0,1,2,1,2,1,2,1,2,1,2,1,2,1,0,1,
                1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,1,
                1,2,1,0,1,2,1,2,1,2,1,0,0,0,0,2,1,
                1,0,2,0,2,0,0,0,0,0,2,0,2,0,2,0,1,
                1,0,1,2,1,2,1,2,1,2,1,2,1,2,0,0,1,
                1,0,0,0,2,0,0,0,2,0,0,0,2,0,0,0,1,
                1,0,0,2,1,0,1,2,1,0,1,2,1,0,0,0,1,
                1,0,0,0,0,0,2,0,0,0,2,0,0,0,2,0,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
            };
            //relação matriz parede = 1, paredeQuebravel = 2, bomba = 3, inimigo = 4, bomberman = 5;

            //Posicao inicial do personagem no console
            int x=1, y=1;

            //Posição inimigos
            inimigo inimigo1, inimigo2, inimigo3;
            inimigo1.x = 1;
            inimigo1.y = 15;
            inimigo2.x = 15;
            inimigo2.y = 1;
            inimigo3.x = 15;
            inimigo3.y = 15;
            vector <inimigo> inimigos{inimigo1, inimigo2, inimigo3};

            inimigos[0].xAnterior = inimigo1.x;
            inimigos[0].yAnterior = inimigo1.y;
            inimigos[1].xAnterior = inimigo2.x;
            inimigos[1].yAnterior = inimigo2.y;
            inimigos[2].xAnterior = inimigo3.x;
            inimigos[2].yAnterior = inimigo3.y;

            //Variavel para tecla precionada
            char tecla;
            //declaração de variaveis
            int XAnterior = x, YAnterior = y;
            bool rastroBombaB = false, bombaMapa = false, bombaExplodiu = true;
            bool norte =false, sul = false, leste = false, oeste = false;
            bool movimentoInimigos =true;
            bool jogando = true;
            time_t  rastroBomba,tempoInimigo, movInimigo;

            Bomba bomba;

            while(jogando){
                ///Posiciona a escrita no iicio do console
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);


                ///Imprime o jogo: mapa e personagem.
                for(int i=0;i<17;i++){
                    for(int j=0;j<17;j++){

                        //condicional para movimento dos inimigos
                        if(movimentoInimigos){
                            tempoInimigo = clock();
                            movimentoInimigos = false;
                        }

                        //verifica passos do player e tira eles da matriz
                        if(i==x && j==y){
                            if(m[XAnterior][YAnterior] == 5){
                                m[XAnterior][YAnterior] = 0;
                            }
                            if (bombaMapa){
                                m[i][j] = 3;
                                bomba.x = i;
                                bomba.y = j;
                                bombaMapa = false;
                                bombaExplodiu = false;
                                norte =true; sul = true;leste = true; oeste = true;
                            }
                            bomba.tempoBombaMapa = clock() - bomba.tempoBomba;
                            if((int)bomba.tempoBombaMapa/CLOCKS_PER_SEC == 3){
                                //condicional para explodir a bomba
                                bombaExplodiu = true;
                                int explosaoX, explosaoY;

                                explosaoY = bomba.y;
                                while(sul) {
                                    if(m[bomba.x][explosaoY] == 1){
                                        sul = false;
                                        break;
                                    }if(m[bomba.x][explosaoY] == 2){
                                        m[bomba.x][explosaoY] = 0;
                                        sul = false;
                                        break;
                                    }
                                    m[bomba.x][explosaoY] = 6;
                                    explosaoY --;
                                }
                                explosaoY = bomba.y;
                                while(norte) {
                                    if(m[bomba.x][explosaoY] == 1){
                                        norte = false;
                                        break;
                                    }if(m[bomba.x][explosaoY] == 2){
                                        m[bomba.x][explosaoY] = 0;
                                        norte = false;
                                        break;
                                    }
                                    m[bomba.x][explosaoY] = 6;
                                    explosaoY ++;
                                }
                                explosaoX = bomba.x;
                                while(leste) {
                                    if(m[explosaoX][bomba.y] == 1){
                                        leste = false;
                                        break;
                                    }if(m[explosaoX][bomba.y] == 2){
                                        m[explosaoX][bomba.y] = 0;
                                        leste = false;
                                        break;
                                    }
                                    m[explosaoX][bomba.y] = 6;
                                    explosaoX --;
                                }
                                explosaoX = bomba.x;
                                while(oeste) {
                                    if(m[explosaoX][bomba.y] == 1){
                                        oeste = false;
                                        break;
                                    }if(m[explosaoX][bomba.y] == 2){
                                        m[explosaoX][bomba.y] = 0;
                                        oeste = false;
                                        break;
                                    }
                                    m[explosaoX][bomba.y] = 6;
                                    explosaoX ++;
                                }

                                rastroBomba = clock();
                                rastroBombaB = true;
                            }
                            rastroBomba = clock() - rastroBomba;
                            //condicional para apagar rastro da bomba
                            if(rastroBombaB){
                                if((int)rastroBomba/CLOCKS_PER_SEC > 0){
                                    for (int ij = 0; ij < 17; ++ij) {
                                        for (int ji = 0; ji < 17; ++ji) {
                                            if(m[ij][ji] == 6){
                                                m[ij][ji] = 0;
                                            }
                                            if(m[ij][ji] == 6){
                                                m[ij][ji] = 0;
                                            }
                                        }
                                    }
                                    rastroBombaB = false;
                                }
                            }
                            //switch de decição do personagem, para verificar se pode ou não andar
                            switch (m[i][j]){
                            case 0:
                                //espaço livre
                                cout<<char(36);
                                m[i][j] = 5;
                                duplaAtribuicao(XAnterior,YAnterior, x, y);
                                break;//personagem break; //caminho
                            case 1:
                            case 2:
                            case 3 :
                                //espaço preenchido, bloqueando player
                                duplaAtribuicao(i , j ,XAnterior, YAnterior );
                                duplaAtribuicao(x , y ,XAnterior, YAnterior );
                                break;
                            case 4:
                                //morte do player
                                system("cls");
                                jogando = false;
                                break;
                            case 6:
                                system("cls");
                                jogando = false;

                                break;
                            }
                        } else{
                            //switch para o print do mapa corretamente
                            switch (m[i][j]){
                            case 0: cout<<" "; break; //caminho
                            case 1: cout<<char(219); break; //parede
                            case 2: cout<<char(221); break; //parede quebrada
                            case 3: cout<<char(184);break;
                            case 4: cout<<char(168); break;
                            case 6: cout<<'x';break;
                                //default: cout<<"-"; //erro
                            } //fim switch
                        }

                        movInimigo = clock() - tempoInimigo;
                        if((int)movInimigo/CLOCKS_PER_SEC == 1){
                            //condicinal para movimentar os inimigos de 1 em 1 segundo
                            movimentoInimigos = true;
                            if(inimigos.empty()){
                                //condição de vitoria - matar todos inimigos
                                system("cls");
                                cout<<"Parabens VC Ganho";
                                return 0;
                            }

                            for(int k = 0; k < inimigos.size(); k++){

                                //random para movimentação
                                int direcao = rand() % 4 + 1;
                                int quantMov = rand() % 3 + 1;

                                for (int movs = 0; movs < quantMov; ++movs) {
                                    //laço baseado na quantidade de moviemntos
                                    m[inimigos[k].x][inimigos[k].y] = 4;
                                    inimigos[k].direcao(direcao);

                                    switch (m[inimigos[k].x][inimigos[k].y]){
                                        //switch verificando se o inimigo pode se movimentar ou não
                                    case 0:
                                        m[inimigos[k].x][inimigos[k].y] = 4;
                                        if(m[inimigos[k].xAnterior][inimigos[k].yAnterior] == 4){
                                            m[inimigos[k].xAnterior][inimigos[k].yAnterior] = 0;
                                        }
                                        duplaAtribuicao(inimigos[k].xAnterior ,  inimigos[k].yAnterior ,inimigos[k].x, inimigos[k].y );
                                        break;
                                    case 1:
                                    case 2:
                                    case 3 :
                                        duplaAtribuicao(inimigos[k].x, inimigos[k].y, inimigos[k].xAnterior ,  inimigos[k].yAnterior );
                                        break;
                                    }

                                }
                                continue;

                            }
                        }

                        for (int k = 0; k < inimigos.size(); k++) {
                            //laço baseado no vector de inimigos, para verificar se foram mortos
                            if(m[inimigos[k].x][inimigos[k].y] == 6){
                                inimigos.erase(inimigos.begin() + k);
                            }
                        }

                    }
                    cout<<"\n";
                } //fim for mapa


                ///executa os movimentos
                if ( _kbhit() ){
                    tecla = getch();
                    switch(tecla)
                    {
                    case 72: case 'w': ///cima
                        x--;
                        break;
                    case 80: case 's': ///baixo
                        x++;
                        break;
                    case 75:case 'a': ///esquerda
                        y--;
                        break;
                    case 77: case 'd': ///direita
                        y++;
                        break;
                    case 76: case 'b':
                        if (!bombaMapa && bombaExplodiu){
                            bombaMapa = true;
                            bomba.tempoBomba = clock();
                        }
                        break;
                    }
                }



            cout<<"inimigos vivos "<< inimigos.size()<<endl;
            } //fim do laco do jogo
            system("cls");
            char continueChoice;
            do {
                // game over
                gameOverMenu();
                cin >> continueChoice;
            } while (continueChoice != '1' && continueChoice != '2');

            if (continueChoice == '1') {
                continue; // Reinicie o jogo
            } else {
                break; // Sai do loop e termina o programa
            }
        } else if (choice == '2') {
            break; // Sai do loop e termina o programa
        } else {
            cout << "Opcao invalida. Tente novamente." << endl;
        }
    } while (true);

    cout << "Obrigado por jogar Bomberman!" << endl;

    return 0;
}
