#include <string.h>
#include <gtk/gtk.h>
#include "model.h"

extern SharedMem *shm;
extern GtkWidget *notebook;

void controller_handle_input(const char *input, GtkTextBuffer *output_buffer, GtkWidget *current_page) {
    char output[1024];

    if (strncmp(input, "@msg", 4) == 0) {
        const char *msg = input + 5;  // skip "@msg "
        model_send_message(msg);

        const char *terminal_label = g_object_get_data(G_OBJECT(current_page), "terminal_label");

        int n_pages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(notebook));
        for (int i = 0; i < n_pages; i++) {
            GtkWidget *page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), i);
            GtkTextBuffer *buffer = g_object_get_data(G_OBJECT(page), "output_buffer");
            GtkTextIter end;
            gtk_text_buffer_get_end_iter(buffer, &end);
            if (page == current_page) {
                snprintf(output, sizeof(output), "[sent] %s\n", msg);
                gtk_text_buffer_insert(buffer, &end, output, -1);
            } else {
                snprintf(output, sizeof(output), "[%s] %s\n", terminal_label, msg);
                gtk_text_buffer_insert(buffer, &end, output, -1);
            }
        }
    } else {
        model_execute_command(input, output, sizeof(output));
        GtkTextIter end;
        gtk_text_buffer_get_end_iter(output_buffer, &end);
        gtk_text_buffer_insert(output_buffer, &end, output, -1);
    }
}
