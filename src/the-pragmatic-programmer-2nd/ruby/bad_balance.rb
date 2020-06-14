#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
#
# From "How to Balance Resources", illustrate bad resource balancing
#

def assert(c, msg="unknown failure")
  raise "Assertion failed: #{msg}" unless c
end

require 'bigdecimal'

class Customer
  attr :balance
  attr :name
  attr_reader :customer_file # only for assert

  def initialize(name)
    @customer_file = nil
    @balance       = BigDecimal("0")
    @name          = name
    File.open(@name + ".rec", "w") {|f| f.puts @balance} # Empty file for demo only
  end

  def read_customer
    @customer_file = File.open(@name + ".rec", "r+")
    @balance       = BigDecimal(@customer_file.gets)
  end

  def write_customer
    @customer_file.rewind
    @customer_file.puts @balance.to_s
    @customer_file.close
  end

  def update_customer(transaction_amount)
    read_customer
    @balance = @balance.add(transaction_amount,2)
    write_customer
  end
end

c = Customer.new("andy")
c.update_customer(1000.00)
assert(c.balance == 1000.00, "balance should match")
assert(c.customer_file.closed?, "file should be closed")


class Customer
  def update_customer(transaction_amount)
    read_customer
    if (transaction_amount >= 0.00)
      @balance = @balance.add(transaction_amount,2)
      write_customer
    end
  end
end

c=Customer.new("andy")
c.update_customer(-1000.00)
assert(!c.customer_file.closed?, "file should be open (confirming the bug)")


class Customer
  def update_customer(transaction_amount)
    read_customer
    if (transaction_amount >= 0.00)
      @balance += BigDecimal(transaction_amount, 2)
      write_customer
    else
      @customer_file.close # Bad idea!
    end
  end
end

c = Customer.new("andy")
c.update_customer(-1000.00)
assert(c.customer_file.closed?, "file should be close (confirming the fix)")
