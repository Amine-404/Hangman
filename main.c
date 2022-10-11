#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
/*This function guarantees the randomness of the world*/
char* random_word(int word_length)
{
    int i=0,n=0;
    char* s;
    char* ch;
    s=(char*)malloc(word_length*sizeof(char));
    ch=(char*)malloc(word_length*sizeof(char));
    srand(time(NULL));
    n= rand()%200;
    FILE* fp=fopen("WORDS.txt","r");
    if (fp==NULL)
        return 0 ;
    while(1)
    {
        fscanf(fp,"%s",s);
        if (strlen(s) == word_length)
        {
            strcpy(ch,s);
             i=i+1;
        }
        if(i==n)
            break;
        if (fscanf(fp,"%s",s)!=1)
            break;
    }
    fclose(fp);
    return ch;
}




/*This function returns the position of the letter in the word whether it is a lowercase or uppercase letter.
  If the letter does not exist it returns -1*/
int pos_letter(char* word,char letter)
{
    int i;
    for(i=0; i<strlen(word); i++)
    {
        if (toupper(word[i])==toupper(letter))
            return i;
    }
    return -1;
}




/*This function replaces every dash with correctly guessed letter*/
void unveil(char* word,char* dashes,char letter)
{
    int i;
    for(i=0; i<strlen(dashes); i++)
    {
        if (toupper(word[i])==toupper(letter))
        {
            dashes[i]=word[i];
        }
    }
}




int main()
{
    char* word;
    char* dashes;
    char letter;
    int miss=0,allowed_miss=0,word_length,i,restart;
    printf("Welcome to the guessing game : Hangman\nFirst, please enter the word's length (Min:2 , Max:15) and the allowed number of misses\n");
    do
    {   fflush(stdin);
        printf("Word's length : ");
        scanf("%d",&word_length);
        if ((word_length<2)||(word_length>15))
        printf("Error, re-enter the word's length, it should be a number between 2 and 15.\n");
    }
    while ((word_length<2)||(word_length>15));
    do
    {    fflush(stdin);
         printf("Allowed number of misses : ");
         scanf("%d",&allowed_miss);
        if (allowed_miss<=0)
        printf("Error, re-enter the allowed number of misses, it should be a number higher than 0.\n");
    }
    while (allowed_miss<=0);
    printf("\n");
    word=(char*)malloc(word_length*sizeof(char));
    word=random_word(word_length);
    dashes=(char*)malloc(word_length*sizeof(char));

    for(i=0; i<word_length; i++)
        dashes[i]='-';
    dashes[i]='\0';
    while((miss<allowed_miss) && (pos_letter(dashes,'-')>=0))
    {
        printf("current word: ");
        puts(dashes);
        do
        {   fflush(stdin);
            printf("\nEnter the letter: ");
            scanf("%c",&letter);
            if ((toupper(letter)<'A')||(toupper(letter)>'Z'))
                printf("Error. enter a letter\n");
        }
        while ((toupper(letter)<'A')||(toupper(letter)>'Z'));
        printf("\n");
        if (pos_letter(word,letter)>=0)
        {
            if (pos_letter(dashes,letter)>=0)
            {
                printf("You have already guessed this letter\n");
            }
            else
            {
                printf("You guessed correctly !\n");
                unveil(word,dashes,letter);
            }
        }
        else
        {
            miss=miss+1;
            printf("Wrong letter ! You have %d tries left\n \n",allowed_miss-miss);
        }
    }
    if (miss<allowed_miss)
        printf("Congratulations, you won.\n");
    else printf("Unfortunately, you lost.\n");
    printf("The word is: ");
    puts(word);
    free(word);
    free(dashes);
    printf("If you wish to play again press (1) if you want to quit press (0)\n");
    scanf("%d",&restart);
    if (restart==1)
        main();
    return 0;
}
