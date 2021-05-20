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
    int exit=0;
    int option=0;
    while(exit==0)
    {
        int limit;
        limit=count();
        printf("Welcome to Gym Agenda!\nWrite\n1 Log in\n2 Log out\n3 Sign up\n");
        printf("Be careful with your input\n");
        scanf("%d", &option);
        if (option==1)
        {
            int user;
            int Monday;
            int Tuesday;
            int Wednesday;
            int Thursday;
            int Friday;
            int Saturday;
            int Sunday;
            int trainningplan;
        printf("Write your pin\n");
        scanf("%d", &pintemporal);
        if (pintemporal<=0)
        {
            printf("Unknown\n");
        }
        
            else if (pintemporal<=limit)
            {
                
                if (matrix[pintemporal-1][1]==-1)
                { 
                    entradaosalida(pintemporal, 0);
                }
                else
                {
                    printf("You have already log in\n");
              }
            }
            else
            {
                printf("User Unknown, please make sure you have an account with us\n");
          }
        }
        else if (option==2)
        {
            
        printf("Write your username again\n");
        scanf("%d", &pintemporal);
        
        if (pintemporal<=0)
        {
            printf("Invalid process, try again\n");
        }
        
            else if (pintemporal<=limit)
            {
               
                if (matrix[pintemporal-1][1]!=-1)
                {  
                    entradaosalida(pintemporal, 1);
                }
                else
                {
                    printf("You havent registered or log in yet\n");
              }
            }
            else
            {
                printf("Sorry, we didnt find your enter, please make sure you log in first\n");
          }
        }
        else if (option==3)
        {
            Signup();
        }
        
        else
        {
            printf("Unavailable\n\n");
      }
    }
    
    return 0;
}

int count()
{
    FILE* sistem = fopen("system.txt", "r");
    char c;
    int count=0;
    while ((c = fgetc(sistem)) != EOF)
    {
    if (c == '\n') {
      count++; 
     }
    }
    
    return count;
}
void Signup()
{
    int pin;
    pin=count()+1;
    char user[MAX];
    int Monday;
    int Tuesday;
    int Wednesday;
    int Thursday;
    int Friday;
    int Saturday;
    int Sunday;
    int hour;
    int min;
    int trainningplan;
    int membership;
    int Plan1;
    int Plan2;
    int Membership1;
    int Membership2;
    int registers;
    printf("Your pin will be <%d>\n", pin);
    registers++;
    printf("What is your name?\n");
    scanf("%s", user);
    
     do
     {
        printf("\nWrite 0 (Not schedule) y 1 (Schedule) depending on your disponibility of time\nFor example 0 1 0 1 1 0 0\n The calendar starts on Monday to Sunday\n");
        printf("You must write 7 numbers\n");
        printf("Mon Tue Wed Thu Fri Sat Sun\n");
        scanf("%d %d %d %d %d %d %d", &Monday, &Tuesday, &Wednesday, &Thursday, &Friday, &Saturday, &Sunday);
    } while(Monday+Tuesday+Wednesday+Thursday+Friday+Saturday+Sunday==0||Monday!=0&&Monday!=1||Tuesday!=0&&Tuesday!=1||Wednesday!=0&&Wednesday!=1||Thursday!=0&&Thursday!=1||Friday!=0&&Friday!=1||Saturday!=0&&Saturday!=1||Sunday!=0&&Sunday!=1);
    
    do 
    {
        printf("\nWrite below the hour that you feel comfortable with\nUse spaces between hours and minutes\n");
        printf("For example 17 00\n");
        scanf("%d %d", &hour, &min);
    } while(hour<0||hour>23||min<0||min>60);
        
    do 
    {
        printf("\nWe offer you two different trainning plans, choose the best for you!\n");
        printf("\nPlan (1): You are allowed to use the exercise machines for 1 hour and a half\nIt includes weekly checks on your weigth and changes in your routine\n It is part of our $200 pesos membership\n");
        printf("\nPlan (2): You are allowed to use the exercise machines for 2 hour and a half and the help of some of our coaches\nIt includes weekly checks on your weigth and changes in your routine\nIt is part of our $400 pesos membership\n");
        scanf("%d,%d", &Plan1, &Plan2);
    }while(Plan1+Plan2==0||Plan1!=1&&Plan2!=2);
    
    printf("Succesful registration\n\n");
    
    FILE* registeronsystem = fopen("system.txt", "a");
    fprintf(registeronsystem, "%d %s %d %d %d %d %d %d %d %d %d %d\n",pin, user, Monday, Tuesday, Wednesday, Thursday,Friday,Saturday,Sunday, hour, min, trainningplan);
    fclose(registeronsystem);
}
void entradaosalida(int pin, int estado)
{
    int diferencia=0; 
    time_t timenow;
    time(&timenow);
    struct tm *mytime = localtime(&timenow);
    int actualsec=mytime->tm_sec;
    int actualmin=mytime->tm_min;
    int actualhora=mytime->tm_hour;
    int actualyear=mytime->tm_year+1900;
    int actualmes=mytime->tm_mon+1;
    int actualdia=mytime->tm_mday;
    int actualwdia=mytime->tm_wday;
    if (estado==0)
    { 
    FILE* entrada = fopen("login.txt", "a");
    fprintf(entrada, "%d %d %d/%d/%d %d:%d:%d\n", pin, actualwdia, actualdia, actualmes, actualyear, actualhora, actualmin, actualsec);
    fclose(entrada);
    matrix[pin-1][0]=actualhora;
    matrix[pin-1][1]=actualmin;
    matrix[pin-1][2]=actualsec;
    printf("Check in approved\n");
    }
    if (estado==1)
    {
    FILE* salida = fopen("logout.txt", "a"); 
    fprintf(salida, "%d %d %d/%d/%d %d:%d\n", pin, actualwdia, actualdia, actualmes, actualyear, actualhora, actualmin);
    fclose(salida);
    printf("Check out approved\n");
    matrix[pin-1][3]=actualhora;
    matrix[pin-1][4]=actualmin;
    matrix[pin-1][5]=actualsec;
    FILE* reporte = fopen("reporte.txt", "a");
    if (totaldesalidas==0)
    {
     
        fprintf(reporte, "Report made on "); 
            switch(actualwdia)
            {
                case 0:
                fprintf(reporte, "Monday");
                break;
                case 1:
                fprintf(reporte, "Tuesday");
                break;
                case 2:
                fprintf(reporte, "Wednesday");
                break;
                case 3:
                fprintf(reporte, "Thursday");
                break;
                case 4:
                fprintf(reporte, "Friday");
                break;
                case 5:
                fprintf(reporte, "Saturday");
                break;
                case 6:
                fprintf (reporte, "Sunday");
                break;
            }
        fprintf(reporte, " %d/%d/%d\n", actualdia, actualmes, actualyear);
    } 
  }
}

