#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "registros.h"

int main()
{
    header();
    int i;
    int j;
    int pintemporal;
    matrix = (int**)malloc(sizeof(int*) * USERS);
    for (i = 0; i < USERS; i ++)
    {
            matrix[i] = (int*)malloc(sizeof(int) * 6);
            for (j=0; j<6; j++)
            {
            matrix[i][j]=-1;
            }
    }
    int salir=0;
    int opcion=0;
    while(salir==0)
    {
        int limite;
        limite=count();
        printf("\nEn este momento hay %d trabajadores registrados\n", limite);
        printf("Se utiliza la funcion scanf, cuide que su entrada sea correcta antes de dar enter\n");
        printf("Bienvenido\nEscribe\n1 Registrar una entrada\n2 Registrar una salida\n3 Registrar un trabajador\n4 Cerrar el programa\n");
        scanf("%d", &opcion);
        if (opcion==1)
        {
            
        printf("Cual es su pin?\n");
        scanf("%d", &pintemporal);
        
        if (pintemporal<=0)
        {
            printf("Entrada no valida\n");
        }
        
            else if (pintemporal<=limite)
            {
                
                if (matrix[pintemporal-1][1]==-1)
                { 
                    entradaosalida(pintemporal, 0);
                }
                else
                {
                    printf("Ya se tiene registrada una entrada de usted\n");
              }
            }
            else
            {
                printf("En este momento hay %d trabajadores no puedes poner ese pin\n", limite);
          }
        }
        else if (opcion==2)
        {
            
        printf("Cual es su pin?\n");
        scanf("%d", &pintemporal);
        
        if (pintemporal<=0)
        {
            printf("Entrada no valida\n");
        }
        
            else if (pintemporal<=limite)
            {
               
                if (matrix[pintemporal-1][1]!=-1)
                {  
                    entradaosalida(pintemporal, 1);
                }
                else
                {
                    printf("Para registrar una salida debio registrarse una entrada\n");
              }
            }
            else
            {
                printf("En este momento hay %d trabajadores no puedes poner ese pin\n", limite);
          }
        }
        else if (opcion==3)
        {
            registrar();
        }
        else if (opcion==4)
        {
            int flag=0;
            for (i=0; i<MAX; i++)
            {
                if(matrix[i][0]*matrix[i][1]*matrix[i][2]>0&&matrix[i][3]*matrix[i][4]*matrix[i][5]<0)
                {
                    flag=-1; 
                    printf("ERROR: El usuario con el pin <%d> registro una entrada pero no una salida\n\n", i+1);
                }
            }
            if (flag==0){
            horario();
            printf("Buend dia!\n");
            salir=1;
          }
        }
        else
        {
            printf("Opcion no disponible\n\n");
      }
    }
    
    return 0;
}

int count()
{
    FILE* sistema = fopen("sistema.txt", "r");
    char c;
    int count=0;
    while ((c = fgetc(sistema)) != EOF)
    {
    if (c == '\n') {
      count++; 
     }
    }
    
    return count;
}
void registrar(){
    int pin;
    pin=count()+1;
    char user[MAX];
    int domingo;
    int lunes;
    int martes;
    int miercoles;
    int jueves;
    int viernes;
    int sabado;
    int hora;
    int min;
    int trabajo;
    printf("El pin de este usuario sera <%d>\n", pin);
    registrados++;
    printf("Cual sera el nombre del usuario?\n");
    scanf("%s", user);
    
     do
     {
        printf("\nEscriba 0 (False) y 1 (True) los dias que el usuario trabajara\nUn ejemplo: 0 0 1 1 1 0 0\nMinimo debe haber un 1\n");
        printf("Debera escribir 7 numeros\n");
        printf("Dom Lun Mar Mie Jue Vie Sab\n");
        scanf("%d %d %d %d %d %d %d", &domingo, &lunes, &martes, &miercoles, &jueves, &viernes, &sabado);
    } while(domingo+lunes+martes+miercoles+jueves+viernes+sabado==0||domingo!=0&&domingo!=1||lunes!=0&&lunes!=1||martes!=0&&martes!=1||miercoles!=0&&miercoles!=1||jueves!=0&&jueves!=1||viernes!=0&&viernes!=1||sabado!=0&&sabado!=1);
    
    do 
    {
        printf("\nEscriba a que hora y minuto trabajara  (con un espacio)\n");
        printf("Un ejemplo: 10 23\n");
        scanf("%d %d", &hora, &min);
    } while(hora<0||hora>23||min<0||min>60);
        
    do 
    {
        printf("\nCuantos segundos trabajara (entre 1 y 60)\n");
        scanf("%d", &trabajo);
    }while(trabajo<=0||trabajo>60);
    printf("Registro exitoso\n\n");
    
    FILE* escribirsistema = fopen("sistema.txt", "a");
    fprintf(escribirsistema, "%d %s %d %d %d %d %d %d %d %d %d %d\n",pin, user, domingo, lunes,martes,miercoles,jueves,viernes,sabado, hora, min, trabajo);
    fclose(escribirsistema);
}
void entradaosalida(int pin, int estado)
{
    int diferencia=0; 
    time_t tiempoahora;
    time(&tiempoahora);
    struct tm *mitiempo = localtime(&tiempoahora);
    int actualsec=mitiempo->tm_sec;
    int actualmin=mitiempo->tm_min;
    int actualhora=mitiempo->tm_hour;
    int actualyear=mitiempo->tm_year+1900;
    int actualmes=mitiempo->tm_mon+1;
    int actualdia=mitiempo->tm_mday;
    int actualwdia=mitiempo->tm_wday;
    if (estado==0)
    { 
    FILE* entrada = fopen("entradas.txt", "a");
    fprintf(entrada, "%d %d %d/%d/%d %d:%d:%d\n", pin, actualwdia, actualdia, actualmes, actualyear, actualhora, actualmin, actualsec);
    fclose(entrada);
    matrix[pin-1][0]=actualhora;
    matrix[pin-1][1]=actualmin;
    matrix[pin-1][2]=actualsec;
    printf("Entrada registrada\n");
    }
    if (estado==1)
    {
    FILE* salida = fopen("salidas.txt", "a"); 
    fprintf(salida, "%d %d %d/%d/%d %d:%d:%d\n", pin, actualwdia, actualdia, actualmes, actualyear, actualhora, actualmin, actualsec);
    fclose(salida);
    printf("Salida registrada\n");
    matrix[pin-1][3]=actualhora;
    matrix[pin-1][4]=actualmin;
    matrix[pin-1][5]=actualsec;
    FILE* reporte = fopen("reporte.txt", "a");
    if (totaldesalidas==0)
    {
     
        fprintf(reporte, "Reporte generado el "); 
            switch(actualwdia)
            {
                case 0:
                fprintf(reporte, "Domingo");
                break;
                case 1:
                fprintf(reporte, "Lunes");
                break;
                case 2:
                fprintf(reporte, "Martes");
                break;
                case 3:
                fprintf(reporte, "Miercoles");
                break;
                case 4:
                fprintf(reporte, "Jueves");
                break;
                case 5:
                fprintf(reporte, "Viernes");
                break;
                case 6:
                fprintf (reporte, "Sabado");
                break;
            }
        fprintf(reporte, " %d/%d/%d\n", actualdia, actualmes, actualyear);
    } 
    
    diferencia=(matrix[pin-1][3]*3600+matrix[pin-1][4]*60+matrix[pin-1][5])-(matrix[pin-1][0]*3600+matrix[pin-1][1]*60+matrix[pin-1][2]);
    int horapin=matrix[pin-1][0];
    int minpin=matrix[pin-1][1];
    int segundopin=matrix[pin-1][2];                                                                             
    fprintf(reporte, "El trabajador con el pin <%d> entro a la hora: <%d:%d:%d> el dia: <%d/%d/%d> trabajo %d segundos\n", pin, horapin, minpin, segundopin, actualdia, actualmes, actualyear, diferencia);
    fclose(reporte);
    matrix[pin-1][0]=-1;
    matrix[pin-1][1]=-1;
    matrix[pin-1][2]=-1;
    matrix[pin-1][3]=-1;
    matrix[pin-1][4]=-1;
    matrix[pin-1][5]=-1;
    
    totaldesalidas=9; 
  }
}

