
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

    /* -- SingleValueAttribute -- */

    /* Public */

    template<typename dataType>
    SingleValueAttribute<dataType>::SingleValueAttribute(const std::string& name)
        : Detail::AttributeBase(name) {}

    template<typename dataType>
    SingleValueAttribute<dataType>::SingleValueAttribute(const std::string& name,
        const dataType& value)
        : Detail::AttributeBase(name), value(value) {}

    template<typename dataType>
    void SingleValueAttribute<dataType>::SetValue(const dataType& value) {

        this->value = value;

    }

    /* Protected */

    template<typename dataType>
    std::string SingleValueAttribute<dataType>::Format() {

        return name + "=\"" + value + "\"";

    }

    /* -- MultiValueAttribute -- */

    /* Public */

    template<typename dataType>
    MultiValueAttribute<dataType>::MultiValueAttribute(const std::string& name)
        : Detail::AttributeBase(name) {}

    template<typename dataType>
    MultiValueAttribute<dataType>::MultiValueAttribute(const std::string& name,
        const std::vector<dataType>& values)
        : Detail::AttributeBase(name), values(values) {}

    template<typename dataType>
    void MultiValueAttribute<dataType>::SetValues(const std::vector<dataType>& values) {

        this->values = values;

    }

    template<typename dataType>
    void MultiValueAttribute<dataType>::AddValue(const dataType& value, int position) {

        if(position < 0) {
            values.push_back(value);
        } else {
            values.insert(values.begin() + position, value);
        }

    }

    /* Protected */

    template<typename dataType>
    std::string MultiValueAttribute<dataType>::Format() {

        std::stringstream strm;

        strm << name << "=\"";

        for(const dataType& value : values) {

            // Deal with last space
            strm << FormatValue(value) << " ";

        }

        strm << "\"";

        return strm.str();

    }

    template<typename dataType>
    std::string MultiValueAttribute<dataType>::FormatValue(const dataType& value) {

        return value;

    }

} // namespace Thoth