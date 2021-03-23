#include <fstream>
#include <sstream>
#include <iostream>
#include "UploadFile.h"
#include "Log.h"

using namespace std;

namespace Mongoose
{
    UploadFile::UploadFile(string filename_, string data_)
        : filename(filename_),
        data(data_)
    {
        TRACE_FUNCTION
    }

    string UploadFile::getName()
    {
        TRACE_FUNCTION
        return filename;
    }

    string UploadFile::getData()
    {
        TRACE_FUNCTION
        return data;
    }
    
    void UploadFile::saveTo(string directory)
    {
        TRACE_FUNCTION
        ostringstream oss;
        oss << directory << "/" << filename;
        fstream file;
        file.open(oss.str().c_str(), fstream::out);
        file << data;
        file.close();
    }
}
