# Part 4 - State

In this part of the assignment you will implement code to handle different game states.

## Game State

Objects in a game can have different states. For example, a player may be in a `walking` state, a `running` state, a `flying` state, or a `dead` state. There is usually different code to execute during a frame update depending on the object's state.

For this assignment there are only two possible states to consider: "flying" or "not flying". The game will behave differently depending on whether the ball is in the "flying" state.

👉 To track the state of the ball, use a `bool` variable. Add this global variable to your `main.cpp` file. Here is an example:

```cpp
bool isFlying = false;
```

Find the `UpdateFrame()` function in `main.cpp`. It is currently empty.

👉 Add a branch to handle different paths depending on if `isFlying` is `true` or `false`. Here is an example:

```cpp
void UpdateFrame()
{
    if (isFlying) {
        // Ball has been shot and is in flight

        // TODO
    }
    else {
        // Ball is waiting to be shot

        // TODO
    }
}
```

Compile your code and make sure there are no compiler errors. Then proceed to the next part of the assignment.

**▶️ Compile the program.** Verify there are no errors.

## End of Part 4

When ready, proceed to [part 5](./5-shooting.md).
