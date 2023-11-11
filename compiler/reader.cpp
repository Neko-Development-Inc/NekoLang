#include "reader.h"
#include "../utils/utils.h"

namespace compiler {

    char Reader::peekPrev() { return peekPrev(1); }
    char Reader::peekPrev(int n) {
        if ((index - n) <= 0)
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

    void Reader::move(long int dir) {
        index += dir;
    }

    constexpr void Reader::set(long int i) {
        index = i;
    }

    // Removes all comments from current text
    void Reader::removeComments() {
        removeComments(false);
    }

    // Removes all comments from current text
    void Reader::removeComments(bool doMapping) {
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
            if (inString) {
                // Include string characters
                out += c;
                // Check for string exit
                if (IN_STRING_1 && p != '\\' && c == '"')
                    IN_STRING_1 = false;
                else if (IN_STRING_2 && p != '\\' && c == '\'')
                    IN_STRING_2 = false;
                else if (IN_STRING_3 && p != '\\' && c == '`')
                    IN_STRING_3 = false;
            } else if (inComment) {
                // Check for comment exit
                if (IN_COMMENT_1 && c == '\n') {
                    IN_COMMENT_1 = false;
                } else if (IN_COMMENT_2 && p != '\\' && c == '*' && n == '/') {
                    IN_COMMENT_2 = false;
                    i++;
                } else if (IN_COMMENT_3 && p != '\\' && c == '\'' && n == '\'' && n2 == '\'') {
                    i += 2;
                    IN_COMMENT_3 = false;
                } else if (IN_COMMENT_4 && p != '\\' && c == '-' && n == '-' && n2 == '>') {
                    i += 2;
                    IN_COMMENT_4 = false;
                }
            } else {
                // Check for string/comment entry
                bool pIsEscape = p == '\\';
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
            if (inString) {
                if (IN_STRING_1) mappings[i] = MappingType::STRING1;
                else if (IN_STRING_2) mappings[i] = MappingType::STRING2;
                else if (IN_STRING_3) mappings[i] = MappingType::STRING3;
                // Check for string exit
                if (IN_STRING_1 && p != '\\' && c == '"')
                    IN_STRING_1 = false;
                else if (IN_STRING_2 && p != '\\' && c == '\'')
                    IN_STRING_2 = false;
                else if (IN_STRING_3 && p != '\\' && c == '`')
                    IN_STRING_3 = false;
            } else if (inComment) {
                // Check for comment exit
                mappings[i] = MappingType::COMMENT;
                if (IN_COMMENT_1 && c == '\n') {
                    IN_COMMENT_1 = false;
                } else if (IN_COMMENT_2 && p != '\\' && c == '*' && n == '/') {
                    IN_COMMENT_2 = false;
                    mappings[i + 1] = MappingType::COMMENT;
                    i++;
                } else if (IN_COMMENT_3 && p != '\\' && c == '\'' && n == '\'' && n2 == '\'') {
                    mappings[i + 1] = MappingType::COMMENT;
                    mappings[i + 2] = MappingType::COMMENT;
                    i += 2;
                    IN_COMMENT_3 = false;
                } else if (IN_COMMENT_4 && p != '\\' && c == '-' && n == '-' && n2 == '>') {
                    mappings[i + 1] = MappingType::COMMENT;
                    mappings[i + 2] = MappingType::COMMENT;
                    i += 2;
                    IN_COMMENT_4 = false;
                }
            } else {
                // Check for string/comment entry
                bool pIsEscape = p == '\\';
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

}