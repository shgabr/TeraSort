#include "CommandLineArguments.h"


CommandLineArguments::CommandLineArguments()
{
    memset(input_file_name,0,COMMAND_LINE_ARGUMENT_MAX_SIZE);    //intintiate memory of 128 bytes to input_file_name
    memset(output_file_name,0,COMMAND_LINE_ARGUMENT_MAX_SIZE);  //intintiate memory of 128 bytes to output_file_name
    memset(error_string,0,ERROR_STRING_MAX_SIZE);     //intintiate memory of 128 bytes to error_string
    mappers = 0;            //set mappers to zero
    reducers = 0;          //set reducers to zero
    sample_size = 0;         //set sample_size to zero
}
bool CommandLineArguments::parser(int argc,char ** argv)
{
    if ( argc %2 == 0 || argc < 2) return false;   //if the entered Command Line Arguments an even number or less than 2 then return false
    else
    {
        for ( uint8_t i = 1 ; i < argc ; i +=2)   //loops over every command line argument
        {
            if ( strcmp(argv[i],"--input-file") == 0)    //locate --input-file and copy the command after it to input_file_name
                strncpy(input_file_name,argv[i+1],COMMAND_LINE_ARGUMENT_MAX_SIZE-1);
            else if ( strcmp(argv[i],"--output-file") == 0)   //locate --output-file and copy the command after it to output_file_name
                strncpy(output_file_name,argv[i+1],COMMAND_LINE_ARGUMENT_MAX_SIZE-1);
            else if ( strcmp(argv[i],"--mappers") == 0)    //locate --mappers and copy the command after it to the number of mappers
            {
                mappers =atoi(argv[i+1]);
            }
            else if ( strcmp(argv[i],"--reducers") == 0)   //locate --reducers and copy the command after it to the number of reducers
            {
                reducers =atoi(argv[i+1]);
            }
            else if ( strcmp(argv[i],"--sample-size") == 0)  //locate --sample_size and copy the command after it to the sample_size
            {
                sample_size =atoi(argv[i+1]);
            }
            else
            {
                sprintf(error_string,"undefined parameter: %s\n",argv[i]);
                return false;    //if a command was incorrectly entered then return false with error string
            }
        }
        if ( strcmp (input_file_name,"") == 0 || strcmp (output_file_name,"") == 0 ||
                mappers == 0 || reducers == 0 | sample_size == 0 ) return false;  //if there is any data member empty then return false
        else return true;    //if every thing is correct then return true

    }
    //this way of handling command line arguments ensures that their order does not matter
}
bool CommandLineArguments::execute()
{

    TeraSort <TeraSortItem,teraitem_r> * teraSort =
            new TeraSort <TeraSortItem,teraitem_r> (input_file_name,output_file_name,mappers,reducers,sample_size);
      //create an object of teraSort with template parameters TeraSortItem and teraitem_r and call the parametrized constructor

    teraSort->execute();   //call teraSort execute
    delete(teraSort);     //delete pointer to object teraSort
    return true;
}
char * CommandLineArguments::getErrorString()
{
    return error_string;   //getter for error_string
}
CommandLineArguments::~CommandLineArguments()
{

}
