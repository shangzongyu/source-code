#---
# Excerpted from "Modern Vim",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/modvim for more book information.
#---
class Homophoner
  attr_reader :dictionary

  def initialize(homophones)
    @dictionary = Hash.new
    homophones.each do |wordlist|
      wordlist.each do |word|
        @dictionary[word] = (wordlist - [word]).sort
      end
    end
  end

  def lookup(word)
    dictionary.fetch(word, [])
  end

  def to_s
    "<" + self.class.name + ": " + dictionary.to_s + ">"
  end
end
