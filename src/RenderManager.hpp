
#pragma once

#include <ostream>
#include <sstream>
#include <vector>

#include "RenderComponent.hpp"

namespace Thoth {

    /*
     *
     * RenderManager :
     * Defines an entire page of HTML to be rendered.
     * 
     * @TODO
     *  Provide some variables to define details about the page
     *  that are for human readability.
     *  See if comp vectors should have elements allowed
     *    Maybe Head needs a custom class of component
     *    Or could be wise to set certain things inside of the
     *    manager directly
     * 
     */
    class RenderManager {

    // Public functions
    public:

        // Default constructor
        RenderManager();

        // Renders the entire page into a given ostream
        virtual void RenderOutput(std::ostream& strm);

        // Adds a component to the head of this manager at the given position
        // Defaults to the end of the list
        RenderManager& AddToHead(RenderComponent* compToAdd, int position = -1);

        // Adds a component to the body of this manager at the given position
        // Defaults to the end of the list
        RenderManager& AddToBody(RenderComponent* compToAdd, int position = -1);

    // Protected functions
    protected:

        // Renders the head of the manager
        virtual std::stringstream RenderHead();
        void RenderHead(std::stringstream& strm);

        // Renders the body of the manager
        virtual std::stringstream RenderBody();
        void RenderBody(std::stringstream& strm);

    // Private variables
    private:

        // Components that make up the page
        std::vector<RenderComponent*> headComponents;
        std::vector<RenderComponent*> bodyComponents;

    };

} // namespace Thoth
