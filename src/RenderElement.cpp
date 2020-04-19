
#include <Thoth/RenderElement.hpp>

namespace Thoth {

    /* Public */

    // Constructs a RenderElement
    RenderElement::RenderElement(const std::string& tag)
        : tag(tag) {}

    // Constructs a RenderElement with content
    RenderElement::RenderElement(const std::string& tag, const contentType& content) 
        : tag(tag), content(content) {}

    /* Protected */

    // Renders the Element as HTML
    std::stringstream RenderElement::RenderOutput(IndentData indentData) {

        // the stream to render into
        std::stringstream strm;

        // Setup indents
        std::string tagIndent = GetIndent(indentData);
        indentData.depth++;
        std::string contentIndent = GetIndent(indentData);

        // Apply tag
        strm << tagIndent << "<" << tag;

        // Format attributes
        if(attributes.size() > 0) {

            strm << " ";

            // Last attribute must be isolated to prevent the last space being added
            auto lastIt = attributes.end();
            lastIt--;

            // Loop through every attribute except the last
            for(auto it = attributes.begin(); it != lastIt; it++) {

                strm << (*it)->Format() << " ";

            }
            strm << (*lastIt)->Format();

        }

        // Close the tag
        strm << ">";

        // Insert content
        bool hasContent = true;
        if(std::string* contentStr = std::get_if<std::string>(&content)) {

            // If there is no content 'contentStr' will be an empty string
            if(hasContent = !contentStr->empty()) {
                strm << "\n" << contentIndent << *contentStr << "\n";
            }

        } else if(RenderElement **contentElm = std::get_if<RenderElement*>(&content)) {

            // A new line must be added since no content is only detected
            // as a string
            strm << "\n";
            (*contentElm)->RenderOutput(strm, indentData);

        } else {
            hasContent = false;
        }

        // Close tag
        if(hasContent)
            strm << tagIndent;

        strm << "</" << tag << ">\n";

        return strm;

    }

    // Renders the Element as HTML
    void RenderElement::RenderOutput(std::stringstream& strm, IndentData indentData) {

        // Calls RenderOutput to generate stringstream to insert
        strm << RenderOutput(indentData).str();

    }

} // namespace Thoth