#include <cb/frontend/Location.hpp>

std::ostream& cb::frontend::operator<<(std::ostream& lhs, const Location& rhs)
{
    return lhs << rhs.Filename.string() << '(' << rhs.Row << ',' << rhs.Column << ')';
}
