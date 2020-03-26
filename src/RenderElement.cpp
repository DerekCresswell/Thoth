
#include "RenderElement.h"

RenderElement::RenderElement(const char* tag, const char* contentStr, RenderElement *contentElm)
    : tag(tag), contentStr(contentStr), contentElm(contentElm) {}

bool RenderElement::RenderInto(std::stringstream& outStrm, int depth) {

    // Internal stream
    std::stringstream intStrm;

    // Whitespace buffer
    // Content is inserted one level farther than the tags
    std::string tagSpace = InsertDepth(depth);
    std::string contentSpace = InsertDepth(depth + 1);

    // Insert the tag
    intStrm << tagSpace << "<" << tag << ">\n";

    intStrm << contentSpace << contentStr << "\n";

    // Render child elements if there are any
    if(contentElm != nullptr)
        contentElm->RenderInto(intStrm, ++depth);

    // Close the tag and output
    intStrm << tagSpace << "</" << tag << ">\n";
    outStrm << intStrm.str();

    return true;

}

std::string RenderElement::InsertDepth(int depth) {

    return std::string(depth * 4, ' ');

}