
#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "IndentData.hpp"

namespace Thoth {

    // Forward declaration for RenderComponent
    class RenderComponent;

    /*
     *
     * RenderElement : 
     * Defines an element of HMTL that can be rendered by
     * a RenderComponent.
     * 
     * @TODO
     *  Add other similar identifiers.
     *  Adds checks for delimiters in AddClass strings
     *  Seperate content rendering into seperate function for easier overriding
     *
     */
    class RenderElement {

    // Short name for allowed content types
    using contentType = std::variant<std::string, RenderElement*>;
 
    // Public functions
    public:

        // Main constructor
        explicit RenderElement(const std::string& tag);

        // Constructor that takes content immediately
        RenderElement(const std::string& tag, const contentType& content);

        // Adds a class (or classes) to this element
        RenderElement& AddClass(const std::string& toAdd);
        RenderElement& AddClass(const std::vector<std::string>& toAdd);

        // Removes a class (or classes) from this element
        // If a class is not present it is ignored
        RenderElement& RemoveClass(const std::string& toRem);
        RenderElement& RemoveClass(const std::vector<std::string>& toRem);

        // Adds the style to this element's inline style
        // Will not add the element if the property is already defined
        // unless 'force' is true
        RenderElement& AddStyle(const std::string& property, const std::string& value,
            bool force = false);
        
        // Removes the inline style from an element using the property
        RenderElement& RemoveStyle(const std::string& property);

    // Protected member variables
    protected:

        // The HTML tag of this element
        const std::string tag;

        // Defines the inline styling of this element
        // in the form of <property, value>
        std::map<std::string, std::string> styles;

        // The content inserted into the element
        contentType content;

        // The classes added to the element's tag
        std::vector<std::string> classes;

    // Protected functions
    protected:

        // Renders the element as HTML as a stringstream
        // Takes an IndentData to define the amount of indentation applied
        virtual std::stringstream RenderOutput(IndentData indentData = NO_INDENT);

        // Renders the element as HTML into a stringstream
        // Takes an IndentData to define the amount of indentation applied
        void RenderOutput(std::stringstream& strm, IndentData indentData = NO_INDENT);

    // Private functions
    private:

        // Prints out an attribute by using the function 'printFunc' on each
        // element between 'begin' and 'end'
        template<class iter, class func>
        std::string FormatAttributes(const std::string& atrName, iter begin,
            iter end, const func& printFunc);

    public:
    
        // Marks the RenderComponent as a friend to allow for rendering
        friend RenderComponent;

    };

} // namespace Thoth