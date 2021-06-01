SNUIFW draws significant inspiration from modern functional document models, like React. Starting from this powerful front facing programming model, a number of additional features are added under the hood:

- Modular Backend: Support for SDL, GLFW, or custom application layers; Support for OpenGL or Vulkan graphics APIs; support for Skia, or our own custom draw layer.
- Performant Powerful Updates: Through the use of a shadow model and immutable data structure principles, we avoid expensive updates.
- Flexible Threading: SNUIFW can work with nearly any thread model, the onus is primarily on the user to coordinate when actions are run and on what threads, or use one of our presets.



## Application

A SNUIFW application is a collection of layers contained in an object called a `Context`. The Context provides support for the layers to communicate and cooperate. The layers typically found in a SNUIFW application include:

- `IApplicationLayer` - Provides a wrapper around the application layer of the program to provide input and window manager interaction. Examples include SDL and GLFW, but this can also be replaced with a custom implementation that wraps an engine's application layer interface, or a virtual window manager's interface.
- `IGraphicsLayer` - Provides a wrapper around the hardware acceleration library layer of the program. Examples include OpenGL and Vulkan (which can take as input our various default implementations of `IApplicationLayer`s via various interfaces that the user may implement) or anything else that can provide hardware acceleration control and synchronization.
- `IDrawLayer` - Provides the internal draw interface, likely wrapped around a graphics layer or draw library. Examples include Skia, and our custom draw layers (which can take as input our various default implementations of `IGraphicsLayer`s via various interfaces that the user may implement). This layer is written in a specific way to optimize reuse and performance of the graphics layer, it primarily exposes primitives, and involves a significant support infrastructure meant to be paired with it.
- `IViewModelLayer` - A layer that provides the primary user features. We provide a modular implementation of this layer, but the user may override this with anything they want to take advantage of the rest of the stack.
  - `IRenderLayer` - A layer which maintains the "shadow-dom" render tree and uses this to manipulate the draw layer as necessary. This handles layout and clipping as well.
  - `IStyleLayer` - A layer which provides CSS-esque styling features, primarily for translating user models into render models. This comes in a couple of different constructions, with different features available for each. This is meant for managing the styling features independent of the user model (or at least so user models may "pass them through"). Many components in our included model library rely on a specific style layer variant.
  - `IStateLayer` - A layer which manages and detects the state differences between user models and triggers updates of the user model layer through to the render layer as necessary.
  - `IModelLayer` - A layer for hosting the user models and managing their outward facing features.

The context also provides a number of dispatch features which any layer can add onto and modify (including multi-methods).
