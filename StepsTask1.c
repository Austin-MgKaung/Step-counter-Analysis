#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assign const variable 
#define MAXCHAR 1000
#define ARRAY_SIZE 1000 // assume record size 

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}


int main() {

    FILE *myfile;
   
    // open CSV file
    myfile = fopen("FitnessData_2023.csv","r");
    

    const char delimiter = ',';
    char row_length [MAXCHAR];
    char temp[10];
    int recordcount = 0; 
    FITNESS_DATA real_record [ARRAY_SIZE];

    //read CSV file 
    while (fgets(row_length,MAXCHAR,myfile))
    {
        // save all data in type define struct fitness data array with helper function 
        tokeniseRecord(row_length, &delimiter,real_record[recordcount].date,real_record[recordcount].time,temp);
        //change string into int
         real_record[recordcount].steps = atoi(temp);
        recordcount++;
        
    }

    fclose(myfile);
    // print all record number
    printf("Number of records in file: %d\n",recordcount);
    // print first 3 row
    for (int i = 0; i < 3 && i < recordcount; i++) {
        printf("%s/%s/%d\n", real_record[i].date, real_record[i].time, real_record[i].steps);
    }
    
    return 0;
}
