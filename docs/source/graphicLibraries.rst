Graphic Libraries
=================

Introduction
----------------

WLA is case sensitive, except with directives, so be careful.


Comments
--------

Comments begin with ``;`` or ``*`` and end along with the line. ``;`` can be
used anywhere, but ``*`` can be placed only at the beginning of a new line.

WLA supports also ANSI C style commenting. This means you can start a
multiline comment with ``/*`` and end it with ``*/``.

What also is supported are C++ style comments. This means you can start a
comment with ``//``.

You can also use ``.ASM`` and ``.ENDASM`` directives to skip characters. These
function much like ANSI C comments, but unlike the ANSI C comments these can be
nested.


Line splitting
--------------

Lines can be split using a ``\`` between elements. So instead of writing

    .db 1, 2, 3, 4, 5, 6, 7, 8

it's possible to write

    .db 1, 2, 3, 4 \
        5, 6, 7, 8

Note that line splitting works only in places where WLA expects a new label,
number, calculation, etc. String splitting isn't currently supported.