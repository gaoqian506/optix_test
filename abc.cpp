



RT_PROGRAM void intersect(int) {

}

RT_PROGRAM void bounds(int, float result[6]) {

}

RT_PROGRAM void closest_hit() {
    //prd_color = make_float3(0, 1, 0);
}

// RT_PROGRAM void any_hit() {
//  prd_color = make_float3(1, 1, 0);
// }



#LIB_DIR += -L/home/gq/Documents/opecv/opencv-2.4.8/lib

	//cv::Mat mat = cv::Mat(height, width, CV_32FC4, image_data);
	//cv::imwrite("output.png", mat * 255.0f);
	
	


INCLUDE_DIR += -I$(CUDA_ROOT)/include
INCLUDE_DIR += -I$(CUDA_ROOT)/targets/x86_64-linux/include
LIB_DIR = -L$(OPTIX_ROOT)/lib64
LIB_DIR += -L/home/gq/Documents/opecv/opencv-2.4.8/lib
LIBS = -lglut -loptix -lGL -lGLEW -lopencv_highgui -lopencv_core



#ifdef OPENCV3
	#include <opencv2/highgui.hpp>
#else
	#include <opencv2/highgui/highgui.hpp>
#endif
#LIB_DIR += -L/usr/lib/x86_64-linux-gnu

Configured with: ../src/configure -v --with-pkgversion='Ubuntu 5.4.1-2ubuntu1~14.04' --with-bugurl=file:///usr/share/doc/gcc-5/README.Bugs --enable-languages=c,ada,c++,java,go,d,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-5 --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=gcc4-compatible --disable-libstdcxx-dual-abi --enable-gnu-unique-object --disable-vtable-verify --enable-libmpx --enable-plugin --with-system-zlib --disable-browser-plugin --enable-java-awt=gtk --enable-gtk-cairo --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-5-amd64/jre --enable-java-home --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-5-amd64 --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-5-amd64 --with-arch-directory=amd64 --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --enable-objc-gc --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix



-lopencv_imgcodecs

-lopencv_highgui -lopencv_core

-l:libopencv_highgui.so.2.4 -l:libopencv_core.so.2.4


    optix::Ray ray(make_float3(0, 0, 0), make_float3(0, 0, 1), 0, 0.1);

    float3 color = make_float3(1, 0, 0);
    rtTrace(rtObject(), ray, color);
    //rtTrace(top_object, ray, prd);

    result_buffer[launch_index] = make_float4(color, 1);
    //result_buffer[launch_index] = make_float4(0, 0, 1, 1);


    // optix::size_t2 screen = result_buffer.size();
    // float2 d = make_float2(launch_index) / make_float2(screen);
    // //float2 d = make_float2(launch_index) /result_buffer.size();
    // result_buffer[launch_index] = make_float4(0, d.x, d.y, 1);

       //  RT_CHECK_ERROR( rtBufferDestroy( buffer ) );
    // RT_CHECK_ERROR( rtProgramDestroy( program ) );
    // RT_CHECK_ERROR( rtContextDestroy( context ) );    



    std::ofstream out_file("output.ppm", std::ios::out | std::ios::binary);
    assert(out_file.is_open());
    out_file << "P6";
    out_file << width << " " << height << std::endl << 255 << std::endl;
    out_file.write((char*)image_data , width * height * 3);
    out_file.close();


//#include <sutil.h>
//#include <optix_world.h>


    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( width, height );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( argv[0] );
    glutHideWindow();

// enum bufferPixelFormat
// {
//     BUFFER_PIXEL_FORMAT_DEFAULT, // The default depending on the buffer type
//     BUFFER_PIXEL_FORMAT_RGB,     // The buffer is RGB or RGBA
//     BUFFER_PIXEL_FORMAT_BGR,     // The buffer is BGR or BGRA
// };

bufferPixelFormat g_image_buffer_format = BUFFER_PIXEL_FORMAT_DEFAULT;

