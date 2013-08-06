File documentation:

assembler.h - Entry point, this is the entry point for the compiler
			  this file responsible on handling all command line
			  arguments and invoke correctly the file parser.

file_parser.h - Responsible on compiling one file.

line_parser.h - Responsible on compiling one line in the file.

structure.h - Responsible on managing all needed types for compiling
			  according to the project characterization.

counter.h - Responsible on managing all counters and static data
			needed for one file compilation.

string_helper.h - Responsible on parsing strings with multiple white 
				  spaces and other seperators.

file_writer.h - This file resposible on writing the compilation 
				result for the input file

file_manager.h - This file resposible on managing files with 
				 io library