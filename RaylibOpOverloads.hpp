#ifndef RAYLIB-OP-OVERLOADS_HPP_INCLUDED
#define RAYLIB-OP-OVERLOADS_HPP_INCLUDED
#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <iostream> //For stream insertion (operator<<) overloading, e.g, cout
#include <string> //For PixelFormatNumberToName()
#include <stdexcept> //For divide-by-zero error trapping

// **************************************************************
//
//      C++ Operator Overloads for RayLib
//
// **************************************************************
//
// RayLib is Copyright (c) 2013-2021 Ramon Santamaria (@raysan5) https://github.com/raysan5/
// Overloads by Eric Jenislawski https://github.com/ProfJski/
//
// These operator overloads are convenience functions of two kinds:
// (1) Arithmetic operator overloads for use on vectors, colors and matricies, etc.  These permit more natural and expressive syntax in C++.
// For example, one can write VectorA=Vector2Subtract(Vector2Scale(VectorB,2),Vector2Add(VectorC,VectorD)) as VectorA=2*VectorB-(VectorA+VectorD).
// (2) Output stream operator overloads to facilitate printing values to cout or filestreams.
//
// --------------------------------------------------------------
//
//  SELECT YOUR OPTIONS USING THE DEFINE STATEMENTS BELOW
//
// (A) Vector format
//
// PRINT_VECTORS_WITH_PARENTHESES prints a vector like an ordered set.  Vector3 {1,2,3} prints as (1,2,3).  Colors print as (255,255,255,255) in RGBA order.
// PRINT_VECTORS_BY_COMPONENT prints a Vector3 {1,2,3} like so: x=1, y=2, z=3.  Colors like so: R=255, G=255, B=255, A=255
//
// (B) Equality Operator
//
// Operator== determines whether Vector A equals Vector B.  The evaluation is straightforward with integer types, but not with floats.
// Three options are provided.
//
// EQUALITY_OPERATOR_SIMPLE: Evaluates VectorA==VectorB as true IFF a.x==b.x and a.y==b.y, etc.  The overload merely invokes how operator== is defined for floats in one's C++ implementation.
// EQUALITY_OPERATOR_KNUTH: Uses C++ machine epsilon from std::numeric_limits to establish inequality if two quantities are close enough to be considered equal given the machine's precision and the magnitude of the floats.  From https://stackoverflow.com/a/253874, which in turn cites Knuth
// NONE: Comment out both options and the equality operator will not be overloaded at all.  Attempts to evaluate VectorA==VectorB will not compile.
//
// To see the difference between _SIMPLE and _KNUTH, try this test: Vector3 v1={1.0,1.5,2.0}; v2=v1; v2*=sqrt(2.0); v2/=sqrt(2.0); Does v1==v2 ?  With _SIMPLE no; with _KNUTH, yes.

//#define PRINT_VECTORS_WITH_PARENTHESES
#define PRINT_VECTORS_BY_COMPONENT

//#define EQUALITY_OPERATOR_SIMPLE
#define EQUALITY_OPERATOR_KNUTH

// **************************************
//
// ARITHMETIC OVERLOADS
//
// **************************************
//
// Since Quaternion is a typedef of Vector4 in RayLib, only addition and substraction overloads are provided for Vector4, since these work the same way with Quaternions as with regular Vectors.
// To avoid confusion, I did not overload Vector4 for negation, multiplication/division or scale, since these operations are different for Quaternions vs. Vector4D


//Addition overloads: componentwise addition
Vector2 operator+(const Vector2& a, const Vector2& b) {
return Vector2Add(a,b);
}

Vector3 operator+(const Vector3& a, const Vector3& b) {
return Vector3Add(a,b);
}

Vector4 operator+(const Vector4& a, const Vector4& b) {
return (Vector4){a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w};
}

Vector2& operator+=(Vector2& a, const Vector2& b) {
    a=a+b;
return a;
}

Vector3& operator+=(Vector3& a, const Vector3& b) {
    a=a+b;
return a;
}

Vector4& operator+=(Vector4& a, const Vector4& b) {
    a=a+b;
return a;
}

