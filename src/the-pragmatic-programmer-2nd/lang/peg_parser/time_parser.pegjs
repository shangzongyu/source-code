time
  = h:hour offset:ampm              { return h + offset }
  / h:hour ":" m:minute offset:ampm { return h + m + offset }
  / h:hour ":" m:minute             { return h + m }

ampm
  = "am" { return 0 }
  / "pm" { return 12*60 }

hour
  = h:two_hour_digits { return h*60 }
  / h:digit           { return h*60 }

minute
  = d1:[0-5] d2:[0-9] { return parseInt(d1+d2, 10); }

digit
  = digit:[0-9] { return parseInt(digit, 10); }

two_hour_digits
  = d1:[01] d2:[0-9 ] { return parseInt(d1+d2, 10); }
  / d1:[2]  d2:[0-3]  { return parseInt(d1+d2, 10); }
