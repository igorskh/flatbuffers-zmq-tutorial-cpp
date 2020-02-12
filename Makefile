LIBS = -lzmq
CC = g++
CFLAGS =  -std=c++11

all: directories schema_generated.h bin/reader bin/echo bin/writer
directories:
	mkdir -p bin
schema_generated.h: schema.fbs
	flatc -o . -c schema.fbs
bin/reader: reader.cpp
	$(CC) $(CFLAGS) -o bin/reader reader.cpp $(LIBS)
bin/echo: echo.cpp
	$(CC) $(CFLAGS) -o bin/echo echo.cpp $(LIBS)
bin/writer: writer.cpp
	$(CC) $(CFLAGS) -o bin/writer writer.cpp $(LIBS)
clean:
	rm -f bin/* schema_generated.h