#include<stdlib.h>
#include<stdio.h>
// AI/ML
/*	How to malloc an array
	double** data = malloc(row * sizeof(double*));
	for(int i = 0; i < col; i++){
		data[i] = malloc(col*sizeof(double*));
	}
*/
double** allocate_matrix(int, int);
void free_matrix(int, int, double**);
double** weightCalc(double**,double**, int, int);
double** transposeCalc(double**, int, int);
double** matrixMultiplication(double**,int, int, double**, int, int);
double** inverseCalc(double**, int, int);
double** augmentedMatrix(double**, int, int);


double** weightCalc(double** trainingMatrix, double** pricesMatrix, int k, int n){
	return matrixMultiplication(matrixMultiplication(inverseCalc(augmentedMatrix(matrixMultiplication(transposeCalc(trainingMatrix, k, n), k+1, n, trainingMatrix, n, k+1), k,n), k, n), k+1, k+1, transposeCalc(trainingMatrix, k, n), k+1, n), k+1, n, pricesMatrix,n,1);

}
double** inverseCalc(double** augmentedMatrix, int k, int n){
	//divide to get 1 for first row
	double constant;
	constant = augmentedMatrix[0][0];
	for(int j = 0; j < (k+1)*2; j++){
		augmentedMatrix[0][j] = augmentedMatrix[0][j] / constant;
	}
	
	
	//ROW ECHELON FORM	
	for(int i = 0; i < k+1; i++){ //counts rows
		for(int j = 0; j <= i; j++){ //counts columns, but doesn't go to identity matrix column, stop right before last column
			double constant = 0;
			if(i == j){
				constant = 1/(augmentedMatrix[i][j]);	
			}
			else{ //if negative
				constant = (-1)*augmentedMatrix[i][j];
	
			}
			for(int r = 0; r < (k+1)*2; r++){ //counts columns for multiplying through
				//find row to divide by - [j][r]
				if(i!=j){
					augmentedMatrix[i][r] = augmentedMatrix[j][r]*constant + augmentedMatrix[i][r];
				}else{
					augmentedMatrix[i][r] = constant*augmentedMatrix[i][r];
				}
				
			}

		}

	}

	//REDUCED ROW ECHELON FORM

	for(int i = 0; i < k+1; i ++){ //counts rows
		
		for(int j = i+1; j < ((k+1)*2)/2; j++){ //counts columns
			
			double constant = (-1)*augmentedMatrix[i][j];

			for(int r = 0; r < (k+1)*2; r++){
				augmentedMatrix[i][r] = constant*augmentedMatrix[j][r] + augmentedMatrix[i][r];

			}

		}

	}
	
	//Print augmented matrix

	/*printf("Inverse with Augment\n");
	for(int i = 0; i < k+1; i ++){
		for(int j = 0; j < (k+1)*2; j++){
			printf("%lf	", augmentedMatrix[i][j]);
		}
		printf("\n");
	}*/

	//copy augmented matrix part into new inverse matrix
	double** inverseMatrix;
	inverseMatrix = allocate_matrix(k+1, k+1);

	for(int i = 0; i < k+1; i ++){ //counts rows of inverseMatrix
		int s=k+1;
		for(int j = 0; j < k+1; j++){ //counts columns of inverseMatrix
			inverseMatrix[i][j] = augmentedMatrix[i][s];
			s++;
		}
	}

	//print inverse
	
	/*printf("Just Inverse\n");

	for(int i = 0; i < k+1; i++){
		for(int j = 0; j < k+1; j++){
			printf("%lf	", inverseMatrix[i][j]);
		}
		printf("\n");
	}*/
	
	return inverseMatrix;
}

double** augmentedMatrix(double** multipliedMatrix, int k, int n){ //k are rows, n are columns, but really k+1 rows

	double** augmentedMatrix;
	augmentedMatrix = allocate_matrix(k+1, (k+1)*2); //augment with identity matrix
	for(int i = 0; i < k+1; i++){
		for(int j = 0; j < (k+1)*2; j++){
			if(j < (k+1)){
				augmentedMatrix[i][j] = multipliedMatrix[i][j];
			}else{
				augmentedMatrix[i][j] = 0;
			}
		}
		augmentedMatrix[i][k+1+i] = 1;
	}

	/*printf("Augmented Matrix\n");
	for(int i = 0; i < k+1; i ++){
		for(int j = 0; j < (k+1)*2; j++){
			printf("%lf	", augmentedMatrix[i][j]);
		}
		printf("\n");
	}

	printf("END OF AUGMENTED MATRIX\n");*/

	return augmentedMatrix;
}

double** transposeCalc(double** trainingMatrix, int k, int n){
	double** transposed;
	transposed = allocate_matrix(k+1, n);
	for(int i = 0; i <n; i++){
		for(int j = 0; j < k+1; j++){
			transposed[j][i] = trainingMatrix[i][j];
		}
	}

	/*printf("Transposed Matrix\n");
	for(int i = 0; i < k+1; i ++){
		for(int j = 0; j < n; j++){
			printf("%lf	", transposed[i][j]);
		}
		printf("\n");
	}*/


	return transposed;
}

