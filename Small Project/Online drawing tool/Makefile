bin=HttpServer
cc=g++ -std=c++11
LDFLAGS=-lpthread


.PHONY:all
all:$(bin)

$(bin):HttpServer.cc
	  $(cc) -o $@ $^ $(LDFLAGS)  
cal:cal.c
	  gcc -o $@ $^
.PHONY:clean
clean:
	rm -f $(bin) cal
