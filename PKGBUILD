# Maintainer: Patrick Desaulniers <patrick dot desaulniers36 at gmail dot com>

pkgname=wolf-midicurve-git
pkgver=r11.ac178c3
pkgrel=1
pkgdesc="MIDI remapping plugin"
arch=('i686' 'x86_64')
url="https://github.com/wolf-plugins/wolf-midicurve"
license=('GPL')
depends=('gcc-libs' 'glibc' 'libglvnd' 'libx11')
makedepends=('lv2' 'jack')
optdepends=('jack: for standalone application'
            'lv2-host: for lv2 plugin'
            'vst-host: for VST plugin')
provides=("${pkgname%-*}")
conflicts=("${pkgname%-*}")
source=("${pkgname%-*}::git+https://github.com/wolf-plugins/wolf-midicurve")
md5sums=('SKIP')

pkgver() {
    cd "${pkgname%-*}"

    # git describe --long --tags | sed 's/^v//;s/\([^-]*-g\)/r\1/;s/-/./g' 

    printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

prepare() {
    cd "${pkgname%-*}"
    git submodule update --init --recursive
}

build() {
    cd "${pkgname%-*}"
    make
}

package() {
    cd "${pkgname%-*}"
    make DESTDIR="$pkgdir" PREFIX="/usr" VST_FOLDER_NAME=vst install
}
