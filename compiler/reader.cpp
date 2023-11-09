#include "reader.h"
#include "../utils/utils.h"

namespace compiler {

    char Reader::peekPrev() {
        if (index == 0)
            return '\n';
        return str[index - 1];
    }

    char Reader::curr() {
        return str[index];
    }

    char Reader::peekNext() {
        if (index > end)
            return '\n';
        return str[index + 1];
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

}