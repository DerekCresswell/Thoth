
#include <Thoth/RenderManager.hpp>

namespace Thoth {

    /* Public */

    // Constructs a blank RenderManager
    RenderManager::RenderManager() {}

    // Constructs RenderManager with a title
    RenderManager::RenderManager(const std::string& title)
        : title(title) {}

    // Renders the entire page into a given ostream
    void RenderManager::RenderOutput(std::ostream& strm) {

        strm << "<!doctype html>\n";
        strm << "<html>\n\n";

        strm << RenderHead().str();
        strm << RenderBody().str();

        strm << "\n</html>";

    }

    // Adds a component to the head at a given position
    RenderManager& RenderManager::AddToHead(RenderComponent* compToAdd, int position) {

        if(position < 0) {
            headComponents.push_back(compToAdd);
        } else {
            headComponents.insert(headComponents.begin() + position, compToAdd);
        }

        return *this;

    }

    // Removes a component from the head at a given position
    RenderManager& RenderManager::RemoveFromHead(int position) {

        // Ensure position is valid
        if(position >= 0 && position < headComponents.size()) {
            headComponents.erase(headComponents.begin() + position);
        }

        return *this;

    }

    // Removes a component from the head by value
    RenderManager& RenderManager::RemoveFromHead(const RenderComponent& compToRem) {

        headComponents.erase(std::remove(headComponents.begin(), headComponents.end(),
            &compToRem), headComponents.end());

        return *this;

    }

    // Adds a component to the body at a given position
    RenderManager& RenderManager::AddToBody(RenderComponent* compToAdd, int position) {

        if(position < 0) {
            bodyComponents.push_back(compToAdd);
        } else {
            bodyComponents.insert(bodyComponents.begin() + position, compToAdd);
        }

        return *this;

    }

    // Removes a component from the body at a given position
    RenderManager& RenderManager::RemoveFromBody(int position) {

        // Ensure position is valid
        if(position >= 0 && position < bodyComponents.size()) {
            bodyComponents.erase(bodyComponents.begin() + position);
        }

        return *this;

    }

    // Removes a component from the body by value
    RenderManager& RenderManager::RemoveFromBody(const RenderComponent& compToRem) {

        bodyComponents.erase(std::remove(bodyComponents.begin(), bodyComponents.end(),
            &compToRem), bodyComponents.end());

        return *this;

    }

    /* Protected */

    // Renders the head as a stringstream
    // @TODO
    //   Perhaps this should be set up to take a 'head struct'
    //   to allow for many managers to share mostly the same data
    //   This would benefit from moving FormatAttributes out of Elm
    std::stringstream RenderManager::RenderHead() {

        std::stringstream strm;

        strm << "<head>\n";
        strm << "<title>" << title << "</title>\n";

        for(RenderComponent* rc : headComponents) {

            rc->RenderOutput(strm);

        }

        strm << "</head>\n\n";

        return strm;

    }

    // Renders the head into a stringstream
    void RenderManager::RenderHead(std::stringstream& strm) {

        strm << RenderHead().str();

    }

    // Renders the body as a stringstream
    std::stringstream RenderManager::RenderBody() {

        std::stringstream strm;

        strm << "<body>\n";

        for(RenderComponent* rc : bodyComponents) {

            rc->RenderOutput(strm);

        }

        strm << "</body>\n";

        return strm;

    }

    // Renders the body into a stringstream
    void RenderManager::RenderBody(std::stringstream& strm) {

        strm << RenderBody().str();

    }

    /* Private */

} // namespace Thoth