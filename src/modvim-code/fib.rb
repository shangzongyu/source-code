#---
# Excerpted from "Modern Vim",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/modvim for more book information.
#---
def fibonacci(n)
  return n if (0..1).include?(n)
  fibonacci(n-1) + fibonacci(n-2)
end
puts fibonacci(5)
puts fibonacci(6)
puts fibonacci(7)
