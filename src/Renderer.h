
#pragma once

#include <sstream>
#include <vector>

#include "RenderElement.h"

/*
 *
 * Renderer :
 * Defines a component of HTML to render.
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

private:
    
    class DomLayer {

    public:
        
        std::vector<RenderElement*> elements;

        DomLayer* nextLayer;
    
    };

};