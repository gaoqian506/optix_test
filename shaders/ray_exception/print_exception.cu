#include <optix.h>

// rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
// rtBuffer<float4, 2> output_buffer;

RT_PROGRAM void exception()
{
	rtPrintExceptionDetails();

  //output_buffer[launch_index] = make_float4(1, 1, 0, 1);
}
