#pragma once

#ifndef ERMINE_WINDOW_H
#define ERMINE_WINDOW_H
#include <stdio.h>
#include <stdbool.h>
#include "ermine-ccolor.h"

typedef struct {
    char *title;
    int width;
    int height;
    void (*fn_init)(void);
    void (*fn_renderer)(void);
}ermine_window_desc_t;

// declarar una func void


ermine_public void ermine_window_close(void);
ermine_public void ermine_window_new(const char *title, int width, int height);
ermine_public void ermine_window_set_title(const char *title);
ermine_public void ermine_window_set_size(int width, int height);

ermine_public void ermine_window_fn_init(void (*fn_init)(void));
ermine_public void ermine_window_fn_renderer(void (*fn_renderer)(void));

ermine_public const char *ermine_window_title(void);
ermine_public int ermine_window_width(void);
ermine_public int ermine_window_height(void);

ermine_public float ermine_window_delta(void);
ermine_public float ermine_window_dpi(void);

bool ermine_window_is_init(void);
ermine_private ermine_window_desc_t ermine_window_get_default(void);
ermine_private void ermine_window_main(void);

#endif // ERMINE_WINDOW_H