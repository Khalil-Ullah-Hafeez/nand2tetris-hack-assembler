inc = -I/authentication -I/parse -I/helper -I/symbols
auth_path = ./authentication
parse_path = ./parse
helper_path = ./helper
symbols_path = ./symbols

Assembler: main.o $(auth_path)/authenticator.o $(parse_path)/parser.o $(helper_path)/helper.o $(symbols_path)/symbols.o
	g++ main.o $(auth_path)/authenticator.o $(parse_path)/parser.o $(helper_path)/helper.o $(symbols_path)/symbols.o -o Assembler $(inc)

main.o: main.cpp
	g++ -c main.cpp

$(auth_path)/authenticator.o: $(auth_path)/authenticator.cpp $(auth_path)/authenticator.h
	g++ -c $(auth_path)/authenticator.cpp $(inc) -o $(auth_path)/authenticator.o

$(helper_path)/helper.o: $(helper_path)/helper.cpp $(helper_path)/helper.h
	g++ -c $(helper_path)/helper.cpp $(inc) -o $(helper_path)/helper.o

$(symbols_path)/symbols.o: $(symbols_path)/symbols.cpp $(symbols_path)/symbols.h
	g++ -c $(symbols_path)/symbols.cpp $(inc) -o $(symbols_path)/symbols.o	

clean:
	del /s *.o Assembler.exe