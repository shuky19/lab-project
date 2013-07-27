#include "line_parser.h"

line_type get_line_type(char *line)
{
	return COMMAND;
}

command_line get_command_line(char *line)
{
	command_line cl;
	return cl;
}

instruction_line get_instruction_line(char *line)
{
	instruction_line il;
	return il;
}

/*
** Create a command from the given command_line
*/
command get_command(command_line *comm_line)
{
	command comm;
	return comm;
}

/*
** Assign symbol address to the command
*/
void assign_symbol_adderss(command *comm, int symbol_index, int symbol_address)
{
	
}

/*
** Get next line in the file
*/
int next_line(FILE *file, char *buffer, size_t len)
{
	char c; 
   int i;

   memset(buffer, 0, len);

   for (i = 0; i < len; i++)
   {   
      int c = fgetc(file); 

      if (!feof(file)) 
      {   
         if (c == '\r')
            buffer[i] = 0;
         else if (c == '\n')
         {   
            buffer[i] = 0;

            return i+1;
         }   
         else
            buffer[i] = c; 
      }   
      else
      {   
         return -1; 
      }   
   }   

   return -1; 
}