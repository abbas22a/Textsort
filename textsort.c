#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdlib.h>


int word_index=0;

/* This function compares both the strings that are inside and outiside the specified word index.
For cases where the index of the string */
int my_compare(const void *elem1, const void *elem2 ){
  
   char **strptr1 = (char**) elem1;
   char **strptr2 = (char**) elem2;
  
   char *str1 = *strptr1;
   char *str2=  *strptr2;
  
   // Make copies of the strings and allocate required memory.
   char *val1 = malloc(strlen(str1)+1);
   char *val2 = malloc(strlen(str2)+1);
   strcpy(val1, str1);
   strcpy(val2, str2);

   // After stroing the words of the sentence, find the word at the specified index. 
   //If the word at the desired index does not exist, choose the last word in the string for comparsion.
   int i=0; int j=0;
   char *line1 = strtok(val1, " ");
   char *lastWord1=line1;
   while(line1!=NULL){
    if(i==(word_index-1)){
      break; 
    }
    lastWord1=line1;
    line1=strtok(NULL, " ");
    i++;
   }

   // Do the same for the second string
   char *line2 = strtok(val2, " ");
   char *lastWord2=line2;
   while(line2!=NULL){
      if(j==(word_index-1)){ 
        break;
      }
      lastWord2=line2;
      line2=strtok(NULL, " ");
      j++;
   }

   // Consider the following cases : */
   // CASE: 1) If both copied strings exists after running through the while loop, return strcmp on the copied strings
   // CASE: 2) If one of the two copied string is emoty, return the last word for one that is emoty and the copy string for the not null one.
   // cASE: 3) If both copied strings are null, return the last words for both the copied strings.
   int value=0;
   if(line1==NULL && line2==NULL){
      value = strcmp(lastWord1, lastWord2);
   }

   else if(line1==NULL && line2!=NULL){
      value = strcmp(lastWord1, line2);
   }

   else if(line1!=NULL && line2==NULL){
     value = strcmp(line1, lastWord2);
   }
   else{
      value =strcmp(line1, line2);
   }
   
   free(val1); 
   free(val2);
     
   return value;
  
}


int main(int argc, char **argv){ 
  
    FILE *f;  char* file; 

    // checking for all possible command line inputs and displacing accordingly.
    // If no arguments are enterred, report error.
    if(argc<2){
       fprintf(stderr, "ERROR: FILE NOT FOUND!\n");
       exit(1);
    }
    
    // If only 1 argument is enterred ,check for correct syntax for the integer parameter if passed in and look for file name.Else report error
    else if( argc==2 &&  (strncmp(argv[1], "-%d", 1) == 0  || (-(strtol(argv[1], NULL, 10))!=0) )){
      fprintf(stderr, "ERROR: Bad Command Line parameters!\n");
      exit(1);
    }
    
    // If only 1 argument is enterred, look for an accurate file path.
    else if(argc==2 && ((strncmp(argv[1], "-%d", 1) != 0)) && (strcmp(argv[1],"%s"))){
       file = argv[1];
       word_index = 1;
    }


    // If 2 arguments are enterred ,check for correct syntax for the integer parameter and look for file name. Else report error.
    else if(argc==3 && strncmp(argv[1], "-%d", 1) != 0 && strcmp(argv[1],"%s")){

       fprintf(stderr, "ERROR: Bad Command Line parameters.\n");
       exit(1);
    }
    
    // store the file name and the word index 
    else{
        file = argv[2];
        word_index = -(strtol(argv[1], NULL, 10));
    }
    
  
  // Open and the read the file 
  f= fopen(file, "r");
  char *line=malloc(128);
  
  // If the file does not exist, report error.
  if(f==NULL){
    fprintf(stderr, "ERROR: cannot open file %s\n", file);
    exit(1);
  }
 
  // Dynamically create the array.  
  char **array; int numLines =10;
  array = malloc(sizeof(char*)*numLines);  

  //check for accurate memory allocation. 
  if(array==NULL){

    fprintf(stderr, "Malloc Failed\n");
    exit(1);
  } 
 
    //parsing and storing the contents of the file into the array. 
     int i=0;
     while(fgets(line,128,f)!=NULL){

      if(strlen(line)>128){
         fprintf(stderr, "ERROR: Line too long\n");

         exit(1);
      }

      // reallocate memory in the event that it is insufficient. 
      if(i == numLines){
          numLines=2*numLines;
          array=realloc(array, sizeof(char*)*numLines); 
      }
        array[i]=strdup(line);  
        i++; 
    }

  printf("ORIGINAL TEXT: \n" );
  for(int j=0; j<i; j++){
     printf("%s" , array[j]);
  }
   
  //sort the array alphabetically   
  qsort(array, i, sizeof(char*), my_compare);

  printf("SORTED TEXT: \n" );
  for(int j=0; j<i; j++){
     printf("%s" , array[j]);
  }
  
  // Free all used memory
  for(int j=0;j<i; j++){
    free(array[j]);
  }   
  free(array);
  free(line);
  return 0;
}