Matrix operator+(const Matrix& left, const Matrix& right) {
return MatrixAdd(left,right);
}

Matrix& operator+=(Matrix& left, const Matrix& right) {
    left=MatrixAdd(left,right);
return left;
}

Color operator+(const Color& a, const Color& b) {
    int red,green,blue,alpha;  //To ensure that addition of a+b does not result in components greater than unsigned char's max of 255, we upconvert to int, then check the sum, and cast back to unsigned char
    Color c;
    red=(int)a.r+(int)b.r;
    green=(int)a.g+(int)b.g;
    blue=(int)a.b+(int)b.b;
    alpha=(int)a.a+(int)b.a;

    c.r=(unsigned char)((red>255)?255:red);
    c.g=(unsigned char)((green>255)?255:green);
    c.b=(unsigned char)((blue>255)?255:blue);
    c.r=(unsigned char)((alpha>255)?255:alpha);
return c;
}

Color& operator+=(Color&a, const Color& b) {
    a=a+b;
return a;
}

//Negation: Unary Minus operator
Vector2& operator-(Vector2& a) {
    a=Vector2Negate(a);
return a;
}

Vector3& operator-(Vector3& a) {
    a=Vector3Negate(a);
return a;
}

//Since Quaternion is a Vector4 typedef, I did not provide a negation for Vector4 to avoid confusion with QuaternionInvert();

//Subtraction overloads: componentwise subtraction
Vector2 operator-(const Vector2& a, const Vector2& b) {
return Vector2Subtract(a,b);
}

Vector3 operator-(const Vector3& a, const Vector3& b) {
return Vector3Subtract(a,b);
}

Vector4 operator-(const Vector4& a, const Vector4& b) {
return (Vector4){a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w};
}

Vector2& operator-=(Vector2& a, const Vector2& b) {
    a=a-b;
return a;
}

Vector3& operator-=(Vector3& a, const Vector3& b) {
    a=a-b;
return a;
}

Vector4& operator-=(Vector4& a, const Vector4& b) {
    a=a-b;
return a;
}

Matrix operator-(const Matrix& left, const Matrix& right) {
return MatrixSubtract(left,right);
}

Matrix& operator-=(Matrix& left, const Matrix& right) {
    left=MatrixSubtract(left,right);
return left;
}

Color operator-(const Color& a, const Color& b) {
    int red,green,blue,alpha;  //Convert to int, clamp to min zero, convert back to unsigned char
    Color c;
    red=(int)a.r-(int)b.r;
    green=(int)a.g-(int)b.g;
    blue=(int)a.b-(int)b.b;
    alpha=(int)a.a-(int)b.a;

    c.r=(unsigned char)((red<0)?0:red);
    c.g=(unsigned char)((green<0)?0:green);
    c.b=(unsigned char)((blue<0)?0:blue);
    c.r=(unsigned char)((alpha<0)?0:alpha);
return c;
}

Color& operator-=(Color&a, const Color& b) {
    a=a-b;
return a;
}

//Multiplication overload only provides for multiplying a vector by a scalar.   Vector * Vector is not overloaded to avoid confusion whether one intends a dot product, cross product, etc.
Vector2 operator*(const Vector2& a, float b) {
return Vector2Scale(a,b);
}

Vector3 operator*(const Vector3& a, float b) {
return Vector3Scale(a,b);
}

Matrix operator*(const Matrix& left, const Matrix& right) {
return MatrixMultiply(left,right);
}

Matrix& operator*=(Matrix& left, const Matrix& right) {
    left=MatrixMultiply(left,right);
return left;
}

Vector2& operator*=(Vector2& a, const float b) {
    a=a*b;
return a;
}

Vector3& operator*=(Vector3& a, const float b) {
    a=a*b;
return a;
}

