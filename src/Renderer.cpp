
#include "Renderer.h"

Renderer::Renderer(RenderElement& root){}// : root(root) {}

std::stringstream Renderer::RenderOutput() {

    // The stream for output
    std::stringstream outStrm;

    // Boiler plate generation
    outStrm << "<!doctype html>\n<html>\n\n";
    outStrm << "<!-- Generated with HTMLRender by Derek Cresswell -->\n\n";
    
    /* Head */

    outStrm << "<head>\n";
    // Implement
    outStrm << "</head>\n";

    /* Body */

    outStrm << "<body>\n";

    // Start by rendering the root element
    //root.RenderInto(outStrm, 0);

    // Close the body and html tag and return
    outStrm << "</body>\n\n</html>";
    return outStrm;

}

void Renderer::RenderOutput(std::stringstream& outStrm) {

    outStrm << RenderOutput().str();

}