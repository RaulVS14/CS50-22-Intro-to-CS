style:
	style50 $(args).c

check:
	check50 cs50/problems/2022/x/$(args)

submit:
	submit50 cs50/problems/2022/x/$(args)

compile:
	make ${args}

run:
	gcc ${args}.c -o ${args} -lcs50 && ./${args}

runs:
	./${args}