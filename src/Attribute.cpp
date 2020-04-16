
#include <Thoth/Attribute.hpp>

namespace Thoth {

    namespace Detail {

        /* -- AttributeBase -- */

        /* Protected */

        AttributeBase::AttributeBase(const std::string& name)
            : name(name) {}

    } // namespace Detail

    /* -- StandAloneAttribute -- */

    /* Public */

    StandAloneAttribute::StandAloneAttribute(const std::string& name)
        : Detail::AttributeBase(name) {}

    /* Protected */

    std::string StandAloneAttribute::Format() {

        return name;

    }

} // namespace Thoth