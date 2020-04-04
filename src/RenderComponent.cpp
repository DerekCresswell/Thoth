
#include "RenderComponent.hpp"

namespace Thoth {

    /* Public */

    // Default constructor
    RenderComponent::RenderComponent() {}

    // Adds an element to the render list a given position
    RenderComponent& RenderComponent::AddElement(RenderElement* elmToAdd, int position) {

        // See if a position was specified
        if(position < 0) {

            elements.push_back(elmToAdd);

        } else {

            elements.insert(elements.begin() + position, elmToAdd);

        }

        return *this;

    }

    // Render the output of all the elements making up this component
    std::stringstream RenderComponent::RenderOutput() {

        std::stringstream strm;

        for(RenderElement* re : elements) {

            // Render each component
            re->RenderOutput(strm, {indentStyle, indentSize, 1});

        }

        return strm;

    }

    // Render the output of all the elements making up this component
    void RenderComponent::RenderOutput(std::stringstream& strm) {

        // Call the RenderOutput function and insert that into the stream
        strm << RenderOutput().str();

    }

    // Sets the indentation style of the component
    void RenderComponent::SetIndentation(IndentStyle style, unsigned int size) {

        indentStyle = style;
        indentSize = size;

    }

} // namespace Thoth