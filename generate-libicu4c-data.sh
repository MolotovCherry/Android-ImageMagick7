LIBDIR=libicu4c-64-2

CPPFLAGS="-DUCONFIG_ONLY_COLLATION=1 -DUCONFIG_NO_LEGACY_CONVERSION=1"

cd $LIBDIR
./configure --with-data-packaging=archive
make
mkdir -p ../src/main/assets/usr/icu
f=libicu4c-64-2/stubdata/icudt*.dat
echo Copied ${f} to ../src/main/assets/usr/icu
cp libicu4c-64-2/stubdata/icudt*.dat ../src/main/assets/usr/icu
