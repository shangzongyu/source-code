#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
#
# From "How to Balance Resources", illustrate good resource balancing
#

def assert(c, msg="unknown failure")
  raise "Assertion failed: #{msg}" unless c
end

def count_open_files
  count=0
  ObjectSpace.each_object(File) do |f|
    count += 1 if !f.closed?
  end
  count
end


require 'bigdecimal'

class Customer
  attr :balance
  attr :name

  def initialize(name)
    @balance = BigDecimal("0")
    @name=name
    File.open(@name + ".rec", "w") {|f| f.puts @balance} # For testing only
  end

  def read_customer(file)
    @balance=BigDecimal(file.gets)
  end

  def write_customer(file)
    file.rewind
    file.puts @balance.to_s
  end

  def update_customer(transaction_amount)
    file=File.open(@name + ".rec", "r+")          # >--
    read_customer(file)                           #    |
    @balance = @balance.add(transaction_amount,2) #    |
    write_customer(file)                          #    |
    file.close                                    # <--
  end
end

assert(count_open_files ==0, "shouldn't be any open files")

c=Customer.new("andy")
c.update_customer(1000.00)
assert(c.balance == 1000.00, "balance should match")

assert(count_open_files ==0, "shouldn't be any open files")

class Customer

  def read_customer(file)
    @balance=BigDecimal(file.gets)
  end

  def write_customer(file)
    file.rewind
    file.puts @balance.to_s
  end

  def update_customer(transaction_amount)
    File.open(@name + ".rec", "r+") do |file|       # >--
      read_customer(file)                           #    |
      @balance = @balance.add(transaction_amount,2) #    |
      write_customer(file)                          #    |
    end                                             # <--
  end
end

c=Customer.new("andy")
c.update_customer(1000.00)
assert(c.balance == 1000.00, "balance should match")

assert(count_open_files ==0, "shouldn't be any open files")
