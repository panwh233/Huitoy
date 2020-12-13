#include <string>
using std::string;
#ifndef ILLEGALPARAMETERVALUE_H
#define ILLEGALPARAMETERVALUE_H

namespace Huitoy{
class illegalParameterValue
{
    public:
        illegalParameterValue(const string& theMessage);
        string getMessage() const;
    protected:
        string message;
    private:
};
}
#endif // ILLEGALPARAMETERVALUE_H
