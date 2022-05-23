<?php
# Cookbook_Webutils.php: MySQL Cookbook web-related utilities

# ----------------------------------------------------------------------
# HTML list generation functions.  These return the list as a string.
# For ordered and unordered lists, pass the items in an array.  The array
# element values are the list items; element keys are ignored.  For
# definition list, pass an array of terms and an array of the corresponding
# definitions.

# The $encode argument should be true or false to indicate whether the
# function should perform HTML-encoding of list items.  Default is true.

#@ _MAKE_ORDERED_LIST_
function make_ordered_list ($items, $encode = TRUE)
{
  $result = "";
  foreach ($items as $val)
  {
    if ($encode)
      $val = htmlspecialchars ($val);
    $result .= "<li>$val</li>";
  }
  return ("<ol>$result</ol>");
}
#@ _MAKE_ORDERED_LIST_

#@ _MAKE_UNORDERED_LIST_
function make_unordered_list ($items, $encode = TRUE)
{
  $result = "";
  foreach ($items as $val)
  {
    if ($encode)
      $val = htmlspecialchars ($val);
    $result .= "<li>$val</li>";
  }
  return ("<ul>$result</ul>");
}
#@ _MAKE_UNORDERED_LIST_

#@ _MAKE_DEFINITION_LIST_
function make_definition_list ($terms, $definitions, $encode = TRUE)
{
  $result = "";
  $n = count ($terms);
  for ($i = 0; $i < $n; $i++)
  {
    $term = $terms[$i];
    $definition = $definitions[$i];
    if ($encode)
    {
      $term = htmlspecialchars ($term);
      $definition = htmlspecialchars ($definition);
    }
    $result .= "<dt>$term</dt><dd>$definition</dd>";
  }
  return ("<dl>$result</dl>");
}
#@ _MAKE_DEFINITION_LIST_

# Create an email hyperlink from a name and email address

#@ _MAKE_EMAIL_LINK_
function make_email_link ($name, $addr = NULL)
{
  $name = htmlspecialchars ($name);
  # return name as static text if address is NULL or empty
  if ($addr === NULL || $addr == '')
    return ($name);
  # return a hyperlink otherwise
  return (sprintf ('<a href="mailto:%s">%s</a>', $addr, $name));
}
#@ _MAKE_EMAIL_LINK_

# ----------------------------------------------------------------------
# Utility functions to generate form list elements.

# make_radio_group ($name, $values, $labels, $default, $vertical)
# make_checkbox_group ($name, $values, $labels, $default, $vertical)
# make_popup_menu ($name, $values, $labels, $default)
# make_scrolling_list ($name, $values, $labels, $default, $size, $multiple)

# $vertical (true/false) indicates whether to put <br /> tags after
# each radio button or checkbox.
# $size indicates the number of visible items in a scrolling list.
# $multiple is true if a scrolling list is a multiple-pick list.
# For scrolling lists, $default should be a scalar for a single-pick
# list, a scalar or an array for a multiple-pick list.  For no default
# selection, pass an unset value or an empty array.


# Check arguments and return a string indicating the problem if they're
# not okay.  This way you get a visual indicator in the web page what
# the problem is.

#@ _MAKE_RADIO_GROUP_
function make_radio_group ($name, $values, $labels, $default, $vertical)
{
  $result = '';
  for ($i = 0; $i < count ($values); $i++)
  {
    # select the item if it corresponds to the default value
    $checked = ($values[$i] == $default ? ' checked="checked"' : '');
    $result .= sprintf (
                 '<input type="radio" name="%s" value="%s"%s />%s',
                 htmlspecialchars ($name),
                 htmlspecialchars ($values[$i]),
                 $checked,
                 htmlspecialchars ($labels[$i]));
    if ($vertical)
      $result .= '<br />'; # display items vertically
  }
  return ($result);
}
#@ _MAKE_RADIO_GROUP_

# $default can be a scalar or an array

#@ _MAKE_CHECKBOX_GROUP_
function make_checkbox_group ($name, $values, $labels, $default, $vertical)
{
  if (!is_array ($default))
    $default = array ($default);  # convert scalar to array
  $result = '';
  for ($i = 0; $i < count ($values); $i++)
  {
    # select the item if it corresponds to one of the default values
    $checked = '';
    foreach ($default as $val)
    {
      if ($values[$i] == $val)
      {
        $checked = ' checked="checked"';
        break;
      }
    }
    $result .= sprintf (
                 '<input type="checkbox" name="%s" value="%s"%s />%s',
                 htmlspecialchars ($name),
                 htmlspecialchars ($values[$i]),
                 $checked,
                 htmlspecialchars ($labels[$i]));
    if ($vertical)
      $result .= '<br />'; # display items vertically
  }
  return ($result);
}
#@ _MAKE_CHECKBOX_GROUP_

#@ _MAKE_POPUP_MENU_
function make_popup_menu ($name, $values, $labels, $default)
{
  $result = '';
  for ($i = 0; $i < count ($values); $i++)
  {
    # select the item if it corresponds to the default value
    $checked = ($values[$i] == $default ? ' selected="selected"' : '');
    $result .= sprintf (
                 '<option value="%s"%s>%s</option>',
                 htmlspecialchars ($values[$i]),
                 $checked,
                 htmlspecialchars ($labels[$i]));
  }
  $result = sprintf (
              '<select name="%s">%s</select>',
              htmlspecialchars ($name),
              $result);
  return ($result);
}
#@ _MAKE_POPUP_MENU_

