
#pragma once

#include <sstream>
#include <string>
#include <variant>

#include "IndentData.hpp"

namespace Thoth {

    // Forward declaration for RenderComponent
    class RenderComponent;

    /*
     *
     * RenderElement : 
     * Defines an element of html that can be rendered by
     * a RenderComponent.
     * 
     * @TODO
     *  Convert classes into vector and add functions for get / set.
     *  Add other similar identifiers.
     *  Make content a vector.
     *  Make functions like addclass return to element for chaining.
     *
     */
    class RenderElement {

    // Short name for allowed content types
    using contentType = std::variant<std::string, RenderElement*>;
 
    // Public functions
    public:

        // Main constructor
        explicit RenderElement(std::string tag);

        // Constructor that takes content immediately
        RenderElement(std::string tag, contentType content);

        // Adds a class to this element
        void AddClass(std::string classes);

    // Protected member variables
    protected:

        // The HTML tag of this element
        std::string tag;

        // The content inserted into the element
        contentType content;

        // The classes added to the element's tag
        std::string classes;

    // Protected functions
    protected:

        // Renders the element as HTML as a stringstream
        // Takes an IndentData to define the amount of indentation applied
        virtual std::stringstream RenderOutput(IndentData indentData = NO_INDENT);

        // Renders the element as HTML into a stringstream
        // Takes an IndentData to define the amount of indentation applied
        virtual void RenderOutput(std::stringstream& strm, IndentData indentData = NO_INDENT);

    public:
    
        // Marks the RenderComponent as a friend to allow for rendering
        friend RenderComponent;

    };

}