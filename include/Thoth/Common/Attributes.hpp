
#pragma once

#include <string>

#include <Thoth/Attribute.hpp>

namespace Thoth {

    class Class : public MultiValueAttribute<std::string> {

    public:

        Class();

    protected:

        virtual std::string FormatValue(const std::string& value) override;
    
    };

    class ID : public SingleValueAttribute<std::string> {

    public:

        ID();

    };

    class Style : public MultiValueAttribute<std::pair<std::string, std::string>> {

    public:

        Style();

    protected:

        virtual std::string FormatValue(const std::pair<std::string, std::string>& value) override;

    };

} // namespace Thoth

/* --- Template Definitions --- */

namespace Thoth {

    /* -- Class -- */

    /* Public */

    Class::Class()
        : MultiValueAttribute<std::string>("class") {}

    /* Protected */

    std::string Class::FormatValue(const std::string& value) {

        return value;

    }

    /* -- ID -- */

    /* Public */

    ID::ID()
        : SingleValueAttribute<std::string>("id") {}

    /* -- Style -- */

    /* Public */

    Style::Style()
        : MultiValueAttribute<std::pair<std::string, std::string>>("stlye") {}

    /* Protected */

    std::string Style::FormatValue(const std::pair<std::string, std::string>& value) {

        return value.first + ":" + value.second + ";";

    }

} // namespace Thoth