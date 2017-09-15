/* 
 * File:   main.c
 * Author: Leng
 *
 * Created on November 6, 2016, 9:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *stream;

void printPuzzle (int size);
void puzzleBoard (char* puzzleName);
void readWords (char * puzzleWordName, char* puzzleSolName);
int looksAround (char * letter, int iValue, int jValue);
void wordSearch(char* puzzleSolName, char *word);

char puzzle [25][25];

/*
 * 
 */
int main(int argc, char** argv) {
    
    char puzzleName[12];
    printf("Please enter the puzzle name: ");
    scanf ("%s", puzzleName);
    while (strlen(puzzleName)>12) {
        printf("Error: The name of the puzzle is more than 12 characters.\n");
        printf("Please enter the puzzle name: ");
        scanf ("%s", puzzleName);
    }
    
    char puzzleWordName[20];
    char puzzleSolName[20];
    strcpy(puzzleWordName, puzzleName);
    strcpy(puzzleSolName, puzzleName);
    
    strcat(puzzleName, ".txt");
    puzzleBoard(puzzleName);
    
    //Reading in words
    strcat(puzzleWordName, "_words.txt");
    strcat(puzzleSolName, "_soln.txt");
    
    FILE * puzzleFile;
    puzzleFile = fopen(puzzleSolName, "w");
    if (puzzleFile == NULL) {
        printf("Error opening %s file.\n", puzzleSolName);
        exit(1);
    }

    readWords(puzzleWordName, puzzleSolName);
    
    
    return (EXIT_SUCCESS);
}

void puzzleBoard (char * puzzleName) {
    FILE * puzzleFile;
    puzzleFile = fopen(puzzleName, "r");
    if (puzzleFile == NULL) {
        printf("Error opening %s file.\n", puzzleName);
        exit(1);
    }
    int i=0;
    int j=0;
    char hold[1];
    int tempSize;
    fscanf(puzzleFile,"%d", &tempSize);
    int size=tempSize;
    puzzle [size][size];
    for (i=0;i<size;i++) {
        for (j=0;j<size;j++) {
            fscanf(puzzleFile, "%s", hold);
            puzzle[i][j]=hold[0];   
        }
    }
    fclose(puzzleFile);
    printPuzzle(size);
}

