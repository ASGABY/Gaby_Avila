#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define FILAS    5
#define COLUMNAS 5 



void show(int OUT [FILAS][COLUMNAS],int u[FILAS][COLUMNAS])                   
{
    int i, j;

    printf("     1 2 3 4 5 \n");                  
    printf("    - - ---------\n");
    for (i = 0; i<FILAS; i++)                                  
    {                                                       
        for (j = 0; j<COLUMNAS; j++)
        {
            if (j == 0)printf("%2d║ ", i+1);
            if (u[i][j] == 0)printf("  ░");
            else if (u[i][j] == 1)
            {
                if (OUT[i][j] == 0)printf("□");
                else printf("%2d", OUT [i][j]);
            }
            else if (u[i][j] == -1) 
            {
                printf("◇");
            }
        }
        printf("\n");
    }
}

int find(int OUT [FILAS][COLUMNAS], int i, int j)                    
{
    int l, c,lmin,cmin, lmax, cmax, num = 0;
    l = lmin = (i - 1) >= 0 ? (i - 1) : 0;                  
    c = cmin = (j - 1) >= 0 ? (j - 1) : 0;
    lmax = ((i + 1) < FILAS ? (i + 1) : 4);                    
    cmax = ((j + 1) < COLUMNAS ? (j + 1) : 4);

    for (l = lmin; l <= lmax; l++)
    {
        for (c = cmin; c <= cmax; c++)
        {
            if (l == i&&c == j)continue;                    
            if (OUT[l][c] == -1)num++;                      
        }
    }
    return num;
}

void init(int OUT[FILAS][COLUMNAS])                                  
{
    int n = 5, l, c, i, j;
    srand(time(NULL));                                      
    for (i = 0; i< 5; i++)
    {
        for (j = 0; j< 5; j++)
        {
            OUT[i][j] = 0;                                  
        }
    }
    while (n--)                                             
    {
        l = rand() % 5;
        c = rand() % 5;
        if (OUT[l][c] != -1)OUT[l][c] = -1;                 
        else n++;
    }
    for (i = 0; i< 5; i++)
    {
        for (j = 0; j< 5; j++)
        {
            if (OUT[i][j] != -1)
            {
                OUT[i][j] = find(OUT, i, j);                
            }
        }
    }
}

void open(int OUT[FILAS][COLUMNAS],int u[FILAS][COLUMNAS], int i, int j)      
{
    u[i][j] = 1;
    if (OUT[i][j] == 0)
    {
        if(i - 1 >= 0 && u[i - 1][j] != 1)open(OUT, u, i - 1, j);  
        if(j - 1 >= 0 && u[i][j - 1] != 1)open(OUT, u, i, j - 1);   
        if (i + 1 <= 4 && u[i + 1][j] != 1)open(OUT, u, i + 1, j);  
        if (j + 1 <= 4&& u[i][j + 1] != 1)open(OUT, u, i, j + 1);  
    }
}

int judge(int u[FILAS][COLUMNAS])                        
{
    int i, j, num = 0;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (u[i][j] == 0 || u[i][j] == -1)num++;
        }
    }
    if (num == 5)return 1;
    else return 0;
}

void fail(int OUT[FILAS][COLUMNAS], int u[FILAS][COLUMNAS])       
{
    int i, j;
    for (i = 0; i < 5; i++)                    
    {
        for (j = 0; j < 5; j++)
        {
            if (OUT[i][j] == 0)printf("  ");
            else if (OUT[i][j] != -1)printf("%2d", OUT[i][j]); 
            else printf("●");
        }
        printf("\n");
    }
    printf("try again\ n");
}

void menu(int OUT[FILAS][COLUMNAS],int u[FILAS][COLUMNAS])            
{
    int x,i,j;
    int boom = 5;                                  
    int num = 0;                                    
    while (1)                                   
    {
        system("cls");
        show(OUT,u);
        printf("Theres% more bombs \ n",boom);
        printf("1. scan 2. pick 3. unpick \ n");
        printf("Take an an option opciones:>");
        scanf("%d", &x);
        if (x > 3 || x < 1) {
            printf("error! \ N");
            system("pause");
            continue;
        }
        printf("Place:>");
        scanf("%d %d", &i, &j);
        if (i < 1 || i>5)
        {
            printf("error! \ N");
            system("pause");
            continue;
        }
        i--;            
        j--;
        if (x == 1)
        {
            if (OUT[i][j] == -1) {
                if (num == 0) {     
                    init(OUT);
                    show(OUT, u);
                    open(OUT, u, i, j);
                    num++;
                    continue;
                }
                else
                {
                    fail(OUT, u);   
                    break;
                }
            }
            if (u[i][j] == 1)       
            {
                printf("error! \ N");
                system("pause");
                continue;
            }
            open(OUT, u, i, j);
            num++;
        }
        else if(x == 2)
        {
            if (u[i][j] == 1) {
                printf("error! \ N"); 
                system("pause");
                continue;
            }
            u[i][j] = -1;
            boom --;            
        }
        else if (x == 3)
        {
            if (u[i][j] != -1) {
                printf("error! \ N");   
                system("pause");
                continue;
            }
            u[i][j] = 0;
            boom++;
        }
    }
}

int main()
{
    int OUT[FILAS][COLUMNAS] = { 0 };        
    int u[FILAS][COLUMNAS] = { 0 };         
    init(OUT);                      
    menu(OUT, u);                
    return 0;
}
