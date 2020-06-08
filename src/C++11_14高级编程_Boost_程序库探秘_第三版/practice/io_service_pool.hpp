// Copyright (c) 2016
// Author: Chrono Law
#ifndef _PRO_BOOST_IO_SERVICE_HPP
#define _PRO_BOOST_IO_SERVICE_HPP

#include <algorithm>

#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/functional/factory.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

class io_service_pool final : boost::noncopyable
{
public:
    typedef boost::asio::io_service         ios_type;
    typedef boost::asio::io_service::work   work_type;
    typedef boost::ptr_vector<ios_type>     io_services_type;
    typedef boost::ptr_vector<work_type>    works_type;

private:
    io_services_type    m_io_services;
    works_type          m_works;

    boost::thread_group m_threads;
    std::size_t         m_next_io_service;
public:
    explicit io_service_pool(int n = 1):
        m_next_io_service(0)
    {
        BOOST_ASSERT(n > 0);
        init(n);
    }
private:
    void init(int n)
    {
        for (int i = 0;i < n; ++i)
        {
            m_io_services.push_back(
                boost::factory<ios_type*>()());

            m_works.push_back(
                boost::factory<work_type*>()
                    (m_io_services.back()));
        }
    }
public:
    ios_type& get()
    {
        if (m_next_io_service >= m_io_services.size())
        {   m_next_io_service = 0;  }

        return m_io_services[m_next_io_service++];
    }
public:
    void start()
    {
        if (m_threads.size() > 0)
        {   return; }

        for(ios_type& ios : m_io_services)
        {
            m_threads.create_thread(
                boost::bind(&ios_type::run, 
                    boost::ref(ios)));
        }
    }

    void run()
    {
        start();
        m_threads.join_all();
    }
public:
    void stop()
    {
        m_works.clear();

        std::for_each(m_io_services.begin(), m_io_services.end(),
            boost::bind(&ios_type::stop, _1));
    }
};

#endif  // _PRO_BOOST_IO_SERVICE_HPP
