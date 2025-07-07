#include <stdio.h>
#include <stdlib.h>
#include "pac.h"

MAPA m;

void alocarMapa()
{
    m.mapa = (char **)malloc(m.linhas * sizeof(char *));
    for (int i = 0; i < m.linhas; i++)
    {
        m.mapa[i] = (char *)malloc((m.colunas + 1) * sizeof(char)); // +1 para o caractere nulo
    }
}

void liberaMapa()
{
    for (int i = 0; i < m.linhas; i++)
    {
        free(m.mapa[i]);
    }
    free(m.mapa);
}

void lerMapa()
{
    FILE *f = fopen("C:\\Users\\hbrag\\OneDrive\\Documentos\\GitHub\\C\\PAC\\mapa.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    fscanf(f, "%d %d", &m.linhas, &m.colunas);

    alocarMapa();
    for (int i = 0; i < 5; i++)
    {
        fscanf(f, "%s", m.mapa[i]);
    }
    fclose(f);
}
void inprimirMapa()
{
    for (int i = 0; i < 5; i++)
    {

        printf("%s\n", m.mapa[i]);
    }
}
int acabou()
{
    return 0;
}
void move(char direcao)
{
    int x;
    int y;

    for (int i = 0; i < m.linhas; i++)
    {
        for (int j = 0; j < m.colunas; j++)
        {
            if (m.mapa[i][j] == '@')
            {
                x = i;
                y = j;
                break;
            }
        }
    }
    switch (direcao)
    {
    case 'a':
        m.mapa[x][y - 1] = '@';
        break;
    case 'w':
        m.mapa[x - 1][y] = '@';
        break;
    case 'd':
        m.mapa[x][y + 1] = '@';
        break;
    case 's':
        m.mapa[x + 1][y] = '@';
        break;
    }
    m.mapa[x][y] = '.';
}
int main()
{
    lerMapa();
    do
    {
        inprimirMapa();
        char comondo;
        scanf(" %c", &comondo);
        move(comondo);
    } while (!acabou());

    liberaMapa();

    return 0;
}