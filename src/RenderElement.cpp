
#include "RenderElement.hpp"

namespace Thoth {

    /* Public */

    // Constructs a RenderElement
    RenderElement::RenderElement(std::string tag)
        : tag(tag) {}

    // Constructs a RenderElement with content
    RenderElement::RenderElement(std::string tag, contentType content) 
        : tag(tag), content(content) {}

    // Adds a class to the classes of this element
    void RenderElement::AddClass(std::string toAdd) {

        if(std::find(classes.begin(), classes.end(), toAdd) == classes.end())
            classes.push_back(toAdd);

    }

    void RenderElement::AddClass(std::vector<std::string> toAdd) {

        for(std::string str : toAdd) {
            AddClass(str);
        }

    }

    // Removes a class from this element
    void RenderElement::RemoveClass(std::string toRem) {

        classes.erase(std::remove(classes.begin(), classes.end(), toRem), classes.end());

    }

    void RenderElement::RemoveClass(std::vector<std::string> toRem) {

        for(std::string str : toRem) {
            RemoveClass(str);
        }

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

            strm << " class=\"";

            // Remove final space
            for(std::string str : classes)
                strm << str << " ";

            strm << "\"";

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