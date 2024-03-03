Master:
	zig c++ ./main.cpp -o ./build/build.exe -I ./include/ ./lib/cyber.lib -Wreturn-stack-address

run:
	build/build.exe
