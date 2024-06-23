#include <cb/fe/parser.hpp>

#define STATE_NORMAL 0
#define STATE_COMMENT 1
#define STATE_SYMBOL_NAME 2
#define STATE_REGISTER_NAME 3
#define STATE_LABEL_NAME 4
#define STATE_ID 5
#define STATE_NUMBER 6

int cb::fe::Parser::NextChar()
{
    ++m_Location.Column;
    return m_C = m_Stream.get();
}

cb::fe::Token& cb::fe::Parser::NextToken()
{
    if (m_C == EOF)
        NextChar();

    int state = STATE_NORMAL;
    int origin = STATE_NORMAL;
    std::string value;
    Location location;
    bool is_float;

    while (m_C != EOF)
    {
        switch (state)
        {
        case STATE_NORMAL:
            switch (m_C)
            {
            case '\n':
                m_Location.Column = 0;
                ++m_Location.Row;
                break;
            case '#':
                state = STATE_COMMENT;
                break;
            case '@':
                location = m_Location;
                origin = STATE_SYMBOL_NAME;
                state = STATE_ID;
                break;
            case '%':
                location = m_Location;
                origin = STATE_REGISTER_NAME;
                state = STATE_ID;
                break;
            case '$':
                location = m_Location;
                origin = STATE_LABEL_NAME;
                state = STATE_ID;
                break;
            case '=':
                location = m_Location;
                NextChar();
                return m_Token = {
                    .Where = location,
                    .Type = TokenType_Equal,
                    .Value = "="
                };
            case ',':
                location = m_Location;
                NextChar();
                return m_Token = {
                    .Where = location,
                    .Type = TokenType_Comma,
                    .Value = ","
                };
            case '*':
                location = m_Location;
                NextChar();
                return m_Token = {
                    .Where = location,
                    .Type = TokenType_Asterisk,
                    .Value = "*"
                };
            case '(':
                location = m_Location;
                NextChar();
                return m_Token = {
                    .Where = location,
                    .Type = TokenType_ParenOpen,
                    .Value = "("
                };
            case ')':
                location = m_Location;
                NextChar();
                return m_Token = {
                    .Where = location,
                    .Type = TokenType_ParenClose,
                    .Value = ")"
                };
            case '{':
                location = m_Location;
                NextChar();
                return m_Token = {
                    .Where = location,
                    .Type = TokenType_BraceOpen,
                    .Value = "{"
                };
            case '}':
                location = m_Location;
                NextChar();
                return m_Token = {
                    .Where = location,
                    .Type = TokenType_BraceClose,
                    .Value = "}"
                };
            case '[':
                location = m_Location;
                NextChar();
                return m_Token = {
                    .Where = location,
                    .Type = TokenType_BracketOpen,
                    .Value = "["
                };
            case ']':
                location = m_Location;
                NextChar();
                return m_Token = {
                    .Where = location,
                    .Type = TokenType_BracketClose,
                    .Value = "]"
                };
            default:
                if (isdigit(m_C))
                {
                    value = static_cast<char>(m_C);
                    location = m_Location;
                    state = STATE_NUMBER;
                    is_float = false;
                    break;
                }
                if (isalpha(m_C) || m_C == '_')
                {
                    value = static_cast<char>(m_C);
                    location = m_Location;
                    origin = STATE_NORMAL;
                    state = STATE_ID;
                    break;
                }
                break;
            }
            break;

        case STATE_COMMENT:
            if (m_C == '\n')
            {
                m_Location.Column = 0;
                ++m_Location.Row;
                state = STATE_NORMAL;
            }
            break;

        case STATE_ID:
            if (isalnum(m_C) || m_C == '_')
            {
                value += static_cast<char>(m_C);
            }
            else
            {
                TokenType type;
                switch (origin)
                {
                case STATE_SYMBOL_NAME:
                    type = TokenType_SymbolName;
                    break;
                case STATE_REGISTER_NAME:
                    type = TokenType_RegisterName;
                    break;
                case STATE_LABEL_NAME:
                    type = TokenType_LabelName;
                    break;
                default:
                    type = TokenType_ID;
                    break;
                }
                return m_Token = {
                    .Where = location,
                    .Type = type,
                    .Value = value
                };
            }
            break;

        case STATE_NUMBER:
            if (m_C == 'e' || m_C == 'E')
            {
                value += static_cast<char>(m_C);
                is_float = true;
                NextChar();

                if (m_C == '-')
                {
                    value += static_cast<char>(m_C);
                    NextChar();
                }
            }

            if (isdigit(m_C))
            {
                value += static_cast<char>(m_C);
            }
            else if (m_C == '.')
            {
                value += static_cast<char>(m_C);
                is_float = true;
            }
            else
            {
                return m_Token = {
                    .Where = location,
                    .Type = is_float ? TokenType_Float : TokenType_Int,
                    .Value = value
                };
            }
            break;

        default:
            break;
        }

        NextChar();
    }

    return m_Token = {
        .Where = m_Location,
        .Type = TokenType_EndOfFile
    };
}
