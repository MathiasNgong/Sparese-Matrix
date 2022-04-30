/*
 * homework.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: kompalli
 */

#include "homework.h"

int main(int argc, char** argv) {
	LogManager::resetLogFile();
	LogManager::writePrintfToLog(LogManager::Level::Status, "main", "In main file.");
	printf("Usage:\n\n");
	printf("./homework addn pathToMatrix1   pathToMatrix2\n\n");
	printf("./homework mult pathToMatrix1   pathToMatrix2\n\n");
	printf("./homework subt pathToMatrix1   pathToMatrix2\n\n");

	int peakMem1 = getPeakRSS();
	int currMem1 = getCurrentRSS();
	printf("peakRSS = %d, currMem=%d\n", peakMem1, currMem1);
	printf("sizeof(bool) = %d \n", (int)sizeof(bool));
	printf("sizeof(int) = %d \n", (int)sizeof(int));
	printf("sizeof(char) = %d \n", (int)sizeof(char));
	printf("INT_MIN = %d, INT_MAX =%d\n", INT_MIN, INT_MAX);

	auto start = std::chrono::high_resolution_clock::now();

	char path1[1024], path2[1024], output[1024];
	sprintf(path1, "%s", argv[2]);
	sprintf(path2, "%s", argv[3]);
	sprintf(output, "%s.out.txt", argv[2]);

	if (!path1){
		printf("allocation of path1 failed\n");
		return -1;
	}
	if (!path2){
		printf("allocation of path2 failed\n");
		return -1;
	}
	if (!output){
		printf("allocation of outputPath failed\n");
		return -1;
	}
	SparseMatrix matrix1(path1);
	SparseMatrix matrix2(path2);
	if (strcmp(argv[1], "addn") == 0){
		SparseMatrix newMat = matrix1 + matrix2;
		newMat.printToASCIIFile(output);
	}
	if (strcmp(argv[1], "subt") == 0){
		SparseMatrix newMat = matrix1 - matrix2;
		newMat.printToASCIIFile(output);
	}
	if (strcmp(argv[1], "mult") == 0){
		SparseMatrix newMat = matrix1 * matrix2;
		newMat.printToASCIIFile(output);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	printf("run time =%d microseconds\n", (int) duration.count());


	int peakMem2 = getPeakRSS();
	int currMem2 = getCurrentRSS();
	printf("peakRSS = %d, currMem=%d\n", peakMem2, currMem2);
	printf("Diff peakRSS = %d, currMem=%d\n", peakMem2-peakMem1, currMem2-currMem1);

}
