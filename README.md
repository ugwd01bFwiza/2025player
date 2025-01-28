# fwwb

# Dependence

```
git clone https://github.com/taglib/taglib.git
cd taglib
cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release -DWITH_ZLIB=OFF .
make
sudo make install
PKG_CONFIG_PATH=$HOME/pkg/lib/pkgconfig pkg-config --libs --cflags taglib
-I/usr/local/include -I/usr/local/include/taglib -L/usr/local/lib -ltag -lz
```