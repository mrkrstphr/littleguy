#!/bin/sh

echo "This will do all the autotools stuff so that you can build"
echo "successfully."
echo
echo "When it is finished, take the usual steps to install:"
echo "./configure"
echo "make"
echo "make install"
echo

(automake --version) < /dev/null > /dev/null 2>&1 || {
	echo;
	echo "You must have automake installed to compile";
	echo;
	exit;
}

(autoconf --version) < /dev/null > /dev/null 2>&1 || {
	echo;
	echo "You must have autoconf installed to compile";
	echo;
	exit;
}

echo "Generating configuration files, please wait..."
echo;

aclocal $ACLOCAL_FLAGS || exit;
autoconf || exit;
automake --foreign || exit;

