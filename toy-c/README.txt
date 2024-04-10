Name: Alex Wyatt
Language: C
Build tool: make

Code Generation Progress:
-Can generate all code specified in part 3,
including functions & function calls

Instructions:

for build:  type make in the terminal from the part1 directory to compile the project. The executable will be
            created in the bin directory.

for run:  	type make run in the terminal from the part1 directory with the following arguments: source="filepath" and flags ="flags"

            Example: make run flags="-verbose" source="tests/parsing/parse.tc"
			Example (Alternative option):  ./bin/tc tests/parsing/parse.tc -verbose -abstract

		  	flag options:
				-help 		    display a usage message
				-output <file> specifies target jasmine file name
				-class <file> specifies class file name
				-debug <level> display messages that aid in tracing the
				compilation process. 
				If level is:
					0 - all messages
					1 - scanner messages only
					2 - parser messages only
					3 - code generation messages only
				-abstract 		dump the abstract syntax tree
				-symbol			dump the symbol table(s)
				-code			dump the generated JVM code 
				-verbose		enable all debug messages 
				-version		display compiler version

for clean: type make clean in the terminal from the part1 directory to remove the bin executable and build folder 


Key: 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