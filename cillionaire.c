#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <strings.h>

/* define para usar strings mais facilmente */
 
#define MSG_WELL "*** Hooray!"
#define MSG_WIN "*** This is incredible! You have won!"
#define MSG_OVER "*** Sorry, you have lost the game. Bye!"
#define MSG_SAVE "*** Ok, your progress has been saved. See you later!"
#define MSG_ERROR "*** Illegal move"
#define MSG_BYE "*** Sad to see you go..."
#define MSG_UNKNOWN "*** Unknown option."
#define MSG_WRONG "***Woops... That's not correct."

struct game{
char questions[256];
char answers[4][128];
char category[128];
char difficulty[20];
};

void remove_element(struct game *array, int index, int array_length)
{
   int i;
   for(i = index; i < array_length - 1; i++) 
   {
    array[i] = array[i + 1];
   }
}

int level(int patamar)
{
  if (patamar == 0)
  {
    return 0;
  }
  else if (patamar == 1)
  {
    return 500;
  }
  else if (patamar ==2)
  {
    return 1000;
  }
  else if (patamar ==3)
  {
    return 2000;
  }
  else if (patamar ==4)
  {
    return 5000;
  }
  else if (patamar ==5)
  {
    return 10000;
  }
  else if (patamar ==6)
  {
    return 20000;
  }
  else if (patamar ==7)
  {
    return 50000;
  }  
  else if (patamar ==8)
  {
    return 1000000;
  }
  return 0;
}

/* JOGO */

int games(char * pficheiro,int patamar, int * i,  struct game *Game, char * A, char *B, char *C, char *D, int progress)
{
  char aux[256];
  
  if(progress==0)
  {
    FILE * fq = fopen(pficheiro,"r" );

    for (int k = 0; k < 500; k++)
    {
      if (fgets(aux, 256, fq) != NULL) 
      {
        strcpy(Game[k].questions, aux);
        fgets(aux, 128, fq);
        strcpy(Game[k].answers[0], aux);
        fgets(aux, 128, fq);
        strcpy(Game[k].answers[1], aux);
        fgets(aux, 128, fq);
        strcpy(Game[k].answers[2], aux);
        fgets(aux, 128, fq);
        strcpy(Game[k].answers[3], aux);
        fgets(aux, 128, fq);
        strcpy(Game[k].category, aux);
        fgets(aux, 256, fq);
        strcpy(Game[k].difficulty, aux);
      } 
    }
    fclose(fq);
  }
    
  srand(time(NULL));
  int num_rand = rand() % 501;
  int rand_ans = rand() % 4;
  while ((strncmp(Game[num_rand].difficulty, "hard",9) ==0 && patamar < 5 ) || (strncmp(Game[num_rand].difficulty, "medium",9) ==0 && (patamar > 5 || patamar<2)) || (strncmp(Game[num_rand].difficulty, "easy",9) ==0 && patamar >2 ))
  {
    num_rand = rand() % 501;
    rand_ans = rand() % 4; 
  }

  
  strcpy(A, Game[num_rand].answers[rand_ans]);
  strcpy(B, Game[num_rand].answers[(1 + rand_ans) % 4]);
  strcpy(C, Game[num_rand].answers[(2 + rand_ans) % 4]);
  strcpy(D, Game[num_rand].answers[(3 + rand_ans) % 4]);

  int k = 1;
  while (k != 0)
  {
    k = (*i + rand_ans) % 4;
    *i+=1;
  }
  *i -= 1;

  printf("Question: %s", Game[num_rand].questions);
  printf("A: %s",A);
  printf("B: %s",B);
  printf("C: %s",C);
  printf("D: %s",D);

  return num_rand;
}

int resposta(char escolha, int *i, char * A, char *B, char *C, char *D, int * patamar)
{
  int absol = abs('A'- escolha);
  if (*i == absol)
  {
    puts(MSG_WELL);
    *patamar += 1;
    return -1;
  }
  else
  {
    puts(MSG_WRONG);
    if (*patamar != 0)
    {
      *patamar -= 1;
    }
    if (*i == 0)
    {
      printf("The correct answer was A: %s", A);
    }
    if (*i == 1)
    {
      printf("The correct answer was B: %s", B);
    }
    if (*i == 2)
    {
      printf("The correct answer was C: %s", C);
    }
    if (*i == 3)
    {
      printf("The correct answer was D: %s", D);
    }
    return 1;
  }
}

