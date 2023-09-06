##
# Project Title
#
# @file
# @version 0.1

main: main.c
	cc main.c -Wall -lSDL2 -lSDL2_ttf -o base

load: load_measurements.c
	cc load_measurements.c -Wall -lm -o load

# end
