#include "ermine-camera.h"
#include "ermine-gfx-renderer.h"
#include "ermine-window.h"
#include "ermine-ecs.h"

// Lista de camaras
static ecamera camera_manager[CAMERA_MANAGER_SIZE];

// Camara que tenemos activa.
// min = 1, max = CAMERA_MANAGER_SIZE
//
// la camara 0 es utilizada por el motor
// para otras cosas.
static int camera_manager_active = 0;

// activar camara o desactivar camara
void ermine_camera_set_active(int i)
{
    camera_manager_active = i;
}

// obtenemos la camara activa
ecamera ermine_camera_get_active(void)
{
    return camera_manager[camera_manager_active];
}

// creamos una nueva camara
void ermine_camera_set(ecamera camera, int index)
{
    if (index > 0)
    {
        camera_manager[index] = camera;
    }
    else
    {
        printf("ERROR: Camera not available [%d]\n", index);
    }
}

//
void ermine_camera_manager_begin(int camera_id)
{
    ecamera camera = camera_manager[camera_id];

    int w = camera.viewport.w == 0 ? ermine_window_width() : camera.viewport.w;
    int h = camera.viewport.h == 0 ? ermine_window_height() : camera.viewport.h;
    int x = camera.viewport.x;
    int y = camera.viewport.y;

    float aspect = (float)w / (float)h;
    float scale = 700.0f;

    ermine_r_scissor(x, y, w, h);
    ermine_r_viewport(x, y, w, h);

    ermine_r_defaults();
    ermine_r_pipeline_begin();
    ermine_r_projection();

    // camera 2d
    float ortho_size = (aspect * scale);
    ermine_ortho(-ortho_size, +ortho_size, -scale, +scale, -1.0f, +1.0f);
    ermine_r_push_matrix();

    ermine_ecs_run("SystemOnRenderer");
}

void ermine_camera_manager_end(void)
{
    ermine_r_draw();
    ermine_r_pop_matrix();
    ermine_r_pipeline_end();
}
