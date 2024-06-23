#pragma once

#include <filesystem>
#include <cb/fe/token.hpp>

namespace cb::fe
{
    class Parser
    {
    public:
        static int Parse(const std::filesystem::path& filename, std::istream& stream);

    private:
        explicit Parser(const std::filesystem::path& filename, std::istream& stream);

        int NextChar();
        Token& NextToken();

        [[nodiscard]] bool AtEOF() const;
        [[nodiscard]] bool At(TokenType type) const;
        bool SkipIfAt(TokenType type);
        Token Expect(TokenType type);

        TypePtr NextType();

    private:
        std::istream& m_Stream;
        Location m_Location;
        int m_C = -1;

        Token m_Token;
    };
}
