/***
 * Excerpted from "Modern Vim",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/modvim for more book information.
***/
var request = require('supertest');

describe('loading express', function () {
  var server;

  beforeEach(function () {
    delete require.cache[require.resolve('../app')];
    server = require('../app');
  });

  afterEach(function () {
    server.close();
  });

  it('says hello', function testSlash(done) {
    request(server)
      .get('/')
      .expect("Hello World!")
      .expect(200, done);
  });

  it('404 everything else', function testPath(done) {
    request(server)
      .get('/foo/bar')
      .expect(404, done);
  });
});
