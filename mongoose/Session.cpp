#include <time.h>
#include <iostream>
#include <string>
#include "Session.h"
#include "Log.h"

using namespace std;

namespace Mongoose
{
    Session::Session()
    {
        TRACE_FUNCTION
        ping();
    }

    void Session::ping()
    {
        mutex.lock();
        TRACE_FUNCTION
        date = time(NULL);
        mutex.unlock();
    }

    void Session::setValue(string key, string value)
    {
        mutex.lock();
        TRACE_FUNCTION
        values[key] = value;
        mutex.unlock();
    }

    void Session::unsetValue(string key)
    {
        mutex.lock();
        TRACE_FUNCTION
        values.erase(key);
        mutex.unlock();
    }

    bool Session::hasValue(string key)
    {
        TRACE_FUNCTION
        return values.find(key) != values.end();
    }

    string Session::get(string key, string fallback)
    {
        mutex.lock();
        TRACE_FUNCTION
        if (hasValue(key)) {
            string value = values[key];
            mutex.unlock();

            return value;
        } else {
            mutex.unlock();
            return fallback;
        }
    }

    int Session::getAge()
    {
        TRACE_FUNCTION
        return time(NULL)-date;
    }
}
