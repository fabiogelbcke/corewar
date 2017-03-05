.name "my name"
.comment "carailhou

"
l2:
	sti r1,%:live,%1 ;no problem
	and r1,%0,r1

live:
	live %1
	zjmp %:live
