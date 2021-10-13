
all: manual_persian manual_english api_persian

manual_persian: FORCE
	xelatex manual_fa.tex
	xelatex manual_fa.tex
	rm manual_fa.aux manual_fa.toc manual_fa.out manual_fa.log

manual_english: FORCE
	xelatex manual.tex
	xelatex manual.tex
	rm manual.aux manual.out manual.log

api_persian: FORCE
	xelatex apimanual_fa.tex
	xelatex apimanual_fa.tex
	rm apimanual_fa.aux apimanual_fa.out apimanual_fa.log apimanual_fa.toc
	rm apimanual_fa.idx apimanual_fa.ilg apimanual_fa.ind 

FORCE:
