/* 
 * File:   wordGen.c
 * Author: Leng
 *
 * Created on November 8, 2016, 1:51 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE * Stream;

void printPuzzle (char * puzzleBoard, int size);
void readWords (char * puzzleBoard, char * puzzleWordName, char* puzzleSolName, int size);
void fillIn (int arraySize);

char puzzle[25][25];

/*
 * 
 */
int main(int argc, char** argv) {
    
    int size;
    printf ("Please enter a puzzle size: ");
    scanf ("%d", &size);
    while (size<8 || size>24) {
        printf ("Error: size of puzzle must be between 8 and 24.\n");
        printf ("Please enter a puzzle size: ");
        scanf ("%d", &size);
    }
    puzzle[size][size];
    
    char puzzleWords[20];
    printf("Please enter the puzzle name: ");
    scanf ("%s", puzzleWords);
    while (strlen(puzzleWords)>12) {
        printf("Error: The name of the puzzle is more than 12 characters.\n");
        printf("Please enter the puzzle name: ");
        scanf ("%s", puzzleWords);
    }
    
    srand(2016); 
    char puzzleBoard[20];
    char puzzleSoln[20];
    strcpy(puzzleBoard, puzzleWords);
    strcpy(puzzleSoln, puzzleWords);
    
    strcat(puzzleBoard, ".txt");
    strcat(puzzleWords, "_words.txt");
    strcat(puzzleSoln, "_soln.txt");
    
    FILE * puzzleOutFile;
    puzzleOutFile = fopen(puzzleSoln, "w");
    if (puzzleOutFile == NULL) {
        printf("Error opening %s file.\n", puzzleSoln);
        exit(1);
    }
    
    readWords(puzzleBoard, puzzleWords, puzzleSoln, size);
    fillIn(size);
    printPuzzle(puzzleBoard, size);
    
    return (EXIT_SUCCESS);
}

void printPuzzle (char * puzzleBoard, int size){
    FILE * puzzleFile = fopen(puzzleBoard, "w");
    int i;
    int j;
    printf("\nPuzzle Board: \n");
    fprintf(puzzleFile, "%d\n", size);
    for (i=0;i<size;i++) {
        for (j=0;j<size;j++) {
            printf("%c ", puzzle[i][j]);
            fprintf(puzzleFile, "%c ", puzzle[i][j]);
        }
        printf("\n");
        fprintf(puzzleFile, "\n");
    }
    printf("\n");
    fclose(puzzleFile);
}

void readWords (char * puzzleBoard, char * puzzleWordName, char* puzzleSolName, int size) {
    FILE * puzzleFile;
    puzzleFile = fopen(puzzleWordName, "r");
    if (puzzleFile == NULL) {
        printf("Error opening %s file.\n", puzzleWordName);
        exit(1);
    }
    FILE * puzzleOutFile;
    puzzleOutFile = fopen(puzzleSolName, "a");
    if (puzzleFile == NULL) {
        printf("Error opening %s file.\n", puzzleSolName);
        exit(1);
    }
    int direction;
    int complete;
    int attempt; //each word is attempted only 25 times to prevent possible infinite while loop
    char word [24];
    //fscanf(puzzleFile, "%s", word);
    //startPosition(word,5,size);
    while (fscanf(puzzleFile, "%s", word)!=EOF) {
        if (strlen(word)>size) {
            printf("The word \"%s\" is too large to fit in the puzzle.\n", word);
            fprintf(puzzleOutFile, "The word \"%s\" is too large to fit in the puzzle.\n", word);
            fillIn(size);
            printPuzzle(puzzleBoard, size);
            exit(1);
        }
        attempt=0;
        complete=0;
        while (complete==0 && attempt<25) {
            direction = 1 + rand() % 8;
            complete = startPosition(puzzleSolName, word, direction, size);
            attempt++;
        }
        if (complete==0) {
            printf("Error: Attempting to insert too many words in a small puzzle.\n"
                   "The word \"%s\" was not inserted into the puzzle.\n", word);
            fprintf(puzzleOutFile, "Error: Attempting to insert too many words in a small puzzle.\n"
                   "The word \"%s\" was not inserted into the puzzle.\n", word);
            fillIn(size);
            printPuzzle(puzzleBoard, size);
            exit(1);
        }
    }
    fclose(puzzleFile);
    fclose(puzzleOutFile);
}

