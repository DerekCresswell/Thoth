
#include "RenderManager.hpp"

namespace Thoth {

    /* Public */

    // Constructs a blank RenderManager
    RenderManager::RenderManager() {}

    // Renders the entire page into a given ostream
    void RenderManager::RenderOutput(std::ostream& strm) {

        //@TODO Add html tags

        strm << RenderHead().str();
        strm << RenderBody().str();

    }

    // Adds a component to the head at a given position
    RenderManager& RenderManager::AddToHead(RenderComponent* compToAdd, int position) {

        if(position < 0) {
            headComponents.push_back(compToAdd);
        } else {
            headComponents.insert(headComponents.begin() + position, compToAdd);
        }

    }

    // Adds a component to the body at a given position
    RenderManager& RenderManager::AddToBody(RenderComponent* compToAdd, int position) {

        if(position < 0) {
            bodyComponents.push_back(compToAdd);
        } else {
            bodyComponents.insert(bodyComponents.begin() + position, compToAdd);
        }

    }

    /* Protected */

    // Renders the head as a stringstream
    std::stringstream RenderManager::RenderHead() {

        //@TODO Add tags

        std::stringstream strm;

        for(RenderComponent* rc : headComponents) {

            rc->RenderOutput(strm);

        }

        return strm;

    }

    // Renders the head into a stringstream
    void RenderManager::RenderHead(std::stringstream& strm) {

        strm << RenderHead().str();

    }

    // Renders the body as a stringstream
    std::stringstream RenderManager::RenderBody() {

        //@TODO Add tags

        std::stringstream strm;

        for(RenderComponent* rc : bodyComponents) {

            rc->RenderOutput(strm);

        }

        return strm;

    }

    // Renders the body into a stringstream
    void RenderManager::RenderBody(std::stringstream& strm) {

        strm << RenderBody().str();

    }

    /* Private */

} // namespace Thoth