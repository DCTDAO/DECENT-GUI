#!/bin/bash

[ $# -lt 4 ] && { echo "Usage: $0 dist_dir dcore_version app_identity install_identity"; exit 1; }

(cd $1/Applications && codesign -s "$3" -v DECENT.app -f --deep -vv)

pkgbuild --root $1 --component-plist decent_pkg.plist DECENT.pkg --sign "$4"
productbuild --distribution decent_distribution.plist --resources dist/Applications/DECENT.app/Contents/Resources --package-path DECENT.pkg DECENT-distribution.$2.pkg --sign "$4"
