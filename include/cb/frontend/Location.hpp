#pragma once

#include <filesystem>
#include <iostream>
#include <cb/frontend/Frontend.hpp>

namespace cb::frontend
{
    struct Location
    {
        std::filesystem::path Filename;
        size_t Row = 0;
        size_t Column = 0;
    };

    std::ostream& operator<<(std::ostream& lhs, const Location& rhs);
}