void header()
{
    printf("It can only be %d\n on each hour\n", USERS);
}

void horario()
{
    time_t timenow;
    time(&timenow);
    int pinleido;
    char usuarioleido[MAX];
    int mondayschedule;
    int tuesdayschedule;
    int wednesdayschedule;
    int thursdayschedule;
    int fridayschedule;
    int saturdayschedule;
    int sundayschedule;
    int horaleida;
    int minutoleido;
    int trainningplan;
    int i;
    struct tm *mytime = localtime(&timenow);
    FILE* leersistema = fopen("system.txt", "r");
    FILE* escribirhorario = fopen("horario.txt", "w");
    char c;
    int count;
    while (fscanf(leersistema, "%d %s %d %d %d %d %d %d %d %d %d %d\n", &pinleido, usuarioleido, &mondayschedule, &tuesdayschedule, &wednesdayschedule, &thursdayschedule, &fridayschedule, &saturdayschedule, &sundayschedule, &horaleida, &minutoleido, &trainningplan) == 12)
    {
    fprintf(escribirhorario, "El usuario <%s> con el pin <%d> debe entrar a las: %d:%d debe trabajar durante <%d segundos> los dias:\n", usuarioleido, pinleido,horaleida, minutoleido, trainningplan);
    if (mondayschedule==1)
    fprintf(escribirhorario, "Monday ");
    if (tuesdayschedule==1)
    fprintf(escribirhorario, "Tuesday ");
    if (wednesdayschedule==1)
    fprintf(escribirhorario, "Wednesday ");
    if (thursdayschedule==1)
    fprintf(escribirhorario, "Thursday ");
    if (fridayschedule==1)
    fprintf(escribirhorario, "Friday ");
    if (saturdayschedule==1)
    fprintf(escribirhorario, "Saturday ");
    if (sundayschedule==1)
    fprintf(escribirhorario, "Sunday ");
    
    fprintf(escribirhorario, "\n\n");    
    }
    fclose(leersistema);
    fclose(escribirhorario);
}