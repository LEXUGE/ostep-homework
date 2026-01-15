# Q1
```
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c EXITS
                               a
                               └── b
Action: a forks d
                               a
                               ├── b
                               └── d
Action: a forks e
                               a
                               ├── b
                               ├── d
                               └── e
```

Pretty straightforward.

An interesting difference:
```
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c EXITS
                               a
                               ├── b
                               └── d
```

We see after `c` exits `d` doesn't terminate because they are really different processes, although they have some information on their parent.

Extra subtleties here as we see that the hierarchy information between `c` and `d` is lost after `d` terminates.
```
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: b EXITS
                               a
                               ├── c
                               └── d

```

> [!CAUTION]
> Actually the above info might be wrong (according to GPT), let's maybe write a simple program to test this behavior out.

So basically in the above example, `a` should be treated as `init`, then the behavior is correct.


# Q4
This is basically what I talked about above. With `-R` (local reparent) we get the following result
```
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: b EXITS
                               a
                               └── c
                                   └── d
```

# Q6
Most of the cases you won't be able to tell:
```
                        Final Process Tree:
                               a
                               ├── b
                               ├── e
                               └── d

```
It could be
```
Action: a forks b
Action: a forks c
Action: a forks d
Action: a forks e
Action: c EXITS
```
Or due to orphan reparenting
```
Action: a forks b
Action: a forks c
Action: c forks d
Action: a forks e
Action: c EXITS
```
