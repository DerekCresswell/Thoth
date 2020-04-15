
#pragma once

#include <string>
#include <sstream>
#include <vector>

/*
 *
 * @TODO
 *  Add comments to attribute files
 *  Remove TEMP tags
 *  Implement proper base format funcs
 *    value() should be empty for stand alone
 *  Figure out defining attributes at run time
 *  Split into diff classes for standalone / multi / solo (??)
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

    class StandAloneAttribute : Detail::AttributeBase {

    public:

        StandAloneAttribute(const std::string& name);

    protected:

        virtual std::string Format() override;

    };

    template<typename dataType>
    class SingleValueAttribute : Detail::AttributeBase {

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
    class MultiValueAttribute : Detail::AttributeBase {

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

        virtual std::string FormatValue(const dataType& value);

    };

} // namespace Thoth