//I'm not sure if the following is useful, but here it is anyway for completeness
Color operator*(const Color& a, const Color& b) {
    int red,green,blue,alpha;
    Color c;
    red=(int)a.r*(int)b.r;
    green=(int)a.g*(int)b.g;
    blue=(int)a.b*(int)b.b;
    alpha=(int)a.a*(int)b.a;

    c.r=(unsigned char)( ( (red>255)?255:(red<0)?0:red) ); //Nested ternary clamps return between 0 and 255
    c.g=(unsigned char)( ( (green>255)?255:(green<0)?0:green) );
    c.b=(unsigned char)( ( (blue>255)?255:(blue<0)?0:blue) );
    c.r=(unsigned char)( ( (alpha>255)?255:(alpha<0)?0:alpha) );
return c;
}

Color& operator*=(Color&a, const Color& b) {
    a=a*b;
return a;
}

Color operator*(const Color& a, const float b) {
    float red,green,blue,alpha;  //We cast to float, clamp, then recast back to unsigned char
    Color c;
    red=(float)a.r*b;
    green=(float)a.g*b;
    blue=(float)a.b*b;
    alpha=(float)a.a*b;

    c.r=(unsigned char)( ( (red>255)?255:(red<0)?0:red) ); //Nested ternary clamps return between 0 and 255
    c.g=(unsigned char)( ( (green>255)?255:(green<0)?0:green) );
    c.b=(unsigned char)( ( (blue>255)?255:(blue<0)?0:blue) );
    c.r=(unsigned char)( ( (alpha>255)?255:(alpha<0)?0:alpha) );
return c;
}

Color& operator*=(Color&a, const float b) {
    a=a*b;
return a;
}

//Division overload: Merely scalar multiplication by the reciprocal, with a Divide-By-Zero check.
Vector2 operator/(const Vector2& a, const float b) {
    if (b==0.0) {
        std::cerr<<"Division by zero error."<<std::endl;
        throw std::domain_error("Division by zero error");
    }
    float recip=1.0/b;
return a*recip;
}

Vector3 operator/(const Vector3& a, const float b) {
    if (b==0.0) {
        std::cerr<<"Division by zero error."<<std::endl;
        throw std::domain_error("Division by zero error");
    }
    float recip=1.0/b;
return a*recip;
}

Vector2& operator/=(Vector2& a, const float b) {
    a=a/b;
return a;
}

Vector3& operator/=(Vector3& a, const float b) {
    a=a/b;
return a;
}

//Equality operator overloads
#ifdef EQUALITY_OPERATOR_SIMPLE
bool operator==(const Vector2& a, const Vector2& b) {
    if ( (a.x==b.x) && (a.y==b.y)) return true;
return false;
}

bool operator==(const Vector3& a, const Vector3& b) {
    if ( (a.x==b.x) && (a.y==b.y) && (a.z==b.z)) return true;
return false;
}

bool operator==(const Vector4& a, const Vector4& b) {
    if ( (a.x==b.x) && (a.y==b.y) && (a.z==b.z) && (a.w==b.w)) return true;
return false;
}
#endif // EQUALITY_OPERATOR_SIMPLE

#ifdef EQUALITY_OPERATOR_KNUTH
//Takes a conservative approach and only affirms that two vectors are equal if all of their respective components are equal within machine precision.
#include <limits>
#include <cmath>
bool operator==(const Vector2& a, const Vector2& b){
    bool XIsEqual=false;
    bool YIsEqual=false;
    XIsEqual = std::fabs(a.x - b.x) <= ( (std::fabs(a.x) > std::fabs(b.x) ? std::fabs(b.x) : std::fabs(a.x)) * std::numeric_limits<float>::epsilon() );
    YIsEqual = std::fabs(a.y - b.y) <= ( (std::fabs(a.y) > std::fabs(b.y) ? std::fabs(b.y) : std::fabs(a.y)) * std::numeric_limits<float>::epsilon() );
return (XIsEqual && YIsEqual);
}

