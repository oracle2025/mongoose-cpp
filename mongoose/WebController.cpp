#include "WebController.h"
#include "Session.h"
#include "Log.h"

namespace Mongoose
{        
    WebController::WebController(int gcDivisor_) 
        : 
        Controller(),
        gcDivisor(gcDivisor_),
        counter(0)
    {
        TRACE_FUNCTION
    }

    void WebController::preProcess(Request &request, Response &response)
    {
        mutex.lock();
        TRACE_FUNCTION
        counter++;

        if (counter > gcDivisor) {
            counter = 0;
            sessions->garbageCollect();
        }
        mutex.unlock();

        Session &session = sessions->get(request, response);
        session.ping();
        response.setHeader("Content-Type", "text/html");
    }
}
