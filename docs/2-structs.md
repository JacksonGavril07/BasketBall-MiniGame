# Part 2 - Structs

This part of the assignment introduces structs. You need to understand how they work to complete the assignment.

👉 You don't have to write any code for this part of the assignment, but make sure you understand how structs work before proceeding to the next part.

## Variables Review

You should already be familiar with variables. For example, here is an integer variable using the `int` data type:

```cpp
int numPoints;
```

Here is a floating-point variable using the `float` data type:

```cpp
float ballPosX;
```

Each variable is allocated a certain amount of memory to store its value in.

## Structs

We can create our own custom data types using structs.

Here is an example of a struct in C++ that is named `Vector2`.

```cpp
struct Vector2
{
    float x;
    float y;
};
```

A struct acts like a blueprint. The struct definition itself does not create any variables. It is a blueprint for variables that will be created in the future.

To use this blueprint, a new variable is created using the name of the struct as the data type. For example:

```cpp
Vector2 ballPos;
```

This code creates a new variable named `ballPos`. The data type is `Vector2`. We call `ballPos` an _instance_ of the `Vector2` struct.

When the `ballPos` variable is created, it acts like a container for all the variables defined in the `struct` blueprint. Since we used the `Vector2` data type, the `ballPos` variable will contain its own set of `x` and `y` variables.

The variables within a struct variable are called _member variables_. A member variable can be accessed by using the struct variable name, followed by a period, then the name of the member variable. For example:

```cpp
Vector2 ballPos;

ballPos.x = 10.0f;
ballPos.y = 15.0f;
```

This code creates a variable named `ballPos`. It then sets the `x` member for `ballPos` to `10.0f` and the `y` member for `ballPos` to `15.0f`.

## Passing Structs

Struct variables can be passed as function parameters just like any other variable. This is common in raylib.

For example, the `DrawTextureEx` function draws a texture at a position using a `Vector2` variable.

```cpp
Texture2D ballTexture;
Vector2 ballPos;

// ...

DrawTextureEx(ballTexture, ballPos, 0, 1, WHITE);
```

## End of Part 2

You should understand the basics of structs in C++.

raylib provides a `Vector2` data type that will be used in multiple places throughout this assignment. This is a struct with two members: `x` and `y`.

When ready, proceed to [part 3](./3-drawing.md).
