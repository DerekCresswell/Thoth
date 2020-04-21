
#pragma once

#include <string>

#include <Thoth/Attribute.hpp>

namespace Thoth {

    /* --- StandAloneAttributes --- */

    /*
     *
     * Hidden :
     * Defines the 'hidden' attribute.
     *
     */
    class Hidden : public StandAloneAttribute {

    // Public functions
    public:

        // Default constructor
        Hidden();

    };

    /* --- End StandAloneAttributes --- */

    /* --- SingleValueAttributes --- */

    /*
     *
     * Alt :
     * Defines the 'alt' attribute.
     *
     */
    class Alt : public SingleValueAttribute<std::string> {

    // Public functions
    public:

        // Default constructor
        Alt();

    };

    /*
     *
     * Href :
     * Defines the 'href' attribute.
     *
     */
    class Href : public SingleValueAttribute<std::string> {

    // Public functions
    public:

        // Default constructor
        Href();

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
     * Name :
     * Defines the 'name' attribute.
     *
     */
    class Name : public SingleValueAttribute<std::string> {

    // Public functions
    public:

        // Default constructor
        Name();

    };

    /*
     *
     * Title :
     * Defines the 'title' attribute.
     *
     */
    class Title : public SingleValueAttribute<std::string> {

    // Public functions
    public:

        // Default constructor
        Title();

    };

    /*
     *
     * Value :
     * Defines the 'value' attribute.
     *
     */
    class Value : public SingleValueAttribute<std::string> {

    // Public functions
    public:

        // Default constructor
        Value();

    };

    /* --- End SingleValueAttributes --- */

    /* --- MultiValueAttributes --- */

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

    /* --- End MultiValueAttributes --- */

} // namespace Thoth

/* --- Template Definitions --- */

namespace Thoth {

    /* --- StandAloneAttributes --- */

    /* -- Hidden -- */

    /* Public */

    // Constructs an empty hidden attribute
    Hidden::Hidden()
        : StandAloneAttribute("hidden") {}

    /* --- End StandAloneAttributes --- */

    /* --- SingleValueAttributes --- */

    /* -- Alt -- */

    /* Public */

    // Constructs an empty alt attribute
    Alt::Alt()
        : SingleValueAttribute<std::string>("alt") {}

    /* -- Href -- */

    /* Public */

    // Constructs an empty href attribute
    Href::Href()
        : SingleValueAttribute<std::string>("href") {}

    /* -- ID -- */

    /* Public */

    // Constructs an empty id attribute
    ID::ID()
        : SingleValueAttribute<std::string>("id") {}

    /* -- Name -- */

    /* Public */

    // Constructs an empty name attribute
    Name::Name()
        : SingleValueAttribute<std::string>("Name") {}

    /* -- Title -- */

    /* Public */

    // Constructs an empty title attribute
    Title::Title()
        : SingleValueAttribute<std::string>("title") {}

    /* -- Value -- */

    /* Public */

    // Constructs an empty value attribute
    Value::Value()
        : SingleValueAttribute<std::string>("value") {}

    /* --- End SingleValueAttributes --- */

    /* --- MultiValueAttributes --- */

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

    /* --- End MultiValueAttributes --- */

} // namespace Thoth