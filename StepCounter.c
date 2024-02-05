#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "FitnessDataStruct.h"

//  Assign const variable 
#define MAXCHAR 1000
#define MAXFILENAME 100
#define ARRAY_SIZE 500// assume record size

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(const char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

FILE* Check_file_name ( char filename[],FITNESS_DATA record[], int *ucount)
{
    FILE* file;
    file = fopen( filename,"r");

    if( file == NULL )
    {
        return NULL;
    }
    else 
    {
        char row_length [MAXCHAR];
        const char delimiter = ',';
        int count = 0;
        while (fgets(row_length,MAXCHAR,file))
        {
        // save all data in type define struct fitness data array with helper function 
        tokeniseRecord(row_length,delimiter,record[count].date,record[count].time,&record[count].steps);
        count++;
        
    }
    *ucount = count; 
    fclose(file);

        return file;
    }
}
int mean_records_calc(FITNESS_DATA record[],int array_size)
{   
    int  count = 0;
    double mean = 0 ;
    for (int i = 0 ; i < array_size; i++)
    {
        mean += record[i].steps;

    }

    return round(mean/array_size);
}

int largest_record_calc(FITNESS_DATA record[],int array_size)
{
    int max = record[0].steps;
    int max_index = 0;
    for (int i = 0 ; i < array_size; i++)
    {
        if (record[i].steps>max)
        {
            max = record[i].steps;
            max_index = i;
        }

    }

    return max_index;

}
int fewest_record_calc(FITNESS_DATA record[],int array_size)
{
    int min = record[0].steps,min_index;
    for (int i = 0 ; i < array_size; i++)
    {
        if (record[i].steps < min )
        {
            min  = record[i].steps;
             min_index = i;
        }

    }

    return min_index;
}
void longest_period(FITNESS_DATA record[],int array_size,int* start,int* end)
{
    int fstart,fend,length = 0;
    int dur_length = 0, max = 0 ;
    bool flag = true;
    for (int i = 0 ; i < array_size; i++)
    {   
        printf("%d\n",record[i].steps);
        if (record[i].steps > 500  && flag == true)
        {
            fstart = i ;
            flag = false;
            length++;
        }
        else if (record[i].steps > 500  && flag == false)
        {
            fend = i ;
            length++;
        }
        else{

            if (flag == false)
            {
                dur_length = length;
                flag = true;
                length = 0 ;
            }
            if (dur_length  > max )
            {
                max = dur_length;
                *start = fstart;
                *end = fend;
            }
        }
        

    }

}

int main() {

    FILE *myfile;
    int count = 0,start,end;
    bool flag = true;
    char user_input;
    FITNESS_DATA real_record [ARRAY_SIZE];
    char filename[MAXFILENAME];
    while (flag )
    {
    printf("Menu Options:\nA: Specify the filename to be imported\nB: Display the total number of records in the file\nC: Find the date and time of the timeslot with the fewest steps\nD: Find the date and time of the timeslot with the largest number of steps\nE: Find the mean step count of all the records in the file\nF: Find the longest continuous period where the step count is above 500 steps\nQ: Quit\nEnter choice:");
    scanf(" %c", &user_input);
    switch (user_input)
    {
        case 'A':
            printf("Input filename: ");
            scanf("%s",filename);
            myfile=Check_file_name(filename,real_record,&count);
            if (myfile == NULL)
            {
                perror("Error: could not open file\n");
                return 1;
            }
            else
            {
                printf("File successfully loaded.\n");
            }
            break;
        case 'B':
            count;
            printf("Total records: %d\n",count);
            break;

        case 'C':
            int min = fewest_record_calc(real_record,count);
            printf("Fewest steps: %s %s\n",real_record[min].date,real_record[min].time);
            break;

            case 'D':
            int umax = largest_record_calc(real_record,count);
            printf("Largest steps: %s %s\n",real_record[umax].date,real_record[umax].time);
            break;
        case 'E':
            int mean_records = mean_records_calc(real_record,count);
            printf("Mean step count: %d\n",mean_records);
            break;
        case 'F':
            longest_period(real_record,count,&start,&end);
             printf("Longest period start: %s %s\n",real_record[start].date,real_record[start].time);
              printf("Longest period end: %s %s\n",real_record[end].date,real_record[end].time);
            break;
        case 'Q':
            return 0;
            break;
    
        default:
             printf("Invalid choice. Try again.\n");
            break;
    }
    }

    
    

   

}
