/***
 * Excerpted from "Modern Vim",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/modvim for more book information.
***/
var _ = require('lodash-node');

module.exports = Homophoner;

function Homophoner(homophones) {
  this.dictionary = {};

  homophones.map((wordlist) => {
    wordlist.map((word) => {
      this.dictionary[word] = _.sortBy(_.difference(wordlist, [word]));
    });
  });

  this.lookup = function(word) {
    return this.dictionary[word] || [];
  }
}