int startPosition (char*puzzleSolName, char* word, int direction, int size) {
    FILE * puzzleOutFile;
    puzzleOutFile = fopen(puzzleSolName, "a");
    if (puzzleOutFile == NULL) {
        printf("Error opening %s file.\n", puzzleSolName);
        exit(1);
    }
    int arraySize = size;
    int wordSize = strlen(word);
    int complete=0;
    int attempt=0;  //each direction is attempted only 25 times to prevent possible infinite while loop
    int i=0;
    int j=0;
    int iValue;
    int jValue;
    if (direction==1) { //NW
        while (complete==0 && attempt<25) {
            iValue = (rand() % arraySize) + (wordSize-1);
            if (iValue<arraySize) {
                jValue = (rand() % arraySize) + (wordSize-1);
                if (jValue<arraySize) {
                    complete = NorthWest(word,iValue,jValue);
                    attempt++;
                }
            }
        }
        if (complete==1) {
            printf("%s (%d,%d) %s\n", word, jValue,iValue, "NW");
            fprintf(puzzleOutFile, "%s (%d,%d) %s\n", word, jValue,iValue, "NW");
            fclose(puzzleOutFile);
            return 1;
        }
    }
    if (direction==2) { //N
        while (complete==0 && attempt<25) {
            iValue = (rand() % arraySize) + (wordSize-1);
            if (iValue<arraySize) {
                jValue = rand() % arraySize;
                complete = North(word,iValue,jValue);
                attempt++;
            }
        }
        if (complete==1) {
            printf("%s (%d,%d) %s\n", word, jValue,iValue, "N");
            fprintf(puzzleOutFile, "%s (%d,%d) %s\n", word, jValue,iValue, "N");
            fclose(puzzleOutFile);
            return 1;
        }
    }
    if (direction==3) { //NE
        while (complete==0 && attempt<25) {
            iValue = (rand() % arraySize) + (wordSize-1);
            if (iValue<arraySize) {
                jValue = (rand() % (1+arraySize)) - wordSize;
                if (jValue>=0) {
                    complete = NorthEast(word,iValue,jValue);
                    attempt++;
                }
            }
        }
        if (complete==1) {
            printf("%s (%d,%d) %s\n", word, jValue,iValue, "NE");
            fprintf(puzzleOutFile, "%s (%d,%d) %s\n", word, jValue,iValue, "NE");
            fclose(puzzleOutFile);
            return 1;
        }
    }
    if (direction==4) { //W
        while (complete==0 && attempt<25) {
            jValue = (rand() % arraySize) + (wordSize-1);
            if (jValue<arraySize) {
                iValue = rand() % arraySize;
                complete = West(word,iValue,jValue);
                attempt++;
            }
        }
        if (complete==1) {
            printf("%s (%d,%d) %s\n", word, jValue,iValue, "W");
            fprintf(puzzleOutFile, "%s (%d,%d) %s\n", word, jValue,iValue, "W");
            fclose(puzzleOutFile);
            return 1;
        }
    }
    if (direction==5) { //E
        while (complete==0 && attempt<25) {
            jValue = (rand() % (1+arraySize)) - wordSize;
            if (jValue>=0) {
                iValue = rand() % arraySize;
                complete = East(word,iValue,jValue);
                attempt++;
            }   
        }
        if (complete==1) {
            printf("%s (%d,%d) %s\n", word, jValue,iValue, "E");
            fprintf(puzzleOutFile, "%s (%d,%d) %s\n", word, jValue,iValue, "E");
            fclose(puzzleOutFile);
            return 1;
        }
    }
    if (direction==6) { //SW
        while (complete==0 && attempt<25) {
            iValue = (rand() % (1+arraySize)) - wordSize;
            if (iValue>=0) {
                jValue = (rand() % arraySize) + (wordSize-1);
                if (jValue<arraySize) {
                    complete = SouthWest(word,iValue,jValue);
                    attempt++;
                }
            }
        }
        if (complete==1) {
            printf("%s (%d,%d) %s\n", word, jValue,iValue, "SW");
            fprintf(puzzleOutFile, "%s (%d,%d) %s\n", word, jValue,iValue, "SW");
            fclose(puzzleOutFile);
            return 1;
        }
    }
    if (direction==7) { //S
        while (complete==0 && attempt<25) {
            iValue = (rand() % (1+arraySize)) - wordSize;
            if (iValue>=0) {
                jValue = rand() % arraySize;
                complete = South(word,iValue,jValue);
                attempt++;
            }
        }
        if (complete==1) {
            printf("%s (%d,%d) %s\n", word, jValue,iValue, "S");
            fprintf(puzzleOutFile, "%s (%d,%d) %s\n", word, jValue,iValue, "S");
            fclose(puzzleOutFile);
            return 1;
        }
    }
    if (direction==8) { //SE
        while (complete==0 && attempt<25) {
            iValue = (rand() % (1+arraySize)) - wordSize;
            if (iValue>=0) {
                jValue = (rand() % (1+arraySize)) - wordSize;
                if (jValue>=0) {
                    complete = SouthEast(word,iValue,jValue);
                    attempt++;
                }
            }
        }
        if (complete==1) {
            printf("%s (%d,%d) %s\n", word, jValue,iValue, "SE");
            fprintf(puzzleOutFile, "%s (%d,%d) %s\n", word, jValue,iValue, "SE");
            fclose(puzzleOutFile);
            return 1;
        }
    }
    return 0;
}

