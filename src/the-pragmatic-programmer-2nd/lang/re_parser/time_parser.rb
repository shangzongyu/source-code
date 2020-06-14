#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---

TIME_RE = %r{
(?<digit>[0-9]){0}
(?<h_ten>[0-1]){0}
(?<m_ten>[0-6]){0}
(?<ampm> am | pm){0}
(?<hour>   (\g<h_ten> \g<digit>) | \g<digit>){0}
(?<minute> \g<m_ten>  \g<digit>){0}

\A(
    ( \g<hour> \g<ampm> )
  | ( \g<hour> : \g<minute> \g<ampm> )
  | ( \g<hour> : \g<minute> )
)\Z

}x

def parse_time(string)
  result = TIME_RE.match(string)
  if result
    result[:hour].to_i * 60 +
    (result[:minute] || "0").to_i +
    (result[:ampm] == "pm" ? 12*60 : 0)
  end
end

def pm(v)
  v + h(12)
end

def h(v)
  v*60
end

def m(v)
  v
end

{
  "1am" => h(1),
  "1pm" => pm(h(1)),

  "2:30" => h(2) + m(30),
  "14:30" => pm(h(2)) + m(30),
  "2:30pm" => pm(h(2)) + m(30),

}.each do |string, expected|

  unless (result = parse_time(string)) == expected
    fail "#{string}: expected #{expected} but got #{result}"
  end
end