/* função que apresenta os status do player */

void print_status(const int nivel, const char * j50, const char * j25, const char * name)
{
    puts("********************************************");
    printf("*** Name:  %s               *\n", name);
    printf("*** Level:  %d                   *\n", nivel);
    printf("*** j50: %s                    *\n", j50);
    printf("*** j25:  %s                   *\n", j25);
    puts("********************************************");
}
 
/* função para dar print no menu */
 
void print_menu(void)
{
    puts("********************************************");
    puts("***            CILLIONAIRE                 *");
    puts("********************************************");
    puts("*** n <name>     - new game                *");
    puts("*** q            - quit                    *");
    puts("*** h            - show this menu          *");
    puts("*** r <filename> - resume game             *");
    puts("*** s <filename> - save progress and quit  *");
    puts("*** j 50         - play 50:50 joker        *");
    puts("*** j 25         - play 25:75 joker        *");
    puts("*** c            - show credits            *");
    puts("********************************************");
}

int main(int argc, char * argv[])
{
  
  print_menu();
  
  /*dar check no argc e argv*/
  char ficheiro[20]; 
  if(argc == 1)
  {
      srand(time(0));
  }
  else if(argc == 3)
  {
      if (strcmp(argv[1], "-s") == 0)
      {
        srand(atoi(argv[2]));
      }
      else
      {
        printf("Illegal move\n");
        return 0;
      }
  }
  else if (argc == 5)
  {
    if (strcmp(argv[1], "-f") == 0)
    {
      strcpy(ficheiro,argv[2]);
      if (strcmp(argv[3], "-s") == 0)
      {
        srand(atoi(argv[4]));
      }
    }
    
  }
  char * pficheiro;
  pficheiro = &ficheiro[0];

  struct game *Game;
  Game = (struct game*) calloc(500, sizeof(struct game));

  if (Game == NULL)
  {
    printf("Out of memory \n");
    return 1;
  }
  /*Variaveis necessarias*/

  char command[20];
  char escolha;
  char option[256];
  int nivel= 0;
  int tentativas = 0;
  int patamar = 0;
  int i = 0;
  char text[] =".txt";
  char j50[] = "YES";
  char j25[] = "YES";
  char name[20] = "Newbie";
  int progress = 0;
  char A[128];
  char B[128];
  char C[128];
  char D[128];
  int num_rand = 0;
  int array_length = 500;
  int n;

  /*Loop que irá continuar até o utilizador parar/perder/ganhar*/

  while(command[0] != 'q' && patamar != 8 && tentativas != 2)
  
  {
    printf(">");
    fgets(command, 100, stdin);
    n = sscanf(command, "%c %s", &escolha, option);
    nivel = level(patamar);

    if (tentativas == 2)
    {
      puts(MSG_OVER);
      break;
    }

    if (escolha == 'h')
    {
      print_menu();
    }

    else if (escolha == 's')
    {
        if (n == 2)
        {
          /* fazer que isto pegue o nome do jogador*/
          char file_name[20];
          strcpy(file_name ,option);
          strcat(file_name, text);
          FILE *save_file;
          save_file = fopen(file_name,"w");
          fprintf(save_file, "%d\n" , nivel);
          fprintf(save_file, "%s\n" , j50);
          fprintf(save_file, "%s\n" , j25);
          fprintf(save_file, "%s\n" , name);
          FILE * fq = fopen(pficheiro,"r" );
          char c = fgetc(fq);
          while (c != EOF)
          {
            fputc(c, save_file); 
            c = fgetc(fq); 
          } 
          fclose(fq);
          fclose(save_file);
          puts(MSG_SAVE);
        }
      
      break;
    }

    else if (escolha == 'q')
    {
      puts(MSG_BYE);
      break;
    }

    else if (escolha == 'c')
    {
      puts("This game was made by :");
      puts("Francisco Salgado (21902823)");
      puts("João Borges (21904214)");
      puts("Rogério Martins (21900241)");
    }

    else if (escolha == 'n' && progress != 1 )
    {
      if (argc >3)
      {
        if (n == 2)
        {
          char new_name[20];
          strcpy(new_name ,option);
          printf("*** Hi %s, let's get started!\n", new_name);
          strcpy(name, new_name);
          patamar = 0;
          nivel = level(patamar);
          printf("%i", patamar);
        }
        else
        {
          puts("*** Hi Newbie, let's get started!");
        }

        print_status(nivel, j50, j25, name);
        num_rand = games(pficheiro,patamar, &i, Game, A,B,C, D, progress);   
        progress = 1; 
      }
      else
      {
        puts(MSG_ERROR);
      }
      
    }
    else if (escolha == 'r' && progress != 1)
    {
      
      /* Do the game first */
      if (n == 2)
      {
        char aux[256];
        char file_name[20];
        strcpy(file_name ,option);
        FILE *save_file; 
        save_file = fopen(file_name,"r");
        fgets(aux, 256, save_file);
        nivel = atoi(aux);
        fgets(aux, 256, save_file);
        strcpy(j25,aux);
        fgets(aux, 256, save_file);
        strcpy(j50,aux);
        fgets(aux, 256, save_file);
        strcpy(name,aux);

        //char new_name[20];
        //strcpy(new_name ,&file_name[2]);
        //strcpy(name, new_name);
        //name = &file_name[2];
        
        printf("*** Ok %s, where were we? Oh there you go:\n", name);
        
        char * psave;
        psave = &file_name[4];
        num_rand = games(psave, patamar, &i, Game, A, B, C, D, progress);
        progress=1;
      }
      else
      {
        puts(MSG_ERROR);
      }
      
      /* game(points, nivel, j50, j25); */
    }



    else
    {
      if (progress == 1 && (escolha == 'A' || escolha == 'B' || escolha == 'C' || escolha == 'D'))
      {
        int tent_add = resposta(escolha, &i, A, B, C, D, &patamar);
        remove_element(Game, num_rand, array_length);
        struct game *tmp = realloc(Game, (array_length - 1) * sizeof(struct game) );
        if (Game == NULL && array_length > 1) {
          exit(EXIT_FAILURE);
        }
        array_length = array_length - 1;
        if (array_length == 0)
        {
          puts("*** This is embarrassing but we're out of questions.");
        }
        Game = tmp;
        tentativas += tent_add;
        i =0;
        nivel = level(patamar);
        if (tentativas == -1)
        {
          tentativas = 0;
        }
        if(tentativas != 2)
        {
          print_status(nivel, j50, j25, name);
          num_rand = games(pficheiro,patamar, &i, Game, A,B,C, D,progress);
        }
      }
      else
      {
        if (progress == 0)
        {
          puts(MSG_UNKNOWN);
        }
        else
        {
          puts(MSG_ERROR);
        }
      }
        if (array_length == 1)
        {
          free(Game);
        }
    }
  }
  
  if (patamar == 8)
  {
    puts(MSG_WIN);
    printf("Congratulations %s \n", name);
    return 0;
  }
  if (tentativas == 2)
  {
    puts(MSG_OVER);
    return 0;
  }
  return 0;
}



