/*  gxfce
 *  Copyright (C) 1999 Olivier Fourdan (fourdan@xfce.org)
 *                2002 Xavier MAILLARD (zedek@fxgsproject.org)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <stdio.h>
#include <string.h>

#include "global.h"
#include "xfce_support.h"
#include "icons/xfce_slogan.xpm"

#ifndef XFCE_LICENSE
#define XFCE_LICENSE "COPYING"
#endif

#ifndef XFCE_AUTHORS
#define XFCE_AUTHORS "ChangeLog"
#endif

#ifndef VERSION
#define VERSION "unknown"
#endif

#define XFCE_VERSION N_("XFce 4: build " VERSION)

static void fill_buffer(const char *filename, char **buf, int *nb)
{
    GError *err = NULL;

    if (!filename)
	return;
    
    g_file_get_contents(filename, buf, nb, &err);

    if(err)
    {
        g_printerr("\nxfce4: %s (line: %d): %s\n\n", __FILE__, __LINE__, 
		err->message);
    }
}

static GtkWidget *create_bold_label(const char *text)
{
    GtkWidget *label;
    char *markup;

    if (!text)
	return gtk_label_new("");

    markup = g_strconcat("<b> ", text, " </b>", NULL);

    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), markup);

    return label;
}

static void info_help_cb(GtkWidget *w, gpointer data)
{
    exec_cmd("xfhelp", FALSE);
}

GtkWidget *create_scrolled_text_view(const char *file)
{
    GtkWidget *frame;
    GtkWidget *sw;
    GtkTextBuffer *textbuffer = gtk_text_buffer_new(NULL);
    GtkWidget *textview = gtk_text_view_new();
    char *buffer;
    int nbytes_read;

    frame = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
    gtk_widget_show(frame);

    sw = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_show(sw);
    gtk_container_add(GTK_CONTAINER(frame), sw);

    fill_buffer(file, &buffer, &nbytes_read);

    if (buffer)
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(textbuffer), buffer, nbytes_read);
    else
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(textbuffer), " ", 1);
    g_free(buffer);

    gtk_text_view_set_buffer(GTK_TEXT_VIEW(textview), textbuffer);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(textview), 6);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(textview), 6);
    gtk_widget_show(textview);
    gtk_container_add(GTK_CONTAINER(sw), textview);

    return frame;
}

static GtkWidget *create_header(void)
{
    GtkWidget *vbox1, *vbox2;
    GdkPixbuf *logo_pb;
    GtkWidget *logo_im;
    GtkWidget *frame;
    GtkWidget *label;

    vbox1 = gtk_vbox_new(FALSE, 4);
    gtk_widget_show(vbox1);

    logo_pb = gdk_pixbuf_new_from_xpm_data((const char **)xfce_slogan_xpm);
    logo_im = gtk_image_new_from_pixbuf(logo_pb);
    g_object_unref(logo_pb);
    gtk_widget_show(logo_im);
    gtk_box_pack_start(GTK_BOX(vbox1), logo_im, FALSE, FALSE, 0);

    frame = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
    gtk_widget_show(frame);
    gtk_box_pack_start(GTK_BOX(vbox1), frame, FALSE, FALSE, 0);

    vbox2 = gtk_vbox_new(FALSE, 6);
    gtk_container_set_border_width(GTK_CONTAINER(vbox2), 4);
    gtk_widget_show(vbox2);
    gtk_container_add(GTK_CONTAINER(frame), vbox2);
    
    label = create_bold_label(_(XFCE_VERSION));
    gtk_widget_show(label);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start(GTK_BOX(vbox2), label, FALSE, FALSE, 0);

    label = create_bold_label(_("By Olivier Fourdan (c) 1997-2002"));
    gtk_widget_show(label);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start(GTK_BOX(vbox2), label, FALSE, FALSE, 0);

    return vbox1;
}

static void add_info_page(GtkNotebook *notebook)
{
    GtkWidget *info_label_1;
    GtkWidget *info_notebook_page;
    GtkWidget *info_bottom_frame;
    GtkWidget *info_view;
    
    info_label_1 = gtk_label_new(_("Info"));
    gtk_widget_show(info_label_1);
  
    info_notebook_page = gtk_vbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(info_notebook_page), 4);
    gtk_widget_show(info_notebook_page);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), info_notebook_page,
	    info_label_1);

    info_bottom_frame = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(info_bottom_frame), GTK_SHADOW_IN);
    gtk_widget_show(info_bottom_frame);
    gtk_box_pack_start(GTK_BOX(info_notebook_page), info_bottom_frame, TRUE, TRUE, 0);

    {
	GtkTextBuffer *tb = gtk_text_buffer_new(NULL);
	char *info_text = "\n\
XFce Desktop Environment\n\
\n\n\
XFce is a collection of programs that together provide the full functionality\n\
of the desktop enviroment. At this time the following programs are part of XFce:\n\
\n\
o Window manager (xfwm4)\n\
   handles the placement on the screen\n\
\n\
o Panel (xfce4)\n\
   start programs, monitor mailboxes, show time\n\
\n\
o File manager (xftree4)\n\
   simple but efficient file manager\n\
\n\
o etc.\n";

	gtk_text_buffer_set_text(tb, info_text, -1);
	info_view = gtk_text_view_new();
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(info_view), tb);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(info_view), FALSE);
	gtk_text_view_set_left_margin(GTK_TEXT_VIEW(info_view), 6);
	gtk_text_view_set_right_margin(GTK_TEXT_VIEW(info_view), 6);
	gtk_widget_show(info_view);
	gtk_container_add(GTK_CONTAINER(info_bottom_frame), info_view);
    }
}

static void add_credits_page(GtkNotebook *notebook)
{
    GtkWidget *info_label;
    GtkWidget *info_notebook_page;
    GtkWidget *info_credits_view;
    char *filename;
    
    info_label = gtk_label_new(_("Credits"));
    gtk_widget_show(info_label);
    
    info_notebook_page = gtk_vbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(info_notebook_page), 4);
    gtk_widget_show(info_notebook_page);
    gtk_notebook_append_page(notebook, info_notebook_page, info_label);

    filename = g_build_filename(DATADIR, XFCE_AUTHORS, NULL);
    info_credits_view = create_scrolled_text_view(filename);
    g_free(filename);
    gtk_container_add(GTK_CONTAINER(info_notebook_page), info_credits_view);
}

static void add_license_page(GtkNotebook *notebook)
{
    GtkWidget *info_label;
    GtkWidget *info_notebook_page;
    GtkWidget *info_license_view;
    char *filename;
    
    info_label = gtk_label_new(_("License"));
    gtk_widget_show(info_label);
    
    info_notebook_page = gtk_vbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(info_notebook_page), 4);
    gtk_widget_show(info_notebook_page);
    gtk_notebook_append_page(notebook, info_notebook_page, info_label);

    filename = g_build_filename(DATADIR, XFCE_LICENSE, NULL);
    info_license_view = create_scrolled_text_view(filename);
    g_free(filename);
    gtk_container_add(GTK_CONTAINER(info_notebook_page), info_license_view);
}

void info_panel_dialog(void)
{
    GtkWidget *info;
    GtkWidget *vbox;
    GtkWidget *header;
    GtkWidget *notebook;
    GtkWidget *info_separator;
    GtkWidget *buttonbox;
    GtkWidget *info_ok_button;
    GtkWidget *info_help_button;

    info = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_position(GTK_WINDOW(info), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(info), _("Info ..."));

    /* Make the info dialog sticky */
    gtk_window_stick(GTK_WINDOW(info));
    gtk_container_set_border_width(GTK_CONTAINER(info), 10);

    vbox = gtk_vbox_new(FALSE, 10);
    gtk_widget_show(vbox);
    gtk_container_add(GTK_CONTAINER(info), vbox);

    /* header with logo */
    header = create_header();
    gtk_box_pack_start(GTK_BOX(vbox), header, FALSE, FALSE, 0);
    
    /* the notebook */
    notebook = gtk_notebook_new();
    gtk_widget_show(notebook);
    gtk_widget_set_size_request(notebook, 300, 400);
    gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);

    /* add pages */
    add_info_page(GTK_NOTEBOOK(notebook));
    add_credits_page(GTK_NOTEBOOK(notebook));
    add_license_page(GTK_NOTEBOOK(notebook));

    /* separator */
    info_separator = gtk_hseparator_new();
    gtk_widget_show(info_separator);
    gtk_box_pack_start(GTK_BOX(vbox), info_separator, FALSE, FALSE, 0);

    /* buttons */
    buttonbox = gtk_hbutton_box_new();
    gtk_widget_show(buttonbox);
    gtk_box_pack_start(GTK_BOX(vbox), buttonbox, FALSE, FALSE, 0);
    
    info_ok_button = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
    gtk_widget_show(info_ok_button);
    gtk_box_pack_start(GTK_BOX(buttonbox), info_ok_button, FALSE, FALSE, 0);

    info_help_button = gtk_button_new_from_stock(GTK_STOCK_HELP);
    gtk_widget_show(info_help_button);
    gtk_box_pack_start(GTK_BOX(buttonbox), info_help_button, FALSE, FALSE, 0);

    gtk_button_box_set_child_secondary(GTK_BUTTON_BOX(buttonbox), info_ok_button, TRUE);
    
    g_signal_connect_swapped(info_ok_button, "clicked", G_CALLBACK(gtk_widget_destroy), info);
    g_signal_connect(info_help_button, "clicked", G_CALLBACK(info_help_cb), NULL);

    gtk_widget_show_all(info);
}
