
#include "CommandLineArguments.h"

int main(int argc, char **argv)
{
    time_t start = time(NULL);   //save current time to start
    CommandLineArguments cmlarg;   //create an object of type CommandLineArguments
    if (cmlarg.parser(argc,argv))  //parse the command line arguments if true then comaands are correct and false otherwise
    {
        if (!cmlarg.execute())  // call method execute (where the program begins)
        {
            if ( strcmp(cmlarg.getErrorString(),"") != 0 )
                printf ("%s\n",cmlarg.getErrorString());
        }
    }
    else
    {
        if ( strcmp(cmlarg.getErrorString(),"") != 0 )    //checks if the error message is empty or not
            printf ("%s",cmlarg.getErrorString());    //if not empty then print the error message and how are the command line arguments expected to be entered
        printf ("usage: %s --input-file <file-name> --output-file <file-name> --mappers <# of mappers> --reducers <# of reducers> --sample-size <# of records in sample>\n",argv[0]);
        exit(1);     //terminate program
   }
    time_t end = time(NULL);   //save current time to end
    printf ("Total time: %lu\n",end-start);  //print the time elapsed by (end time) - (start time)


    return 0;
}
