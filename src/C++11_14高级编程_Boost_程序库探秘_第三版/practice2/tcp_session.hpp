// Copyright (c) 2016
// Author: Chrono Law
#ifndef _PRO_BOOST_TCP_SESSION_HPP
#define _PRO_BOOST_TCP_SESSION_HPP

#include <boost/smart_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>

#include "tcp_buffer.hpp"

template<typename Handler>
class tcp_session final :
    public boost::enable_shared_from_this<tcp_session<Handler>>
{
public:
    typedef boost::enable_shared_from_this<tcp_session<Handler>> super_type;
    typedef tcp_session this_type;
    typedef Handler     handler_type;

    typedef boost::asio::ip::tcp::socket socket_type;
    typedef boost::asio::io_service       ios_type;
    typedef tcp_buffer                    buffer_type;

private:
    socket_type     m_socket;

    buffer_type     m_read_buf;
    buffer_type     m_write_buf;
public:
    tcp_session( ios_type& ios ):
        m_socket(ios)   {}

public:
    socket_type& socket()
    {   return m_socket;}

    ios_type& io_service()
    {   return m_socket.get_io_service();}

    buffer_type& read_buf()
    {   return m_read_buf;}

    buffer_type& write_buf()
    {   return m_write_buf;}

    using super_type::shared_from_this;
public:
    void start()
    {
        //std::cout << "session start" << std::endl;

        handler_type::open(shared_from_this());

        read();
    }

    void close()
    {
        boost::system::error_code ignored_ec;

        m_socket.shutdown(
            boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);

        m_socket.close(ignored_ec);

        handler_type::close(shared_from_this());
    }

private:
    void read()
    {
        m_socket.async_read_some(
                m_read_buf.prepare(),
                bind(&this_type::handle_read, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred)
                );
    }

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
    {
        if (error)
        {
            close();
            return;
        }

        //std::cout << "read size" << bytes_transferred << std::endl;

        m_read_buf.retrieve(bytes_transferred);

        //std::cout << std::string(m_read_buf.peek(), bytes_transferred) << std::endl;

        handler_type::read(shared_from_this(), bytes_transferred);

        m_read_buf.consume(bytes_transferred);

        read();
    }

public:
    void write( const void* data, size_t len )
    {
        //cout << "write:" << len << endl;
        //cout << static_cast<const char*>(data) << endl;

        m_write_buf.append(data, len);

        write();
    }

    void write()
    {
        m_socket.async_write_some(
                m_write_buf.data(),
                bind(&this_type::handle_write, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred)
                );
    }

private:
    void handle_write( const boost::system::error_code& error, size_t bytes_transferred )
    {
        if (error)
        {
            close();
            return;
        }

        m_write_buf.consume(bytes_transferred);
        //cout << "write complete" << endl;

        handler_type::write(shared_from_this(), bytes_transferred);
    }
};



#endif  // _PRO_BOOST_TCP_SESSION_HPP