bool operator==(const Vector3& a, const Vector3& b){
    bool XIsEqual=false;
    bool YIsEqual=false;
    bool ZIsEqual=false;
    XIsEqual = std::fabs(a.x - b.x) <= ( (std::fabs(a.x) > std::fabs(b.x) ? std::fabs(b.x) : std::fabs(a.x)) * std::numeric_limits<float>::epsilon() );
    YIsEqual = std::fabs(a.y - b.y) <= ( (std::fabs(a.y) > std::fabs(b.y) ? std::fabs(b.y) : std::fabs(a.y)) * std::numeric_limits<float>::epsilon() );
    ZIsEqual = std::fabs(a.z - b.z) <= ( (std::fabs(a.z) > std::fabs(b.z) ? std::fabs(b.z) : std::fabs(a.z)) * std::numeric_limits<float>::epsilon() );
return (XIsEqual && YIsEqual && ZIsEqual);
}

bool operator==(const Vector4& a, const Vector4& b){
    bool XIsEqual=false;
    bool YIsEqual=false;
    bool ZIsEqual=false;
    bool WIsEqual=false;
    XIsEqual = std::fabs(a.x - b.x) <= ( (std::fabs(a.x) > std::fabs(b.x) ? std::fabs(b.x) : std::fabs(a.x)) * std::numeric_limits<float>::epsilon() );
    YIsEqual = std::fabs(a.y - b.y) <= ( (std::fabs(a.y) > std::fabs(b.y) ? std::fabs(b.y) : std::fabs(a.y)) * std::numeric_limits<float>::epsilon() );
    ZIsEqual = std::fabs(a.z - b.z) <= ( (std::fabs(a.z) > std::fabs(b.z) ? std::fabs(b.z) : std::fabs(a.z)) * std::numeric_limits<float>::epsilon() );
    WIsEqual = std::fabs(a.w - b.w) <= ( (std::fabs(a.w) > std::fabs(b.w) ? std::fabs(b.w) : std::fabs(a.w)) * std::numeric_limits<float>::epsilon() );
return (XIsEqual && YIsEqual && ZIsEqual && WIsEqual);
}
#endif // EQUALITY_OPERATOR_KNUTH


// ********************************************
//
//           OUTPUT STREAM OVERLOADS
//
// ********************************************
// For use with cout, filestreams, etc.
// Two different formats are provided for printing vectors and colors.  Use the #define section at the top of the file to select betweem them.
// Other convenience overloads are provided below which allow for easy printing of components of structs.  Some of these make use of the vector format selected above when Vectors are part of the struct

#ifdef PRINT_VECTORS_WITH_PARENTHESES
std::ostream& operator<<(std::ostream& os, Vector2 a) {
    os<<"("<<a.x<<","<<a.y<<")";
return os;
}

std::ostream& operator<<(std::ostream& os, Vector3 a) {
    os<<"("<<a.x<<","<<a.y<<","<<a.z<<")";
return os;
}

std::ostream& operator<<(std::ostream& os, Vector4 a) {
    os<<"("<<a.x<<","<<a.y<<","<<a.z<<","<<a.w<<")";
return os;
}

std::ostream& operator<<(std::ostream& os, Color c) {
    os<<"("<<(unsigned int)c.r<<","<<(unsigned int)c.g<<","<<(unsigned int)c.b<<","<<(unsigned int)c.a<<")";
return os;
}
#endif

#ifdef PRINT_VECTORS_BY_COMPONENT
std::ostream& operator<<(std::ostream& os, Vector2 a) {
    os<<"x="<<a.x<<", y="<<a.y;
return os;
}

std::ostream& operator<<(std::ostream& os, Vector3 a) {
    os<<"x="<<a.x<<", y="<<a.y<<", z="<<a.z;
return os;
}

std::ostream& operator<<(std::ostream& os, Vector4 a) {
    os<<"x="<<a.x<<", y="<<a.y<<", z="<<a.z<<", w="<<a.w;
return os;
}

std::ostream& operator<<(std::ostream& os, Color c) {
    os<<"R="<<(unsigned int)c.r<<" G="<<(unsigned int)c.g<<" B="<<(unsigned int)c.b<<" A="<<(unsigned int)c.a;
return os;
}
#endif

