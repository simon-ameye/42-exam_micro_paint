gcc -Wall -Wextra -Werror my_micro_paint.c -o my.out
gcc -Wall -Wextra -Werror glagan_micro_paint.c -o ref.out

function test()
{
    echo test $@
    ./my.out examples_rectangles/$@ > my
    echo $? >> my
    ./ref.out examples_rectangles/$@ > ref
    echo $? >> ref
    diff my ref
}

test 1
test 2
test 3
test 4
test 5
test 6

test err1
test err2
test err3
test err4
test err6
test err7
test notexisting