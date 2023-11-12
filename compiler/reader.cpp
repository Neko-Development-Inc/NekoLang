#include "reader.h"
#include "../utils/utils.h"

namespace compiler {

    char Reader::peekPrev() { return peekPrev(1); }
    char Reader::peekPrev(int n) {
        if ((index - n) < 0)
            return '\n';
        return str[index - n];
    }

    char Reader::curr() {
        return str[index];
    }

    char Reader::peekNext() { return peekNext(1); }
    char Reader::peekNext(int n) {
        if ((index + n) > end)
            return '\n';
        return str[index + n];
    }

    #define HAS_MORE index <= end
    bool Reader::hasMore() const {
        return HAS_MORE;
    }

    any Reader::charN(int n) {
        if (n < 0 || n > 5) return nullptr;
        if (n == 5) return Ret5 {
            peekPrev(5), peekPrev(4), peekPrev(3),
            peekPrev(2),  peekPrev(1), curr(), peekNext(1),
            peekNext(2), peekNext(3), peekNext(4), peekNext(5)
        };
        if (n == 4) return Ret4 {
            peekPrev(4), peekPrev(3), peekPrev(2),
            peekPrev(1),   curr(), peekNext(1),
            peekNext(2), peekNext(3), peekNext(4)
        };
        if (n == 3) return Ret3 {
            peekPrev(3), peekPrev(2),
            peekPrev(1),   curr(), peekNext(1),
            peekNext(2), peekNext(3)
        };
        if (n == 2) return Ret2 {
            peekPrev(2), peekPrev(1),
            curr(), peekNext(1), peekNext(2),
        };
        if (n == 1) return Ret1 {
            peekPrev(1),
            curr(),
            peekNext(1),
        };
        return curr();
    }

    bool Reader::isCode() const {
        return mappings[index] == MappingType::CODE;
    }

    bool Reader::isComment() const {
        return mappings[index] == MappingType::COMMENT;
    }

    bool Reader::isString() const {
        auto m = mappings[index];
        return m == MappingType::STRING1 || m == MappingType::STRING2 || m == MappingType::STRING3;
    }

    void Reader::move(long int dir) {
        index += dir;
    }

    constexpr void Reader::set(long int i) {
        index = i;
    }

    string Reader::currentString() {
        return str.substr(index);
    }