//Per definition of Matrix in raylib.h as "Matrix type (OpenGL style 4x4 - right handed, column major)"
std::ostream& operator<<(std::ostream& os, Matrix m) {
    os<<" \t"<<m.m0<< "\t"<<m.m4<<" \t"<<m.m8<<" \t"<<m.m12<<"\n";
    os<<" \t"<<m.m1<< "\t"<<m.m5<<" \t"<<m.m9<<" \t"<<m.m13<<"\n";
    os<<" \t"<<m.m2<< "\t"<<m.m6<<" \t"<<m.m10<<" \t"<<m.m14<<"\n";
    os<<" \t"<<m.m3<< "\t"<<m.m7<<" \t"<<m.m11<<" \t"<<m.m15<<"\n";
return os;
}

std::ostream& operator<<(std::ostream& os, Rectangle r) {
    os<<"Rectangle corner: ("<<r.x<<","<<r.y<<"), Width="<<r.width<<"Height="<<r.height;
return os;
}

std::string PixelFormatNumberToName(int format) {
    std::string os;
    //Enum is found in raylib.h.  This merely "reverses" it.
    switch (format) {

    case (PIXELFORMAT_UNCOMPRESSED_GRAYSCALE): { os="PIXELFORMAT_UNCOMPRESSED_GRAYSCALE, 8 bit per pixel (no alpha)"; break; }
    case (PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA): { os="PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA, 8*2 bpp (2 channels)"; break; }
    case (PIXELFORMAT_UNCOMPRESSED_R5G6B5): { os="PIXELFORMAT_UNCOMPRESSED_R5G6B5, 16 bpp"; break; }
    case (PIXELFORMAT_UNCOMPRESSED_R8G8B8): { os="PIXELFORMAT_UNCOMPRESSED_R8G8B8, 24 bpp"; break; }
    case (PIXELFORMAT_UNCOMPRESSED_R5G5B5A1): {  os="PIXELFORMAT_UNCOMPRESSED_R5G5B5A1, 16 bpp (1 bit alpha)"; break; }
    case (PIXELFORMAT_UNCOMPRESSED_R4G4B4A4): {  os="PIXELFORMAT_UNCOMPRESSED_R4G4B4A4, 16 bpp (4 bit alpha)"; break; }
    case (PIXELFORMAT_UNCOMPRESSED_R8G8B8A8): { os="PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 32 bpp"; break; }
    case (PIXELFORMAT_UNCOMPRESSED_R32): { os="PIXELFORMAT_UNCOMPRESSED_R32, 32 bpp (1 channel - float)"; break; }
    case (PIXELFORMAT_UNCOMPRESSED_R32G32B32): { os="PIXELFORMAT_UNCOMPRESSED_R32G32B32, 32*3 bpp (3 channels - float)"; break; }
    case (PIXELFORMAT_UNCOMPRESSED_R32G32B32A32): { os="PIXELFORMAT_UNCOMPRESSED_R32G32B32A32, 32*4 bpp (4 channels - float)"; break; }
    case (PIXELFORMAT_COMPRESSED_DXT1_RGB): { os="PIXELFORMAT_COMPRESSED_DXT1_RGB, 4 bpp (no alpha)"; break; };
    case (PIXELFORMAT_COMPRESSED_DXT1_RGBA): { os="PIXELFORMAT_COMPRESSED_DXT1_RGBA, 4 bpp (1 bit alpha)"; break; }
    case (PIXELFORMAT_COMPRESSED_DXT3_RGBA): { os="PIXELFORMAT_COMPRESSED_DXT3_RGBA, 8 bpp"; break; }
    case (PIXELFORMAT_COMPRESSED_DXT5_RGBA): { os="PIXELFORMAT_COMPRESSED_DXT5_RGBA, 8 bpp"; break; }
    case (PIXELFORMAT_COMPRESSED_ETC1_RGB): { os="PIXELFORMAT_COMPRESSED_ETC1_RGB, 4 bpp"; break; }
    case (PIXELFORMAT_COMPRESSED_ETC2_RGB): { os="PIXELFORMAT_COMPRESSED_ETC2_RGB, 4 bpp"; break; }
    case (PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA): { os="PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA, 8 bpp"; break; }
    case (PIXELFORMAT_COMPRESSED_PVRT_RGB): { os="PIXELFORMAT_COMPRESSED_PVRT_RGB, 4 bpp"; break; }
    case (PIXELFORMAT_COMPRESSED_PVRT_RGBA): { os="PIXELFORMAT_COMPRESSED_PVRT_RGBA, 4 bpp"; break; }
    case (PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA): { os="PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA, 8 bpp"; break; }
    case (PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA): { os="PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA, 2 bpp"; break; }
    default: { os="Unrecognized PixelFormat number"; }
    }

return os;
}


