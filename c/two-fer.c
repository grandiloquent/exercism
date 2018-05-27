#include <stdio.h>

#define BUFFER_SIZE (100)
#define SEQUENCE "One for %s,one for me."

void two_fer(char *buffer,const char *name){
    snprintf(buffer,BUFFER_SIZE,SEQUENCE,(buffer==NULL||name==NULL||name[0]=='\0')?"you":name);
}


int main(int argc, char const *argv[])
{
   char response[BUFFER_SIZE];

   two_fer(response,"Alice");

   printf("%s\r\n",response);

   
   two_fer(response,NULL);


   printf("%s\r\n",response);
   two_fer(response,"");


   printf("%s\r\n",response);

    return 0;
}

// gcc two-fer.c
