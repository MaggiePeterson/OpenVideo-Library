cwd=$(pwd)

/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
Brew install cmake
Brew install pkgconfig

brew install libusb
git clone https://github.com/ktossell/libuvc.git
cd libuvc
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install

cd..
cd..
brew tap homebrew/science
brew install opencv3

git clone https://github.com/MaggiePeterson/OpenVideo-Library.git
