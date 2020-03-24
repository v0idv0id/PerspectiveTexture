# PerspectiveTexture
This example shows how to render a perspective texture on a quad in only 2-dimensions using a nonAffine projective interpolation.

The render pipeline uses modern OpenGL and shaders.

In the assets folder you will find the textures, screenshots of the two ways to render and a screen capture video that shows the program in action.

Click the image below to see the screen capture vide of the program on youtube:

[![Perspective Texture on a quad using non-Affine rendering](http://img.youtube.com/vi/ICWvt6AYo-U/0.jpg)](https://www.youtube.com/watch?v=ICWvt6AYo-U "Perspective Texture on a quad using non-Affine rendering")

## How it works
The problem with quads and linear UV interpolation is that it only arbitrary affine transforms are allowed as long as quad stays a parallelogram. To solve this problem projective interpolation is needed (UVQ). 

This example uses 

* four vertices (3d), each vertex has texture coordinates (3d) and original texture coordinates (3d).

* The OpenGL context, the events and the window is created using glfw.
* The rendering uses a element buffer (indices) to render the 6 vertices (2 triangles) which build the quad.
* Two textures are rendered to the quad:
  * One texture (0) using the UVQ coordinates modified by the nonAffine() function which does the math.
  * The other texture (1) is using the default, unmodified texture coordinats which gives the "wrong" result.
* In the main loop the function nonAffine() is called on every pass and recalculates the TexCoords for the UVQ in the quadVertices array. This array is then uploaded to the GPU ```glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);```
* The vertex shader for the quad just passes the TexCoords and TexCoords_orig to the fragment shader without any modification.
* The fragment shader renders one texture (0) with the modified coordinates ``` texture(texture0,TexCoords.xy/TexCoords.z) ```, the other texture (1) with ``` texture(texture1,TexCoords_orig.xy)```.
  


## Dependencies

* Main dependencies: 
  
  * libglfw3-dev

## Installation / Compile
* make sure you do fullfill the requirements: 
  * ``` sudo apt-get install libglfw3-dev build-essential ```
  
* To compile the demonstration just use:
  * ``` make  ```
* To run it:
  * ``` ./PerspectiveTexture ``` 

While the program is running you can control it with:
```
***Use the mouse to click'n'drag the corners

[A] start/stop animation
[ESC] Exit the program
[Q] Cycle textures
[W] Fade to texture0 (the original coordinates)
[S] Fade to texture1 (the perspective corrected)
[D] Reset to initial state
[E] Dump texture coordinates UVQ
```

## Notes
* Calculating the UVQ in the main program is not really necessary nowerdays - it should be done in the shader - this is part of the future development of this example.#
* Most of the code is for handling the mouse events, keystrokes, loading textures, animation,... the real "magic" is just the ```nonAffine()``` function and using the new coordinates in the fragment shader.

## References
* The main OpenGL concept is based on the examples from https://www.learnopengl.com
* http://reedbeta.com/blog/quadrilateral-interpolation-part-1/ 
* http://www.reedbeta.com/blog/quadrilateral-interpolation-part-2/
* https://github.com/Geistyp/Projective-Interpolation-to-Quadrilateral

## License and Author

MIT License - Copyright (c) 2020 v0idv0id - Martin Willner - lvslinux@gmail.com



