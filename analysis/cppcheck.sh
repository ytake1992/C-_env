cd ../

cppcheck --enable=all --language=c++ --xml  -I ./src/include  src > analysis/cppcheck.xml

# cppcheck --enable=all --std=c++03 --xml src > analysis/cppcheck.xml