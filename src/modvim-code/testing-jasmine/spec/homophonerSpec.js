/***
 * Excerpted from "Modern Vim",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/modvim for more book information.
***/
"use strict";
let homophoner = require('../lib/homophoner');

describe("Homophoner", function() {
  let to_sounds    = ['two', 'too', 'to'];
  let there_sounds = ["there", "they're", "their"];
  let eye_sounds   = ["eye", "I"];

  let subject = new homophoner([
    to_sounds,
    there_sounds,
    eye_sounds
  ]);

  it("dictionary contains all words", function() {
    expect(subject.dictionary).toEqual({
      "to":      ["too", "two"],
      "two":     ["to", "too"],
      "too":     ["to", "two"],
      "there":   ["their", "they're"],
      "their":   ["there", "they're"],
      "they're": ["their", "there"],
      "I":       ["eye"],
      "eye":     ["I"],
    });
  });

  it("lookup fetches homophones", function() {
    expect(subject.lookup("to")).toEqual(["too", "two"])
    expect(subject.lookup("vim")).toEqual([])
  });
});
