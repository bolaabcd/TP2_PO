build: tp2.out
	g++ tp2.cpp -O3 -std=c++17 -o tp2.out
dbg: tp2.cpp checker.cpp gen.cpp
	g++ tp2.cpp -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts -o tp2.out
	g++ checker.cpp -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts -o checker.out
	g++ gen.cpp -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts -o tp2.out
	
test: tp2.out gen.out checker.out

tp2.out: tp2.cpp
	g++ tp2.cpp -O3 -std=c++17 -o tp2.out
gen.out: gen.cpp
	g++ gen.cpp -O3 -std=c++17 -o gen.out
checker.out: checker.cpp
	g++ checker.cpp -O3 -std=c++17 -o checker.out
