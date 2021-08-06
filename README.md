# cgol-c

Conway's Game of Life, for the terminal, written in C

---------

This is a near direct translation of [my other implementation in Go](https://github.com/zsarge/cgol-go).

I wrote this to see if switching to a non-gc'd language would make a significant performance impact.

Using the same logic in both programs, both Go and C have roughly equivalent performance on my system.

I have not taken many steps towards optimization. If you are interested in optimizing Conway's Game of Life, I recommend looking into [HashLife](https://en.wikipedia.org/wiki/Hashlife) or [this StackOverflow thread](https://stackoverflow.com/questions/40485/optimizing-conways-game-of-life).

---------

`gcc main.c -o a.out && ./a.out` = 

```

+--------------------------------------------------------------------------------+
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|     X                                                                          |
|      X                                                                         |
|    XXX                                                                         |
|                                                                                |
|                                                                                |
+--------------------------------------------------------------------------------+


```

... and so on

