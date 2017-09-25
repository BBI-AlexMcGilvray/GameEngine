EngineCore

Core library to be used by all components of the engine

This is the continuation/improvement to https://github.com/jcnast/Core_Deprecated

The plan here is to make a more dynamic, scalable, and longer lasting engine. If you wish to see a larger scope of the plan,
please see https://github.com/jcnast/EngineCore/_Planning, in particular, the diagram image.

Through Core_Deprecated I have become more familiar with different coding techniques (primarily templates) and have put myself
in a position where I feel comfortable progressing past basic functionality.

I have integreated the Core_Deprecated library into this project and have done the basics of connecting SDL2 (at least in terms
of opening a window and createing an OpenGL context. To re-familiarize myself with SDL I have started writing some basic input
wrapping before moving onto more in-depth systems.

First will likely be some rendering - as the visual confirmation of other systems will be a much needed element.

Outside of rendering, basic functionality in terms of clicking/interacting with the camera will have to come next - along
with possibly some basic UI for generating further elements.

After the basics, GameObject and Collision systems will be next in line.

However, due to the design and de-coupling of the aforementioned systems - I expect to jump around a decent amount to keep things
interesting for me and to be able to have a better idea of how they will all tie together.
