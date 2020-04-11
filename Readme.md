# Thoth

Static HTML generation using C++ based on a "atomic design" philosophy.

_**NOTE**_\
This is in *very* infantile stages of production.

## Introduction

Thoth aims to bring an easy to build and modify way of creating pages of HTML using C++.\
The main goal is to allow for an easily iterchangable design when creating a basic website. For instance, you might use this when creating an API documentation site.\
The generator does not limit what you want to add to your site, small changes between pages are a breeze. It also allows you to break it's own rules and build the entire page with one element.

This library uses C++ 17.

## Design Model

The model used when creating HTML with Thoth is based on an "atomic design" philosophy. It is not strict though, as stated [above](#introduction) you can break the rules.\
This means that your pages should be broken down into it's smallest elements. These should be very small reusable bits of HTML.\
For instance a single image. You then combine these into larger and larger pieces that eventually turn into an entire page.

Now it is not strictly atomic. The structure used here has three layers (element, compoment, manager) where as most atomic designs would have around four or five (atom, compound, layout, template). The names are not important but Thoth is slimmer then those.\
The other main difference is that most atomic designs have a strict rule where the hierarchy of parts must be obeyed. Meaning an compound can contain an atom but it cannot contain a layout. This is not the case in Thoth.\
At first that might sound like it defeats the entire purpose of atomic design, which it may. Do we care? Not really.\
Thoth gets rid of the strict hierarchy for two main reasons.

* The first is for freedom. You can do what you want.
* The second is to allow for the parts of your site to be defined by what it does rather then what it contains.

The second arguement may need a bit more detail.\
A part of your HTML should not be so strictly defined just from it being an atom. Instead, that atom should be able to hold whatever data you want it to and still define it as an atom. The meaning of an element being an element should be defined by *you*.\
For example, you may want a wrapper around certain sections of your HTML. In a typical atomic design you would create a "larger" part to hold everything you wanted to wrap.\
In Thoth though you would instead have an element defined as a wrapper. You can then put this around a "larger" component. The reasoning for this is that the wrapper is actually a very small part even though it may have a lot of stuff inside of it.

Here is a brief overview of the three main types used to build HTML with Thoth.

### RenderElement

The [RenderElement](./src/RenderElement.hpp), or element, is used to define a small and reusable part of HTML.\
These elements are defined as any class that is or inherits from the `RenderElement` class.

An element is comprised at the base level as a tag, any attributes, and the content which is usually a string or another element.

By themselves these cannot be rendered; they have to be rendered through a [RenderComponent](./src/RenderComponent.hpp).

### RenderComponent

The [RenderComponent](./src/RenderComponent.hpp), or component, is used to define a group of RenderElements that should render together. This is defined as any class that is or inherits from the `RenderComponent` class.

Components are comprised at the base level of elements. At this level the component can be rendered into HTML.

### RenderManager

The [RenderManager](./src/RenderManager.hpp), or manager, is used to define a full page of HTML. This is defined as any class that is or inherits from the `RenderManager` class.

A manager is comprised at the base level as a set of components. Typically the user should over ride this class and implement logic to the rendering that manages which components should be rendered and with what info.\
The class is reusable so not every page needs an entirely seperate manager.

This is the class you want an outside service, such as a server, to interact with.

## Getting Started

To add the Thoth library to your project it's suggested you include this via [git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules) if you are using git in your project.\
To link up CMake you should just need to this to your `CMakeLists.txt` file (assuming Thoth is within the `lib` folder) :

```
add_subdirectory(lib/Thoth)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Setup your exe here.

target_link_libraries(myExe PUBLIC Thoth)
```

Then you should be able to include neccesary headers by using `<Thoth/header.hpp>`.

## Name

The name "Thoth" comes from the Egyptian god with the same name.

> Thoth, (Greek), Egyptian Djhuty, in Egyptian religion, a god of the moon, of reckoning, of learning, and of writing. He was held to be the inventor of writing, the creator of languages, the scribe...

[Source](https://www.britannica.com/topic/Thoth)

This was chosen due to the connection to writing and this project being made to write HTML. That's it, nothing too fancy.

## TODO

* Header of typical definitions (a, img, p, ...)
    * Perhaps make in this or also a "RenderSuite" header that includes all the needed stuff for quick building
* Remove str content and replace with a no tag element
* allow linking CSS
* Debugging mode where comments appear before components, make an ifdef or as statics if set by ui
* Replace stringstreams with ostream?
* Allow elements to be used as a "wrapper" for other groups
* Get a visualization for the data module
* Have element content rendering be seperate function to allow for easier overriding
* Make tests folder and create tests
    * Add as examples
* Have empty elements render on one line with no space
* Allow for elements like br or img to render like "<xyz />"
* Allow for comments placing (why would you manually need this but we will make it)
* Caching
    * Elements with no variable data cache the first time they are rendered
    * Variable data elements will be cached once when the render manager is used
    * Should elements cache within themselves or have a central storage in the manager?
    * Indentation would have to be differnent, setwidth might help
* Have renderer automatically link files / images from a dir to avoid hardcoded links
* Since this uses variant, look into string_view for optimization
* CMake
    * See about private vs public include paths
    * Set the standard automatically