build:
	g++ tp2.cpp -O2 -std=c++17 -o tp2.out
dbg: tp2.out

tp2.out: tp2.cpp
	g++ tp2.cpp -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts -o tp2.out
