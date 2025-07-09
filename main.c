#include <gtk/gtk.h>
#include "model.h"
#include "controller.c" // Basitlik için burada doğrudan ekledik

GtkWidget *notebook;
int terminal_count = 0;

void add_terminal_tab();

void on_enter_pressed(GtkWidget *widget, gpointer data) {
    GtkWidget *current_page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook)));
    GtkWidget *entry = g_object_get_data(G_OBJECT(current_page), "entry");
    GtkTextBuffer *output_buffer = g_object_get_data(G_OBJECT(current_page), "output_buffer");
    const gchar *input = gtk_entry_get_text(GTK_ENTRY(entry));
    controller_handle_input(input, output_buffer, current_page);
    gtk_entry_set_text(GTK_ENTRY(entry), ""); // temizle
}

void add_terminal_tab() {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Komut çıktısı
    GtkWidget *text_view = gtk_text_view_new();
    gtk_widget_set_name(text_view, "terminal_output");
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    GtkTextBuffer *output_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);

    // Komut girişi
    GtkWidget *entry = gtk_entry_new();
    gtk_widget_set_name(entry, "terminal_input");
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    g_signal_connect(entry, "activate", G_CALLBACK(on_enter_pressed), NULL);

    terminal_count++;
    char terminal_label[20];
    snprintf(terminal_label, sizeof(terminal_label), "Terminal %d", terminal_count);

    int page_num = gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, gtk_label_new(terminal_label));
    gtk_widget_show_all(vbox);

    // Verileri sakla
    g_object_set_data(G_OBJECT(vbox), "entry", entry);
    g_object_set_data(G_OBJECT(vbox), "output_buffer", output_buffer);
    g_object_set_data(G_OBJECT(vbox), "terminal_label", g_strdup(terminal_label));

    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), page_num);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    model_init_shared_memory();

    // Stil dosyasını yükle
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Multi Shell");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), vbox, TRUE, TRUE, 0);

    // Notebook (Sekmeler)
    notebook = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);

    // Yeni Terminal butonu
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), button_box, FALSE, FALSE, 0);

    GtkWidget *button = gtk_button_new_with_label("Terminal Ekle");
    gtk_widget_set_name(button, "add_terminal_button");
    g_signal_connect(button, "clicked", G_CALLBACK(add_terminal_tab), NULL);
    gtk_box_pack_end(GTK_BOX(button_box), button, FALSE, FALSE, 0);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