void fillIn (int arraySize) {
    int i;
    int j;
    char randChar;
    for (i=0;i<arraySize;i++) {
        for (j=0;j<arraySize;j++) {
            if (puzzle[i][j] == '\0') {
                randChar = 97 + rand() % (122-97+1);
                puzzle[i][j] = randChar;
            }
        }
    }
}

int NorthWest (char* word, int iValue, int jValue) {
    int index;
    int i=iValue;
    int j=jValue;
    int size = strlen(word);
    for (index=0;index<size;index++) {
        if (puzzle[iValue][jValue]!='\0' && puzzle[iValue][jValue]!=word[index])
            return 0;
        iValue--;
        jValue--;
    }
    iValue = i;
    jValue = j;
    for (index=0;index<size;index++) {
        puzzle[iValue][jValue] = word[index];
        iValue--;
        jValue--;
    }
    return 1;
}

int North (char* word, int iValue, int jValue) {
    int index;
    int i=iValue;
    int j=jValue;
    int size = strlen(word);
    for (index=0;index<size;index++) {
        if (puzzle[iValue][jValue]!='\0' && puzzle[iValue][jValue]!=word[index])
            return 0;
        iValue--;
    }
    iValue = i;
    for (index=0;index<size;index++) {
        puzzle[iValue][jValue] = word[index];
        iValue--;
    }
    return 1;
}

int NorthEast (char *word, int iValue, int jValue) {
    int index;
    int i=iValue;
    int j=jValue;
    int size = strlen(word);
    for (index=0;index<size;index++) {
        if (puzzle[iValue][jValue]!='\0' && puzzle[iValue][jValue]!=word[index])
            return 0;
        iValue--;
        jValue++;
    }
    iValue = i;
    jValue = j;
    for (index=0;index<size;index++) {
        puzzle[iValue][jValue] = word[index];
        iValue--;
        jValue++;
    }
    return 1;
}

int West (char *word, int iValue, int jValue) {
    int index;
    int i=iValue;
    int j=jValue;
    int size = strlen(word);
    for (index=0;index<size;index++) {
        if (puzzle[iValue][jValue]!='\0' && puzzle[iValue][jValue]!=word[index])
            return 0;
        jValue--;
    }
    jValue = j;
    for (index=0;index<size;index++) {
        puzzle[iValue][jValue] = word[index];
        jValue--;
    }
    return 1;
}

int East (char *word, int iValue, int jValue) {
    int index;
    int i=iValue;
    int j=jValue;
    int size = strlen(word);
    for (index=0;index<size;index++) {
        if (puzzle[iValue][jValue]!='\0' && puzzle[iValue][jValue]!=word[index])
            return 0;
        jValue++;
    }
    jValue = j;
    for (index=0;index<size;index++) {
        puzzle[iValue][jValue] = word[index];
        jValue++;
    }
    return 1;
}

int SouthWest (char *word, int iValue, int jValue) {
    int index;
    int i=iValue;
    int j=jValue;
    int size = strlen(word);
    for (index=0;index<size;index++) {
        if (puzzle[iValue][jValue]!='\0' && puzzle[iValue][jValue]!=word[index])
            return 0;
        iValue++;
        jValue--;
    }
    iValue = i;
    jValue = j;
    for (index=0;index<size;index++) {
        puzzle[iValue][jValue] = word[index];
        iValue++;
        jValue--;
    }
    return 1;
}

int South (char *word, int iValue, int jValue) {
    int index;
    int i=iValue;
    int j=jValue;
    int size = strlen(word);
    for (index=0;index<size;index++) {
        if (puzzle[iValue][jValue]!='\0' && puzzle[iValue][jValue]!=word[index])
            return 0;
        iValue++;
    }
    iValue = i;
    for (index=0;index<size;index++) {
        puzzle[iValue][jValue] = word[index];
        iValue++;
    }
    return 1;
}

int SouthEast (char *word, int iValue, int jValue) {
    int index;
    int i=iValue;
    int j=jValue;
    int size = strlen(word);
    for (index=0;index<size;index++) {
        if (puzzle[iValue][jValue]!='\0' && puzzle[iValue][jValue]!=word[index])
            return 0;
        iValue++;
        jValue++;
    }
    iValue = i;
    jValue = j;
    for (index=0;index<size;index++) {
        puzzle[iValue][jValue] = word[index];
        iValue++;
        jValue++;
    }
    return 1;
}