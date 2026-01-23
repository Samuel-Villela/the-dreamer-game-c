#include <stdio.h>
void MostrarMenu (int *menu);
int main (void)
{
    int *menu=0;
    MostrarMenu(menu);

    return 0;
}

void MostrarMenu (int *menu)
{
    int menuOpcao=0;
    *menu=1;
    while (*menu == 1)
    {
        printf("Aqui vem o titulo?");
        printf("Escolha uma opcao:");
        printf("1) Cadastrar onibus");
        printf("2) Verificar onibus");
        printf("3) Ajuste manual de entrada/saida");
        printf("4) Sair");

        printf("Escolha sua opcao");
        scanf("%d",&menuOpcao);

        if(menuOpcao == 1){
            //CadastrarOnibus(int *menu, int *a);
        }
        else if(menuOpcao == 2){
            //VerificarOnibus(int *menu, int *a);
        }
        else if(menuOpcao == 3){
            //AjusteManual(int *menu);
        }
        else if(menuOpcao == 4){
            menuOpcao=0;
            *menu=0;
        }
    }
}