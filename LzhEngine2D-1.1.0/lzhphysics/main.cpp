#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>
#include <LzhVector2d.h>
#include <LzhVector3d.h>
#include <LzhMatrix3x3.h>

/*===========================================================================*/

void Run(LZH_ENGINE *engine);

/*===========================================================================*/

int main(int argc, char *argv[])
{
    LZH_ENGINE *engine = NULL;

    lzh_init();

    engine = lzh_engine_create("Physics", 800, 600);
    if (!engine) {
        goto end;
    }

    Run(engine);

end:
    lzh_engine_destroy(engine);
    lzh_quit();
    return 0;
}

/*===========================================================================*/

void Run(LZH_ENGINE *engine)
{
    Lzh_Vec3d<float> vec1(1.0f, 3.0f, 5.0f);

    Lzh_Mat3x3f<float> mat1;
    mat1[0][0] = 5.0f;
    mat1[1][1] = 5.0f;
    mat1[2][2] = 5.0f;

    Lzh_Mat3x3f<float> mat2;
    mat2[0][0] = 2.0f;
    mat2[1][1] = 2.0f;
    mat2[2][2] = 2.0f;

    mat1 = mat2 * mat1;
    vec1 = mat1 * vec1;

    printf("vec1 = %f, %f, %f\n", vec1.x, vec1.y, vec1.z);

    mat1 = -mat1;
    vec1 = mat1 * vec1;

    printf("vec1 = %f, %f, %f\n", vec1.x, vec1.y, vec1.z);

    lzh_engine_update(engine);
}

/*===========================================================================*/
