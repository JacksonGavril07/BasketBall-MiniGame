# Part 9 - Timer

This is the final part of the assignment. You will implement a game timer.

## Timer

👉 Implement a timer in the game. The timer should count down from 30 to 0. When the timer hits 0:

- the game should stop updating.
- a message should appear on the screen telling the player the game is over.

The implementation (and any other behavior) is up to you.

Tip: The example below demonstrates how to stop the program from updating after the timer expires:

```cpp
void UpdateFrame()
{
    // Stop updating after timer expires
    if (timer <= 0) {
        return;
    }

    // Existing code
}
```

**▶️ Build and run.** Verify the game timer appears and works as expected.

## End of Part 9

Congratulations on finishing the assignment!

Make sure to commit and push your changes back to GitHub.
