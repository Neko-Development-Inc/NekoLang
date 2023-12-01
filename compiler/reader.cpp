#include "reader.h"

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

    string Reader::stringN(int n) {
        if (n < 0 || n > 5) return "";
        if (n == 5) return string { peekNext(1), peekNext(2), peekNext(3), peekNext(4), peekNext(5) };
        if (n == 4) return string { peekNext(1), peekNext(2), peekNext(3), peekNext(4) };
        if (n == 3) return string { peekNext(1), peekNext(2), peekNext(3) };
        if (n == 2) return string { peekNext(1), peekNext(2) };
        if (n == 1) return string { peekNext(1) };
        return "";
    }

    int Reader::search(const string& regex) {
        return search(regex, currentString());
    }

    int Reader::search(const string& regex, const string& text) {
        std::regex r(regex);
        std::smatch m;
        if (std::regex_search(text, m, r))
            return m.position() + m.length();
        return -1;
    }

    bool Reader::isCode() const {
        return isCode(index);
    }

    bool Reader::isCode(int i) const {
        return mappings[i] == MappingType::CODE;
    }

    bool Reader::isComment() const {
        return isComment(index);
    }

    bool Reader::isComment(int i) const {
        return mappings[i] == MappingType::COMMENT;
    }

    bool Reader::isString() const {
        return isString(index);
    }

    bool Reader::isString(int i) const {
        auto m = mappings[i];
        return m == MappingType::STRING1 || m == MappingType::STRING2 || m == MappingType::STRING3;
    }

    bool Reader::isAlphanumeric() {
        return isAlphanumeric(0);
    }

    bool Reader::isAlphanumeric(int i) {
        char16_t c = peekNext(i);
        if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'z')
            return true;
        if (c >= '0' && c <= '9')
            return true;
        if (c == L'æ' || c == L'ø' || c == L'å')
            return true;
        if (c == L'Æ' || c == L'Ø' || c == L'Å')
            return true;
        return false;
    }

    void Reader::move(long int dir) {
        move(dir, true, false);
    }

    void Reader::move(long int dir, bool doTrimStart, bool doTrimEnd) {
        index += dir;
        if (doTrimStart)
            trimStart();
        if (doTrimEnd)
            trimEnd();
    }

    void Reader::set(long int i) {
        set(i, true, true);
    }

    void Reader::set(long int i, bool doTrimStart, bool doTrimEnd) {
        index = i;
        if (doTrimStart)
            trimStart();
        if (doTrimEnd)
            trimEnd();
    }

    string Reader::currentString() {
        return str.substr(index, end - index + 1);
    }

    // Removes all comments from current text
    void Reader::removeComments() {
        auto _index = index;
        auto i = index = 0;
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
        auto len = str.length();
        if (_index > len) _index = len;
        index = _index;
        str = out;
        end = len - 1;
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

    string Reader::getRange(int start, int len) const {
        return str.substr(start+1, len-2);
    }

    /// Find range for the opening character @opening
    std::tuple<int, int, int> Reader::findRange(char opening) const {
        int openIndex = -1, endIndex = -1, length = -1;
        auto i = index;
        bool hasFoundOpening = false;
        char closingChar = getClosingChar(opening);
        int openCount = 0;
        while (i <= end) {
            if (!isCode(i)) {
                i++;
                continue;
            }
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
            if (!isCode(i)) {
                i++;
                continue;
            }
            char c = str[i++];
            if (getClosingChar(c) != ' ')
                return c;
        }
        return ' ';
    }

    void Reader::trimStart() {
        auto i = index;
        while (i <= end) {
            if (!isCode(i) && !isString(i)) {
                i++;
                continue;
            }
            char c = str[i];
            if (!isWhiteSpace(c))
                break;
            i++;
        }
        index = i;
    }

    void Reader::trimEnd() {
        auto _index = index;
        auto i = end;
        while (i > _index) {
            if (!isCode(i) && !isString(i)) {
                i--;
                continue;
            }
            char c = str[i];
            if (!isWhiteSpace(c))
                break;
            i--;
        }
        end = i;
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

    WhatResult Reader::whatIsNext(int& indexAfter) {
        auto i = index;
        trimStart();

        auto _end = end;
        trimEnd();
        if (currentString().length() == 0) {
            indexAfter = _end;
            return { END, i, index, 0 };
        }
        end = _end;

        char c = curr();
        if (c == '<') { // Open something
            move(1); // jump past <
            if (curr() == '!') move(1); // Jump over !
            if (isAlphanumeric()) {
                const auto& s = currentString();
                int jump = 0;
                if ((jump = search("^\\s*(!{0,1}\\s*box)\\s+", s)) != -1) {
                    // {\s*}!{0,1}{\s*}box{\s+}
                    indexAfter = index + jump;
                    set(i, false, false);
                    int len = indexAfter - i;
                    if (len < 0) len = 0;
                    if (indexAfter < i) indexAfter = i;
                    return { BOX, i, indexAfter, len };
                }
                // Alphanumeric, but not box

                if ((jump = search("^\\s*(!{0,1}\\s*fun)\\s+", s)) != -1) {
                    // {\s*}fun{\s+}
                    indexAfter = index + jump;
                    set(i, false, false);
                    int len = indexAfter - i;
                    if (len < 0) len = 0;
                    if (indexAfter < i) indexAfter = i;
                    return { FUN, i, indexAfter, len };
                }
                // Alphanumeric, but not fun

                int max = 25;
                if (max > s.length()) max = s.length();
                cout << "Error: Unknown alphanumeric text inside '<': `" <<
                        s.substr(0, max) << "`\n";
                int len = index - 1;
                if (len < 0) len = 0;
                return { UNKNOWN, i, index, len };
            }
//        } else if (c == '!') {
//            // Either: Box metadata, or static functions
//            int len = index - 1;
//            if (len < 0) len = 0;
//            return { EX_MARK, i, index, len };
        } else if (c == ':' && peekNext(1) == '3') {
            // Either: catflap or cat-flap
            move(2); // Jump past :3
            int len = index - 1;
            if (len < 0) len = 0;
            return { CAT_FLAP, i, index, len };
        } else if (isAlphanumeric()) {
            const auto& s = currentString();
            int jump = 0;
            if ((jump = search("^\\s*(owo|var|uwu)\\s+\\w+\\s*<", s)) != -1) {
                indexAfter = index + jump - 1;
                set(i, false, false);
                int len = indexAfter - i;
                if (len < 0) len = 0;
                if (indexAfter < i) indexAfter = i;
                return { VAR, i, indexAfter, len };
            }
            // Alphanumeric, but not owo/var/uwu

            if ((jump = search("^\\s*(scawy|spoopy)\\s*<", s)) != -1) {
                // {\s*}(scawy or spoopy){\s+}
                indexAfter = index + jump - 1;
                set(i, false, false);
                int len = indexAfter - i;
                if (len < 0) len = 0;
                if (indexAfter < i) indexAfter = i;
                return { SCAWY_SPOOPY, i, indexAfter, len };
            }
            // Alphanumeric, but not scawy/spoopy

            // Not owo/var/uwu, but alphanumeric
            return { UNKNOWN, i, index, 0 };
        }

        int len = index - 1;
        if (len < 0) len = 0;
        return { UNKNOWN, i, index, len };
    }

}