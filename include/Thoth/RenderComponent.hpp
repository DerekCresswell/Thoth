
#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include <Thoth/IndentData.hpp>
#include <Thoth/RenderElement.hpp>

namespace Thoth {

    /*
     *
     * RenderComponent :
     * Holds and renders a set of elements
     *
     * @TODO
     *  Allow for more verbose adding / subtracting of elements
     *  Allow chaining those functions
     *  Implicit constructor from single element?
     *
     */
    class RenderComponent {

    // Public variables
    public:

        // The indent style used when rendering
        IndentStyle indentStyle = IndentStyle::TABS;

        // The size of the indents to use
        unsigned int indentSize = 1;

    // Public functions
    public:

        // The default constructor
        RenderComponent();

        // Adds an element to the render list at the given position
        // Defaults to the end of the list
        RenderComponent& AddElement(RenderElement* elmToAdd, int position = -1);

        // Removes an element from the render list by position or value
        RenderComponent& RemoveElement(int position);
        RenderComponent& RemoveElement(RenderElement elmToRemove);
        RenderComponent& RemoveElement(RenderElement* elmToRemove);

        // Renders all of the elements in the render list
        // as a stringstream
        virtual std::stringstream RenderOutput();

        // Renders all of the elements in the render list
        // into a given stringstream
        void RenderOutput(std::stringstream& strm);

        // Sets the indentation style of this component
        void SetIndentation(IndentStyle style, unsigned int size);

    // Private variables
    private:

        // The elements that define the render output of
        // this component
        std::vector<RenderElement*> elements;

    };

} // namespace Thoth