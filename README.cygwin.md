# Instructions to compile GT.M on Cygwin
These are quick instructions to first install Cygwin x86 and then compile GT.M on it. It will take a while as compiling on Cygwin/gcc is really slow.

Tested most recently on Cygwin 2.5 x86 / Windows 10 Beta Build 14342.

# Install Instructions
Open cmd as admin, and install chocolatey, and then install Cygwin x86. 

```
@powershell -NoProfile -ExecutionPolicy Bypass -Command "iex ((new-object net.webclient).DownloadString('https://chocolatey.org/install.ps1'))" && SET PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin
choco install cygwin -x86
```

You now need to open cygwin, in its default location under the START>All Programs>Cygwin>Cygwin Terminal. Once in, install apt-cyg and use that to install most software.

```
lynx -source rawgit.com/transcode-open/apt-cyg/master/apt-cyg > apt-cyg
install apt-cyg /bin
```
if you a message such as
```
Looking up rawgit.com
Making HTTP connection to rawgit.com
Sending HTTP request.
HTTP request sent; waiting for response.
HTTP/1.1 301 Moved Permanently
Data transfer complete
HTTP/1.1 301 Moved Permanently
Using https://raw.githubusercontent.com/transcode-open/apt-cyg/master/apt-cyg
Looking up raw.githubusercontent.com
Making HTTPS connection to raw.githubusercontent.com
SSL callback:unable to get local issuer certificate, preverify_ok=0, ssl_okay=0
Retrying connection without TLS.
Looking up raw.githubusercontent.com
Making HTTPS connection to raw.githubusercontent.com
Alert!: Unable to make secure connection to remote host.

lynx: Can't access startfile http://rawgit.com/transcode-open/apt-cyg/master/apt-cyg
```
Then there was a problem installing cygwin. You should download cygwin without using chocolatey by going to cygwin.com

Then install lots of stuff.
```
apt-cyg install cmake wget git libelf0-devel zlib-devel libicu-devel libgpgme-devel libgpg-error-devel openssl-devel tcsh libncurses-devel gcc4-g++ gdb automake make flex bison libnettle-devel libgcrypt-devel libcrypt-devel
```

Install both libconfig and cmake from source:
```
git clone https://github.com/hyperrealm/libconfig && cd libconfig
git checkout v1.5
autoheader && aclocal && automake --add-missing --copy && autoconf && ./configure
make && make install
```

To compile and run GT.M you need to install and start the cygserver. (During compilation, it's used to build the GT.M help files which are actual GT.M databases.)

In an administrator cygwin-terminal (right click cygwin-terminal and click run as administrator)
```
/usr/bin/cygserver-config
net start cygserver
```

Now, compile GT.M:
```
cd
git clone https://github.com/shabiel/fis-gtm && cd fis-gtm
git checkout cygwin
cmake .
make
```

Follow the original README on how to install GT.M. In short, `make install` makes an installable package; and you then need to do ./configure to actually install GT.M.
