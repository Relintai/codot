# Codot Engine

This is a VERY experimental project to port the godot engine to C, mostly to satisfy my curiosity.

Yes, this is probably a very bad and dumb idea. However:

1. I want to learn C.
2. I noticed a while ago that it would not be too difficult to convert simple / clean / [orthodox](https://gist.github.com/bkaradzic/2e39896bc7d8c34e042b) c++ code to c, (except for virtuals / inheritance it's mostly simple text editing - and even that system is mostly only a one time setup -) and godot's source base is super good in this regard. Also godot is only using single inheritance, which makes things a lot easier. Also a possible solution: https://www.cs.rit.edu/%7Eats/books/ooc.pdf .
3. There is also this paper https://greenlab.di.uminho.pt/wp-content/uploads/2017/10/sleFinal.pdf . Where they compare the energy efficiency of a bunch of languages. However what caught my attention is the run speed performace: C 1.00, C++: 1.56. Yes I know that what they tested is a bit different than a game, where you have virtuals, and constant cache misses due to the program execution going all over the place, however if even half of that can be achieved, it's might worth the time and effort.
4. It might make compile times faster.
 
Based on my fork of godot (https://github.com/Relintai/godot) Commit: c4864a0e5f73a375259503ea1485794a6aad6df7

Some remarks:

After messing around for a bit, doing this by hand will take a lot longer that I first thought.

Still need prototype implementations for: OOP, inheritance, virtuals, References, Nodes, binding api.
I expect references (Ref<> s) to be a bit more annoying, as there are no destructors in C.

I think transpiling the code would be a better idea, and writing some tools to maybe clean up the resulting code.\
(Or writing a project specific transpiler - Maybe something could be bodged together even with clangd and clang-complete.-).

Some references:
https://stackoverflow.com/questions/5050349/is-there-a-way-to-compile-c-to-c-code

Maybe even writing a new not-bodged together transpiler that tries to produce human readable code would be good.\
It does not have to be that good, to produce good enough results, that is easy to clean up by hand later.\
It needs to handle inheritance (single should be enugh), templates (template->macro, + instatiation), and virtuals.\
And most importantly destructors, and operator overloading needs to be handled properly.
(maybe could use clang complete to get the exact operator that gets called).

More notes:

If the ClassDB is extended to handle engine side virtuals, then there is no need to implement them in C.

I think the simplest way might be to:

0. make engine side virtuals implemented in classdb.
1. Make a tool that creates global functions for every class methods, copy paste class method content to that, and amke the class methods call the global one.

like:

Class Vector2 {
    void normalize() {
        vector2_normalize(this);
    }
}

vector2_normalize(Vector2 self) {
    //normalize;
}

2. then change the binding api to only take the global methods, and not the instance methods.
3. Then the class methods can be removed. (except for operators.)
4. somehow unroll the operators into new global methods.

Vector2 a, b;
a = a + a + b * a;
-> turn these into normal method calls;

5. Get rid of references in mthod arguments, turn them into pointers. (Or rather move the & symbols to where a method is called.)
6. Turn templates into macros. They also need to become c-like.
7. Turn destructors and constructors into globals aswell.
8. Get rid of contructors.
9. Get rid of destructors, but somehow calls need to be inserted everyewhere where c++ just calls them.
10. Set up c struct "inheritance". If classdb handles engine side virtuals this should be almost trivial to do using the GDCLSSS macro. Also casting will only need to be implemented in Object::cast_to, and Ref<>.
11. Switch to an actual c compiler.
12. Could actually do this with some of the modules. For example Bullet. Also MAkeing an alternative physics engine from bullet that is simplified, might not be a bad idea.
12. ????
13. Profit?

Most of these (the transformations) might be doable with clang complete and maybe with simple vscode extensions.

Also they wouldn't even take that much time to do.

Now the only question that reamins is that would this worth it.

Pros:
- Code completion for C is a lot simpler. (And a LOT less resource intensive.)
- Syntax highlighting for c is a lot simpler. More tools can do it well.
- Lower level. You can optimize the code more, because it's easier to notice inefficiencies when working closer to metal. (Like unecessary type conversions.)
- I'll get to know godot internals even better. Like 2d rendering.
- Less bloat: I'll probably remove things that I personally don't use. Like GLES3, Lightmapping (shadows would stay), VisualScipt, GDNative, more arcane asset loaders, probably assimp (stuff can be imported in vanilla godot and transferred. Maybe I could have a custom tool for it), etc.
- Less bloat: Compile times should decrease dramatically.
- I'll probably remove things that I personally don't use. Others might needs those. Less interest from others. -> I can just hack whatever I want. Like I can have simplified physics engines that only do collision detection and kinematic body moves, no dynamic physics objects, also can experiment with software rendering (really good to have for tools) etc.
- I get to know C to probably it's fullest.

Cons:
- The engine has to be converted to C.
- More verbose / Lower level. Needs more manual work.
- C++ is more accepted in gamedev -> more c++ devs. Also people will probably look for c++ engines first, because that's the current way of thinking.
- Breaking compat with godot means no more updates.
- I'll probably remove things that I personally don't use. Others might needs those. Less interest from others.

Neutral:
- Will likely never have RenderingDevice and Vulkan, and multiple window support. However based on what is going on in the world right now, vulkan is probably not worth having for quite a while. Only high end phones can use it righ now, and I don't expect adoption to increase anytime soon. In fact I think we might actually see adoption go down, as people will just go back to using their older devices if the new ones break (because of both price, and stupid - kind of orwellian - decisions on the behalf of the manufacturers.). (Also on the desktop we have gpu shortages, and higer prices (even laptops) etc). Also I kind of like to mess with vertex color a lot more, so I don't really need to many advanced features anyway.

Questions:
- Performance? - Expectation: better
- Compile performance? - Expectation: better
- Would it worth the work?