std::ostream& operator<<(std::ostream& os, Image i) {
    os<<"Image width="<<i.width<<" Height="<<i.height<<" Mipmap levels="<<i.mipmaps<<" PixelFormat number:"<<i.format<<" type: "<<PixelFormatNumberToName(i.format)<<" ";
return os;
}

std::ostream& operator<<(std::ostream& os, Texture t) {
    os<<"Texture ID#: "<<t.id<<" Width="<<t.width<<" Height="<<t.height<<" Mipmap levels="<<t.mipmaps<<" PixelFormat number:"<<t.format<<" type: "<<PixelFormatNumberToName(t.format)<<" ";
return os;
}

std::ostream& operator<<(std::ostream& os, Camera2D c) {
    os<<"** 2D Camera info. **\nOffset: "<<c.offset<<" Target: "<<c.target<<" Rotation: "<<c.rotation<<" Zoom="<<c.zoom;
    Matrix m=GetCameraMatrix2D(c);
    os<<"\nCamera matrix\n"<<m<<"\n";
return os;
}

//Definition of Camera3D in raylib.h states that fovy is field-of-view aperture in perspective mode, but near plane width in orthographic mode
std::ostream& operator<<(std::ostream& os, Camera3D c) {
    os<<"*** 3D Camera info. ***\nPosition: "<<c.position<<" Target: "<<c.target<<" Up vector: "<<c.up<<"\n";
    if (c.projection==CAMERA_PERSPECTIVE) {
        os<<"Projection mode: perspective.  FOV="<<c.fovy<<" degrees\n";
    }
    if (c.projection==CAMERA_ORTHOGRAPHIC) {
        os<<"Projection mode: orthographic. Near plane width="<<c.fovy<<"\n";
    }
    Matrix m=GetCameraMatrix(c);
    os<<"Camera matrix:\n"<<m<<"\n";
return os;
}

std::ostream& operator<<(std::ostream&os, Ray r){
    os<<"Ray position: "<<r.position<<" Ray direction: "<<r.direction;
return os;
}

std::ostream& operator<<(std::ostream&os, const RayHitInfo& rhi){
    if (rhi.hit) {
        os<<"Ray hit. Distance="<<rhi.distance<<" Position: "<<rhi.position<<" Surface normal: "<<rhi.normal;
    }
    else {
        os<<"Ray missed.";
    }
return os;
}

std::ostream& operator<<(std::ostream&os, const BoundingBox& bb){
    os<<"Bounding box coordinates.  Min: "<<bb.min<<" Max: "<<bb.max;
return os;
}

std::ostream& operator<<(std::ostream&os, const NPatchInfo& np){
    os<<"NPatch info:  Rectangle: "<<np.source<<" Border offsets: Left: "<<np.left<<" Right: "<<np.right<<" Top: "<<np.top<<" Bottom: "<<np.bottom<<" Layout: "<<np.layout;
return os;
}

std::ostream& operator<<(std::ostream&os, const CharInfo& ci){
    os<<"Char info:  Char value: "<<ci.value<<" Offset X: "<<ci.offsetX<<" Offset Y: "<<ci.offsetY<<" Advance position X: "<<ci.advanceX;
return os;
}

std::ostream& operator<<(std::ostream&os, const Font& f){
    os<<"Font info:  Base size (default char height): "<<f.baseSize<<" Number of characters: "<<f.charsCount<<" Padding around chars: "<<f.charsPadding;
return os;
}

#endif // RAYLIB-OP-OVERLOADS_HPP_INCLUDED
