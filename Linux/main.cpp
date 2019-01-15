#include "../FourtyTwo/Process.hpp"
#include <gtk/gtk.h>

static FourtyTwo::Process *gProcess;

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    GdkPixbuf *pixBuf;
    FourtyTwo::PixelData pixelData;

    gProcess->getPixelData(&pixelData);

    if (!pixelData.pixels) {
        printf("Pixel data is NULL\n");
        return FALSE;
    }

    pixBuf = gdk_pixbuf_new_from_data(pixelData.pixels, GDK_COLORSPACE_RGB, FALSE, 8, pixelData.width, pixelData.height, pixelData.width * 3, NULL, NULL);
    gdk_cairo_set_source_pixbuf(cr, pixBuf, 0, 0);
    cairo_paint(cr);

    return FALSE;
}

static gboolean resize_cb(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    guint width, height;
    GtkStyleContext *context;

    context = gtk_widget_get_style_context(widget);
    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    gProcess->setViewportSize(width, height);

    return FALSE;
}

static void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *drawing_area;

    gProcess = new FourtyTwo::Process();

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Browsery");

    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request (drawing_area, 640, 480);
    gtk_container_add (GTK_CONTAINER (window), drawing_area);

    g_signal_connect(drawing_area, "configure-event", G_CALLBACK(resize_cb), NULL);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), NULL);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
