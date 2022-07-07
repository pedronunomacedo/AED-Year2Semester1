cd codigo
make clean
cd ..
rm -rf documentacao/
doxygen Doxyfile
cd apresentacao
pdflatex apresentacao.tex
pdflatex apresentacao.tex
rm -f apresentacao.synctex.gz
rm -f apresentacao.aux
rm -f apresentacao.log
rm -f apresentacao.nav
rm -f apresentacao.out
rm -f apresentacao.snm
rm -f apresentacao.toc
rm -f apresentacao.vrb
cd ..
rm -f AEDA1920Parte2_Turma5_G3.zip
zip -r AEDA1920Parte2_Turma5_G3.zip codigo/ documentacao/ README.md
cd apresentacao/
zip -r ../AEDA1920Parte2_Turma5_G3.zip apresentacao.pdf
