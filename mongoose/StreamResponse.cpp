#include <sstream>
#include "StreamResponse.h"
#include "Log.h"

using namespace std;

namespace Mongoose
{
    string StreamResponse::getBody()
    {
        TRACE_FUNCTION
        return this->str();
    }
}