# $default can be a scalar or an array

#@ _MAKE_SCROLLING_LIST_
function make_scrolling_list ($name, $values, $labels, $default,
                $size, $multiple)
{
  if (!is_array ($default))
    $default = array ($default);  # convert scalar to array
  $result = '';
  for ($i = 0; $i < count ($values); $i++)
  {
    # select the item if it corresponds to one of the default values
    $checked = '';
    foreach ($default as $val)
    {
      if ($values[$i] == $val)
      {
        $checked = ' selected="selected"';
        break;
      }
    }
    $result .= sprintf (
                 '<option value="%s"%s>%s</option>',
                 htmlspecialchars ($values[$i]),
                 $checked,
                 htmlspecialchars ($labels[$i]));
  }
  $result = sprintf (
              '<select name="%s" size="%s"%s>%s</select>',
              htmlspecialchars ($name),
              htmlspecialchars ($size),
              $multiple ? ' multiple="multiple"' : '',
              $result);
  return ($result);
}
#@ _MAKE_SCROLLING_LIST_

# ----------------------------------------------------------------------
# Utility functions to generate form hidden elements, text fields, and
# submit buttons.

# make_hidden_field ($name, $value)
# make_text_field ($name, $value, $size)
# make_submit_button ($name, $value)

#@ _MAKE_HIDDEN_FIELD_
function make_hidden_field ($name, $value)
{
  $result = sprintf (
              '<input type="hidden" name="%s" value="%s" />',
              htmlspecialchars ($name),
              htmlspecialchars ($value));
  return ($result);
}
#@ _MAKE_HIDDEN_FIELD_

#@ _MAKE_TEXT_FIELD_
function make_text_field ($name, $value, $size = 10)
{
  $result = sprintf (
              '<input type="text" name="%s" value="%s" size="%s" />',
              htmlspecialchars ($name),
              htmlspecialchars ($value),
              htmlspecialchars ($size));
  return ($result);
}
#@ _MAKE_TEXT_FIELD_

#@ _MAKE_SUBMIT_BUTTON_
function make_submit_button ($name, $value)
{
  $result = sprintf (
              '<input type="submit" name="%s" value="%s" />',
              htmlspecialchars ($name),
              htmlspecialchars ($value));
  return ($result);
}
#@ _MAKE_SUBMIT_BUTTON_

# ----------------------------------------------------------------------
# Functions for obtaining web input parameter and environment values

# All of the functions that extract values from the script environment
# return NULL if the requested value is not available.

# get_param_val() retrieves a get or post variable, stripping slashes
# added by magic_quotes_gpc if necessary.  Assumes that track_vars is on.
# Doesn't assume anything about magic_quotes_gpc, and is neutral to the
# setting of register_globals (both of which are removed as of PHP 5.4,
# anyway).

# The helper function strip_slash_helper() is used to strip backslashes,
# accounting for whether the value is a scalar or an array.  It works even
# for nested arrays (it's possible to create input parameters as nested
# arrays as of PHP 4).

#@ _STRIP_SLASH_HELPER_
function strip_slash_helper ($val)
{
  if (!is_array ($val))
    $val = stripslashes ($val);
  else
  {
    foreach ($val as $k => $v)
      $val[$k] = strip_slash_helper ($v);
  }
  return ($val);
}
#@ _STRIP_SLASH_HELPER_

#@ _GET_PARAM_VAL_
function get_param_val ($name)
{
  $val = NULL;
  if (isset ($_GET[$name]))
    $val = $_GET[$name];
  else if (isset ($_POST[$name]))
    $val = $_POST[$name];
  if (isset ($val) && get_magic_quotes_gpc ())
    $val = strip_slash_helper ($val);
  return ($val);
}
#@ _GET_PARAM_VAL_

# Get a list of all the (unique) parameter names present in
# get or post variables.

#@ _GET_PARAM_NAMES_
function get_param_names ()
{
  # construct an array in which each element has a parameter name as
  # both key and value.  (Using names as keys eliminates duplicates.)
  $names = array ();
  foreach (array_keys ($_GET) as $name)
    $names[$name] = $name;
  foreach (array_keys ($_POST) as $name)
    $names[$name] = $name;
  return ($names);
}
#@ _GET_PARAM_NAMES_

# Given the name of a file upload field, return a four element associative
# array containing information about the file.  The element names are:
# tmp_name - name of temporary file on server
# name - original name of file on client
# size - size of file in bytes
# type - MIME type of file

#@ _GET_UPLOAD_INFO_
function get_upload_info ($name)
{
  # Check the $_FILES array tmp_name member to make sure there is a
  # file. (The entry might be present even if no file was uploaded.)
  $val = NULL;
  if (isset ($_FILES[$name])
      && $_FILES[$name]["tmp_name"] != ""
      && $_FILES[$name]["tmp_name"] != "none")
    $val = $_FILES[$name];
  return ($val);
}
#@ _GET_UPLOAD_INFO_

# Get the value of a server variable.

#@ _GET_SERVER_VAL_
function get_server_val ($name)
{
  $val = NULL;
  if (isset ($_SERVER[$name]))
    $val = $_SERVER[$name];
  return ($val);
}
#@ _GET_SERVER_VAL_
?>
