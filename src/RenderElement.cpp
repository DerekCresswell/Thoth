
#include "RenderElement.hpp"

namespace Thoth {

    /* Public */

    // Constructs a RenderElement
    RenderElement::RenderElement(std::string tag)
        : tag(tag) {}

    // Constructs a RenderElement with content
    RenderElement::RenderElement(std::string tag, contentType content) 
        : tag(tag), content(content) {}

    // Sets the class of the Element
    // Will be turned into vectors later
    void RenderElement::AddClass(std::string classes) {

        this->classes = classes;

    }

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

        // Apply classes if they exist
        if(classes.size() > 0) {

            strm << " class=\"" << classes << "\"";

        }

        // Close the tag
        strm << ">\n";

        // Insert content
        if(std::string* contentStr = std::get_if<std::string>(&content)) {

            strm << contentIndent << *contentStr << "\n";

        // How does get_if work if it's a pointer?
        } else {

            RenderElement* contentElm = std::get<RenderElement*>(content);
            contentElm->RenderOutput(strm, indentData);

        }

        // Close tag
        strm << tagIndent << "</" << tag << ">\n";

        return strm;

    }

    // Renders the Element as HTML
    void RenderElement::RenderOutput(std::stringstream& strm, IndentData indentData) {

        // Calls RenderOutput to generate stringstream to insert
        strm << RenderOutput(indentData).str();

    }

}