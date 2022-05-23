# Cookbook_Webutils.rb: MySQL Cookbook web-related utilities

require "cgi"
require "dbi"

# These methods generate HTML directly rather than using CGI object methods
# so as to avoid having to create a CGI object.  CGI class methods are used
# because they're available without creating an object.

# Note: The cgi module contains object methods that enable you to generate
# most of the HTML structures provided by the following utility methods.
# However, in my opinion, the cgi methods are more difficult to use than
# the utility methods.

# ----------------------------------------------------------------------
# HTML list generation methods.  These return the list as a string.
# For ordered and unordered lists, pass the items in an array.  The array
# element values are the list items; element keys are ignored.  For
# definition list, pass an array of terms and an array of the corresponding
# definitions.

# The encode argument should be true or false to indicate whether the
# method should perform HTML-encoding of list items.  Default is true.

#@ _MAKE_ORDERED_LIST_
def make_ordered_list(items, encode = true)
  result = ""
  items.each do |item|
    item = CGI.escapeHTML(item.to_s) if encode
    result << "<li>" + item + "</li>"
  end
  return "<ol>" + result + "</ol>"
end
#@ _MAKE_ORDERED_LIST_

#@ _MAKE_UNORDERED_LIST_
def make_unordered_list(items, encode = true)
  result = ""
  items.each do |item|
    item = CGI.escapeHTML(item.to_s) if encode
    result << "<li>" + item + "</li>"
  end
  return "<ul>" + result + "</ul>"
end
#@ _MAKE_UNORDERED_LIST_

#@ _MAKE_DEFINITION_LIST_
def make_definition_list(terms, definitions, encode = true)
  result = ""
  for i in 0...terms.length
    term = terms[i]
    definition = definitions[i]
    if encode
      term = CGI.escapeHTML(term.to_s)
      definition = CGI.escapeHTML(definition.to_s)
    end
    result << "<li>" + term + "</li>"
    result << "<li>" + definition + "</li>"
  end
  return "<dd>" + result + "</dd>"
end
#@ _MAKE_DEFINITION_LIST_

# Create an email hyperlink from a name and email address

#@ _MAKE_EMAIL_LINK_
def make_email_link(name, addr = nil)
  name = CGI.escapeHTML(name.to_s)
  # return name as static text if address is nil or empty
  return name if addr.nil? or addr == ""
  # return a hyperlink otherwise
  return "<a href=\"mailto:#{addr}\">#{name}</a>"
end
#@ _MAKE_EMAIL_LINK_

# ----------------------------------------------------------------------
# Utility methods to generate form list elements.

# make_radio_group(name, values, labels, default, vertical)
# make_checkbox_group(name, values, labels, default, vertical)
# make_popup_menu(name, values, labels, default)
# make_scrolling_list(name, values, labels, default, size, multiple)

# vertical (true/false) indicates whether to put <br /> tags after
# each radio button or checkbox.
# size indicates the number of visible items in a scrolling list.
# multiple is true if a scrolling list is a multiple-pick list.
# For scrolling lists, default should be a scalar for a single-pick
# list, a scalar or an array for a multiple-pick list.  For no default
# selection, pass an unset value or an empty array.


# Check arguments and return a string indicating the problem if they're
# not okay.  This way you get a visual indicator in the web page what
# the problem is.

#@ _MAKE_RADIO_GROUP_
def make_radio_group(name, values, labels, default, vertical)
  str = ""
  for i in 0...values.length do
    # select the item if it corresponds to the default value
    checked = (values[i] == default ? " checked=\"checked\"" : "")
    str << sprintf(
             "<input type=\"radio\" name=\"%s\" value=\"%s\"%s />%s",
             CGI.escapeHTML(name.to_s),
             CGI.escapeHTML(values[i].to_s),
             checked,
             CGI.escapeHTML(labels[i].to_s))
    str << "<br />" if vertical   # display items vertically
  end
  return str
end
#@ _MAKE_RADIO_GROUP_

# default can be a scalar or an array

#@ _MAKE_CHECKBOX_GROUP_
def make_checkbox_group(name, values, labels, default, vertical)
  # make sure default is an array (converts a scalar to an array)
  default = [ default ].flatten
  str = ""
  for i in 0...values.length do
    # select the item if it corresponds to one of the default values
    checked = (default.include?(values[i]) ? " checked=\"checked\"" : "")
    str << sprintf(
             "<input type=\"checkbox\" name=\"%s\" value=\"%s\"%s />%s",
             CGI.escapeHTML(name.to_s),
             CGI.escapeHTML(values[i].to_s),
             checked,
             CGI.escapeHTML(labels[i].to_s))
    str << "<br />" if vertical   # display items vertically
  end
  return str
end
#@ _MAKE_CHECKBOX_GROUP_

#@ _MAKE_POPUP_MENU_
def make_popup_menu(name, values, labels, default)
  str = ""
  for i in 0...values.length do
    # select the item if it corresponds to the default value
    checked = (values[i] == default ? " selected=\"selected\"" : "")
    str << sprintf(
             "<option value=\"%s\"%s>%s</option>",
             CGI.escapeHTML(values[i].to_s),
             checked,
             CGI.escapeHTML(labels[i].to_s))
  end
  str = sprintf(
          "<select name=\"%s\">%s</select>",
          CGI.escapeHTML(name.to_s),
          str)
  return str
end
#@ _MAKE_POPUP_MENU_

# default can be a scalar or an array

#@ _MAKE_SCROLLING_LIST_
def make_scrolling_list(name, values, labels, default, size, multiple)
  # make sure default is an array (converts a scalar to an array)
  default = [ default ].flatten
  str = ""
  for i in 0...values.length do
    # select the item if it corresponds to one of the default values
    checked = (default.include?(values[i]) ? " selected=\"selected\"" : "")
    str << sprintf(
             "<option value=\"%s\"%s>%s</option>",
             CGI.escapeHTML(values[i].to_s),
             checked,
             CGI.escapeHTML(labels[i].to_s))
  end
  str = sprintf(
          "<select name=\"%s\" size=\"%s\"%s>%s</select>",
          CGI.escapeHTML(name.to_s),
          CGI.escapeHTML(size.to_s),
          multiple ? " multiple=\"multiple\"" : "",
          str)
  return str
end
#@ _MAKE_SCROLLING_LIST_

# ----------------------------------------------------------------------

# Given the name of a file upload field, return ...

# Return nil if the requested value is not available.

#@ _GET_UPLOAD_INFO_
def get_upload_info(name)
end
#@ _GET_UPLOAD_INFO_
