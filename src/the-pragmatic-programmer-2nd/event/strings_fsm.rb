#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
TRANSITIONS = {

  # current        new state        action to take
  #---------------------------------------------------------

  look_for_string: {
    '"'      => [ :in_string,       :start_new_string ],
    :default => [ :look_for_string, :ignore ],
  },

  in_string: {
    '"'      => [ :look_for_string, :finish_current_string ],
    '\\'     => [ :copy_next_char,  :add_current_to_string ],
    :default => [ :in_string,       :add_current_to_string ],
  },

  copy_next_char: {
    :default => [ :in_string,       :add_current_to_string ],
  },
}

state = :look_for_string
result = []

while ch = STDIN.getc
  state, action = TRANSITIONS[state][ch] || TRANSITIONS[state][:default]
  case action
  when :ignore
  when :start_new_string
    result = []
  when :add_current_to_string
    result << ch
  when :finish_current_string
    puts result.join
  end
end
