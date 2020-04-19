
#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include <Thoth/Attribute.hpp>
#include <Thoth/IndentData.hpp>

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

        // Adds an attribute of type 'AttrType' to the element and returns a
        // pointer to it
        // If that attribute type is already present this will just return
        // a pointer to that attribut
        template<class AttrType>
        std::shared_ptr<AttrType> AddAttribute();

        // Retrieves an attribute of type 'AttrType'
        // Returns 'nullptr' if the attribute is not found
        template<class AttrType>
        std::shared_ptr<AttrType> GetAttribute();

        // Deletes an attribute of type 'AttrType' and returns a boolean based
        // on whether anything was removed
        template<class AttrType>
        bool RemoveAttribute();

    // Protected variables
    protected:

        // The HTML tag of this element
        const std::string tag;

        // The content inserted into the element
        contentType content;

        // Attributes of this element
        std::vector<std::shared_ptr<Detail::AttributeBase>> attributes;

    // Protected functions
    protected:

        // Renders the element as HTML as a stringstream
        // Takes an IndentData to define the amount of indentation applied
        virtual std::stringstream RenderOutput(IndentData indentData = NO_INDENT);

        // Renders the element as HTML into a stringstream
        // Takes an IndentData to define the amount of indentation applied
        void RenderOutput(std::stringstream& strm, IndentData indentData = NO_INDENT);

    // Friends
    public:

        // Allows for rendering
        friend RenderComponent;

    };

} // namespace Thoth

/* --- Template Definitions --- */

namespace Thoth {

    /* Public */

    // Adds an attribute to this element of type 'AttrType'
    template<class AttrType>
    std::shared_ptr<AttrType> RenderElement::AddAttribute() {

        // First check for an existing attribute of the type
        if(std::shared_ptr<AttrType> attr = GetAttribute<AttrType>()) {

            return attr;

        } else {

            attr = std::make_shared<AttrType>();
            attributes.push_back(attr);
            return attr;

        }

    }

    // Gets the attribute of type 'AttrType' on this element
    // Returns 'nullptr' if it's not found
    template<class AttrType>
    std::shared_ptr<AttrType> RenderElement::GetAttribute() {

        // Check that 'AttrType' is an attribute
        // Only needed here as the other attribute functions all this
        static_assert(std::is_base_of<Detail::AttributeBase, AttrType>::value,
            "'AttrType' must derive from 'Detail::AttributeBase'");

        for(std::shared_ptr<Detail::AttributeBase>& attr : attributes) {

            std::shared_ptr<AttrType> castedPtr = std::dynamic_pointer_cast<AttrType>(attr);

            // @TODO this will allow derived classes to be used
            //   ie (dd : d) but asking for d will return dd
            if(castedPtr) {
                return castedPtr;
            }

        }

        return nullptr;

    }

    // Removes an attribute of type 'AttrType' from this element
    template<class AttrType>
    bool RenderElement::RemoveAttribute() {

        if(std::shared_ptr<AttrType> attr = GetAttribute<AttrType>()) {

            attributes.erase(attr);
            return true;

        }

        return false;

    }

} // namespace Thoth
