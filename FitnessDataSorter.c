#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "FitnessDataStruct.h"

//  Assign const variable
#define MAXCHAR 1000
#define MAXFILENAME 100
#define ARRAY_SIZE 300 // assume record size

// Define the struct for the fitness data
typedef struct
{
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(const char *record, char delimiter, char *date, char *time, int *steps)
{
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL)
    {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL)
        {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL)
            {
                *steps = atoi(ptr);
            }
        }
    }
}

FILE *Check_file_name(char filename[], FITNESS_DATA record[], int *ucount)
{
    FILE *file;
    file = fopen(filename, "r");

    if (file == NULL)
    {
        return NULL;
    }
    else
    {
        char row_length[MAXCHAR];
        const char delimiter = ',';
        int count = 0;
        while (fgets(row_length, MAXCHAR, file))
        {
            // save all data in type define struct fitness data array with helper function
            tokeniseRecord(row_length, delimiter, record[count].date, record[count].time, &record[count].steps);
            count++;
        }
        *ucount = count;
        fclose(file);

        return file;
    }
}

void sortIndicesBySteps(int indices[], FitnessData record[], int size) {
    int i, j, tempIndex;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (record[indices[j]].steps > record[indices[j + 1]].steps) {
                // Swap the indices
                tempIndex = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIndex;
            }
        }
    }
}


int main()
{

    FILE *myfile;
    int count = 0;

    FITNESS_DATA real_record[ARRAY_SIZE];
    int index[ARRAY_SIZE];
    char filename[MAXFILENAME];

   printf("Enter filename: ");
   scanf("%s",filename);

    myfile = Check_file_name(filename, real_record, &count);
   
    int sortred_array[ARRAY_SIZE];
    if (myfile == NULL)
    {
        perror("Error: invalid file\n");
        return 1;
    }
    else
    {
         for (int i= 0 ; i < count ; i++)
    {
        //printf("%d\t%s\t%s\t%d\n",i+1,real_record[i].date,real_record[i].time,real_record[i].steps);
        if (real_record[i].steps == 0 )
        {
            //printf("hii");
            return 1;
        }
    }
        printf("Data sorted and written to ");
        strcat(filename,".tsv");
        printf(filename);
        printf("\n");
        for(int i = 0 ; i <count ; i++)
        {
            index[i]= i;
           // printf("%d\n",index[i]);
        }
        sortIndicesBySteps(index, real_record , count);



        /* for(int i = 0 ; i <count ; i++)
        {
            printf(" count %d is %d\n",i+1,real_record[index[i]].steps);
             printf("index %d \n",index[i]);
        }
        */

        FILE * outfile = fopen(filename,"w");
        if( outfile == NULL )
        {
            perror("Error opening file");
            return 1;
        }
        for(int i = count ; i >0  ; i--)
        {
            fprintf(outfile,"%s\t%s\t%d\n",real_record[index[i-1]].date,real_record[index[i-1]].time,real_record[index[i-1]].steps);
           // printf("index %d \n",index[i-1]);
        }
        fclose(outfile);
        
    }
}
