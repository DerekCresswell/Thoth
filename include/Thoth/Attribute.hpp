
#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

/*
 *
 * @TODO
 *  Add comments to attribute files
 *  Figure out defining attributes at run time
 *  Implement other common attributes
 *  Expand adding / deleting values to include more convience
 *    Add optional safety for overwriting
 *  Implement other base functions
 *  Use conditional_t and is_fundemental_t to increase preformance of
 *  passing dataType by ref or not
 *  Ensure datatype can become string
 *  
 *  Setup Elm to utilise these attributes properly 
 * 
 */

namespace Thoth {
        
    class RenderElement;
    
    namespace Detail {

        class AttributeBase {

        public:

            const std::string name;

        protected:

            AttributeBase(const std::string& name);

            virtual std::string Format() = 0;

        public:

            friend RenderElement;

        };

    } // namespace Detail

    class StandAloneAttribute : public Detail::AttributeBase {

    public:

        StandAloneAttribute(const std::string& name);

    protected:

        virtual std::string Format() override;

    };

    template<typename dataType>
    class SingleValueAttribute : public Detail::AttributeBase {

    public:

        SingleValueAttribute(const std::string& name);
        SingleValueAttribute(const std::string& name, const dataType& value);

        virtual void SetValue(const dataType& value);

    protected:

        dataType value;

    protected:

        virtual std::string Format() override;

    };

    template<typename dataType>
    class MultiValueAttribute : public Detail::AttributeBase {

    public:

        MultiValueAttribute(const std::string& name);
        MultiValueAttribute(const std::string& name, const std::vector<dataType>& values);

        virtual void SetValues(const std::vector<dataType>& values);

        virtual void AddValue(const dataType& value, int position = -1);

        virtual bool RemoveValue(int position);
        virtual bool RemoveValue(const dataType& value);

    protected:

        std::vector<dataType> values;

    protected:

        virtual std::string Format() override;

        virtual std::string FormatValue(const dataType& value) = 0;

    };

} // namespace Thoth

/* --- Template Definitions --- */

namespace Thoth {

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

    template<typename dataType>
    bool MultiValueAttribute<dataType>::RemoveValue(int position) {

        if(position < 0 && position >= values.size())
            return false;

        values.erase(std::remove(values.begin(), values.end(), values[position]), values.end());

        return true;

    }

    // @TODO allow removing multiple, + ensure working proper
    template<typename dataType>
    bool MultiValueAttribute<dataType>::RemoveValue(const dataType& value) {

        auto it = values.erase(std::remove(values.begin(), values.end(), value), values.end());

        if(it == values.end())
            return false;

        return true;

    }

    /* Protected */

    template<typename dataType>
    std::string MultiValueAttribute<dataType>::Format() {

        std::stringstream strm;

        strm << name << "=\"";

        // Last element must be isolated to prevent the last space being added
        auto lastIt = values.end();
        lastIt--;
        for(auto it = values.begin(); it != lastIt; it++) {

            strm << FormatValue(*it) << " ";

        }
        strm << FormatValue(*lastIt) << "\"";

        return strm.str();

    }

} // namespace Thoth