ass2 a2empty.pls > a2empty.out
ass2 ass2r.pls > ass2r.out
ass2 ass2w.pls > ass2w.out
ass2 a2error.pls > a2error.out

diff a2empty.out outputs/a2empty.out
diff ass2r.out outputs/ass2r.out
diff ass2w.out outputs/ass2w.out
diff a2error.out outputs/a2error.out

pause
