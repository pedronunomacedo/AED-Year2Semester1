RM=rm -f
RMDIR=rm -rf
LATEX=latexmk -synctex=1 -interaction=nonstopmode -pdf

DDIR=./documentacao
DOC_INDEX= $(DDIR)/index.html

OUTFILES=apresentacao/AEDA_proj_pres1.pdf \
		 apresentacao/AEDA_proj_pres2.pdf

all: $(DOC_INDEX) $(OUTFILES)

%.pdf: %.tex $(DOC_INDEX)
	cd $(<D) && $(LATEX) $(<F)

$(DOC_INDEX):
	doxygen

clean:
	$(RMDIR) $(DDIR)
	$(RM) $(OUTFILES)
