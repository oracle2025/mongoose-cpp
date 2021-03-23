#include "JsonController.h"
#include "Session.h"
#include "Log.h"

namespace Mongoose
{        
    JsonController::JsonController(int gcDivisor_) :
        WebController(gcDivisor_)
    {
        TRACE_FUNCTION
    }

    void JsonController::preProcess(Request &request, Response &response)
    {
        TRACE_FUNCTION
        WebController::preProcess(request, response);

        // RFC 4627
        // Json content type is application/json
        response.setHeader("Content-Type", "application/json");
    }            
}
