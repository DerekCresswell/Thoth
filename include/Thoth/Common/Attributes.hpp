
#pragma once

#include <string>

#include <Thoth/Attribute.hpp>

namespace Thoth {

    /*
     *
     * Class :
     * Defines the 'class' attribute.
     *
     */
    class Class : public MultiValueAttribute<std::string> {

    // Public functions
    public:

        // Default constructor
        Class();

    // Protected functions
    protected:

        // Overrides MultiValueAttribute::FormatValue
        // By default formats as 'class="value"' (less outer quotes)
        virtual std::string FormatValue(const std::string& value) override;

    };

    /*
     *
     * ID :
     * Defines the 'id' attribute.
     *
     */
    class ID : public SingleValueAttribute<std::string> {

    // Public functions
    public:

        // Default constructor
        ID();

    };

    /*
     *
     * Style :
     * Defines the 'style' attribute.
     * Takes a pair of strings to define each styling where the first value
     * is the CSS property and the second is the CSS value.
     *
     */
    class Style : public MultiValueAttribute<std::pair<std::string, std::string>> {

    // Public functions
    public:

        // Default constructor
        Style();

    // Protected functions
    protected:

        // Overrides MultiValueAttribute::FormatValue
        // By defaults as 'style="value.first:value.second;"' (Less outer quotes)
        virtual std::string FormatValue(const std::pair<std::string, std::string>& value) override;

    };

} // namespace Thoth

/* --- Template Definitions --- */

namespace Thoth {

    /* -- Class -- */

    /* Public */

    // Constructs an empty class attribute
    Class::Class()
        : MultiValueAttribute<std::string>("class") {}

    /* Protected */

    // Formats the values of the class, just passes back value
    std::string Class::FormatValue(const std::string& value) {

        return value;

    }

    /* -- ID -- */

    /* Public */

    // Constructs an empty id attribute
    ID::ID()
        : SingleValueAttribute<std::string>("id") {}

    /* -- Style -- */

    /* Public */

    // Constructs an empty style attribute
    Style::Style()
        : MultiValueAttribute<std::pair<std::string, std::string>>("stlye") {}

    /* Protected */

    // Formats the values of a style
    // Uses 'value.first' as the CSS property and 'value.second' as the CSS value
    std::string Style::FormatValue(const std::pair<std::string, std::string>& value) {

        return value.first + ":" + value.second + ";";

    }

} // namespace Thoth