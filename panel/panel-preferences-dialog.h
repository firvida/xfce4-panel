/* $Id$ */
/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __PANEL_PREFERENCES_DIALOG_H__
#define __PANEL_PREFERENCES_DIALOG_H__

#include <gtk/gtk.h>
#include <panel/panel-application.h>
#include <panel/panel-window.h>

G_BEGIN_DECLS

typedef struct _PanelPreferencesDialogClass PanelPreferencesDialogClass;
typedef struct _PanelPreferencesDialog      PanelPreferencesDialog;

#define PANEL_TYPE_PREFERENCES_DIALOG            (panel_preferences_dialog_get_type ())
#define PANEL_PREFERENCES_DIALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), PANEL_TYPE_PREFERENCES_DIALOG, PanelPreferencesDialog))
#define PANEL_PREFERENCES_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PANEL_TYPE_PREFERENCES_DIALOG, PanelPreferencesDialogClass))
#define PANEL_IS_PREFERENCES_DIALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PANEL_TYPE_PREFERENCES_DIALOG))
#define PANEL_IS_PREFERENCES_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PANEL_TYPE_PREFERENCES_DIALOG))
#define PANEL_PREFERENCES_DIALOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), PANEL_TYPE_PREFERENCES_DIALOG, PanelPreferencesDialogClass))

GType      panel_preferences_dialog_get_type (void) G_GNUC_CONST;

void       panel_preferences_dialog_show     (PanelWindow *active);

G_END_DECLS

#endif /* !__PANEL_PREFERENCES_DIALOG_H__ */