//--------------------------------------------
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <time.h>
// #include <string.h>
// #include <strings.h>

// /* define para usar strings mais facilmente */
 
// #define MSG_WELL "*** Hooray!"
// #define MSG_WIN "*** This is incredible! You have won!"
// #define MSG_OVER "*** Sorry, you have lost the game. Bye!"
// #define MSG_SAVE "*** Ok, your progress has been saved. See you later!"
// #define MSG_ERROR "*** Illegal move"
// #define MSG_BYE "*** Sad to see you go..."
// #define MSG_UNKNOWN "*** Unknown adicional."

// /* JOGO */

// int game(int i)
// {
//     FILE *quest_file;
//     //int ascii = 65;
//     //char answers_1 [4];
//     /*char answers_2 [1];
//     char answers_3 [1];
//     char answers_4 [1];*/
//     //nt number = 200;
//     //char buff[200];
//     //char print_text [5000][200];
//     quest_file = fopen("questions.txt","r");
    
//     fclose(quest_file);
//     return i + 8;

// }

// /* função que apresenta os status do player */

// void print_status(const int nivel, const char * j50, const char * j25, const char * name)
// {
//     puts("********************************************");
//     printf("*** Name:  %s               *\n", name);
//     printf("*** Level:  %d                  *\n", nivel);
//     printf("*** j50: %s                    *\n", j50);
//     printf("*** j25:  %s                   *\n", j25);
//     puts("********************************************");
// }
 
