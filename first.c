#include<stdlib.h>
#include<stdio.h>
// Hexadoku
char** allocate_matrix(int, int);
void free_matrix(int, int, char**);
int checkRow(char**, int, char);
int checkColumn(char**, int, char);
int checkSquare(char**, int, char);
int checkEverything(char**,int, int, int, char);
int findSquare(int, int);
int checkIfValid(char**);

int checkIfValid(char** originalMatrix){
	int answer = 0;
	char indexArray[16] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9','A','B','C', 'D', 'E', 'F'};
	for(int a = 0; a < 16; a++){ //indexArrayCounter
		for(int i = 0; i < 16; i++){ //rowCounter
					int counter = 0;
			for(int j = 0; j < 16; j++){ //columnCounter
				if(originalMatrix[i][j] == indexArray[a]){
					counter++;
					if (counter > 1){
						//printf("Counter(row), character %c\n", indexArray[a]);
						answer = 1;
					}
				}
			}
		}

		for(int r = 0; r < 16; r++){ //ColumnCounter
			int counter2 = 0;
			for(int s = 0; s < 16; s++){ //rowCounter
				if(originalMatrix[s][r] == indexArray[a]){
					counter2++;
					if(counter2 > 1){
						//printf("Counter2(column), character %c\n", indexArray[a]);
						answer = 1;
					}
				}
			}
		}
		
		
		
	}
	
	return answer;
}

	


int findSquare(int rowNumber, int columnNumber){
	int square;
	if(columnNumber == 0 || columnNumber == 1 || columnNumber == 2 || columnNumber == 3){
		if(rowNumber == 0 || rowNumber == 1 || rowNumber == 2 || rowNumber == 3){
			square = 1;
		}
		else if(rowNumber == 4 || rowNumber == 5 || rowNumber == 6 || rowNumber == 7){
			square = 5;
		}
		else if(rowNumber == 8 || rowNumber == 9 || rowNumber == 10 || rowNumber == 11){
			square = 9;
		}
		else{
			square = 13;
		}
	}

	else if(columnNumber == 4 || columnNumber == 5 || columnNumber == 6 || columnNumber == 7){
		if(rowNumber == 0 || rowNumber == 1 || rowNumber == 2 || rowNumber == 3){
			square = 2;
		}
		else if(rowNumber == 4 || rowNumber == 5 || rowNumber == 6 || rowNumber == 7){
			square = 6;
		}
		else if(rowNumber == 8 || rowNumber == 9 || rowNumber == 10 || rowNumber == 11){
			square = 10;
		}
		else{
			square = 14;
		}
	}

	else if(columnNumber == 8 || columnNumber == 9 || columnNumber == 10 || columnNumber == 11){
		if(rowNumber == 0 || rowNumber == 1 || rowNumber == 2 || rowNumber == 3){
			square = 3;
		}
		else if(rowNumber == 4 || rowNumber == 5 || rowNumber == 6 || rowNumber == 7){
			square = 7;
		}
		else if(rowNumber == 8 || rowNumber == 9 || rowNumber == 10 || rowNumber == 11){
			square = 11;
		}
		else{
			square = 15;
		}
	}

	else{
		if(rowNumber == 0 || rowNumber == 1 || rowNumber == 2 || rowNumber == 3){
			square = 4;
		}
		else if(rowNumber == 4 || rowNumber == 5 || rowNumber == 6 || rowNumber == 7){
			square = 8;
		}
		else if(rowNumber == 8 || rowNumber == 9 || rowNumber == 10 || rowNumber == 11){
			square = 12;
		}
		else{
			square = 16;
		}
	}

	return square;
}

int checkEverything(char** originalMatrix, int rowNumber, int columnNumber, int squareNumber, char target){
	int answer = 0; //not present all the way
	if(checkRow(originalMatrix,rowNumber,target) == 1){ //present in row
		if(checkColumn(originalMatrix,columnNumber, target) == 1){
			if(checkSquare(originalMatrix,squareNumber, target)==1){
				answer = 1; // present all the way
			}
		}
	}
	return answer;	
}

