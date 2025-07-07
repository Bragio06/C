void liberaMapa();
void lerMapa();
void alocarMapa();
void move(char direcao);
int acabou();
void inprimirMapa();
struct mapa{
    char **mapa;
    int linhas, colunas;
};
typedef struct mapa MAPA;


