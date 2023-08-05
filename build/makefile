src=$(wildcard ../src/*.cpp)
obj=$(patsubst ../src/%.cpp,%.o,$(src))
target=qzip
CXX=g++
CPPFLAGS=-I../include

all:$(target)
$(target):$(obj)
	$(CXX) -o $@ $^
%.o:../src/%.cpp
	$(CXX) -o $@ -c $< $(CPPFLAGS)

.PHONY:clean
clean:
	-rm -f $(target) $(obj)