int checkRow(char** originalMatrix, int rowNumber, char target){
	//int actualRow = rowNumber -1;
	int answer = 0; //not present
	for(int j = 0; j < 16; j++){
		if(originalMatrix[rowNumber][j] == target){
			answer = 1; //present
		}
	}
	return answer;
}

int checkColumn(char** originalMatrix, int columnNumber, char target){
	//int actualCol = columnNumber - 1;
	int answer = 0; //not present
	for(int i = 0; i < 16; i++){
		if(originalMatrix[i][columnNumber] == target){
			answer = 1; //present
		}
	} 
	return answer;
}

int checkSquare(char** originalMatrix, int squareNumber, char target){ //across
	int answer = 0; //not present
	int starter;
	int rowStarter;
	if(squareNumber<=4){
		starter = 0;
		rowStarter = 0;
	}else if(squareNumber <= 8){
		starter = 4;
		rowStarter = 4;
	}else if(squareNumber <= 12){
		starter = 8;
		rowStarter = 8;
	}else{
		starter = 12;
		rowStarter = 12;
	}
	int counter = squareNumber;

	while(counter > 1){
		if(starter <= 12){
			starter = starter + 4;
		}else{
			starter = 0;
		}
		counter--;
	}

	for(int i = rowStarter; i < rowStarter + 4; i++){
		for(int j = starter; j < starter + 4; j++){
			char check = originalMatrix[i][j];
			if(check == target){
				answer = 1;
			}
		}
	}
	return answer;
}

char** allocate_matrix(int rows, int columns){
	char** returnValue = malloc(rows*sizeof(int*));
	for(int i = 0; i < rows; i++){
		returnValue[i] = malloc(columns * sizeof(int));
	}
	return returnValue;
}

void free_matrix (int rows, int columns, char** matrix){
	for(int i = 0; i < rows; i ++){
		free(matrix[i]);
	}
	free(matrix);
}
int main (int argc, char ** argv){
	char indexArray[16] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9','A','B','C', 'D', 'E', 'F'};
	char** originalMatrix;
	originalMatrix = allocate_matrix(16,16);
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("File does not exist\n");
		exit(0);
	}
	for(int i = 0; i < 16; i ++){
		for(int j = 0; j < 16; j++){
			fscanf(fp, "%c\n", &originalMatrix[i][j]);
			//printf("%c	", originalMatrix[i][j]);
		}
		//printf("\n");
	}
	fclose(fp);
	if(checkIfValid(originalMatrix) == 0){ //valid
		//will go by rows
		//check for empty squares in row
		for(int i = 0; i < 16; i++){ //row counter
			//printf("HI i = %d\n", i);
			
			int j = 0;
			while(j < 16){
				int blankCounter = 0; //uncomment
				//printf("SECOND HI\n");
				if(checkRow(originalMatrix,i,indexArray[j]) == 0){ //not there, check for blank
						while(blankCounter < 16){
							//printf("THIRD HI\n");
							if(originalMatrix[i][blankCounter] == '-'){
								//printf("FOURTH HI\n");
								if(checkColumn(originalMatrix,blankCounter,indexArray[j]) == 0){ //not in column either
									int square = findSquare(i,blankCounter);
									//printf("FIFTH HI\n");
									if(checkSquare(originalMatrix, square, indexArray[j]) == 0){
										if(checkRow(originalMatrix,i,indexArray[j]) == 0){
											//printf("LAST\n");
											originalMatrix[i][blankCounter] = indexArray[j];
											/*printf("Just changed ");
											printf("%d ", i);
											printf("%d ", blankCounter);
											printf("to ");
											printf("%c\n", indexArray[j]);*/
										}
									}

			   					}

							}
							blankCounter++;
						}
					}
				j++;

				}
		}

		
		//int ans = checkSquare(originalMatrix, 16, 'B');

		for(int r = 0; r < 16; r++){
			for(int s = 0; s < 16; s++){
				printf("%c	", originalMatrix[r][s]);
			}
			printf("\n");
		}
	}
	else{
		printf("no-solution\n");
		//printf("answer is %d\n", checkIfValid(originalMatrix));
	}
	//printf("%d\n", ans);
	free_matrix(16,16,originalMatrix);
	return 0;
}