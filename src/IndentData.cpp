
#include "IndentData.hpp"

namespace Thoth {

    // Creates a sting that is size * depth of style characters 
    std::string GetIndent(IndentData indentData) {

        return std::string(indentData.size * indentData.depth, (char)indentData.style);

    }

} // namespace Thoth