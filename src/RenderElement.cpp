
#include <Thoth/RenderElement.hpp>

namespace Thoth {

    /* Public */

    // Constructs a RenderElement
    RenderElement::RenderElement(const std::string& tag)
        : tag(tag) {}

    // Constructs a RenderElement with content
    RenderElement::RenderElement(const std::string& tag, const contentType& content) 
        : tag(tag), content(content) {}

    // Adds a class to the classes of this element
    RenderElement& RenderElement::AddClass(const std::string& toAdd) {

        if(std::find(classes.begin(), classes.end(), toAdd) == classes.end())
            classes.push_back(toAdd);

        return *this;

    }

    RenderElement& RenderElement::AddClass(const std::vector<std::string>& toAdd) {

        for(std::string str : toAdd) {
            AddClass(str);
        }

        return *this;

    }

    // Removes a class from this element
    RenderElement& RenderElement::RemoveClass(const std::string& toRem) {

        classes.erase(std::remove(classes.begin(), classes.end(), toRem), classes.end());

        return *this;

    }

    RenderElement& RenderElement::RemoveClass(const std::vector<std::string>& toRem) {

        for(std::string str : toRem) {
            RemoveClass(str);
        }

        return *this;

    }

    // Adds an inline style to this element
    RenderElement& RenderElement::AddStyle(const std::string& property, const std::string& value,
        bool force) {

        auto it = styles.find(property);

        // If the property does not exist we can add the style
        if(it == styles.end()) {
            styles[property] = value;
            return *this;
        }

        // If we are not forcing there is nothing left to do
        if(!force)
            return *this;

        // Otherwise we set the property to the new value
        styles[property] = value;

        return *this;

    }

    // Removes an inline style from this element
    RenderElement& RenderElement::RemoveStyle(const std::string& property) {

        auto it = styles.find(property);
        
        if(it != styles.end())
            styles.erase(it);

        return *this;

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
        if(classes.size() > 0)
            strm << FormatAttributes("class", classes.begin(), classes.end(),
                [](const std::string& str) {
                    return str;
                }
            );

        // Apply styles if they exist
        if(styles.size() > 0)
            strm << FormatAttributes("style", styles.begin(), styles.end(),
                [](auto p) {
                    return p.first + ":" + p.second + ";";
                }
            );

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

    /* Private */

    // Formats attributes and returns them as a string
    // @TODO find out how to enforce that the lambda needs to return a string
    template<class Iter, class Func>
    std::string RenderElement::FormatAttributes(const std::string& atrName, Iter it1,
        Iter it2, const Func& printFunc) {

        std::stringstream strm;

        // Insert the attribute name
        strm << " " << atrName << "=\"";

        // run the format function on each iterator except for the last
        // Doing `it2 - 1` crashes if the iterator is from a map
        // that makes this feel less clean but it works just fine
        for(--it2; it1 != it2; it1++) {
           strm << printFunc(*it1) << " ";
        }
        // Last iterator does not need a space after it
        strm << printFunc(*it2) << "\"";

        return strm.str();

    }

} // namespace Thoth