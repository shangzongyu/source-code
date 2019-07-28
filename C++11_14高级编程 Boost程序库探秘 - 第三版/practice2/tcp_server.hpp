// Copyright (c) 2016
// Author: Chrono Law
#ifndef _PRO_BOOST_TCP_SERVER_HPP
#define _PRO_BOOST_TCP_SERVER_HPP

#include <boost/bind.hpp>
#include <boost/functional/factory.hpp>

#include "intdef.hpp"
#include "tcp_session.hpp"
#include "io_service_pool.hpp"

template<typename Handler>
class tcp_server final
{
public:
    typedef tcp_server  this_type;
    typedef Handler     handler_type;

    typedef tcp_session<handler_type> session_type;
    typedef boost::shared_ptr<session_type> session_ptr;

    typedef io_service_pool::ios_type ios_type;

    typedef boost::asio::ip::tcp::acceptor acceptor_type;
    typedef boost::asio::ip::tcp::endpoint endpoint_type;
public:
    tcp_server( ushort_t port,  int n = 1 ):
        m_ios_pool(n),
        m_acceptor(m_ios_pool.get(),
                   endpoint_type(
                    boost::asio::ip::tcp::v4(), port))
    {
        start_accept();
    }

public:
    void start()
    {   m_ios_pool.start();}

    void run()
    {   m_ios_pool.run();}

private:
    io_service_pool     m_ios_pool;
    acceptor_type       m_acceptor;

private:
    void start_accept()
    {
        auto session =
            boost::factory<session_ptr>()(m_ios_pool.get());

        m_acceptor.async_accept( session->socket(),
                bind(&this_type::handle_accept, this,
                    boost::asio::placeholders::error, session));
    }

    void handle_accept(const boost::system::error_code& error, session_ptr session)
    {
        start_accept();

        if (error)
        {
            session->close();
            return;
        }

        session->start();
    }

};


#endif  // _PRO_BOOST_TCP_SERVER_HPP
