
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
 *  
 *  Setup Elm to utilise these attributes properly 
 * 
 */

namespace Thoth {
    
    class RenderElement;

    template<typename dataType>
    class Attribute {

    public:

        std::string name;

        bool isStandAlone;

        bool isMultiValue;

        std::vector<dataType> values;

    // TEMP
    //protected:

        Attribute(const std::string& name, bool isStandAlone, bool isMultiValue);

        std::string Format();

        virtual std::string FormatValue();

    public:

        friend RenderElement;

    };

    template class Attribute<std::string>;

} // namespace Thoth