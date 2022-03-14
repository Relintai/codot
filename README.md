# Codot Engine

This is a VERY experimental project to port the godot engine to C, mostly to satisfy my curiosity.

Yes, this is probably a very bad and dumb idea. However:

1. I want to learn C.
2. I noticed a while ago that it would not be too difficult to convert simple / clean / [orthodox](https://gist.github.com/bkaradzic/2e39896bc7d8c34e042b) c++ code to c, (except for virtuals / inheritance it's mostly simple text editing - and even that system is mostly only a one time setup -) and godot's source base is super good in this regard. Also godot is only using single inheritance, which makes things a lot easier. Also a possible solution: https://www.cs.rit.edu/%7Eats/books/ooc.pdf .
3. There is also this gem of a paper https://greenlab.di.uminho.pt/wp-content/uploads/2017/10/sleFinal.pdf . Where they compare the energy efficiency of a bunch of languages. However what caught my attention is the run speed performace: C 1.00, C++: 1.56. Yes I know that what they tested is a bit different than a game, where you have virtuals, and constant cache misses due to the program execution going all over the place, however if even half of that can be achieved, it's probably worth the time and effort.
4. It might make compile times faster.
 
Based on my fork of godot (https://github.com/Relintai/godot) Commit: c4864a0e5f73a375259503ea1485794a6aad6df7