//Test - Printing of original puzzle
void printPuzzle (int size){
    int i;
    int j;
    printf("\nPuzzle Board: \n");
    for (i=0;i<size;i++) {
        for (j=0;j<size;j++) {
            printf("%c ", puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void readWords (char * puzzleWordName, char* puzzleSolName) {
    FILE * puzzleFile;
    puzzleFile = fopen(puzzleWordName, "r");
    if (puzzleFile == NULL) {
        printf("Error opening %s file.\n", puzzleWordName);
        exit(1);
    }
    char word [24];
    while (fscanf(puzzleFile, "%s", word)!=EOF) {
        wordSearch(puzzleSolName, word);
    }
    fclose(puzzleFile);
}

void wordSearch(char* puzzleSolName, char *word) {
    FILE * puzzleFile;
    puzzleFile = fopen(puzzleSolName, "a");
    if (puzzleFile == NULL) {
        printf("Error opening %s file.\n", puzzleSolName);
        exit(1);
    }
    int i;
    int j;
    int direction=0;
    int size = strlen(puzzle[1]);
    for (i=0; i<size; i++) {
        for (j=0; j<size; j++) {
            if (word[0]==puzzle[i][j]) {
                direction = looksAround(word,i,j);
                if (direction!=0) {
                    if (direction==1) {
                        printf("%s (%d,%d) %s\n", word, j, i,"NW");
                        fprintf(puzzleFile, "%s (%d,%d) %s\n", word, j, i,"NW");
                        break;
                    }
                    if (direction==2) {
                        printf("%s (%d,%d) %s\n", word, j, i,"N");
                        fprintf(puzzleFile, "%s (%d,%d) %s\n", word, j, i,"N");
                        break;
                    }
                    if (direction==3) {
                        printf("%s (%d,%d) %s\n", word, j, i,"NE");
                        fprintf(puzzleFile, "%s (%d,%d) %s\n", word, j, i,"NE");
                        break;
                    }
                    if (direction==4) {
                        printf("%s (%d,%d) %s\n", word, j, i,"W");
                        fprintf(puzzleFile, "%s (%d,%d) %s\n", word, j, i,"W");
                        break;
                    }
                    if (direction==5) {
                        printf("%s (%d,%d) %s\n", word, j, i,"E");
                        fprintf(puzzleFile, "%s (%d,%d) %s\n", word, j, i,"E");
                        break;
                    }
                    if (direction==6) {
                        printf("%s (%d,%d) %s\n", word, j, i,"SW");
                        fprintf(puzzleFile, "%s (%d,%d) %s\n", word, j, i,"SW");
                        break;
                    }
                    if (direction==7) {
                        printf("%s (%d,%d) %s\n", word, j, i,"S");
                        fprintf(puzzleFile, "%s (%d,%d) %s\n", word, j, i,"S");
                        break;
                    }
                    if (direction==8) {
                        printf("%s (%d,%d) %s\n", word, j, i,"SE");
                        fprintf(puzzleFile, "%s (%d,%d) %s\n", word, j, i,"SE");
                        break;
                    }
                }
            }
        }
        if(direction!=0) {  //breaks out of first for-loop once word is found
            break;
        }
    }
    if (direction==0) {
        printf("The word \"%s\" was not found.\n", word);
        fprintf(puzzleFile, "The word \"%s\" was not found.\n", word);
        exit(1);
    }
    fclose(puzzleFile);   
}

int looksAround (char *letter, int iValue, int jValue) {
    int i;
    int j;
    int returnValue=0;
    for (i=iValue-1;i<=iValue+1;i++) {
        for (j=jValue-1;j<=jValue+1;j++) {
            if (letter[1]==puzzle[i][j] && (i!=iValue || j!=jValue)) {
                if (i==iValue-1) {
                    if (j==jValue-1) 
                        if (1==NorthWest(letter, i, j))
                            return 1;
                    if (j==jValue) 
                        if (2==North(letter, i, j))
                            return 2;
                    if (j==jValue+1) 
                        if (3==NorthEast(letter, i, j))
                            return 3;
                }
                if (i==iValue) {
                    if (j==jValue-1)
                        if (4==West(letter,i,j))
                            return 4;
                    if (j==jValue+1)
                        if (5==East(letter,i,j))
                            return 5;
                }
                if (i==iValue+1) {
                    if (j==jValue-1)
                        if (6==SouthWest(letter,i,j))
                            return 6;
                    if (j==jValue)
                        if (7==South (letter,i,j))
                            return 7;
                    if (j==jValue+1)
                        if (8==SouthEast(letter,i,j))
                            return 8;
                }
            }
        }
    }
    return returnValue;
}

int NorthWest (char* word, int iValue, int jValue) {
    int index;
    for (index=2;index<strlen(word);index++) {
        iValue--;
        jValue--;
        if (word[index]!=puzzle[iValue][jValue]) {
            return 0;
        }
    }
    return 1;
}

int North (char* word, int iValue, int jValue) {
    int index;
    for (index=2;index<strlen(word);index++) {
        iValue--;
        if (word[index]!=puzzle[iValue][jValue]) {
            return 0;
        }
    }
    return 2;
}

int NorthEast (char *word, int iValue, int jValue) {
    int index;
    for (index=2;index<strlen(word);index++) {
        iValue--;
        jValue++;
        if (word[index]!=puzzle[iValue][jValue]) {
            return 0;
        }
    }
    return 3;
}

int West (char *word, int iValue, int jValue) {
    int index;
    for (index=2;index<strlen(word);index++) {
        jValue--;
        if (word[index]!=puzzle[iValue][jValue]) {
            return 0;
        }
    }
    return 4;
}

int East (char *word, int iValue, int jValue) {
    int index;
    for (index=2;index<strlen(word);index++) {
        jValue++;
        if (word[index]!=puzzle[iValue][jValue]) {
            return 0;
        }
    }
    return 5;
}

int SouthWest (char *word, int iValue, int jValue) {
    int index;
    for (index=2;index<strlen(word);index++) {
        iValue++;
        jValue--;
        if (word[index]!=puzzle[iValue][jValue]) {
            return 0;
        }
    }
    return 6;
}

int South (char *word, int iValue, int jValue) {
    int index;
    for (index=2;index<strlen(word);index++) {
        iValue++;
        if (word[index]!=puzzle[iValue][jValue]) {
            return 0;
        }
    }
    return 7;
}

int SouthEast (char *word, int iValue, int jValue) {
    int index;
    for (index=2;index<strlen(word);index++) {
        iValue++;
        jValue++;
        if (word[index]!=puzzle[iValue][jValue]) {
            return 0;
        }
    }
    return 8;
}


