
#pragma once

#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "IndentData.hpp"
#include "RenderElement.hpp"

namespace Thoth {

    /*
     *
     * RenderComponent :
     * Holds and renders a set of elements
     * 
     * @TODO
     *  Allow for more verbose adding / subtracting of elements
     *  Allow chaining those functions
     * 
     */
    class RenderComponent {

    // Public member variables
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

        // Renders all of the elements in the render list
        // as a stringstream
        virtual std::stringstream RenderOutput();

        // Renders all of the elements in the render list
        // into a given stringstream
        virtual void RenderOutput(std::stringstream& strm);

        // Sets the indentation style of this component
        void SetIndentation(IndentStyle style, unsigned int size);

    // Private member variables
    private:

        // The elements that define the render output of
        // this component
        std::vector<RenderElement*> elements;

    };

} // namespace Thoth