#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_first3_last4(char* original)
{
    char* removed = malloc(strlen(original-6)*sizeof(char));
    removed = original + 3;
    removed[strlen(removed) - 4] = '\0';
    return removed;

}

int main(int argc, char const *argv[])
{

    FILE *fptr;
    FILE* out_file;
    char filename[15];
    char* file_lines_array[50];
    //we can create a new address for each line entry
    char* line;
 
    printf("Enter the filename to be opened \n");
    scanf("%s", filename);
    /*  open the file for reading */
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

     /*We are opening the file to write to here.
    This is just another way to write the code, but it does the same as 
    the code above that opens the file to read
    The only difference is the mode. Above is "r" to read below is "w" to write */
    if ((out_file = fopen("./new_files/outfile_removed.txt", "w")) == NULL){
            printf("Error! opening file\n");
    }
    
    /*You need to check the return value of fgets. If a read has been successful, 
    fgets returns the pointer to the buffer that you passed to it 
    (i.e. string in your example). If the End-of-File is encountered and no 
    characters have been read, fgets returns NULL.*/
    int count = 0;
    line = malloc(100*sizeof(char));
    while(fgets(line,100, fptr) != NULL) {
        line = strtok(line, "\n");
        file_lines_array[count] = line;
        line = malloc(50*sizeof(char));
        count++;
    }
    
    printf("print array\n");
    int i;
    char* removed;
    for(i=0;i<count;i++) {
        removed = malloc(strlen(file_lines_array[i])-6);
        removed = file_lines_array[i] + 3;
        removed[strlen(removed) - 4] = '\0';
       /* You can do the string manipulation in a function
       see the function above
       Using a function is a better way to do this
       You should always modularize your code
       removed=remove_first3_last4(file_lines_array[i]);
       */
        printf("%s\n", removed);
        char* new_line = malloc(sizeof(char));
        strcpy(new_line,"\n");
        //print the line with characters removed
        fprintf(out_file,removed,strlen(removed));
        //prints a new line character  
        fprintf(out_file,new_line,sizeof(char));    
    }
    fclose(fptr);
    fclose(out_file);
    return 0;
}