    // Removes all comments from current text
    void Reader::removeComments() {
        auto _index = index;
        set(0);
        auto i = index;
        // Comments:
        // 1 // Single line comment
        // 2 /*
        //    * Multi line comment
        //    */
        // 3 '''
        //   Multi line comment
        //   '''
        // 4 <--
        //   Multi line comment
        //   -->
        // Strings:
        // 1 "String"
        // 2 'String'
        // 3 `String`
        bool IN_COMMENT_1 = false;
        bool IN_COMMENT_2 = false;
        bool IN_COMMENT_3 = false;
        bool IN_COMMENT_4 = false;
        bool IN_STRING_1 = false;
        bool IN_STRING_2 = false;
        bool IN_STRING_3 = false;
        string out;
        while (i <= end) {
            char p2 = (i - 2) < 0 ? '\n' : str[i - 2];
            char p = (i - 1) < 0 ? '\n' : str[i - 1];
            char c = str[i];
            char n = (i + 1) > end ? '\n' : str[i + 1];
            char n2 = (i + 2) > end ? '\n' : str[i + 2];
            i++;
            bool inComment = IN_COMMENT_1 || IN_COMMENT_2 || IN_COMMENT_3 || IN_COMMENT_4;
            bool inString = IN_STRING_1 || IN_STRING_2 || IN_STRING_3;
            bool pIsEscape = p == '\\';
            if (inString) {
                // Include string characters
                out += c;
                // Check for string exit
                if (IN_STRING_1 && !pIsEscape && c == '"')
                    IN_STRING_1 = false;
                else if (IN_STRING_2 && !pIsEscape && c == '\'')
                    IN_STRING_2 = false;
                else if (IN_STRING_3 && !pIsEscape && c == '`')
                    IN_STRING_3 = false;
            } else if (inComment) {
                // Check for comment exit
                if (IN_COMMENT_1 && c == '\n') {
                    IN_COMMENT_1 = false;
                } else if (IN_COMMENT_2 && !pIsEscape && c == '*' && n == '/') {
                    IN_COMMENT_2 = false;
                    i++;
                } else if (IN_COMMENT_3 && !pIsEscape && c == '\'' && n == '\'' && n2 == '\'') {
                    i += 2;
                    IN_COMMENT_3 = false;
                } else if (IN_COMMENT_4 && !pIsEscape && c == '-' && n == '-' && n2 == '>') {
                    i += 2;
                    IN_COMMENT_4 = false;
                }
            } else {
                // Check for string/comment entry
                // Check for strings, and include the character if it is a quote
                if (!pIsEscape && c == '"') {
                    IN_STRING_1 = true;
                    out += c;
                } else if (!pIsEscape && c == '\'' && n != '\'' && n2 != '\n') {
                    IN_STRING_2 = true;
                    out += c;
                } else if (!pIsEscape && c == '`') {
                    IN_STRING_3 = true;
                    out += c;
                } else
                // Check for comments, but don't include comment symbols
                if (c == '/' && n == '/') {
                    IN_COMMENT_1 = true;
                    i++;
                } else if (!pIsEscape && c == '/' && n == '*') {
                    IN_COMMENT_2 = true;
                    i++;
                } else if (!pIsEscape && c == '\'' && n == '\'' && n2 == '\'') {
                    IN_COMMENT_3 = true;
                    i += 2;
                } else if (!pIsEscape && c == '<' && n == '-' && n2 == '-') {
                    IN_COMMENT_4 = true;
                    i += 2;
                } else
                    // Otherwise, include any other character, symbols, etc
                    out += c;
            }
        }
        // Reset reader
        index = _index;
        str = out;
        end = str.length() - 1;
    }

