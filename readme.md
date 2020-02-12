# FlatBuffers and ZeroMQ Sample in C++

[First part, detailed description and implementation in Go](https://github.com/igorskh/flatbuffers-zmq-tutorial).

## Build
The following code generates C++ header file from FlatBuffers schema and builds executables in `bin` folder:
```bash
make
```

## Run
First, we run the router, which is a receiver:
```bash
./bin/reader
``` 

It listens on `tcp://*:5555"`.

Secondly run the dealer, which sends data to the router:
```bash
./bin/writer
```

You should now see the received data in the router `STDOUT`:
```text
Received request for Median on axis 0
Description: do any calc
Number of values: 
```

Alternatively you can run applications from [Go implementation](https://github.com/igorskh/flatbuffers-zmq-tutorial). They are based on the same FlatBuffers schema and are interchangeable. 

C++ is a router, Go is a dealer:
```bash
./bin/reader
go run $GOPATH/src/github.com/igorskh/flatbuffers-zmq-tutorial/writer/main.go
```

Output:
```text
Received request for Average on axis 0
Description: do something
Number of values: 5 
```

Go is a router, C++ is a dealer:
```bash
go run $GOPATH/src/github.com/igorskh/flatbuffers-zmq-tutorial/reader/main.go
./bin/writer
```

Output: 
```text
2020/02/12 12:24:14 router created and bound
2020/02/12 12:24:15 router received from '[0 60 125 57 156]'
Got request:  do any calc
Calc axis:  0
Values:  5
[0 1 2 3 4]
Calculating Median
Result:  1.5
```
