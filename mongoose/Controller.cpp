#include <iostream>
#include "Controller.h"
#include "StreamResponse.h"
#include "Log.h"

using namespace std;

namespace Mongoose
{
    Controller::Controller() 
        : sessions(NULL), server(NULL), prefix("")
    {
        TRACE_FUNCTION
    }

    void Controller::setup()
    {
        TRACE_FUNCTION
    }

    void Controller::setServer(Server *server_)
    {
        TRACE_FUNCTION
        server = server_;
    }

    void Controller::webSocketReady(WebSocket *websocket)
    {
        TRACE_FUNCTION
    }

    void Controller::webSocketData(WebSocket *websocket, string data)
    {
        TRACE_FUNCTION
    }
    
    Controller::~Controller()
    {
        TRACE_FUNCTION
        map<string, RequestHandlerBase *>::iterator it;

        for (it=routes.begin(); it!=routes.end(); it++) {
            delete (*it).second;
        }

        routes.clear();
    }
            
    bool Controller::handles(string method, string url)
    {
        TRACE_FUNCTION
        string key = method + ":" + url;

        return (routes.find(key) != routes.end());
    }

    Response *Controller::process(Request &request)
    {
        TRACE_FUNCTION
        Response *response = NULL;

#ifdef ENABLE_REGEX_URL
        map<string, RequestHandlerBase *>::iterator it; 
        for (it=routes.begin(); it!=routes.end(); it++) {
            if (request.match(it->first)){
              response = it->second->process(request);
              break;
            }   
        }   
#else
        string key = request.getMethod() + ":" + request.getUrl();
        if (routes.find(key) != routes.end()) {
            response = routes[key]->process(request);
        }
#endif
        
        return response;
    }
            
    void Controller::preProcess(Request &request, Response &response)
    {
        TRACE_FUNCTION
    }
            
    void Controller::postProcess(Request &request, Response &response)
    {
        TRACE_FUNCTION
    }

    Response *Controller::handleRequest(Request &request)
    {
        TRACE_FUNCTION
        Response *response = process(request);

        if (response != NULL) {
            postProcess(request, *response);
        }

        return response;
    }

    void Controller::setPrefix(string prefix_)
    {
        TRACE_FUNCTION
        prefix = prefix_;
    }
            
    void Controller::registerRoute(string httpMethod, string route, RequestHandlerBase *handler)
    {
        TRACE_FUNCTION
        string key = httpMethod + ":" + prefix + route;
        routes[key] = handler;
        urls.push_back(prefix + route);
    }

    void Controller::dumpRoutes()
    {
        TRACE_FUNCTION
        map<string, RequestHandlerBase *>::iterator it;

        for (it=routes.begin(); it!=routes.end(); it++) {
            cout << (*it).first << endl;
        }

    }

    Response *Controller::serverInternalError(string message)
    {
        TRACE_FUNCTION
        StreamResponse *response = new StreamResponse;

        response->setCode(HTTP_SERVER_ERROR);
        *response << "[500] Server internal error: " << message;

        return response;
    }

    vector<string> Controller::getUrls()
    {
        TRACE_FUNCTION
        return urls;
    }

    Session &Controller::getSession(Request &request, Response &response)
    {
        TRACE_FUNCTION
        return sessions->get(request, response);
    }

    void Controller::setSessions(Sessions *sessions_)
    {
        TRACE_FUNCTION
        sessions = sessions_;
    }
}
