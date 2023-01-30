# GEngine

this is my attemt to create a game engine in c++

more readme coming soon (probably i'll be the only person using this engine)

licensed under This work is licensed under a Creative Commons Attribution-NonCommercial 4.0 International License.

Part 1: datatypes
```c++
RGBA{
    float r,g,b,a;
};
```
you can probably guess what the RGBA datatype is for

```c++
G_bmp{
    float xpos,ypos, width,height;
    vector<vector<RGBA>> pixels;
};
```
this data structure is a little bit trickier, because it stores a scalable bitmap. note that when the pixel value is RGBA(0,0,0,0), then it is invisible (not rendered)
xpos and ypos represent the top left corner of the bitmap, and width and height represent the width and height of the bitmap

```c++
G_text{
    float xpos,ypos;
    string text
    RGBA color;
    void* font;
};
```
this structure is even trickier, because of the `void* font`. actually for some unknown reason GLUT fonts
are stored as a void pointer, so i have to use that. the other variables are pretty self explanatory.
xpos and ypos represent the top left corner of the text

```c++
G_triangle{
    float x1,y1,x2,y2,x3,y3;
    RGBA color;
};
```
pretty basic struct, keeps triangle vertices and color

```c++
G_Button{
    G_bmp bmp;
    void (*callback)();
};
```
this is a button, just to make creating menus easier. the callback function is called when the button is clicked

```c++
g_quad{
    float x1,y1,x2,y2,x3,y3,x4,y4;
    RGBA color;
};
```
just keeps the vertices of a rectangle

```c++
G_line{
    float x1,y1,x2,y2;
    RGBA color;
};
```
keeps x and y coordinates of two points, and the color of the line


```c++
glist{
    vector<G_bmp> bmps;
    vector<G_text> texts;
    vector<G_triangle> triangles;
    vector<G_quad> quads;
    vector<G_Button> buttons;
};
```
this is the main storage, it stores all the objects that are rendered on the screen. it is a vector of all the objects, so you can add and remove objects from the screen ever tick.
it supports ```c++ glist.add() ```for every data type represented

#Part 2: functions

```c++
onMouse(int button, int state, int x, int y)
```
this is a funtion tha handles mouse movements. it is called whenever mouse is clicked or enters the screen (after modding the lib you can technically run it in a window, but it is not advised)

```c++
onKeyboard(unsigned char key, int x, int y)
```
this function handles keyboard input. it is called whenever a key is pressed.

```c++
onKeyboardUp(unsigned char key, int x, int y)
```
the opposite of onKeyboard, it is called when a key is released

```c++
onPassiveMouse(int x, int y)
```
this function is called when the mouse is moved, but not clicked

```c++
onSpecial(int key, int x, int y)
```
if you want to handle special keys (like arrow keys) you can use this function

reference (here)[https://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard/]

```c++
onSpecialUp(int key, int x, int y)
```
guess what it is

# Part 3: main file structure

the main file, called Game.cpp must include the `Game.h` header file.

every game tick (`gutils.cpp -> designated_Tps`) function `tick()` is called.
after it finishes, the rendering module is called and the screen is updated.

by default ticks happen once a second, but you can easily change that int the file gutils.cpp, or just by overriding the variable 
`designated_Tps` in your Game.cpp file.

# Part 4 : coordinate system

this game engine is equipped with a rather simple coordinate system. basically it ranges from (-1000,-1000),
which is the bottom left corner, to (1000,1000) = top right;


there is however a thing that i have not explained yet. it is the `SCREEN_PROP_CONST` constant.
you can think about it as a converter. basically when a window is created, it is not square, but 16:9 (usually)

because of that, if you wanted to draw a square x = ((0,0),(0,1),(1,1),(1,0)), it would instead
be drawn as a rectangle, because the length of one "coordinate" vertically and horizontally is different.

to circumvent this issue, i created a constant, which is equal to a casual screen ratio (16:9) inversed.

if you want to draw a shape that you can do math on, you can use this constant to make it work.

`SCREEN_PROP_CONST = 0.5625` = 9/16

i think this needs a bit more explanation, so i will make a table.


| -    | x=1  | x=2   | x=3   | x=4   | x=5  | x=6   | x=7   |
|------|------|-------|-------|-------|------|-------|-------|
| y=1  |      |       |       |       |      |       |       |
| y=2  |      |       |       |       |      |       |       |
| y=3  |      |       |       |       |      |       |       |
| y=4  |      |       |       |       |      |       |       |
| y=5  |      |       |       |       |      |       |       |

if you draw a rectangle from (2, 3) to (4,6), you can see that our 3x3 rectangle is not square, because the pixels are not square.
how do we fix this? let's try on a real-world example. if your screen is 1920x1080, the ratio is 16:9. this also means that a openGL "square" is also 16:9

if we want to convert it back, we have to divide its lenght by 16 and multiply by 9. this will give us a pixel with a ratio of 9:9 = 1:1 (square)

so, if you want a stretched figure, divide your `x` by `SCREEN_PROP_CONST` (the library has the exact reverse process inside)

there is one more thing to this. whenever you divide, it also causes the `x = 1000` coord to not be the exact end of screen.
you can do it yourself, but from what I calculated, the maximum `x` after division is `562.5` (and minium `-562.5`)


if you have any questions, dm me on discord


# Part 5: how to use - examples - coming soon

```c++
//
// Created by jj15 on 1/29/23.
//

#include "Game.h"

using namespace std;

```

we will now go through the code step by step

```c++
#include "Game.h"
```

this server 3 purposes.

* first, it the header contains other includes, to internal library parts, so you don't have to include them yourself.
* second, it contains the declaration of the `gobjs` variable, which is the main storage of the library.
* third, it overrides the required functions, which causes them to be called when an event (like a mouse click) happens

```c++
using namespace std;
```
don't worry about this, it is just to make the code shorter

```c++
void tick(){ 
```
your main function is declared right here. it is called every tick, and it is where you should put all your code.
remember that the functions type has to be `void`, and it has to have no parameters.

```c++
    G_bmp test = G_bmp(-1000/SCREEN_PROP_CONST, 900, 2000/SCREEN_PROP_CONST, 60, vector<vector<RGBA>>());
```
here we define a variable called `test`, and is the type `G_bmp`.

we can go through the parameters one by one.
```
xpos = -1000/SCREEN_PROP_CONST
ypos = 900

width = 2000/SCREEN_PROP_CONST
height = 60

pixels = empty vector
```
