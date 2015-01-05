#include <gtk/gtk.h>
#include <sstream>
#include <ctime>

static unsigned long start;
static GtkWidget *label;

static void start_timer(GtkWidget *widget, gpointer data)
{
	start = clock();
	gtk_label_set_text(GTK_LABEL(label), "Stopwatch is running...");
}

static void stop_timer(GtkWidget *widget, gpointer data)
{
	std::stringstream str;
	str << "Elapsed time is ";
	str << ((double)clock() - start) / CLOCKS_PER_SEC;
	gtk_label_set_text(GTK_LABEL(label), str.str().c_str());
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *startButton;
	GtkWidget *stopButton;

	gtk_init(&argc, &argv);

	//make window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "D. Buff's Stopwatch");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	//make grid
	grid = gtk_grid_new();
	//add grid
	gtk_container_add(GTK_CONTAINER(window), grid);

	//make components
	startButton = gtk_button_new_with_label("Start");
	g_signal_connect(startButton, "clicked", G_CALLBACK(start_timer), NULL);

	stopButton = gtk_button_new_with_label("Stop");
	g_signal_connect(stopButton, "clicked", G_CALLBACK(stop_timer), NULL);

	label = gtk_label_new("Press Start to begin timing.");

	//add components to grid
	gtk_grid_attach(GTK_GRID(grid), startButton, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), stopButton, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 2, 1);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}