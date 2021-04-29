#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"


node* insert(char* u, char* p, node* pos, int d) 
{
  node* temp;
  if (pos == NULL) 
  {
    pos = (node*)malloc(sizeof(node));
    pos->user = u;
    pos->password = p;
    pos->depth = d;
    printf ("The user has been registered <%s> with the next password <%s>\n\n", u, p);
  } 
  else 
  {
    if (strcmp(pos->user, u) == 0) 
    {
      if (pos->password!=NULL)
      {
      printf("This user is already registered\n\n");
      }
      else
      {
          pos->password = p;
          printf ("The user has been registered <%s> with the next password <%s>\n\n", u, p);
     }
    } 
    else if (strcmp(pos->user, u)>0) 
    {
      temp = insert(u, p, pos->leftchild, d + 1);
      if (pos->leftchild == NULL) 
      {
	pos->leftchild = temp;
     }
    } 
    else if (strcmp(pos->user, u)<0)
    {
      temp = insert(u, p, pos->rightchild, d + 1); 
      if (pos->rightchild == NULL) 
      {
	pos->rightchild = temp;
    }
   }
  }
  return pos;
 }

void alpha(node* position) 
{
  if (position != NULL) 
  {
    alpha(position->leftchild);
    if (position->password!=NULL)
    {
    printf("%s ", position->user);
    }
    alpha(position->rightchild);
 }
}

void delete(node* position, char* u, char* p, int* n)
{
    if (position != NULL) 
    {
        delete (position->leftchild, u, p, n);
        delete (position->rightchild, u, p, n);
        if (strcmp(position->user, u) == 0&&strcmp(position->password, p) == 0){
            position->password=NULL;
            printf("User %s has been removed\n\n", u);
            *n = 1;
  }
 }
}

int main() 
{
  extern char line[];
  node* n = NULL;
  node* tree = NULL; 
  int i;
  int l = 0;
  char* u;
  char* p;
  int indicator=0;
  int spacecounter=0;
  int j;
  printf("Hello!\n\n");
  printf("To add a user please use the next expresion: add (user password)\n\n");
  printf("To remove a user please use the next expresion: del (user password)\n\n");
  printf("To clarify dont use the () in the expresions (user password) those are only to tell that you are going to write the name of the user and then  the password\n\n");
  printf("To see the names of the users arranged alphabetically please use the next expression: view\n\n");
  printf("This program takes into account upper and lower case letters (That means that for example: GABY is not the same as gaby)\n\n");
  printf("Please make sure that your input is correct before accepting the user\n\n");
  while ((l = getout()) == 0) 
  {
      spacecounter=0;
    for (j=0; j<MAX; j++)
    {
        if (line[j]==' '||line[j]=='\t')
        {
            spacecounter++;
     }
    }
    if (strstr(line, "del") != NULL&&strlen(line)>=7&&spacecounter==2) 
    {
      get(line, password, user);
      u = (char*)malloc(sizeof(int*) * strlen(user));
      p = (char*)malloc(sizeof(int*) * strlen(password));
      for (i=0; i<strlen(user);i++)
      {
          u[i]=user[i];
      }
      for (i=0; i<strlen(password);i++)
      {
          p[i]=password[i];
      }
      
      indicator=0;
      delete(tree, u, p, &indicator);
      if (indicator==0)
      {
          printf("The user wasn't removed plese check that the user name and/or the password are correct\n\n");
      }

      indicator=0;
      spacecounter=0;
      }
    
    else if (strstr(line, "add") != NULL&&strlen(line)>=7&&spacecounter==2) 
    {
      get(line, password, user);
      u = (char*)malloc(sizeof(int*) * strlen(user));
      p = (char*)malloc(sizeof(int*) * strlen(password));
      for (i=0; i<strlen(user);i++)
      {
          u[i]=user[i];
      }
      for (i=0; i<strlen(password);i++)
      {
          p[i]=password[i];
      }
      
      if (strlen(password)>0&&strlen(user)>0)
      {
      n = insert(u,p, tree, 0); 
	  if (tree == NULL) 
	  {
	    tree = n;
	    }
	   spacecounter=0;
      }
      else if (strlen(password)<=0||strlen(user)<=0)
      {
          printf ("Please check your input\n\n");
      }
     }
      
    else if (strstr(line, "view") != NULL&&strlen(line)==4) 
    {
      alpha(tree);
      printf("\n\n");
      spacecounter=0;
    }
    else
    {
        printf("Please check your input\n\n");
        spacecounter=0;
    }
  }
  return 0;
 }


int getout() 
{
  extern char line[];
  int c, i = 0;

  for (; i < MAX - 1 && (c = getchar()) != EOF && c != '\n';) 
  {
        line[i++] = c;
  }
  line[i] = '\0';
  return c == EOF;
}

void get (char l[MAX],char p[MAX],char u[MAX])
{
    int a = 4, b = 0, c=0;
    while (l[a]!=' '&&l[a]!='\t')
    {
        u[b]=l[a];
        b++;
        a++;
    }
    u[b]='\0';
    int length = strlen(u);
    a++;
    while (l[a]!=' '&&l[a]!='\t'&&l[a]!='\0')
    {
       p[c]=l[a];
       c++;
       a++;
    }
    p[c]='\0';
    int length2 = strlen(p);
}

