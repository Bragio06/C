#include <stdio.h>
#include <stdlib.h>

char **mapa;
int linhas, colunas;
void alocarMapa(){
    mapa = (char **)malloc(linhas * sizeof(char *));
    for (int i = 0; i < linhas; i++){
        mapa[i] = (char *)malloc((colunas + 1) * sizeof(char)); // +1 para o caractere nulo
    }
}

void liberaMapa(){
    for (int i = 0; i < linhas; i++){
        free(mapa[i]);
    }
    free(mapa);
}

void lerMapa(){
    FILE *f = fopen("C:\\Users\\T-GAMER\\OneDrive\\Documentos\\trabalho\\C\\PAC\\mapa.txt", "r");
    if (f == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    fscanf(f, "%d %d", &linhas, &colunas);

    alocarMapa();
    for (int i = 0; i < 5; i++){
        fscanf(f, "%s", mapa[i]);
    }
    fclose(f);
}

int main(){
    lerMapa();
    for (int i = 0; i < 5; i++){

        printf("%s\n", mapa[i]);
    }

    liberaMapa();

    return 0;
}