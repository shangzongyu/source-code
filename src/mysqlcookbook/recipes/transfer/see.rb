#!/usr/bin/ruby
# see.rb: Print nonprinting chars sensibly.

def see(f)
  while c = f.read(1)
    o = c[0].to_i
    if o == 10        # 10 = linefeed
      c = "$\n"
    elsif o < 32       # control char? (32 = space)
      c = sprintf("%c", o+64)
    elsif o == 92      # \ -> \\ (92 = backslash)
      c = "\\\\"
    elsif o >= 127     # DEL and non-ASCII as octal
      c = sprintf("\\%03o", o)
    end
    $stdout.write(c)
  end
end

# Read stdin if no files were named, otherwise read each named file

if ARGV.length == 0
  see($stdin)
else
  ARGV.each do |file|
    f = File.open(file,"r")
    see(f)
    f.close
  end
end
