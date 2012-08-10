AC_INIT(src/main.cpp)

AM_INIT_AUTOMAKE(stratu,0.1)

AC_PROG_CC
AC_PROG_CXX

# Check for SDL
SDL_VERSION=1.1.8
AM_PATH_SDL($SDL_VERSION, :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))
AC_CHECK_LIB(SDL_ttf, TTF_Quit, have_sdl_ttf=yes)
CFLAGS="$CFLAGS $SDL_CFLAGS"
CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS -lSDL_ttf"

AC_PROG_INSTALL

AC_OUTPUT(Makefile src/Makefile)
