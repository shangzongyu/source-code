#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
TRANSITIONS = {
  initial: {header: :reading},
  reading: {data: :reading, trailer: :done},
}

state = :initial

while state != :done && state != :error
  msg = get_next_message()
  state = TRANSITIONS[state][msg.msg_type] || :error 
end