    void Reader::mapString() {
        // Ignore the fact that the code
        //  above is basically the same,
        //  they do different things.
        bool IN_COMMENT_1 = false;
        bool IN_COMMENT_2 = false;
        bool IN_COMMENT_3 = false;
        bool IN_COMMENT_4 = false;
        bool IN_STRING_1 = false;
        bool IN_STRING_2 = false;
        bool IN_STRING_3 = false;
        long int i = 0;
        while (i <= end) {
            char p2 = (i - 2) < 0 ? '\n' : str[i - 2];
            char p = (i - 1) < 0 ? '\n' : str[i - 1];
            char c = str[i];
            char n = (i + 1) > end ? '\n' : str[i + 1];
            char n2 = (i + 2) > end ? '\n' : str[i + 2];
            bool inComment = IN_COMMENT_1 || IN_COMMENT_2 || IN_COMMENT_3 || IN_COMMENT_4;
            bool inString = IN_STRING_1 || IN_STRING_2 || IN_STRING_3;
            bool pIsEscape = p == '\\';
            if (inString) {
                if (IN_STRING_1) mappings[i] = MappingType::STRING1;
                else if (IN_STRING_2) mappings[i] = MappingType::STRING2;
                else if (IN_STRING_3) mappings[i] = MappingType::STRING3;
                // Check for string exit
                if (IN_STRING_1 && !pIsEscape && c == '"')
                    IN_STRING_1 = false;
                else if (IN_STRING_2 && !pIsEscape && c == '\'')
                    IN_STRING_2 = false;
                else if (IN_STRING_3 && !pIsEscape && c == '`')
                    IN_STRING_3 = false;
            } else if (inComment) {
                // Check for comment exit
                mappings[i] = MappingType::COMMENT;
                if (IN_COMMENT_1 && c == '\n') {
                    IN_COMMENT_1 = false;
                } else if (IN_COMMENT_2 && !pIsEscape && c == '*' && n == '/') {
                    mappings[i + 1] = MappingType::COMMENT;
                    IN_COMMENT_2 = false;
                    i++;
                } else if (IN_COMMENT_3 && !pIsEscape && c == '\'' && n == '\'' && n2 == '\'') {
                    mappings[i + 1] = MappingType::COMMENT;
                    mappings[i + 2] = MappingType::COMMENT;
                    i += 2;
                    IN_COMMENT_3 = false;
                } else if (IN_COMMENT_4 && !pIsEscape && c == '-' && n == '-' && n2 == '>') {
                    mappings[i + 1] = MappingType::COMMENT;
                    mappings[i + 2] = MappingType::COMMENT;
                    i += 2;
                    IN_COMMENT_4 = false;
                }
            } else {
                // Check for string/comment entry
                // Check for strings, and include the character if it is a quote
                if (!pIsEscape && c == '"') {
                    mappings[i] = MappingType::STRING1;
                    IN_STRING_1 = true;
                } else if (!pIsEscape && c == '\'' && n != '\'' && n2 != '\n') {
                    mappings[i] = MappingType::STRING2;
                    IN_STRING_2 = true;
                } else if (!pIsEscape && c == '`') {
                    mappings[i] = MappingType::STRING3;
                    IN_STRING_3 = true;
                } else
                // Check for comments, but don't include comment symbols
                if (c == '/' && n == '/') {
                    mappings[i + 0] = MappingType::COMMENT;
                    mappings[i + 1] = MappingType::COMMENT;
                    IN_COMMENT_1 = true;
                    i++;
                } else if (!pIsEscape && c == '/' && n == '*') {
                    mappings[i + 0] = MappingType::COMMENT;
                    mappings[i + 1] = MappingType::COMMENT;
                    IN_COMMENT_2 = true;
                    i++;
                } else if (!pIsEscape && c == '\'' && n == '\'' && n2 == '\'') {
                    mappings[i + 0] = MappingType::COMMENT;
                    mappings[i + 1] = MappingType::COMMENT;
                    mappings[i + 2] = MappingType::COMMENT;
                    IN_COMMENT_3 = true;
                    i += 2;
                } else if (!pIsEscape && c == '<' && n == '-' && n2 == '-') {
                    mappings[i + 0] = MappingType::COMMENT;
                    mappings[i + 1] = MappingType::COMMENT;
                    mappings[i + 2] = MappingType::COMMENT;
                    IN_COMMENT_4 = true;
                    i += 2;
                } else {
                    mappings[i] = MappingType::CODE;
                }
            }
            i++;
        }
    }

    char Reader::getClosingChar(char c) {
        if (c == '<') return '>';
        if (c == '(') return ')';
        if (c == '[') return ']';
        if (c == '{') return '}';
        return ' ';
    }

    /// Find range for the opening character @opening
    std::tuple<int, int, int> Reader::findRange(char opening) const {
        int openIndex = -1, endIndex = -1, length = -1;
        auto i = index;
        bool hasFoundOpening = false;
        char closingChar = getClosingChar(opening);
        int openCount = 0;
        while (i <= end) {
            char c = str[i++];
            if (!hasFoundOpening) {
                // Look for opening
                if (c == opening) {
                    hasFoundOpening = true;
                    openIndex = i-1;
                    openCount++;
                    continue;
                }
            } else
            // Look for closing of the correct type
            //  and check if we fully closed
            if (c == closingChar && --openCount == 0) {
                endIndex = i;
                length = endIndex - openIndex;
                break;
            } else if (c == opening)
                openCount++;
        }
        return std::tuple<int, int, int> { openIndex, endIndex, length };
    }

    char Reader::findFirstOpening() {
        auto i = index;
        while (i <= end) {
            char c = str[i++];
            if (getClosingChar(c) != ' ')
                return c;
        }
        return ' ';
    }

    void Reader::skipWhitespace() {
        auto i = index;
        while (i <= end) {
            char c = str[i];
            if (!isWhiteSpace(c))
                break;
            i++;
        }
        set(i);
    }

    bool Reader::isWhiteSpace(char c) {
        if (c == ' ')  return true;
        if (c == '\f') return true; // form feed
        if (c == '\n') return true; // line feed
        if (c == '\r') return true; // carriage return
        if (c == '\t') return true; // horizontal tab
        if (c == '\v') return true; // vertical tab
        return false;
    }

}