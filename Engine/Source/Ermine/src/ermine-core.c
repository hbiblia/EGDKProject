#include "ermine-core.h"
#include "ermine-ecs.h"
#include "ermine-window.h"
#include "ermine-resource.h"

void ermine_init(int argc, char *argv[])
{
    ermine_ecs_init();
    ermine_resource_init(argv[1]);
}

void ermine_main(void)
{
    ermine_window_main();
}
