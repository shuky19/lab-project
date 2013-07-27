all: pre-clean project.o post-clean

project.o: structure.o file_manager.o file_writer.o assembler.o counter.o file_parser.o line_parser.o string_helper.o
	     @gcc -g -rdynamic structure.o file_manager.o file_writer.o assembler.o counter.o file_parser.o line_parser.o string_helper.o -o project

assembler.o:
	@gcc -g -rdynamic -c assembler.c -o assembler.o

file_parser.o:
	 @gcc -c -g -rdynamic file_parser.c -o file_parser.o

file_writer.o:
	 @gcc -c -g -rdynamic file_writer.c -o file_writer.o

file_manager.o:
	 @gcc -c -g -rdynamic file_manager.c -o file_manager.o

line_parser.o:
	 @gcc -c -g -rdynamic line_parser.c -o line_parser.o

counter.o:
	 @gcc -c -g -rdynamic counter.c -o counter.o

structure.o:
	 @gcc -c -g -rdynamic structure.c -o structure.o

string_helper.o:	
	 @gcc -c string_helper.c -o string_helper.o

pre-clean:
	@rm -rf *.o

post-clean:
	@rm -rf *.o
