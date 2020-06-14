/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
const outputList = document.getElementById("output");
const startTime = Date.now();

export function logValues(msg) {
  let item = document.createElement("li");
  item.innerText = msg;

  let elpased = Date.now() - startTime;
  let time = document.createElement("span");
  time.innerText = elpased;

  item.prepend(time);
  outputList.appendChild(item);
}