// /* função para dar print no menu */
 
// void print_menu(void)
// {
//     puts("********************************************");
//     puts("***            CILLIONAIRE                 *");
//     puts("********************************************");
//     puts("*** n <name>     - new game                *");
//     puts("*** q            - quit                    *");
//     puts("*** h            - show this menu          *");
//     puts("*** r <filename> - resume game             *");
//     puts("*** s <filename> - save progress and quit  *");
//     puts("*** j 50         - play 50:50 joker        *");
//     puts("*** j 25         - play 25:75 joker        *");
//     puts("*** c            - show credits            *");
//     puts("********************************************");
// }

// int main(int argc, char * argv[])
// {
    
//     print_menu();
    
//     /*dar check no argc e argv*/

//     if(argc == 1)
//     {
//         srand(time(0));
//     }
//     else if(argc == 2)
//     {
//         srand(atoi(argv[1]));
//     }
    
//     /*Variaveis necessarias*/

//     char command[20];
//     char escolha;
//     char adicional;
//     int return  0;
//     int tentativas = 0;
//     int patamar = 0;
//     int i = 0;
//     char text[] =".txt";
//     char j50[] = "YES";
//     char j25[] = "YES";
//     char name[20] = "Newbie";

//     /*Loop que irá continuar até o utilizador parar/perder/ganhar*/

//     while(command[0] != 'q' && patamar != 9 && tentativas != 2)
//     {
//         printf(">");
//         fgets(command, 100, stdin);
//         sscanf(command, "%c %s", &escolha, &adicional);

//         if (escolha == 'n')
//         {
//             if (adicional)
//             {
//                 char new_name[20];
//                 strcpy(new_name ,&adicional);
//                 printf("*** Hi %s, let's get started!\n", new_name);
//                 strcpy(name, new_name);
//                 patamar = 1;
//             }
//             if (patamar == 0)
//             {
//                 puts("*** Hi Newbie, let's get started!");
//             }
//             print_status(nivel, j50, j25, name);
//             game(i);
//         }

//         else if (escolha == 'r')
//         {
//             /* Do the game first */
//             char file_name[20];
//             strcpy(file_name ,&adicional);
//             strcat(file_name, text);
//             FILE *save_file; 
//             save_file = fopen(file_name,"r");
//             fprintf(save_file, "%d\n" , nivel);
//             char name[] = "something";
//             printf("*** Ok %s, where were we? Oh there you go:\n", name);
//             /* game(points, nivel, j50, j25); */
//         }

//         else if (escolha == 's')
//         {
//             if (adicional)
//             {
//                 /* fazer que isto pegue o nome do jogador*/
//                 char file_name[20];
//                 strcpy(file_name ,&adicional);
//                 strcat(file_name, text);
//                 FILE *save_file; 
//                 save_file = fopen(file_name,"w");
//                 fprintf(save_file, "%d\n" , nivel);
//                 fprintf(save_file, "%s\n" , j50);
//                 fprintf(save_file, "%s\n" , j25);
//                 fprintf(save_file, "%s\n" , name);
//                 fclose(save_file);
//                 puts(MSG_SAVE);
//             }
// 			break;
//         }

//         else if (escolha == 'h')
//         {
//             print_menu();
//         }

//         else if (escolha == 'q')
//         {
//             puts(MSG_BYE);
//             break;
//         }

//         else if (escolha == 'c')
//         {
//             puts("This game was made by :");
//             puts("Francisco Salgado (21902823)");
//             puts("João Boeges (21904214)");
//             puts("Rogério Martins (21900241)");
//         }

//         else
//         {
//             puts(MSG_UNKNOWN);
//         }
//     }

//     return 0;
// }