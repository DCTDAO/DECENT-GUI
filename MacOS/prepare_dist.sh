#!/bin/bash

[ $# -lt 2 ] && { echo "Usage: $0 install_dir dcore_version"; exit 1; }

set -e
BASEDIR=$(dirname "$0")

rm -rf $BASEDIR/dist
mkdir -p $BASEDIR/dist/Applications
cp -R $1 $BASEDIR/dist/Applications
chmod +w $BASEDIR/dist/Applications/DECENT.app/Contents/MacOS/*

cp $BASEDIR/Resources/* $BASEDIR/dist/Applications/DECENT.app/Contents/Resources
rm -f $BASEDIR/dist/Applications/DECENT.app/Contents/Info.plist
sed "s/VERSION/$2/" $BASEDIR/Info.plist > $BASEDIR/dist/Applications/DECENT.app/Contents/Info.plist
cd $BASEDIR/dist/Applications/DECENT.app/Contents

mkdir Plugins
cp -R /usr/local/opt/qt/plugins/iconengines Plugins
cp -R /usr/local/opt/qt/plugins/imageformats Plugins
cp -R /usr/local/opt/qt/plugins/platforms Plugins
rm Plugins/platforms/libqwebgl.dylib

mkdir Frameworks
cd Frameworks

# openssl
cp /usr/local/opt/openssl@1.1/lib/libcrypto.1.1.dylib .
cp /usr/local/opt/openssl@1.1/lib/libssl.1.1.dylib .
chmod 644 libssl.1.1.dylib libcrypto.1.1.dylib

install_name_tool -change /usr/local/opt/openssl@1.1/lib/libcrypto.1.1.dylib @executable_path/../Frameworks/libcrypto.1.1.dylib libssl.1.1.dylib

# cryptopp
cp /usr/local/opt/cryptopp/lib/libcryptopp.dylib .
chmod 644 libcryptopp.dylib

# gmp
cp /usr/local/opt/gmp/lib/libgmp.10.dylib .
chmod 644 libgmp.10.dylib

# pbc
cp /usr/local/opt/pbc/lib/libpbc.1.dylib .
chmod 644 libpbc.1.dylib

install_name_tool -change /usr/local/opt/gmp/lib/libgmp.10.dylib @executable_path/../Frameworks/libgmp.10.dylib libpbc.1.dylib

# readline
cp /usr/local/opt/readline/lib/libreadline.8.dylib .
chmod 644 libreadline.8.dylib

# Qt
cp /usr/local/opt/qt/lib/QtCore.framework/Versions/5/QtCore .
cp /usr/local/opt/qt/lib/QtDBus.framework/Versions/5/QtDBus .
cp /usr/local/opt/qt/lib/QtGui.framework/Versions/5/QtGui .
cp /usr/local/opt/qt/lib/QtPrintSupport.framework/Versions/5/QtPrintSupport .
cp /usr/local/opt/qt/lib/QtSvg.framework/Versions/5/QtSvg .
cp /usr/local/opt/qt/lib/QtWidgets.framework/Versions/5/QtWidgets .
chmod 644 QtCore QtDBus QtGui QtPrintSupport QtSvg QtWidgets

QT_PATH=`realpath /usr/local/opt/qt`
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore QtDBus
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore QtGui
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore QtPrintSupport
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore QtSvg
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore QtWidgets
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui QtPrintSupport
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui QtSvg
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui QtWidgets
install_name_tool -change $QT_PATH/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets QtPrintSupport
install_name_tool -change $QT_PATH/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets QtSvg

cd ../Plugins
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore iconengines/libqsvgicon.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui iconengines/libqsvgicon.dylib
install_name_tool -change $QT_PATH/lib/QtSvg.framework/Versions/5/QtSvg @executable_path/../Frameworks/QtSvg iconengines/libqsvgicon.dylib
install_name_tool -change $QT_PATH/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets iconengines/libqsvgicon.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore platforms/libqcocoa.dylib
install_name_tool -change $QT_PATH/lib/QtDBus.framework/Versions/5/QtDBus @executable_path/../Frameworks/QtDBus platforms/libqcocoa.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui platforms/libqcocoa.dylib
install_name_tool -change $QT_PATH/lib/QtPrintSupport.framework/Versions/5/QtPrintSupport @executable_path/../Frameworks/QtPrintSupport platforms/libqcocoa.dylib
install_name_tool -change $QT_PATH/lib/QtSvg.framework/Versions/5/QtSvg @executable_path/../Frameworks/QtSvg platforms/libqcocoa.dylib
install_name_tool -change $QT_PATH/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets platforms/libqcocoa.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore platforms/libqminimal.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui platforms/libqminimal.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore platforms/libqoffscreen.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui platforms/libqoffscreen.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqgif.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqgif.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqicns.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqicns.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqico.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqico.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqjpeg.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqjpeg.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqmacheif.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqmacheif.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqmacjp2.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqmacjp2.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqsvg.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqsvg.dylib
install_name_tool -change $QT_PATH/lib/QtSvg.framework/Versions/5/QtSvg @executable_path/../Frameworks/QtSvg imageformats/libqsvg.dylib
install_name_tool -change $QT_PATH/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets imageformats/libqsvg.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqtga.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqtga.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqtiff.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqtiff.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqwbmp.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqwbmp.dylib
install_name_tool -change $QT_PATH/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore imageformats/libqwebp.dylib
install_name_tool -change $QT_PATH/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui imageformats/libqwebp.dylib

cd ../MacOS
cp /usr/local/bin/ipfs .
install_name_tool -change /usr/local/opt/cryptopp/lib/libcryptopp.dylib @executable_path/../Frameworks/libcryptopp.dylib DECENT
install_name_tool -change /usr/local/opt/gmp/lib/libgmp.10.dylib @executable_path/../Frameworks/libgmp.10.dylib DECENT
install_name_tool -change /usr/local/opt/openssl@1.1/lib/libcrypto.1.1.dylib @executable_path/../Frameworks/libcrypto.1.1.dylib DECENT
install_name_tool -change /usr/local/opt/openssl@1.1/lib/libssl.1.1.dylib @executable_path/../Frameworks/libssl.1.1.dylib DECENT
install_name_tool -change /usr/local/opt/pbc/lib/libpbc.1.dylib @executable_path/../Frameworks/libpbc.1.dylib DECENT
install_name_tool -change /usr/local/opt/readline/lib/libreadline.8.dylib @executable_path/../Frameworks/libreadline.8.dylib DECENT
install_name_tool -change /usr/local/opt/qt/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore DECENT
install_name_tool -change /usr/local/opt/qt/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui DECENT
install_name_tool -change /usr/local/opt/qt/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets DECENT
install_name_tool -add_rpath @executable_path/../Frameworks/ DECENT

(otool -L DECENT | grep -q /usr/local) && echo "DECENT: found /usr/local in RPATH" && exit 1

echo "Prepared DCore $2 distribution"
