#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <gtk/gtk.h>

void controller_handle_input(const char *input, GtkTextBuffer *output_buffer);
void controller_refresh_messages(GtkTextBuffer *msg_buffer);

#endif
