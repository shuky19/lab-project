#include "line_parser.h"

line_type get_line_type(char *line)
{
	return COMMAND;
}

command_line *get_command_line(char *line)
{
	command_line *cl = (command_line *)malloc(sizeof(command_line));
   cl->label = "Shuky";
   cl->command = "mov";
	return cl;
}

instruction_line get_instruction_line(char *line)
{
   unsigned int data[] = {0,1,2};
   instruction_content content;
   content.data = data;
	instruction_line il;
   il.command = DATA;
   il.content = content;
	return il;
}

/*
** Create a command from the given command_line
*/
command *get_command(command_line *comm_line)
{
	command *comm = (command *)malloc(sizeof(command));
   comm->comb = 1;
   comm->dest_reg = 2;
   comm->dest_add = 3;
   comm->source_reg = 1;
   comm->source_add = 2;
   comm->opcode = 3;
   comm->type = 0;
   comm->dbl = 1;
   comm->extra_word_count = 0;
   comm->symbols_count = 0;
	return comm;
}

/*
** Assign symbol address to the command
*/
void assign_symbol_adderss(command *comm, int symbol_index, int symbol_address)
{
	printf("Should not happend\n");
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
         {
            buffer[i] = 0;
         }
         else if (c == '\n')
         {   
            buffer[i] = 0;
            return i+1;
         }   
         else
         {
            buffer[i] = c; 
         }
      }   
      else
      {   
         return -1; 
      }   
   }   

   return -1; 
}