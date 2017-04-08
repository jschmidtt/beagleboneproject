#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getLine (FILE *fp); /*gets line from file*/
void outputData(char *outputFile); /* outputs the data to a file passed in at argv[2] */
void parseLine(char*line, int index); /* parse the lines from the input file to tokens and get dates and data */
void printData(); /* loops through dates and data and prints to output stream */
void mallocData(); /* mallocs the arrays dates and data */

char *dates[31]; /* array of strings that stores the datas from the input file */
char *data[31]; /* array of strings that stores the data/reading from the input file */

int main (int argc, char* argv[]){
    
/* open the file passed into at the start of the program
   currently only looks for argv[1] */
    
    FILE *fp;
    
    fp = fopen(argv[1],"r");
    if(fp==NULL){
        exit(EXIT_FAILURE);
    }
    else{
        printf("File found: %s\n",argv[1]);
    }
    
    mallocData();

    
/* get name of ouputFile from argv[2]*/   
    char *outputFile;
    if(argv[2]==NULL){
        printf("No ouptput file given..\n");
        exit(EXIT_FAILURE);
    }
    else{
        outputFile = argv[2];
    }

/* get lines for correct amount of desired readings */
    int x=0;
    char *test[38];
    while(x<38){
        test[x]=malloc(sizeof(char)*26);
        test[x]=getLine(fp);
        //printf("%d: %s\n",x-6,test[x]);
        x++;
    }
    
/* parse the lines for dates and data */
    x=0;
    int a=6;
    while(x<30){
        parseLine(test[a],a);
        //printf("%d: %s\n",x,dates[x]);
        //printf("%d: %s\n",x,data[x]);
        a++;
        x++;
    }
    
/*do a quick check, see printData*/
    printData();
    
/* calls method to output data to a file */
    outputData(outputFile);
    
    printf("End Main, exiting....\n");
    
    exit(EXIT_SUCCESS);
    
}//end Main

/* reads a line from the file of 100 chars long just to make sure you reach end of line returns this line to caller */
char *getLine (FILE *fp){
    char *line;
    line = malloc(sizeof(char)*26);
    fgets(line,100
    ,fp);
    //printf("Line Read: %s\n",line);
    return line;
}//end getLine

/* parse the line looking for the token ';' returns this new char to caller */
void parseLine(char*line, int index){
    char*tmp=strtok(line,";");
    dates[index-6]=tmp;
    tmp=strtok(NULL,";");
    tmp=strtok(NULL,";");
    data[index-6]=tmp;
    
}//end parseLine

/* once properly working should output the data to the txt file passed in after the .csv (argv[2])
    assuming this is not empty */
void outputData(char *outputFile){
    
    FILE *tmp;
    tmp = fopen(outputFile,"w");
    if(tmp==NULL){
        exit(EXIT_FAILURE);
    }
    else{
        printf("Output File Opened, writing data...\n");
    }
    
    int x=0;
    while(x<30){
        fputs("Date: ",tmp);
        fputs(dates[x],tmp);
        fputs("--",tmp);
        fputs(data[x],tmp);
        fputs("--mg/dl",tmp);
        fputs("\n",tmp);
        x++;
    }
    
    printf("Finished, closing file.\n");
    
    //fclose(tmp); /*if you clsoe the file you get an error, trying to work this out */
    
}//end outputData

/*call this if you wish to quickly print out the info stored in dates and data
    only prints to output stream not a file */
void printData(){
    int cnt=0;
    printf("Printing data...\n");
    while(cnt<30){
        printf("%d: %s",cnt+1,dates[cnt]);
        printf(" Reading: %s\n",data[cnt]);
        cnt++;
    }
}

/* ensures there is proper space for all the data put into these arrays */
void mallocData(){
    int cnt=0;
    while(cnt<30){
        dates[cnt]=malloc(sizeof(char)*10);
        data[cnt]=malloc(sizeof(char)*5);
        cnt++;
    }
}