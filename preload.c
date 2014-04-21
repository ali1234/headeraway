// preload.c
//
// Copyright (C) 2014 Alistair Buxton <a.j.buxton@gmail.com>
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
