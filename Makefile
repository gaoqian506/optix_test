



SRCS = $(shell find -name *.cpp)
CUS = $(shell find -name *.cu)
OBJS = $(SRCS:%.cpp=%.o)
TARGET = $(OBJS:%.o=%)
PTXES = $(CUS:%.cu=%.ptx)

OPTIX_ROOT = ../../nvidia/OptiX-5.0.0
CUDA_ROOT = /usr/local/cuda

INCLUDE_DIR = -I$(OPTIX_ROOT)/include
INCLUDE_DIR += -I$(OPTIX_ROOT)/SDK/sutil
INCLUDE_DIR += -I$(CUDA_ROOT)/targets/x86_64-linux/include
LIB_DIR = -L$(OPTIX_ROOT)/lib64
LIBS = -lglut -loptix -lGL -lGLEW -lopencv_highgui -lopencv_core

FLAGS = -g



all : $(TARGET) $(PTXES)

$(PTXES) :  %.ptx : %.cu
	$(CUDA_ROOT)/bin/nvcc -ptx -Wno-deprecated-gpu-targets $< -o $@ $(INCLUDE_DIR)

$(TARGET) : % : %.o
	g++ $< -o $@ $(LIBS) $(LIB_DIR) $(FLAGS)

$(OBJS) : %.o : %.cpp
	g++ -c $< -o $@ $(INCLUDE_DIR) $(FLAGS)

clean:
	rm -f $(OBJS) $(TARGET) $(PTXES)

rhello:
	./hello/hello	

dhello:
	gdb ./hello/hello		

rbox:
	./box/box
	xdg-open output.png

dbox:
	gdb ./box/box

echo:
	echo $(SRCS)
	echo $(OBJS)	
	echo $(TARGET)	
	echo $(PTXES)

 #-lsutil_sdk -loptixu