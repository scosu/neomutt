/**
 * @file
 * Shared code for the Alias and Query Dialogs
 *
 * @authors
 * Copyright (C) 2020 Richard Russon <rich@flatcap.org>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @page alias_gui Shared code for the Alias and Query Dialogs
 *
 * Shared code for the Alias and Query Dialogs
 */

#include "config.h"
#include <stdlib.h>
#include <string.h>
#include "mutt/lib.h"
#include "address/lib.h"
#include "config/lib.h"
#include "gui.h"
#include "lib.h"
#include "alias.h"
#include "mutt_menu.h"
#include "sort.h"

/**
 * alias_config_observer - Listen for `sort_alias` configuration changes and reorders menu items accordingly
 */
int alias_config_observer(struct NotifyCallback *nc)
{
  if (!nc->event_data)
    return -1;
  if (nc->event_type != NT_CONFIG)
    return 0;

  struct EventConfig *ec = nc->event_data;

  if (!mutt_str_equal(ec->name, "sort_alias"))
    return 0;

  struct AliasMenuData *mdata = nc->global_data;

  alias_array_sort(&mdata->ava, mdata->sub);

  return 0;
}

/**
 * alias_color_observer - Listen for color configuration changes and refreshes the menu
 */
int alias_color_observer(struct NotifyCallback *nc)
{
  if ((nc->event_type != NT_COLOR) || !nc->event_data || !nc->global_data)
    return -1;

  struct Menu *menu = nc->global_data;
  menu->redraw = REDRAW_FULL;

  return 0;
}

/**
 * alias_array_alias_add - Add an Alias to the AliasViewArray
 * @param ava Array of Aliases
 * @param alias Alias to add
 *
 * @note The Alias is wrapped in an AliasView
 * @note Call alias_array_sort() to sort and reindex the AliasViewArray
 */
int alias_array_alias_add(struct AliasViewArray *ava, struct Alias *alias)
{
  if (!ava || !alias)
    return -1;

  struct AliasView av = {
    .num = 0,
    .orig_seq = ARRAY_SIZE(ava),
    .is_tagged = false,
    .is_deleted = false,
    .is_visible = true,
    .alias = alias,
  };
  ARRAY_ADD(ava, av);
  return ARRAY_SIZE(ava);
}

/**
 * alias_array_alias_delete - Delete an Alias from the AliasViewArray
 * @param ava    Array of Aliases
 * @param alias Alias to remove
 *
 * @note Call alias_array_sort() to sort and reindex the AliasViewArray
 */
int alias_array_alias_delete(struct AliasViewArray *ava, struct Alias *alias)
{
  if (!ava || !alias)
    return -1;

  struct AliasView *avp = NULL;
  ARRAY_FOREACH(avp, ava)
  {
    if (avp->alias != alias)
      continue;

    ARRAY_REMOVE(ava, avp);
    break;
  }

  return ARRAY_SIZE(ava);
}

/**
 * alias_array_count_visible - Count number of visible Aliases
 * @param ava Array of Aliases
 */
int alias_array_count_visible(struct AliasViewArray *ava)
{
  int count = 0;

  struct AliasView *avp = NULL;
  ARRAY_FOREACH(avp, ava)
  {
    if (avp->is_visible)
      count++;
  }

  return count;
}

/**
 * menu_create_alias_title - Create a title string for the Menu
 * @param menu_name Menu name
 * @param limit     Limit being applied
 *
 * @note Caller must free the returned string
 */
char *menu_create_alias_title(char *menu_name, char *limit)
{
  if (limit)
  {
    char *tmp_str = NULL;
    char *new_title = NULL;

    mutt_str_asprintf(&tmp_str, _("Limit: %s"), limit);
    mutt_str_asprintf(&new_title, "%s - %s", menu_name, tmp_str);

    FREE(&tmp_str);

    return new_title;
  }
  else
  {
    return strdup(menu_name);
  }
}
