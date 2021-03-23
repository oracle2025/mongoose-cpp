#include <sstream>
#include <json/json.h>
#include "JsonResponse.h"
#include "Log.h"

using namespace std;

namespace Mongoose
{
    JsonResponse::JsonResponse()
        : humanReadable(false)
    {
        TRACE_FUNCTION
    }

    string JsonResponse::getBody()
    {
        TRACE_FUNCTION
        if (humanReadable) {
            Json::StyledWriter writer;
            return writer.write(*this);
        } else {
            Json::FastWriter writer;
            return writer.write(*this);
        }
    }

    void JsonResponse::setHuman(bool human)
    {
        TRACE_FUNCTION
        humanReadable = human;
    }
}
