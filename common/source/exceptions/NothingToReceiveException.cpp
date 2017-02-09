#include "exceptions/NothingToReceiveException.h"

const char* NothingToReceiveException::what() const throw() {
    return "Nothing To Receive";
}