void header()
{
    time_t tiempoahora;
    time(&tiempoahora);
    struct tm *mitiempo = localtime(&tiempoahora);
    switch(mitiempo->tm_wday)
    {
        case 0:
        printf("Hoy es Domingo\n");
        break;
        case 1:
        printf("Hoy es Lunes\n");
        break;
        case 2:
        printf("Hoy es Martes\n");
        break;
        case 3:
        printf("Hoy es Miercoles\n");
        break;
        case 4:
        printf("Hoy es Jueves\n");
        break;
        case 5:
        printf("Hoy es Viernes\n");
        break;
        case 6:
        printf ("Hoy es Sabado\n");
        break;
    }
    printf("Dia: %d/%d/%d\n", mitiempo->tm_mday, mitiempo->tm_mon+1, mitiempo->tm_year+1900); 
    printf("Hora: %d:%d\n", mitiempo->tm_hour, mitiempo->tm_min);
    printf("El numero maximo de usuarios que pueden estar en el sistema son %d\n", USERS);
}

void horario()
{
    time_t tiempoahora;
    time(&tiempoahora);
    int pinleido;
    char usuarioleido[MAX];
    int domingohorario;
    int luneshorario;
    int marteshorario;
    int miercoleshorario;
    int jueveshorario;
    int vierneshorario;
    int sabadohorario;
    int horaleida;
    int minutoleido;
    int trabajo;
    int i;
    struct tm *mitiempo = localtime(&tiempoahora);
    FILE* leersistema = fopen("sistema.txt", "r");
    FILE* escribirhorario = fopen("horario.txt", "w");
    char c;
    int count;
    while (fscanf(leersistema, "%d %s %d %d %d %d %d %d %d %d %d %d\n", &pinleido, usuarioleido, &domingohorario, &luneshorario, &marteshorario, &miercoleshorario, &jueveshorario, &vierneshorario, &sabadohorario, &horaleida, &minutoleido, &trabajo) == 12)
    {
    fprintf(escribirhorario, "El usuario <%s> con el pin <%d> debe entrar a las: %d:%d debe trabajar durante <%d segundos> los dias:\n", usuarioleido, pinleido,horaleida, minutoleido, trabajo);
    if (domingohorario==1)
    fprintf(escribirhorario, "domingo ");
    if (luneshorario==1)
    fprintf(escribirhorario, "lunes ");
    if (marteshorario==1)
    fprintf(escribirhorario, "martes ");
    if (miercoleshorario==1)
    fprintf(escribirhorario, "miercoles ");
    if (jueveshorario==1)
    fprintf(escribirhorario, "jueves ");
    if (vierneshorario==1)
    fprintf(escribirhorario, "viernes ");
    if (sabadohorario==1)
    fprintf(escribirhorario, "sabado ");
    
    fprintf(escribirhorario, "\n\n");    
    }
    fclose(leersistema);
    fclose(escribirhorario);
}