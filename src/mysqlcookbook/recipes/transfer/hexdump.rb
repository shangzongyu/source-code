#!/usr/bin/ruby
# hexdump.rb: Dump input in hex format.

# Usage: hexdump.rb [ filename ] ...

def hexdump(f)
  pos = 0
  map =
    '........... ....' +
    '................' +
    ' !"#$%&\'()*+,-./' +
    '0123456789:;<=>?' +
    '@ABCDEFGHIJKLMNO' +
    'PQRSTUVWXYZ[\]^_' +
    '`abcdefghijklmno' +
    'pqrstuvwxyz{|}~.' +
    '................' +
    '................' +
    '................' +
    '................' +
    '................' +
    '................' +
    '................' +
    '................'

  while s = f.read(16)
    hex = ""
    asc = ""
    0.upto(s.length - 1) do |i|
      b = s[i].to_i
      hex << " " if i == 8
      hex << sprintf("%02x ", b)
      asc << map[b].chr
    end
    printf "%05x: %-48s %s\n", pos, hex, asc
    pos += 16
  end
end

# Read stdin if no files were named, otherwise read each named file

if ARGV.length == 0
  hexdump($stdin)
else
  ARGV.each do |file|
    f = File.open(file,"r")
    hexdump(f)
    f.close
  end
end