double** matrixMultiplication(double** firstMatrix,int firstRow, int firstColumn, double** secondMatrix, int secondRow, int secondColumn){
	double** answerMatrix;
	answerMatrix = allocate_matrix(firstRow, secondColumn);
	//printf("ROWS: %d, COLUMNS: %d", firstRow, secondColumn);

	//populate answer matrix with 1s

	for(int i = 0; i < firstRow; i ++){
		for(int j = 0; j < secondColumn; j++){
			answerMatrix[i][j] = 0;
		}
	}
	
	/*int tempSum = 0;
	for(int i = 0 ; i < firstRow; i++){
		for(int j = 0; j < secondColumn; j++){
			for(int s = 0; s < firstColumn; s++){ //secondRow
				tempSum = firstMatrix[i][s]*secondMatrix[s][j];
				answerMatrix[i][j] = answerMatrix[i][j] + tempSum;
			}
		}
	}*/

	for(int i=0; i<firstRow; ++i){
        	for(int j=0; j<secondColumn; ++j){
           		for(int k=0; k<firstColumn; ++k){
            		
               			 answerMatrix[i][j]+=firstMatrix[i][k]*secondMatrix[k][j];
           		 }
		}
	}

	/*printf("Multiplied Matrix\n");
	for(int i = 0; i < firstRow; i ++){
		for(int j = 0; j < secondColumn; j++){
			printf("%lf	", answerMatrix[i][j]);
		}
		printf("\n");
	}
	printf("HIIIIII\n");*/
	
	return answerMatrix;

}

double** allocate_matrix(int rows, int columns){
	double** returnValue = malloc(rows*sizeof(double*));
	for(int i = 0; i < rows; i++){
		returnValue[i] = malloc(columns * sizeof(double));
	}
	return returnValue;
}

void free_matrix (int rows, int columns, double** matrix){
	for(int i = 0; i < rows; i ++){
		free(matrix[i]);
	}
	free(matrix);
}

int main (int argc, char ** argv){
	//training data set

	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("File does not exist\n");
		exit(0);
	}
	int k; //number of attributes
	int n; //number of training examples 
	fscanf(fp, "%d", &k);
	fscanf(fp, "%d", &n);

	double** trainingMatrix; //X
	trainingMatrix = allocate_matrix(n,k+1);
	//make 0 column
	for(int a = 0; a < n; a++){
		trainingMatrix[a][0] = 1;
	}
	//populate matrix
	double temp;
	for(int i = 0; i < n; i++){  //counts rows in matrix
		
		if(i != 0){
			fscanf(fp, "%lf", &temp);
		}
		for(int j = 0; j < (k+1); j++){ //counts columns in matrix
			if(j == 0){
				j++;
				fscanf(fp, "%lf,", &trainingMatrix[i][j]);
				
			}
			else{
				fscanf(fp, "%lf,", &trainingMatrix[i][j]);
				
			}
		}
	}			
	
	fclose(fp); //close training data


	//print training Matrix


	double** pricesMatrix; //Y
	double** weightsMatrix; //W
	pricesMatrix = allocate_matrix(n,1);
	weightsMatrix = allocate_matrix(k+1,1);
	
	//fill in pricesMatrix
	
	FILE* prices = fopen(argv[1], "r");
	fscanf(prices, "%lf,", &temp);
	fscanf(prices, "%lf,", &temp);
	
		for(int j = 0; j < n; j++){ //row 
			for(int r = 0; r < k+1; r++){
				if(r == k){
					
					fscanf(prices, "%lf", &pricesMatrix[j][0]);
				}else{
					fscanf(prices, "%lf,", &temp);
				} 
			}
		}
	//}
	fclose(prices);

	//print pricesMatrix
	/*printf("Y MATRIX\n");
	for(int i = 0; i < n; i++){
		printf("%lf\n", pricesMatrix[i][0]);
	}

	printf("TRAINING MATRIX(x)\n");
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < (k+1); j++){
			printf("%lf	", trainingMatrix[i][j]);
		}
		printf("\n");
	}
*/
	//calculate weights
	//weightCalc(trainingMatrix, pricesMatrix, weightsMatrix);
	//transposeCalc(trainingMatrix,k,n);
	//matrixMultiplication(transposeCalc(trainingMatrix,k,n), k+1, n, trainingMatrix, n, k+1);
	//inverseCalc(augmentedMatrix(matrixMultiplication(transposeCalc(trainingMatrix,k,n), k+1, n, trainingMatrix, n, k+1), k,n), k, n);
	
	weightsMatrix = weightCalc(trainingMatrix,pricesMatrix,k,n);

	/*printf("WEIGHTS MATRIX\n");
	for(int i = 0; i < k+1;i++){
		printf("%lf\n", weightsMatrix[i][0]);
	}*/

	

	//test data
	FILE* read = fopen(argv[2], "r");
	if(read == NULL){
		printf("File does not exist\n");
		exit(0);
	}
	double m; //number of test data points
	fscanf(read, "%lf", &m);

	//test data evaluation
	
	//printf("FINAL ANSWER!!!!!\n");

	double** testMatrix;
	testMatrix = allocate_matrix(m,k);
	
	for(int j = 0; j < m; j++){ //row 
		for(int r = 0; r < k; r++){
				
			fscanf(read, "%lf,", &testMatrix[j][r]);
		} 
	}
	for(int i = 0; i < m; i++){
		double sum = weightsMatrix[0][0];
		for(int j = 0; j < k; j++){
			sum+=testMatrix[i][j]*weightsMatrix[j+1][0];
		}
		printf("%0.0lf\n", sum);
	}

	
	
	fclose(read); //close test data

	
	free_matrix(n, k+1, trainingMatrix);
	free_matrix(k+1,1, weightsMatrix);
	free_matrix(n,1,pricesMatrix);
	free_matrix(m,k,testMatrix);
	return 0;
}