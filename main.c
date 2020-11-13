/************************************************************
*** Title: hAnGmAn GaMe *************************************
*** Author: cold_summer aka Elizabeth Maslennikova **********
*** Date: 07/11/2020 ****************************************
*** Description: If you kill him I'm gonna call 911! ********
************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MAX 99// temp const for arrays
#define ATTEMPTS 5// parts of the hanged man (head,hands,legs. Begins from 0)
#define HANGMAN_ROWS 5// rows of string (begins from 0)
#define HANGMAN_COLUMNS 7// columns of  string (begins from 0)

static int game_over = -1, wrong = -1, counter = -1;
static char player_word[MAX], var_for_enter, pc_or_player;

char *hangu_mane[] = 
{" +----+",
" |    |",
"x_x   |",
"/|\\   |",
"/ \\   |",
"=R=I=P=",
};//       \T_T/ defeat

char *hangu_mane_saved[] = 
{" +----+",
" !    |",
"^o^   |",
"\\|/   |",
"/ \\   |",
"=Y=E=S=",
};//       \*O*/ victory

char *dancing_men[] = 
{".......................................................................",
".   o   \\ o /  _ o        __|    \\ /     |__         o _  \\ o /   o   .",
".  /|\\    |     /\\   __\\o   \\o    |    o/     o/__   /\\     |    /|\\  .",
".  / \\   / \\   | \\  /) |    ( \\  /o\\  / )     |  (\\  / |   / \\   / \\  .",
"....................................................................... ",
};// menu graphics xD

char *border[] = 
{"________________________________",
"/   \\                           \\.",
"|   |                            |.",
"\\___|                            |.",
"    |                            |.",
"    |                            |.",
"    |                            |.",
"    |                            |.",
"    |                            |.",
"    |                            |.",
"    |                            |.",
"    | credits: cold_summer       |.",
"    |                            |.",
"    | 🄴 🄻 🄸 🅉 🄰 🄱 🄴 🅃 🄷          |.",
"    | 🅼 🅰 🆂 🅻 🅴 🅽 🅽 🅸 🅺 🅾 🆅 🅰    |.",
"    |   _________________________|___",
"    |  /                            /.",
"    \\_/____________________________/.",
};// this game took a lot of hours of my life... and also nerve cells xD
// at least know who made it, ok O:-)

char *logo[] = 
{"___",                              
"| |",                                            
"| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __",
"| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\",
"| | | | (_| | | | | (_| | | | | | | (_| | | | |",
"|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|",
"                    __/ |                      ",
"                   |___/",                       
};

typedef struct secret_random_word
{
  int random_index;
  int length;
  char letters[MAX];
  int array_with_nulls[MAX];
}srw;// abbreviation for "secret random word"


srw word;// data type 'srw' and its var "word"

srw word_constructer(char pc_or_player);// func-randomizer
int check_if_correct(char users_input);// func-checker
void draw(int users_input);// func-painter
void clearscr();// func-screen-cleaner for all OS's 
void game_with_pc(char users_input);
void game_with_player(char users_input);


