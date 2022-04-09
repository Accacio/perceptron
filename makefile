##
# perCeptron
#
# @file
# @version 0.1

all: debug

debug: debug-compile
release: compile

compile:
	@ gcc main.c -o perceptron

debug-compile:
	@ gcc main.c -Wall -g -o perceptron -pg --coverage

run:
	@./perceptron tests/data.csv
# end
