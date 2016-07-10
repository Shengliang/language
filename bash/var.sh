#!/bin/bash
# Local variables can be created by using the keyword local.
# Remember to use local to avoid any side effects on global vars.

var=Hello 
function bar {
        echo in bar: var=$var
        local var=World
        echo in bar: var=$var
}
function foo {
        echo in foo: var=$var
        var=World
        echo in foo: var=$var
}
echo main: var=$var
bar
echo main: var=$var
foo
echo main: var=$var

A=abcABC123ABCabc
e4357@e4357-Latitude-E6230:~/language/bash$ echo ${A:6:3}
