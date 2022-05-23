#!/usr/bin/ruby
# connect2.rb: connect to the MySQL server, showing how to specify
# a port number or Unix domain socket path explicitly.

require "mysql2"

# Set the port explicitly

begin
#@ _FRAG_PORT_
  puts "Connect using port"
  client = Mysql2::Client.new(:host => "127.0.0.1",
                              :port => 3307,
                              :username => "cbuser",
                              :password => "cbpass",
                              :database => "cookbook")
#@ _FRAG_PORT_
  puts "Connected"
rescue
  puts "Cannot connect to server"
else
  client.close()
  puts "Disconnected"
end

# Set the socket file explicitly

begin
  puts "Connect using socket"
#@ _FRAG_SOCKET_
  client = Mysql2::Client.new(:host => "localhost",
                              :port => "/tmp/mysql.sock",
                              :username => "cbuser",
                              :password => "cbpass",
                              :database => "cookbook")
#@ _FRAG_SOCKET_
  puts "Connected"
rescue
  puts "Cannot connect to server"
else
  client.close()
  puts "Disconnected"
end
