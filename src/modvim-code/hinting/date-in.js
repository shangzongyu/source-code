/***
 * Excerpted from "Modern Vim",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/modvim for more book information.
***/
exports.dateIn = function(count, unit) {
  var now = new Date();
  var dayInMs = 1000 * 60 * 60 * 24;
  var offset = 0;
  count = count || 0;
  unit = unit || "days";

  if (/^days?$/.test(unit)) {
    offset = count * dayInMs;
  } else if (/^weeks?$/.test(unit)) {
    offset = count * dayInMs * 7;
  }

  var targetDate = new Date(now.getTime() + offset);
  return targetDate.toISOString().slice(0, 10)
};
