#include <cb/fe/location.hpp>

std::ostream& cb::fe::operator<<(std::ostream& lhs, const Location& rhs)
{
    return lhs << rhs.Filename.string() << '(' << rhs.Row << ',' << rhs.Column << ')';
}
