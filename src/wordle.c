#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>


#define RED "\033[0m\e[0;31m"
#define GRN "\033[0m\e[0;32m"
#define YEL "\033[0m\e[0;33m"
#define PUR "\033[0m\e[0;35m"
#define BLU "\033[0m\e[0;34m"
#define CYN "\033[0m\e[0;36m"
#define MAG "\033[0m\e[0;35m"
#define WIT "\033[0m\e[1;97m"

int wordLen = 0;

char* getWord();
void statusUpdate(char guess[],int status[],int mappedWord[],char word[]);
void display(int status[], char guess[]);
bool win(int status[]);

//bool winConditionMatched(char guess[], char word[]);

int main(int argc, char** argv)
{
     char* word = getWord();
     wordLen = strlen(word);
     printf("word is %s",word);

    int mappedWord[26] = {0};    
    //mapping letters
    for(int i = 1; i <= wordLen; i++)
    {
        if(mappedWord[word[i-1] - 'a'] == 0)
            mappedWord[word[i-1] - 'a'] = 1;
        else
            mappedWord[word[i-1] - 'a']++;
    }

    //clear status array
    int status[wordLen];
    for(int i = 0; i < wordLen; i++)
        status[i] = 0;

    //print start area
    printf("\n"PUR"W"GRN"E"YEL"L"RED"C"BLU"O"CYN"M"MAG"E"YEL" T"BLU"O "GRN"W"PUR"O"CYN"R"MAG"D"YEL"L"WIT"E" "\033[0m\n");
    printf("Guess this %d letter Word, U get %d Tries\n",wordLen,wordLen + 1);
    // for(int i = 0; i < wordLen; i++)
    //     printf(WIT"#");
    // printf("\n");
    

    int no_of_guesses = wordLen + 1;  
    char guess[wordLen + 1]; //user input of matching size
    char buffer[100];  //to take user input
    int i = 0;
    for(i = 0; i < no_of_guesses && !win(status); i++)
    {
        do
        {
            printf("guess %d>>",i+1);
            scanf("%s",buffer);
        } while(strlen(buffer) != wordLen);
        strncpy(guess,buffer,wordLen);
        statusUpdate(guess,status,mappedWord,word);
        display(status,guess);
    }

    if(!win(status))
        printf("The Word was %s\nBetter Luck Next Time!!!\n",word);
    else
        printf("Congratulation U guessd the word in %d attempts !!!!",i);
        
    return 0;
}


char* getWord()
{
    srand(time(0));
    int wordSize = 5 + rand()%4;
    
    char filename[15];
    sprintf(filename,".\\src\\%d.txt",wordSize);

    FILE* word_file_ptr = fopen(filename,"r");
    if(word_file_ptr == NULL)
    {
        printf("Txt File not Found\n");
        exit(EXIT_FAILURE);
    }

    char* word = (char* )malloc(sizeof(char)*wordSize + 1);
    int randomLineCount = rand() % 1000;
    while(randomLineCount-- > 0)
    {
        fgets(word,100,word_file_ptr);
        word[strcspn(word,"\n")] = '\0';
    }
    return word;
}


void statusUpdate(char guess[],int status[],int mappedword[],char word[])
{
    char copy[26];
    for(int i = 0; i < 26; i++)
        copy[i] = mappedword[i];

    for(int i = 0; i < wordLen; i++)
    {
        if(guess[i] != word[i])
            status[i] = -1;
        else if(guess[i] == word[i])
        {
            copy[guess[i] - 'a']--;
            status[i] = 1;
        }
    }
    for(int i = 0; i < wordLen; i++)
    {
        if(status[i] == -1 && copy[guess[i] - 'a'] != 0)
        {
            copy[guess[i] - 'a']--;
            status[i] = 0;
        }      
    }
}


void display(int status[],char guess[])
{
    for(int i = 0; i < wordLen; i++)
    {
        if(status[i] == 1)
            printf(GRN"%c",guess[i]);
        else if(status[i] == 0)
            printf(YEL"%c",guess[i]);
        else
            printf(RED"%c",guess[i]);
    }
    printf("\033[0m\n");
}

bool win(int status[])
{
    for(int i = 0; i < wordLen; i++)
    {
        if(status[i] != 1)
            return false;
    }
    return true;
}



