
#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

/*
 *
 * @TODO
 *  Figure out defining attributes at run time
 *  Implement other common attributes
 *  Expand adding / deleting values to include more convience
 *    Add optional safety for overwriting
 *    Clearing values
 *    Dealing with empty values
 *  Use conditional_t and is_fundemental_t to increase preformance of
 *  passing dataType by ref or not
 *  Ensure datatype can become string
 *  Organize Attributes by type too
 *  Add chaining to add, remove, etc
 *
 *  Setup Elm to utilise these attributes properly
 *
 */

namespace Thoth {

    // Forward Declaration for RenderElement
    class RenderElement;

    namespace Detail {

        /*
         *
         * AttributeBase :
         * Defines the base feature set that is an attribute that can be attached
         * to a RenderElement.
         * Rendering capablities are accessible through the RenderElement.
         *
         */
        class AttributeBase {

        // Public variables
        public:

            // The name tof the attribute
            // I.E. "class", "id"
            const std::string name;

        // Protected functions
        protected:

            // Main constructor for attributes
            AttributeBase(const std::string& name);

            // Returns the attribute as it should be rendered
            // This should include name, quotation marks, etc.
            virtual std::string Format() = 0;

        // Friends
        public:

            friend RenderElement;

        };

    } // namespace Detail

    /*
     *
     * StandAloneAttribute :
     * Base class for an attribute with no values.
     * By default this will render as 'name' (less quotes).
     *
     */
    class StandAloneAttribute : public Detail::AttributeBase {

    // Public functions
    public:

        // Main constructor of StandAloneAttribute
        StandAloneAttribute(const std::string& name);

    // Protected functions
    protected:

        // Override of AttributeBase::Format
        virtual std::string Format() override;

    };

    /*
     *
     * SingleValueAttribute :
     * Base class for attributes that have a single data value.
     * By default it renders as 'name="value"' (less outer quotes).
     *
     * The typename 'dataType' determines the type of the value.
     * This type must be able to convert to a string or have an overridden
     * 'Format' function.
     *
     */
    template<typename dataType>
    class SingleValueAttribute : public Detail::AttributeBase {

    // Public functions
    public:

        // Main constructors for SingleValueAttribute
        SingleValueAttribute(const std::string& name);
        SingleValueAttribute(const std::string& name, const dataType& value);

        // Sets the value of this attribute
        virtual void SetValue(const dataType& value);

    // Protected variables
    protected:

        // The value of this attribute
        dataType value;

    // Protected functions
    protected:

        // Override of AttributeBase::Format
        virtual std::string Format() override;

    };

    /*
     *
     * MultiValueAttribute :
     * Base class for attributes with multiple values.
     * By default renders like 'name=""' (less outer quotes) but requires
     * 'FormatValue' to put each value into the list.
     *
     * The typename 'dataType' determines the type of the value.
     *
     */
    template<typename dataType>
    class MultiValueAttribute : public Detail::AttributeBase {

    // Public functions
    public:

        // Main constructors for MultiValueAttribute
        MultiValueAttribute(const std::string& name);
        MultiValueAttribute(const std::string& name, const std::vector<dataType>& values);

        // Sets the values vector directly
        // Does not perserve previous values
        virtual void SetValues(const std::vector<dataType>& values);

        // Adds a value to this attributes values
        // Optionally specify a position for it to be put in at (default is last)
        virtual void AddValue(const dataType& value, int position = -1);

        // Removes a value from this attributes values by position or value
        // Returns a boolean based on whether an element was actually removed
        virtual bool RemoveValue(int position);
        virtual bool RemoveValue(const dataType& value);

    // Protected variables
    protected:

        // Stores the values of this attribute
        std::vector<dataType> values;

    // Protected functions
    protected:

        // Overrides AttributeBase::Format
        virtual std::string Format() override;

        // Defines how an individual value is formatted
        // and returns it as a string
        virtual std::string FormatValue(const dataType& value) = 0;

    };

} // namespace Thoth

/* --- Template Definitions --- */

namespace Thoth {

    /* -- SingleValueAttribute -- */

    /* Public */

    // Constructs an empty SingleValueAttribute
    template<typename dataType>
    SingleValueAttribute<dataType>::SingleValueAttribute(const std::string& name)
        : Detail::AttributeBase(name) {}

    // Constructs a SingleValueAttribute with a value
    template<typename dataType>
    SingleValueAttribute<dataType>::SingleValueAttribute(const std::string& name,
        const dataType& value)
        : Detail::AttributeBase(name), value(value) {}

    // Sets the value of this attribute
    template<typename dataType>
    void SingleValueAttribute<dataType>::SetValue(const dataType& value) {

        this->value = value;

    }

    /* Protected */

    // Default formatting of SingleValueAttibute
    // 'name="value"'
    template<typename dataType>
    std::string SingleValueAttribute<dataType>::Format() {

        return name + "=\"" + value + "\"";

    }

    /* -- MultiValueAttribute -- */

    /* Public */

    // Constructs an empty MultiValueAttribute
    template<typename dataType>
    MultiValueAttribute<dataType>::MultiValueAttribute(const std::string& name)
        : Detail::AttributeBase(name) {}

    // Constructs MultiValueAttribute with a default value list
    template<typename dataType>
    MultiValueAttribute<dataType>::MultiValueAttribute(const std::string& name,
        const std::vector<dataType>& values)
        : Detail::AttributeBase(name), values(values) {}

    // Directly sets the value list of this attribute
    template<typename dataType>
    void MultiValueAttribute<dataType>::SetValues(const std::vector<dataType>& values) {

        this->values = values;

    }

    // Adds a value to this attributes list
    template<typename dataType>
    void MultiValueAttribute<dataType>::AddValue(const dataType& value, int position) {

        // If position is not set use 'push_back'
        if(position < 0) {
            values.push_back(value);
        } else {
            values.insert(values.begin() + position, value);
        }

    }

    // Removes a value from this attributes list by position
    template<typename dataType>
    bool MultiValueAttribute<dataType>::RemoveValue(int position) {

        // Ensure the position is valid
        if(position < 0 && position >= values.size())
            return false;

        values.erase(values.begin() + position);

        return true;

    }

    // Removes a value from this attribute by value
    // @TODO
    //   allow removing multiple, + ensure working proper
    //   Add checks for seeing if element was removed
    template<typename dataType>
    bool MultiValueAttribute<dataType>::RemoveValue(const dataType& value) {

        // Try erasing value
        auto it = values.erase(std::remove(values.begin(), values.end(), value), values.end());

        // Check if value was found

        return true;

    }

    /* Protected */

    // Renders this attribute and returns it as a string
    template<typename dataType>
    std::string MultiValueAttribute<dataType>::Format() {

        std::stringstream strm;

        strm << name << "=\"";

        // Last element must be isolated to prevent the last space being added
        auto lastIt = values.end();
        lastIt--;

        // Loop through every value except the last
        for(auto it = values.begin(); it != lastIt; it++) {

            strm << FormatValue(*it) << " ";

        }
        strm << FormatValue(*lastIt) << "\"";

        return strm.str();

    }

} // namespace Thoth