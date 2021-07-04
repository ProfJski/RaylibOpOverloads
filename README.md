# RaylibOpOverloads
## C++ Operator Overloads for RayLib

### What is it?
RaylibOpOverloads is a header-only include file that adds a variety of operator overloads to make C++ coding with Raylib easier.

[RayLib](https://github.com/raysan5/raylib) is a great graphics library written in C by Ramon Santamaria.  The C language does not provide operator overloads.  For those who prefer to work in C++, operator overloads can make your code easier to write and read.

The Raylib Operator Overloads header provides two families of overloads:
1. Arithmetic operator overloads for the Vector, Matrix and Color types
2. Output stream overloads for printing most `struct` variables to `cout`, filestreams, etc.

The arithmetic operators permit a more natural, algebraic way of writing equations.  For example, the cumbersome and hard-to-read expression

`VectorA=Vector2Subtract(Vector2Scale(VectorB,2.0),Vector2Add(VectorC,VectorD))` 

can be rewritten in more expressive and succinct form:

`VectorA=2.0*VectorB-(VectorA+VectorD)`

The output stream overloads permit easy printing of most `struct` variables to any C++ output stream.  Want to print all the parameters of your `Camera3D mycamera`?  Simply write:

`cout<<mycamera;`

Presto!  All the data about your camera will be printed: its position, target, up vector, projection type, FOV and camera matrix.  Great for debugging, logging, etc.

### What it isn't
If you are looking for a C++ wrapper, there are projects such as [Rob Loach's raylib-cpp at https://github.com/RobLoach/raylib-cpp](https://github.com/RobLoach/raylib-cpp).  No new methods or objects are introduced in my header, merely operator overloads, many of which call RayLib functions.

## List of Overloads
### Arithmetic operators:
* `operator+` (Addition) for Vector2, Vector3, Vector4, Matrix and Color
* `operator+=`(Addition and assignment) for Vector2, Vector3, Vector4, Matrix and Color
* `operator-` (Unary negation) for Vector2 and Vector 3
* `operator-` (Subtraction) for Vector2, Vector3, Vector4, Matrix and Color
* `operator-=` (Subtraction and assignment) for Vector2, Vector3, Vector4, Matrix and Color
* `operator*` (Multiplication) for scalar multiplication of Vector2, Vector3 and Color
* `operator*=` (Multiplication and assignment) for scalar multiplication of Vector2, Vector3 and Color
* `operator*`(Multiplication) for Matrix * Matrix and Color * Color
* `operator*=`(Multiplication and assignment) for Matrix * Matrix and Color*Color
* `operator/` (Division) for scalar division of Vector2, Vector3 and Color.  Checks for division by zero and throws an exception (RayLib has no such check)
* `operator/=` (Division and assignment) for scalar division of Vector2, Vector3 and Color.
* `operator==` (Equality operator) for Color.  Special options for Vector2 and Vector3.
### Output stream operators `operator<<` for:
* `Vector2`, `Vector3` and `Vector4`. Your choice of two styles: ordered pair `(1,2,3)` or labeled components `x=1, y=2, z=3`
* `Color`.  Likewise two styles: ordered set `(255,255,255,255)` in RGBA order or labeled components `r=255, g=255, b=255, a=255`
* `Matrix`. OpenGL style 4x4 - right handed, column major  (This is the only kind of Matrix in RayLib)
* `Rectangle`
* `Image` and `Texture`.  Simply write `cout<<image` to print the image's width, height, mipmap levels and pixel format both by number and _by name_ which makes it easy to see how your pixels are stored.  Instead of just `"PixelFormat=7"` you will see the `enum` name and comment `"PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 32 bpp"` which is much more informative.
* `Camera2D`.  Prints the camera's offset, target, rotation, zoom and matrix.
* `Camera3D`.  If the projection is perspective, it prints the camera's position, target, up vector, projection mode, field-of-view and projection matrix.  If the projection is orthographic, it prints the near plane width instead of FOV.
* `Ray`. Position and direction.
* `RayHitInfo`. If no hit, it prints "Ray missed."  If hit, it prints "Ray hit" followed by distance, position and surface normal vectors.
* `BoundingBox`.  Prints coordinates of min and max corners.
* `NPatchInfo`. Prints source rectangle, offsets for left, right, top and bottom, and layout code
* `CharInfo`. (For Fonts) Prints Unicode value, X & Y Offsets, and X Advance position
* `FontInfo`. Prints base size, number of characters, and padding.

## FAQ
*What are the options for the equlity operator `operator==`?*

Comparing two integer quantities is straightforward and so is comparing any type based upon them like RayLib's `Color`.  Comparing two float values [is not straightforward](https://floating-point-gui.de/errors/comparison/).  Therefore you have a choice in the `#define` section at the head of the file.

`EQUALITY_OPERATOR_SIMPLE`: Evaluates `VectorA==VectorB` as true IFF a.x==b.x and a.y==b.y, etc.  The overload merely invokes how `operator==` is defined for floats in one's C++ implementation.

`EQUALITY_OPERATOR_KNUTH`: Uses C++ machine epsilon from `std::numeric_limits` to establish inequality if two quantities are close enough to be considered equal given the machine's precision and the magnitude of the floats.  From [https://stackoverflow.com/a/253874](https://stackoverflow.com/a/253874), which in turn cites Knuth

**NONE**: If you comment out both define statements, attempts to evaluate `VectorA==VectorB` will fail to compile, which may be preferable behavior depending on the context.

Why does it matter?  Sometimes rounding error can make two vectors which should be identical fail an equality test.  Try something like this:

```
Vector3 v1={1.0,1.5,2.0};
Vector3 v2=v1;
v2*=sqrt(2.0);
v2/=sqrt(2.0);
cout<<(v1==v2);
```
Does v1==v2?  The result may depend on your computer architecture and compiler.  On my system (Intel, Debian) with `EQUALITY_OPERATOR_SIMPLE`, no.  With `EQUALITY_OPERATOR_KNUTH`, yes.

*Why does Vector4 lack scalar multiplication, scalar division, and unary negation?*

Because in RayLib Quaternion is a `typedef` (alias) of Vector4.  Since scaling and negation work differently in quaternion mathematics vs. linear vectors, I wished to avoid any confusion by defining overloads that may not behave as expected when used with this type.  You can always write your own based on the models provided if you wish.

*Can you add something I'd like?*

Maybe, if it's an operator overload and I know how to do it.

*Why did you use references in most cases?*

To avoid the overhead of passing by value and copying if these operations are used frequently in a loop.  Const references are not used for the left hand side of operators with assignment ( `+=` `-=` `*=` `/=` ) because the left-hand-side is modified and then returned for operator chaining, which seems to be best practice, if I understand it correctly.
Of course, there's still overhead when the RayLib functions themselves are invoked, because the arguments are passed by value, but I have no control over that.


