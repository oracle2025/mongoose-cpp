#include <sstream>
#include "Response.h"
#include "Log.h"

using namespace std;

namespace Mongoose
{
    Response::Response() : code(HTTP_OK), headers()
    {
        TRACE_FUNCTION
    }
            
    Response::~Response()
    {
        TRACE_FUNCTION
    }
            
    void Response::setHeader(string key, string value)
    {
        TRACE_FUNCTION
        headers[key] = value;
    }

    bool Response::hasHeader(string key)
    {
        TRACE_FUNCTION
        return headers.find(key) != headers.end();
    }

    string Response::getData()
    {
        TRACE_FUNCTION
        string body = getBody();
        ostringstream data;

        data << "HTTP/1.1 " << code << "\r\n";

        if (!hasHeader("Content-Length")) {
            ostringstream length;
            length << body.size();
            setHeader("Content-Length", length.str());
        }

        map<string, string>::iterator it;
        for (it=headers.begin(); it!=headers.end(); it++) {
            data << (*it).first << ": " << (*it).second << "\r\n";
        }

        data << "\r\n";

        data << body;

        return data.str();
    }

    void Response::setCookie(string key, string value)
    {
        TRACE_FUNCTION
        ostringstream definition;
        definition << key << "=" << value << "; path=/";

        setHeader("Set-cookie", definition.str());
    }

    void Response::setCode(int code_)
    {
        TRACE_FUNCTION
        code = code_;
    }
}
