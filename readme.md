How to install the ncurses (Mac):
```
curl -O ftp://ftp.gnu.org/gnu/ncurses/ncurses-5.9.tar.gz
tar -xzvf ncurses-5.9.tar.gz
cd ./ncurses-5.9
./configure --prefix=/usr/local \
  --without-cxx --without-cxx-binding --without-ada --without-progs --without-curses-h \
  --with-shared --without-debug \
  --enable-widec --enable-const --enable-ext-colors --enable-sigwinch --enable-wgetch-events \
&& make
sudo make install
```

How to install the ncurses (For Windows using cygwin):
```
open cygwin
select package: ncurses
press to install all the libs for ncurses
press next and install
```

To build the program:
```
cd <yourprojectdirectory>
g++ -std=c++11 -Wall -lncurses main.cpp -o snake
```

To run the program (Mac/Linux):
```
./snake
```