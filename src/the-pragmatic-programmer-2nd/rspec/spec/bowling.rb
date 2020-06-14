#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
class BowlingScore
  attr_reader :total

  def initialize
    @total = 0
  end

  def add_pins(n)
    @total += n
  end
end

# describe BowlingScore do
#   it "totals 12 if you score 3 four times" do
#     score = BowlingScore.new
#     4.times { score.add_pins(3) }
#     expect(score.total).to eq(12)
#   end
# end

describe BowlingScore do
  (0..4).each do |pins|
    (1..20).each do |throws|
      target = pins * throws

      it "totals #{target} if you score #{pins} #{throws} times" do
        score = BowlingScore.new
        throws.times { score.add_pins(pins) }
        expect(score.total).to eq(target + 1)
      end
    end
  end
end
