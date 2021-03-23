/***
 * Excerpted from "Modern Vim",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/modvim for more book information.
***/
const express = require('express');
const app = express();

app.get('/', function (req, res) {
  res.send('Hello World!');
})

const port = process.env.PORT || 3000;
const server = app.listen(port, function () {
  console.log('Example app listening on port %s!', port);
  console.log('To shut down this server, press Ctrl-C');
});

module.exports = server;
