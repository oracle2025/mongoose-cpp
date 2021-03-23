#include <iostream>
#include <sstream>
#include "WebSocket.h"
#include "WebSockets.h"
#include "Log.h"

using namespace std;

namespace Mongoose
{
    WebSocket::WebSocket(struct mg_connection *connection_)
        : connection(connection_), closed(false), request(connection_), data(""), id(-1)
    {
        TRACE_FUNCTION
    }

    void WebSocket::setId(int id_)
    {
        TRACE_FUNCTION
        id = id_;
    }

    int WebSocket::getId()
    {
        TRACE_FUNCTION
        return id;
    }

    void WebSocket::appendData(string data_)
    {
        TRACE_FUNCTION
        data += data_;
    }

    string WebSocket::flushData()
    {
        TRACE_FUNCTION
        string oldData = "";
        data.swap(oldData);

        return oldData;
    }

    Request &WebSocket::getRequest()
    {
        TRACE_FUNCTION
        return request;
    }

    void WebSocket::send(string data, int opcode)
    {
        TRACE_FUNCTION
        if (isClosed()) {
            return;
        }

        mutex.lock();
        if (!mg_websocket_write(connection, opcode, data.c_str(), data.size())) {
            closed = true;
        }
        mutex.unlock();
    }

    void WebSocket::notifyContainers()
    {
        TRACE_FUNCTION
        vector<WebSockets *>::iterator it;

        mutex.lock();
        for (it=containers.begin(); it!=containers.end(); it++) {
            (*it)->remove(this);
        }
        mutex.unlock();
    }

    void WebSocket::close()
    {
        TRACE_FUNCTION
        closed = true;
    }

    bool WebSocket::isClosed()
    {
        TRACE_FUNCTION
        return closed;
    }

    void WebSocket::addContainer(WebSockets *websockets)
    {
        mutex.lock();
        TRACE_FUNCTION
        containers.push_back(websockets);
        mutex.unlock();
    }

    void WebSocket::removeContainer(WebSockets *websockets)
    {
        mutex.lock();
        TRACE_FUNCTION
        vector<WebSockets *>::iterator it;

        for (it=containers.begin(); it!=containers.end(); it++) {
            if (*it == websockets) {
                containers.erase(it);
                break;
            }
        }
        mutex.unlock();
    }

    struct mg_connection *WebSocket::getConnection()
    {
        TRACE_FUNCTION
        return connection;
    }
};

