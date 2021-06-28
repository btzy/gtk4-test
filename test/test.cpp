#include <cstdio>
#include <gtk/gtk.h>

void DialogResponseHandler(GtkDialog*, gint resp, gpointer out_resp_gp) {
    gint* out_resp = static_cast<gint*>(out_resp_gp);
    *out_resp = resp;
}

int main() {
    gtk_init_check();
    g_set_prgname(program_invocation_short_name);

    GtkWidget* widget = gtk_file_chooser_dialog_new("Save File",
                                                    nullptr,
                                                    GTK_FILE_CHOOSER_ACTION_SAVE,
                                                    "_Cancel",
                                                    GTK_RESPONSE_CANCEL,
                                                    "_Save",
                                                    GTK_RESPONSE_ACCEPT,
                                                    nullptr);
    
    gint resp = 0;
    g_signal_connect(G_OBJECT(widget),
                     "response",
                     G_CALLBACK(DialogResponseHandler),
                     static_cast<gpointer>(&resp));
    gtk_widget_show(widget);
    while (resp == 0) g_main_context_iteration(NULL, TRUE);

    GFile* file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(widget));
    printf("%s\n", g_file_get_path(file));
    gtk_window_destroy(GTK_WINDOW(widget));
    return resp;
}
