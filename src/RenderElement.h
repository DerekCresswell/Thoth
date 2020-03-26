
#pragma once

#include <sstream>
#include <string>

// Forward declaration for the friend
class Renderer;

/*
 *
 * RenderElement :
 * Defines an element of HTML that can be rendered.
 * Mainly for internal use by the Renderer class.
 * 
 * This is the "Atom" of this library.
 * 
 */
class RenderElement {

public:

    // The tag for the element
    const char* tag;

    // The content of the element
    const char* contentStr;

    // A reference to a RenderElement to render inside
    // this element
    RenderElement* contentElm;

    // Constructor
    // Takes a tag then the content
    RenderElement(const char*, const char*, RenderElement* = nullptr);

private:

    // Render output into a stringstream with a depth given
    // by the second argument
    // Returns true if the rendering succeeded
    bool RenderInto(std::stringstream&, int);

    // Returns a string of whitespace to insert depth into
    // the output stream
    std::string InsertDepth(int);

public:

    friend Renderer;

};