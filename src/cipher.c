#include <gtk/gtk.h> 
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* -----------------------------------------------------------
   NUMERIC VIGENERE CIPHER FUNCTIONS
   ----------------------------------------------------------- */

int shift_from_digit(char d) {
    return d - '0';
}

char shift_char(char c, int shift) {
    if (!isalpha(c))
        return c;

    char base = isupper(c) ? 'A' : 'a';
    return (char)((((c - base) + shift + 26) % 26) + base);
}

void vigenere_numeric_encrypt(const char *msg, const char *key, char *out) {
    int keylen = strlen(key);
    int j = 0;

    for (int i = 0; msg[i]; i++) {
        if (isalpha(msg[i])) {
            int s = shift_from_digit(key[j % keylen]);
            out[i] = shift_char(msg[i], s);
            j++;
        } else {
            out[i] = msg[i];
        }
    }
    out[strlen(msg)] = '\0';
}

void vigenere_numeric_decrypt(const char *msg, const char *key, char *out) {
    int keylen = strlen(key);
    int j = 0;

    for (int i = 0; msg[i]; i++) {
        if (isalpha(msg[i])) {
            int s = -shift_from_digit(key[j % keylen]);
            out[i] = shift_char(msg[i], s);
            j++;
        } else {
            out[i] = msg[i];
        }
    }
    out[strlen(msg)] = '\0';
}

/* -----------------------------------------------------------
   GTK UI CODE
   ----------------------------------------------------------- */

GtkTextBuffer *msg_buffer;
GtkTextBuffer *key_buffer;
GtkTextBuffer *output_buffer;

GtkWidget *msg_view;
GtkWidget *key_view;
GtkWidget *output_view;

void on_encrypt(GtkButton *button, gpointer user_data) {
    GtkTextIter start, end;

    gtk_text_buffer_get_bounds(msg_buffer, &start, &end);
    char *msg = gtk_text_buffer_get_text(msg_buffer, &start, &end, FALSE);

    gtk_text_buffer_get_bounds(key_buffer, &start, &end);
    char *key = gtk_text_buffer_get_text(key_buffer, &start, &end, FALSE);

    char *out = malloc(strlen(msg) + 1);
    vigenere_numeric_encrypt(msg, key, out);

    gtk_text_buffer_set_text(output_buffer, out, -1);

    free(out);
    free(msg);
    free(key);
}

void on_decrypt(GtkButton *button, gpointer user_data) {
    GtkTextIter start, end;

    gtk_text_buffer_get_bounds(msg_buffer, &start, &end);
    char *msg = gtk_text_buffer_get_text(msg_buffer, &start, &end, FALSE);

    gtk_text_buffer_get_bounds(key_buffer, &start, &end);
    char *key = gtk_text_buffer_get_text(key_buffer, &start, &end, FALSE);

    char *out = malloc(strlen(msg) + 1);
    vigenere_numeric_decrypt(msg, key, out);

    gtk_text_buffer_set_text(output_buffer, out, -1);

    free(out);
    free(msg);
    free(key);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Numeric Vigenère Cipher");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 500);

    GtkWidget *grid = gtk_grid_new();

    gtk_widget_set_margin_start(grid, 10);
    gtk_widget_set_margin_end(grid, 10);
    gtk_widget_set_margin_top(grid, 10);
    gtk_widget_set_margin_bottom(grid, 10);

    gtk_window_set_child(GTK_WINDOW(window), grid);

    /* Message input */
    GtkWidget *msg_scroll = gtk_scrolled_window_new();
    msg_view = gtk_text_view_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(msg_scroll), msg_view);
    gtk_widget_set_size_request(msg_scroll, 500, 150);
    gtk_widget_set_hexpand(msg_scroll, TRUE);
    gtk_widget_set_vexpand(msg_scroll, TRUE);
    msg_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(msg_view));
    gtk_text_buffer_set_text(msg_buffer, "HELLO WORLD", -1);

    /* Key input */
    GtkWidget *key_scroll = gtk_scrolled_window_new();
    key_view = gtk_text_view_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(key_scroll), key_view);
    gtk_widget_set_size_request(key_scroll, 500, 60);
    gtk_widget_set_hexpand(key_scroll, TRUE);
    gtk_widget_set_vexpand(key_scroll, TRUE);
    key_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(key_view));
    gtk_text_buffer_set_text(key_buffer, "1234", -1);

    /* Output area */
    GtkWidget *output_scroll = gtk_scrolled_window_new();
    output_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output_view), FALSE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(output_scroll), output_view);
    gtk_widget_set_size_request(output_scroll, 500, 150);
    gtk_widget_set_hexpand(output_scroll, TRUE);
    gtk_widget_set_vexpand(output_scroll, TRUE);
    output_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_view));

    /* Buttons */
    GtkWidget *btn_encrypt = gtk_button_new_with_label("Encrypt");
    GtkWidget *btn_decrypt = gtk_button_new_with_label("Decrypt");

    g_signal_connect(btn_encrypt, "clicked", G_CALLBACK(on_encrypt), NULL);
    g_signal_connect(btn_decrypt, "clicked", G_CALLBACK(on_decrypt), NULL);

    /* Layout */
    GtkWidget *lbl_msg = gtk_label_new("Message:");
    gtk_label_set_xalign(GTK_LABEL(lbl_msg), 0.0);
    gtk_grid_attach(GTK_GRID(grid), lbl_msg, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), msg_scroll,                   0, 1, 2, 1);

    GtkWidget *lbl_key = gtk_label_new("Key:");
    gtk_label_set_xalign(GTK_LABEL(lbl_key), 0.0);
    gtk_grid_attach(GTK_GRID(grid), lbl_key, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), key_scroll,                   0, 3, 2, 1);

    gtk_grid_attach(GTK_GRID(grid), btn_encrypt,                  0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_decrypt,                  1, 4, 1, 1);

    GtkWidget *lbl_out = gtk_label_new("Output:");
    gtk_label_set_xalign(GTK_LABEL(lbl_out), 0.0);
    gtk_grid_attach(GTK_GRID(grid), lbl_out, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), output_scroll,                0, 6, 2, 1);

    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app =
        gtk_application_new("com.example.cipher", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

