# Instructions to compile GT.M on Cygwin
These are quick instructions to first install Cygwin x86 and then compile GT.M on it. It will take a while as compiling on Cygwin/gcc is really slow.

Tested on Windows 10.

Open cmd as admin, and install chocolatey, and then install Cygwin x86. 

```
@powershell -NoProfile -ExecutionPolicy Bypass -Command "iex ((new-object net.webclient).DownloadString('https://chocolatey.org/install.ps1'))" && SET PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin
choco install cygwin -x86
```

You now need to open cygwin, in its default location under `c:\tools\cygwin\` and execute the bat file. Once in, install apt-cyg and use that to install most software.

```
lynx -source rawgit.com/transcode-open/apt-cyg/master/apt-cyg > apt-cyg
install apt-cyg /bin
hash -r
```

Then install lots of stuff. But NOT!! cmake. The version in the repos is corrupt. We will compile cmake from source.
```
apt-cyg install wget git libelf0-devel zlib-devel libicu-devel libgpgme-devel libgpg-error-devel libgrcypt-devel openssl-devel tcsh libncurses-devel gcc4-g++ gdb automake make flex bison
hash -r
```

Install both libconfig and cmake from source:
```
git clone https://github.com/hyperrealm/libconfig && cd libconfig
./configure
make
make install
cd
wget --no-check-certificate https://cmake.org/files/v3.4/cmake-3.4.0.tar.gz
tar xzvf cmake-3.4.0.tar.gz
cd cmake-3.4.0
./bootstrap && make && make install
```

Now, compile GT.M:
```
git clone https://github.com/shabiel/fis-gtm && cd fis-gtm
git checkout cygwin
cmake . (add debug options here or use ccmake)
make
make install
```
