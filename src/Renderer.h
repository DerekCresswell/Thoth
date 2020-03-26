
#pragma once

#include <sstream>
#include <vector>

#include "RenderElement.h"

/*
 *
 * Renderer :
 * Defines a component of HTML to render.
 * 
 * This is the "Compound" of this library.
 * 
 */
class Renderer {

public:

    // Default constructor
    Renderer(RenderElement&);

    // Outputs HTML as a stringstream
    std::stringstream RenderOutput();

    // Outputs HTML into the string stream
    void RenderOutput(std::stringstream&);

    // Adds a sibling RenderElement to the root element
    void AddSibling(RenderElement&);

private:
    
    // The root element of this renderer
    RenderElement root;


};