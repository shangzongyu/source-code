# cookbook_webutils.py: MySQL Cookbook web-related utilities

import types
import cgi

# Conversion to string with str(x) is done here for any value passed
# to cgi.escape because that method requires a string first argument.

# ----------------------------------------------------------------------
# HTML list generation methods.  These return the list as a string.
# For ordered and unordered lists, pass the items in a tuple or list.
# For definition lists, pass two tuples or lists, one for terms and the
# other for the corresponding definitions.

# The encode argument should be true or false to indicate whether the
# method should perform HTML-encoding of list items.  Default is true.

#@ _MAKE_ORDERED_LIST_
def make_ordered_list(items, encode=True):
  result = ""
  for item in items:
    if item is None:  # handle possibility of NULL item
      item = ""
    # make sure item is a string, then encode if necessary
    item = str(item)
    if encode:
      item = cgi.escape(item, 1)
    result += "<li>" + item + "</li>"
  return "<ol>" + result + "</ol>"
#@ _MAKE_ORDERED_LIST_

#@ _MAKE_UNORDERED_LIST_
def make_unordered_list(items, encode=True):
  result = ""
  for item in items:
    if item is None:  # handle possibility of NULL item
      item = ""
    # make sure item is a string, then encode if necessary
    item = str(item)
    if encode:
      item = cgi.escape(item, 1)
    result += "<li>" + item + "</li>"
  return "<ul>" + result + "</ul>"
#@ _MAKE_UNORDERED_LIST_

#@ _MAKE_DEFINITION_LIST_
def make_definition_list(terms, definitions, encode=True):
  result = ""
  for i in range(len(terms)):
    term = terms[i]
    definition = definitions[i]
    if term is None:  # handle possibility of NULL values
      term = ""
    if definition is None:
      definition = ""
    # make sure term/definition are strings, then encode if necessary
    term = str(term)
    definition = str(definition)
    if encode:
      term = cgi.escape(term, 1)
      definition = cgi.escape(definition, 1)
    result += "<dt>" + term + "</dt>"
    result += "<dd>" + definition + "</dd>"
  return "<dd>" + result + "</dd>"
#@ _MAKE_DEFINITION_LIST_

# Create an email hyperlink from a name and email address

#@ _MAKE_EMAIL_LINK_
def make_email_link(name, addr=None):
  name = cgi.escape(name, 1)
  # return name as static text if address is None or empty
  if addr is None or addr == '':
    return name
  # return a hyperlink otherwise
  return '<a href="mailto:%s">%s</a>' % (addr, name)
#@ _MAKE_EMAIL_LINK_

# ----------------------------------------------------------------------
# Utility methods to generate form list elements.

# make_radio_group(name, values, labels, default, vertical)
# make_checkbox_group(name, values, labels, default, vertical)
# make_popup_menu(name, values, labels, default)
# make_scrolling_list(name, values, labels, default, size)

# vertical (true/false) indicates whether to put <br /> tags after
# each radio button or checkbox.
# size indicates the number of visible items in a scrolling list.
# multiple is true if a scrolling list is a multiple-pick list.
# For scrolling lists, default should be a scalar for a single-pick
# list, a scalar or a list for a multiple-pick list.  For no default
# selection, pass an unset value or an empty list.


# Check arguments and return a string indicating the problem if they're
# not okay.  This way you get a visual indicator in the web page what
# the problem is.

#@ _MAKE_RADIO_GROUP_
def make_radio_group(name, values, labels, default, vertical):
  result = ''
  # make sure name and default are strings
  name = str(name)
  default = str(default)
  for i in range(len(values)):
    # make sure value and label are strings
    value = str(values[i])
    label = str(labels[i])
    # select the item if it corresponds to the default value
    if value == default:
      checked = ' checked="checked"'
    else:
      checked = ''
    result += '<input type="radio" name="%s" value="%s"%s />%s' % (
                cgi.escape(name, 1),
                cgi.escape(value, 1),
                checked,
                cgi.escape(label, 1))
    if vertical:
      result += '<br />'  # display items vertically
  return result