//let's play!
int main(void)// START of MAIN
{  
  srand(time(NULL));
  char users_input;

   for(int columns = 0; columns < 8; columns++)
   printf("\n\t\t\t\t%s", logo[columns]);
  printf("\n\n\n\n\t\t\t\t☆ﾟ. * ･ ｡ﾟ ~... 𝐇 𝐄 𝐋 𝐋 𝐎  𝐔 𝐒 𝐄 𝐑 ! ...~ ☆ﾟ. * ･ ｡ﾟ\n\n\nThis is a 🄷 🄰 🄽 🄶 🄼 🄰 🄽  game.\nBefore you start playing let me tell you the rules.\n");
  printf("\n\n\t\t\t\t\t\t So, there are only two of them:");
  printf("\n\n\t\t\t\t\t   ☻ Maximum 6 mistakes are allowed");
	printf("\n\n\t\t\t\t\t   ☻ All symbols are in English only\n");
   for(int columns = 0; columns < 18; columns++)
   printf("\n%s",border[columns]);	
   printf("\n");
   for(int columns = 0; columns < 5; columns++)
   printf("\n%s",dancing_men[columns]);
  
  printf("\n\n\t\t\t\t\t\t☆ﾟ. * ･ ｡ﾟ Let's start the game! ☆ﾟ. * ･ ｡ﾟ \n\t\t	(づ ￣ ³￣)づ\n\n\t\t\t\t\t\t Who are you going to play with? (ง •̀_•́)ง ผ(•̀_•́ผ)\n");
  printf("\n\t\t\t\t\t\t Press:\n\t\t\t\t\t\t 🅲  to play with your computer ᕙ (`▿´)ᕗ\n\t\t\t\t\t\t 🅿  to play with another player ٩(˘◡˘)۶\n\t\t\t\t\t\t 🅇  to quit the game .·´¯`(>▂<)´¯`·.");
  printf("\nSo, your choice is: ");
  pc_or_player = getchar();
  pc_or_player = tolower(pc_or_player);
  var_for_enter = getchar();

  if(!isalpha(pc_or_player))// checks if the input is an int
  { 
  printf(ANSI_COLOR_RED "\n\n[C], [P] or [X] only, please: "ANSI_COLOR_RESET);
  return main();
  }
  if(isalpha(pc_or_player))// checks if the input is an uppercase char
  {
    game_over = -1, wrong = -1, counter = -1;
    pc_or_player = tolower(pc_or_player);
  }

  if(pc_or_player == 'c')
  {
   game_over = -1, wrong = -1, counter = -1;
   word = word_constructer(pc_or_player);// initialize var for a random word
   game_with_pc(users_input);// START of game with pc
  }
  if(pc_or_player == 'p')
  { 
   game_over = -1, wrong = -1, counter = -1;
   game_with_player(users_input);// START of game with another player
  }
  if(pc_or_player == 'x')// quit the game
  printf("\nAlready leaving? \nHope to see you soon! ~");
  
  if(game_over == 1 || game_over ==0)
  { 
    while(users_input != 'y' || users_input !='n')
    { 
     printf("\n\n Wanna play again?\n \t (^-ω-^) 🆈  / 🅽 (⌣_⌣”)\n");
     users_input = getchar(); 
     users_input = tolower(users_input);  
     var_for_enter = getchar();
   
      if(!isalpha(users_input))
      printf("\n\nOnly alphabetical characters please!");
      if(users_input == 'y')
      {
       clearscr();
       main();
      }
      if(users_input == 'n')
      printf("Thank you! Hope to see you soon. \nBye ~");
    }
  } 
  return 0;
}// END of MAIN


// let's extract words from the file (if game with pc)
// or ask a word from your opponent (if game with player)
srw word_constructer(char pc_or_player)// START of func
{
  if(pc_or_player == 'c')
  {
  word.random_index = rand()%2999;

  FILE *file_pointer;
  file_pointer = fopen("dictionary.txt","r");
  
  if(file_pointer != NULL)
  {
   for (int rows = 0; rows <= word.random_index; rows++)
   { 
     for (int columns = 0; columns <= '\0'; columns ++)
    fgets(word.letters,MAX,file_pointer);
    word.length = strlen(word.letters) - 1;
    }
  }
  else
  printf("ERROR! Text file is not found. Try again.\n");
  
 fclose(file_pointer);
  }

  else
  { 
   word.length = strlen(player_word);
   for(int columns = 0; columns < word.length; columns++)
   word.letters[columns] = player_word[columns];
  }

  for(int columns = 0; columns < word.length; columns++)
  word.array_with_nulls[columns] = 0; 

 return word;
}// END of func


int check_if_correct(char users_input)// START of func
{ 
 int boolean = 0;

  for(int columns = 0; columns < word.length; columns ++)
  { 
    if((word.letters[columns]) == users_input)
   { 
       boolean = 1;   
       word.array_with_nulls[columns] = 1;
    }    
  } 
  if(users_input == '0' || users_input == '1' || users_input == '2' || users_input == '3')
  boolean = -1;
  
  return boolean;
}// END of func


