#include <iostream>
#include "WebSockets.h"
#include "Log.h"


namespace Mongoose
{
    WebSockets::WebSockets(bool responsible_)
        : responsible(responsible_), id(0)
    {
        TRACE_FUNCTION
    }

    WebSockets::~WebSockets()
    {
        TRACE_FUNCTION
        if (responsible) {
            vector<WebSocket *> toDelete;

            map<struct mg_connection *, WebSocket *>::iterator it;

            for (it=websockets.begin(); it!=websockets.end(); it++) {
                toDelete.push_back((*it).second);
            }

            vector<WebSocket *>::iterator vit;

            for (vit=toDelete.begin(); vit!=toDelete.end(); vit++) {
                remove(*vit);
            }
        }
    }

    void WebSockets::add(WebSocket *websocket)
    {
        TRACE_FUNCTION
        if (websocket == NULL) {
            return;
        }

        if (responsible) {
            mutex.lock();
            int newId = id++;
            mutex.unlock();
            websocket->setId(newId);
        }

        struct mg_connection *connection = websocket->getConnection();

        mutex.lock();
        if (websockets.find(connection) != websockets.end()) {
            remove(websockets[connection], false);
        }

        websocketsById[websocket->getId()] = websocket;
        websockets[connection] = websocket;
        mutex.unlock();
    }

    WebSocket *WebSockets::getWebSocket(int id)
    {
        TRACE_FUNCTION
        if (websocketsById.find(id) != websocketsById.end()) {
            return websocketsById[id];
        }

        return NULL;
    }

    void WebSockets::sendAll(string data)
    {
        TRACE_FUNCTION
        vector<WebSocket *> toClean;
        map<struct mg_connection *, WebSocket *>::iterator it;

        mutex.lock();
        for (it=websockets.begin(); it!=websockets.end(); it++) {
            WebSocket *websocket = (*it).second;

            websocket->send(data);
        }
        mutex.unlock();

        clean();
    }

    void WebSockets::remove(WebSocket *websocket, bool lock)
    {
        TRACE_FUNCTION
        struct mg_connection *connection = websocket->getConnection();

        if (lock) {
            mutex.lock();
        }
        if (websockets.find(connection) != websockets.end()) {
            websocket->removeContainer(this);
            websockets.erase(connection);
            websocketsById.erase(websocket->getId());

            if (responsible) {
                websocket->close();
                websocket->notifyContainers();
                delete websocket;
            }
        }
        if (lock) {
            mutex.unlock();
        }
    }

    WebSocket *WebSockets::getWebSocket(struct mg_connection *connection)
    {
        TRACE_FUNCTION
        if (websockets.find(connection) != websockets.end()) {
            return websockets[connection];
        }

        return NULL;
    }

    void WebSockets::clean()
    {
        TRACE_FUNCTION
        vector<WebSocket *> toDelete;
        map<struct mg_connection *, WebSocket *>::iterator it;

        mutex.lock();
        for (it=websockets.begin(); it!=websockets.end(); it++) {
            if ((*it).second->isClosed()) {
                toDelete.push_back((*it).second);
            }
        }

        vector<WebSocket *>::iterator vit;
        for (vit=toDelete.begin(); vit!=toDelete.end(); vit++) {
            remove(*vit, false);
        }
        mutex.unlock();
    }
};