#@ _MAKE_RADIO_GROUP_

# default can be a scalar or a list/tuple

#@ _MAKE_CHECKBOX_GROUP_
def make_checkbox_group(name, values, labels, default, vertical):
  if type(default) not in (types.ListType, types.TupleType):
    default = [default]   # convert scalar to list
  result = ''
  # make sure name is a string
  name = str(name)
  for i in range(len(values)):
    # make sure value and label are strings
    value = str(values[i])
    label = str(labels[i])
    checked = ''
    for d in default:
      d = str(d)
      if value == d:
        checked = ' checked="checked"'
        break
    result += '<input type="checkbox" name="%s" value="%s"%s />%s' % (
                cgi.escape(name, 1),
                cgi.escape(value, 1),
                checked,
                cgi.escape(label, 1))
    if vertical:
      result += '<br />'  # display items vertically
  return result
#@ _MAKE_CHECKBOX_GROUP_

#@ _MAKE_POPUP_MENU_
def make_popup_menu(name, values, labels, default):
  result = ''
  # make sure name and default are strings
  name = str(name)
  default = str(default)
  for i in range(len(values)):
    # make sure value and label are strings
    value = str(values[i])
    label = str(labels[i])
    # select the item if it corresponds to the default value
    if value == default:
      checked = ' selected="selected"'
    else:
      checked = ''
    result += '<option value="%s"%s>%s</option>' % (
                cgi.escape(value, 1),
                checked,
                cgi.escape(label, 1))

  result = '<select name="%s">%s</select>' % (
                 cgi.escape(name, 1), result)
  return result
#@ _MAKE_POPUP_MENU_

# default can be a scalar or a list/tuple

#@ _MAKE_SCROLLING_LIST_
def make_scrolling_list(name, values, labels, default, size, multiple):
  if type(default) not in (types.ListType, types.TupleType):
    default = [default]   # convert scalar to list
  result = ''
  # make sure name and size are strings
  name = str(name)
  size = str(size)
  for i in range(len(values)):
    # make sure value and label are strings
    value = str(values[i])
    label = str(labels[i])
    # select the item if it corresponds to one of the default values
    checked = ''
    for d in default:
      d = str(d)
      if value == d:
        checked = ' selected="selected"'
        break
    result += '<option value="%s"%s>%s</option>' % (
                cgi.escape(value, 1),
                checked,
                cgi.escape(label, 1))

  if multiple:
    multiple = ' multiple="multiple"'
  else:
    multiple = ''
  result = '<select name="%s" size="%s"%s>%s</select>' % (
             cgi.escape(name, 1),
             cgi.escape(size, 1),
             multiple,
             result)
  return result
#@ _MAKE_SCROLLING_LIST_

# ----------------------------------------------------------------------
# Utility methods to generate form hidden elements, text fields, and
# submit buttons.

# make_hidden_field(name, value)
# make_text_field(name, value, size)
# make_submit_button(name, value)

#@ _MAKE_HIDDEN_FIELD_
def make_hidden_field(name, value):
  # make sure escaped values are strings
  name = str(name)
  value = str(value)
  return '<input type="hidden" name="%s" value="%s" />' % (
           cgi.escape(name, 1),
           cgi.escape(value, 1))
#@ _MAKE_HIDDEN_FIELD_

#@ _MAKE_TEXT_FIELD_
def make_text_field(name, value, size=10):
  # make sure escaped values are strings
  name = str(name)
  value = str(value)
  size = str(size)
  return '<input type="text" name="%s" value="%s" size="%s" />' % (
           cgi.escape(name, 1),
           cgi.escape(value, 1),
           cgi.escape(size, 1))
#@ _MAKE_TEXT_FIELD_

#@ _MAKE_SUBMIT_BUTTON_
def make_submit_button(name, value):
  # make sure escaped values are strings
  name = str(name)
  value = str(value)
  return '<input type="submit" name="%s" value="%s" />' % (
           cgi.escape(name, 1),
           cgi.escape(value, 1))
#@ _MAKE_SUBMIT_BUTTON_
