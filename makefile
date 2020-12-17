##
# perCeptron
#
# @file
# @version 0.1

all: debug run

debug: debug-compile
release: compile

compile:
	@ gcc main.c -o perceptron

debug-compile:
	@ gcc main.c -g -o perceptron

run:
	@./perceptron
# end