GLenum glFormatFromBufferFormat(bufferPixelFormat pixel_format, RTformat buffer_format)
{
    if (buffer_format == RT_FORMAT_UNSIGNED_BYTE4)
    {
        switch (pixel_format)
        {
        case BUFFER_PIXEL_FORMAT_DEFAULT:
            return GL_BGRA;
        case BUFFER_PIXEL_FORMAT_RGB:
            return GL_RGBA;
        case BUFFER_PIXEL_FORMAT_BGR:
            return GL_BGRA;
        default:
            throw Exception("Unknown buffer pixel format");
        }
    }
    else if (buffer_format == RT_FORMAT_FLOAT4)
    {
        switch (pixel_format)
        {
        case BUFFER_PIXEL_FORMAT_DEFAULT:
            return GL_RGBA;
        case BUFFER_PIXEL_FORMAT_RGB:
            return GL_RGBA;
        case BUFFER_PIXEL_FORMAT_BGR:
            return GL_BGRA;
        default:
            throw Exception("Unknown buffer pixel format");
        }
    }
    else if (buffer_format == RT_FORMAT_FLOAT3)
        switch (pixel_format)
        {
        case BUFFER_PIXEL_FORMAT_DEFAULT:
            return GL_RGB;
        case BUFFER_PIXEL_FORMAT_RGB:
            return GL_RGB;
        case BUFFER_PIXEL_FORMAT_BGR:
            return GL_BGR;
        default:
            throw Exception("Unknown buffer pixel format");
        }
    else if (buffer_format == RT_FORMAT_FLOAT)
        return GL_LUMINANCE;
    else
        throw Exception("Unknown buffer format");
}


# SRCS = $(wildcard  *.cpp)


# all:
# 	echo $(SRCS)


# INCLUDE_DIR = -I/home/gq/Documents/nvidia/NVIDIA-OptiX-SDK-5.0.0-linux64/include
# INCLUDE_DIR += -I/home/gq/Documents/nvidia/NVIDIA-OptiX-SDK-5.0.0-linux64/SDK/sutil
# INCLUDE_DIR += -I/usr/local/cuda-8.0/targets/x86_64-linux/include
# LIBS = -loptix -lsutil_sdk -loptixu
# LIB_DIR = -L/home/gq/Documents/nvidia/NVIDIA-OptiX-SDK-5.0.0-linux64/lib64
# LIB_DIR += -L/home/gq/Documents/nvidia/NVIDIA-OptiX-SDK-5.0.0-linux64/SDK-precompiled-samples
# FLAGS = -g
# SRCS=$(wildcard  samples/*.cpp)
# OBJS=$(SRCS:%.cpp=%.o)
# TARGET = test



# $(TARGET) : $(OBJS)
# 	g++ $(OBJS) $(FLAGS) $(LIB_DIR) $(LIBS) -o $(TARGET)


# optixHello_generated_draw_color.cu.ptx: samples/draw_color.cu
# 	/usr/local/cuda/bin/nvcc -Wno-deprecated-gpu-targets -ptx $(INCLUDE_DIR) $(LIB_DIR) $(LIBS) samples/draw_color.cu


# $(OBJS) : %.o : %.cpp
# 	g++ -c $(INCLUDE_DIR) $(LIB_DIR) $(LIBS) $(FLAGS) $< -o $@





# debug:
# 	gdb ./$(TARGET)
	
# run:
# 	./$(TARGET)


# INCLUDE_DIR = -Iinclude -I/home/gq/Documents/github/caffe/include
# LIBS = -lopencv_core -lopencv_highgui -lcaffe -lboost_system
# LIB_DIR = -L/home/gq/Documents/github/caffe/build/lib
# FLAGS = -g -DCPU_ONLY
# SRCS=$(wildcard  src/*.cpp)
# OBJS=$(SRCS:%.cpp=%.o)
# TARGET = train


# $(TARGET) : $(OBJS)
# 	g++ $(OBJS) $(FLAGS) $(LIB_DIR) $(LIBS) -o $(TARGET)

# $(OBJS) : %.o : %.cpp
# 	g++ -c $(INCLUDE_DIR) $(LIB_DIR) $(LIBS) $(FLAGS) $< -o $@



# clean:
# 	rm -f $(OBJS) $(TARGET)

# debug:
# 	gdb ./$(TARGET)
	
# run:
# 	./$(TARGET)	


#INCLUDE_DIR = -Iinclude
#LIBS = -lGL -lGLU -lglut -lpthread -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_calib3d
#FLAGS = -g	

# longxuan:
# 	./$(TARGET) data/videos/longxuan.mp4
	
# texie:
# 	./$(TARGET) data/videos/texie.mp4

# shanghai:
# 	./$(TARGET) data/videos/shanghai.mp4

# gongyuan:
# 	./$(TARGET) data/videos/gongyuan.mp4	
	
# dajiang:
# 	./$(TARGET) data/videos/dajiang0229.mp4
	
# m1_left_8x8:
# 	./$(TARGET) data/images/move_left_8x8_001.png data/images/move_left_8x8_002.png

# m2_left_64x64:
# 	./$(TARGET) data/images/move_left_64x64_001.png data/images/move_left_64x64_002.png
	
# tsukuba:
# 	./$(TARGET) data/images/tsukuba_l.png data/images/tsukuba_r.png
	
# tsukuba2:
# 	./$(TARGET) data/images/tsukuba_l.png data/images/tsukuba_r_rot.png


	
