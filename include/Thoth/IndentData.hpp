
#pragma once

#include <string>

namespace Thoth {

    // Enum for the ASCII codes of tabs and spaces
    enum IndentStyle {

        TABS = 9,
        SPACES = 32

    };

    // Holder for data of how to make indentation
    struct IndentData {

        IndentStyle style;
        unsigned int size;
        unsigned int depth;

    };

    // Static IndentData that yields no indentation
    static IndentData NO_INDENT = {IndentStyle::TABS, 0, 0};

    // Returns a string containing the indent string
    std::string GetIndent(IndentData indentData);

} // namespace Thoth