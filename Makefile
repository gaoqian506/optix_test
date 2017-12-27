



SRCS = $(shell find -name *.cpp)
CUS = $(shell find -name *.cu)
OBJS = $(SRCS:%.cpp=%.o)
TARGET = $(OBJS:%.o=%)
PTXES = $(CUS:%.cu=%.ptx)



all : $(TARGET) $(PTXES)

$(PTXES) :  %.ptx : %.cu
	nvcc -ptx -Wno-deprecated-gpu-targets $< -o $@

$(TARGET) : % : %.o
	g++ $< -o $@

$(OBJS) : %.o : %.cpp
	g++ -c $< -o $@	

clean:
	rm -f $(OBJS) $(TARGET) $(PTXES)

run_hello:
	./hello/hello	

echo:
	echo $(SRCS)
	echo $(OBJS)	
	echo $(TARGET)	
	echo $(PTXES)