// OK, it's going to be a big func, but its logic is simple. Don't be afraid of it
// there are lots of lines of code which are my comments or printf drawing
void draw(int users_input)// START of func
{   
// for one usage of every hint
  int one_time_only = -1, one_time_only_2 = -1, one_time_only_3 = -1, hints = -1;

   do // game process, loop while game over is false
    { 

// draw the secret word
      printf(ANSI_COLOR_CYAN "\nThe word is: " ANSI_COLOR_RESET); 
      for(int columns = 0; columns < word.length; columns++)
      {
       if(!*(word.array_with_nulls + columns))
       {
            printf( ANSI_COLOR_CYAN "[✖]" ANSI_COLOR_RESET);   
       }
       else 
          { 
            printf("\033[0;31m");
            printf("%c", word.letters[columns]);
            printf("\033[0m");
          }
      }

// the lines from 269 to 329 have to do with hints (1st hint, 2nd hint, etc ...~)
      if(users_input == '0')
      {
       printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tThere are three kinds of hints.\n\t\t\t\t\t\t\t\t\t\t\t\t\tYou you can use only two of them.\n\t\t\t\t\t\t\t\t\t\t\t\t\t");
       printf("Press:\n\t\t\t\t\t\t\t\t\t\t\t\t\t 1⃞ to show one correct letter\n\t\t\t\t\t\t\t\t\t\t\t\t\t 2⃞ to show one correct and one random \n\t\t\t\t\t\t\t\t\t\t\t\t\t 3⃞ to forget your next input if it will be wrong\n");
      }
// user presses 1
      if(users_input == '1')
      {  
       int random_index = rand()%word.length;// for 1st and 2nd hints 
            
        if (word.array_with_nulls[random_index] == 1)
        {
         do 
         {
          random_index = rand()%word.length;
          }while(word.array_with_nulls[random_index] == 1);
         }
   
        if((one_time_only == -1) && (hints < 2))
        {
         word.array_with_nulls[random_index] = 1;  
            hints++;   
            one_time_only++;        
         }       
      }
// user presses 2
      if((users_input == '2') && (one_time_only_2 == -1) && (hints < 2))
      {  
        char alphabet[26] = {"abcdefghijklmnopqrstuvwxyz"};
        int random_index = rand()%word.length;
        int random_index_2 = rand()%25;
        printf("\n It's [%c] or [%c]", word.letters[random_index], alphabet[random_index_2]);
        hints ++;
        one_time_only_2 ++;
        }
// user presses 3
      if((users_input == '3') && (hints < 2) && (one_time_only_3 == -1))
      { 
        printf("\033[1;31m"); 
        printf("\n PC: — OK! It will be our secret ;)\n");
        printf("\033[1;0m");        
          
          printf(ANSI_COLOR_BLUE "Enter your letter: " ANSI_COLOR_RESET );
          char temp_wrong_letter;
          users_input = getchar(); 
          users_input = tolower(users_input);  
          var_for_enter = getchar();
            
          for(int columns = 0; columns < word.length; columns++)
          {
           if(word.letters[columns] != users_input)
           {
            temp_wrong_letter = users_input;  
            wrong--;
            hints++;
           }
                                                 
            else
            continue;
          }
          printf("\033[1;31m");
          printf("\n PC: — OH! There is no '%c' in the word. Remember that.", temp_wrong_letter);
          printf("\033[1;0m");        
      }
           
      if(hints >= 1)
      printf(ANSI_COLOR_RED "\n PC: — Only two hints are allowed!\nYou have already used them.\n" ANSI_COLOR_RESET);

// requires user's input
      printf(ANSI_COLOR_BLUE "\nEnter your letter: "  ANSI_COLOR_RESET );
      users_input = getchar(); 
      users_input = tolower(users_input);  
      var_for_enter = getchar();

// control user's input
      if(!isalpha(users_input) && users_input != '0' && users_input != '1' && users_input != '2' && users_input != '3')
      {
      printf(ANSI_COLOR_RED "\nOnly alphabetical characters please!\n Play again?\n 🆈  / 🅽\n" ANSI_COLOR_RESET);

    users_input = getchar();  
    var_for_enter = getchar();
    users_input = tolower(users_input);

      if(users_input == 'y')
      {
       clearscr();
       main();
       break;
      }
      if(users_input == 'n')
       printf("Thank you! Hope to see you soon. \nBye ~");
      else
       printf("\n42");
      }
      
    clearscr ();// calls func-screen-cleaner

      int counter_twin = 0;
      for(int columns = 0; columns < word.length; columns++)
      { // word.array_with_nulls consists of 1s or 0s only
        // so, its summary would be equal to word's length
        // it's needed to finish the game if user
        // founds out all letters
        counter_twin  += *(word.array_with_nulls + columns);
        counter = counter_twin;
          if(counter == word.length - 1)
          game_over = 1; 
      }

// let's compare user's input to the secret word
// if the input does not exist in the word
      if(check_if_correct(users_input) == 1)
      { 
       printf(ANSI_COLOR_GREEN "Right!\n PC: (╯°□°）╯︵ ┻━┻ — Nooo... \n\n" ANSI_COLOR_RESET);

       if(game_over == 1)
       {
        clearscr ();
         for(int rows = 0; rows <= HANGMAN_ROWS; rows++)  
         {  
          printf("\n\t\t\t\t\t\t\t\t");
            for(int columns = 0; columns <= HANGMAN_COLUMNS; columns++)
            {      
              printf("\033[1;32m");
              printf("%c",hangu_mane_saved[rows][columns]);
              printf("\033[0m");
             }
          }
        } 
      }
// if the input does not exist in the word
      if(check_if_correct(users_input) == 0)
      {   
      printf(ANSI_COLOR_YELLOW "Wrong!\n PC:（ ^_^）o自自o（^_^ ）— Cheers!\n\n" ANSI_COLOR_RESET);
      wrong++; 
        if(wrong == ATTEMPTS)
        game_over = 0;
  
       for(int rows = 0; rows <= wrong; rows++)  
       {
        printf("\n\t\t\t\t\t\t\t\t");

        for(int columns = 0; columns <= HANGMAN_COLUMNS; columns++)
         { 
         printf("\033[1;31m");
         printf("%c",hangu_mane[rows][columns]);
         printf("\033[1;0m");        
         }
        }
      }     
// result of the game
      if(game_over == 0)// in case of defeat
      {
      printf("\n\n\t\t\t\t   ☆ﾟ. * ･ ｡ﾟ 𝐃 𝐄 𝐅 𝐄 𝐀 𝐓 ☆ﾟ. * ･ ｡ﾟ");
      printf(ANSI_COLOR_CYAN "\n\n\t\t\t\t\t\t( ͡°( ͡° ͜ʖ( ͡° ͜ʖ ͡°)ʖ ͡°) ͡°)" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_MAGENTA "\n\t\t\t\t\t\t   Ⓦ Ⓘ Ⓣ Ⓝ Ⓔ Ⓢ Ⓢ Ⓔ Ⓢ" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_CYAN "\n\t\t\t\t\t\t⎧ᴿᴵᴾ⎫◟◟◟◟◟◟◟◟ ❀◟(ó ̯ ò, )" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_MAGENTA "\n\t— OMG!\n\t— It seems that your IQ killed him... \n\t— Za toboy uzhe vyehali, suka. " ANSI_COLOR_RESET);
      printf(ANSI_COLOR_CYAN "━╤デ╦︻(▀̿̿Ĺ̯̿̿▀̿ ̿)\n" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_CYAN "\t(︶︹︺)\n\n" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_RED "\n\nPC: — I won.\n" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_RED "\nDon't be upset. Drink some chamomile tea and meditate.\n" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_RED "P.S. by the way, the word was: " ANSI_COLOR_RESET);
      printf("%s", word.letters);
      }

      if(game_over == 1)// in case of victory
      {
      printf("\n\n\t\t\t\t  ☆ﾟ. * ･ ｡ﾟ 𝐕 𝐈 𝐂 𝐓 𝐎 𝐑 𝐘 ☆ﾟ. * ･ ｡ﾟ");
      printf(ANSI_COLOR_CYAN "\n\n\t\t\t\t\t\t\\(^o^)/ *.*.* \\(^o^)/" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_YELLOW "\n\t\t\t\t\t   Ⓨ Ⓞ Ⓤ Ⓡ  Ⓕ Ⓐ Ⓝ Ⓖ Ⓘ Ⓡ Ⓛ Ⓢ " ANSI_COLOR_RESET);
      printf(ANSI_COLOR_CYAN "\n\t\t\t\t\t\tƪ(˘⌣˘)┐ ƪ(˘⌣˘)ʃ ┌(˘⌣˘)ʃ\n" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_YELLOW "\n\t— ~(‾▿‾)~ Wow ~(‾▿‾)~ \n\n" ANSI_COLOR_RESET);   
      printf(ANSI_COLOR_CYAN "\n\t ͡ ͡° ͜ ʖ ͡ ͡°)\n\t\\╭☞ \\╭☞ "ANSI_COLOR_CYAN);
      printf(ANSI_COLOR_YELLOW "— You are my hero...\n\n" ANSI_COLOR_RESET);
      printf(ANSI_COLOR_RED"\n\nPC: You won.\nYou found my secret word. \nYeah. It was: " ANSI_COLOR_RESET);
      printf("%s",word.letters);
      printf(ANSI_COLOR_RED "\nCongrats, genius ~ \nYou saved that dude from suicide.\n\n ( ^-^)_旦 I just reserved a place in paradise for you ;)\n" ANSI_COLOR_RESET);
      }
      if(game_over == -1)
      printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t Need help? There are some hints.\n\t\t\t\t\t\t\t\t\t\t\t\t\t Press 🅾 (zero) if needed\n");
   
    }while(game_over == -1 );
}// END of func  


void clearscr ()// START of func-screen-cleaner
{
  for ( int i = 0; i < 50; i++ ) // 50 is arbitrary
  printf("\n");
}// END of func  


void game_with_pc(char users_input)// START of func
{ 
 draw(users_input);
}// END of func  


void game_with_player(char users_input)// START of func
{
printf("\nPlease, make up a word for another player to guess: ");

scanf("%s",player_word);
 var_for_enter = getchar();

word = word_constructer(pc_or_player);

draw(users_input);
}// END of func  
