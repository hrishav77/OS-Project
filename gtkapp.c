#include <gtk/gtk.h>
#include <linux/input.h>
#include <stdio.h>
#include <fcntl.h>  // Include this header for open(), O_WRONLY, and O_NONBLOCK
#include <unistd.h> 

// Function to send key press event to virtual keyboard driver
void send_key_press(int key) {
    // Open input event file for virtual keyboard (replace "/dev/input/eventX" with actual device file)
    int fd = open("/dev/input/event6", O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        g_print("Failed to open input event file\n");
        return;
    }
    
    printf("working");
    // Create input event structure
    struct input_event ev;
    memset(&ev, 0, sizeof(struct input_event));
    
    // Populate input event structure with key press event
    ev.type = EV_KEY;
    ev.code = key;
    ev.value = 1;  // Key press event
    
    // Write input event to input event file
    if (write(fd, &ev, sizeof(struct input_event)) < 0) {
        g_print("Failed to send key press event\n");
    }
    
    // Close input event file
    close(fd);
}

// Callback function for button click event
void on_button_clicked(GtkWidget *widget, gpointer data) {
    int key = GPOINTER_TO_INT(data);
    printf("working1");
    send_key_press(key);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create buttons for each key
    button = gtk_button_new_with_label("A");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), GINT_TO_POINTER(KEY_A));
    gtk_container_add(GTK_CONTAINER(window), button);

    // Add more buttons for other keys as needed...

    gtk_widget_show_all(window);

    gtk_main();
     printf("working2");

    return 0;
}
