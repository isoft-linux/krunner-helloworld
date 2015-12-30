# krunner-helloworld

KRunner Helloworld plugin.

## Build

```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr \
    -DLIB_INSTALL_DIR=lib \
    -DLIBEXEC_INSTALL_DIR=lib \
    -DKDE_INSTALL_USE_QT_SYS_PATHS=ON   \
    -DENABLE_DEBUG=ON
make -j 5
```
