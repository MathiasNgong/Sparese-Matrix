/*
 *  Created on: Dec 22, 2020
 *      Author: kompalli
 */
#include "SparseMatrix.h"

int extractDimension(char str[]){
    int index=5;
    int indexTmp=0;
    char nString[13]="\0\0\0\0\0\0\0\0\0\0\0\0";
    while (str[index] >= '0' && str[index] <= '9') {
    nString[indexTmp]=str[index];
    index++;
    indexTmp++;
    }
    return atoi (nString); 
}


void extractData(char str[], int &x, int &y, int &number){
    int index=1; 
    int indexTmp=0;
    
    char xString[13]="\0\0\0\0\0\0\0\0\0\0\0\0";
    while(str[index]==' ' |str[index]=='\t'  )
        index++;
    while (str[index] >= '0' && str[index] <= '9') {
    xString[indexTmp]=str[index];
    index++;
    indexTmp++;
    }
    x=atoi(xString);
    indexTmp=0;
    char yString[13]="\0\0\0\0\0\0\0\0\0\0\0\0";
    while(str[index]==',' | str[index]==' ' |str[index]=='\t'  )
        index++;
    while (str[index] >= '0' && str[index] <= '9') {
    yString[indexTmp]=str[index];
    index++;
    indexTmp++;
    }
    y=atoi(yString);
    
    indexTmp=0;
    char nString[13]="\0\0\0\0\0\0\0\0\0\0\0\0";
    while(str[index]==',' | str[index]==' ' |str[index]=='\t'  )
        index++;
    if (str[index]='-') {
        nString[indexTmp]=str[index];
        index++;
        indexTmp++;
    }
    while (str[index] >= '0' && str[index] <= '9') {
    nString[indexTmp]=str[index];
    index++;
    indexTmp++;
    }
    number=atoi(nString);
}

SparseMatrix::SparseMatrix(char* matrixFilePath){
	FILE* inFileStream = fopen(matrixFilePath, "r");
	if (! inFileStream){
		char* message = new char[2048];
		sprintf(message, "Cannot open input file for reading");
		throw std::ios_base::failure(message);
		delete []message;
	}
	LogManager::writePrintfToLog(LogManager::Level::Status, "SparseMatrix::SparseMatrix",
			"Loading input file: %s", matrixFilePath);



	char line[255];
	int currRow1,currCol1,currVal1;
	int count=0;
	
	
			fgets(line, 255, inFileStream);
			rows=extractDimension(line);
			count++; 		
	

			fgets(line, 255, inFileStream);
			cols=extractDimension(line);
			count++; 

			myMatrix=new int [rows*cols]();
			// for (int i = 0; i < (rows * cols); i++) myMatrix[i] = 0;
		std::cout<<" rows : "<< rows<<" cols : "<< cols<<std::endl;
	

	while(!feof(inFileStream)){
		
		
			fgets(line, 255, inFileStream);
			extractData(line,currRow1,currCol1,currVal1);
			setElement(currRow1,currCol1,currVal1);
			count++; 
			std::cout<<" rows : "<< currRow1<<" cols : "<< currCol1<< " value : "<<currVal1<< " gotten : "<<getElement(currRow1,currCol1)<< std::endl;
		}
		
		
	
	
}

void SparseMatrix::printToASCIIFile(char* outputFileName){
	FILE* outFileStream = fopen(outputFileName, "w");
	if (! outFileStream){
		char* message = new char[2048];
		sprintf(message, "Cannot open output file for writing");
		throw std::ios_base::failure(message);
		delete []message;
	}
	LogManager::writePrintfToLog(LogManager::Level::Status, "SparseMatrix::printToASCIIFile",
			"Writing matrix to file: %s", outputFileName);
	fprintf(outFileStream, "rows=%d\n", rows);
	fprintf(outFileStream, "cols=%d\n", cols);
	int value;
	for (int currRow = 0; currRow < rows; currRow++)
		for (int currCol = 0; currCol < cols; currCol++){
			value = getElement(currRow, currCol);
			if (value != 0){
				fprintf(outFileStream, "(%d, %d, %d)\n", currRow, currCol, value);
			}
		}
}

SparseMatrix SparseMatrix::operator+ (SparseMatrix  &inputObject)  {
	if (inputObject.rows != rows){
		char* message = new char[2048];
		sprintf(message, "Number of rows are not same");
		throw std::invalid_argument(message);
		delete []message;
	}
	if (inputObject.cols != cols){
		char* message = new char[2048];
		sprintf(message, "Number of cols are not same");
		throw std::invalid_argument(message);
		delete []message;
	}

	SparseMatrix resultMat(inputObject.rows, inputObject.cols);

	int value;

	for (int currRow = 0; currRow < inputObject.rows; currRow++)
		for (int currCol = 0; currCol < inputObject.cols; currCol++){
			value = getElement(currRow, currCol) + inputObject.getElement(currRow, currCol);
			resultMat.setElement(currRow, currCol, value);
		}
	return resultMat;
}


SparseMatrix SparseMatrix::operator- (SparseMatrix  &inputObject)   {
	if (inputObject.rows != rows){
		char* message = new char[2048];
		sprintf(message, "Number of rows are not same");
		throw std::invalid_argument(message);
		delete []message;
	}
	if (inputObject.cols != cols){
		char* message = new char[2048];
		sprintf(message, "Number of cols are not same");
		throw std::invalid_argument(message);
		delete []message;
	}

	SparseMatrix resultMat(inputObject.rows, inputObject.cols);
	int value;

	for (int currRow = 0; currRow < inputObject.rows; currRow++)
		for (int currCol = 0; currCol < inputObject.cols; currCol++){
			value = getElement(currRow, currCol) - inputObject.getElement(currRow, currCol);
			resultMat.setElement(currRow, currCol, value);
		}
	return resultMat;
}


SparseMatrix SparseMatrix::operator* (SparseMatrix  &inputObject)  {
	if (inputObject.rows != cols){
		char* message = new char[2048];
		sprintf(message, "Input does not satisfy following condition: Number of rows in second matrix must be equal to num of cols in first matrix");
		throw std::invalid_argument(message);
		delete []message;
	}
	if (inputObject.cols != rows){
		char* message = new char[2048];
		sprintf(message, "Input does not satisfy following condition: Number of cols in second matrix must be equal to num of rows in first matrix");
		throw std::invalid_argument(message);
		delete []message;
	}

	/**
	 * In matrix multiplication, number of rows in the result is equal to number of rows in first matrix.
	 * number of cols in the result is equal to number of cols in first matrix.
	 */
	SparseMatrix resultMat(rows, inputObject.cols);
	int value;

for (int i = 0; i < rows; i++)
    for (int k = 0; k < cols; k++)
    {
        value = getElement(i, k);
        if (value != 0)
        for (int j = 0; j < resultMat.cols; j++)
        {   
             int val = resultMat.getElement(i, j) + (value * inputObject.getElement(k, j));
             resultMat.setElement(i, j, val);
        }
    }    
	return resultMat;
}


void SparseMatrixTester::generateTestCases(char* outputFolderPath){
	
}


void SparseMatrixTester::generateTestCases(char* outputFilePath, int min, int max, int numRows, int numCols){
}