
#include <GL/glew.h>
#include <GL/glut.h>
#include <optix.h>
#include <sutil.h>


int width = 512, height = 512;
RTbuffer  buffer;


void displayBufferSwap() {

    static unsigned int gl_tex_id = 0;
    if( !gl_tex_id )
    {
        glGenTextures( 1, &gl_tex_id );
        glBindTexture( GL_TEXTURE_2D, gl_tex_id );

        // Change these to GL_LINEAR for super- or sub-sampling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // GL_CLAMP_TO_EDGE for linear filtering, not relevant for nearest.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glBindTexture( GL_TEXTURE_2D, gl_tex_id );

    // send PBO or host-mapped image data to texture
    unsigned int pboId;
    rtBufferGetGLBOId(buffer, &pboId);
    GLvoid* imageData = 0;
    if( pboId )
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, pboId );
     else
     	RT_CHECK_ERROR( rtBufferMap( buffer, &imageData ) );

    RTsize elmt_size;
    RT_CHECK_ERROR( rtBufferGetElementSize(buffer, &elmt_size) );
    if      ( elmt_size % 8 == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
    else if ( elmt_size % 4 == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    else if ( elmt_size % 2 == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    else                          glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	RTformat buffer_format;
	RT_CHECK_ERROR( rtBufferGetFormat(buffer, &buffer_format) );
    if( buffer_format == RT_FORMAT_UNSIGNED_BYTE4)
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    else if(buffer_format == RT_FORMAT_FLOAT4)
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, width, height, 0, GL_RGBA, GL_FLOAT, imageData );
    else if(buffer_format == RT_FORMAT_FLOAT3)
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB32F_ARB, width, height, 0, GL_RGB, GL_FLOAT, imageData );
    else if(buffer_format == RT_FORMAT_FLOAT)
        glTexImage2D( GL_TEXTURE_2D, 0, GL_LUMINANCE32F_ARB, width, height, 0, GL_LUMINANCE, GL_FLOAT, imageData );
    else
        throw std::exception();

    if( pboId )
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
     else
         RT_CHECK_ERROR( rtBufferUnmap( buffer) );

    // 1:1 texel to pixel mapping with glOrtho(0, 1, 0, 1, -1, 1) setup:
    // The quad coordinates go from lower left corner of the lower left pixel
    // to the upper right corner of the upper right pixel.
    // Same for the texel coordinates.

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f( 0.0f, 0.0f );
    glVertex2f( 0.0f, 0.0f );

    glTexCoord2f( 1.0f, 0.0f );
    glVertex2f( 1.0f, 0.0f);

    glTexCoord2f( 1.0f, 1.0f );
    glVertex2f( 1.0f, 1.0f );

    glTexCoord2f(0.0f, 1.0f );
    glVertex2f( 0.0f, 1.0f );
    glEnd();

    glDisable(GL_TEXTURE_2D);

 	glutSwapBuffers();

}

int main(int argc, char** argv) {








	glutInit(&argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_ALPHA | GLUT_DOUBLE );
	glutInitWindowSize( width, height );
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( argv[0] );

    glutSetWindowTitle(argv[0]);
    glutReshapeWindow( width, height );

    RTcontext context = 0;
	RT_CHECK_ERROR( rtContextCreate( &context ) );
	RT_CHECK_ERROR( rtContextSetRayTypeCount(context, 1) );
	RT_CHECK_ERROR( rtContextSetEntryPointCount(context, 1) );


	RT_CHECK_ERROR( rtBufferCreate(context, RT_BUFFER_OUTPUT, &buffer) );
	RT_CHECK_ERROR( rtBufferSetFormat(buffer, RT_FORMAT_FLOAT4) );
	RT_CHECK_ERROR( rtBufferSetSize2D(buffer, width, height) );

	RTvariable result_buffer;
	RT_CHECK_ERROR( rtContextDeclareVariable( context, "result_buffer", &result_buffer ) );
	RT_CHECK_ERROR( rtVariableSetObject( result_buffer, buffer ) );	



	RTprogram program;
	RT_CHECK_ERROR( rtProgramCreateFromPTXFile(context, "hello/hello.ptx", "hello", &program) );
	RT_CHECK_ERROR( rtContextSetRayGenerationProgram(context, 0, program) );

	RT_CHECK_ERROR( rtContextValidate(context) );
	RT_CHECK_ERROR( rtContextLaunch2D(context, 0, width, height) );    

    // Init state
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0, 0, width, height);

    //glutKeyboardFunc(keyPressed);
    glutDisplayFunc(displayBufferSwap);
    glutSwapBuffers();

    glutMainLoop();	


    RT_CHECK_ERROR( rtBufferDestroy( buffer ) );
    RT_CHECK_ERROR( rtProgramDestroy( program ) );
    RT_CHECK_ERROR( rtContextDestroy( context ) );    



	
	return 0;
}
