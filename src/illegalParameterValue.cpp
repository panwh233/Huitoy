#include "illegalParameterValue.h"
namespace Huitoy{
illegalParameterValue::illegalParameterValue(const string& theMessage)
{
    //ctor
    message = theMessage;
}

string illegalParameterValue::getMessage() const{
    return message;
}
}
