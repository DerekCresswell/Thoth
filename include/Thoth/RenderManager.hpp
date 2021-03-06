
#pragma once

#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>

#include <Thoth/RenderComponent.hpp>

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
     *  Add better data insertion for head / html elements
     *  Create overload for head elements and streamline input there
     *
     */
    class RenderManager {

    // Public functions
    public:

        // Default constructor
        RenderManager();
        RenderManager(const std::string& title);

        // Renders the entire page into a given ostream
        virtual void RenderOutput(std::ostream& strm);

        // Adds a component to the head of this manager at the given position
        // Defaults to the end of the list
        RenderManager& AddToHead(RenderComponent* compToAdd, int position = -1);

        // Removes a component from the head of this manager at a given
        // position or by value
        RenderManager& RemoveFromHead(int position);
        RenderManager& RemoveFromHead(const RenderComponent& compToRem);

        // Adds a component to the body of this manager at the given position
        // Defaults to the end of the list
        RenderManager& AddToBody(RenderComponent* compToAdd, int position = -1);

        // Removes a component from the body of this manager at a given
        // position or by value
        RenderManager& RemoveFromBody(int position);
        RenderManager& RemoveFromBody(const RenderComponent& compToRem);

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

        // Title inserted into the head
        std::string title;

        // Components that make up the page
        std::vector<RenderComponent*> headComponents;
        std::vector<RenderComponent*> bodyComponents;

    };

} // namespace Thoth
