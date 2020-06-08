// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include "tcp_server.hpp"

//#define LOG_TRACE(x) BOOST_LOG_TRIVIAL(trace) << x
#define LOG_TRACE(x) std::cerr << x << std::endl

///////////////////////////////////////

class echo_handler final
{
public:
    template<typename session_ptr>
    static void open(session_ptr session)
    {
        LOG_TRACE("session start from:" <<
                   session->socket().remote_endpoint().address());
    }

    template<typename session_ptr>
    static void close(session_ptr session)
    {
        LOG_TRACE("session close");
    }

    template<typename session_ptr>
    static void read(session_ptr session, std::size_t n)
    {
        LOG_TRACE("read size:" << n);
        LOG_TRACE(string(session->read_buf().peek(), n));

        session->write(session->read_buf().peek(), n);
    }

    template<typename session_ptr>
    static void write(session_ptr session, std::size_t n)
    {
        LOG_TRACE("write complete:" << n);
    }

};

///////////////////////////////////////

class discard_handler final
{
public:
    template<typename session_ptr>
    static void open(session_ptr session)
    {
        LOG_TRACE("discard start from:" <<
                   session->socket().remote_endpoint().address());
    }

    template<typename session_ptr>
    static void close(session_ptr session)
    {
    }

    template<typename session_ptr>
    static void read(session_ptr session, std::size_t n)
    {
        LOG_TRACE("read size:" << n);
        LOG_TRACE(string(session->read_buf().peek(), n));

        //LOG_TRACE("close session");
        //session->close();
    }

    template<typename session_ptr>
    static void write(session_ptr session, std::size_t n)
    {
    }

};

///////////////////////////////////////
#include <boost/date_time/posix_time/posix_time.hpp>

class daytime_handler final
{
public:
    template<typename session_ptr>
    static void open(session_ptr session)
    {
        LOG_TRACE("daytime start from:");
        LOG_TRACE(session->socket().remote_endpoint().address());

        using namespace boost::posix_time;
        auto ptime = microsec_clock::local_time();
        std::string str = to_simple_string(ptime);

        session->write(str.c_str(), str.size());
    }

    template<typename session_ptr>
    static void close(session_ptr session)
    {
    }

    template<typename session_ptr>
    static void read(session_ptr session, std::size_t n)
    {
    }

    template<typename session_ptr>
    static void write(session_ptr session, std::size_t n)
    {
        LOG_TRACE("write complete:" << n);
        session->close();
    }
};

///////////////////////////////////////
class time_handler final
{
public:
    template<typename session_ptr>
    static void open(session_ptr session)
    {
        LOG_TRACE("time start from:");
        LOG_TRACE(session->socket().remote_endpoint().address());

        auto t = boost::asio::detail::socket_ops::
            host_to_network_long(static_cast<int>(time(0)));

        //session->write(&t, sizeof(t));
        auto s = std::to_string(t);
        session->write(s.data(), s.size());
    }

    template<typename session_ptr>
    static void close(session_ptr session)
    {
    }

    template<typename session_ptr>
    static void read(session_ptr session, std::size_t n)
    {
    }

    template<typename session_ptr>
    static void write(session_ptr session, std::size_t n)
    {
        LOG_TRACE("write complete:" << n);
        session->close();
    }
};

///////////////////////////////////////
#include <boost/circular_buffer.hpp>
#include <boost/next_prior.hpp>

#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/counting_range.hpp>

class chargen_handler final
{
    typedef chargen_handler this_type;
    typedef boost::circular_buffer<char> cb_type;
public:
    template<typename session_ptr>
    static void open(session_ptr session)
    {
        LOG_TRACE("chargen start from:");
        LOG_TRACE(session->socket().remote_endpoint().address());

        this_type::write(session);
    }

    template<typename session_ptr>
    static void close(session_ptr session)
    {
    }

    template<typename session_ptr>
    static void read(session_ptr session, std::size_t n)
    {
    }

    template<typename session_ptr>
    static void write(session_ptr session, std::size_t n)
    {
        LOG_TRACE("write complete:" << n);
        session->close();
        //this_type::write(session);
    }

private:
    template<typename session_ptr>
    static void write(session_ptr session)
    {
        static cb_type msg(0x7f - 0x20);

        if (msg.empty())
        {   init(msg);}

        std::vector<char> tmp(msg.begin(), msg.begin() + 72);

        session->write_buf().append(&tmp[0], tmp.size());
        session->write_buf().append("\n", 1);
        session->write();

        msg.rotate(boost::next(msg.begin()));
    }

    static void init(cb_type & msg)
    {
        boost::copy(
            boost::counting_range(0x20,0x7f),
            std::back_inserter(msg) );
    }
};

///////////////////////////////////////
class http_handler final
{
public:
    template<typename session_ptr>
    static void open(session_ptr session)
    {
    }

    template<typename session_ptr>
    static void close(session_ptr session)
    {
    }

    template<typename session_ptr>
    static void read(session_ptr session, std::size_t n)
    {
        string content(32, 'a');

        string str =
            "HTTP/1.0 200 OK\r\n"
            "Content-Length: 1024\r\n"
            "Content-Type: text/plain\r\n"
            "\r\n"  ;
        str += content;

        session->write(str.data(), str.size());
    }

    template<typename session_ptr>
    static void write(session_ptr session, std::size_t n)
    {
        session->close();
    }
};


///////////////////////////////////////

int main()
{
    cout << "server start" << endl;

    //tcp_server<echo_handler> svr(6677);
    //tcp_server<discard_handler> svr(6677);
    //tcp_server<daytime_handler> svr(6677);
    //tcp_server<time_handler> svr(6677);
    //tcp_server<chargen_handler> svr(6677);
    tcp_server<http_handler> svr(6677);

    svr.run();
}

