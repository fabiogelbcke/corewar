l2:
		sti r1, %:live, %1
		ld %65, r2
		and r1, %0, r1
		fork %:willidie

live:
		live %1
		zjmp %:live

willidie:
		aff r2
		zjmp %:willidie
