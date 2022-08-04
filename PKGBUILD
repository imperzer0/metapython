# Mainained by imper <imperator999mcpe@gmail.com>
pkgname="metapython"
pkgver=1.0
pkgrel=0
pkgdesc="Translator from metapython to python code"
author="imperzer0"
url="https://github.com/$author/$pkgname"
arch=("x86_64")
license=('GPL3')
depends=("openssl" "python>=3.10")
makedepends=("cmake>=3.0" "python>=3.10")
optdepends=("bash-completion")

_srcprefix="local:/"
_libfiles=("CMakeLists.txt" "main.cpp" "pycompile.hpp" "pyexec.hpp" "helpers.hpp"
           "parsed_arguments.cpp" "parsed_arguments.h" "defines.h" "tests.cpp" "$pkgname-completion.bash")

for _libfile in ${_libfiles[@]}
{
    source=(${source[@]} "$_srcprefix/$_libfile")
}

for _libfile in ${_libfiles[@]}
{
    md5sums=(${md5sums[@]} "SKIP")
}

_package_version="("$pkgver"-"$pkgrel")"

build()
{
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++\
	      -DAPP_VERSION="$_package_version" -DAPP_NAME="$pkgname" .
	make -j 6
}

package()
{
	install -Dm755 $pkgname "$pkgdir/usr/bin/$pkgname"
	install -Dm644 "$pkgname-completion.bash" "$pkgdir/usr/share/bash-completion/completions/$pkgname"
}

notarch_package()
{
	cp -f $pkgname "$pkgdir/usr/bin/$pkgname"
	chmod 755 "$pkgdir/usr/bin/$pkgname"

	cp -f "$pkgname-completions.bash" "$pkgdir/usr/share/bash-completion/completions/$pkgname"
	chmod 644 "$pkgdir/usr/share/bash-completion/completions/$pkgname"
}