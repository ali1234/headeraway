// preload.c
// Alistair Buxton <a.j.buxton@gmail.com>

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include <glib-object.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

void __attribute__ ((constructor)) load(void);

// Called when the library is loaded and before dlopen() returns
void load(void)
{
    fprintf(stderr, "preload hack loaded...\n");
}

GtkWidget *gtk_header_bar_new(void)
{
    GtkWidget *bar = gtk_frame_new(NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(bar), box);

    GtkWidget *start_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(box), start_box, FALSE, FALSE, 0);

    GtkWidget *end_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_end(GTK_BOX(box), end_box, FALSE, FALSE, 0);

    g_object_set_data(G_OBJECT(bar), "start_box", start_box);
    g_object_set_data(G_OBJECT(bar), "end_box", end_box);

    gtk_widget_set_visible(box, TRUE);
    gtk_widget_set_visible(start_box, TRUE);
    gtk_widget_set_visible(end_box, TRUE);

    GtkStyleContext *context = gtk_widget_get_style_context (GTK_WIDGET (bar));
    gtk_style_context_add_class (context, "header-bar");
    gtk_style_context_add_class (context, GTK_STYLE_CLASS_HORIZONTAL);
    gtk_widget_set_visible(bar, TRUE);
    return bar;
}

void gtk_header_bar_set_title (GtkHeaderBar *bar, const gchar *title)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(bar));
    if (GTK_IS_WINDOW (toplevel))
    {
        gtk_window_set_title(GTK_WINDOW(toplevel), title); /* Perform action on toplevel. */
    }
}

const gchar *  gtk_header_bar_get_title (GtkHeaderBar *bar) { return NULL; }
void gtk_header_bar_set_subtitle (GtkHeaderBar *bar, const gchar *subtitle) { ; }
const gchar *  gtk_header_bar_get_subtitle (GtkHeaderBar *bar) { return NULL; }
void gtk_header_bar_set_custom_title (GtkHeaderBar *bar, GtkWidget *title_widget) { ; }
GtkWidget *  gtk_header_bar_get_custom_title (GtkHeaderBar *bar) { return NULL; }
void gtk_header_bar_set_show_close_button (GtkHeaderBar *bar, gboolean setting) { ; }
gboolean gtk_header_bar_get_show_close_button (GtkHeaderBar *bar) { return FALSE; }

void gtk_header_bar_pack_start(GtkHeaderBar *bar, GtkWidget *child)
{
    GtkBox *box = g_object_get_data(G_OBJECT(bar), "start_box");
    gtk_box_pack_start(box, child, FALSE, FALSE, 0);
}

void gtk_header_bar_pack_end(GtkHeaderBar *bar, GtkWidget *child)
{
    GtkBox *box = g_object_get_data(G_OBJECT(bar), "end_box");
    gtk_box_pack_start(box, child, FALSE, FALSE, 0);
}
