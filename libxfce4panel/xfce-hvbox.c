/* $Id$ */
/*
 *  OBox Copyright (c) 2002      Red Hat Inc. based on GtkHBox
 *  Copyright      (c) 2006      Jani Monoses <jani@ubuntu.com>
 *  Copyright      (c) 2006-2007 Jasper Huijsmans <jasper@xfce.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#include <libxfce4panel/xfce-panel-macros.h>
#include <libxfce4panel/xfce-hvbox.h>



static void            xfce_hvbox_class_init    (XfceHVBoxClass *klass);
static void            xfce_hvbox_init          (XfceHVBox      *hvbox);
static GtkWidgetClass *xfce_hvbox_get_class     (XfceHVBox      *hvbox);
static void            xfce_hvbox_size_request  (GtkWidget      *widget,
                                                 GtkRequisition *requisition);
static void            xfce_hvbox_size_allocate (GtkWidget      *widget,
                                                 GtkAllocation  *allocation);



G_DEFINE_TYPE (XfceHVBox, xfce_hvbox, GTK_TYPE_BOX)



static void
xfce_hvbox_class_init (XfceHVBoxClass *klass)
{
  GtkWidgetClass *gtkwidget_class;

  gtkwidget_class = GTK_WIDGET_CLASS (klass);
  gtkwidget_class->size_request  = xfce_hvbox_size_request;
  gtkwidget_class->size_allocate = xfce_hvbox_size_allocate;
}



static void
xfce_hvbox_init (XfceHVBox *hvbox)
{
  /* initialize variables */
  hvbox->orientation = GTK_ORIENTATION_HORIZONTAL;
}



static GtkWidgetClass *
xfce_hvbox_get_class (XfceHVBox *hvbox)
{
  GType type;

  if (hvbox->orientation == GTK_ORIENTATION_HORIZONTAL)
    type = GTK_TYPE_HBOX;
  else
    type = GTK_TYPE_VBOX;

  /* return the widget class of the type */
  return GTK_WIDGET_CLASS (gtk_type_class (type));
}



static void
xfce_hvbox_size_request (GtkWidget      *widget,
                         GtkRequisition *requisition)
{
  GtkWidgetClass *klass;

  /* get the widget class */
  klass = xfce_hvbox_get_class (XFCE_HVBOX (widget));

  (*klass->size_request) (widget, requisition);
}



static void
xfce_hvbox_size_allocate (GtkWidget     *widget,
                          GtkAllocation *allocation)
{
  GtkWidgetClass *klass;

  /* get the widget class */
  klass = xfce_hvbox_get_class (XFCE_HVBOX (widget));

  (*klass->size_allocate) (widget, allocation);
}



/**
 * xfce_hvbox_new:
 * @orientation : Orientation of the #XfceHVBox
 * @homogeneous : whether all children should be allocated the same size
 * @spacing     : spacing between #XfceHVBox children
 *
 * Creates a new #XfceHVBox container widget.
 *
 * Return value: the newly allocated #XfceHVBox container widget.
 **/
GtkWidget *
xfce_hvbox_new (GtkOrientation orientation,
                gboolean       homogeneous,
                gint           spacing)
{
  XfceHVBox *box;

  /* create new object */
  box = g_object_new (XFCE_TYPE_HVBOX, "homogeneous", homogeneous, "spacing", spacing, NULL);

  /* store the orientation */
  box->orientation = orientation;

  return GTK_WIDGET (box);
}



/**
 * xfce_hvbox_set_orientation:
 * @hvbox       : #XfceHVBox
 * @orientation : the new orientation of the #XfceHVBox
 *
 * Set the new orientation of the #XfceHVBox container widget.
 **/
void
xfce_hvbox_set_orientation (XfceHVBox      *hvbox,
                            GtkOrientation  orientation)
{
  g_return_if_fail (XFCE_IS_HVBOX (hvbox));

  if (G_LIKELY (hvbox->orientation != orientation))
    {
      /* store new orientation */
      hvbox->orientation = orientation;

      /* queue a resize */
      gtk_widget_queue_resize (GTK_WIDGET (hvbox));
    }
}



/**
 * xfce_hvbox_get_orientation:
 * @hvbox       : #XfceHVBox
 *
 * Returns the current orientation of the #XfceHVBox.
 **/
GtkOrientation
xfce_hvbox_get_orientation (XfceHVBox *hvbox)
{
  g_return_val_if_fail (XFCE_IS_HVBOX (hvbox), GTK_ORIENTATION_HORIZONTAL);

  return hvbox->orientation;
}
