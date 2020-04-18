
#include <Thoth/Attribute.hpp>

namespace Thoth {

    namespace Detail {

        /* -- AttributeBase -- */

        /* Protected */

        // Main constructor for AttributeBase
        AttributeBase::AttributeBase(const std::string& name)
            : name(name) {}

    } // namespace Detail

    /* -- StandAloneAttribute -- */

    /* Public */

    // Main constructor for StandAloneAttribute
    StandAloneAttribute::StandAloneAttribute(const std::string& name)
        : Detail::AttributeBase(name) {}

    /* Protected */

    // Default formatting for StandAloneAttribute
    std::string StandAloneAttribute::Format() {

        return name;

    }

} // namespace Thoth