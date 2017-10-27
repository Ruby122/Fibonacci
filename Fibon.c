//Cse2421 Lab3
//Yiqing Zhang
//gcc -o Fibon Fibon.c
#include <stdio.h>
#include <string.h>

int main (int argc, char **argv){
	printf("%d \n",atoi(*(argv+1)));
	FILE *finout;
  char fileName[20];
  strcpy(fileName, *argv);
  /*Important: array decays to pointers but it is not a pointer
if we increment argv, then the memory address increase by sizeof(char array) = 8 bits. Fibon is only 5 bits, so it moves to /0 and this cannot be printed*/
  // argv++;
  //int N = atoi(*argv);
  strcat(fileName, "acci");//since argv is Fibon
  int N = atoi(argv[1]);
  if(N <= 2){
		printf("ERROR: N should be larger than 2.");
    return -1;
	}	
	finout = fopen(fileName, "w+");
	//check if file is opened or not
	if(finout == NULL){
		printf("Open file failed.");
		return -1;
	}
	else{	
			
		printf("You entered argument: %d\n\n", N);
		printf("1. File Fibonacci content: \n");
		// print the first 2 fibon numbers		
		int count = 2;
		unsigned long long num1 = 1, num2 = 1;
		fprintf(finout, "%20lu%20lu", num1, num2);//%25lu 25: width lu:unsigned long
		printf("%20lu%20lu", num1, num2);
		int i;
		for(i = 1; i <= N-2; i++){
			unsigned long next = num1 + num2;
			if(num2 > next){//check for overflow
				printf("Overflow in Fibonacci numbers.");
				break;
			}
			num1 = num2;
			num2 = next;
			fprintf(finout, "%20lu", next);
			printf("%20lu", next);
			count++;
			//4 Fibonacci numbers in a row
			if(count % 4 == 0){
				fprintf(finout, "\n");
			        printf("\n");
			}
		}
		//read from the beginning of the file Fibonacci		
		rewind(finout);
		fflush(finout);
		printf("Total: %d numbers in Fibonacci\n", count);

		//calculate the median: middle element if count is odd, and average of two middle otherwise
		unsigned long long median, a, b;
		int medianPos;
		if(count % 2 != 0){
			medianPos = (count + 1) / 2;
			for(i = 1; i <= medianPos; i++){
				fscanf(finout, "%lu", &median);
				printf("2. The Fibonacci median: %lu\n\n", median);
			}
		}
		else{
			medianPos = count / 2;
			for(i = 1; i <= medianPos; i++){
				fscanf(finout, "%lu", &a);
			}
			fscanf(finout, "%lu", &b);
			//avoid overflow for long long int
			printf("2. The Fibonacci median: %.2f\n\n", ((double)a + (double)b) / 2);
		}
	
		//copy odd to Fibonacci.odd and even to Fibonacci.even
		//read from the beginning of the file Fibonacci		
		rewind(finout);
		fflush(finout);	
		FILE *fileEven = fopen("Fibonacci.even", "w+");
		FILE *fileOdd = fopen("Fibonacci.odd", "w+");
		//check if the files are opened or not
		if(fileOdd == NULL || fileEven == NULL){
			printf("Open Fibonacci.even or Fibonacci.odd failed.");
			return -1;
		}	
		//copy odd and even numbers and 4 numbers in a row
		int countEven = 0, countOdd = 0;
		unsigned long long num;
		while(fscanf(finout, "%20lu", &num) != EOF){
			if(num % 2 == 0){
				fprintf(fileEven, "%25lu", num);
				countEven++;
				if(countEven % 4 == 0){
					fprintf(fileEven, "\n");	
				}
			}
			else{
				fprintf(fileOdd, "%25lu", num);
				countOdd++;
				if(countOdd % 4 == 0){
					fprintf(fileOdd, "\n");	
				}
			}
		}
		//close finout
		fclose(finout);
		printf("3. Total: %d numbers in Fibonacci.even\n", countEven);
		printf("   Total: %d numbers in Fibonacci.odd\n", countOdd);
		//calculate median in both files
		unsigned long long medianEven, medianOdd;
		//read from the beginning of the file Fibonacci.even		
		rewind(fileEven);
		fflush(fileEven);
		if(countEven % 2 != 0){
			medianPos = (countEven + 1) / 2;
			int i;
			for(i = 1; i <= medianPos; i++){
				fscanf(fileEven, "%lu", &medianEven);
				printf("   Fibonacci.even medium: %lu\n", medianEven);
			}
		}
		else{
			medianPos = countEven / 2;
			int i;
			for(i = 1; i <= medianPos; i++){
				fscanf(fileEven, "%lu", &a);
			}
			fscanf(fileEven, "%lu", &b);
			//avoid overflow for long long int
			printf("   Fibonacci.even medium: %.2f\n", ((double)a + (double)b) / 2);
		}
		//read from the beginning of the file Fibonacci.odd		
		rewind(fileOdd);
		fflush(fileOdd);
		if(countOdd % 2 != 0){
			medianPos = (countOdd + 1) / 2;
			int i;
			for(i = 1; i <= medianPos; i++){
				fscanf(fileOdd, "%lu", &medianOdd);
				printf("   Fibonacci.odd medium: %lu\n\n", medianOdd);
			}
		}
		else{
			medianPos = countOdd / 2;
			int i;
			for(i = 1; i <= medianPos; i++){
				fscanf(fileOdd, "%lu", &a);
			}
			fscanf(fileOdd, "%lu", &b);
			//avoid overflow for long long int
			printf("   Fibonacci.odd medium: %.2f\n\n", ((double)a + (double)b) / 2);
		}
		
		//Copy all even numbers at the end of Fibonacci.odd
		//read from the beginning of the file Fibonacci.even		
		rewind(fileEven);
		fflush(fileEven);
		int countNew;
		unsigned long long copy;
		//Move the pointer to the end of the Fibonacci.odd
		while (fscanf(fileOdd, "%lu", &copy) != EOF){
			fscanf(fileOdd, "%lu", &copy);
		}
		fprintf(fileOdd, "\n");
		//copy even numbers
		while (fscanf(fileEven, "%lu", &copy) != EOF){
			fprintf(fileOdd, "%20lu", copy);
			countNew++;
			if(countNew % 6 == 0){
				fprintf(fileOdd, "\n");
			}
		}
		fclose(fileEven);
		
		//print fileOdd to the screen
		printf("4. Total count in Fibonacci.odd is now: %d\n", countNew + countOdd);
		countNew = 0;
		//read from the beginning of the file Fibonacci.odd		
		rewind(fileOdd);
		fflush(fileOdd);
		while(fscanf(fileOdd, "%20lu", &copy) != EOF){
			printf("%20lu", copy);
			countNew++;
			if(countNew % 5 == 0){
				printf("\n");
			}
		}
		fclose(fileOdd);
		return 0;
	}
}
		

  

  
