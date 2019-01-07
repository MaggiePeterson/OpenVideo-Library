cwd=$(pwd)

sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

sudo apt-get install libusb
git clone https://github.com/ktossell/libuvc.git
cd libuvc
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install

cd ..
cd ..
sudo apt-get install opencv3

git clone https://github.com/MaggiePeterson/OpenVideo-Library.git

echo "Installation finished. <₍⸍⸌̣ʷ̣̫⸍̣⸌₎/ "
