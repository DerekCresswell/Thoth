
#include <Thoth/Attribute.hpp>

namespace Thoth {

    /* Protected */

    template<typename dataType>
    Attribute<dataType>::Attribute(const std::string& name, bool isStandAlone,
        bool isMultiValue)
        : name(name), isStandAlone(isStandAlone), isMultiValue(isMultiValue) {}

    template<typename dataType>
    std::string Attribute<dataType>::Format() {

        if(isStandAlone)
            return name;

        std::stringstream strm;

        // TEMP
        strm << name << "=\"";

        strm << FormatValue();

        strm << "\"";

        return strm.str();

    }

    template<typename dataType>
    std::string Attribute<dataType>::FormatValue() {

        // TEMP
        return "a";

    }

} // namespace Thoth