#---
# Excerpted from "Modern Vim",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/modvim for more book information.
#---
require 'rspec'
require_relative '../lib/homophoner'

describe Homophoner do
  let(:to_sounds)    { ["to", "two", "too"] }
  let(:there_sounds) { ["there", "they're", "their"] }
  let(:eye_sounds)   { ["I", "eye"] }
  subject { Homophoner.new([to_sounds, there_sounds, eye_sounds]) }

  it '#dictionary contains all words' do
    expect(subject.dictionary).to eql({
      "there"   => ["their", "they're"],
      "their"   => ["there", "they're"],
      "they're" => ["their", "there"],
      "to"      => ["too", "two"],
      "too"     => ["to",  "two"],
      "two"     => ["to",  "too"],
      "I"       => ["eye"],
      "eye"     => ["I"],
    })
  end

  it '#lookup(word) fetches homophones' do
    expect(subject.lookup("to")).to eql(["too", "two"])
    expect(subject.lookup("vim")).to eql([])
  end
end
